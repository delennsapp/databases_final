testlist: testlist.o doublylinked.o node.o utilities.o scanner.o
	gcc -Wall -g testlist.o doublylinked.o node.o utilities.o scanner.o -o testlist 

testlist.o: testlist.c doublylinked.h ../node/node.h
	gcc -Wall -g -c testlist.c 

doublylinked.o: doublylinked.c doublylinked.h ../node/node.h ../../io/utilities/utilities.h ../../scanner/scanner.h
	gcc -Wall -g -c doublylinked.c

node.o: ../node/node.c ../node/node.h ../../io/utilities/utilities.h ../../scanner/scanner.h
	gcc -Wall -g -c ../node/node.c 

utilities.o: ../../io/utilities/utilities.c ../../io/utilities/utilities.h
	gcc -Wall -g -c ../../io/utilities/utilities.c 

scanner.o: ../../scanner/scanner.c ../../scanner/scanner.h
	gcc -Wall -g -c ../../scanner/scanner.c

clean: 
	rm *.o

run:
	testlist
