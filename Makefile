CC = g++
INC = include
#LIB = /home/shek/progs/ogl/lib
SRC = src
CPPFLAGS = -g -I$(INC) 
LDFLAGS = -lglut -lGL -lGLU
OBJECTS = main.o obj2ogl.o util.o #bmp_io.o

test: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

main.o: $(SRC)/main.cpp $(INC)/obj2ogl.h
	$(CC) $(CPPFLAGS) -c $(SRC)/main.cpp

obj2ogl.o: $(SRC)/obj2ogl.cpp $(INC)/obj2ogl.h $(INC)/util.h
	$(CC) $(CPPFLAGS) -c $(SRC)/obj2ogl.cpp

util.o: $(SRC)/util.cpp $(INC)/util.h
	$(CC) $(CPPFLAGS) -c $(SRC)/util.cpp

bmp_io.o: $(SRC)/bmp_io.cpp $(INC)/bmp_io.h
	$(CC) $(CPPFLAGS) -c $(SRC)/bmp_io.cpp

clean:
	rm test *.o
