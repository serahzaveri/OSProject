/*
PCB has 3 fields
PC : Points to the the current line reached for that program
start: Points to first line of that program
end: Points to last line of that program
*/
#ifndef PCB_H
#define PCB_H

typedef struct PCB
{
    int PC;
    //int start;
    //int end;
    int PC_page;
    int PC_offset;
    int pages_max;
    int pagetable[10];
}PCB;

//The index of the array is the page number. The values stored in the cell is the frame number. 


/*
Passes 2 parameters (start , end)
This method creates a PCB with fields set as this:
PC = start
start = start
end = end
*/
PCB* makePCB(int pages_max);

#endif
