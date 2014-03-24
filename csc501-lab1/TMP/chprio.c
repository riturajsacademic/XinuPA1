/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include<lab1.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return(SYSERR);
	}
	pptr->pprio = newprio;
	if(getschedclass()==1){

	//now we are in the other function so here we will insert the process using enqueue so we can use it like a FiFo]
		if(pptr->pstate==PRREADY){
		enqueue(dequeue(pid),tname(queuedecider(pid)));
		}
	
	}
	if(getschedclass()==2){
		//I should come here when we call chprio.
		//no need to work on chprio.., as when the priority changes, then it should change in next epoch.
		
	
	}
	//I think here I should think of calculating of where to put this process. 
	restore(ps);
	return(newprio);
}
