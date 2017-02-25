all: string_0.100000.pdf string_0.100000.dat

string_0.100000.pdf:string_0.100000.dat
	 python cuerda.py string_0.100000.dat 

string_0.100000.dat: string.x
	./string.x 0.1

string.x: cuerda.c
	gcc -o string.x cuerda.c  
clean:
	rm -f  *.pdf *.dat *.x 


