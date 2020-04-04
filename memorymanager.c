#include<stdio.h>
#include<string.h>
#include<windows.h>

int countTotalPages(FILE *fp){
    //returns the total number of pages needed by the program
    int count =0;
    char c;
    //Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
    printf("No of lines is %d\n",count);
    int q = count/4;
    if (q*4 < count)
        ++q;
    return q;
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
    fclose(fp);
    printf("The file needs %d pages\n", number);
    return 0;
}