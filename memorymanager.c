#include<stdio.h>
#include<string.h>
#include<windows.h>

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
    //GetCurrentDirectory(100, buffer);
    //printf("%s\n", buffer);
    strcat(buffer, "//targetfile5.txt");
    FILE *target = fopen(buffer,"w");

    if( target == NULL ) {
      printf("Press any key to exit...\n");
   }
    char ch;
    ch = fgetc(source);
    while(ch != EOF) {
        //printf("Entered\n");
        fputc(ch, target);
        ch = fgetc(source);
    }

    printf("File copied successfully\n");
    fclose(source);
    
    fclose(target);

    //We now need to copy FILE p into our current directory
    //BOOL copied = CopyFileA(p, buffer, 0);
    printf("New file created\n");
    return 0;
}