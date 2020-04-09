#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"ram.h"
#include"pcb.h"
#include"kernel.h"

int num = 0;

int countTotalPages(FILE *fo){
    //returns the total number of pages needed by the program
    int count = -1;
    char c;
    //Extract characters from file and store in character c 
    for (c = getc(fo); c != EOF; c = getc(fo)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
    printf("No of lines starting from zero is %d\n",count);
    int q = count/4;
    if (q*4 < count)
        ++q;
    return q;
}

int findFrame(){
    //findFrame should be looking for NULL frames and returning -1 if none are found
    int i;
    for(i =0; i <=36; i = i+4){
        if(ram[i] == NULL) {
            printf("Frame no: %d in RAM is empty\n", i/4);
            return i/4;
        }
    }
    return -2;
}

int findVictim () {
    //Initilizes random number generator
    int r = rand() % 11;
    return r;
}

void loadPage(int pageNumber, FILE *fp, int framenumber) {
    //FILE *f points to the beginning of the file in the backing store
    //int pageNumber is the desired page from the backing store
    //The function loads the 4 lines of code from the page into the frame in ram[]

    //we first calculate the lines of code the page number refers to
    int file_start = pageNumber * 4;
    int file_end = file_start + 3;

    //we then calculate the position in RAM[] that it needs to be loaded into
    
    int ram_start = framenumber * 4;
    int ram_end = ram_start +3;

    printf("The lines of code of the file are from %d --- %d and the index in RAM are %d -- %d\n", file_start, file_end, ram_start, ram_end);
    char str[60];
    int i = 0;
    while(fscanf(fp, "%[^\n]\n", str) != EOF) {
        //printf("CHECK: %s\n", str);
        if (i >= file_start && i <= file_end) {
            printf("Line %s is in RAM at %d\n", str, ram_start);
            ram[ram_start] = str;
            ram_start ++;
        }
        i++;
    }
}

int updatePageTable(PCB *p, int pagenumber, int framenumber, int victimframe) {
    if(victimframe == -1){
        p->pagetable[pagenumber] = framenumber;
    }
    else {
        p->pagetable[pagenumber] = victimframe;
    }
    
    return 0;
}

int launcher(FILE *source){
    //printf("Launcher entered\n");
    //we now copy the file into the backing store
    //in order to do so we first get the current directory
    char buffer[100];
    //we have buffer2 to go back to the previous dircetory
    char buffer2[100];
    //we first get the current diretory 
    GetCurrentDirectory(100, buffer);
    strcpy(buffer2, buffer);
    //we then concat backing store to the current directory
    char add[] = "//backingstore";
    strcat(buffer, add);
    BOOL changeDIR = SetCurrentDirectory(buffer);
    char i[5];
    itoa(num, i, 10);
    char name[] = "//";
    strcat(name, i);
    num++;
    strcat(name, ".txt");
    printf("IMPO: the name of the file will be %s\n", name);
    strcat(buffer, name);
    //printf("This is what is stored in the buffer %s \n", buffer);
    FILE *target = fopen(buffer,"w");

    if( target == NULL ) {
      printf("Unable to create file in directory\n");
   }
    char ch;
    ch = fgetc(source);
    while(ch != EOF) {
        fputc(ch, target);
        ch = fgetc(source);
    }

    //printf("File copied successfully\n");
    //Close file pointer pointing to original file
    fclose(source);
    fclose(target);

    FILE *fp;
    char filename[] = "0.txt";
    // Open the file 
    fp = fopen(filename, "r"); 
    // Check if file exists 
    if (fp == NULL) 
    { 
        printf("Could not open file\n"); 
        return 0; 
    } 
    
    
    // we now call countTotalPages
    int number = countTotalPages(fp);
    //we rewind the get the pointer pointing at start of file
    PCB* pc1 = makePCB(number);
    printf("PCB created with %d pages\n", pc1->pages_max);
    addToReady(pc1);
    printf("Added to ready queue\n");
    rewind(fp);
    //testing loadpage function
    loadPage(0, fp, 2);
    updatePageTable(pc1, 1, 0, -1);
    printf("Page table updated\n");
    fclose(fp);
    int emptyFrame = findFrame();
    //if(emptyFrame == -1) {
    int random = findVictim();
    printf("The random number generated is %d\n", random);
    
    //DeleteFile("0.txt");
    SetCurrentDirectory(buffer2);
    //}
    return 0;
}