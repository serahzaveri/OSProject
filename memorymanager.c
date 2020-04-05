#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"ram.h"

int countTotalPages(FILE *fo){
    //returns the total number of pages needed by the program
    int count = 0;
    char c;
    //Extract characters from file and store in character c 
    for (c = getc(fo); c != EOF; c = getc(fo)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
    printf("No of lines is %d\n",count);
    int q = count/4;
    if (q*4 < count)
        ++q;
    return q;
}

int findFrame(){
    return 0;
}

void loadPage(int pageNumber, FILE *fp, int framenumber) {
    //FILE *f points to the beginning of the file in the backing store
    //int pageNumber is the desired page from the backing store
    //The function loads the 4 lines of code from the page into the frame in ram[]

    //we first calculate the lines of code the page number refers to
    int file_end = pageNumber * 4;
    int file_start = file_end - 3;

    //we then calculate the position in RAM[] that it needs to be loaded into
    int ram_end = framenumber * 4 - 1;
    int ram_start = ram_end - 3;

    printf("The lines of code of the file are from %d --- %d and the index in RAM are %d -- %d\n", file_start, file_end, ram_start, ram_end);
    char str[60];
    int i = 1;
    while(fscanf(fp, "%[^\n]\n", str) != EOF) {
        printf("CHECK: %s\n", str);
        if (i >= file_start && i <= file_end) {
            printf("Entered %d\n", i);
            ram[ram_start] = str;
            ram_start ++;
        }
        i++;
    }
    
}

int launcher(FILE *source){
    printf("Launcher entered\n");
    //we now copy the file into the backing store
    //in order to do so we first get the current directory
    char buffer[100];
    //we first get the current diretory 
    GetCurrentDirectory(100, buffer);
    //we then concat backing store to the current directory
    char add[] = "//backingstore";
    strcat(buffer, add);
    BOOL changeDIR = SetCurrentDirectory(buffer);
    int num = 0;
    char i[5];
    itoa(num, i, 10);
    char name[] = "//targetfile";
    strcat(name, i);
    num++;
    strcat(name, ".txt");
    printf("IMPO: the name of the file will be %s\n", name);
    strcat(buffer, name);
    printf("This is what is stored in the buffer %s \n", buffer);
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

    printf("File copied successfully\n");
    //Close file pointer pointing to original file
    fclose(source);
    fclose(target);

    FILE *fp;
    char filename[] = "targetfile0.txt";
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
    rewind(fp);
    //testing loadpage function
    loadPage(2, fp, 3);
    fclose(fp);
    return 0;
}