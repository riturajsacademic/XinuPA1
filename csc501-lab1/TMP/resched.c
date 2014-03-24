/* resched.c  -  resched */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lab1.h>

#include <stdio.h>

unsigned long currSP;	/* REAL sp of current process */
extern int ctxsw(int, int, int, int);
/*-----------------------------------------------------------------------
 * resched  --  reschedule processor to highest priority ready process
 *
 * Notes:	Upon entry, currpid gives current process id.
 *		Proctab[currpid].pstate gives correct NEXT state for
 *			current process if other than PRREADY.
 *------------------------------------------------------------------------
 */
 
 
 
int resched()
{
	register struct	pentry	*optr;	/* pointer to old process entry */
	register struct	pentry	*nptr;	/* pointer to new process entry */
	int choice;
	
	struct pentry *tempptr;
	
	
	int oldpid=0;	//represents the choice of queue to be selected from which to schedule
	if(getschedclass()==0){
	//kprintf("\n with scheduler 0");
	/* no switch needed if current process priority higher than next*/
	/*now I have 3 queue stacks and I have to handle all 3 of them based on the priority of process that I get. Plus that too based on the variable of sheduling*/
	if ( ( (optr= &proctab[currpid])->pstate == PRCURR) &&
	   (lastkey(rdytail)<optr->pprio)) {
	   optr->totalclockticks = optr->totalclockticks + 1;
		return(OK);
	}
	
	/* force context switch */

	if (optr->pstate == PRCURR) {
		optr->pstate = PRREADY;
		optr->totalclockticks = QUANTUM - preempt + optr->totalclockticks;
		insert(currpid,rdyhead,optr->pprio);
		//kprintf("\nInserted %d",oldpid);
	}

	/* remove highest priority process at end of ready list */

	nptr = &proctab[ (currpid = getlast(rdytail)) ];
	nptr->pstate = PRCURR;		/* mark it currently running	*/
	
#ifdef	RTCLOCK
	preempt = QUANTUM;		/* reset preemption counter	*/
#endif
	
	ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
	/* The OLD process returns here when resumed. */
	return OK;
	}else if(getschedclass()==1){
			//kprintf("\n with scheduler 1");

			
			//get a random number, and reschedule, not like last one.
				choice = returnnextpid();
				//kprintf("\nIn queue chosen is: %d",choice);

			/*choice has the queue which is to be used to 
			we will check if count is 100 and then return 0;*/
			
			//it never goes inside here is it?, even thoguh the queues are empty.., this should be specially for null process is it?
			optr= &proctab[currpid];
			if(currpid==0 && choice==0){
					optr->totalclockticks = optr->totalclockticks + 1;
					//kprintf("\nFirst solution, we are continuing and waiting for 1sec more");
					return(OK);
			}
			oldpid = currpid;
			// To think about the ratio.
			currpid = getfirst(hname(choice));
			/*The current process which is  executing should not switch if tyhe currpid is 0*/
			/*Changing here Attention*/
					
			
			if (optr->pstate == PRCURR) {
				//kprintf("\nsecond solution, we are rescheduling the process");

				optr->pstate = PRREADY;
				optr->totalclockticks = QUANTUM - preempt + optr->totalclockticks;
				insert(oldpid,rdyhead,optr->pprio);//does not matters what we pass here as rdyhead, as we will take care of this in insert.c
				//kprintf("\nInserted %d",oldpid);
			}
			
			//kprintf("\nCurrent process chosen: %d",currpid);
			nptr = &proctab[currpid];
			nptr->pstate = PRCURR;		/* mark it currently running	*/
	
			#ifdef	RTCLOCK
				preempt = QUANTUM;		/* reset preemption counter	*/
			#endif
	
			ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
			/* The OLD process returns here when resumed. */
			return OK;
			
			
			
	}
	else if(getschedclass()==2){
		
		/*this is called when rescheduling the process. */
		int nresched = EPOCHSET;
		//used for checking if new epoch has started or not.
		int i=0;
		int processID = 0;
		for(i=0;i<NPROC;i++){
			optr = &proctab[i];
			if(optr->pstate == PRREADY){
				if(optr->flag == FLAGSET){ // if any process with flag set, then we do not resc
					nresched = EPOCHNOT; 
					//if there is any process with flag as 1 and with max goodness
					if((tempptr = &proctab[processID])->goodness <= optr->goodness){
							processID = i;
					//let us check break
					}
				}
			}
		}
		
		if(nresched==EPOCHNOT){
			if(tempptr->pstate==PRSLEEP){
		//kprintf("\ncalled by sleeping process in 1");
	}
		//if it comes here then we schedule new process and do not start a new epoch.
		//what if the Quantum of process has not completed and 
			int oldpid = currpid;
			//if the current processes goodness is 0 then that implies that all other process also had goodness as 0.
			tempptr = &proctab[processID];
			if(tempptr->goodness != 0) {
/*one*/		currpid = dequeue(processID);//check this. VV IMP.
				//kprintf("\nRunning %d from",currpid);
			}else if(tempptr->goodness==0){
				//we take the the stuff fifo.
				currpid = getlast(rdytail);
				//kprintf("\nRunning %d",currpid);
			}
			
			/*I think rather than taking the process out, lets check the process */
					
			/**/
			//kprintf("\nScheduling new process");
			//calculating the goodness, time and other things for process.
			optr = &proctab[oldpid];
			optr->totalclockticks =  optr->ttr - preempt + optr->totalclockticks; // gives me the total number of clock ticks the process has executed of the given time to execute.
			//you should keep it in PRREADY.
			//we should have a current clock tick.
			if(optr->pstate==PRCURR){
			optr->clocktick = optr->ttr - preempt + optr->clocktick;
			optr->pstate = PRREADY;
			//kprintf("\n\nExcuted time %d process is %d", oldpid,optr->totalclockticks);
			if(optr->clocktick >= optr->ttr){
				//kprintf("\n\nProcess %d has completed its quantum.",oldpid);
				//kprintf("Y: %d  %d",oldpid,currpid);
				optr->goodness = 0;
				optr->flag = FLAGNOT;
				optr->exhaust = EXHAUSTSET; // setting this tells that the process has exhausted its epoch.
				insert(oldpid,rdyhead,optr->goodness);
				
				//kprintf("\nInserted %d",oldpid);
				//we have put the new process in queue again with no goodness and this will not be executed till next epoch/
	
			}else if(optr->clocktick < optr->ttr)
			{
				//calculate the new ptr of this process.
				optr->counter = optr->ttr - optr->clocktick;
				optr->ttr = optr->counter;
				insert(oldpid,rdyhead,optr->goodness);
				//issue is when process comes here which will end..
				//kprintf("\nInserted %d",oldpid);
				//kprintf("\n\nNew time for %d process is %d", oldpid,optr->ttr);
				
			}	
			}
			
				nptr = &proctab[currpid];
				nptr->pstate = PRCURR;
				//kprintf("\n\nNew process selected is %d , with goodness %d, with epoch %d EPOCHNOT\n",currpid, nptr->goodness, nptr->ttr);
			#ifdef	RTCLOCK
				preempt = nptr->ttr;		/* reset preemption counter	*/
			#endif
	
			ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
			/* The OLD process returns here when resumed. */
			return OK;
	
		} else if(nresched == EPOCHSET){
		if(tempptr->pstate==PRSLEEP){
		//kprintf("\ncalled by sleeping process 2");
	}
		//kprintf("\n");
		//kprintf("\nCalculating new epoch here");
			//start new epoch as no processes are there to execute.
			int i=0;
			//currently executing process, what to do with that.., if there is no currently executing process
			//what to do with that...!!
			//either lets insert it into queue and then lets take out a process with most goodness from queue.
		
			for(i=0;i<NPROC;i++){
				optr = &proctab[i];
				
				if(optr->pstate == PRREADY)
				{	
					
					if(optr->exhaust == EXHAUSTSET){
						//the process had exhausted its last quantum.
						optr->goodness = 0;
						optr->ttr = optr->pprio;
						optr->clocktick = 0;
						optr->exhaust = EXHAUSTNOT;	//taking exhaust flag off, making this process runnable in next epoch cycle
									//this should run	
						//kprintf("1");
						
					}
					else if(optr->exhaust == EXHAUSTNOT && optr->counter > 0){
						optr->goodness = optr->counter + optr->pprio; //if last process did not exhaust its quantum.
						optr->clocktick = 0;
						optr->ttr = (optr->counter/2) + optr->pprio;
						//kprintf("2");
						
				}	else if(optr->exhaust == EXHAUSTNOT && optr->flag==FLAGNOT){
						//if the process has not exhausted and its flag is not set, meaning that process came in between of last epoch and 
						//should be made to run now.
						//for any new process.
						optr->goodness = optr->pprio;
						optr->clocktick = 0;
						optr->ttr = optr->pprio;
						//kprintf("3");
						
				
				}
				optr->flag=FLAGSET;
				//reschedule every ready processes flag to 1, so they run.
				//now once we have refreshed all the process in the process table, we refresh the queue.
				
			} else if(optr->pstate==PRCURR)
			{// For the currently running process, what do we do, we make its goodness and other values equal to its priority and reschedule it again.
					optr->goodness = optr->pprio;
					optr->ttr = optr->pprio;
					//optr->clocktick = 0;
					optr->flag=FLAGSET;
					//kprintf("\nRecalculated mains goodness %d", optr->goodness);
					//here, we have set all the things for main process to run or whichever is the current process.
			}
			// I think I should do context switching here, most imp...
			
			
		}
		//kprintf("\n\nall processes have been recalculated for goodness");
		for(i=0;i<NPROC;i++){
					optr = &proctab[i];
					if(optr->pstate == PRREADY){
						//insert only if goodness has changed, or keep it as it is.
						if(optr->goodness!=0){
						insert(dequeue(i),rdyhead,optr->goodness);
						}
						//kprintf("\nInserted %d",i);
						//here, we have again made the queue nice.
						//kprintf("\ninserted process %d",i);
					}
				}
		/*I think I should reschedule somehow, cause system has not process to run
		I can try to call resched again, cause now I have set the stuff and it should go in the last loop.*/
		/*putting the current process which is executing in queue and taking the goodness process in*/
		//kprintf("old pid is %d",currpid);
		int oldpid = currpid;
		optr = &proctab[oldpid];
		if(optr->pstate==PRCURR){
		optr->pstate = PRREADY;
		insert(oldpid,rdyhead,optr->goodness);
		}
		//kprintf("\nInserted %d",oldpid);
		currpid = getlast(rdytail);
		nptr = &proctab[currpid];
		nptr->pstate = PRCURR;
		//kprintf("\n\nNew process selected is %d , with goodness %d, with epoch %d EPOCHSET\n",currpid, nptr->goodness, nptr->ttr);
			#ifdef	RTCLOCK
				preempt = nptr->ttr;		/* reset preemption counter	*/
			#endif
	
			ctxsw((int)&optr->pesp, (int)optr->pirmask, (int)&nptr->pesp, (int)nptr->pirmask);
			/* The OLD process returns here when resumed. */
		
		
		return OK;
	}
}
}
