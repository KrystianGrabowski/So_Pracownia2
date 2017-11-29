#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

int mysliwi, kucharze, zwierzyna, pozywienie;
int ocalali;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


int kostka_rzut(){
    return (std::rand() % 6) + 1;
}

void polowanie(){

    int mysliwy_rzut = kostka_rzut();
    int zwierz_rzut = kostka_rzut();
    pthread_mutex_lock(&lock);
    if (mysliwy_rzut > zwierz_rzut) {
        zwierzyna++;
        printf("Udane polowanie +1 <zwierzyna {%d}>\n", zwierzyna);
    }
    pthread_mutex_unlock(&lock);


}

void pieczenie(){
    pthread_mutex_lock(&lock);
    if (zwierzyna > 0){
        zwierzyna--;
        int kucharz_rzut = kostka_rzut();
        pozywienie += kucharz_rzut;
        printf("Udane pieczenie +%d <pozywienie {%d}>\n", kucharz_rzut, pozywienie);
    }
    pthread_mutex_unlock(&lock);
}

void *mysliwy(void*){
    for (int dzien = 1; dzien <= 365; dzien++){

        polowanie();
        pthread_mutex_lock(&lock);
        if (pozywienie > 0){
            pozywienie--;
            pthread_mutex_unlock(&lock);
            usleep(500);
        }
        else{
            printf("Mysliwy odszedl z wioski !!\n");
            ocalali--;
            pthread_mutex_unlock(&lock);
            break;

        }

    }
    return 0;
}

void *kucharz(void*){
    for (int dzien = 1; dzien <= 365; dzien++){

        pieczenie();
        pthread_mutex_lock(&lock);
        if (pozywienie > 0 ){
            pozywienie--;
            pthread_mutex_unlock(&lock);
            usleep(500);
        }
        else{
            printf("Kucharz odszedl z wioski !!\n");
            ocalali--;
            pthread_mutex_unlock(&lock);
            break;
        }

    }
    return 0;
}

int main(int argc, char* argv[]){

    int k, m;

    srand( time( NULL ) );
    mysliwi = atoi(argv[1]);
    kucharze = atoi(argv[2]);
    zwierzyna = atoi(argv[3]);
    pozywienie = atoi(argv[4]);
    ocalali = mysliwi + kucharze;

    pthread_t tab_k[kucharze];
    pthread_t tab_m[mysliwi];

    for (k = 0; k < kucharze; k++){
        pthread_create(&tab_k[k], NULL, &kucharz, NULL);
    }
    for (m = 0; m < mysliwi; m++){
        pthread_create(&tab_m[m], NULL, &mysliwy, NULL);
    }

    for (k = 0; k < kucharze; k++){
        pthread_join(tab_k[k], NULL);
    }
    for (m = 0; m < mysliwi; m++){
        pthread_join(tab_m[m], NULL);
    }
    pthread_mutex_destroy(&lock);
    printf("\nPodsumowanie :\n ocalali = %d \n pozywnie = %d\n", ocalali, pozywienie);

    return 0;
}
