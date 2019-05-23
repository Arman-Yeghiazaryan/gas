CFLAGS = -g -Wall
OBJ = experiment.o main.o
EXE = model

all: $(EXE)

model: $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(EXE)
clean:
	$(RM) *.o

gas:
	g++ -c draw.cpp -I/home/user/SFML-2.4.0/include
	g++ draw.o -o test -L/home/user/SFML-2.4.0/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=/home/user/SFML-2.4.0/lib && ./test