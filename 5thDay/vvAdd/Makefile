vvAdd0: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O0 -DwithMACRO

vvAdd1: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O1 -DwithMACRO

vvAdd2: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O2 -DwithMACRO

vvAdd3: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O3 -DwithMACRO

vvAdd0OpenMP: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O0 -fopenmp -DwithMACRO

vvAdd1OpenMP: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O1 -fopenmp -DwithMACRO

vvAdd2OpenMP: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O2 -fopenmp -DwithMACRO

vvAdd3OpenMP: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O3 -fopenmp -DwithMACRO


vvAdd3OpenMP-verbose: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O3 -fopenmp -fopt-info -DwithMACRO

vvAdd0-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O0 

vvAdd1-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O1 

vvAdd2-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O2 

vvAdd3-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O3 

vvAdd0OpenMP-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O0 -fopenmp 

vvAdd1OpenMP-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O1 -fopenmp 

vvAdd2OpenMP-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O2 -fopenmp 

vvAdd3OpenMP-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O3 -fopenmp 


vvAdd3OpenMP-verbose-macroless: purge
	g++ -o vvAdd vvAdd.cpp -Wall -Wextra -O3 -fopenmp -fopt-info 


purge:
	rm vvAdd || true