/* ready.c - ready */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab1.h>
#include <q.h>

/*------------------------------------------------------------------------
 * ready  --  make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
int ready(int pid, int resch)
{
	register struct	pentry	*pptr;

	if (isbadpid(pid))
		return(SYSERR);
	pptr = &proctab[pid];
	pptr->pstate = PRREADY;
	//change the insert here.
	if(getschedclass()==2){
		insert(pid,rdyhead,pptr->goodness);
		//what if I enqueue this from tail, but max is also in tail..
	
	}else{
	insert(pid,rdyhead,pptr->pprio);
	}
	if (resch)
		resched();
	return(OK);
}
