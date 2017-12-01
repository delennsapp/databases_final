final: final.o file.o database.o document.o collection.o scanner.o array.o dictionary.o doublylinked.o node.o utilities.o
	gcc -Wall -g final.o file.o database.o document.o collection.o scanner.o array.o dictionary.o doublylinked.o node.o utilities.o -o final

final.o: final.c io/file/file.h database/document/document.h database/collection/collection.h
	gcc -Wall -g -c final.c

file.o: io/file/file.c io/file/file.h io/utilities/utilities.h
	gcc -Wall -g -c io/file/file.c

database.o: database/database.c database/database.h database/collection/collection.h database/document/document.h scanner/scanner.h list/doublylinked/doublylinked.h array/array.h
	gcc -Wall -g -c database/database.c

document.o: database/document/document.c database/document/document.h dictionary/dictionary.h scanner/scanner.h 
	gcc -Wall -g -c database/document/document.c

collection.o: database/collection/collection.c database/collection/collection.h database/document/document.h scanner/scanner.h list/doublylinked/doublylinked.h array/array.h
	gcc -Wall -g -c database/collection/collection.c

scanner.o: scanner/scanner.c scanner/scanner.h
	gcc -Wall -g -c scanner/scanner.c

array.o: array/array.c array/array.h scanner/scanner.h
	gcc -Wall -g -c array/array.c

dictionary.o: dictionary/dictionary.c dictionary/dictionary.h array/array.h scanner/scanner.h
	gcc -Wall -g -c dictionary/dictionary.c

doublylinked.o: list/doublylinked/doublylinked.c list/doublylinked/doublylinked.h scanner/scanner.h list/node/node.h io/utilities/utilities.h
	gcc -Wall -g -c list/doublylinked/doublylinked.c

node.o: list/node/node.c list/node/node.h scanner/scanner.h io/utilities/utilities.h
	gcc -Wall -g -c list/node/node.c

utilities.o: io/utilities/utilities.c io/utilities/utilities.h
	gcc -Wall -g -c io/utilities/utilities.c

clean:
	rm -f *.o final
