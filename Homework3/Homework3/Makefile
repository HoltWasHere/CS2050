#Put your stuff ABOVE this line!
#If you have trouble, and you KNOW THAT YOU DID THE MAKEFILE CORRECTLY,
#then try the following things:
#	1. change "${OUTPUT_PATH}" in your run command to your actual executable name you made in this file, 
#	   adding .exe to the end, and putting it in the quotes
#	2. Hit the button to the left of the run button (the green arrow). Highlighted, it
#	   should be the one for clean and build. Then run your code (that's what this clean 
#	   target is for!)
#The following things might make you do the above:
#	You run the program, and you get something saying your executable is not found
#	You change your code, but you see no change in the output, even though you should.
all: main.c bossFunctions.o debugPrint.o fightFunctions.o
	gcc main.c bossFunctions.o debugPrint.o fightFunctions.o -o HW3
	
bossFunctions.o: bossFunctions.c
	gcc -c bossFunctions.c

debugPrint.o: debugPrint.c
	gcc -c debugPrint.c
	
fightFunctions.o: fightFunctions.c
	gcc -c fightFunctions.c

clean:
	rm *.o HW3.exe