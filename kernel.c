#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include"shell.h"
#include"pcb.h"
#include"ram.h"
#include"cpu.h"
#include"interpreter.h"
#include"memorymanager.h"

/*
This is a node in the Ready Queue implemented as 
a linked list.
A node holds a PCB pointer and a pointer to the next node.
PCB: PCB
next: next node
*/
typedef struct ReadyQueueNode {
    PCB*  PCB;
    struct ReadyQueueNode* next;
} ReadyQueueNode;



ReadyQueueNode* head = NULL;
ReadyQueueNode* tail = NULL;
int sizeOfQueue = 0;

int kernel(){
    int err = shellUI();
    return err;
}

void boot(){
    //INITIALIZE AND ACQUIRE RESOURCES TO RUN
    //1: Handle's RAM
    removeFromRam(0, 39);
    resetRAM();
    //2: Prepare's the backing store
    char buffer[100];
    //we first get the current diretory 
    GetCurrentDirectory(100, buffer);
    //we then concat backing store to the current directory
    char add[] = "//BackingStore";
    strcat(buffer, add);
    printf("%s\n", buffer);
    //we now delete if that directory exists
    //NOTE: IT ONLT GETS DELETED IF THE DIRECTORY IS EMPTY
    BOOL deleted = RemoveDirectory(buffer);
    if(deleted){
        printf("Directory deleted successfully\n");
    }
    if(!deleted){
        printf("Directory not found to delete\n");
    }
    //we now create the directory
    BOOL bdir = CreateDirectory(buffer, NULL);
    
    if(!bdir) {
        printf("Unable to create directory\n");
    }
    else{
        printf("Directory created successfully\n");
    }
    
}

int main(int argc, char const *argv[])
{
    int error = 0;
    boot(); //First: actions performed by boot
    error = kernel(); //Second: actions performed by kernel
    return error;
}
/*
Adds a pcb to the tail of the linked list
*/
void addToReady(struct PCB* pcb) {
    ReadyQueueNode* newNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
    newNode->PCB = pcb;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    sizeOfQueue++;
}

/*
Returns the size of the queue
*/
int size(){
    return sizeOfQueue;
}

/*
Pops the pcb at the head of the linked list.
pop will cause an error if linkedlist is empty.
Always check size of queue using size()
*/
struct PCB* pop(){
    PCB* topNode = head->PCB;
    ReadyQueueNode * temp = head;
    if (head == tail){
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
    }
    free(temp);
    sizeOfQueue--;
    return topNode;
}

/*
Passes a filename
Opens the file, copies the content in the RAM.
Creates a PCB for that program.
Adds the PCB on the ready queue.
Return an errorCode:
ERRORCODE 0 : NO ERROR
ERRORCODE -3 : SCRIPT NOT FOUND
ERRORCODE -5 : NOT ENOUGH RAM (EXEC)
*/
int myinit(char* filename){
    /*
    // Open the filename to get FILE *
    // call addToRam on that File *
    // If error (check via start/end variable), return that error
    // Else create pcb using MakePCB
    // Then add it to the ReadyQueue
    FILE * fp = fopen(filename,"r");
    if (fp == NULL) return -3;
    int start;
    int end;
    addToRAM(fp,&start,&end);
    fclose(fp);
    if (start == -1) return -5;
    PCB* pcb = makePCB(start,end);
    addToReady(pcb); */ 
    return 0;
}

int myinit2(char* filename){
    // Open the filename to get FILE *
    // call addToRam on that File *
    // If error (check via start/end variable), return that error
    // Else create pcb using MakePCB
    // Then add it to the ReadyQueue
    FILE * fp = fopen(filename,"r");
    if (fp == NULL) return -3;
    int start;
    int end;
    //printf("File opened\n");
    //addToRAM(fp,&start,&end);
    // WE CALL LAUNCHER HERE
    //printf("Calling launcher\n");
    launcher(fp);
    fclose(fp);
    //addToRAM(fp, &start, &end);
    //if (start == -1) return -5;
    //PCB* pcb = makePCB(start,end);
    //addToReady(pcb);  
    return 0;
}

int scheduler(){
    /*
    // set CPU quanta to default, IP to -1, IR = NULL
    CPU.quanta = DEFAULT_QUANTA;
    CPU.IP = -1;
    while (size() != 0){
        //pop head of queue
        PCB* pcb = pop();
        //copy PC of PCB to IP of CPU
        CPU.IP = pcb->PC;

        int isOver = FALSE;
        int remaining = (pcb->end) - (pcb->PC) + 1;
        int quanta = DEFAULT_QUANTA;

        if (DEFAULT_QUANTA >= remaining) {
            isOver = TRUE;
            quanta = remaining;
        }

        int errorCode = run(quanta);

        if ( errorCode!=0 || isOver ){
            removeFromRam(pcb->start,pcb->end);
            free(pcb);
        } else {
            pcb->PC += DEFAULT_QUANTA;
            addToReady(pcb);
        }
    }
    // reset RAM
    resetRAM();*/
    return 0;
}

/*
Flushes every pcb off the ready queue in the case of a load error
*/
void emptyReadyQueue(){
    while (head!=NULL){
        ReadyQueueNode * temp = head;
        head = head->next;
        free(temp->PCB);
        free(temp);
    }
    sizeOfQueue =0;
}

