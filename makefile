osadnicy: osadnicy.cpp
	g++ -pthread -Wall -Werror osadnicy.cpp -o osadnicy
	
run: osadnicy
	./osadnicy 25 25 50 50
