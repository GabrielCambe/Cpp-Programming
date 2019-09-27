NOME_main = -o main
CPP_Flgs = -std=c++17 -Wall -Wextra -g
OBJ_Flgs = $(CPP_Flgs) -c
STIC_FLgs = -L. -lheader
DYNMC_Flgs = -shared -fPIC

all-static:
	g++ $(OBJ_Flgs) header.cpp
	ar crv libheader.a header.o
	g++ $(OBJ_Flgs) main.cpp
	g++ $(NOME_main) main.o $(STIC_FLgs)
		# -L sets the path for libraries, here to the current folder “.”
		# -l adds a library

all-dynamic:
	#g++ $(OBJ_Flgs) $(DYNMC_Flgs) header.cpp
	g++ $(DYNMC_Flgs) -o libheader.so header.cpp
	g++ $(OBJ_Flgs) main.cpp
	g++ $(NOME_main) main.o ./libheader.so


clean:
	rm *.o || true
	rm *.a || true
	rm *.so || true

purge: clean
	rm main || true