<#
.SYNOPSIS
  The Dawn of the Dragon launcher: builds and starts the port, points it at your copy of the game, and sets the
  graphics options and the keyboard controls. Start it with launcher.cmd.

.DESCRIPTION
  A plain Windows Forms window (part of Windows: nothing to install).
  - Start: starts dotd.exe as it is built (it builds it first only when there is none yet; Build brings it up to
    date). The game's log shows in the window; while the game runs the button stops it.
  - Build: configures and builds dotd.exe (the first build takes several minutes; CMake fetches the SDL and FFmpeg
    sources itself). Without Visual Studio's C++ tools it offers to install the free Build Tools (winget).
  - Game: (the button before the folder): the disc dump's folder (the one holding PS3_GAME, PS3_GAME itself or USRDIR) or a decrypted .iso,
    copied out once to %LOCALAPPDATA%\dotd\game. The game files are only ever read.
  - Graphics / Game: written to dotd.ini next to dotd.exe as soon as they change (README "Resolution",
    "Full screen", "Anti-aliasing").
  - Controls: the keyboard pad, the way RPCS3 sets it (click a button, press its key): dotd.ini key_<button> lines.
  Command-line options are for starting dotd.exe by hand (README); most have a dotd.ini line too.

.PARAMETER SelfTest
  (development) Checks the parts that need no window (dotd.ini editing, the key tables) and exits.
.PARAMETER Screenshot
  (development) Saves the window to this PNG and exits; with -Dialog controls, the Controls dialog.
#>
param(
    [switch]$SelfTest,
    [string]$Screenshot = "",
    [string]$Dialog = ""
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Windows.Forms, System.Drawing

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$BuildDir = Join-Path $Root "build\windows-msvc"
$ExeDir = Join-Path $BuildDir "Release"
$Exe = Join-Path $ExeDir "dotd.exe"
$Ini = Join-Path $ExeDir "dotd.ini"
$StateDir = Join-Path $env:LOCALAPPDATA "dotd"       # the launcher's logs and job scripts; the .iso copy
$IsoCopy = Join-Path $StateDir "game"
# BLUS30205 (USA): the only version the port is made from.
$EbootBinSha = "99F8B87105C0E1FD7DEF9B1633536F5DCF3405F606D654A95552B462E1E900CC"
$EbootElfSha = "C6CA6B1FDEF4736DDA071BC406EE7B3EF4961653EFABFCD926A5540B8A2E3455"
$Oem = [System.Text.Encoding]::GetEncoding([System.Globalization.CultureInfo]::CurrentCulture.TextInfo.OEMCodePage)
New-Item -ItemType Directory -Force $StateDir | Out-Null

# ---- native helpers: DPI awareness, the key names Windows shows, and a form that catches every key -----------------
# (KeyCaptureForm: while Capturing, ProcessCmdKey takes each key press before the controls see it, arrows, Tab, Enter
# and Space included, and reports its scan code, which is what SDL and dotd's key_ lines go by.)
Add-Type -ReferencedAssemblies System.Windows.Forms, System.Drawing -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace DotdLauncher {
    // A ring of moving rainbow colours around the control it holds (its Padding is the ring's width), drawn while
    // Active: the button to press next.
    public class RainbowRing : Panel {
        readonly Timer timer = new Timer();
        float phase;
        bool active;
        public RainbowRing() {
            SetStyle(ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer |
                     ControlStyles.ResizeRedraw, true);
            timer.Interval = 30;
            timer.Tick += delegate { phase = (phase + 5f) % 360f; Invalidate(); };
        }
        public bool Active {
            get { return active; }
            set { active = value; if (value) timer.Start(); else timer.Stop(); Invalidate(); }
        }
        // The held control sits one pixel into the band with that outer pixel clipped off: a push button paints its
        // outermost pixels in the window colour, which would show as a gap between the ring and its border.
        protected override void OnControlAdded(ControlEventArgs e) {
            base.OnControlAdded(e);
            e.Control.SizeChanged += delegate { Fit(); };
            Fit();
        }
        void Fit() {
            if (Controls.Count == 0) return;
            Control c = Controls[0];
            int p = Math.Max(1, Padding.Left);
            c.Location = new Point(p - 1, p - 1);
            c.Region = new Region(new Rectangle(1, 1, c.Width - 2, c.Height - 2));
            Size = new Size(c.Width + 2 * (p - 1), c.Height + 2 * (p - 1));
        }
        static Color Hue(double degrees) {
            double h = ((degrees % 360) + 360) % 360 / 60.0;
            double x = 1 - Math.Abs(h % 2 - 1);
            double r = 0, g = 0, b = 0;
            if (h < 1) { r = 1; g = x; } else if (h < 2) { r = x; g = 1; } else if (h < 3) { g = 1; b = x; }
            else if (h < 4) { g = x; b = 1; } else if (h < 5) { r = x; b = 1; } else { r = 1; b = x; }
            return Color.FromArgb((int)(r * 255), (int)(g * 255), (int)(b * 255));
        }
        // A square band of even width (Padding.Left) right around the held control, pixel-crisp (no smoothing) like the
        // button's own edges: each 2-pixel piece coloured by its distance along the band, the hues moving round.
        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            if (!active) return;
            Graphics g = e.Graphics;
            g.SmoothingMode = SmoothingMode.None;
            int w = Math.Max(1, Padding.Left), W = Width, H = Height;
            double perimeter = 2.0 * (W + H);
            const int step = 2;
            for (int x = 0; x < W; x += step) {
                int rw = Math.Min(step, W - x);
                Piece(g, x, 0, rw, w, x, perimeter);                       // top, left to right
                Piece(g, x, H - w, rw, w, W + H + (W - x - rw), perimeter);  // bottom, right to left
            }
            for (int y = w; y < H - w; y += step) {
                int rh = Math.Min(step, H - w - y);
                Piece(g, W - w, y, w, rh, W + y, perimeter);                  // right, top to bottom
                Piece(g, 0, y, w, rh, 2 * W + H + (H - y - rh), perimeter);  // left, bottom to top
            }
        }
        void Piece(Graphics g, int x, int y, int rw, int rh, double along, double perimeter) {
            using (SolidBrush brush = new SolidBrush(Hue(along / perimeter * 360.0 - phase))) g.FillRectangle(brush, x, y, rw, rh);
        }
        protected override void Dispose(bool disposing) { if (disposing) timer.Dispose(); base.Dispose(disposing); }
    }
    // The game folder: a rounded, lightly shaded chip with the path (shortened in the middle when long), softer than an
    // input box. A click works like the Game: button.
    public class PathBox : Control {
        public PathBox() {
            SetStyle(ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer |
                     ControlStyles.ResizeRedraw | ControlStyles.SupportsTransparentBackColor, true);
            Cursor = Cursors.Hand;
        }
        protected override void OnTextChanged(EventArgs e) { base.OnTextChanged(e); Invalidate(); }
        protected override void OnPaint(PaintEventArgs e) {
            Graphics g = e.Graphics;
            g.SmoothingMode = SmoothingMode.AntiAlias;
            Color back = Parent != null ? Parent.BackColor : SystemColors.Control;
            g.Clear(back);
            RectangleF r = new RectangleF(0.5f, 0.5f, Width - 1.5f, Height - 1.5f);
            float d = Math.Min(r.Height, 12f);
            using (GraphicsPath path = new GraphicsPath()) {
                path.AddArc(r.X, r.Y, d, d, 180, 90);
                path.AddArc(r.Right - d, r.Y, d, d, 270, 90);
                path.AddArc(r.Right - d, r.Bottom - d, d, d, 0, 90);
                path.AddArc(r.X, r.Bottom - d, d, d, 90, 90);
                path.CloseFigure();
                // (a shade between the window's grey and an input's white, a border lighter than an input's)
                using (SolidBrush fill = new SolidBrush(Color.FromArgb(Math.Min(255, back.R + 8), Math.Min(255, back.G + 8), Math.Min(255, back.B + 9))))
                    g.FillPath(fill, path);
                using (Pen border = new Pen(Color.FromArgb(205, 205, 212)))
                    g.DrawPath(border, path);
            }
            Rectangle text = new Rectangle(8, 0, Width - 16, Height);
            TextRenderer.DrawText(g, Text, Font, text, ForeColor,
                TextFormatFlags.VerticalCenter | TextFormatFlags.Left | TextFormatFlags.PathEllipsis | TextFormatFlags.NoPrefix |
                TextFormatFlags.SingleLine);
        }
    }
    public static class Native {
        [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
        [DllImport("user32.dll", CharSet = CharSet.Unicode)] static extern int GetKeyNameText(int lParam, StringBuilder name, int size);
        // The key's name on this keyboard layout (e.g. "Page Down", "Num 0", or "Q" for the A key of an AZERTY).
        public static string KeyLabel(int scancode, bool extended) {
            StringBuilder name = new StringBuilder(64);
            int lParam = (scancode << 16) | (extended ? 1 << 24 : 0);
            return GetKeyNameText(lParam, name, name.Capacity) > 0 ? name.ToString() : "";
        }
    }
    public class KeyCapturedEventArgs : EventArgs {
        public int Scancode; public bool Extended; public Keys Key;
    }
    public class KeyCaptureForm : Form {
        public bool Capturing;
        public event EventHandler<KeyCapturedEventArgs> KeyCaptured;
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData) {
            if (Capturing && (msg.Msg == 0x100 || msg.Msg == 0x104)) {  // WM_KEYDOWN, WM_SYSKEYDOWN
                long lParam = msg.LParam.ToInt64();
                KeyCapturedEventArgs e = new KeyCapturedEventArgs();
                e.Scancode = (int)((lParam >> 16) & 0xFF);
                e.Extended = ((lParam >> 24) & 1) != 0;
                e.Key = keyData & Keys.KeyCode;
                EventHandler<KeyCapturedEventArgs> handler = KeyCaptured;
                if (handler != null) handler(this, e);
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}
"@

# ---- keys ------------------------------------------------------------------------------------------------------------
# SDL's key names by Windows scan code (generated from SDL's scancodes_windows.h and SDL_keymap.c): the index is the
# scan code byte, plus 0x80 for an E0-prefixed (extended) key, as SDL's Windows backend makes it.
$ScancodeNames = @{
    1 = 'Escape'; 2 = '1'; 3 = '2'; 4 = '3'; 5 = '4'; 6 = '5'
    7 = '6'; 8 = '7'; 9 = '8'; 10 = '9'; 11 = '0'; 12 = '-'
    13 = '='; 14 = 'Backspace'; 15 = 'Tab'; 16 = 'Q'; 17 = 'W'; 18 = 'E'
    19 = 'R'; 20 = 'T'; 21 = 'Y'; 22 = 'U'; 23 = 'I'; 24 = 'O'
    25 = 'P'; 26 = '['; 27 = ']'; 28 = 'Return'; 29 = 'Left Ctrl'; 30 = 'A'
    31 = 'S'; 32 = 'D'; 33 = 'F'; 34 = 'G'; 35 = 'H'; 36 = 'J'
    37 = 'K'; 38 = 'L'; 39 = ';'; 40 = ''''; 41 = '`'; 42 = 'Left Shift'
    43 = '\'; 44 = 'Z'; 45 = 'X'; 46 = 'C'; 47 = 'V'; 48 = 'B'
    49 = 'N'; 50 = 'M'; 51 = ','; 52 = '.'; 53 = '/'; 54 = 'Right Shift'
    55 = 'Keypad *'; 56 = 'Left Alt'; 57 = 'Space'; 58 = 'CapsLock'; 59 = 'F1'; 60 = 'F2'
    61 = 'F3'; 62 = 'F4'; 63 = 'F5'; 64 = 'F6'; 65 = 'F7'; 66 = 'F8'
    67 = 'F9'; 68 = 'F10'; 69 = 'Numlock'; 70 = 'ScrollLock'; 71 = 'Keypad 7'; 72 = 'Keypad 8'
    73 = 'Keypad 9'; 74 = 'Keypad -'; 75 = 'Keypad 4'; 76 = 'Keypad 5'; 77 = 'Keypad 6'; 78 = 'Keypad +'
    79 = 'Keypad 1'; 80 = 'Keypad 2'; 81 = 'Keypad 3'; 82 = 'Keypad 0'; 83 = 'Keypad .'; 86 = 'NonUSBackslash'
    87 = 'F11'; 88 = 'F12'; 89 = 'Keypad ='; 92 = 'International 6'; 100 = 'F13'; 101 = 'F14'
    102 = 'F15'; 103 = 'F16'; 104 = 'F17'; 105 = 'F18'; 106 = 'F19'; 107 = 'F20'
    108 = 'F21'; 109 = 'F22'; 110 = 'F23'; 112 = 'International 2'; 113 = 'Language 2'; 114 = 'Language 1'
    115 = 'International 1'; 118 = 'F24'; 119 = 'Language 4'; 120 = 'Language 3'; 121 = 'International 4'; 123 = 'International 5'
    125 = 'International 3'; 126 = 'Keypad ,'; 135 = 'Again'; 136 = 'Undo'; 138 = 'Paste'; 144 = 'MediaTrackPrevious'
    151 = 'Cut'; 152 = 'Copy'; 153 = 'MediaTrackNext'; 156 = 'Keypad Enter'; 157 = 'Right Ctrl'; 160 = 'Mute'
    162 = 'MediaPlayPause'; 164 = 'MediaStop'; 172 = 'Eject'; 174 = 'VolumeDown'; 176 = 'VolumeUp'; 178 = 'AC Home'
    181 = 'Keypad /'; 182 = 'Right Shift'; 183 = 'PrintScreen'; 184 = 'Right Alt'; 187 = 'Help'; 190 = 'AC New'
    191 = 'AC Open'; 192 = 'AC Close'; 197 = 'Numlock'; 198 = 'Pause'; 199 = 'Home'; 200 = 'Up'
    201 = 'PageUp'; 203 = 'Left'; 205 = 'Right'; 207 = 'End'; 208 = 'Down'; 209 = 'PageDown'
    210 = 'Insert'; 211 = 'Delete'; 215 = 'AC Save'; 216 = 'AC Print'; 219 = 'Left GUI'; 220 = 'Right GUI'
    221 = 'Application'; 222 = 'Power'; 223 = 'Sleep'; 227 = 'Wake'; 229 = 'AC Search'; 230 = 'AC Bookmarks'
    231 = 'AC Refresh'; 232 = 'AC Stop'; 233 = 'AC Forward'; 234 = 'AC Back'; 237 = 'MediaSelect'
}
$NameToIndex = @{}
foreach ($entry in $ScancodeNames.GetEnumerator()) {
    $lower = $entry.Value.ToLower()
    if (-not $NameToIndex.ContainsKey($lower)) { $NameToIndex[$lower] = [int]$entry.Key }
}

# The keyboard pad's actions: dotd.ini key_<Name>, the label in the Controls dialog, the default keys. Keep in step with
# dotd's src/platform/sdl/app.cpp kKeyActions (RPCS3's default keyboard pad plus a few extra keys).
$KeyActions = @(
    @{ Name = "dpad_up"; Label = "Up"; Default = "Up" },
    @{ Name = "dpad_left"; Label = "Left"; Default = "Left" },
    @{ Name = "dpad_right"; Label = "Right"; Default = "Right" },
    @{ Name = "dpad_down"; Label = "Down"; Default = "Down" },
    @{ Name = "lstick_up"; Label = "Up"; Default = "W" },
    @{ Name = "lstick_left"; Label = "Left"; Default = "A" },
    @{ Name = "lstick_right"; Label = "Right"; Default = "D" },
    @{ Name = "lstick_down"; Label = "Down"; Default = "S" },
    @{ Name = "l1"; Label = "L1"; Default = "Q" },
    @{ Name = "l2"; Label = "L2"; Default = "R, 1" },
    @{ Name = "l3"; Label = "L3"; Default = "F, Tab" },
    @{ Name = "select"; Label = "Select"; Default = "Space, Backspace" },
    @{ Name = "start"; Label = "Start"; Default = "Return" },
    @{ Name = "r1"; Label = "R1"; Default = "E" },
    @{ Name = "r2"; Label = "R2"; Default = "T, 3" },
    @{ Name = "r3"; Label = "R3"; Default = "G, Keypad 0" },
    @{ Name = "triangle"; Label = "Triangle"; Default = "V, I" },
    @{ Name = "square"; Label = "Square"; Default = "Z, J" },
    @{ Name = "circle"; Label = "Circle"; Default = "C, Escape, L" },
    @{ Name = "cross"; Label = "Cross"; Default = "X, K" },
    @{ Name = "rstick_up"; Label = "Up"; Default = "Home, Keypad 8" },
    @{ Name = "rstick_left"; Label = "Left"; Default = "Delete, Keypad 4" },
    @{ Name = "rstick_right"; Label = "Right"; Default = "PageDown, Keypad 6" },
    @{ Name = "rstick_down"; Label = "Down"; Default = "End, Keypad 5, Keypad 2" }
)

function Split-Keys([string]$keys) {
    return @($keys -split "," | ForEach-Object { $_.Trim() } | Where-Object { $_ -ne "" })
}

# A key list as shown on a button: the first key's name on this keyboard, "+N" for more.
function Format-Keys([string]$keys) {
    $list = @(Split-Keys $keys)  # (@(): a one-key list comes back from a function as the bare string)
    if ($list.Count -eq 0) { return "-" }
    $labels = foreach ($key in $list) {
        $label = $key
        if ($NameToIndex.ContainsKey($key.ToLower())) {
            $index = $NameToIndex[$key.ToLower()]
            $shown = [DotdLauncher.Native]::KeyLabel($index -band 0x7F, $index -ge 0x80)
            if ($shown -ne "") { $label = $shown }
        }
        $label
    }
    return (@($labels) -join ", ")
}

# ---- dotd.ini --------------------------------------------------------------------------------------------------------
function Read-Ini {
    $values = @{}
    if (-not (Test-Path -LiteralPath $Ini)) { return $values }
    foreach ($line in [System.IO.File]::ReadAllLines($Ini)) {
        if ($line -match '^\s*([A-Za-z0-9_]+)\s*=\s*(.*?)\s*$') { $values[$matches[1]] = $matches[2] }
    }
    return $values
}

# Sets keys in dotd.ini, keeping every other line and comment: an existing "key = ..." line is replaced, else the new
# line goes under its commented example ("# key = ...", dotd.ini.example's), else at the end. A $null value removes the
# key. Without a dotd.ini the file starts as dotd.ini.example.
function Write-IniValues([System.Collections.IDictionary]$values) {
    $lines = New-Object System.Collections.Generic.List[string]
    $source = $Ini
    if (-not (Test-Path -LiteralPath $source)) { $source = Join-Path $Root "dotd.ini.example" }
    if (Test-Path -LiteralPath $source) { foreach ($line in [System.IO.File]::ReadAllLines($source)) { $lines.Add($line) } }
    foreach ($key in @($values.Keys)) {
        $value = $values[$key]
        $pattern = '^\s*' + [regex]::Escape($key) + '\s*='
        $example = '^\s*#\s*' + [regex]::Escape($key) + '\s*='
        $active = -1
        $commented = -1
        for ($i = 0; $i -lt $lines.Count; $i++) {
            if ($lines[$i] -match $pattern) {
                if ($active -lt 0) { $active = $i } else { $lines.RemoveAt($i); $i-- }
            } elseif ($commented -lt 0 -and $lines[$i] -match $example) {
                $commented = $i
            }
        }
        if ($null -eq $value) {
            if ($active -ge 0) { $lines.RemoveAt($active) }
            continue
        }
        $text = "$key = $value"
        if ($active -ge 0) { $lines[$active] = $text }
        elseif ($commented -ge 0) { $lines.Insert($commented + 1, $text) }
        else { $lines.Add($text) }
    }
    New-Item -ItemType Directory -Force (Split-Path -Parent $Ini) | Out-Null
    # (UTF-8 without a byte order mark: the port reads plain text)
    [System.IO.File]::WriteAllLines($Ini, $lines.ToArray(), (New-Object System.Text.UTF8Encoding($false)))
}

# "1920x1080" (also "1920 x 1080", "1920*1080") into @(w, h), or $null.
function Parse-Resolution([string]$text) {
    if ($text -match '^\s*(\d{2,5})\s*[x*,]\s*(\d{2,5})') { return @([int]$matches[1], [int]$matches[2]) }
    return $null
}

# ---- the game folder -------------------------------------------------------------------------------------------------
# The USRDIR inside a folder dump: the folder itself, PS3_GAME, the folder above PS3_GAME, or one level further down
# (e.g. "Legend of Spyro (USA)\Legend of Spyro (USA)\PS3_GAME").
function Resolve-UsrDir([string]$path) {
    foreach ($candidate in @($path, (Join-Path $path "USRDIR"), (Join-Path $path "PS3_GAME\USRDIR"))) {
        if (Test-Path -LiteralPath (Join-Path $candidate "GAME.KP3")) { return (Resolve-Path -LiteralPath $candidate).Path }
    }
    foreach ($sub in (Get-ChildItem -LiteralPath $path -Directory -ErrorAction SilentlyContinue)) {
        $candidate = Join-Path $sub.FullName "PS3_GAME\USRDIR"
        if (Test-Path -LiteralPath (Join-Path $candidate "GAME.KP3")) { return (Resolve-Path -LiteralPath $candidate).Path }
    }
    return $null
}

function Current-UsrDir {
    $values = Read-Ini
    if ($values.ContainsKey("usrdir")) {
        $usr = $values["usrdir"].Replace("/", "\")
        if (Test-Path -LiteralPath (Join-Path $usr "GAME.KP3")) { return $usr }
    }
    return $null
}

function Find-VisualStudio {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path -LiteralPath $vswhere)) { return $null }
    $path = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ([string]::IsNullOrWhiteSpace($path)) { return $null }
    return ($path | Select-Object -First 1).Trim()
}

# ---- self-test (development) -----------------------------------------------------------------------------------------
if ($SelfTest) {
    $failures = 0
    function Check([string]$what, $got, $want) {
        if ("$got" -eq "$want") { Write-Host "ok    $what" } else { Write-Host "FAIL  $what`n      got:  $got`n      want: $want"; $script:failures++ }
    }
    $savedIni = $Ini
    $Ini = Join-Path $StateDir "selftest\dotd.ini"
    Remove-Item -Recurse -Force (Split-Path -Parent $Ini) -ErrorAction SilentlyContinue
    New-Item -ItemType Directory -Force (Split-Path -Parent $Ini) | Out-Null
    [System.IO.File]::WriteAllLines($Ini, [string[]]@("# comment", "usrdir = C:/old", "vsync = 1", "# msaa = 4", "fps = 60", "fps = 30"))
    Write-IniValues ([ordered]@{ usrdir = "D:/Games/USRDIR"; msaa = 8; vsync = $null; key_cross = "J"; fps = 144 })
    Check "dotd.ini edited in place" (([System.IO.File]::ReadAllLines($Ini)) -join " | ") "# comment | usrdir = D:/Games/USRDIR | # msaa = 4 | msaa = 8 | fps = 144 | key_cross = J"
    $read = Read-Ini
    Check "dotd.ini read back" ("{0} {1} {2}" -f $read["msaa"], $read["key_cross"], $read.ContainsKey("vsync")) "8 J False"
    Remove-Item -Force $Ini
    Write-IniValues @{ fxaa = 1 }
    $fromExample = [System.IO.File]::ReadAllLines($Ini)
    Check "a new dotd.ini starts as dotd.ini.example" (($fromExample -match '^fxaa = 1$').Count -eq 1 -and ($fromExample -match '^language = 1$').Count -eq 1) "True"
    $Ini = $savedIni
    Check "scan code 0x1C" $ScancodeNames[0x1C] "Return"
    Check "scan code E0 53" $ScancodeNames[0x53 + 0x80] "Delete"
    Check "scan code 0x52 (numpad)" $ScancodeNames[0x52] "Keypad 0"
    Check "scan code E0 51" $ScancodeNames[0x51 + 0x80] "PageDown"
    $unknown = @()
    foreach ($action in $KeyActions) { foreach ($k in (Split-Keys $action.Default)) { if (-not $NameToIndex.ContainsKey($k.ToLower())) { $unknown += $k } } }
    Check "every default key has a scan code" ($unknown -join ",") ""
    Check "key labels of Delete, Keypad 4" (Format-Keys "Delete, Keypad 4") ("{0}, {1}" -f [DotdLauncher.Native]::KeyLabel(0x53, $true), [DotdLauncher.Native]::KeyLabel(0x4B, $false))
    Check "key label of one key" (Format-Keys "Return") ([DotdLauncher.Native]::KeyLabel(0x1C, $false))
    Check "resolution parse" ((Parse-Resolution "2560 x 1440 (screen)") -join "x") "2560x1440"
    Check "resolution parse, bad" ($null -eq (Parse-Resolution "big")) "True"
    Remove-Item -Recurse -Force (Split-Path -Parent (Join-Path $StateDir "selftest\dotd.ini")) -ErrorAction SilentlyContinue
    if ($failures -eq 0) { Write-Host "self-test passed" } else { Write-Host "$failures failure(s)" }
    exit $failures
}

# ---- the window ------------------------------------------------------------------------------------------------------
[DotdLauncher.Native]::SetProcessDPIAware() | Out-Null
[System.Windows.Forms.Application]::EnableVisualStyles()
$UiFont = New-Object System.Drawing.Font("Segoe UI", 9)
$BoldFont = New-Object System.Drawing.Font("Segoe UI", 9, [System.Drawing.FontStyle]::Bold)

$form = New-Object System.Windows.Forms.Form
$form.Text = "Dawn of the Dragon - Launcher"
$form.Font = $UiFont
$form.StartPosition = "CenterScreen"
if (Test-Path -LiteralPath $Exe) { try { $form.Icon = [System.Drawing.Icon]::ExtractAssociatedIcon($Exe) } catch { } }
$Scale = $form.CreateGraphics().DpiX / 96.0
function S([double]$value) { return [int]([math]::Round($value * $Scale)) }
$form.ClientSize = New-Object System.Drawing.Size((S 760), (S 600))
$form.MinimumSize = New-Object System.Drawing.Size((S 640), (S 480))

$layout = New-Object System.Windows.Forms.TableLayoutPanel
$layout.Dock = "Fill"
$layout.ColumnCount = 1
$layout.Padding = New-Object System.Windows.Forms.Padding((S 8))
$form.Controls.Add($layout)

# Toolbar.
$toolbar = New-Object System.Windows.Forms.FlowLayoutPanel
$toolbar.AutoSize = $true
$toolbar.WrapContents = $false
$toolbar.Dock = "Fill"
function New-ToolButton([string]$text, [bool]$bold = $false) {
    $button = New-Object System.Windows.Forms.Button
    $button.Text = $text
    $button.AutoSize = $true
    $button.Padding = New-Object System.Windows.Forms.Padding((S 6), (S 3), (S 6), (S 3))
    $button.Margin = New-Object System.Windows.Forms.Padding(0, (S 3), (S 6), (S 3))  # (in line with the ringed button)
    if ($bold) { $button.Font = $BoldFont }
    $toolbar.Controls.Add($button)
    return $button
}
$PlayGlyph = [string][char]0x25B6
$StopGlyph = [string][char]0x25A0
$startButton = New-ToolButton "$PlayGlyph  Start" $true
$buildButton = New-ToolButton "Build"
$controlsButton = New-ToolButton "Controls..."
$layout.Controls.Add($toolbar)

# The game line: "Game:" and the folder, cut with "..." when long (the whole path in its tool tip).
$gamePanel = New-Object System.Windows.Forms.TableLayoutPanel
$gamePanel.AutoSize = $true
$gamePanel.Dock = "Fill"
$gamePanel.ColumnCount = 2
[void]$gamePanel.ColumnStyles.Add((New-Object System.Windows.Forms.ColumnStyle("AutoSize")))
[void]$gamePanel.ColumnStyles.Add((New-Object System.Windows.Forms.ColumnStyle("Percent", 100)))
$gamePanel.Margin = New-Object System.Windows.Forms.Padding(0, (S 8), 0, (S 4))
# The Game: button chooses the game folder; while none is set a rainbow ring turns around it (Update-GameLabel).
$gameButton = New-Object System.Windows.Forms.Button
$gameButton.Text = "Game:"
$gameButton.Font = $BoldFont
$gameButton.AutoSize = $true
$gameButton.Padding = New-Object System.Windows.Forms.Padding((S 6), (S 2), (S 6), (S 2))
$gameButton.Margin = New-Object System.Windows.Forms.Padding(0)
$gameRing = New-Object DotdLauncher.RainbowRing
$gameRing.Padding = New-Object System.Windows.Forms.Padding((S 3))
$gameRing.Margin = New-Object System.Windows.Forms.Padding(0, 0, (S 6), 0)
$gameRing.Controls.Add($gameButton)  # (the ring sizes itself around it: RainbowRing.Fit)
$gameTitle = $gameRing
$gameLabel = New-Object DotdLauncher.PathBox
$gameLabel.Dock = "Fill"
$gameLabel.Margin = New-Object System.Windows.Forms.Padding(0, (S 3), 0, (S 3))
$gameLabel.AccessibleName = "Game folder"
$gamePanel.Controls.AddRange(@($gameTitle, $gameLabel))
$layout.Controls.Add($gamePanel)

$separator = New-Object System.Windows.Forms.Label
$separator.BorderStyle = "Fixed3D"
$separator.Height = 2
$separator.Dock = "Fill"
$separator.Margin = New-Object System.Windows.Forms.Padding(0, (S 2), 0, (S 6))
$layout.Controls.Add($separator)

# A group of settings: a GroupBox holding rows of (label, control, control, ...).
function New-SettingsGroup([string]$title) {
    $group = New-Object System.Windows.Forms.GroupBox
    $group.Text = $title
    $group.AutoSize = $true
    $group.Dock = "Fill"
    $group.Padding = New-Object System.Windows.Forms.Padding((S 8), (S 6), (S 8), (S 6))
    $table = New-Object System.Windows.Forms.TableLayoutPanel
    $table.AutoSize = $true
    $table.Dock = "Fill"
    $table.ColumnCount = 4
    $group.Controls.Add($table)
    $layout.Controls.Add($group)
    return $table
}
function Add-Row($table, [string]$label, [object[]]$controls) {
    $caption = New-Object System.Windows.Forms.Label
    $caption.Text = $label
    $caption.AutoSize = $true
    $caption.Anchor = "Left"
    $caption.Margin = New-Object System.Windows.Forms.Padding(0, (S 6), (S 10), (S 6))
    $table.Controls.Add($caption)
    # (names for screen readers and UI Automation: the row's caption, or the control's own text)
    if ([string]::IsNullOrEmpty($controls[0].AccessibleName)) { $controls[0].AccessibleName = $label }
    foreach ($control in $controls) {
        $control.Anchor = "Left"
        $control.Margin = New-Object System.Windows.Forms.Padding(0, (S 3), (S 14), (S 3))
        $table.Controls.Add($control)
    }
    for ($i = $controls.Count; $i -lt 3; $i++) { $table.Controls.Add((New-Object System.Windows.Forms.Label)) }
}
function New-Combo([object[]]$items, [bool]$editable = $false, [int]$width = 150) {
    $combo = New-Object System.Windows.Forms.ComboBox
    if ($editable) { $combo.DropDownStyle = "DropDown" } else { $combo.DropDownStyle = "DropDownList" }
    $combo.Width = S $width
    foreach ($item in $items) { [void]$combo.Items.Add($item) }
    return $combo
}
function New-Check([string]$text) {
    $check = New-Object System.Windows.Forms.CheckBox
    $check.Text = $text
    $check.AutoSize = $true
    return $check
}

# Graphics.
$graphics = New-SettingsGroup "Graphics"
$screen = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
$resolutions = New-Object System.Collections.Generic.List[string]
foreach ($size in @("1280x720", "1600x900", "1920x1080", "2560x1440", "3200x1800", "3840x2160", "5120x2880", "7680x4320")) {
    $wh = Parse-Resolution $size
    if ($size -eq "1280x720") { $resolutions.Add("1280 x 720 (PS3)") }
    elseif ($wh[0] -le $screen.Width -and $wh[1] -le $screen.Height) {
        if ($wh[0] -eq $screen.Width -and $wh[1] -eq $screen.Height) { $resolutions.Add("$($wh[0]) x $($wh[1]) (screen)") }
        else { $resolutions.Add("$($wh[0]) x $($wh[1])") }
    }
}
if (-not ($resolutions | Where-Object { $_ -like "*(screen)" })) {
    $resolutions.Add("$($screen.Width) x $($screen.Height) (screen)")  # (another aspect: the view widens, README)
}
$resolutionCombo = New-Combo $resolutions.ToArray() $true 170
$fullscreenCheck = New-Check "Full screen"
$fullscreenKind = New-Combo @("Borderless", "Exclusive") $false 110
$fullscreenKind.AccessibleName = "Full screen kind"
Add-Row $graphics "Resolution" @($resolutionCombo, $fullscreenCheck, $fullscreenKind)
$msaaCombo = New-Combo @("Off", "2x", "4x", "8x", "16x") $false 170
$a2cCheck = New-Check "Smooth leaves and grass"
$fxaaCheck = New-Check "FXAA"
Add-Row $graphics "MSAA" @($msaaCombo, $fxaaCheck)
Add-Row $graphics "" @($a2cCheck)
$a2cCheck.AccessibleName = "Smooth leaves and grass"
$fpsCombo = New-Combo @("60 (original)", "No cap (display rate)", "120", "144", "165", "240") $true 170
$vsyncCheck = New-Check "Vsync"
$showFpsCheck = New-Check "Show FPS"
Add-Row $graphics "Frame rate" @($fpsCombo, $vsyncCheck, $showFpsCheck)

# Game.
$gameGroup = New-SettingsGroup "Game"
# (CELL_SYSUTIL_SYSTEMPARAM_ID_LANG values of the disc's ten languages)
$Languages = [ordered]@{ "English (US)" = 1; "English (UK)" = 18; "Francais" = 2; "Deutsch" = 4; "Espanol" = 3; "Italiano" = 5;
                         "Nederlands" = 6; "Svenska" = 13; "Norsk" = 15; "Dansk" = 14; "Suomi" = 12 }
$languageCombo = New-Combo @($Languages.Keys) $false 170
$confirmCombo = New-Combo @("Cross", "Circle") $false 110
$confirmCombo.AccessibleName = "Confirm button"
$confirmLabel = New-Object System.Windows.Forms.Label
$confirmLabel.Text = "Confirm button"
$confirmLabel.AutoSize = $true
Add-Row $gameGroup "Language" @($languageCombo, $confirmLabel, $confirmCombo)

$tips = New-Object System.Windows.Forms.ToolTip
$tips.SetToolTip($resolutionCombo, "The pixels the game is rendered at. 16:9 sizes keep the original picture, only sharper; another aspect widens the view.`nType your own as WxH.")
$tips.SetToolTip($fullscreenKind, "Borderless: other windows can show over the game, Alt+Tab is instant.`nExclusive: the screen switches to the resolution's mode; minimised on Alt+Tab.")
$tips.SetToolTip($msaaCombo, "Multisampling: smooth polygon edges (the PS3 game had none). F3 changes it in the game.")
$tips.SetToolTip($a2cCheck, "Alpha-to-coverage: MSAA also smooths cut-out leaves, grass and fences (Ctrl+F3 in the game).")
$tips.SetToolTip($fxaaCheck, "An edge filter on the 3D picture (not the HUD), instead of MSAA: smooths every edge, softens fine detail a little (Shift+F3).")
$tips.SetToolTip($fpsCombo, "60 is the original's timing. Above it the game keeps its speed (60 Hz timing). F2 switches 60 / no cap in the game.")

# The log.
$log = New-Object System.Windows.Forms.TextBox
$log.Multiline = $true
$log.ReadOnly = $true
$log.ScrollBars = "Vertical"
$log.WordWrap = $false
$log.Dock = "Fill"
$log.BackColor = [System.Drawing.SystemColors]::Window
$log.Font = New-Object System.Drawing.Font("Consolas", 9)
$log.Margin = New-Object System.Windows.Forms.Padding(0, (S 8), 0, 0)
$log.AccessibleName = "Log"
$layout.Controls.Add($log)
for ($i = 0; $i -lt $layout.Controls.Count - 1; $i++) { [void]$layout.RowStyles.Add((New-Object System.Windows.Forms.RowStyle("AutoSize"))) }
[void]$layout.RowStyles.Add((New-Object System.Windows.Forms.RowStyle("Percent", 100)))

$status = New-Object System.Windows.Forms.StatusStrip
$statusLabel = New-Object System.Windows.Forms.ToolStripStatusLabel
$statusLabel.Spring = $true
$statusLabel.TextAlign = "MiddleLeft"
$progress = New-Object System.Windows.Forms.ToolStripProgressBar
$progress.Visible = $false
[void]$status.Items.Add($statusLabel)
[void]$status.Items.Add($progress)
$form.Controls.Add($status)
$layout.BringToFront()  # (docking: the Fill panel last, after the status strip took the bottom)

function Set-Status([string]$text) { $statusLabel.Text = $text }
function Add-Log([string]$text) {
    if ($log.TextLength -gt 600000) { $log.Text = $log.Text.Substring(300000) }
    $log.AppendText($text + "`r`n")
}
function Show-Message([string]$text, [string]$icon = "Information") {
    [void][System.Windows.Forms.MessageBox]::Show($form, $text, "Dawn of the Dragon", "OK", $icon)
}
function Ask-YesNo([string]$text) {
    return [System.Windows.Forms.MessageBox]::Show($form, $text, "Dawn of the Dragon", "YesNo", "Question") -eq "Yes"
}
# An event handler's body: an error goes to the log and a message box instead of ending the launcher.
function Invoke-Safe([scriptblock]$body) {
    try { & $body } catch { Add-Log ("error: " + $_.Exception.Message); Show-Message $_.Exception.Message "Error" }
}

# ---- settings <-> dotd.ini ---------------------------------------------------------------------------------------------
$script:Loading = $false
function Select-Item($combo, [string]$text) {
    $index = $combo.Items.IndexOf($text)
    if ($index -ge 0) { $combo.SelectedIndex = $index } else { $combo.Text = $text }
}
function Load-Settings {
    $script:Loading = $true
    try {
        $v = Read-Ini
        $get = { param($key, $default) if ($v.ContainsKey($key) -and $v[$key] -ne "") { $v[$key] } else { $default } }
        $res = Parse-Resolution (& $get "resolution" "")
        if ($null -eq $res -or ($res[0] -eq 1280 -and $res[1] -eq 720) -or ($res[0] -eq 0)) {
            $resolutionCombo.SelectedIndex = 0
        } else {
            $match = $resolutionCombo.Items | Where-Object { $_ -like "$($res[0]) x $($res[1])*" } | Select-Object -First 1
            if ($match) { Select-Item $resolutionCombo $match } else { $resolutionCombo.Text = "$($res[0]) x $($res[1])" }
        }
        $fullscreenCheck.Checked = (& $get "fullscreen" "0") -match '^(1|borderless|exclusive)$'
        $kind = & $get "fullscreen_mode" "borderless"
        if ((& $get "fullscreen" "0") -eq "exclusive") { $kind = "exclusive" }
        if ($kind -eq "exclusive") { $fullscreenKind.SelectedIndex = 1 } else { $fullscreenKind.SelectedIndex = 0 }
        $msaa = [int](& $get "msaa" "0")
        $msaaCombo.SelectedIndex = [math]::Max(0, [array]::IndexOf(@(0, 2, 4, 8, 16), $msaa))
        $script:A2cWanted = (& $get "alpha_to_coverage" "1") -ne "0"
        $script:FxaaWanted = (& $get "fxaa" "0") -ne "0"
        $fps = & $get "fps" "60"
        if ($fps -eq "60") { $fpsCombo.SelectedIndex = 0 } elseif ($fps -eq "0") { $fpsCombo.SelectedIndex = 1 } else { Select-Item $fpsCombo $fps }
        $vsyncCheck.Checked = (& $get "vsync" "1") -ne "0"
        $showFpsCheck.Checked = (& $get "show_fps" "0") -ne "0"
        $language = [int](& $get "language" "1")
        $name = $Languages.Keys | Where-Object { $Languages[$_] -eq $language } | Select-Object -First 1
        if ($name) { Select-Item $languageCombo $name } else { $languageCombo.SelectedIndex = 0 }
        if ((& $get "enter_button" "1") -eq "0") { $confirmCombo.SelectedIndex = 1 } else { $confirmCombo.SelectedIndex = 0 }
        Update-AaChecks
    } finally {
        $script:Loading = $false
    }
}
function Save-Settings {
    if ($script:Loading) { return }
    $values = [ordered]@{}
    $res = Parse-Resolution $resolutionCombo.Text
    if ($null -eq $res) {
        Set-Status "Resolution: write it as WIDTHxHEIGHT, e.g. 1920x1080 (not saved)"
    } elseif ($res[0] -eq 1280 -and $res[1] -eq 720) {
        $values["resolution"] = $null
    } else {
        $values["resolution"] = "$($res[0])x$($res[1])"
    }
    if ($fullscreenCheck.Checked) { $values["fullscreen"] = 1 } else { $values["fullscreen"] = 0 }
    $values["fullscreen_mode"] = @("borderless", "exclusive")[[math]::Max(0, $fullscreenKind.SelectedIndex)]
    $values["msaa"] = @(0, 2, 4, 8, 16)[[math]::Max(0, $msaaCombo.SelectedIndex)]
    $values["alpha_to_coverage"] = [int]$script:A2cWanted  # (the choice, kept while MSAA is off)
    $msaaOn = $msaaCombo.SelectedIndex -gt 0
    $values["fxaa"] = [int]((-not $msaaOn) -and $script:FxaaWanted)
    $fps = $fpsCombo.Text
    if ($fpsCombo.SelectedIndex -eq 0) { $fps = "60" } elseif ($fpsCombo.SelectedIndex -eq 1) { $fps = "0" }
    if ($fps -match '^\s*(\d{1,4})\s*$') { $values["fps"] = [int]$matches[1] } else { Set-Status "Frame rate: a number, e.g. 144 (not saved)" }
    $values["vsync"] = [int]$vsyncCheck.Checked
    $values["show_fps"] = [int]$showFpsCheck.Checked
    if ($Languages.Contains($languageCombo.Text)) { $values["language"] = $Languages[$languageCombo.Text] }
    $values["enter_button"] = @(1, 0)[[math]::Max(0, $confirmCombo.SelectedIndex)]
    Write-IniValues $values
}

# MSAA and FXAA exclude each other: with MSAA on, FXAA is greyed out and unticked; with FXAA ticked, the MSAA list is
# greyed out (at Off). "Smooth leaves and grass" (alpha-to-coverage, an MSAA feature) can be ticked only with MSAA. Each
# box keeps what was chosen while it is greyed out ($script:A2cWanted / FxaaWanted) and shows it again when it applies.
$script:A2cWanted = $true
$script:FxaaWanted = $false
$script:SyncingAa = $false
function Update-AaChecks {
    $script:SyncingAa = $true
    try {
        $msaaOn = $msaaCombo.SelectedIndex -gt 0
        $a2cCheck.Enabled = $msaaOn
        $a2cCheck.Checked = $msaaOn -and $script:A2cWanted
        $fxaaCheck.Enabled = -not $msaaOn
        $fxaaCheck.Checked = (-not $msaaOn) -and $script:FxaaWanted
        $msaaCombo.Enabled = -not $fxaaCheck.Checked
    } finally {
        $script:SyncingAa = $false
    }
}
$a2cCheck.add_CheckedChanged({ if (-not $script:SyncingAa -and $a2cCheck.Enabled) { $script:A2cWanted = $a2cCheck.Checked } })
$fxaaCheck.add_CheckedChanged({ if (-not $script:SyncingAa -and $fxaaCheck.Enabled) { $script:FxaaWanted = $fxaaCheck.Checked; Update-AaChecks } })
$msaaCombo.add_SelectedIndexChanged({ if (-not $script:Loading) { Update-AaChecks } })
$onChange = { Invoke-Safe { Save-Settings } }
foreach ($combo in @($resolutionCombo, $fullscreenKind, $msaaCombo, $fpsCombo, $languageCombo, $confirmCombo)) {
    $combo.add_SelectedIndexChanged($onChange)
}
foreach ($combo in @($resolutionCombo, $fpsCombo)) { $combo.add_Leave($onChange) }  # (typed values)
foreach ($check in @($fullscreenCheck, $a2cCheck, $fxaaCheck, $vsyncCheck, $showFpsCheck)) { $check.add_CheckedChanged($onChange) }

function Update-GameLabel {
    $usr = Current-UsrDir
    if ($null -ne $usr) {
        $gameLabel.Text = $usr
        $gameLabel.ForeColor = [System.Drawing.SystemColors]::ControlText
        $tips.SetToolTip($gameLabel, "$usr`n(click to change)")
        $gameRing.Active = $false
    } else {
        $gameLabel.Text = "not set: click Game: (your PS3_GAME folder or a decrypted .iso)"
        $gameLabel.ForeColor = [System.Drawing.Color]::Firebrick
        $gameRing.Active = $true
    }
}

# ---- jobs: a batch file run hidden, its output streamed into the log ---------------------------------------------------
# (The output goes to a file the timer reads: a PowerShell event handler cannot run on the process's reader thread.)
$script:Job = $null
$jobTimer = New-Object System.Windows.Forms.Timer
$jobTimer.Interval = 200
function Start-BatchJob([string]$title, [string]$name, [string[]]$lines, [scriptblock]$onExit) {
    if ($null -ne $script:Job) { Show-Message "Wait for this to finish first: $($script:Job.Title)"; return $false }
    $batch = Join-Path $StateDir "$name.cmd"
    $logFile = Join-Path $StateDir "$name.log"
    [System.IO.File]::WriteAllLines($batch, [string[]]$lines, [System.Text.Encoding]::Default)  # (cmd reads the ANSI code page)
    Remove-Item -LiteralPath $logFile -ErrorAction SilentlyContinue
    $info = New-Object System.Diagnostics.ProcessStartInfo
    $info.FileName = "cmd.exe"
    $info.Arguments = "/c `"`"$batch`" > `"$logFile`" 2>&1`""
    $info.UseShellExecute = $false
    $info.CreateNoWindow = $true
    $info.WorkingDirectory = $Root
    $process = [System.Diagnostics.Process]::Start($info)
    $script:Job = @{ Title = $title; Name = $name; Process = $process; Log = $logFile; Position = 0; Partial = ""; OnExit = $onExit }
    Add-Log ""
    Add-Log "== $title"
    Set-Status "$title..."
    Update-Buttons
    $jobTimer.Start()
    return $true
}
function Read-JobOutput($job) {
    if (-not (Test-Path -LiteralPath $job.Log)) { return }
    $stream = [System.IO.File]::Open($job.Log, "Open", "Read", "ReadWrite")
    try {
        $length = $stream.Length
        if ($length -le $job.Position) { return }
        [void]$stream.Seek($job.Position, "Begin")
        $buffer = New-Object byte[] ($length - $job.Position)
        $count = $stream.Read($buffer, 0, $buffer.Length)
        $job.Position += $count
        $text = $job.Partial + $Oem.GetString($buffer, 0, $count)
        $parts = $text -split "`n"
        $job.Partial = $parts[-1]
        for ($i = 0; $i -lt $parts.Count - 1; $i++) {
            $line = $parts[$i].TrimEnd("`r")
            Add-Log $line
            if ($line -match '^\[(\d+)/(\d+)\]') {  # (Ninja's progress)
                $progress.Visible = $true
                $progress.Maximum = [int]$matches[2]
                $progress.Value = [math]::Min([int]$matches[1], [int]$matches[2])
            }
        }
    } finally {
        $stream.Close()
    }
}
$jobTimer.add_Tick({
    Invoke-Safe {
        $job = $script:Job
        if ($null -eq $job) { $jobTimer.Stop(); return }
        Read-JobOutput $job
        if ($job.Process.HasExited) {
            Read-JobOutput $job
            if ($job.Partial -ne "") { Add-Log $job.Partial }
            $code = $job.Process.ExitCode
            if ($job.Name -eq "game" -and $script:StopRequested) { Add-Log "== The game was stopped" }
            elseif ($job.Name -eq "game") { Add-Log "== The game ended (exit code $code)" }
            else { Add-Log "== $($job.Title): done (exit code $code)" }
            $script:Job = $null
            $jobTimer.Stop()
            $progress.Visible = $false
            Update-Buttons
            if ($null -ne $job.OnExit) { & $job.OnExit $code }
        }
    }
})
$script:StopRequested = $false
function Stop-CurrentJob {
    if ($null -eq $script:Job) { return }
    $script:StopRequested = $true
    & taskkill.exe /PID $script:Job.Process.Id /T /F | Out-Null
}
function Update-Buttons {
    $busy = $null -ne $script:Job
    $playing = $busy -and $script:Job.Name -eq "game"
    if ($playing) { $startButton.Text = "$StopGlyph  Stop" } else { $startButton.Text = "$PlayGlyph  Start" }
    $startButton.Enabled = (-not $busy) -or $playing
    $buildButton.Enabled = -not $busy
    $gameButton.Enabled = -not $busy
}

# ---- build -----------------------------------------------------------------------------------------------------------
# A build in a batch file: Visual Studio's x64 environment (vcvars64.bat), then CMake. $configure: configure first
# (otherwise only when the build folder is new). $then runs after a successful build.
$script:AfterBuild = $null
function Start-Build([bool]$configure, [scriptblock]$then) {
    $vs = Find-VisualStudio
    if ($null -eq $vs) { Offer-BuildTools; return }
    $vcvars = Join-Path $vs "VC\Auxiliary\Build\vcvars64.bat"
    $lines = @(
        "@echo off",
        "call `"$vcvars`" >nul 2>&1",
        "if errorlevel 1 (echo error: vcvars64.bat failed & exit /b 1)",
        "where cmake >nul 2>&1 || (echo error: CMake is missing. In the Visual Studio Installer tick C++ CMake tools for Windows. & exit /b 1)",
        "where ninja >nul 2>&1 || (echo error: Ninja is missing. In the Visual Studio Installer tick C++ CMake tools for Windows. & exit /b 1)",
        "cd /d `"$Root`""
    )
    if ($configure -or -not (Test-Path -LiteralPath (Join-Path $BuildDir "CMakeCache.txt"))) {
        $lines += @(
            "cmake --preset windows-msvc",
            "if not errorlevel 1 goto configured",
            "if not exist `"build\windows-msvc\CMakeCache.txt`" exit /b 1",
            "echo The build folder comes from an older configure: configuring it again from scratch.",
            "del /q `"build\windows-msvc\CMakeCache.txt`"",
            "if exist `"build\windows-msvc\CMakeFiles`" rmdir /s /q `"build\windows-msvc\CMakeFiles`"",
            "cmake --preset windows-msvc || exit /b 1",
            ":configured"
        )
    }
    $lines += @("cmake --build --preset windows-msvc-release --target dotd || exit /b 1")
    $script:AfterBuild = $then
    [void](Start-BatchJob "Building dotd.exe" "build" $lines {
        param($code)
        if ($code -eq 0) {
            Set-Status "Built: $Exe"
            $next = $script:AfterBuild
            $script:AfterBuild = $null
            if ($null -ne $next) { & $next }
        } else {
            $script:AfterBuild = $null
            Set-Status "The build failed (see the log)"
            Show-Message "The build failed: the log shows why." "Warning"
        }
    })
}

function Offer-BuildTools {
    $winget = Get-Command winget -ErrorAction SilentlyContinue
    if ($null -eq $winget) {
        Show-Message ("Building needs Visual Studio's C++ tools. Install 'Build Tools for Visual Studio' with the 'Desktop " +
                      "development with C++' workload from https://visualstudio.microsoft.com/downloads/ and try again.") "Warning"
        return
    }
    if (-not (Ask-YesNo ("Building needs Visual Studio's C++ tools, and none were found. Install the free 'Build Tools for " +
                         "Visual Studio' now (about 6 GB, needs administrator rights, takes a while)?"))) { return }
    [void](Start-BatchJob "Installing the Visual Studio Build Tools" "buildtools" @(
        "@echo off",
        "winget install --id Microsoft.VisualStudio.2022.BuildTools -e --source winget --accept-package-agreements --accept-source-agreements --override `"--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended`""
    ) {
        param($code)
        if ($null -ne (Find-VisualStudio)) { Set-Status "Build Tools installed: click Build" } else { Set-Status "The Build Tools install did not finish (see the log)" }
    })
}

# ---- start -----------------------------------------------------------------------------------------------------------
function Start-Game {
    if ($null -eq (Current-UsrDir)) {
        Show-Message "Choose your copy of the game first (the Game: button)." "Warning"
        return
    }
    Save-Settings
    $lines = @("@echo off", "cd /d `"$ExeDir`"", "`"$Exe`"")
    [void](Start-BatchJob "Playing (the game's log follows)" "game" $lines {
        param($code)
        if ($script:StopRequested) { Set-Status "The game was stopped" }
        elseif ($code -eq 0) { Set-Status "The game ended" }
        else { Set-Status "The game ended with code $code (see the log)" }
        $script:StopRequested = $false
    })
}
function On-Start {
    if ($null -ne $script:Job -and $script:Job.Name -eq "game") { Stop-CurrentJob; return }
    $log.Clear()  # (each start of the game begins with a clean log)
    if ($null -eq (Current-UsrDir)) {
        Choose-Game
        return
    }
    if (-not (Test-Path -LiteralPath $Exe)) {
        if (-not (Ask-YesNo "dotd.exe is not built yet. Build it now (the first build takes several minutes) and then start?")) { return }
        Start-Build $true { Start-Game }
        return
    }
    Start-Game  # (the exe as it is: no build first, Build brings it up to date)
}

# ---- the game folder -------------------------------------------------------------------------------------------------
function Set-GameFolder([string]$usr) {
    $elf = Join-Path $usr "EBOOT.elf"
    $bin = Join-Path $usr "EBOOT.BIN"
    if (Test-Path -LiteralPath $elf) {
        if ((Get-FileHash -Algorithm SHA256 -LiteralPath $elf).Hash -ne $EbootElfSha) { Add-Log "warning: EBOOT.elf is not the BLUS30205 (USA) executable; the port is made from that version only." }
    } elseif (Test-Path -LiteralPath $bin) {
        if ((Get-FileHash -Algorithm SHA256 -LiteralPath $bin).Hash -ne $EbootBinSha) { Add-Log "warning: EBOOT.BIN is not the BLUS30205 (USA) executable; the port is made from that version only." }
    } else {
        Show-Message "This game folder has no EBOOT.BIN (the port reads the shaders from it)." "Warning"
        return
    }
    Write-IniValues @{ usrdir = $usr.Replace("\", "/") }
    Update-GameLabel
    Add-Log "Game files: $usr"
    if (Test-Path -LiteralPath $Exe) {
        [void](Start-BatchJob "Checking the game files" "check" @("@echo off", "cd /d `"$ExeDir`"", "`"$Exe`" --check-game 2>nul") {
            param($code)
            if ($code -eq 0) { Set-Status "Ready to play" } else { Set-Status "The check found a problem (the lines starting with 'error')" }
        })
    } else {
        Set-Status "Game folder set. Click Start to build dotd.exe and play."
    }
}

# A decrypted .iso: mounted (Windows' own ISO support), checked, its PS3_GAME copied to %LOCALAPPDATA%\dotd\game once,
# unmounted (a hidden PowerShell job; the copy's file list shows in the log).
function Copy-Iso([string]$iso) {
    $usr = Join-Path $IsoCopy "PS3_GAME\USRDIR"
    if (Test-Path -LiteralPath (Join-Path $usr "GAME.KP3")) {
        if (Ask-YesNo "A copy of the game from an .iso is already in $IsoCopy. Use it instead of copying again?") { Set-GameFolder $usr; return }
        Remove-Item -Recurse -Force $IsoCopy
    }
    $copyScript = Join-Path $StateDir "copy-iso.ps1"
    Set-Content -LiteralPath $copyScript -Encoding UTF8 -Value @'
param([string]$Iso, [string]$Target)
$ErrorActionPreference = "Stop"
Write-Output "Mounting $Iso"
$image = Mount-DiskImage -ImagePath $Iso -PassThru
try {
    $letter = ($image | Get-Volume).DriveLetter
    if ([string]::IsNullOrEmpty($letter)) { Write-Output "error: Windows mounted the .iso without a drive letter."; exit 1 }
    $source = "$($letter):\PS3_GAME"
    if (-not (Test-Path -LiteralPath (Join-Path $source "USRDIR\GAME.KP3"))) { Write-Output "error: the .iso holds no PS3_GAME\USRDIR\GAME.KP3."; exit 1 }
    $head = New-Object byte[] 4
    $stream = [System.IO.File]::OpenRead((Join-Path $source "USRDIR\EBOOT.BIN"))
    try { [void]$stream.Read($head, 0, 4) } finally { $stream.Close() }
    if ([System.Text.Encoding]::ASCII.GetString($head, 0, 3) -ne "SCE") {
        Write-Output "error: this .iso is encrypted (a redump-style image). Decrypt it first with a PS3 ISO decryption tool and its disc key (.dkey), or use a folder dump of the disc."
        exit 1
    }
    $bytes = (Get-ChildItem -LiteralPath $source -Recurse -File | Measure-Object -Property Length -Sum).Sum
    $free = (Get-PSDrive -Name $Target.Substring(0, 1)).Free
    if ($free -lt $bytes + 1GB) { Write-Output ("error: not enough free space on {0} (need {1:N1} GB)" -f $Target.Substring(0, 2), ($bytes / 1GB)); exit 1 }
    Write-Output ("Copying the game ({0:N1} GB) to {1}" -f ($bytes / 1GB), $Target)
    New-Item -ItemType Directory -Force (Join-Path $Target "PS3_GAME") | Out-Null
    & robocopy $source (Join-Path $Target "PS3_GAME") /E /NDL /NJH /NJS /NP /R:1 /W:1
    if ($LASTEXITCODE -ge 8) { Write-Output "error: copying from the .iso failed (robocopy exit $LASTEXITCODE)."; exit 1 }
    Get-ChildItem -LiteralPath $Target -Recurse -File | ForEach-Object { $_.IsReadOnly = $false }
    Write-Output "Copied."
} finally {
    Dismount-DiskImage -ImagePath $Iso | Out-Null
}
exit 0
'@
    $script:IsoUsr = $usr
    [void](Start-BatchJob "Copying the game from the .iso" "copy-iso" @(
        "@echo off",
        "powershell -NoProfile -ExecutionPolicy Bypass -File `"$copyScript`" -Iso `"$iso`" -Target `"$IsoCopy`""
    ) {
        param($code)
        if ($code -eq 0) { Set-GameFolder $script:IsoUsr } else { Set-Status "The .iso was not copied (see the log)"; Show-Message "The .iso could not be used: the log says why." "Warning" }
    })
}

# The "what do you have" question, then a folder or file picker.
function Choose-Game {
    $ask = New-Object System.Windows.Forms.Form
    $ask.Text = "Your copy of the game"
    $ask.Font = $UiFont
    $ask.FormBorderStyle = "FixedDialog"
    $ask.MaximizeBox = $false
    $ask.MinimizeBox = $false
    $ask.StartPosition = "CenterParent"
    $ask.AutoSize = $true
    $ask.AutoSizeMode = "GrowAndShrink"
    $panel = New-Object System.Windows.Forms.FlowLayoutPanel
    $panel.FlowDirection = "TopDown"
    $panel.AutoSize = $true
    $panel.Padding = New-Object System.Windows.Forms.Padding((S 12))
    $text = New-Object System.Windows.Forms.Label
    $text.Text = "Where is your copy of The Legend of Spyro: Dawn of the Dragon (BLUS30205)?"
    $text.AutoSize = $true
    $text.Margin = New-Object System.Windows.Forms.Padding(0, 0, 0, (S 10))
    $panel.Controls.Add($text)
    foreach ($choice in @(@("Folder", "A folder dump of the disc (the folder holding PS3_GAME)..."), @("Iso", "A decrypted disc image (.iso)..."))) {
        $button = New-Object System.Windows.Forms.Button
        $button.Text = $choice[1]
        $button.Tag = $choice[0]
        $button.AutoSize = $true
        $button.Width = S 420
        $button.Height = S 34
        $button.TextAlign = "MiddleLeft"
        $button.Margin = New-Object System.Windows.Forms.Padding(0, 0, 0, (S 6))
        $button.add_Click({ $script:GameChoice = $this.Tag; $this.FindForm().DialogResult = "OK" })
        $panel.Controls.Add($button)
    }
    $cancel = New-Object System.Windows.Forms.Button
    $cancel.Text = "Cancel"
    $cancel.DialogResult = "Cancel"
    $cancel.AutoSize = $true
    $panel.Controls.Add($cancel)
    $ask.CancelButton = $cancel
    $ask.Controls.Add($panel)
    $script:GameChoice = $null
    if ($ask.ShowDialog($form) -ne "OK") { return }
    if ($script:GameChoice -eq "Iso") {
        $dialog = New-Object System.Windows.Forms.OpenFileDialog
        $dialog.Title = "Select the Dawn of the Dragon .iso"
        $dialog.Filter = "Disc images (*.iso)|*.iso|All files (*.*)|*.*"
        if ($dialog.ShowDialog($form) -ne "OK") { return }
        Copy-Iso $dialog.FileName
        return
    }
    $dialog = New-Object System.Windows.Forms.FolderBrowserDialog
    $dialog.Description = "Select the Dawn of the Dragon game folder (the one holding PS3_GAME, or PS3_GAME itself)"
    $dialog.ShowNewFolderButton = $false
    if ($dialog.ShowDialog($form) -ne "OK") { return }
    $usr = Resolve-UsrDir $dialog.SelectedPath
    if ($null -eq $usr) {
        Show-Message ("No PS3_GAME\USRDIR\GAME.KP3 under $($dialog.SelectedPath). Pick the folder of the disc dump that " +
                      "holds PS3_GAME (or PS3_GAME / USRDIR itself).") "Warning"
        return
    }
    Set-GameFolder $usr
}

# ---- controls ----------------------------------------------------------------------------------------------------------
# RPCS3's pad dialog, for the keyboard: a box per button with the key on it. Click one, press the key (Esc cancels);
# a key taken by another button moves. Saved as dotd.ini key_<button> lines (only those that differ from the defaults).
function Show-Controls([string]$screenshotPath = "") {
    $values = Read-Ini
    $bindings = @{}
    foreach ($action in $KeyActions) {
        $key = "key_" + $action.Name
        if ($values.ContainsKey($key)) { $bindings[$action.Name] = $values[$key] } else { $bindings[$action.Name] = $action.Default }
    }
    $dialog = New-Object DotdLauncher.KeyCaptureForm
    $dialog.Text = "Controls - keyboard"
    $dialog.Font = $UiFont
    $dialog.FormBorderStyle = "FixedDialog"
    $dialog.MaximizeBox = $false
    $dialog.MinimizeBox = $false
    $dialog.StartPosition = "CenterParent"
    $dialog.ClientSize = New-Object System.Drawing.Size((S 1124), (S 520))
    $buttons = @{}
    $script:Capture = $null
    $hint = New-Object System.Windows.Forms.Label

    # (every key of the button, spelled out; one too long for the button ends in "..." with the whole list in a tooltip,
    # from the button's AutoEllipsis)
    function Refresh-Binding([string]$name) {
        $buttons[$name].Text = Format-Keys $bindings[$name]
    }
    $countdown = New-Object System.Windows.Forms.Timer
    $countdown.Interval = 1000
    $countdown.add_Tick({ Invoke-Safe {
        $c = $script:Capture
        if ($null -eq $c) { $countdown.Stop(); return }
        $c.Left--
        if ($c.Left -le 0) {
            $countdown.Stop()
            $dialog.Capturing = $false
            $script:Capture = $null
            Refresh-Binding $c.Name
            $hint.Text = "No key pressed: unchanged."
        } else {
            $buttons[$c.Name].Text = "Press a key ($($c.Left))"
        }
    } })
    $onBindingClick = { Invoke-Safe {
        if ($null -ne $script:Capture) { Refresh-Binding $script:Capture.Name }
        $script:Capture = @{ Name = $this.Tag; Left = 5 }
        $this.Text = "Press a key (5)"
        $dialog.Capturing = $true
        $countdown.Stop()
        $countdown.Start()
    } }
    $dialog.add_KeyCaptured({
        param($sender, $e)
        Invoke-Safe { Apply-CapturedKey $e }
    })
    function Apply-CapturedKey($e) {
        $c = $script:Capture
        if ($null -eq $c) { return }
        $countdown.Stop()
        $dialog.Capturing = $false
        $script:Capture = $null
        $index = $e.Scancode + $(if ($e.Extended) { 0x80 } else { 0 })
        if ($e.Scancode -eq 0x01 -and -not $e.Extended) { Refresh-Binding $c.Name; $hint.Text = "Cancelled."; return }
        if ($e.Scancode -eq 0x38) { Refresh-Binding $c.Name; $hint.Text = "Alt is kept for Alt+Enter (full screen)."; return }
        if (-not $ScancodeNames.ContainsKey($index)) { Refresh-Binding $c.Name; $hint.Text = "That key cannot be used (scan code $index)."; return }
        $name = $ScancodeNames[$index]
        $hint.Text = ""
        # The key leaves any other button it was on.
        foreach ($other in @($bindings.Keys)) {
            if ($other -eq $c.Name) { continue }
            $before = @(Split-Keys $bindings[$other])
            $kept = @($before | Where-Object { $_.ToLower() -ne $name.ToLower() })
            if ($kept.Count -ne $before.Count) {
                $bindings[$other] = $kept -join ", "
                Refresh-Binding $other
                $hint.Text = "$(Format-Keys $name) moved here from another button."
            }
        }
        $bindings[$c.Name] = $name
        Refresh-Binding $c.Name
        if ($hint.Text -notlike "*moved*") { $hint.Text = "Set to $(Format-Keys $name)." }
    }

    # A titled box with the key button, at (x, y) in 96-dpi units, $width wide (the default fits "End, Num 5, Num 2").
    function Add-Binding($parent, [string]$name, [int]$x, [int]$y, [int]$width = 146) {
        $action = $KeyActions | Where-Object { $_.Name -eq $name } | Select-Object -First 1
        $box = New-Object System.Windows.Forms.GroupBox
        $box.Text = $action.Label
        $box.Location = New-Object System.Drawing.Point((S $x), (S $y))
        $box.Size = New-Object System.Drawing.Size((S $width), (S 54))
        $button = New-Object System.Windows.Forms.Button
        $button.Tag = $name
        $button.AutoEllipsis = $true
        $button.Location = New-Object System.Drawing.Point((S 10), (S 20))
        $button.Size = New-Object System.Drawing.Size((S ($width - 20)), (S 26))
        $button.add_Click($onBindingClick)
        $box.Controls.Add($button)
        $parent.Controls.Add($box)
        $buttons[$name] = $button
        Refresh-Binding $name
    }
    # A group of four (up, left, right, down) like RPCS3's d-pad and sticks.
    function Add-Cross([string]$title, [string]$prefix, [int]$x, [int]$y) {
        $group = New-Object System.Windows.Forms.GroupBox
        $group.Text = $title
        $group.Location = New-Object System.Drawing.Point((S $x), (S $y))
        $group.Size = New-Object System.Drawing.Size((S 330), (S 196))
        $dialog.Controls.Add($group)
        $names = @("up", "left", "right", "down")
        if ($prefix -eq "face") { $names = @("triangle", "square", "circle", "cross") }
        $spots = @(@(92, 20), @(8, 76), @(176, 76), @(92, 132))
        for ($i = 0; $i -lt 4; $i++) {
            $name = $names[$i]
            if ($prefix -ne "face") { $name = "$($prefix)_$name" }
            Add-Binding $group $name $spots[$i][0] $spots[$i][1]
        }
    }
    Add-Cross "D-Pad" "dpad" 10 8
    Add-Cross "Left Stick" "lstick" 10 210
    Add-Cross "Face Buttons" "face" 784 8
    Add-Cross "Right Stick" "rstick" 784 210
    Add-Binding $dialog "l1" 352 12 136
    Add-Binding $dialog "l2" 352 72 136
    Add-Binding $dialog "select" 494 12 136
    Add-Binding $dialog "start" 494 72 136
    Add-Binding $dialog "r1" 636 12 136
    Add-Binding $dialog "r2" 636 72 136
    Add-Binding $dialog "l3" 416 348 136
    Add-Binding $dialog "r3" 572 348 136
    $hint.Location = New-Object System.Drawing.Point((S 10), (S 418))
    $hint.Size = New-Object System.Drawing.Size((S 1104), (S 22))
    $dialog.Controls.Add($hint)

    $defaultsButton = New-Object System.Windows.Forms.Button
    $defaultsButton.Text = "Restore defaults"
    $defaultsButton.Location = New-Object System.Drawing.Point((S 10), (S 470))
    $defaultsButton.Size = New-Object System.Drawing.Size((S 130), (S 30))
    $defaultsButton.add_Click({ Invoke-Safe {
        foreach ($action in $KeyActions) { $bindings[$action.Name] = $action.Default; Refresh-Binding $action.Name }
        $hint.Text = "The default keys (RPCS3's keyboard pad, and a second key on some buttons). Save to keep them."
    } })
    $saveButton = New-Object System.Windows.Forms.Button
    $saveButton.Text = "Save"
    $saveButton.Location = New-Object System.Drawing.Point((S 894), (S 470))
    $saveButton.Size = New-Object System.Drawing.Size((S 105), (S 30))
    $saveButton.add_Click({
        $changes = [ordered]@{}
        foreach ($action in $KeyActions) {
            $now = (Split-Keys $bindings[$action.Name]) -join ", "
            $default = (Split-Keys $action.Default) -join ", "
            if ($now -eq $default) { $changes["key_" + $action.Name] = $null } else { $changes["key_" + $action.Name] = $now }
        }
        Invoke-Safe { Write-IniValues $changes; Set-Status "Controls saved (dotd.ini)" }
        $dialog.DialogResult = "OK"
    })
    $cancelButton = New-Object System.Windows.Forms.Button
    $cancelButton.Text = "Cancel"
    $cancelButton.Location = New-Object System.Drawing.Point((S 1009), (S 470))
    $cancelButton.Size = New-Object System.Drawing.Size((S 105), (S 30))
    $cancelButton.DialogResult = "Cancel"
    $dialog.Controls.AddRange(@($defaultsButton, $saveButton, $cancelButton))
    $dialog.AcceptButton = $saveButton

    if ($screenshotPath -ne "") {
        $dialog.add_Shown({
            $dialog.Refresh()
            $bitmap = New-Object System.Drawing.Bitmap($dialog.Width, $dialog.Height)
            $dialog.DrawToBitmap($bitmap, (New-Object System.Drawing.Rectangle(0, 0, $dialog.Width, $dialog.Height)))
            $bitmap.Save($screenshotPath, [System.Drawing.Imaging.ImageFormat]::Png)
            $dialog.Close()
        })
    }
    [void]$dialog.ShowDialog($form)
    $countdown.Stop()
}

# ---- wiring ----------------------------------------------------------------------------------------------------------
$startButton.add_Click({ Invoke-Safe { On-Start } })
$buildButton.add_Click({ Invoke-Safe { Start-Build $true $null } })
$gameButton.add_Click({ Invoke-Safe { Choose-Game } })
$gameLabel.add_Click({ if ($gameButton.Enabled) { Invoke-Safe { Choose-Game } } })
$controlsButton.add_Click({ Invoke-Safe { Show-Controls } })
$form.add_FormClosing({
    param($sender, $e)
    if ($null -ne $script:Job -and $script:Job.Name -ne "game") {
        if (-not (Ask-YesNo "$($script:Job.Title) is still running. Stop it and close?")) { $e.Cancel = $true; return }
        Stop-CurrentJob
    }
})

Load-Settings
Update-GameLabel
Update-Buttons
if (Test-Path -LiteralPath $Exe) {
    Set-Status "Ready"
} else {
    Set-Status "dotd.exe is not built yet: Start (or Build) builds it"
}
Add-Log "Source: $Root"
Add-Log "Settings: $Ini"

if ($Screenshot -ne "") {
    $form.add_Shown({
        $form.Refresh()
        if ($Dialog -eq "controls") {
            Show-Controls $Screenshot
        } else {
            $bitmap = New-Object System.Drawing.Bitmap($form.Width, $form.Height)
            $form.DrawToBitmap($bitmap, (New-Object System.Drawing.Rectangle(0, 0, $form.Width, $form.Height)))
            $bitmap.Save($Screenshot, [System.Drawing.Imaging.ImageFormat]::Png)
        }
        $form.Close()
    })
}
[System.Windows.Forms.Application]::Run($form)
