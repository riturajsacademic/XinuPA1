
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <q.h>

#include <lab1.h>

int tname(int i){
switch(i){
	case 1: return ftail;
			break;
	case 2: return stail;
			break;
	case 3: return ttail;
			break;
	default: return 0;
				break;
}

}