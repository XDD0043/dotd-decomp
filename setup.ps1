<#
.SYNOPSIS
  One-click setup of the Dawn of the Dragon port (Windows): builds dotd.exe from this source folder and points it at
  your own copy of the game.

.DESCRIPTION
  1. Finds Visual Studio's C++ tools (offers to install the free Build Tools with winget when there are none).
  2. Builds the Release dotd.exe. CMake downloads the SDL and FFmpeg *source* archives itself (checked by SHA-256)
     and compiles them with the same compiler, so nothing else has to be installed.
  3. Asks for the game: a folder dump of the disc (the folder holding PS3_GAME, PS3_GAME itself or USRDIR) or a
     decrypted .iso, which is copied out once. The disc's encrypted EBOOT.BIN is fine: the port decrypts it in
     memory. No RPCS3 is needed. The game files are only ever read.
  4. Writes dotd.ini, checks the install (dotd.exe --check-game) and offers a desktop shortcut.

.PARAMETER GamePath
  The game folder or .iso. Without it a folder picker opens.
.PARAMETER Yes
  Answer every question with its default (no prompts; for scripts).
.PARAMETER NoBuild
  Skip the build (dotd.exe already built): only the game folder, dotd.ini and the check.
.PARAMETER Clean
  Configure the build folder from scratch.
.PARAMETER NoShortcut
  Do not offer the desktop shortcut.
#>
param(
    [string]$GamePath = "",
    [switch]$Yes,
    [switch]$NoBuild,
    [switch]$Clean,
    [switch]$NoShortcut
)

$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$BuildDir = Join-Path $Root "build\windows-msvc"
$ExeDir = Join-Path $BuildDir "Release"
$Exe = Join-Path $ExeDir "dotd.exe"
# BLUS30205 (USA): the only version the port is made from.
$EbootBinSha = "99F8B87105C0E1FD7DEF9B1633536F5DCF3405F606D654A95552B462E1E900CC"
$EbootElfSha = "C6CA6B1FDEF4736DDA071BC406EE7B3EF4961653EFABFCD926A5540B8A2E3455"

function Say([string]$text) { Write-Host $text }
function Step([string]$text) { Write-Host ""; Write-Host "== $text" -ForegroundColor Cyan }
function Warn([string]$text) { Write-Host "warning: $text" -ForegroundColor Yellow }
function Fail([string]$text) {
    Write-Host ""
    Write-Host "Setup stopped: $text" -ForegroundColor Red
    Finish 1
}
function Finish([int]$code) {
    if (-not $Yes) {
        Write-Host ""
        Read-Host "Press Enter to close" | Out-Null
    }
    exit $code
}
function Ask([string]$question, [bool]$default = $true) {
    if ($Yes) { return $default }
    $hint = "[Y/n]"
    if (-not $default) { $hint = "[y/N]" }
    $answer = Read-Host "$question $hint"
    if ([string]::IsNullOrWhiteSpace($answer)) { return $default }
    return $answer.Trim().ToLower().StartsWith("y")
}

Write-Host "The Legend of Spyro: Dawn of the Dragon - native port setup" -ForegroundColor Green
Say "Source folder: $Root"

# ---- 1. compiler ------------------------------------------------------------------------------------------------
function Find-VisualStudio {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) { return $null }
    $path = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ([string]::IsNullOrWhiteSpace($path)) { return $null }
    return ($path | Select-Object -First 1).Trim()
}

# The x64 build environment of vcvars64.bat, imported into this PowerShell process (cl, link, cmake, ninja on PATH).
function Import-VcVars([string]$vsPath) {
    $vcvars = Join-Path $vsPath "VC\Auxiliary\Build\vcvars64.bat"
    if (-not (Test-Path -LiteralPath $vcvars)) { Fail "vcvars64.bat not found in $vsPath" }
    # (through a small batch file: Windows PowerShell mangles quotes inside a cmd /c argument)
    $batch = Join-Path $env:TEMP "dotd-setup-vcvars.cmd"
    Set-Content -LiteralPath $batch -Encoding ASCII -Value @("@call `"$vcvars`" >nul 2>&1", "@if errorlevel 1 exit /b 1", "@set")
    $lines = & cmd.exe /c $batch
    $code = $LASTEXITCODE
    Remove-Item -LiteralPath $batch -ErrorAction SilentlyContinue
    if ($code -ne 0) { Fail "vcvars64.bat failed" }
    foreach ($line in $lines) {
        $eq = $line.IndexOf("=")
        if ($eq -gt 0) { [Environment]::SetEnvironmentVariable($line.Substring(0, $eq), $line.Substring($eq + 1), "Process") }
    }
}

if (-not $NoBuild) {
    Step "1/4  Looking for the C++ compiler (Visual Studio)"
    $vs = Find-VisualStudio
    if ($null -eq $vs) {
        Say "No Visual Studio with the C++ tools was found. The free 'Build Tools for Visual Studio' (about 6 GB)"
        Say "can be installed now with winget; it needs administrator rights and takes a while."
        $winget = Get-Command winget -ErrorAction SilentlyContinue
        if ($null -eq $winget) {
            Fail ("winget is not available. Install 'Build Tools for Visual Studio' with the 'Desktop development with C++'" +
                  " workload from https://visualstudio.microsoft.com/downloads/ and run setup again.")
        }
        if (-not (Ask "Install the Visual Studio Build Tools now?")) { Fail "a C++ compiler is needed to build the game." }
        & winget install --id Microsoft.VisualStudio.2022.BuildTools -e --source winget --accept-package-agreements --accept-source-agreements `
            --override "--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
        $vs = Find-VisualStudio
        if ($null -eq $vs) { Fail "the Build Tools install did not finish. Run setup again once it has." }
    }
    Say "Found: $vs"
    Import-VcVars $vs
    $cmake = Get-Command cmake -ErrorAction SilentlyContinue
    $ninja = Get-Command ninja -ErrorAction SilentlyContinue
    if ($null -eq $cmake -or $null -eq $ninja) {
        Fail ("CMake or Ninja is missing. In the Visual Studio Installer, modify your install and tick " +
              "'C++ CMake tools for Windows' (part of 'Desktop development with C++'), then run setup again.")
    }

    # ---- 2. build -----------------------------------------------------------------------------------------------
    Step "2/4  Building dotd.exe (the first build takes several minutes)"
    Push-Location $Root
    try {
        $cache = Join-Path $BuildDir "CMakeCache.txt"
        if ($Clean -and (Test-Path -LiteralPath $BuildDir)) { Remove-Item -Recurse -Force $BuildDir }
        & cmake --preset windows-msvc
        if ($LASTEXITCODE -ne 0 -and (Test-Path -LiteralPath $cache)) {
            # A build folder from an older configure (another generator or compiler): start it again once.
            Warn "configure failed with the existing build folder; trying again from scratch"
            Remove-Item -LiteralPath $cache -Force
            $files = Join-Path $BuildDir "CMakeFiles"
            if (Test-Path -LiteralPath $files) { Remove-Item -LiteralPath $files -Recurse -Force }
            & cmake --preset windows-msvc
        }
        if ($LASTEXITCODE -ne 0) { Fail "CMake configure failed (see the messages above)." }
        & cmake --build --preset windows-msvc-release --target dotd
        if ($LASTEXITCODE -ne 0) { Fail "the build failed (see the messages above)." }
    } finally {
        Pop-Location
    }
}
if (-not (Test-Path -LiteralPath $Exe)) { Fail "$Exe was not built." }
Say "Built: $Exe"

# ---- 3. the game -------------------------------------------------------------------------------------------------
Step "3/4  Your copy of the game"

# The USRDIR inside a folder dump: the folder itself, PS3_GAME, or the folder above PS3_GAME.
function Resolve-UsrDir([string]$path) {
    foreach ($candidate in @($path, (Join-Path $path "USRDIR"), (Join-Path $path "PS3_GAME\USRDIR"))) {
        if (Test-Path -LiteralPath (Join-Path $candidate "GAME.KP3")) { return (Resolve-Path -LiteralPath $candidate).Path }
    }
    # One level down (e.g. "Legend of Spyro (USA)\Legend of Spyro (USA)\PS3_GAME").
    foreach ($sub in (Get-ChildItem -LiteralPath $path -Directory -ErrorAction SilentlyContinue)) {
        $candidate = Join-Path $sub.FullName "PS3_GAME\USRDIR"
        if (Test-Path -LiteralPath (Join-Path $candidate "GAME.KP3")) { return (Resolve-Path -LiteralPath $candidate).Path }
    }
    return $null
}

function Pick-Game {
    Add-Type -AssemblyName System.Windows.Forms
    Say "Choose what you have:"
    Say "  1  a folder dump of the disc (holds PS3_GAME)   [default]"
    Say "  2  an .iso of the disc"
    $choice = Read-Host "1 or 2"
    if ($choice.Trim() -eq "2") {
        $dialog = New-Object System.Windows.Forms.OpenFileDialog
        $dialog.Title = "Select the Dawn of the Dragon .iso"
        $dialog.Filter = "Disc images (*.iso)|*.iso|All files (*.*)|*.*"
        if ($dialog.ShowDialog() -ne [System.Windows.Forms.DialogResult]::OK) { return "" }
        return $dialog.FileName
    }
    $dialog = New-Object System.Windows.Forms.FolderBrowserDialog
    $dialog.Description = "Select the Dawn of the Dragon game folder (the one holding PS3_GAME)"
    $dialog.ShowNewFolderButton = $false
    if ($dialog.ShowDialog() -ne [System.Windows.Forms.DialogResult]::OK) { return "" }
    return $dialog.SelectedPath
}

# A decrypted .iso: mounted (Windows' own ISO support), checked, its PS3_GAME copied to the user's local app data
# once, unmounted. An encrypted (redump-style) image shows the files but their contents are scrambled.
function Copy-FromIso([string]$iso) {
    $target = Join-Path $env:LOCALAPPDATA "dotd\game"
    $usr = Join-Path $target "PS3_GAME\USRDIR"
    if (Test-Path -LiteralPath (Join-Path $usr "GAME.KP3")) {
        if (-not (Ask "A copy of the game is already in $target. Use it instead of copying the .iso again?")) {
            Remove-Item -Recurse -Force $target
        } else {
            return $usr
        }
    }
    Say "Mounting $iso"
    $image = Mount-DiskImage -ImagePath $iso -PassThru
    try {
        $letter = ($image | Get-Volume).DriveLetter
        if ([string]::IsNullOrEmpty($letter)) { Fail "Windows mounted the .iso without a drive letter." }
        $source = "$($letter):\PS3_GAME"
        if (-not (Test-Path -LiteralPath (Join-Path $source "USRDIR\GAME.KP3"))) { Fail "the .iso holds no PS3_GAME\USRDIR\GAME.KP3." }
        $head = New-Object byte[] 4
        $stream = [System.IO.File]::OpenRead((Join-Path $source "USRDIR\EBOOT.BIN"))
        try { [void]$stream.Read($head, 0, 4) } finally { $stream.Close() }
        $magic = [System.Text.Encoding]::ASCII.GetString($head, 0, 3)
        if ($magic -ne "SCE") {
            Fail ("this .iso is encrypted (a redump-style image: the files are there but scrambled). Decrypt it first " +
                  "with a PS3 ISO decryption tool and its disc key (.dkey), or use a folder dump of the disc.")
        }
        $bytes = (Get-ChildItem -LiteralPath $source -Recurse -File | Measure-Object -Property Length -Sum).Sum
        Say ("Copying the game ({0:N1} GB) to {1}" -f ($bytes / 1GB), $target)
        $free = (Get-PSDrive -Name $target.Substring(0, 1)).Free
        if ($free -lt $bytes + 1GB) { Fail ("not enough free space on {0}: (need {1:N1} GB)" -f $target.Substring(0, 2), ($bytes / 1GB)) }
        New-Item -ItemType Directory -Force (Join-Path $target "PS3_GAME") | Out-Null
        & robocopy $source (Join-Path $target "PS3_GAME") /E /NFL /NDL /NJH /NP /R:1 /W:1 | Out-Null
        if ($LASTEXITCODE -ge 8) { Fail "copying from the .iso failed (robocopy exit $LASTEXITCODE)." }
        # (files from a disc image are read-only; the copy need not be)
        Get-ChildItem -LiteralPath $target -Recurse -File | ForEach-Object { $_.IsReadOnly = $false }
    } finally {
        Dismount-DiskImage -ImagePath $iso | Out-Null
    }
    return $usr
}

if ([string]::IsNullOrWhiteSpace($GamePath)) {
    $ini = Join-Path $ExeDir "dotd.ini"
    if (Test-Path -LiteralPath $ini) {
        $line = Select-String -LiteralPath $ini -Pattern '^\s*usrdir\s*=\s*(.+)$' | Select-Object -First 1
        if ($null -ne $line) {
            $old = $line.Matches[0].Groups[1].Value.Trim()
            if ((Test-Path -LiteralPath (Join-Path $old "GAME.KP3")) -and (Ask "Keep the game folder from the last setup ($old)?")) {
                $GamePath = $old
            }
        }
    }
}
if ([string]::IsNullOrWhiteSpace($GamePath)) {
    if ($Yes) { Fail "no -GamePath given." }
    $GamePath = Pick-Game
    if ([string]::IsNullOrWhiteSpace($GamePath)) { Fail "no game folder chosen." }
}
if (-not (Test-Path -LiteralPath $GamePath)) { Fail "$GamePath does not exist." }

if ($GamePath.ToLower().EndsWith(".iso")) {
    $UsrDir = Copy-FromIso $GamePath
} else {
    $UsrDir = Resolve-UsrDir $GamePath
    if ($null -eq $UsrDir) {
        Fail ("no PS3_GAME\USRDIR\GAME.KP3 under $GamePath. Pick the folder of the disc dump that holds PS3_GAME " +
              "(or PS3_GAME / USRDIR itself).")
    }
}
Say "Game files: $UsrDir"

# The version check: BLUS30205's executable, encrypted (the disc's) or decrypted (RPCS3's EBOOT.elf).
$elf = Join-Path $UsrDir "EBOOT.elf"
$bin = Join-Path $UsrDir "EBOOT.BIN"
if (Test-Path -LiteralPath $elf) {
    if ((Get-FileHash -Algorithm SHA256 -LiteralPath $elf).Hash -ne $EbootElfSha) { Warn "EBOOT.elf is not the BLUS30205 (USA) executable; the port is made from that version only." }
} elseif (Test-Path -LiteralPath $bin) {
    if ((Get-FileHash -Algorithm SHA256 -LiteralPath $bin).Hash -ne $EbootBinSha) { Warn "EBOOT.BIN is not the BLUS30205 (USA) executable; the port is made from that version only." }
} else {
    Fail "the game folder has no EBOOT.BIN (the port reads the shaders from it)."
}

# ---- 4. dotd.ini, check, shortcut ---------------------------------------------------------------------------------
Step "4/4  Settings and a last check"
$ini = Join-Path $ExeDir "dotd.ini"
$usrLine = "usrdir = " + $UsrDir.Replace("\", "/")
if (Test-Path -LiteralPath $ini) {
    $text = Get-Content -LiteralPath $ini
    $found = $false
    $text = $text | ForEach-Object {
        if ($_ -match '^\s*usrdir\s*=') { $found = $true; $usrLine } else { $_ }
    }
    if (-not $found) { $text = @($usrLine) + $text }
} else {
    $text = Get-Content -LiteralPath (Join-Path $Root "dotd.ini.example") | ForEach-Object {
        if ($_ -match '^\s*usrdir\s*=') { $usrLine } else { $_ }
    }
}
# (ASCII without a byte order mark: the port's ini reader expects plain text)
[System.IO.File]::WriteAllLines($ini, [string[]]$text, (New-Object System.Text.UTF8Encoding($false)))
Say "Wrote $ini"

# (the port's log goes to stderr and is dropped here; with "Stop", Windows PowerShell would throw on its first line)
$ErrorActionPreference = "Continue"
$output = & $Exe --check-game 2>$null
$code = $LASTEXITCODE
$ErrorActionPreference = "Stop"
$output | Where-Object { $_ -match '^(ok|error|usrdir):' } | ForEach-Object { Say "  $_" }
if ($code -ne 0) { Fail "the check found a problem (the lines starting with 'error' above)." }

$launcher = Join-Path $Root "launch.cmd"
if (-not $NoShortcut -and (Ask "Create a desktop shortcut?")) {
    $shell = New-Object -ComObject WScript.Shell
    $link = $shell.CreateShortcut((Join-Path ([Environment]::GetFolderPath("Desktop")) "Dawn of the Dragon.lnk"))
    $link.TargetPath = $launcher
    $link.WorkingDirectory = $Root
    $link.IconLocation = "$Exe,0"
    $link.Save()
    Say "Shortcut created on the desktop."
}

Write-Host ""
Write-Host "Done. Start the game with launch.cmd (or the desktop shortcut)." -ForegroundColor Green
if (-not $Yes -and (Ask "Start it now?")) { Start-Process -FilePath $launcher -WorkingDirectory $Root }
Finish 0
