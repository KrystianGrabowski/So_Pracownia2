#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <cstdlib>

int mysliwi, kucharze, zwierzyna, pozywienie;

int kostka_rzut(){
    return (std::rand() % 6) + 1;
}

void polowanie(){
    int mysliwy_rzut = kostka_rzut();
    int zwierz_rzut = kostka_rzut();


    if (mysliwy_rzut > zwierz_rzut) {
        zwierzyna++;

    }
}

void pieczenie(){
    if (zwierzyna > 0){
        zwierzyna--;
        int kucharz_rzut = kostka_rzut();
        pozywienie += kucharz_rzut;
    }
}

void *mysliwy(void*){
    for (int dzien = 1; dzien <= 365; dzien++){

    }
    return 0;
}

void *kucharz(void*){
    for (int dzien = 1; dzien <= 365; dzien++){

    }
    return 0;
}

int main(int argc, char* argv[]){

    mysliwi = atoi(argv[1]);
    kucharze = atoi(argv[2]);
    zwierzyna = atoi(argv[3]);
    pozywienie = atoi(argv[4]);

}
