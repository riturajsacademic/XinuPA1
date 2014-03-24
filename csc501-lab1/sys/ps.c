#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab1.h>
#include <stdio.h>
#include <q.h>

struct info{
	int pid;
	int cticks;
};
char * processstate(int a){
switch (a){
		case 1: return "PRCURR";
				break;
		case 2: return "PRFREE";
		break;
		case 3: return "PRREADY";
		break;
		case 4: return "PRRECV";
		break;
		case 5: return "PRSLEEP";
		break;
		case 6: return "PRSUSP";
		break;
		case 7: return "PRWAIT";
		break;
		case 10: return "PRTRECV";
		break;
		default: return "null";
				break;



}

}


void ps(){
	struct info temp[NPROC];
	struct info var;
	
	struct pentry *pte; // process table entry
	char ps;
	
	int i=1;	
	int j=0;
	int k=0;
	
	
	disable(ps);
	
	for(i=0;i<NPROC;i++){
		pte = &proctab[i];
		if(pte->pstate!=PRFREE)
		{
			temp[j].pid =i;
			temp[j].cticks = pte->totalclockticks;
			j++;
		}

		}	
		//Now we sort the array:
		for(i=0;i<j-1;i++){
			for(k=1+i;k<j;k++){
				if(temp[i].cticks < temp[k].cticks){
					//exchange them
					//kprintf("\nvalue of temp click and pid to change were: %d\t%d\t%d\t%d\t",temp[i].cticks,temp[i].pid,temp[k].cticks,temp[k].pid);
					var.cticks = temp[i].cticks;
					temp[i].cticks = temp[k].cticks;
					temp[k].cticks = var.cticks;
					var.pid = temp[i].pid;
					temp[i].pid = temp[k].pid;
					temp[k].pid = var.pid;
					
				}else if(temp[i].cticks==temp[k].cticks){
					if(temp[i].pid<temp[k].pid){
						//if my cticks are the same then we exchange the process based on the pid.
						var.cticks = temp[i].cticks;
						temp[i].cticks = temp[k].cticks;
						temp[k].cticks = var.cticks;
						var.pid = temp[i].pid;
						temp[i].pid = temp[k].pid;
						temp[k].pid = var.pid;
					}
				
				}
			}
		}
		kprintf("\nPName  PID   priority   status   ticks    stacksize   queue");
		for(i=0;i<j;i++){
			k=temp[i].pid;
			pte=&proctab[k];
			kprintf("\n%s\t%d\t%d\t%s\t    %d\t\t%d\t%d",pte->pname,k,pte->pprio,processstate(pte->pstate),pte->totalclockticks,pte->pstklen,queuedecider(k),pte->goodness,pte->counter,pte->ttr);
		}
		restore(ps);
	
	}

