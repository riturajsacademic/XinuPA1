#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>

#include<stdio.h>
/*decides and return the queue number in which the process should go*/
int queuedecider(int processid){
		struct	pentry	*ptr;
		ptr=&proctab[processid];
		if(66<=ptr->pprio && ptr->pprio<=99){
				return 1;
		
		} else if(33<=ptr->pprio && ptr->pprio<=65){
				return 2;
				
		
		}else if(0<=ptr->pprio && ptr->pprio<=32){
				
				return 3;
		}
		

}