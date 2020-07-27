# OSProject

Built my own OS Shell using modular programming techniques.

Commands user can run are as follows:

help - displays all the commands
quit - Exits / terminates the shell
set VAR STRING - Assigns a value to shell memory
print VAR - Displays the STRING assigned to VAR
run SCRIPT.TXT - Executes the file SCRIPT.TXT
exec prog1 prog2 prog3 - This new command will simulate the kernel run-time environment, which includes the PCB, the ready
queue, the CPU, and a temporary simple memory.

Instructions to run OS Shell:
gcc -c shell.c interpreter.c shellmemory.c kernel.c cpu.c pcb.c ram.c
gcc -o mykernel shell.o interpreter.o shellmemory.o kernel.o cpu.o pcb.o ram.o
./mykernel
