#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/tty.h>
#include <linux/user.h>

// TODO WGJA sys_socketcall 
extern "C" int sys_socketcall(void)
{
	printk("TODO: sys_socketcall\n");
	return -ENOSYS;
}

// TODO WGJA sock_fcntl
int sock_fcntl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("// TODO WGJA sock_fcntl\n");
	return(-EINVAL);
}

// TODO WGJA sock_init
void sock_init()
{
	printk("TODO WGJA sock_init\n");
}
