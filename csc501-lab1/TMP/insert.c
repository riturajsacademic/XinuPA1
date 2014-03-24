/* insert.c  -  insert */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lab1.h>

#include <stdio.h>

/*------------------------------------------------------------------------
 * insert.c  --  insert an process into a q list in key order
 *------------------------------------------------------------------------
 */
int insert(int proc, int head, int key)
{
	int	next;			/* runs through list		*/
	int	prev;

	if(getschedclass()==0 || getschedclass() == 2){
	next = q[head].qnext;
	
	while (q[next].qkey < key){	/* tail has maxint as key	*/
		next = q[next].qnext;
		
		}
	q[proc].qnext = next;
	q[proc].qprev = prev = q[next].qprev;
	q[proc].qkey  = key;
	q[prev].qnext = proc;
	q[next].qprev = proc;
	return(OK);
	}
	else if(getschedclass()==1){

	//now we are in the other function so here we will insert the process using enqueue so we can use it like a FiFo]
		
		enqueue(proc,tname(queuedecider(proc)));
		return(OK);		
	}
}
