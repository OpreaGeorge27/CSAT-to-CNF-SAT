#include <stdio.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("ARGUMENT ERROR!\n");
        return 0;
    }   

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");
    
    if(inputFile == NULL || outputFile == NULL){
        printf("FILE ERROR!\n");
        return 0;
    }

    int nr_clauze=0;
    int out_index = 0;
    
    char linie[150];
    if(fgets(linie, sizeof(linie), inputFile) != NULL) {
        out_index = atoi(linie+2);
    }

    nod* noduri = (nod*)malloc(100*sizeof(nod));
    int contor = 0;

    while(fgets(linie, sizeof(linie), inputFile) != NULL){
        int **argumente = split_line_to_args(linie);
        noduri[contor]=malloc(sizeof(nod));
        noduri[contor]->intrari=malloc((argumente[0][1]-1)*sizeof(int));
        noduri[contor]->tip_nod=argumente[0][0];
        for (int i = 0; i < argumente[0][1]-1; i++)
        {
            noduri[contor]->intrari[i]=argumente[1][i];
        }
        noduri[contor]->iesire=argumente[0][2];
        contor++;
    }
    
    fprintf(outputFile,"p cnf %d %d\n",contor,nr_clauze);
    int **output;
    for(int i = 0;i<contor;i++){
        int clauze_poarta=0;
        output = node_to_out(noduri[i],&nr_clauze, &clauze_poarta);
        for (int i = 0; i < clauze_poarta; i++)
        {
            for (int j = 0; j<100 ; j++)
            {
                if(output[i][j] == -101)
                    break;

                fprintf(outputFile,"%d ",output[i][j]);

            }
            fprintf(outputFile,"0\n");
        }
    }
    fclose(inputFile);
    fclose(outputFile);

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    //AM REPETAT PROCESUL CA SA POT AVEA ACCES LA NR DE CLAUZE :)
    fprintf(outputFile,"p cnf %d %d\n",out_index,nr_clauze+1);
    for(int i = 0;i<contor;i++){
        int clauze_poarta=0;
        output = node_to_out(noduri[i],&nr_clauze, &clauze_poarta);
        for (int i = 0; i < clauze_poarta; i++)
        {
            for (int j = 0; j<100 ; j++)
            {
                if(output[i][j] == -101)
                    break;

                fprintf(outputFile,"%d ",output[i][j]);

            }
            fprintf(outputFile,"0\n");
        }
    }
    fprintf(outputFile,"%2d 0",out_index);
    
    fclose(inputFile);
    fclose(outputFile);


    return 0;
}

