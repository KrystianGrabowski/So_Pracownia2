osadnicy: osadnicy.cpp
	g++ -pthread -Wall -Werror osadnicy.cpp -o osadnicy
	
run: osadnicy
	./osadnicy 10 10 10 10
