#include <stdio.h>
#include <stdlib.h>
/*
PCB has 3 fields
PC : Points to the the current line reached for that program
start: Points to first line of that program
end: Points to last line of that program
*/

//typedef struct PCB PCB;

typedef struct PCB
{
    int PC;
    int start;
    int end; 
    int PC_page;
    int PC_offset;
    int pages_max;
}PCB;


/*
Passes 2 parameters (start , end)
This method creates a PCB with fields set as this:
PC = start
start = start
end = end
*/
PCB* makePCB(int start, int end, int pages_max, int PC_page, int PC_offset){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->PC = start;
    pcb->start = start;
    pcb->end = end;
    pcb->pages_max = pages_max;
    pcb->PC_offset = PC_offset;
    pcb->PC_page = PC_page;
    return pcb;
}


