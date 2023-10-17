all: StructStrQsort.o ReadStrings.o OnegMain.o
	g++ StructStrQsort.o ReadStrings.o OnegMain.o -o Q.exe

StructStrQsort.o: StructStrQsort.cpp
	g++ StructStrQsort.cpp -c

ReadStrings.o: ReadStrings.cpp
	g++ ReadStrings.cpp -c

OnegMain.o: OnegMain.cpp
	g++ OnegMain.cpp -c

clean:
	@echo "Clean project"
	rm -f StructStrQsort.o StrQsort.o ReadStrings.o OnegMain.o
	@echo "Clean complited"
