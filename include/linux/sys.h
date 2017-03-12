/*
 * Why isn't this a .c file?  Enquiring minds....
 */

#define sys_clone sys_fork

extern "C" {

extern int sys_todo();
extern int sys_setup();
extern int sys_exit();
extern int sys_fork();
extern int sys_read();
extern int sys_write();
extern int sys_open(const char *, int, int);

extern int sys_close(unsigned int);
extern int sys_waitpid();
extern int sys_creat();
extern int sys_link();
extern int sys_unlink();
// TODO WGJA WIP: extern int sys_execve();
extern int sys_chdir();
// TODO WGJA WIP: extern int sys_time();
extern int sys_mknod();
extern int sys_chmod();
extern int sys_chown();
// TODO WGJA WIP: extern int sys_break();
// TODO WGJA WIP: extern int sys_stat();
extern int sys_lseek();
extern int sys_getpid();
// TODO WGJA WIP: extern int sys_mount();
// TODO WGJA WIP: extern int sys_umount();
// TODO WGJA WIP: extern int sys_setuid();
// TODO WGJA WIP: extern int sys_getuid();
// TODO WGJA WIP: extern int sys_stime();
// TODO WGJA WIP: extern int sys_ptrace();
// TODO WGJA WIP: extern int sys_alarm();
// TODO WGJA WIP: extern int sys_fstat();
// TODO WGJA WIP: extern int sys_pause();
extern int sys_utime();
// TODO WGJA WIP: extern int sys_stty();
// TODO WGJA WIP: extern int sys_gtty();
extern int sys_access();
extern int sys_nice(long int);
// TODO WGJA WIP: extern int sys_ftime();
extern int sys_sync();
extern int sys_kill();
extern int sys_rename();
extern int sys_mkdir();
extern int sys_rmdir();
extern int sys_dup();
extern int sys_pipe();
// TODO WGJA WIP: extern int sys_times();
// TODO WGJA WIP: extern int sys_prof();
// TODO WGJA WIP: extern int sys_brk();
// TODO WGJA WIP: extern int sys_setgid();
extern int sys_getgid();
extern int sys_signal();
extern int sys_geteuid();
extern int sys_getegid();
// TODO WGJA WIP: extern int sys_acct();
// TODO WGJA WIP: extern int sys_phys();
// TODO WGJA WIP: extern int sys_lock();
// TODO WGJA WIP: extern int sys_ioctl();
// TODO WGJA WIP: extern int sys_fcntl();
// TODO WGJA WIP: extern int sys_mpx();
// TODO WGJA WIP: extern int sys_setpgid();
// TODO WGJA WIP: extern int sys_ulimit();
// TODO WGJA WIP: extern int sys_uname();
// TODO WGJA WIP: extern int sys_umask();
extern int sys_chroot();
extern int sys_ustat();
// TODO WGJA WIP: extern int sys_dup2();
extern int sys_getppid();
// TODO WGJA WIP: extern int sys_getpgrp();
// TODO WGJA WIP: extern int sys_setsid();
extern int sys_sigaction();
extern int sys_sgetmask();
extern int sys_ssetmask();
// TODO WGJA WIP: extern int sys_setreuid();
// TODO WGJA WIP: extern int sys_setregid();
extern int sys_sigpending();
extern int sys_sigsuspend();
// TODO WGJA WIP: extern int sys_sethostname();
// TODO WGJA WIP: extern int sys_setrlimit();
// TODO WGJA WIP: extern int sys_getrlimit();
extern int sys_getrusage();
// TODO WGJA WIP: extern int sys_gettimeofday();
// TODO WGJA WIP: extern int sys_settimeofday();
// TODO WGJA WIP: extern int sys_getgroups();
// TODO WGJA WIP: extern int sys_setgroups();
// TODO WGJA WIP: extern int sys_select();
extern int sys_symlink();
// TODO WGJA WIP: extern int sys_lstat();
// TODO WGJA WIP: extern int sys_readlink();
// TODO WGJA WIP: extern int sys_uselib();
// TODO WGJA WIP: extern int sys_swapon();
extern int sys_reboot();
extern int sys_readdir();
// TODO WGJA WIP: extern int sys_mmap();
// TODO WGJA WIP: extern int sys_munmap();
extern int sys_truncate();
extern int sys_ftruncate();
extern int sys_fchmod();
extern int sys_fchown();
// TODO WGJA WIP: extern int sys_getpriority();
// TODO WGJA WIP: extern int sys_setpriority();
// TODO WGJA WIP: extern int sys_profil();
extern int sys_statfs();
extern int sys_fstatfs();
extern int sys_ioperm();
// TODO WGJA WIP: extern int sys_socketcall();
// TODO WGJA WIP: extern int sys_syslog();
// TODO WGJA WIP: extern int sys_getitimer();
// TODO WGJA WIP: extern int sys_setitimer();
// TODO WGJA WIP: extern int sys_newstat();
// TODO WGJA WIP: extern int sys_newlstat();
// TODO WGJA WIP: extern int sys_newfstat();
// TODO WGJA WIP: extern int sys_newuname();
extern int sys_iopl();
extern int sys_vhangup();
extern int sys_idle();
// TODO WGJA WIP: extern int sys_vm86();
extern int sys_wait4();
// TODO WGJA WIP: extern int sys_swapoff();
// TODO WGJA WIP: extern int sys_sysinfo();
// TODO WGJA WIP: extern int sys_ipc();
extern int sys_fsync();
extern int sys_sigreturn();
// TODO WGJA WIP: extern int sys_setdomainname();
// TODO WGJA WIP: extern int sys_olduname();
// TODO WGJA WIP: extern int sys_old_syscall();
// TODO WGJA WIP: extern int sys_modify_ldt();

/*
 * These are system calls that will be removed at some time
 * due to newer versions existing..
 */
#ifdef notdef
#define sys_waitpid	sys_old_syscall	/* sys_wait4	*/
#define sys_olduname	sys_old_syscall /* sys_newuname	*/
#define sys_stat	sys_old_syscall /* sys_newstat	*/
#define sys_fstat	sys_old_syscall	/* sys_newfstat	*/
#define sys_lstat	sys_old_syscall /* sys_newlstat	*/
#define sys_signal	sys_old_syscall	/* sys_sigaction */
#endif

typedef int (*fn_ptr)();


// TODO WGJA syscalls
fn_ptr sys_call_table[] = {
  sys_setup, 			// #define __NR_setup		  0
  sys_exit, 			// #define __NR_exit		  1	Done
  sys_fork, 			// #define __NR_fork		  2	Done
  (fn_ptr) sys_read, 		// #define __NR_read		  3	Done
  (fn_ptr) sys_write, 		// #define __NR_write		  4	Done
  (fn_ptr) sys_open, 		// #define __NR_open		  5	Done
  (fn_ptr) sys_close, 		// #define __NR_close		  6	Done
  sys_waitpid, 			// #define __NR_waitpid		  7	Done
  sys_creat, 			// #define __NR_creat		  8	Done
  sys_link, 			// #define __NR_link		  9	Done
  sys_unlink, 			// #define __NR_unlink		 10	Done
  sys_todo, 			// #define __NR_execve		 11
  sys_todo, 			// #define __NR_chdir		 12
  sys_todo, 			// #define __NR_time		 13
  sys_mknod, 			// #define __NR_mknod		 14	Done
  sys_chmod, 			// #define __NR_chmod		 15	Done
  sys_chown, 			// #define __NR_chown		 16	Done
  sys_todo, 			// #define __NR_break		 17
  sys_todo, 			// #define __NR_oldstat		 18
  sys_lseek, 			// #define __NR_lseek		 19	Done
  sys_getpid, 			// #define __NR_getpid		 20	Done
  sys_todo, 			// #define __NR_mount		 21
  sys_todo, 			// #define __NR_umount		 22
  sys_todo, 			// #define __NR_setuid		 23
  sys_todo, 			// #define __NR_getuid		 24
  sys_todo, 			// #define __NR_stime		 25
  sys_todo, 			// #define __NR_ptrace		 26
  sys_todo, 			// #define __NR_alarm		 27
  sys_todo, 			// #define __NR_oldfstat	 28
  sys_todo, 			// #define __NR_pause		 29
  sys_utime, 			// #define __NR_utime		 30	Done
  sys_todo, 			// #define __NR_stty		 31
  sys_todo, 			// #define __NR_gtty		 32
  sys_access, 			// #define __NR_access		 33	Done
  (fn_ptr) sys_nice, 		// #define __NR_nice		 34	Done
  sys_todo, 			// #define __NR_ftime		 35
  sys_sync, 			// #define __NR_sync		 36	Done
  sys_kill, 			// #define __NR_kill		 37	Done
  sys_rename, 			// #define __NR_rename		 38	Done
  sys_mkdir, 			// #define __NR_mkdir		 39	Done
  sys_rmdir, 			// #define __NR_rmdir		 40	Done
  sys_dup, 			// #define __NR_dup		 41	Done
  sys_pipe, 			// #define __NR_pipe		 42	Done
  sys_todo, 			// #define __NR_times		 43
  sys_todo, 			// #define __NR_prof		 44
  sys_todo, 			// #define __NR_brk		 45
  sys_todo, 			// #define __NR_setgid		 46
  sys_getgid, 			// #define __NR_getgid		 47	Done
  sys_signal, 			// #define __NR_signal		 48	Done
  sys_geteuid, 			// #define __NR_geteuid		 49	Done
  sys_getegid, 			// #define __NR_getegid		 50	Done
  sys_todo, 			// #define __NR_acct		 51
  sys_todo, 			// #define __NR_phys		 52
  sys_todo, 			// #define __NR_lock		 53
  sys_todo, 			// #define __NR_ioctl		 54
  sys_todo, 			// #define __NR_fcntl		 55
  sys_todo, 			// #define __NR_mpx		 56
  sys_todo, 			// #define __NR_setpgid		 57
  sys_todo, 			// #define __NR_ulimit		 58
  sys_todo, 			// #define __NR_oldolduname	 59
  sys_todo, 			// #define __NR_umask		 60
  sys_chroot, 			// #define __NR_chroot		 61
  sys_ustat, 			// #define __NR_ustat		 62	Done
  sys_todo, 			// #define __NR_dup2		 63
  sys_getppid, 			// #define __NR_getppid		 64	Done
  sys_todo, 			// #define __NR_getpgrp		 65
  sys_todo, 			// #define __NR_setsid		 66
  sys_sigaction, 		// #define __NR_sigaction	 67	Done
  sys_sgetmask, 		// #define __NR_sgetmask	 68	Done
  sys_ssetmask, 		// #define __NR_ssetmask	 69	Done
  sys_todo, 			// #define __NR_setreuid	 70
  sys_todo, 			// #define __NR_setregid	 71
  sys_sigsuspend, 		// #define __NR_sigsuspend	 72	Done
  sys_sigpending, 		// #define __NR_sigpending	 73	Done
  sys_todo, 			// #define __NR_sethostname	 74
  sys_todo, 			// #define __NR_setrlimit	 75
  sys_todo, 			// #define __NR_getrlimit	 76
  sys_getrusage, 		// #define __NR_getrusage	 77	Done
  sys_todo, 			// #define __NR_gettimeofday	 78
  sys_todo, 			// #define __NR_settimeofday	 79
  sys_todo, 			// #define __NR_getgroups	 80
  sys_todo, 			// #define __NR_setgroups	 81
  sys_todo, 			// #define __NR_select		 82
  sys_symlink, 			// #define __NR_symlink		 83	Done
  sys_todo, 			// #define __NR_oldlstat	 84
  sys_todo, 			// #define __NR_readlink	 85
  sys_todo, 			// #define __NR_uselib		 86
  sys_todo, 			// #define __NR_swapon		 87
  sys_reboot, 			// #define __NR_reboot		 88	Done
  sys_readdir, 			// #define __NR_readdir		 89	Done
  sys_todo, 			// #define __NR_mmap		 90
  sys_todo, 			// #define __NR_munmap		 91
  sys_truncate, 		// #define __NR_truncate	 92	Done
  sys_ftruncate, 		// #define __NR_ftruncate	 93	Done
  sys_fchmod, 			// #define __NR_fchmod		 94	Done
  sys_fchown, 			// #define __NR_fchown		 95	Done
  sys_todo, 			// #define __NR_getpriority	 96
  sys_todo, 			// #define __NR_setpriority	 97
  sys_todo, 			// #define __NR_profil		 98
  sys_statfs, 			// #define __NR_statfs		 99	Done
  sys_fstatfs, 			// #define __NR_fstatfs		100	Done
  sys_ioperm, 			// #define __NR_ioperm		101	Done
  sys_todo, 			// #define __NR_socketcall	102
  sys_todo, 			// #define __NR_syslog		103
  sys_todo, 			// #define __NR_setitimer	104
  sys_todo, 			// #define __NR_getitimer	105
  sys_todo, 			// #define __NR_stat		106
  sys_todo, 			// #define __NR_lstat		107
  sys_todo, 			// #define __NR_fstat		108
  sys_todo, 			// #define __NR_olduname	109
  sys_iopl, 			// #define __NR_iopl		110	Done
  sys_vhangup, 			// #define __NR_vhangup		111	Done
  sys_idle, 			// #define __NR_idle		112	Done
  sys_todo, 			// #define __NR_vm86		113
  sys_wait4, 			// #define __NR_wait4		114	Done
  sys_todo, 			// #define __NR_swapoff		115
  sys_todo, 			// #define __NR_sysinfo		116
  sys_todo, 			// #define __NR_ipc		117
  sys_fsync, 			// #define __NR_fsync		118	Done
  sys_sigreturn, 		// #define __NR_sigreturn	119	Done
  sys_todo, 			// #define __NR_clone		120
  sys_todo, 			// #define __NR_setdomainname	121
  sys_todo, 			// #define __NR_uname		122
  sys_todo, 			// #define __NR_modify_ldt	123
};



// TODO WGJA WIP: fn_ptr sys_call_table[] = { sys_setup, sys_exit, sys_fork, sys_read,
// TODO WGJA WIP: sys_write, sys_open, sys_close, sys_waitpid, sys_creat, sys_link,
// TODO WGJA WIP: sys_unlink, sys_execve, sys_chdir, sys_time, sys_mknod, sys_chmod,
// TODO WGJA WIP: sys_chown, sys_break, sys_stat, sys_lseek, sys_getpid, sys_mount,
// TODO WGJA WIP: sys_umount, sys_setuid, sys_getuid, sys_stime, sys_ptrace, sys_alarm,
// TODO WGJA WIP: sys_fstat, sys_pause, sys_utime, sys_stty, sys_gtty, sys_access,
// TODO WGJA WIP: sys_nice, sys_ftime, sys_sync, sys_kill, sys_rename, sys_mkdir,
// TODO WGJA WIP: sys_rmdir, sys_dup, sys_pipe, sys_times, sys_prof, sys_brk, sys_setgid,
// TODO WGJA WIP: sys_getgid, sys_signal, sys_geteuid, sys_getegid, sys_acct, sys_phys,
// TODO WGJA WIP: sys_lock, sys_ioctl, sys_fcntl, sys_mpx, sys_setpgid, sys_ulimit,
// TODO WGJA WIP: sys_olduname, sys_umask, sys_chroot, sys_ustat, sys_dup2, sys_getppid,
// TODO WGJA WIP: sys_getpgrp, sys_setsid, sys_sigaction, sys_sgetmask, sys_ssetmask,
// TODO WGJA WIP: sys_setreuid,sys_setregid, sys_sigsuspend, sys_sigpending,
// TODO WGJA WIP: sys_sethostname, sys_setrlimit, sys_getrlimit, sys_getrusage,
// TODO WGJA WIP: sys_gettimeofday, sys_settimeofday, sys_getgroups, sys_setgroups,
// TODO WGJA WIP: sys_select, sys_symlink, sys_lstat, sys_readlink, sys_uselib,
// TODO WGJA WIP: sys_swapon, sys_reboot, sys_readdir, sys_mmap, sys_munmap, sys_truncate,
// TODO WGJA WIP: sys_ftruncate, sys_fchmod, sys_fchown, sys_getpriority, sys_setpriority,
// TODO WGJA WIP: sys_profil, sys_statfs, sys_fstatfs, sys_ioperm, sys_socketcall,
// TODO WGJA WIP: sys_syslog, sys_setitimer, sys_getitimer, sys_newstat, sys_newlstat,
// TODO WGJA WIP: sys_newfstat, sys_uname, sys_iopl, sys_vhangup, sys_idle, sys_vm86,
// TODO WGJA WIP: sys_wait4, sys_swapoff, sys_sysinfo, sys_ipc, sys_fsync, sys_sigreturn,
// TODO WGJA WIP: sys_clone, sys_setdomainname, sys_newuname, sys_modify_ldt};

}

/* So we don't have to do any more manual updating.... */
int NR_syscalls = sizeof(sys_call_table)/sizeof(fn_ptr);
