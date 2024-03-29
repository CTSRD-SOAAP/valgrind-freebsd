
/*--------------------------------------------------------------------*/
/*--- FreeBSD-specific kernel interface.             vki-freebsd.h ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2005 Julian Seward 
      jseward@acm.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

/* This file defines types and constants for the kernel interface, and to
   make that clear everything is prefixed VKI_/vki_.

   All code is copied verbatim from kernel source files, except that:
   - VKI_/vki_ prefixes are added
   - some extra explanatory comments are included;  they are all within
     "[[ ]]"
   - for some types, we only care about the size;  for a few of them (big
     ones that are painful to fully drag in here), a VKI_SIZEOF_* constant
     is used.
   
   The files the code is taken from is indicated.

   Note especially that the types are not the glibc versions, many of which
   are different to those in here. 

   Also note that this file contains all the generic header info, ie. that
   from linux/include/linux/ *.h.  The arch-specific header info, eg. that
   from linux/include/asm-i386/ *.h, is in vki-$PLATFORM.h and
   vki_posixtypes-$PLATFORM.h.  (Two files are required to avoid
   circular dependencies between the generic VKI header and the
   arch-specific VKI header.  It's possible in the future, as more stuff
   gets pulled in, that we might have to split files up some more to avoid
   further circular dependencies.)
   
   Finally, note that it is assumed that __KERNEL__ is set for all these
   definitions, which affects some of them.
*/

#ifndef __VKI_FREEBSD_H
#define __VKI_FREEBSD_H

//----------------------------------------------------------------------
// Arch-specific POSIX types
//----------------------------------------------------------------------

#if defined(VGA_x86)
#  include "vki-machine-types-x86-freebsd.h"
#elif defined(VGA_amd64)
#  include "vki-machine-types-amd64-freebsd.h"
#else
#  error Unknown platform
#endif


//----------------------------------------------------------------------
// From sys/select.h
//----------------------------------------------------------------------

typedef unsigned long __vki_fd_mask;

#undef __VKI_NFDBITS
#define __VKI_NFDBITS	(8 * sizeof(__vki_fd_mask))

#undef __VKI_FD_SETSIZE
#define __VKI_FD_SETSIZE	1024U

#undef __VKI_FDSET_LONGS
#define __VKI_FDSET_LONGS	(__VKI_FD_SETSIZE/__VKI_NFDBITS)

#undef __VKI_FDELT
#define	__VKI_FDELT(d)	((d) / __VKI_NFDBITS)

#undef __VKI_FDMASK
#define	__VKI_FDMASK(d)	(1UL << ((d) % __VKI_NFDBITS))

typedef struct {
	unsigned long fds_bits [__VKI_FDSET_LONGS];
} __vki_fd_set;

//----------------------------------------------------------------------
// sys/_types.h
//----------------------------------------------------------------------
/* MD QQQ 32 on 64 */
typedef	long		__vki_key_t;
typedef	long		__vki_suseconds_t;
typedef	struct __timer	*__vki_timer_t;
typedef	struct __mq	*__vki_mqd_t;

/* MI */
typedef	vki_uint32_t	__vki_blksize_t;
typedef	vki_int64_t	__vki_blkcnt_t;
typedef	vki_int32_t	__vki_clockid_t;
typedef	vki_int32_t	__vki_ct_rune_t;
typedef	vki_uint32_t	__vki_fflags_t;
typedef	vki_uint64_t	__vki_fsblkcnt_t;
typedef	vki_uint64_t	__vki_fsfilcnt_t;
typedef	vki_uint32_t	__vki_gid_t;
typedef	vki_int64_t	__vki_id_t;	
typedef	vki_uint32_t	__vki_ino_t;
typedef	vki_int32_t	__vki_lwpid_t;
typedef	vki_uint16_t	__vki_mode_t;
typedef	vki_uint16_t	__vki_nlink_t;
typedef	vki_int64_t	__vki_off_t;
typedef	vki_int32_t	__vki_pid_t;
typedef	vki_int64_t	__vki_rlim_t;
typedef	vki_uint8_t	__vki_sa_family_t;
typedef	vki_uint32_t	__vki_socklen_t;
typedef	vki_uint32_t	__vki_uid_t;
typedef	vki_int32_t	__vki_useconds_t;
typedef	__vki_ct_rune_t	__vki_rune_t;
typedef	__vki_ct_rune_t	__vki_wchar_t;
typedef	__vki_ct_rune_t	__vki_wint_t;
typedef	vki_uint32_t	__vki_dev_t;
typedef	vki_uint32_t	__vki_fixpt_t;


//----------------------------------------------------------------------
// sys/types.h
//----------------------------------------------------------------------

typedef	vki_uint8_t		vki_u_int8_t;
typedef	vki_uint16_t		vki_u_int16_t;
typedef	vki_uint32_t		vki_u_int32_t;
typedef	vki_uint64_t		vki_u_int64_t;

typedef	vki_uint64_t		vki_u_quad_t;
typedef	vki_int64_t		vki_quad_t;
typedef	__vki_caddr_t		vki_caddr_t;
typedef __const __vki_caddr_t	vki_c_caddr_t;
typedef __volatile __vki_caddr_t vki_v_caddr_t;

typedef __vki_blksize_t		vki_blksize_t;
typedef __vki_blkcnt_t		vki_blkcnt_t;
typedef __vki_clock_t		vki_clock_t;
typedef __vki_clockid_t		vki_clockid_t;
typedef __vki_dev_t		vki_dev_t;
typedef __vki_fflags_t		vki_fflags_t;
typedef __vki_fixpt_t		vki_fixpt_t;
typedef __vki_fsblkcnt_t	vki_fsblkcnt_t;
typedef __vki_fsfilcnt_t	vki_fsfilcnt_t;
typedef __vki_gid_t		vki_gid_t;
typedef vki_uint32_t		vki_in_addr_t;
typedef vki_uint16_t		vki_in_port_t;
typedef __vki_id_t		vki_id_t;
typedef __vki_ino_t		vki_ino_t;
typedef __vki_key_t		vki_key_t;
typedef __vki_lwpid_t		vki_lwpid_t;
typedef __vki_mode_t		vki_mode_t;
typedef __vki_nlink_t		vki_nlink_t;
typedef __vki_off_t		vki_off_t;
typedef __vki_pid_t		vki_pid_t;
typedef __vki_register_t	vki_register_t;
typedef __vki_rlim_t		vki_rlim_t;
typedef __vki_segsz_t		vki_segsz_t;
typedef __vki_size_t		vki_size_t;
typedef __vki_ssize_t		vki_ssize_t;
typedef __vki_suseconds_t	vki_suseconds_t;
typedef __vki_time_t		vki_time_t;
typedef __vki_timer_t		vki_timer_t;
typedef __vki_mqd_t		vki_mqd_t;
typedef __vki_u_register_t	vki_u_register_t;
typedef __vki_uid_t		vki_uid_t;
typedef __vki_useconds_t	vki_useconds_t;

typedef __vki_vm_offset_t	vki_vm_offset_t;
typedef __vki_vm_ooffset_t	vki_vm_ooffset_t;
typedef __vki_vm_paddr_t	vki_vm_paddr_t;
typedef __vki_vm_pindex_t	vki_vm_pindex_t;
typedef __vki_vm_size_t		vki_vm_size_t;

//----------------------------------------------------------------------
// sys/select.h
//----------------------------------------------------------------------

typedef __vki_fd_set		vki_fd_set;

//----------------------------------------------------------------------
// Now the rest of the arch-specific stuff
//----------------------------------------------------------------------

#if defined(VGA_x86)
#  include "vki-x86-freebsd.h"
#elif defined(VGA_amd64)
#  include "vki-amd64-freebsd.h"
#elif defined(VGA_ppc32)
#  include "vki-ppc32-freebsd.h"
#elif defined(VGA_ppc64)
#  include "vki-ppc64-freebsd.h"
#else
#  error Unknown platform
#endif

//----------------------------------------------------------------------
// linux and freebsd version hacks
//----------------------------------------------------------------------
#ifndef ELFMAG
#define ELFMAG	"\177ELF"	/* magic string */
#endif
#ifndef SELFMAG
#define SELFMAG	4		/* magic string size */
#endif

//----------------------------------------------------------------------
// From sys/syslimits.h
//----------------------------------------------------------------------

#define VKI_PATH_MAX       1024


//----------------------------------------------------------------------
// From sys/timespec.h
//----------------------------------------------------------------------

struct vki_timespec {
	vki_time_t	tv_sec;		/* seconds */
	long		tv_nsec;	/* nanoseconds */
};

struct  vki_itimerspec {
        struct  vki_timespec it_interval;    /* timer period */
        struct  vki_timespec it_value;       /* timer expiration */
};

//----------------------------------------------------------------------
// From sys/_time.h
//----------------------------------------------------------------------

struct vki_timeval {
	vki_time_t	tv_sec;		/* seconds */
	vki_suseconds_t	tv_usec;	/* microseconds */
};

//----------------------------------------------------------------------
// From sys/time.h
//----------------------------------------------------------------------

#define VKI_CLOCK_REALTIME            0
#define VKI_CLOCK_MONOTONIC           1
#define VKI_CLOCK_PROCESS_CPUTIME_ID  2
#define VKI_CLOCK_THREAD_CPUTIME_ID   3

struct vki_timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};

struct	vki_itimerval {
	struct	vki_timeval it_interval;	/* timer interval */
	struct	vki_timeval it_value;	/* current value */
};

//----------------------------------------------------------------------
// From sys/timex.h
//----------------------------------------------------------------------

struct vki_ntptimeval {
	struct vki_timespec time;
	long maxerror;
	long esterror;
	long tai;
	int time_state;
};

struct vki_timex {
	unsigned int modes;	/* mode selector */
	long offset;		/* time offset (usec) */
	long freq;		/* frequency offset (scaled ppm) */
	long maxerror;		/* maximum error (usec) */
	long esterror;		/* estimated error (usec) */
	int status;		/* clock command/status */
	long constant;		/* pll time constant */
	long precision;		/* clock precision (usec) (read only) */
	long tolerance;		/* clock frequency tolerance (ppm)
				 * (read only)
				 */
	long ppsfreq;           /* pps frequency (scaled ppm) (ro) */
	long jitter;            /* pps jitter (us) (ro) */
	int shift;              /* interval duration (s) (shift) (ro) */
	long stabil;            /* pps stability (scaled ppm) (ro) */
	long jitcnt;            /* jitter limit exceeded (ro) */
	long calcnt;            /* calibration intervals (ro) */
	long errcnt;            /* calibration errors (ro) */
	long stbcnt;            /* stability limit exceeded (ro) */
};

#define MOD_OFFSET		0x0001	/* time offset */
#define MOD_FREQUENCY		0x0002	/* frequency offset */
#define MOD_MAXERROR		0x0004	/* maximum time error */
#define MOD_ESTERROR		0x0008	/* estimated time error */
#define MOD_STATUS		0x0010	/* clock status */
#define MOD_TIMECONST		0x0020	/* pll time constant */
#define MOD_PPSMAX		0x0040
#define MOD_TAI			0x0080
#define MOD_MICRO		0x1000
#define MOD_NANO		0x2000
#define MOD_CLKB		0x4000
#define MOD_CLKA		0x8000

//----------------------------------------------------------------------
// From sys/times.h
//----------------------------------------------------------------------

struct vki_tms {
	vki_clock_t tms_utime;
	vki_clock_t tms_stime;
	vki_clock_t tms_cutime;
	vki_clock_t tms_cstime;
};

//----------------------------------------------------------------------
// From sys/stat.h
//----------------------------------------------------------------------

/* QQQ 4.x stat layout */
struct vki_stat {
	vki_dev_t	st_dev;
	vki_ino_t	st_ino;
	vki_mode_t	st_mode;
	vki_nlink_t	st_nlink;
	vki_uid_t	st_uid;
	vki_gid_t	st_gid;
	vki_dev_t	st_rdev;
#if 0
	struct vki_timespec	st_atimespec;
	struct vki_timespec	st_mtimespec;
	struct vki_timespec	st_ctimespec;
#else
	vki_time_t	st_atime;
	long		st_atime_nsec;
	vki_time_t	st_mtime;
	long		st_mtime_nsec;
	vki_time_t	st_ctime;
	long		st_ctime_nsec;
#endif
	vki_off_t	st_size;
	vki_blkcnt_t	st_blocks;
	vki_blksize_t	st_blksize;
	vki_fflags_t	st_flags;
	vki_uint32_t	st_gen;
	vki_int32_t	st_lspare;
	struct vki_timespec	st_birthtimespec;
	unsigned int :(8 / 2) * (16 - (int)sizeof(struct vki_timespec));
	unsigned int :(8 / 2) * (16 - (int)sizeof(struct vki_timespec));
};


//----------------------------------------------------------------------
// From linux-2.6.8.1/include/linux/sched.h
//----------------------------------------------------------------------

struct vki_sched_param {
	int sched_priority;
};

//----------------------------------------------------------------------
// From sys/signal.h
//----------------------------------------------------------------------

#define	VKI_SIG_BLOCK	1	/*  block specified signal set */
#define	VKI_SIG_UNBLOCK	2	/*  unblock specified signal set */
#define	VKI_SIG_SETMASK	3	/*  set specified signal set */

#define	VKI_SIG_DFL	((__vki_sighandler_t)0)
#define	VKI_SIG_IGN	((__vki_sighandler_t)1)
#define	VKI_SIG_ERR	((__vki_sighandler_t)-1)

typedef void __vki_signalfn_t(int);
typedef __vki_signalfn_t *__vki_sighandler_t;

#define	VKI_SIGHUP		1
#define	VKI_SIGINT		2
#define	VKI_SIGQUIT		3
#define	VKI_SIGILL		4
#define	VKI_SIGTRAP		5
#define	VKI_SIGABRT		6
#define	VKI_SIGEMT		7
#define	VKI_SIGFPE		8
#define	VKI_SIGKILL		9
#define	VKI_SIGBUS		10
#define	VKI_SIGSEGV		11
#define	VKI_SIGSYS		12
#define	VKI_SIGPIPE		13
#define	VKI_SIGALRM		14
#define	VKI_SIGTERM		15
#define	VKI_SIGURG		16
#define	VKI_SIGSTOP		17
#define	VKI_SIGTSTP		18
#define	VKI_SIGCONT		19
#define	VKI_SIGCHLD		20
#define	VKI_SIGTTIN		21
#define	VKI_SIGTTOU		22
#define	VKI_SIGIO		23
#define	VKI_SIGXCPU		24
#define	VKI_SIGXFSZ		25
#define	VKI_SIGVTALRM		26
#define	VKI_SIGPROF		27
#define	VKI_SIGWINCH		28
#define	VKI_SIGINFO		29
#define	VKI_SIGUSR1		30
#define	VKI_SIGUSR2		31
#define	VKI_SIGTHR		32

#define	VKI_SIGRTMIN		65
#define	VKI_SIGRTMAX		126

#define	VKI_SA_ONSTACK		0x0001
#define	VKI_SA_RESTART		0x0002
#define	VKI_SA_RESETHAND	0x0004
#define	VKI_SA_NOCLDSTOP	0x0008
#define	VKI_SA_NODEFER		0x0010
#define	VKI_SA_NOCLDWAIT	0x0020
#define	VKI_SA_SIGINFO		0x0040

#define	VKI_SS_ONSTACK		0x0001
#define	VKI_SS_DISABLE		0x0004

#define	VKI_SA_ONESHOT		VKI_SA_RESETHAND
#define	VKI_SA_NOMASK		VKI_SA_NODEFER

struct vki_sigaction {
	__vki_sighandler_t ksa_handler;
	int		sa_flags;
	vki_sigset_t	sa_mask;
};

typedef struct vki_sigaltstack {
	void		*ss_sp;
	vki_size_t	ss_size;
	int		ss_flags;
} vki_stack_t;

typedef union vki_sigval {
	int sival_int;
	void *sival_ptr;
} vki_sigval_t;

#if 0 	/* freebsd6 */
typedef struct vki_siginfo {
	int si_signo;
	int si_errno;
	int si_code;
	vki_pid_t si_pid;
	vki_uid_t si_uid;
	int si_status;
	void *si_addr;
	vki_sigval_t si_value;

	union {

		/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
		struct {
			int _trapno;	/* TRAP # which caused the signal */
		} _sigfault;

		/* POSIX.1b timers */
		struct {
			int _timerid;		/* timer id */
			int _overrun;		/* overrun count */
		} _timer;

		struct {
			int _mqd;
		} _mesgq;

		/* SIGPOLL */
		struct {
			long _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
		} _sigpoll;

		struct {
			long __spare1__;
			int __spare2[7];
		} __spare__;
	} _sifields;
} vki_siginfo_t;
#endif
typedef struct vki_siginfo {
	int si_signo;
	int si_errno;
	int si_code;
	vki_pid_t si_pid;
	vki_uid_t si_uid;
	int si_status;
	void *si_addr;
	vki_sigval_t si_value;
// 666: not valid. switch to above def
#ifdef si_band
#undef si_band
#endif
	long si_band;
	int __spare__[7];
} vki_siginfo_t;

/*
 * si_code values
 */
#define VKI_SI_USER	0x10001		/* sent by kill, sigsend, raise */
#define VKI_SI_QUEUE	0x10002
#define VKI_SI_TIMER	0x10003
#define VKI_SI_ASYNCIO	0x10004
#define VKI_SI_MESGQ	0x10005

/*
 * SIGILL si_codes
 */
#define VKI_ILL_ILLOPC	1	/* illegal opcode */
#define VKI_ILL_ILLOPN	2	/* illegal operand */
#define VKI_ILL_ILLADR	3	/* illegal addressing mode */
#define VKI_ILL_ILLTRP	4	/* illegal trap */
#define VKI_ILL_PRVOPC	5	/* privileged opcode */
#define VKI_ILL_PRVREG	6	/* privileged register */
#define VKI_ILL_COPROC	7	/* coprocessor error */
#define VKI_ILL_BADSTK	8	/* internal stack error */

/*
 * SIGFPE si_codes
 */
#define VKI_FPE_INTOVF	1	/* integer overflow */
#define VKI_FPE_INTDIV	2	/* integer divide by zero */
#define VKI_FPE_FLTDIV	3	/* floating point divide by zero */
#define VKI_FPE_FLTOVF	4	/* floating point overflow */
#define VKI_FPE_FLTUND	5	/* floating point underflow */
#define VKI_FPE_FLTRES	6	/* floating point inexact result */
#define VKI_FPE_FLTINV	7	/* floating point invalid operation */
#define VKI_FPE_FLTSUB	8	/* subscript out of range */

/*
 * SIGSEGV si_codes
 */
#define VKI_SEGV_MAPERR	1	/* address not mapped to object */
#define VKI_SEGV_ACCERR	2	/* invalid permissions for mapped object */
/* XXX i386 and amd64 specific */
#define	VKI_SEGV_PAGE_FAULT	12

/*
 * SIGBUS si_codes
 */
#define VKI_BUS_ADRALN	1	/* invalid address alignment */
#define VKI_BUS_ADRERR	2	/* non-existant physical address */
#define VKI_BUS_OBJERR	3	/* object specific hardware error */

/*
 * SIGTRAP si_codes
 */
#define VKI_TRAP_BRKPT	1	/* process breakpoint */
#define VKI_TRAP_TRACE	2	/* process trace trap */


#if 0	/* freebsd-6 */
typedef struct vki_sigevent {
	int sigev_notify;
	int sigev_signo;
	vki_sigval_t sigev_value;
	union {
		int _threadid;

		struct {
			void (*_function)(vki_sigval_t);
			void *_attribute;	/* really pthread_attr_t */
		} _sigev_thread;
		long __spare__[8];
	} _sigev_un;
} vki_sigevent_t;
#endif

struct vki_sigevent {
	int     sigev_notify;           /* Notification type */
	union {
		int	__sigev_signo;  /* Signal number */
		int	__sigev_notify_kqueue;
	} __sigev_u;
	vki_sigval_t sigev_value;       /* Signal value */
};
#if 0
#define sigev_signo             __sigev_u.__sigev_signo
#define sigev_notify_kqueue     __sigev_u.__sigev_notify_kqueue
#endif

//----------------------------------------------------------------------
// From sys/_iovec.h
//----------------------------------------------------------------------

struct vki_iovec
{
	void *iov_base;
	__vki_size_t iov_len;
};

//----------------------------------------------------------------------
// From sys/socket.h
//----------------------------------------------------------------------

typedef __vki_sa_family_t	vki_sa_family_t;
typedef __vki_socklen_t		vki_socklen_t;

struct vki_sockaddr {
	vki_uint8_t	sa_len;
	vki_sa_family_t	sa_family;	/* address family, AF_xxx	*/
	char		sa_data[14];	/* 14 bytes of protocol address	*/
};

struct vki_msghdr {
	void	*	msg_name;	/* Socket name			*/
	vki_socklen_t	msg_namelen;	/* Length of name		*/
	struct vki_iovec *	msg_iov;	/* Data blocks			*/
	int		msg_iovlen;	/* Number of blocks		*/
	void 	*	msg_control;	/* Per protocol magic (eg BSD file descriptor passing) */
	vki_socklen_t	msg_controllen;	/* Length of cmsg list */
	int		msg_flags;
};

struct vki_cmsghdr {
	vki_socklen_t	cmsg_len;	/* data byte count, including hdr */
        int		cmsg_level;	/* originating protocol */
        int		cmsg_type;	/* protocol-specific type */
};

#define __VKI_CMSG_NXTHDR(ctl, len, cmsg) __vki_cmsg_nxthdr((ctl),(len),(cmsg))
#define VKI_CMSG_NXTHDR(mhdr, cmsg) vki_cmsg_nxthdr((mhdr), (cmsg))

#define VKI_CMSG_ALIGN(len) ( ((len)+sizeof(long)-1) & ~(sizeof(long)-1) )

#define VKI_CMSG_DATA(cmsg)	((void *)((char *)(cmsg) + VKI_CMSG_ALIGN(sizeof(struct vki_cmsghdr))))

#define __VKI_CMSG_FIRSTHDR(ctl,len) ((len) >= sizeof(struct vki_cmsghdr) ? \
				  (struct vki_cmsghdr *)(ctl) : \
				  (struct vki_cmsghdr *)NULL)
#define VKI_CMSG_FIRSTHDR(msg)	__VKI_CMSG_FIRSTHDR((msg)->msg_control, (msg)->msg_controllen)

// [[Urgh, this is revolting...]
// QQQ check
static __inline struct vki_cmsghdr * __vki_cmsg_nxthdr(void *__ctl, vki_socklen_t __size,
					       struct vki_cmsghdr *__cmsg)
{
	struct vki_cmsghdr * __ptr;

	__ptr = (struct vki_cmsghdr*)(((unsigned char *) __cmsg) +  VKI_CMSG_ALIGN(__cmsg->cmsg_len));
	if ((unsigned long)((char*)(__ptr+1) - (char *) __ctl) > __size)
		return (struct vki_cmsghdr *)0;

	return __ptr;
}

static __inline struct vki_cmsghdr * vki_cmsg_nxthdr (struct vki_msghdr *__msg, struct vki_cmsghdr *__cmsg)
{
	return __vki_cmsg_nxthdr(__msg->msg_control, __msg->msg_controllen, __cmsg);
}

#define	VKI_SCM_RIGHTS	0x01		/* rw: access rights (array of int) */

#define VKI_AF_UNIX	1	/* Unix domain sockets 		*/
#define VKI_AF_INET	2	/* Internet IP Protocol		*/
#define VKI_AF_INET6	28	/* IP version 6			*/

#define VKI_MSG_NOSIGNAL	0x20000	/* Do not generate SIGPIPE */

#define VKI_SOL_SOCKET	0xffff

#define VKI_SO_TYPE	0x1008

#define VKI_SOCK_STREAM	1
//----------------------------------------------------------------------
// From netinet/in.h
//----------------------------------------------------------------------

struct vki_in_addr {
	vki_in_addr_t	s_addr;
};

/* Structure describing an Internet (IP) socket address. */
#define __VKI_SOCK_SIZE__	16	/* sizeof(struct sockaddr)	*/
struct vki_sockaddr_in {
  vki_uint8_t		sin_len;
  vki_sa_family_t	sin_family;	/* Address family		*/
  vki_in_port_t		sin_port;	/* Port number			*/
  struct vki_in_addr	sin_addr;	/* Internet address		*/
  char			sin_zero[8];
};

//----------------------------------------------------------------------
// From netinet6/in6.h
//----------------------------------------------------------------------

struct vki_in6_addr
{
	union 
	{
		vki_uint8_t	u6_addr8[16];
		vki_uint16_t	u6_addr16[8];
		vki_uint32_t	u6_addr32[4];
	} vki_in6_u;
#define vki_s6_addr		vki_in6_u.u6_addr8
#define vki_s6_addr16		vki_in6_u.u6_addr16
#define vki_s6_addr32		vki_in6_u.u6_addr32
};

struct vki_sockaddr_in6 {
	vki_uint8_t		sin6_len;
	vki_sa_family_t		sin6_family;    /* AF_INET6 */
	vki_uint16_t		sin6_port;      /* Transport layer port # */
	vki_uint32_t		sin6_flowinfo;  /* IPv6 flow information */
	struct vki_in6_addr	sin6_addr;      /* IPv6 address */
	vki_uint32_t		sin6_scope_id;  /* scope id (new in RFC2553) */
};

//----------------------------------------------------------------------
// From sys/un.h
//----------------------------------------------------------------------

#define VKI_UNIX_PATH_MAX	104	/* QQQ overridden by sun_len */

struct vki_sockaddr_un {
	unsigned char sun_len;
	vki_sa_family_t sun_family;	/* AF_UNIX */
	char sun_path[VKI_UNIX_PATH_MAX];	/* pathname */
};

#if 0
//----------------------------------------------------------------------
// From linux-2.6.8.1/include/linux/if.h
//----------------------------------------------------------------------

#define	VKI_IFNAMSIZ	16

struct vki_ifmap 
{
	unsigned long mem_start;
	unsigned long mem_end;
	unsigned short base_addr; 
	unsigned char irq;
	unsigned char dma;
	unsigned char port;
	/* 3 bytes spare */
};

struct vki_if_settings
{
	unsigned int type;	/* Type of physical device or protocol */
	unsigned int size;	/* Size of the data allocated by the caller */
	union {
                // [[Nb: converted these all to void* to avoid pulling in
                //   unnecessary headers]]]
		/* {atm/eth/dsl}_settings anyone ? */
		void /*raw_hdlc_proto		*/__user *raw_hdlc;
		void /*cisco_proto		*/__user *cisco;
		void /*fr_proto			*/__user *fr;
		void /*fr_proto_pvc		*/__user *fr_pvc;
		void /*fr_proto_pvc_info	*/__user *fr_pvc_info;

		/* interface settings */
		void /*sync_serial_settings	*/__user *sync;
		void /*te1_settings		*/__user *te1;
	} ifs_ifsu;
};

struct vki_ifreq 
{
#define VKI_IFHWADDRLEN	6
	union
	{
		char	ifrn_name[VKI_IFNAMSIZ];		/* if name, e.g. "en0" */
	} ifr_ifrn;
	
	union {
		struct	vki_sockaddr ifru_addr;
		struct	vki_sockaddr ifru_dstaddr;
		struct	vki_sockaddr ifru_broadaddr;
		struct	vki_sockaddr ifru_netmask;
		struct  vki_sockaddr ifru_hwaddr;
		short	ifru_flags;
		int	ifru_ivalue;
		int	ifru_mtu;
		struct  vki_ifmap ifru_map;
		char	ifru_slave[VKI_IFNAMSIZ];	/* Just fits the size */
		char	ifru_newname[VKI_IFNAMSIZ];
		void __user *	ifru_data;
		struct	vki_if_settings ifru_settings;
	} ifr_ifru;
};

#define vki_ifr_name	ifr_ifrn.ifrn_name	/* interface name 	*/
#define ifr_hwaddr	ifr_ifru.ifru_hwaddr	/* MAC address 		*/
#define	ifr_addr	ifr_ifru.ifru_addr	/* address		*/
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-p lnk	*/
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address	*/
#define	ifr_netmask	ifr_ifru.ifru_netmask	/* interface net mask	*/
#define	vki_ifr_flags	ifr_ifru.ifru_flags	/* flags		*/
#define	vki_ifr_metric	ifr_ifru.ifru_ivalue	/* metric		*/
#define	vki_ifr_mtu		ifr_ifru.ifru_mtu	/* mtu			*/
#define ifr_map		ifr_ifru.ifru_map	/* device map		*/
#define ifr_slave	ifr_ifru.ifru_slave	/* slave device		*/
#define	vki_ifr_data	ifr_ifru.ifru_data	/* for use by interface	*/
#define vki_ifr_ifindex	ifr_ifru.ifru_ivalue	/* interface index	*/
#define ifr_bandwidth	ifr_ifru.ifru_ivalue    /* link bandwidth	*/
#define ifr_qlen	ifr_ifru.ifru_ivalue	/* Queue length 	*/
#define ifr_newname	ifr_ifru.ifru_newname	/* New name		*/
#define ifr_settings	ifr_ifru.ifru_settings	/* Device/proto settings*/

struct vki_ifconf 
{
	int	ifc_len;			/* size of buffer	*/
	union 
	{
		char __user *ifcu_buf;
		struct vki_ifreq __user *ifcu_req;
	} ifc_ifcu;
};
#define	vki_ifc_buf	ifc_ifcu.ifcu_buf	/* buffer address	*/

//----------------------------------------------------------------------
// From linux-2.6.8.1/include/linux/if_arp.h
//----------------------------------------------------------------------

struct vki_arpreq {
  struct vki_sockaddr	arp_pa;		/* protocol address		*/
  struct vki_sockaddr	arp_ha;		/* hardware address		*/
  int			arp_flags;	/* flags			*/
  struct vki_sockaddr   arp_netmask;    /* netmask (only for proxy arps) */
  char			arp_dev[16];
};

//----------------------------------------------------------------------
// From linux-2.6.8.1/include/linux/route.h
//----------------------------------------------------------------------

struct vki_rtentry 
{
	unsigned long	rt_pad1;
	struct vki_sockaddr	rt_dst;		/* target address		*/
	struct vki_sockaddr	rt_gateway;	/* gateway addr (RTF_GATEWAY)	*/
	struct vki_sockaddr	rt_genmask;	/* target network mask (IP)	*/
	unsigned short	rt_flags;
	short		rt_pad2;
	unsigned long	rt_pad3;
	void		*rt_pad4;
	short		rt_metric;	/* +1 for binary compatibility!	*/
	char __user	*rt_dev;	/* forcing the device at add	*/
	unsigned long	rt_mtu;		/* per route MTU/Window 	*/
// [[Not important for Valgrind]]
//#ifndef __KERNEL__
//#define rt_mss	rt_mtu		/* Compatibility :-(            */
//#endif
	unsigned long	rt_window;	/* Window clamping 		*/
	unsigned short	rt_irtt;	/* Initial RTT			*/
};
#endif

// QQQ sort

//----------------------------------------------------------------------
// From sys/mount.h
//----------------------------------------------------------------------

typedef struct vki_fsid { vki_int32_t val[2]; } vki_fsid_t;
#define VKI_OMFSNAMELEN	16
#define VKI_OMNAMELEN	(88 - 2 * sizeof(long))
#define VKI_MFSNAMELEN	16
#define VKI_MNAMELEN	88

struct vki_statfs4 {
	long		f_spare2;
	long		f_bsize;
	long		f_iosize;
	long		f_blocks;
	long		f_bfree;
	long		f_bavail;
	long		f_files;
	long		f_ffree;
	vki_fsid_t	f_fsid;
	vki_uid_t	f_owner;
	vki_int32_t	f_type;
	vki_int32_t	f_flags;
	long		f_syncwrites;
	long		f_asyncwrites;
	char		f_fstypename[VKI_OMFSNAMELEN];
	char		f_mntonname[VKI_OMNAMELEN];
	long		f_syncreads;
	long		f_asyncreads;
	vki_int16_t	f_spares1;
	char		f_mntfromnname[VKI_OMNAMELEN];
	vki_int16_t	f_spares2;
	long		f_spare[2];
};

struct vki_statfs {
	vki_uint32_t	f_version;
	vki_uint32_t	f_type;
	vki_uint64_t	f_flags;
	vki_uint64_t	f_bsize;
	vki_uint64_t	f_iosize;
	vki_uint64_t	f_blocks;
	vki_uint64_t	f_bfree;
	vki_int64_t	f_bavail;
	vki_uint64_t	f_files;
	vki_int64_t	f_ffree;
	vki_uint64_t	f_syncwrites;
	vki_uint64_t	f_asyncwrites;
	vki_uint64_t	f_syncreads;
	vki_uint64_t	f_asyncreads;
	vki_uint64_t	f_spare[10];
	vki_uint32_t	f_namemax;
	vki_uid_t	f_owner;
	vki_fsid_t	f_fsid;
	char		f_charspare[80];
	char		f_fstypename[VKI_MFSNAMELEN];
	char		f_mntfromnname[VKI_MNAMELEN];
	char		f_mntonname[VKI_MNAMELEN];
};

#define MAXFIDSZ        16

struct vki_fid {
        vki_uint16_t    fid_len;
        vki_uint16_t    fid_reserved;
        char            fid_data[MAXFIDSZ];
};

struct vki_fhandle {
	vki_fsid_t	fh_fsid;
	struct vki_fid	fh_fid;
};

#define VKI_MNAMELEN6	88
struct vki_statfs6 {
	vki_uint32_t	f_version;
	vki_uint32_t	f_type;
	vki_uint64_t	f_flags;
	vki_uint64_t	f_bsize;
	vki_uint64_t	f_iosize;
	vki_uint64_t	f_blocks;
	vki_uint64_t	f_bfree;
	vki_int64_t	f_bavail;
	vki_uint64_t	f_files;
	vki_int64_t	f_ffree;
	vki_int64_t	f_syncwrites;
	vki_int64_t	f_asyncwrites;
	vki_int64_t	f_syncreads;
	vki_int64_t	f_asyncreads;
	vki_uint64_t	f_spare[10];
	vki_uint32_t	f_namemax;
	vki_uid_t	f_owner;
	vki_fsid_t	f_fsid;
	char		f_charspare[80];
	char		f_fstypename[VKI_MFSNAMELEN];
	char		f_mntfromnname[VKI_MNAMELEN6];
	char		f_mntonname[VKI_MNAMELEN6];
};

//----------------------------------------------------------------------
// From sys/ttycom.h
//----------------------------------------------------------------------

struct vki_winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};


//----------------------------------------------------------------------
// From sys/termios.h
//----------------------------------------------------------------------

typedef unsigned int    vki_tcflag_t;
typedef unsigned char   vki_cc_t;
typedef unsigned int    vki_speed_t;

#define VKI_NCCS 20
struct vki_termios {
	vki_tcflag_t c_iflag;		/* input mode flags */
	vki_tcflag_t c_oflag;		/* output mode flags */
	vki_tcflag_t c_cflag;		/* control mode flags */
	vki_tcflag_t c_lflag;		/* local mode flags */
	vki_cc_t c_cc[VKI_NCCS];	/* control characters */
	vki_speed_t c_ispeed;
	vki_speed_t c_ospeed;
};

//----------------------------------------------------------------------
// From sys/ioccom.h
//----------------------------------------------------------------------

/* QQQ keep linux's naming, but use our layout */

/*
 * We actually have a 16 bit "base" ioctl, which may or may not be decoded
 * into number/group
 */
#define	_VKI_IOC_BASEBITS	16
#define _VKI_IOC_NRBITS		8	/* "num" on freebsd */
#define _VKI_IOC_TYPEBITS	8	/* "group" on freebsd */

#define _VKI_IOC_SIZEBITS	13
#define _VKI_IOC_DIRBITS	3

#define	_VKI_IOC_BASEMASK	((1ul << _VKI_IOC_BASEBITS)-1)
#define _VKI_IOC_NRMASK		((1ul << _VKI_IOC_NRBITS)-1)
#define _VKI_IOC_TYPEMASK	((1ul << _VKI_IOC_TYPEBITS)-1)
#define _VKI_IOC_SIZEMASK	((1ul << _VKI_IOC_SIZEBITS)-1)
#define _VKI_IOC_DIRMASK	((1ul << _VKI_IOC_DIRBITS)-1)

#define	_VKI_IOC_BASESHIFT	0
#define _VKI_IOC_NRSHIFT	0
#define _VKI_IOC_TYPESHIFT	(_VKI_IOC_NRSHIFT+_VKI_IOC_NRBITS)
#define _VKI_IOC_SIZESHIFT	(_VKI_IOC_TYPESHIFT+_VKI_IOC_TYPEBITS)
#define _VKI_IOC_DIRSHIFT	(_VKI_IOC_SIZESHIFT+_VKI_IOC_SIZEBITS)

#define _VKI_IOC_NONE	1U	/* "void" on freebsd, as a specific mode */
#define _VKI_IOC_READ	2U	/* "out", copyout in reversed linux terminology */
#define _VKI_IOC_WRITE	4U	/* "in", copyin in reversed linux terminology */
#define _VKI_IOC_RDWR	6U	/* "inout", copyin and copyout */

#define _VKI_IOC(dir,type,nr,size) \
	(((dir)  << _VKI_IOC_DIRSHIFT) | \
	 ((type) << _VKI_IOC_TYPESHIFT) | \
	 ((nr)   << _VKI_IOC_NRSHIFT) | \
	 ((size) << _VKI_IOC_SIZESHIFT))

/* provoke compile error for invalid uses of size argument */
extern unsigned int __vki_invalid_size_argument_for_IOC;
#define _VKI_IOC_TYPECHECK(t) \
	((sizeof(t) == sizeof(t[1]) && \
	  sizeof(t) < (1 << _VKI_IOC_SIZEBITS)) ? \
	  sizeof(t) : __vki_invalid_size_argument_for_IOC)

/* used to create numbers */
#define _VKI_IO(type,nr)	_VKI_IOC(_VKI_IOC_NONE,(type),(nr),0)
#define _VKI_IOR(type,nr,size)	_VKI_IOC(_VKI_IOC_READ,(type),(nr),(_VKI_IOC_TYPECHECK(size)))
#define _VKI_IOW(type,nr,size)	_VKI_IOC(_VKI_IOC_WRITE,(type),(nr),(_VKI_IOC_TYPECHECK(size)))
#define _VKI_IOWR(type,nr,size)	_VKI_IOC(_VKI_IOC_READ|_VKI_IOC_WRITE,(type),(nr),(_VKI_IOC_TYPECHECK(size)))

/* used to decode ioctl numbers.. */
#define _VKI_IOC_DIR(nr)	(((nr) >> _VKI_IOC_DIRSHIFT) & _VKI_IOC_DIRMASK)
#define _VKI_IOC_TYPE(nr)	(((nr) >> _VKI_IOC_TYPESHIFT) & _VKI_IOC_TYPEMASK)
#define _VKI_IOC_NR(nr)		(((nr) >> _VKI_IOC_NRSHIFT) & _VKI_IOC_NRMASK)
#define _VKI_IOC_SIZE(nr)	(((nr) >> _VKI_IOC_SIZESHIFT) & _VKI_IOC_SIZEMASK)
#define _VKI_IOC_BASE(nr)	(((nr) >> _VKI_IOC_BASESHIFT) & _VKI_IOC_BASEMASK)


//----------------------------------------------------------------------
// From sys/termios.h
//----------------------------------------------------------------------

#if 0
#define VKI_TCGETS	0x5401
#define VKI_TCSETS	0x5402 /* Clashes with SNDCTL_TMR_START sound ioctl */
#define VKI_TCSETSW	0x5403
#define VKI_TCSETSF	0x5404
#define VKI_TCGETA	0x5405	y
#define VKI_TCSETA	0x5406	y
#define VKI_TCSETAW	0x5407	y
#define VKI_TCSETAF	0x5408	y
#define VKI_TCSBRK	0x5409
#define VKI_TCXONC	0x540A
#define VKI_TCFLSH	0x540B	y
#define VKI_TIOCSCTTY	0x540E
#define VKI_TIOCGPGRP	0x540F	y
#define VKI_TIOCSPGRP	0x5410	y
#define VKI_TIOCOUTQ	0x5411
#define VKI_TIOCGWINSZ	0x5413	y
#define VKI_TIOCSWINSZ	0x5414	y
#define VKI_TIOCMGET	0x5415	y
#define VKI_TIOCMBIS	0x5416	y
#define VKI_TIOCMBIC	0x5417	y
#define VKI_TIOCMSET	0x5418	y
#define VKI_FIONREAD	0x541B
#define VKI_TIOCLINUX	0x541C
#define VKI_FIONBIO	0x5421
#define VKI_TCSBRKP	0x5425	/* Needed for POSIX tcsendbreak() */
#define VKI_TIOCGPTN	_VKI_IOR('T',0x30, unsigned int) /* Get Pty Number (of pty-mux device) */
#define VKI_TIOCSPTLCK	_VKI_IOW('T',0x31, int)  /* Lock/unlock Pty */

#define VKI_FIOASYNC	0x5452
#define VKI_TIOCSERGETLSR   0x5459 /* Get line status register */

#define VKI_TIOCGICOUNT	0x545D	/* read serial port inline interrupt counts */
#endif

#define	VKI_TIOCFLUSH	_VKI_IOW('t', 16, int);
#define	VKI_TIOCGETA	_VKI_IOR('t', 19, struct vki_termios)	/* get termios */
#define	VKI_TIOCSETA	_VKI_IOR('t', 20, struct vki_termios)	/* set termios */
#define	VKI_TIOCSETAW	_VKI_IOR('t', 21, struct vki_termios)	/* drain,set */
#define	VKI_TIOCSETAF	_VKI_IOR('t', 22, struct vki_termios)	/* flush,set */

#define	VKI_TIOCSBRK	_VKI_IO('t', 123)
#define	VKI_TIOCCBRK	_VKI_IO('t', 122)
#define	VKI_TIOCGPGRP	_VKI_IOR('t', 119, int)		/* get pgrp */
#define	VKI_TIOCSPGRP	_VKI_IOW('t', 118, int)		/* set pgrp */

#define VKI_TIOCGWINSZ	_VKI_IOR('t', 104, struct vki_winsize)  /* get window size */
#define VKI_TIOCSWINSZ	_VKI_IOW('t', 103, struct vki_winsize)  /* set window size */

#define VKI_TIOCMGET	_VKI_IOR('t', 106, int)	/* get all modem bits */
#define VKI_TIOCMBIS	_VKI_IOW('t', 108, int)	/* bis modem bits */
#define VKI_TIOCMBIC	_VKI_IOW('t', 107, int)	/* bic modem bits */
#define VKI_TIOCMSET	_VKI_IOW('t', 109, int)	/* set all modem bits */


//----------------------------------------------------------------------
// From sys/filio.h
//----------------------------------------------------------------------

#define VKI_FIOCLEX	_VKI_IO('f', 1)		/* close on exec */
#define VKI_FIONCLEX	_VKI_IO('f', 2)		/* no close on exec */
#define VKI_FIONREAD	_VKI_IOR('f', 127, int)
#define VKI_FIONBIO	_VKI_IOW('f', 126, int)
#define VKI_FIOASYNC	_VKI_IOW('f', 125, int)
#define VKI_FIOSETOWN	_VKI_IOW('f', 124, int)
#define VKI_FIOGETOWN	_VKI_IOW('f', 123, int)

//----------------------------------------------------------------------
// From sys/poll.h
//----------------------------------------------------------------------

#define VKI_POLLIN		0x0001

struct vki_pollfd {
	int fd;
	short events;
	short revents;
};

//----------------------------------------------------------------------
// From sys/kevent.h
//----------------------------------------------------------------------
struct vki_kevent {
	vki_uintptr_t  ident;
	vki_int16_t    filter;
	vki_uint16_t   flags;
	vki_uint32_t   fflags;
	vki_intptr_t   data;
	void           *udata;
};


// QQQ sort

//----------------------------------------------------------------------
// From sys/resource.h
//----------------------------------------------------------------------

struct	vki_rusage {
	struct vki_timeval ru_utime;	/* user time used */
	struct vki_timeval ru_stime;	/* system time used */
	long	ru_maxrss;		/* maximum resident set size */
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data size */
	long	ru_isrss;		/* integral unshared stack size */
	long	ru_minflt;		/* page reclaims */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
};

struct vki_rlimit {
	vki_rlim_t	rlim_cur;
	vki_rlim_t	rlim_max;
};

#define VKI_RLIMIT_DATA		2	/* max data size */
#define VKI_RLIMIT_STACK	3	/* max stack size */
#define VKI_RLIMIT_CORE		4	/* max core file size */
#define VKI_RLIMIT_NOFILE	8	/* max number of open files */

//----------------------------------------------------------------------
// From sys/procfs.h
//----------------------------------------------------------------------

#define VKI_PRSTATUS_VERSION	1
struct vki_elf_prstatus
{
	int		pr_version;	/* version of struct - PRSTATUS_VERSION */
	vki_size_t	pr_statussz;
	vki_size_t	pr_gregsetsz;
	vki_size_t	pr_fpregsetsz;
	int		pr_osreldate;
	short		pr_cursig;	/* Current signal */
	vki_pid_t	pr_pid;
	vki_elf_gregset_t pr_reg;	/* GP registers */
};

#define VKI_ELF_PRARGSZ	(80)	/* Number of chars for args */
#define VKI_MAXCOMLEN	(16)

#define	VKI_PRPSINFO_VERSION	1
struct vki_elf_prpsinfo
{
	int	pr_version;	/* version of struct - PRPSINFO_VERSION */
	vki_size_t	pr_psinfosz;
	char	pr_fname[VKI_MAXCOMLEN+1];		/* filename of executable */
	char	pr_psargs[VKI_ELF_PRARGSZ];	/* initial part of arg list */
};

//----------------------------------------------------------------------
// From posix4/mqueue.h
//----------------------------------------------------------------------

struct vki_mq_attr {
	long	mq_flags;	/* message queue flags			*/
	long	mq_maxmsg;	/* maximum number of messages		*/
	long	mq_msgsize;	/* maximum message size			*/
	long	mq_curmsgs;	/* number of messages currently queued	*/
};

//----------------------------------------------------------------------
// From sys/ucontext.h
//----------------------------------------------------------------------

#define	VKI_UCF_SWAPPED	1

struct vki_ucontext {
	vki_sigset_t		uc_sigmask;
	struct vki_mcontext	uc_mcontext;
	struct vki_ucontext	*uc_link;
	vki_stack_t		uc_stack;
	int			uc_flags;
	unsigned int		__spare__[4];
};

//----------------------------------------------------------------------
// From sys/utsname.h
//----------------------------------------------------------------------

#define VKI_SYS_NMLN        32

struct vki_utsname {
        char    sysname[VKI_SYS_NMLN];      /* Name of this OS. */
        char    nodename[VKI_SYS_NMLN];     /* Name of this network node. */
        char    release[VKI_SYS_NMLN];      /* Release level. */
        char    version[VKI_SYS_NMLN];      /* Version level. */
        char    machine[VKI_SYS_NMLN];      /* Hardware type. */
};

#define VKI_IPC_CREAT  00001000   /* create if key is nonexistent */
#define VKI_IPC_EXCL   00002000   /* fail if key exists */
#define VKI_IPC_NOWAIT 00004000   /* return error on wait */

#define VKI_IPC_RMID 0     /* remove resource */
#define VKI_IPC_SET  1     /* set ipc_perm options */
#define VKI_IPC_STAT 2     /* get ipc_perm options */
#define VKI_IPC_INFO 3     /* see ipcs */

struct vki_ipc_perm
{
	vki_uid_t	cuid;
	vki_gid_t	cgid;
	vki_uid_t	uid;
	vki_gid_t	gid;
	vki_mode_t	mode;
	unsigned short	seq;
	vki_key_t	key;
};

struct vki_ipc_perm7
{
	unsigned short	cuid;
	unsigned short	cgid;
	unsigned short	uid;
	unsigned short	gid;
	unsigned short	mode;
	unsigned short	seq;
	vki_key_t	key;
};

//----------------------------------------------------------------------
// From sys/sem.h
//----------------------------------------------------------------------

#if 0
#define VKI_SEMOP                1
#define VKI_SEMGET               2
#define VKI_SEMCTL               3
#define VKI_SEMTIMEDOP           4
#endif

#define VKI_GETALL  6       /* get all semval's */
#define VKI_SETVAL  8       /* set semval */
#define VKI_SETALL  9       /* set all semval's */
#define VKI_SEM_STAT 10
#define VKI_SEM_INFO 11

/* Obsolete, used only for backwards compatibility and libc5 compiles */
struct vki_semid_ds {
	struct vki_ipc_perm	sem_perm;		/* permissions .. see ipc.h */
        // [[Use void* to avoid excess header copying]]
	void/*struct sem	*/*sem_base;		/* ptr to first semaphore in array */
	unsigned short		sem_nsems;		/* no. of semaphores in array */
	vki_time_t		sem_otime;		/* last semop time */
	vki_time_t		sem_ctime;		/* last change time */
	long			sem_pad2;
	long			sem_pad3[4];
};

struct vki_sembuf {
	vki_uint16_t	sem_num;	/* semaphore index in array */
	vki_int16_t	sem_op;		/* semaphore operation */
	vki_int16_t	sem_flg;	/* operation flags */
};

union vki_semun {
	int val;			/* value for SETVAL */
	struct vki_semid_ds *buf;	/* buffer for IPC_STAT & IPC_SET */
	vki_uint16_t *array;	/* array for GETALL & SETALL */
};


//----------------------------------------------------------------------
// From sys/errno.h
//----------------------------------------------------------------------

#define VKI_ERESTART	-1
#define VKI_EPERM           1               /* Operation not permitted */
#define VKI_ENOENT          2               /* No such file or directory */
#define VKI_ESRCH           3               /* No such process */
#define VKI_EINTR           4               /* Interrupted system call */
#define VKI_EIO             5               /* Input/output error */
#define VKI_ENXIO           6               /* Device not configured */
#define VKI_E2BIG           7               /* Argument list too long */
#define VKI_ENOEXEC         8               /* Exec format error */
#define VKI_EBADF           9               /* Bad file descriptor */
#define VKI_ECHILD          10              /* No child processes */
#define VKI_EDEADLK         11              /* Resource deadlock avoided */
#define VKI_ENOMEM          12              /* Cannot allocate memory */
#define VKI_EACCES          13              /* Permission denied */
#define VKI_EFAULT          14              /* Bad address */
#define VKI_ENOTBLK         15              /* Block device required */
#define VKI_EBUSY           16              /* Device busy */
#define VKI_EEXIST          17              /* File exists */
#define VKI_EXDEV           18              /* Cross-device link */
#define VKI_ENODEV          19              /* Operation not supported by device */
#define VKI_ENOTDIR         20              /* Not a directory */
#define VKI_EISDIR          21              /* Is a directory */
#define VKI_EINVAL          22              /* Invalid argument */
#define VKI_ENFILE          23              /* Too many open files in system */
#define VKI_EMFILE          24              /* Too many open files */
#define VKI_ENOTTY          25              /* Inappropriate ioctl for device */
#define VKI_ETXTBSY         26              /* Text file busy */
#define VKI_EFBIG           27              /* File too large */
#define VKI_ENOSPC          28              /* No space left on device */
#define VKI_ESPIPE          29              /* Illegal seek */
#define VKI_EROFS           30              /* Read-only filesystem */
#define VKI_EMLINK          31              /* Too many links */
#define VKI_EPIPE           32              /* Broken pipe */
#define VKI_EDOM            33              /* Numerical argument out of domain */
#define VKI_ERANGE          34              /* Result too large */
#define VKI_EAGAIN          35              /* Resource temporarily unavailable */
#define VKI_EWOULDBLOCK     VKI_EAGAIN          /* Operation would block */
#define VKI_EINPROGRESS     36              /* Operation now in progress */
#define VKI_EALREADY        37              /* Operation already in progress */
#define VKI_ENOTSOCK        38              /* Socket operation on non-socket */
#define VKI_EDESTADDRREQ    39              /* Destination address required */
#define VKI_EMSGSIZE        40              /* Message too long */
#define VKI_EPROTOTYPE      41              /* Protocol wrong type for socket */
#define VKI_ENOPROTOOPT     42              /* Protocol not available */
#define VKI_EPROTONOSUPPORT 43              /* Protocol not supported */
#define VKI_ESOCKTNOSUPPORT 44              /* Socket type not supported */
#define VKI_EOPNOTSUPP      45              /* Operation not supported */
#define VKI_ENOTSUP         VKI_EOPNOTSUPP      /* Operation not supported */
#define VKI_EPFNOSUPPORT    46              /* Protocol family not supported */
#define VKI_EAFNOSUPPORT    47              /* Address family not supported by protocol family */
#define VKI_EADDRINUSE      48              /* Address already in use */
#define VKI_EADDRNOTAVAIL   49
#define VKI_ENETDOWN        50              /* Network is down */
#define VKI_ENETUNREACH     51              /* Network is unreachable */
#define VKI_ENETRESET       52              /* Network dropped connection on reset */
#define VKI_ECONNABORTED    53              /* Software caused connection abort */
#define VKI_ECONNRESET      54              /* Connection reset by peer */
#define VKI_ENOBUFS         55              /* No buffer space available */
#define VKI_EISCONN         56              /* Socket is already connected */
#define VKI_ENOTCONN        57              /* Socket is not connected */
#define VKI_ESHUTDOWN       58              /* Can't send after socket shutdown */
#define VKI_ETOOMANYREFS    59              /* Too many references: can't splice */
#define VKI_ETIMEDOUT       60              /* Operation timed out */
#define VKI_ECONNREFUSED    61              /* Connection refused */
#define VKI_ELOOP           62              /* Too many levels of symbolic links */
#define VKI_ENAMETOOLONG    63              /* File name too long */
#define VKI_EHOSTDOWN       64              /* Host is down */
#define VKI_EHOSTUNREACH    65              /* No route to host */
#define VKI_ENOTEMPTY       66              /* Directory not empty */
#define VKI_EPROCLIM        67              /* Too many processes */
#define VKI_EUSERS          68              /* Too many users */
#define VKI_EDQUOT          69              /* Disc quota exceeded */
#define VKI_ESTALE          70              /* Stale NFS file handle */
#define VKI_EREMOTE         71              /* Too many levels of remote in path */
#define VKI_EBADRPC         72              /* RPC struct is bad */
#define VKI_ERPCMISMATCH    73              /* RPC version wrong */
#define VKI_EPROGUNAVAIL    74              /* RPC prog. not avail */
#define VKI_EPROGMISMATCH   75              /* Program version wrong */
#define VKI_EPROCUNAVAIL    76              /* Bad procedure for program */
#define VKI_ENOLCK          77              /* No locks available */
#define VKI_ENOSYS          78              /* Function not implemented */
#define VKI_EFTYPE          79              /* Inappropriate file type or format */
#define VKI_EAUTH           80              /* Authentication error */
#define VKI_ENEEDAUTH       81              /* Need authenticator */
#define VKI_EIDRM           82              /* Identifier removed */
#define VKI_ENOMSG          83              /* No message of desired type */
#define VKI_EOVERFLOW       84              /* Value too large to be stored in data type */
#define VKI_ECANCELED       85              /* Operation canceled */
#define VKI_EILSEQ          86              /* Illegal byte sequence */
#define VKI_ENOATTR         87              /* Attribute not found */
#define VKI_EDOOFUS         88              /* Programming error */
#define VKI_EBADMSG         89              /* Bad message */
#define VKI_EMULTIHOP       90              /* Multihop attempted */
#define VKI_ENOLINK         91              /* Link has been severed */
#define VKI_EPROTO          92              /* Protocol error */
#define VKI_ENOTCAPABLE     93              /* Capabilities insufficient */
#define VKI_ECAPMODE        94              /* Not permitted in capability mode */

//----------------------------------------------------------------------
// From sys/wait.h
//----------------------------------------------------------------------

#define VKI_WNOHANG	0x00000001

//----------------------------------------------------------------------
// From sys/mman.h
//----------------------------------------------------------------------

#define VKI_PROT_NONE	0x00		/* No page permissions */
#define VKI_PROT_READ	0x01		/* page can be read */
#define VKI_PROT_WRITE	0x02		/* page can be written */
#define VKI_PROT_EXEC	0x04		/* page can be executed */

#define VKI_MAP_SHARED	0x01		/* Share changes */
#define VKI_MAP_PRIVATE	0x02		/* Changes are private */
#define VKI_MAP_FIXED	0x10		/* Interpret addr exactly */
#define VKI_MAP_NORESERVE	0x0040		/* don't check for reservations */
#define	VKI_MAP_STACK	0x400
#define VKI_MAP_ANON	0x1000	/* don't use a file */
#define	VKI_MAP_ANONYMOUS	VKI_MAP_ANON

//----------------------------------------------------------------------
// From sys/stat.h
//----------------------------------------------------------------------

#define VKI_S_IFMT  00170000

#define VKI_S_IFWHT  0160000
#define VKI_S_IFSOCK 0140000
#define VKI_S_IFLNK  0120000
#define VKI_S_IFREG  0100000
#define VKI_S_IFBLK  0060000
#define VKI_S_IFDIR  0040000
#define VKI_S_IFCHR  0020000
#define VKI_S_IFIFO  0010000
#define VKI_S_ISUID  0004000
#define VKI_S_ISGID  0002000
#define VKI_S_ISTXT  0001000

#define VKI_S_ISLNK(m)	(((m) & VKI_S_IFMT) == VKI_S_IFLNK)
#define VKI_S_ISREG(m)	(((m) & VKI_S_IFMT) == VKI_S_IFREG)
#define VKI_S_ISDIR(m)	(((m) & VKI_S_IFMT) == VKI_S_IFDIR)
#define VKI_S_ISCHR(m)	(((m) & VKI_S_IFMT) == VKI_S_IFCHR)
#define VKI_S_ISBLK(m)	(((m) & VKI_S_IFMT) == VKI_S_IFBLK)
#define VKI_S_ISFIFO(m)	(((m) & VKI_S_IFMT) == VKI_S_IFIFO)
#define VKI_S_ISSOCK(m)	(((m) & VKI_S_IFMT) == VKI_S_IFSOCK)
#define VKI_S_ISWHT(m)	(((m) & VKI_S_IFMT) == VKI_S_IFWHT)

#define VKI_S_IRWXU 00700
#define VKI_S_IRUSR 00400
#define VKI_S_IWUSR 00200
#define VKI_S_IXUSR 00100

#define VKI_S_IRWXG 00070
#define VKI_S_IRGRP 00040
#define VKI_S_IWGRP 00020
#define VKI_S_IXGRP 00010

#define VKI_S_IRWXO 00007
#define VKI_S_IROTH 00004
#define VKI_S_IWOTH 00002
#define VKI_S_IXOTH 00001


//----------------------------------------------------------------------
// From sys/dirent.h
//----------------------------------------------------------------------

struct vki_dirent {
	vki_uint32_t	d_fileno;
	vki_uint16_t	d_reclen;
	vki_uint8_t	d_type;
	vki_uint8_t	d_namelen;
	char		d_name[256]; /* We must not include limits.h! */
};

//----------------------------------------------------------------------
// From sys/fcntl.h
//----------------------------------------------------------------------

#define VKI_O_RDONLY	  0x0000
#define VKI_O_WRONLY	  0x0001
#define VKI_O_RDWR	  0x0002

#define VKI_O_NONBLOCK	  0x0004
#define VKI_O_APPEND	  0x0008
#define VKI_O_CREAT	  0x0200	/* not fcntl */
#define VKI_O_TRUNC	  0x0400	/* not fcntl */
#define VKI_O_EXCL	  0x0800	/* not fcntl */

#define VKI_AT_FDCWD            -100

#define VKI_F_DUPFD		0	/* dup */
#define VKI_F_GETFD		1	/* get close_on_exec */
#define VKI_F_SETFD		2	/* set/clear close_on_exec */
#define VKI_F_GETFL		3	/* get file->f_flags */
#define VKI_F_SETFL		4	/* set file->f_flags */
#define VKI_F_SETOWN		5	/*  for sockets. */
#define VKI_F_GETOWN		6	/*  for sockets. */
#define VKI_F_OGETLK		7	/* get record locking information */
#define VKI_F_OSETLK		8	/* set record locking information */
#define VKI_F_OSETLKW		9	/* F_SETLK; wait if blocked */
#define VKI_F_DUP2FD		10	/* duplicate file descriptor to arg */
#define VKI_F_GETLK		11	/* get record locking information */
#define VKI_F_SETLK		12	/* set record locking information */
#define VKI_F_SETLKW		13	/* F_SETLK; wait if blocked */
#define VKI_F_SETLK_REMOTE	14	/* debugging support for remote locks */

/* for F_[GET|SET]FL */
#define VKI_FD_CLOEXEC	1	/* actually anything with low bit set goes */

//----------------------------------------------------------------------
// From sys/unistd.h
//----------------------------------------------------------------------

#define VKI_SEEK_SET              0
#define VKI_SEEK_CUR              1
#define VKI_SEEK_END              2

#define VKI_F_OK	0       /* test for existence of file */
#define VKI_X_OK	0x01    /* test for execute or search permission */
#define VKI_W_OK	0x02    /* test for write permission */
#define VKI_R_OK	0x04    /* test for read permission */

//----------------------------------------------------------------------
// From sys/msg.h
//----------------------------------------------------------------------

#if 0	/* not in freebsd */
#define VKI_MSGSND              11
#define VKI_MSGRCV              12
#define VKI_MSGGET              13
#define VKI_MSGCTL              14
#endif

struct vki_msqid_ds {
	struct vki_ipc_perm msg_perm;
	struct vki_msg *msg_first;		/* first message on queue,unused  */
	struct vki_msg *msg_last;		/* last message in queue,unused */
	vki_uint32_t msg_cbytes;	/* current number of bytes on queue */
	vki_uint32_t msg_qnum;	/* number of messages in queue */
	vki_uint32_t msg_qbytes;	/* max number of bytes on queue */
	vki_pid_t	msg_lspid;	/* pid of last msgsnd */
	vki_pid_t	msg_lrpid;	/* last receive pid */
	vki_time_t	msg_stime;	/* last msgsnd time */
	vki_uint32_t	msg_pad1;
	vki_time_t	msg_rtime;	/* last msgrcv time */
	vki_uint32_t	msg_pad2;
	vki_time_t 	msg_ctime;	/* last change time */
	vki_uint32_t	msg_pad3;
	vki_uint32_t	msg_pad4[4];
};

struct vki_msgbuf {
	long mtype;         /* type of message */
	char mtext[1];      /* message text */
};


//----------------------------------------------------------------------
// From sys/shm.h
//----------------------------------------------------------------------

struct vki_shmid_ds {
	struct vki_ipc_perm	shm_perm;	/* operation perms */
	vki_size_t		shm_segsz;	/* size of segment (bytes) */
	vki_pid_t		shm_lpid;	/* pid of last operator */
	vki_pid_t		shm_cpid;	/* pid of creator */
	int			shm_nattch;	/* no. of current attaches */
	vki_time_t		shm_atime;	/* last attach time */
	vki_time_t		shm_dtime;	/* last detach time */
	vki_time_t		shm_ctime;	/* last change time */
};

struct vki_shmid_ds7 {
	struct vki_ipc_perm7	shm_perm;	/* operation perms */
	int			shm_segsz;	/* size of segment (bytes) */
	vki_pid_t		shm_lpid;	/* pid of last operator */
	vki_pid_t		shm_cpid;	/* pid of creator */
	short			shm_nattch;	/* no. of current attaches */
	vki_time_t		shm_atime;	/* last attach time */
	vki_time_t		shm_dtime;	/* last detach time */
	vki_time_t		shm_ctime;	/* last change time */
	void			*shm_internal;	/* sysv stupidity */
};

#define VKI_SHMLBA  VKI_PAGE_SIZE
#define VKI_SHM_RDONLY  010000  /* read-only access */
#define	VKI_SHM_ANON	(1UL)

#if 0	/* not in freebsd abi */
#define VKI_SHMAT               21
#define VKI_SHMDT               22
#define VKI_SHMGET              23
#define VKI_SHMCTL              24
#endif

#if 0
//----------------------------------------------------------------------
// From linux-2.6.8.1/include/linux/sockios.h
//----------------------------------------------------------------------

#define VKI_SIOCOUTQ		VKI_TIOCOUTQ

#define VKI_SIOCADDRT		0x890B	/* add routing table entry	*/
#define VKI_SIOCDELRT		0x890C	/* delete routing table entry	*/

#define VKI_SIOCGIFNAME		0x8910	/* get iface name		*/
#define VKI_SIOCGIFCONF		0x8912	/* get iface list		*/
#define VKI_SIOCGIFFLAGS	0x8913	/* get flags			*/
#define VKI_SIOCSIFFLAGS	0x8914	/* set flags			*/
#define VKI_SIOCGIFADDR		0x8915	/* get PA address		*/
#define VKI_SIOCSIFADDR		0x8916	/* set PA address		*/
#define VKI_SIOCGIFDSTADDR	0x8917	/* get remote PA address	*/
#define VKI_SIOCSIFDSTADDR	0x8918	/* set remote PA address	*/
#define VKI_SIOCGIFBRDADDR	0x8919	/* get broadcast PA address	*/
#define VKI_SIOCSIFBRDADDR	0x891a	/* set broadcast PA address	*/
#define VKI_SIOCGIFNETMASK	0x891b	/* get network PA mask		*/
#define VKI_SIOCSIFNETMASK	0x891c	/* set network PA mask		*/
#define VKI_SIOCGIFMETRIC	0x891d	/* get metric			*/
#define VKI_SIOCSIFMETRIC	0x891e	/* set metric			*/
#define VKI_SIOCGIFMTU		0x8921	/* get MTU size			*/
#define VKI_SIOCSIFMTU		0x8922	/* set MTU size			*/
#define	VKI_SIOCSIFHWADDR	0x8924	/* set hardware address 	*/
#define VKI_SIOCGIFHWADDR	0x8927	/* Get hardware address		*/
#define VKI_SIOCGIFINDEX	0x8933	/* name -> if_index mapping	*/

#define VKI_SIOCGIFTXQLEN	0x8942	/* Get the tx queue length	*/
#define VKI_SIOCSIFTXQLEN	0x8943	/* Set the tx queue length 	*/

#define VKI_SIOCGMIIPHY		0x8947	/* Get address of MII PHY in use. */
#define VKI_SIOCGMIIREG		0x8948	/* Read MII PHY register.	*/
#define VKI_SIOCSMIIREG		0x8949	/* Write MII PHY register.	*/

#define VKI_SIOCDARP		0x8953	/* delete ARP table entry	*/
#define VKI_SIOCGARP		0x8954	/* get ARP table entry		*/
#define VKI_SIOCSARP		0x8955	/* set ARP table entry		*/

#define VKI_SIOCDRARP		0x8960	/* delete RARP table entry	*/
#define VKI_SIOCGRARP		0x8961	/* get RARP table entry		*/
#define VKI_SIOCSRARP		0x8962	/* set RARP table entry		*/

#define VKI_SIOCGIFMAP		0x8970	/* Get device parameters	*/
#define VKI_SIOCSIFMAP		0x8971	/* Set device parameters	*/

//----------------------------------------------------------------------
// From linux-2.6.9/include/linux/kb.h
//----------------------------------------------------------------------

#define VKI_GIO_FONT       0x4B60  /* gets font in expanded form */
#define VKI_PIO_FONT       0x4B61  /* use font in expanded form */

#define VKI_GIO_FONTX      0x4B6B  /* get font using struct consolefontdesc */
#define VKI_PIO_FONTX      0x4B6C  /* set font using struct consolefontdesc */
struct vki_consolefontdesc {
	unsigned short charcount;	/* characters in font (256 or 512) */
	unsigned short charheight;	/* scan lines per character (1-32) */
	char __user *chardata;		/* font data in expanded form */
};

#define VKI_PIO_FONTRESET  0x4B6D  /* reset to default font */

#define VKI_GIO_CMAP       0x4B70  /* gets colour palette on VGA+ */
#define VKI_PIO_CMAP       0x4B71  /* sets colour palette on VGA+ */

#define VKI_KIOCSOUND      0x4B2F  /* start sound generation (0 for off) */
#define VKI_KDMKTONE       0x4B30  /* generate tone */

#define VKI_KDGETLED       0x4B31  /* return current led state */
#define VKI_KDSETLED       0x4B32  /* set led state [lights, not flags] */

#define VKI_KDGKBTYPE      0x4B33  /* get keyboard type */

#define VKI_KDADDIO        0x4B34  /* add i/o port as valid */
#define VKI_KDDELIO        0x4B35  /* del i/o port as valid */
#define VKI_KDENABIO       0x4B36  /* enable i/o to video board */
#define VKI_KDDISABIO      0x4B37  /* disable i/o to video board */

#define VKI_KDSETMODE      0x4B3A  /* set text/graphics mode */
#define VKI_KDGETMODE      0x4B3B  /* get current mode */

#define VKI_KDMAPDISP      0x4B3C  /* map display into address space */
#define VKI_KDUNMAPDISP    0x4B3D  /* unmap display from address space */

#define		VKI_E_TABSZ		256
#define VKI_GIO_SCRNMAP    0x4B40  /* get screen mapping from kernel */
#define VKI_PIO_SCRNMAP	   0x4B41  /* put screen mapping table in kernel */
#define VKI_GIO_UNISCRNMAP 0x4B69  /* get full Unicode screen mapping */
#define VKI_PIO_UNISCRNMAP 0x4B6A  /* set full Unicode screen mapping */

#define VKI_GIO_UNIMAP     0x4B66  /* get unicode-to-font mapping from kernel */
#define VKI_PIO_UNIMAP     0x4B67  /* put unicode-to-font mapping in kernel */
#define VKI_PIO_UNIMAPCLR  0x4B68  /* clear table, possibly advise hash algorithm */

#define VKI_KDGKBMODE      0x4B44  /* gets current keyboard mode */
#define VKI_KDSKBMODE      0x4B45  /* sets current keyboard mode */

#define VKI_KDGKBMETA      0x4B62  /* gets meta key handling mode */
#define VKI_KDSKBMETA      0x4B63  /* sets meta key handling mode */

#define VKI_KDGKBLED       0x4B64  /* get led flags (not lights) */
#define VKI_KDSKBLED       0x4B65  /* set led flags (not lights) */

struct vki_kbentry {
	unsigned char kb_table;
	unsigned char kb_index;
	unsigned short kb_value;
};
#define VKI_KDGKBENT       0x4B46  /* gets one entry in translation table */
#define VKI_KDSKBENT       0x4B47  /* sets one entry in translation table */

struct vki_kbsentry {
	unsigned char kb_func;
	unsigned char kb_string[512];
};
#define VKI_KDGKBSENT      0x4B48  /* gets one function key string entry */
#define VKI_KDSKBSENT      0x4B49  /* sets one function key string entry */

struct vki_kbdiacr {
        unsigned char diacr, base, result;
};
struct vki_kbdiacrs {
        unsigned int kb_cnt;    /* number of entries in following array */
	struct vki_kbdiacr kbdiacr[256];    /* MAX_DIACR from keyboard.h */
};
#define VKI_KDGKBDIACR     0x4B4A  /* read kernel accent table */
#define VKI_KDSKBDIACR     0x4B4B  /* write kernel accent table */

struct vki_kbkeycode {
	unsigned int scancode, keycode;
};
#define VKI_KDGETKEYCODE   0x4B4C  /* read kernel keycode table entry */
#define VKI_KDSETKEYCODE   0x4B4D  /* write kernel keycode table entry */

#define VKI_KDSIGACCEPT    0x4B4E  /* accept kbd generated signals */

struct vki_kbd_repeat {
	int delay;	/* in msec; <= 0: don't change */
	int period;	/* in msec; <= 0: don't change */
			/* earlier this field was misnamed "rate" */
};
#define VKI_KDKBDREP       0x4B52  /* set keyboard delay/repeat rate;
                                    * actually used values are returned */

#define VKI_KDFONTOP       0x4B72  /* font operations */

//----------------------------------------------------------------------
// From linux-2.6.9/include/linux/kb.h
//----------------------------------------------------------------------

typedef __vki_kernel_uid32_t vki_qid_t; /* Type in which we store ids in memory */

#endif

//----------------------------------------------------------------------
// From sys/ptrace.h
//----------------------------------------------------------------------

#define VKI_PTRACE_TRACEME         0
#define VKI_PTRACE_READ_I	   1
#define VKI_PTRACE_READ_D	   2
/* 3 - read user struct */
#define VKI_PTRACE_WRITE_I	   4
#define VKI_PTRACE_WRITE_D	   5
/* 6 - write user struct */
#define VKI_PTRACE_CONTINUE	   7
#define VKI_PTRACE_KILL		   8
#define VKI_PTRACE_STEP		   9
#define VKI_PTRACE_ATTACH	   10
#define VKI_PTRACE_DETACH	   11
#define VKI_PTRACE_IO		   12
#define VKI_PTRACE_LWPINFO	   13
#define VKI_PTRACE_GETNUMLWPS	   14
#define VKI_PTRACE_GETLWPLIST	   15
#define VKI_PTRACE_CLEARSTEP	   16
#define VKI_PTRACE_SETSTEP	   17
#define VKI_PTRACE_SUSPEND	   18
#define VKI_PTRACE_RESUME	   19
#define VKI_PTRACE_TO_SCE	   20
#define VKI_PTRACE_TO_SCX	   21
#define VKI_PTRACE_SYSCALL	   22
/* md */
#define VKI_PTRACE_GETREGS	   33
#define VKI_PTRACE_SETREGS	   34
#define VKI_PTRACE_GETFPREGS	   35
#define VKI_PTRACE_SETFPREGS	   36
#define VKI_PTRACE_GETDBREGS	   37
#define VKI_PTRACE_SETDBREGS	   38

#define	VKI_PTRACE_VM_TIMESTAMP    40
#define	VKI_PTRACE_VM_ENTRY        41

#define VKI_PTRACE_FIRSTMACH	   64

struct vki_ptrace_io_desc {
	int		piod_op;
	void *		piod_offs;
	void *		piod_addr;
	vki_size_t	piod_len;
};
#define VKI_PIOD_READ_D		1
#define VKI_PIOD_WRITE_D	2
#define VKI_PIOD_READ_I		3
#define VKI_PIOD_WRITE_I	4

struct vki_ptrace_lwpinfo {
	vki_lwpid_t	pl_lwpid;
	int		pl_event;
#define	VKI_PL_EVENT_NONE	0
#define	VKI_PL_EVENT_SIGNAL	1
	int		pl_flags;
#define VKI_FLAG_SA		0x01
#define	VKI_FLAG_BOUND		0x02
	vki_sigset_t pl_sigmask;
	vki_sigset_t pl_siglist;
};

struct vki_ptrace_vm_entry {
	int		pve_entry;	/* Entry number used for iteration. */
	int		pve_timestamp;	/* Generation number of VM map. */
	unsigned long	pve_start;	/* Start VA of range. */
	unsigned long	pve_end;	/* End VA of range (incl). */
	unsigned long	pve_offset;	/* Offset in backing object. */
	unsigned int	pve_prot;	/* Protection of memory range. */
	unsigned int	pve_pathlen;	/* Size of path. */
	long		pve_fileid;	/* File ID. */
	vki_uint32_t	pve_fsid;	/* File system ID. */
	char		*pve_path;	/* Path name of object. */
};

#endif // __VKI_FREEBSD_H

//----------------------------------------------------------------------
// From i386/include/sysarch.h and amd64/include/sysarch.h (interchangeable)
//----------------------------------------------------------------------

#define VKI_I386_GET_FSBASE     7
#define VKI_I386_SET_FSBASE     8
#define VKI_I386_GET_GSBASE     9
#define VKI_I386_SET_GSBASE     10

#define VKI_AMD64_GET_FSBASE    128
#define VKI_AMD64_SET_FSBASE    129
#define VKI_AMD64_GET_GSBASE    130
#define VKI_AMD64_SET_GSBASE    131

//----------------------------------------------------------------------
// From sys/module.h
//----------------------------------------------------------------------

#define VKI_MAXMODNAME 32

typedef union vki_modspecific {
	vki_int32_t	intval;
	vki_uint32_t	u_intval;
#if defined(VGP_x86_freebsd)
	vki_int32_t	longval;
	vki_uint32_t	u_longval;
#elif defined(VGP_amd64_freebsd)
	vki_int64_t	longval;
	vki_uint64_t	u_longval;
#else
#error Unknown platform
#endif
} vki_modspecific_t;

struct vki_module_stat {
	int	version;
	char	name[VKI_MAXMODNAME];
	int	refs;
	int	id;
	vki_modspecific_t data;
};

//----------------------------------------------------------------------
// From sys/rtprio.h
//----------------------------------------------------------------------

struct vki_rtprio {
	vki_uint16_t	type;
	vki_uint16_t	prio;
};

#define VKI_RTP_LOOKUP	0
#define VKI_RTP_SET	1

//----------------------------------------------------------------------
// From sys/umtx.h
//----------------------------------------------------------------------

struct vki_umtx {
	unsigned long	u_owner;
};

struct vki_umutex {
	vki_lwpid_t	m_owner;
	vki_uint32_t	m_flags;
	vki_uint32_t	m_ceilings[2];
	vki_uint32_t	m_spare[4];
};

struct vki_ucond {
	vki_uint32_t	c_has_waiters;
	vki_uint32_t 	c_flags;
	vki_uint32_t	c_spare[2];
};

struct vki_urwlock {
	vki_uint32_t	rw_state;
	vki_uint32_t	rw_flags;
	vki_uint32_t	rw_blocked_readers;
	vki_uint32_t	rw_blocked_writers;
	vki_uint32_t	rw_spare[4];
};

#define	VKI_UMTX_OP_LOCK		0
#define	VKI_UMTX_OP_UNLOCK		1
#define	VKI_UMTX_OP_WAIT		2
#define	VKI_UMTX_OP_WAKE		3
#define	VKI_UMTX_OP_MUTEX_TRYLOCK	4
#define	VKI_UMTX_OP_MUTEX_LOCK		5
#define	VKI_UMTX_OP_MUTEX_UNLOCK	6
#define	VKI_UMTX_OP_SET_CEILING		7
#define	VKI_UMTX_OP_CV_WAIT		8
#define	VKI_UMTX_OP_CV_SIGNAL		9
#define	VKI_UMTX_OP_CV_BROADCAST	10
#define	VKI_UMTX_OP_WAIT_UINT		11
#define	VKI_UMTX_OP_RW_RDLOCK		12
#define	VKI_UMTX_OP_RW_WRLOCK		13
#define	VKI_UMTX_OP_RW_UNLOCK		14
#define	VKI_UMTX_OP_WAIT_UINT_PRIVATE	15
#define	VKI_UMTX_OP_WAKE_PRIVATE	16
#define	VKI_UMTX_OP_MUTEX_WAIT		17
#define	VKI_UMTX_OP_MUTEX_WAKE		18
#define	VKI_UMTX_OP_MAX			19


//----------------------------------------------------------------------
// From sys/acl.h
//----------------------------------------------------------------------

struct vki_acl_entry {
	int		ae_tag;
	vki_uid_t	ae_uid;
	vki_mode_t	ae_perm;
};

#define VKI_ACL_MAX_ENTRIES 32
struct vki_acl {
	int		acl_cnt;
	struct vki_acl_entry acl_entry[VKI_ACL_MAX_ENTRIES];
};


//----------------------------------------------------------------------
// From sys/uuid.h
//----------------------------------------------------------------------

struct vki_uuid {
	vki_uint32_t	time_low;
	vki_uint16_t	time_mid;
	vki_uint16_t	time_hi_and_version;
	vki_uint8_t	clock_seq_hi_and_reserved;
	vki_uint8_t	clock_seq_low;
	vki_uint8_t	node[6];
};

//----------------------------------------------------------------------
// From sys/user.h
//----------------------------------------------------------------------

#define VKI_KVME_TYPE_NONE          0
#define VKI_KVME_TYPE_DEFAULT       1
#define VKI_KVME_TYPE_VNODE         2
#define VKI_KVME_TYPE_SWAP          3
#define VKI_KVME_TYPE_DEVICE        4
#define VKI_KVME_TYPE_PHYS          5
#define VKI_KVME_TYPE_DEAD          6
#define VKI_KVME_TYPE_UNKNOWN       255

#define VKI_KVME_PROT_READ          0x00000001
#define VKI_KVME_PROT_WRITE         0x00000002
#define VKI_KVME_PROT_EXEC          0x00000004

#define VKI_KVME_FLAG_COW           0x00000001
#define VKI_KVME_FLAG_NEEDS_COPY    0x00000002

struct vki_kinfo_vmentry {
	int	kve_structsize;
	int	kve_type;
	ULong	kve_start;
	ULong	kve_end;
	Off64T	kve_offset;
	ULong   kve_fileid;
	UInt    kve_fsid;
	int	kve_flags;
	int	kve_resident;
	int	kve_private_resident;
	int	kve_protection;
	int	kve_ref_count;
	int	kve_shadow_count;
	int	_kve_pad0;
	int	kve_ispare[16];
	char	kve_path[VKI_PATH_MAX];
};

struct vki_kinfo_file {
        int     kf_structsize;                  /* Variable size of record. */
        int     kf_type;                        /* Descriptor type. */
        int     kf_fd;                          /* Array index. */
        int     kf_ref_count;                   /* Reference count. */
        int     kf_flags;                       /* Flags. */
        int     _kf_pad0;                       /* Round to 64 bit alignment */
        Off64T  kf_offset;                      /* Seek location. */
        int     kf_vnode_type;                  /* Vnode type. */
        int     kf_sock_domain;                 /* Socket domain. */
        int     kf_sock_type;                   /* Socket type. */
        int     kf_sock_protocol;               /* Socket protocol. */
        char    kf_sa_local[128];               /* Socket address. */
        char    kf_sa_peer[128];                /* Peer address. */
        int     _kf_ispare[16];                 /* Space for more stuff. */
        /* Truncated before copyout in sysctl */
        char    kf_path[VKI_PATH_MAX];          /* Path to file, if any. */
};

//----------------------------------------------------------------------
// From sys/kenv.h
//----------------------------------------------------------------------
#define VKI_KENV_GET		0
#define VKI_KENV_SET		1
#define VKI_KENV_UNSET		2
#define VKI_KENV_DUMP		3

//----------------------------------------------------------------------
// From sys/sysctl.h (and related)
//----------------------------------------------------------------------

#include <sys/types.h>
#include <sys/sysctl.h>

#define VKI_CTL_KERN         CTL_KERN
#define VKI_CTL_HW           CTL_HW
#define VKI_KERN_PROC        KERN_PROC
#define VKI_KERN_PROC_VMMAP  KERN_PROC_VMMAP
#define VKI_KERN_PROC_FILEDESC KERN_PROC_FILEDESC
#define VKI_HW_MACHINE       HW_MACHINE

//----------------------------------------------------------------------
// From sys/thr.h
//----------------------------------------------------------------------

struct vki_thr_param {
	void	(*start_func)(void *);
	void	*arg;
	char	*stack_base;
	vki_size_t	stack_size;
	char	*tls_base;
	vki_size_t	tls_size;
	long	*child_tid;
	long	*parent_tid;
	int	flags;
	struct vki_rtprio *rtp;
	void	*spare[3];
};

/*--------------------------------------------------------------------*/
/*--- end                                                          ---*/
/*--------------------------------------------------------------------*/
