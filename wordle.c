//Sandru Rares-Andrei
//grupa 161
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define NR_MAXIM_CUVINTE 100
int numarCuvinteFisier = 0, contor = 1;

int verificareIncercare();
char **citireFisier();
char *cuvantRandom();
void derulareJoc();

int main() {

    char ** listaCuvinte = calloc(NR_MAXIM_CUVINTE, sizeof(char * ));
    citireFisier(listaCuvinte);
    derulareJoc(listaCuvinte);


    return 0;
}




int verificareIncercare(const char * raspuns, const char * incercare) {
    int i, j;
    char indiciu[6] = {'-', '-', '-', '-', '-', '\0'};
    //un set de indicatori care arata daca litera respectiva din raspuns este utilizata ca indiciu
    int litereCorecte[5] = {0, 0, 0, 0, 0};

    //verificam daca este solutie, adaugam verde
    for (i = 0; i < 5; i++) {
        if (incercare[i] == raspuns[i]) {
            indiciu[i] = 'V';
            litereCorecte[i] = 1;
        }
    }

    //a doua iteratie, verificam ce litere are in comun incercarea cu solutia
    for (i = 0; i < 5; i++) {
        if (indiciu[i] == '-') { //nu am gasit o litera comuna
            for (j = 0; j < 5; j++) {
                if (incercare[i] == raspuns[j] && !litereCorecte[j]) {
                    //am gasit litera in ambele cuvinte, coloram galben
                    indiciu[i] = 'G';
                    litereCorecte[j] = 1;
                    break; //coloram o singura litera din indiciu cu galben, conform regulilor Wordle
                }
            }
        }
    }

    printf("%s\n", indiciu);
    return strcmp(indiciu, "VVVVV") == 0; //daca avem 5G in indiciu evident jucatorul a gasit solutia.
}

char **citireFisier(char **listaCuvinte){
    char * cuvantCinciLitere = malloc(6 * sizeof(char));
    FILE * fisierCuvinte = fopen("words.txt", "r");
    if (fisierCuvinte == NULL) {
        perror("Nu am putut sa deschidem fisierul! ");
        assert(fisierCuvinte == NULL);
    }
    while (fscanf(fisierCuvinte, "%s", cuvantCinciLitere) != EOF) {
        assert(strlen(cuvantCinciLitere)==5);
        listaCuvinte[numarCuvinteFisier] = cuvantCinciLitere;
        numarCuvinteFisier++;
        assert(numarCuvinteFisier<=100);
        cuvantCinciLitere = malloc(6 * sizeof(char));
    }
    free(cuvantCinciLitere);
    fclose(fisierCuvinte);
    return listaCuvinte;
}

void derulareJoc(char **listaCuvinte){
    int i;
    char * raspuns = cuvantRandom(listaCuvinte);
    int numarIncercari, incercari_corecte=0;
    char * incercare = malloc(6 * sizeof(char));
    for(i=0; i<6 && !incercari_corecte; i++){
        //citim o incercare de la jucator
        printf("Introduce un cuvant de 5 litere si apasa enter: ");
        scanf("%s", incercare);
        assert(strlen(incercare)==5);
        printf("Ai ghicit: %s\n", incercare);
        //procesam incercarea si rulam bucla pana gasim o solutie
        incercari_corecte = verificareIncercare(raspuns, incercare);
        numarIncercari=i;
    }

    if (incercari_corecte) {
        printf("Bravo ai ghicit cuvantul din incercarea numarul %d!\n", numarIncercari+1);
    } else {
        printf("Ai ramas fara incercari, cuvantul este %s\n", raspuns);
    }

    for (i = 0; i < numarCuvinteFisier; i++) {
        free(listaCuvinte[i]);
    }
    free(listaCuvinte);
    free(incercare);    
}

char *cuvantRandom(char **listaCuvinte){
    srand(time(NULL));
    return listaCuvinte[rand() % numarCuvinteFisier];
}
