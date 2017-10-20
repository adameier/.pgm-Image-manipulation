CC=g++
TAGS= -std=c++11

imageops: Image.o
	$(CC) -o imageops Imageops.cpp Image.o $(TAGS)

Image.o:
	$(CC) -c -o Image.o Image.cpp $(TAGS)

test: Image.o
	$(CC) -o tests Tests.cpp Image.o $(TAGS)
	./tests

clean:
	@rm -f *.o
	@rm -f imageops
	@rm -f tests
