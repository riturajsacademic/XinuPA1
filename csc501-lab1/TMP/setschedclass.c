#include<stdio.h>
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>


void setschedclass(int schedclass){

int oldalgo = getschedclass();
schedalgo = schedclass;
register struct	pentry	*ptr;	
if(oldalgo== 0 && schedalgo == 1){
//we want ot implement randionm schexuling algo from default. Now we hjave the basic queue structure and we will dequeue fthe system queue and input in our own queues
int i=0;
for(i=0;i<NPROC;i++){
	ptr = &proctab[i];
	if(ptr->pstate==PRREADY){
		if(66<=ptr->pprio && ptr->pprio<=99){
				enqueue(dequeue(i),ftail);
				//kprintf("\nputting the ptr %d with priority %d in 1",i,ptr->pprio);
		
		} else if(33<=ptr->pprio && ptr->pprio<=65){
				enqueue(dequeue(i),stail);
				//kprintf("\nputting the ptr %d with priority %d in 2",i,ptr->pprio);
		
		}else if(0<=ptr->pprio && ptr->pprio<=32){
				enqueue(dequeue(i),ttail);
				//kprintf("\nputting the ptr %d with priority %d in 3",i,ptr->pprio);
		
		}
	
	}
	//this initializes the random scheduling queue.
}
}
else if((oldalgo == 1 && schedalgo ==2)) {
int i=0;
//when we call random sched and later call linux, we should copy the stuff
for(i=0;i<NPROC;i++){
	ptr = &proctab[i];
	if(ptr->pstate==PRREADY){
		if(0<=ptr->pprio && ptr->pprio<=99){
		//I think we should enqueue this based on process priority. cause initially goodness = priority
				insert(dequeue(i),rdyhead,ptr->pprio);
				//based on the priority we are inserting the process. Also, their priority is also equal to goodness initially.
				//kprintf("\nputting the ptr %d with priority %d in ready head",i,ptr->pprio);
		
		} 
	}
	//this initializes the random scheduling queue.
}
} else if(oldalgo==2&& schedalgo==1){
int i=0;
//kprintf("\n\ttransferring from Linux to Rand\n");
for(i=0;i<NPROC;i++){
	ptr = &proctab[i];
	if(ptr->pstate==PRREADY){
		if(66<=ptr->pprio && ptr->pprio<=99){
				
				enqueue(dequeue(i),ftail);
				//kprintf("\nputting the ptr %d with priority %d in 1",i,ptr->pprio);
		
		} else if(33<=ptr->pprio && ptr->pprio<=65){
				enqueue(dequeue(i),stail);
				//kprintf("\nputting the ptr %d with priority %d in 2",i,ptr->pprio);
		
		}else if(0<=ptr->pprio && ptr->pprio<=32){
				enqueue(dequeue(i),ttail);
				//kprintf("\nputting the ptr %d with priority %d in 3",i,ptr->pprio);
		
		}
	
	}
	//this initializes the random scheduling queue.
}
} else if( oldalgo==0 && schedalgo==2){
	//direct from normal to linux scheduling.
	//for this we should copy all the process from default priority to linux like for goodness
	//here, 
}



/*Now once the sched class is set we can changfe it dynamically.*/


}