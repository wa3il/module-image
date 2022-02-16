all: ./bin/test

./bin/test: ./obj/mainTest.o ./obj/Image.o ./obj/Pixel.o 
	g++ -g ./obj/mainTest.o ./obj/Image.o ./obj/Pixel.o -o ./bin/test

./obj/mainTest.o: ./src/mainTest.cpp ./src/Image.h ./src/Pixel.h
	g++ -g -Wall -c ./src/mainTest.cpp -o ./obj/mainTest.o

./obj/Image.o: ./src/Image.cpp ./src/Image.h ./src/Pixel.h
	g++ -g -Wall -c ./src/Image.cpp -o ./obj/Image.o

./obj/Pixel.o: ./src/Pixel.cpp ./src/Pixel.h
	g++ -g -Wall -c ./src/Pixel.cpp -o ./obj/Pixel.o

clean:
	rm *.o