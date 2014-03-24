#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lab1.h>
#include<sleep.h>
#include<stdio.h>
/*returns which queue is to be selected for rescheduling. 
By default returns 3, which is the least queue, if all the queues are empty.*/

int returnnextpid(){
 //returns the next queue which needs to be selected for processer scheduling.
	int flag =0,choice =0,count=0;
	int x;
	//kprintf("\nreturnnextpid()");
	srand(ctr1000);
	while(flag==0){
		
		x = rand()%100+1;
		/*finds the queue which is to be selected for next rescheduling*/
		//kprintf("\nvalue of %d",x);
	if(50<=x && x<=99){
				choice= 1;
		
		} else if(25<=x && x<=49){
				choice =  2;
				
		
		}else if(0<=x && x<=24){
				
				choice =  3;
		}
		
		
		
		/**/
		if(!isempty(hname(choice))){
			//kprintf("\nIn returnnextpid value selected %d, the queue is %d",x,choice);
			flag = 1;
		
			return choice;
		}	
		if(count==100 ){
			//kprintf("\ncount reached:");
			flag = 1;
			return 0;//put it into the last queue which is availible.
		}
		count++;
	}
	return 0;
 
 }