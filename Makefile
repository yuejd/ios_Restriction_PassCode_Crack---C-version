default : 
	make cracker

iosPCCrack.o : iosPCCrack.c header.h
	gcc -c iosPCCrack.c -o iosPCCrack.o

mythread.o : mythread.c header.h
	gcc -c mythread.c -o mythread.o

base64_cd.o : base64_cd.c
	gcc -c base64_cd.c -o base64_cd.o

parsefile.o : parsefile.c
	gcc -c parsefile.c -o parsefile.o

cracker : iosPCCrack.o mythread.o base64_cd.o parsefile.o
	gcc iosPCCrack.o mythread.o base64_cd.o parsefile.o -o cracker -lpthread -lcrypto

run :
	./cracker

clean :
	rm *.o
