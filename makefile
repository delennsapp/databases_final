final: final.o file.o document.o collection.o scanner.o array.o dictionary.o
	gcc -Wall -g final.o file.o document.o collection.o scanner.o array.o dictionary.o -o final

final.o: final.c io/file/file.h database/document/document.h database/collection/collection.h
	gcc -Wall -g -c final.c

file.o: io/file/file.c io/file/file.h io/utilities/utilities.h
	gcc -Wall -g -c file.c

document.o: database/document/document.c database/document/document.h dictionary/dictionary.h scanner/scanner.h database/collection/collection.h
	gcc -Wall -g -c document.c

collection.o: database/collection/collection.c database/collection/collection.h scanner/scanner.h list/doublylinked/doublylinked.h
	gcc -Wall -g -c collection.c

scanner.o: scanner/scanner.c scanner/scanner.h
	gcc -Wall -g -c scanner.c

array.o: array/array.c array/array.h scanner/scanner.h
	gcc -Wall -g -c array.c

dictionary.o: dictionary/dictionary.c dictionary/dictionary.h array/array.h scanner/scanner.h
	gcc -Wall -g -c dictionary.c

doublylinked.o: list/doublylinked/doublylinked.c list/doublylinked/doublylinked.h scanner/scanner.h list/node/node.h
	gcc -Wall -g -c doublylinked.c
