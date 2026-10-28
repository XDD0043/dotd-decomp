/* config.h - handwritten FFmpeg configuration for the dotd Bink-only build (FFmpeg n7.1.2, MSVC and
 * clang/gcc, x86/x64/arm64, C only: no assembly, no threads, no external libraries).
 * Written by hand instead of running FFmpeg's configure; every macro the compiled sources and their
 * headers test is listed (collected with a scan of the sources, 2026-10-18). Not part of FFmpeg. */
#ifndef DOTD_FFMPEG_CONFIG_H
#define DOTD_FFMPEG_CONFIG_H

#define FFMPEG_CONFIGURATION "dotd bink-only (handwritten config.h)"
#define FFMPEG_LICENSE "LGPL version 2.1 or later"
#define CONFIG_THIS_YEAR 2025
#define FFMPEG_DATADIR "."
#define AVCONV_DATADIR "."
#define CC_IDENT "dotd"
#define OS_NAME "dotd"
#define EXTERN_PREFIX ""
#define EXTERN_ASM
#define BUILDSUF ""
#define SLIBSUF ""
#define SWS_MAX_FILTER_SIZE 256

#if defined(_MSC_VER) && !defined(__clang__)
#define av_restrict __restrict
#else
#define av_restrict restrict
#endif

/* ---- architecture: generic C everywhere ---- */
#define ARCH_AARCH64 0
#define ARCH_ARM 0
#define ARCH_LOONGARCH 0
#define ARCH_LOONGARCH64 0
#define ARCH_MIPS 0
#define ARCH_MIPS64 0
#define ARCH_PPC 0
#define ARCH_PPC64 0
#define ARCH_RISCV 0
#define ARCH_X86 0
#define ARCH_X86_32 0
#define ARCH_X86_64 0

#define HAVE_X86ASM 0
#define HAVE_INLINE_ASM 0
#define HAVE_INLINE_ASM_DIRECT_SYMBOL_REFS 0
#define HAVE_XFORM_ASM 0
#define HAVE_XMM_CLOBBERS 0
#define HAVE_MMX 0
#define HAVE_MMX_EXTERNAL 0
#define HAVE_MMX_INLINE 0
#define HAVE_MM_EMPTY 0
#define HAVE_I686 0
#define HAVE_6REGS 0
#define HAVE_7REGS 0
#define HAVE_EBP_AVAILABLE 0
#define HAVE_EBX_AVAILABLE 0
#define HAVE_RDTSC 0
#define HAVE_INTRINSICS_SSE2 0
#define HAVE_INTRINSICS_NEON 0
#define HAVE_ARMV5TE_INLINE 0
#define HAVE_ARMV6 0
#define HAVE_ARMV6_INLINE 0
#define HAVE_ASM_MOD_Q 0
#define HAVE_LDBRX 0
#define HAVE_PPC4XX 0
#define HAVE_LOONGSON3 0
#define HAVE_MIPS64R6 0
#define HAVE_MIPSFPU 0
#define HAVE_RV 0
#define HAVE_RVV 0
#define HAVE_SIMD_ALIGN_16 0
#define HAVE_SIMD_ALIGN_32 0
#define HAVE_SIMD_ALIGN_64 0
#define HAVE_LOCAL_ALIGNED 1

#define HAVE_BIGENDIAN 0
#define HAVE_FAST_UNALIGNED 1
#define HAVE_FAST_CLZ 0
#if defined(_M_X64) || defined(_M_ARM64) || defined(__x86_64__) || defined(__aarch64__)
#define HAVE_FAST_64BIT 1
#else
#define HAVE_FAST_64BIT 0
#endif

/* ---- C library and OS ---- */
#if defined(_WIN32)
#define HAVE_WINDOWS_H 1
#define HAVE_IO_H 1
#define HAVE_UNISTD_H 0
#define HAVE_MALLOC_H 1
#define HAVE_ALIGNED_MALLOC 1
#define HAVE_POSIX_MEMALIGN 0
#define HAVE_DOS_PATHS 1
#define HAVE_GETSYSTEMTIMEASFILETIME 1
#define HAVE_GETTIMEOFDAY 0
#define HAVE_CLOCK_GETTIME 0
#define HAVE_SLEEP 1
#define HAVE_USLEEP 0
#define HAVE_NANOSLEEP 0
#define HAVE_GETSTDHANDLE 1
#define HAVE_SETCONSOLETEXTATTRIBUTE 1
#define HAVE_GETPROCESSAFFINITYMASK 1
#define HAVE_SYSCONF 0
#define HAVE_GMTIME_R 0
#define HAVE_LOCALTIME_R 0
#else
#define HAVE_WINDOWS_H 0
#define HAVE_IO_H 0
#define HAVE_UNISTD_H 1
#define HAVE_MALLOC_H 0
#define HAVE_ALIGNED_MALLOC 0
#define HAVE_POSIX_MEMALIGN 1
#define HAVE_DOS_PATHS 0
#define HAVE_GETSYSTEMTIMEASFILETIME 0
#define HAVE_GETTIMEOFDAY 1
#define HAVE_CLOCK_GETTIME 1
#define HAVE_SLEEP 0
#define HAVE_USLEEP 1
#define HAVE_NANOSLEEP 1
#define HAVE_GETSTDHANDLE 0
#define HAVE_SETCONSOLETEXTATTRIBUTE 0
#define HAVE_GETPROCESSAFFINITYMASK 0
#define HAVE_SYSCONF 1
#define HAVE_GMTIME_R 1
#define HAVE_LOCALTIME_R 1
#endif
#define HAVE_MEMALIGN 0
#define HAVE_ISATTY 0
#define HAVE_LIBC_MSVCRT 0
#define HAVE_WINRT 0
#define HAVE_BCRYPT 0
#define HAVE_ARC4RANDOM_BUF 0
#define HAVE_GETAUXVAL 0
#define HAVE_ELF_AUX_INFO 0
#define HAVE_GETHRTIME 0
#define HAVE_MACH_ABSOLUTE_TIME 0
#define HAVE_PRCTL 0
#define HAVE_SCHED_GETAFFINITY 0
#define HAVE_SYSCTL 0
#define HAVE_SYS_PARAM_H 0
#define HAVE_STRERROR_R 0
#define HAVE_VALGRIND_VALGRIND_H 0
#define HAVE_PRAGMA_DEPRECATED 0

/* No threads: libavutil/thread.h then provides the single-threaded fallbacks (ff_thread_once etc.). */
#define HAVE_THREADS 0
#define HAVE_PTHREADS 0
#define HAVE_W32THREADS 0
#define HAVE_OS2THREADS 0
#define HAVE_PTHREAD_NP_H 0
#define HAVE_PTHREAD_SETNAME_NP 0
#define HAVE_PTHREAD_SET_NAME_NP 0

/* C99 math: present in every supported C library. */
#define HAVE_ATAN2F 1
#define HAVE_ATANF 1
#define HAVE_CBRT 1
#define HAVE_CBRTF 1
#define HAVE_COPYSIGN 1
#define HAVE_COSF 1
#define HAVE_ERF 1
#define HAVE_EXP2 1
#define HAVE_EXP2F 1
#define HAVE_EXPF 1
#define HAVE_HYPOT 1
#define HAVE_ISFINITE 1
#define HAVE_ISINF 1
#define HAVE_ISNAN 1
#define HAVE_LDEXPF 1
#define HAVE_LLRINT 1
#define HAVE_LLRINTF 1
#define HAVE_LOG10F 1
#define HAVE_LOG2 1
#define HAVE_LOG2F 1
#define HAVE_LRINT 1
#define HAVE_LRINTF 1
#define HAVE_POWF 1
#define HAVE_RINT 1
#define HAVE_ROUND 1
#define HAVE_ROUNDF 1
#define HAVE_SINF 1
#define HAVE_TRUNC 1
#define HAVE_TRUNCF 1

/* ---- build options ---- */
#define CONFIG_SHARED 0
#define CONFIG_SMALL 0
#define CONFIG_GRAY 0
#define CONFIG_HARDCODED_TABLES 0
#define CONFIG_MEMORY_POISONING 0
#define CONFIG_SAFE_BITSTREAM_READER 1
#define CONFIG_RUNTIME_CPUDETECT 0
#define CONFIG_FRAME_THREAD_ENCODER 0
#define CONFIG_OSSFUZZ 0
#define CONFIG_LINUX_PERF 0
#define CONFIG_MACOS_KPERF 0
#define CONFIG_VALGRIND_BACKTRACE 0

/* ---- external libraries and hardware acceleration: none ---- */
#define CONFIG_CUDA 0
#define CONFIG_D3D11VA 0
#define CONFIG_D3D12VA 0
#define CONFIG_DXVA2 0
#define CONFIG_GCRYPT 0
#define CONFIG_ICONV 0
#define CONFIG_LCMS2 0
#define CONFIG_LIBDRM 0
#define CONFIG_LIBLCEVC_DEC 0
#define CONFIG_MEDIACODEC 0
#define CONFIG_OPENCL 0
#define CONFIG_OPENSSL 0
#define CONFIG_QSV 0
#define CONFIG_VAAPI 0
#define CONFIG_VDPAU 0
#define CONFIG_VIDEOTOOLBOX 0
#define CONFIG_VULKAN 0

#endif /* DOTD_FFMPEG_CONFIG_H */
