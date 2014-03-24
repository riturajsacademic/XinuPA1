
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <q.h>

#include <lab1.h>
int hname(int i){
switch(i){
	case 1: return fhead;
			break;
	case 2: return shead;
			break;
	case 3: return thead;
			break;
	default: return 0;
				break;
}

}
