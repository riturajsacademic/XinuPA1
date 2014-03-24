/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab1.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		return(SYSERR);
	}
	prio = pptr->pprio;
	//kprintf("came here with process %d",pid);
	/*here, we have to put some stuff.., */
	if(getschedclass()==2){
	ready(pid, RESCHNO);
	}else {
		ready(pid, RESCHYES);
	}
	restore(ps);
	return(prio);
}
