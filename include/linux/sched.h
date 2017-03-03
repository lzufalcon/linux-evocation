#ifndef _LINUX_SCHED_H
#define _LINUX_SCHED_H

#define NEW_SWAP

/*
 * define DEBUG if you want the wait-queues to have some extra
 * debugging code. It's not normally used, but might catch some
 * wait-queue coding errors.
 *
 *  #define DEBUG
 */

#define HZ 100

#include <linux/tasks.h>
#include <asm/system.h>

/*
 * User space process size: 3GB. This is hardcoded into a few places,
 * so don't change it unless you know what you are doing.
 */
#define TASK_SIZE	0xc0000000

/*
 * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.
 */
#define IO_BITMAP_SIZE	32

// TODO WGJA WIP: /*
// TODO WGJA WIP:  * These are the constant used to fake the fixed-point load-average
// TODO WGJA WIP:  * counting. Some notes:
// TODO WGJA WIP:  *  - 11 bit fractions expand to 22 bits by the multiplies: this gives
// TODO WGJA WIP:  *    a load-average precision of 10 bits integer + 11 bits fractional
// TODO WGJA WIP:  *  - if you want to count load-averages more often, you need more
// TODO WGJA WIP:  *    precision, or rounding will get you. With 2-second counting freq,
// TODO WGJA WIP:  *    the EXP_n values would be 1981, 2034 and 2043 if still using only
// TODO WGJA WIP:  *    11 bit fractions.
// TODO WGJA WIP:  */
// TODO WGJA WIP: extern unsigned long avenrun[];		/* Load averages */
// TODO WGJA WIP: 
// TODO WGJA WIP: #define FSHIFT		11		/* nr of bits of precision */
// TODO WGJA WIP: #define FIXED_1		(1<<FSHIFT)	/* 1.0 as fixed-point */
// TODO WGJA WIP: #define LOAD_FREQ	(5*HZ)		/* 5 sec intervals */
// TODO WGJA WIP: #define EXP_1		1884		/* 1/exp(5sec/1min) as fixed-point */
// TODO WGJA WIP: #define EXP_5		2014		/* 1/exp(5sec/5min) */
// TODO WGJA WIP: #define EXP_15		2037		/* 1/exp(5sec/15min) */
// TODO WGJA WIP: 
// TODO WGJA WIP: #define CALC_LOAD(load,exp,n) \
// TODO WGJA WIP: 	load *= exp; \
// TODO WGJA WIP: 	load += n*(FIXED_1-exp); \
// TODO WGJA WIP: 	load >>= FSHIFT;
// TODO WGJA WIP: 
// TODO WGJA WIP: #define CT_TO_SECS(x)	((x) / HZ)
// TODO WGJA WIP: #define CT_TO_USECS(x)	(((x) % HZ) * 1000000/HZ)

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#include <linux/head.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/signal.h>
#include <linux/time.h>
#include <linux/param.h>
#include <linux/resource.h>
#include <linux/vm86.h>
#include <linux/math_emu.h>

#define TASK_RUNNING		0
#define TASK_INTERRUPTIBLE	1
#define TASK_UNINTERRUPTIBLE	2
#define TASK_ZOMBIE		3
#define TASK_STOPPED		4
#define TASK_SWAPPING		5

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifdef __KERNEL__

extern void sched_init(void);
// TODO WGJA WIP: extern void show_state(void);
extern void trap_init(void);
// TODO WGJA WIP: extern void panic(const char * str);

extern "C" void schedule(void);

#endif /* __KERNEL__ */

struct i387_hard_struct {
	long	cwd;
	long	swd;
	long	twd;
	long	fip;
	long	fcs;
	long	foo;
	long	fos;
	long	st_space[20];	/* 8*10 bytes for each FP-reg = 80 bytes */
};

struct i387_soft_struct {
	long	cwd;
	long	swd;
	long	twd;
	long	fip;
	long	fcs;
	long	foo;
	long	fos;
	long    top;
	struct fpu_reg	regs[8];	/* 8*16 bytes for each FP-reg = 128 bytes */
	unsigned char	lookahead;
	struct info	*info;
	unsigned long	entry_eip;
};

union i387_union {
	struct i387_hard_struct hard;
	struct i387_soft_struct soft;
};

struct tss_struct {
	unsigned short	back_link,__blh;
	unsigned long	esp0;
	unsigned short	ss0,__ss0h;
	unsigned long	esp1;
	unsigned short	ss1,__ss1h;
	unsigned long	esp2;
	unsigned short	ss2,__ss2h;
	unsigned long	cr3;
	unsigned long	eip;
	unsigned long	eflags;
	unsigned long	eax,ecx,edx,ebx;
	unsigned long	esp;
	unsigned long	ebp;
	unsigned long	esi;
	unsigned long	edi;
	unsigned short	es, __esh;
	unsigned short	cs, __csh;
	unsigned short	ss, __ssh;
	unsigned short	ds, __dsh;
	unsigned short	fs, __fsh;
	unsigned short	gs, __gsh;
	unsigned short	ldt, __ldth;
	unsigned short	trace, bitmap;
	unsigned long	io_bitmap[IO_BITMAP_SIZE+1];
	unsigned long	tr;
	union i387_union i387;
};

struct task_struct {
/* these are hardcoded - don't touch */
	long state;		/* -1 unrunnable, 0 runnable, >0 stopped */
	long counter;
	long priority;
	unsigned long signal;
	unsigned long blocked;	/* bitmap of masked signals */
	unsigned long flags;	/* per process flags, defined below */
	int errno;
/* various fields */
	struct task_struct *next_task, *prev_task;
	struct sigaction sigaction[32];
	unsigned long saved_kernel_stack;
	unsigned long kernel_stack_page;
	int exit_code, exit_signal;
	int elf_executable:1;
	int dumpable:1;
	int swappable:1;
	unsigned long start_code,end_code,end_data,start_brk,brk,start_stack,start_mmap;
	unsigned long arg_start, arg_end, env_start, env_end;
	long pid,pgrp,session,leader;
	int	groups[NGROUPS];
	/* 
	 * pointers to (original) parent process, youngest child, younger sibling,
	 * older sibling, respectively.  (p->father can be replaced with 
	 * p->p_pptr->pid)
	 */
	struct task_struct *p_opptr,*p_pptr, *p_cptr, *p_ysptr, *p_osptr;
	struct wait_queue *wait_chldexit;	/* for wait4() */
	/*
	 * For ease of programming... Normal sleeps don't need to
	 * keep track of a wait-queue: every task has an entry of it's own
	 */
	unsigned short uid,euid,suid;
	unsigned short gid,egid,sgid;
	unsigned long timeout;
	unsigned long it_real_value, it_prof_value, it_virt_value;
	unsigned long it_real_incr, it_prof_incr, it_virt_incr;
	long utime,stime,cutime,cstime,start_time;
	unsigned long min_flt, maj_flt;
	unsigned long cmin_flt, cmaj_flt;
	struct rlimit rlim[RLIM_NLIMITS]; 
	unsigned short used_math;
	unsigned short rss;	/* number of resident pages */
	char comm[16];
	struct vm86_struct * vm86_info;
	unsigned long screen_bitmap;
/* file system info */
	int link_count;
	int tty;		/* -1 if no tty, so it must be signed */
	unsigned short umask;
	struct inode * pwd;
	struct inode * root;
	struct inode * executable;
	struct vm_area_struct * mmap;
	struct shm_desc *shm;
	struct sem_undo *semun;
	struct file * filp[NR_OPEN];
	fd_set close_on_exec;
/* ldt for this task - used by Wine.  If NULL, default_ldt is used */
	struct desc_struct *ldt;
/* tss for this task */
	struct tss_struct tss;
#ifdef NEW_SWAP
	unsigned long old_maj_flt;	/* old value of maj_flt */
	unsigned long dec_flt;		/* page fault count of the last time */
	unsigned long swap_cnt;		/* number of pages to swap on next pass */
	short swap_table;		/* current page table */
	short swap_page;		/* current page */
#endif NEW_SWAP
};

/*
 * Per process flags
 */
#define PF_ALIGNWARN	0x00000001	/* Print alignment warning msgs */
					/* Not implemented yet, only for 486*/
#define PF_PTRACED	0x00000010	/* set if ptrace (0) has been called. */
#define PF_TRACESYS	0x00000020	/* tracing system calls */

/*
 * cloning flags:
 */
#define CSIGNAL		0x000000ff	/* signal mask to be sent at exit */
#define COPYVM		0x00000100	/* set if VM copy desired (like normal fork()) */
#define COPYFD		0x00000200	/* set if fd's should be copied, not shared (NI) */

/*
 *  INIT_TASK is used to set up the first task table, touch at
 * your own risk!. Base=0, limit=0x1fffff (=2MB)
 */
#define INIT_TASK \
/* state etc */	{ 0,15,15,0,0,0,0, \
/* schedlink */	&init_task,&init_task, \
/* signals */	{{ 0, },}, \
/* stack */	0,0, \
/* ec,brk... */	0,0,0,0,0,0,0,0,0,0,0,0, \
/* argv.. */	0,0,0,0, \
/* pid etc.. */	0,0,0,0, \
/* suppl grps*/ {NOGROUP,}, \
/* proc links*/ &init_task,&init_task,(task_struct*) NULL,(task_struct*) NULL,(task_struct*) NULL,(wait_queue*) NULL, \
/* uid etc */	0,0,0,0,0,0, \
/* timeout */	0,0,0,0,0,0,0,0,0,0,0,0, \
/* min_flt */	0,0,0,0, \
/* rlimits */   { {LONG_MAX, LONG_MAX}, {LONG_MAX, LONG_MAX},  \
		  {LONG_MAX, LONG_MAX}, {LONG_MAX, LONG_MAX},  \
		  {LONG_MAX, LONG_MAX}, {LONG_MAX, LONG_MAX}}, \
/* math */	0, \
/* rss */	2, \
/* comm */	"swapper", \
/* vm86_info */	(vm86_struct*)NULL, 0, \
/* fs info */	0,-1,0022,(inode*)NULL,(inode*)NULL,(inode*)NULL,(vm_area_struct*)NULL, \
/* ipc */	(shm_desc*) NULL, (sem_undo*) NULL, \
/* filp */	{(file *) NULL,}, \
/* cloe */	{{ 0, }}, \
/* ldt */	(desc_struct*) NULL, \
/*tss*/	{0,0, \
	 sizeof(init_kernel_stack) + (long) &init_kernel_stack, KERNEL_DS, 0, \
	 0,0,0,0,0,0, \
	 (long) &swapper_pg_dir, \
	 0,0,0,0,0,0,0,0,0,0, \
	 USER_DS,0,USER_DS,0,USER_DS,0,USER_DS,0,USER_DS,0,USER_DS,0, \
	 _LDT(0),0, \
	 0, 0x8000, \
/* ioperm */ 	{~0, }, \
	 _TSS(0), \
/* 387 state */	{ { 0, }, } \
	} \
}

extern struct task_struct init_task;
extern struct task_struct *task[NR_TASKS];
extern struct task_struct *last_task_used_math;
extern struct task_struct *current;
extern unsigned long volatile jiffies;
extern unsigned long startup_time;
extern int jiffies_offset;
extern int need_resched;

extern int hard_math;
extern int x86;
extern int ignore_irq13;
extern int wp_works_ok;

#define CURRENT_TIME (startup_time+(jiffies+jiffies_offset)/HZ)

extern void sleep_on(struct wait_queue ** p);
extern void interruptible_sleep_on(struct wait_queue ** p);
extern void wake_up(struct wait_queue ** p);
extern void wake_up_interruptible(struct wait_queue ** p);

// TODO WGJA WIP: extern void notify_parent(struct task_struct * tsk);
extern int send_sig(unsigned long sig,struct task_struct * p,int priv);
extern int in_group_p(gid_t grp);

extern int request_irq(unsigned int irq,void (*handler)(int));
extern void free_irq(unsigned int irq);
extern int irqaction(unsigned int irq,struct sigaction * sa);

/*
 * Entry into gdt where to find first TSS. GDT layout:
 *   0 - nul
 *   1 - kernel code segment
 *   2 - kernel data segment
 *   3 - user code segment
 *   4 - user data segment
 * ...
 *   8 - TSS #0
 *   9 - LDT #0
 *  10 - TSS #1
 *  11 - LDT #1
 */
#define FIRST_TSS_ENTRY 8
#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
#define _TSS(n) ((((unsigned long) n)<<4)+(FIRST_TSS_ENTRY<<3))
#define _LDT(n) ((((unsigned long) n)<<4)+(FIRST_LDT_ENTRY<<3))
#define load_TR(n) __asm__("ltr %%ax": /* no output */ :"a" (_TSS(n)))
#define load_ldt(n) __asm__("lldt %%ax": /* no output */ :"a" (_LDT(n)))
#define store_TR(n) \
__asm__("str %%ax\n\t" \
	"subl %2,%%eax\n\t" \
	"shrl $4,%%eax" \
	:"=a" (n) \
	:"0" (0),"i" (FIRST_TSS_ENTRY<<3))
/*
 *	switch_to(n) should switch tasks to task nr n, first
 * checking that n isn't the current task, in which case it does nothing.
 * This also clears the TS-flag if the task we switched to has used
 * tha math co-processor latest.
 */
#define switch_to(tsk) \
__asm__( \
	"cmpl %%ecx,current\n\t" \
	"je 1f\n\t" \
	"cli\n\t" \
	"xchgl %%ecx,current\n\t" \
	"ljmp 0(%%ebx)\n\t" \
	"sti\n\t" \
	"cmpl %%ecx,last_task_used_math\n\t" \
	"jne 1f\n\t" \
	"clts\n" \
	"1:" \
	: /* no output */ \
	:"c" (tsk), \
	 "b" (((char *)&tsk->tss.tr)-4) \
	:)

// TODO WGJA WIP: #define _set_base(addr,base) \
// TODO WGJA WIP: __asm__("movw %%dx,%0\n\t" \
// TODO WGJA WIP: 	"rorl $16,%%edx\n\t" \
// TODO WGJA WIP: 	"movb %%dl,%1\n\t" \
// TODO WGJA WIP: 	"movb %%dh,%2" \
// TODO WGJA WIP: 	: /* no output */ \
// TODO WGJA WIP: 	:"m" (*((addr)+2)), \
// TODO WGJA WIP: 	 "m" (*((addr)+4)), \
// TODO WGJA WIP: 	 "m" (*((addr)+7)), \
// TODO WGJA WIP: 	 "d" (base) \
// TODO WGJA WIP: 	:"dx")
// TODO WGJA WIP: 
// TODO WGJA WIP: #define _set_limit(addr,limit) \
// TODO WGJA WIP: __asm__("movw %%dx,%0\n\t" \
// TODO WGJA WIP: 	"rorl $16,%%edx\n\t" \
// TODO WGJA WIP: 	"movb %1,%%dh\n\t" \
// TODO WGJA WIP: 	"andb $0xf0,%%dh\n\t" \
// TODO WGJA WIP: 	"orb %%dh,%%dl\n\t" \
// TODO WGJA WIP: 	"movb %%dl,%1" \
// TODO WGJA WIP: 	: /* no output */ \
// TODO WGJA WIP: 	:"m" (*(addr)), \
// TODO WGJA WIP: 	 "m" (*((addr)+6)), \
// TODO WGJA WIP: 	 "d" (limit) \
// TODO WGJA WIP: 	:"dx")
// TODO WGJA WIP: 
// TODO WGJA WIP: #define set_base(ldt,base) _set_base( ((char *)&(ldt)) , base )
// TODO WGJA WIP: #define set_limit(ldt,limit) _set_limit( ((char *)&(ldt)) , (limit-1)>>12 )

/*
 * The wait-queues are circular lists, and you have to be *very* sure
 * to keep them correct. Use only these two functions to add/remove
 * entries in the queues.
 */
extern inline void add_wait_queue(struct wait_queue ** p, struct wait_queue * wait)
{
	unsigned long flags;

#ifdef DEBUG
	if (wait->next) {
		unsigned long pc;
		__asm__ __volatile__("call 1f\n"
			"1:\tpopl %0":"=r" (pc));
		printk("add_wait_queue (%08x): wait->next = %08x\n",pc,wait->next);
	}
#endif
	save_flags(flags);
	cli();
	if (!*p) {
		wait->next = wait;
		*p = wait;
	} else {
		wait->next = (*p)->next;
		(*p)->next = wait;
	}
	restore_flags(flags);
}

extern inline void remove_wait_queue(struct wait_queue ** p, struct wait_queue * wait)
{
	unsigned long flags;
	struct wait_queue * tmp;
#ifdef DEBUG
	unsigned long ok = 0;
#endif

	save_flags(flags);
	cli();
	if ((*p == wait) &&
#ifdef DEBUG
	    (ok = 1) &&
#endif
	    ((*p = wait->next) == wait)) {
		*p = (wait_queue *)NULL;
	} else {
		tmp = wait;
		while (tmp->next != wait) {
			tmp = tmp->next;
#ifdef DEBUG
			if (tmp == *p)
				ok = 1;
#endif
		}
		tmp->next = wait->next;
	}
	wait->next = (wait_queue *)NULL;
	restore_flags(flags);
#ifdef DEBUG
	if (!ok) {
		printk("removed wait_queue not on list.\n");
		printk("list = %08x, queue = %08x\n",p,wait);
		__asm__("call 1f\n1:\tpopl %0":"=r" (ok));
		printk("eip = %08x\n",ok);
	}
#endif
}

extern inline void select_wait(struct wait_queue ** wait_address, select_table * p)
{
	struct select_table_entry * entry;

	if (!p || !wait_address)
		return;
	if (p->nr >= __MAX_SELECT_TABLE_ENTRIES)
		return;
 	entry = p->entry + p->nr;
	entry->wait_address = wait_address;
	entry->wait.task = current;
	entry->wait.next = (wait_queue *)NULL;
	add_wait_queue(wait_address,&entry->wait);
	p->nr++;
}

// TODO WGJA WIP: static inline unsigned long _get_base(char * addr)
// TODO WGJA WIP: {
// TODO WGJA WIP: 	unsigned long __base;
// TODO WGJA WIP: 	__asm__("movb %3,%%dh\n\t"
// TODO WGJA WIP: 		"movb %2,%%dl\n\t"
// TODO WGJA WIP: 		"shll $16,%%edx\n\t"
// TODO WGJA WIP: 		"movw %1,%%dx"
// TODO WGJA WIP: 		:"=&d" (__base)
// TODO WGJA WIP: 		:"m" (*((addr)+2)),
// TODO WGJA WIP: 		 "m" (*((addr)+4)),
// TODO WGJA WIP: 		 "m" (*((addr)+7)));
// TODO WGJA WIP: 	return __base;
// TODO WGJA WIP: }
// TODO WGJA WIP: 
// TODO WGJA WIP: #define get_base(ldt) _get_base( ((char *)&(ldt)) )
// TODO WGJA WIP: 
// TODO WGJA WIP: static inline unsigned long get_limit(unsigned long segment)
// TODO WGJA WIP: {
// TODO WGJA WIP: 	unsigned long __limit;
// TODO WGJA WIP: 	__asm__("lsll %1,%0"
// TODO WGJA WIP: 		:"=r" (__limit):"r" (segment));
// TODO WGJA WIP: 	return __limit+1;
// TODO WGJA WIP: }

#define REMOVE_LINKS(p) do { unsigned long flags; \
	save_flags(flags) ; cli(); \
	(p)->next_task->prev_task = (p)->prev_task; \
	(p)->prev_task->next_task = (p)->next_task; \
	restore_flags(flags); \
	if ((p)->p_osptr) \
		(p)->p_osptr->p_ysptr = (p)->p_ysptr; \
	if ((p)->p_ysptr) \
		(p)->p_ysptr->p_osptr = (p)->p_osptr; \
	else \
		(p)->p_pptr->p_cptr = (p)->p_osptr; \
	} while (0)

#define SET_LINKS(p) do { unsigned long flags; \
	save_flags(flags); cli(); \
	(p)->next_task = &init_task; \
	(p)->prev_task = init_task.prev_task; \
	init_task.prev_task->next_task = (p); \
	init_task.prev_task = (p); \
	restore_flags(flags); \
	(p)->p_ysptr = (task_struct*) NULL; \
	if (((p)->p_osptr = (p)->p_pptr->p_cptr) != NULL) \
		(p)->p_osptr->p_ysptr = p; \
	(p)->p_pptr->p_cptr = p; \
	} while (0)

#define for_each_task(p) \
	for (p = &init_task ; (p = p->next_task) != &init_task ; )

/*
 * This is the ldt that every process will get unless we need
 * something other than this.
 */
extern struct desc_struct default_ldt;

#endif
