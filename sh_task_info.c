#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/pid_namespace.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <linux/file.h>

#include <linux/errno.h>

#include <uapi/asm-generic/errno-base.h>


asmlinkage long sys_sh_task_info(long pidno, char* filename)
{
	struct task_struct *proc;

	struct file *file;
	loff_t pos = 0;
	int fd;
	

	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);

	
	fd = sys_open(filename, O_WRONLY|O_CREAT,0644);

	char arr[100000];
	
	for_each_process(proc)
	{
		if((long)task_pid_nr(proc) == pidno)
		
		{
		printk(
			"Process : %s\n \
			pid_number : %ld\n \
			process state : %ld\n \
			priority : %ld\n \
			rt_priority : %ld\n \
			static priority : %ld\n \
			normal priority : %ld\n, \
			on_cpu : %ld\n, \
			sched_entity : %u\n, \
			sigset blocked : %d\n, \
			sigset real_blocked : %d\n, \
			thread_sp : %lu\n", \
   
			proc->comm, \
			(long)task_pid_nr(proc), \
			(long)proc->state, \
			(long)proc->prio, \
			(long)proc->rt_priority, \
			(long)proc->static_prio, \
			(long)proc->normal_prio, \
			(long)proc->on_cpu, \
			(unsigned int)proc->se.on_rq,\
			proc->blocked,\
			proc->real_blocked,\
			proc->thread.sp \
		);
		
		sprintf(arr,"Process : %s\n \
			pid_number : %ld\n \
			process state : %ld\n \
			priority : %ld\n \
			rt_priority : %ld\n \
			static priority : %ld\n \
			normal priority : %ld\n, \
			on_cpu : %ld\n, \
			sched_entity : %u\n, \
			sigset blocked : %d\n, \
			sigset real_blocked : %d\n, \
			thread_sp : %lu\n", \
			proc->comm, \
			(long)task_pid_nr(proc), \
			(long)proc->state, \
			(long)proc->prio, \
			(long)proc->rt_priority, \
			(long)proc->static_prio, \
			(long)proc->normal_prio, \
			(long)proc->on_cpu, \
			(unsigned int)proc->se.on_rq,\
			proc->blocked,\
			proc->real_blocked,\
			proc->thread.sp \
			);

		//Error Handling with errno
		if(fd<0){
		printk("Opening file : Failed\n");
		return -EISDIR;
		}
		//If file opens/gets created successfully
		else if(fd>=0){
		sys_write(fd,arr,strlen(arr));
		file = fget(fd);
		if(file){
		 vfs_write(file,arr,strlen(arr),&pos);
		 fput(file);
		}
		sys_close(fd);
		}
		set_fs(old_fs);		
	}
	set_fs(old_fs);
	return 0;
}

}


//(unsigned long)thread->sp, \
			//(unsigned long)thread->sp0,

//struct thread_struct *thread;














//if(proc->parent)
			//printk(
				//"Parent process :  %s, 
				//PID_Number : %ld", 
				//proc->parent->comm, 
				//(long)task_pid_nr(proc->parent) 
			//);
			//printk("\n\n");



