#include "utils.h"

int** split_line_to_args(char *linie){
    int **result = (int**)malloc(2 * sizeof(int*));
    result[0] = (int*)malloc(3*sizeof(int));
    result[1] = (int*)malloc(100*sizeof(int));

    // result : TIP, CONTOR, IESIRE \n iesiri...
    
    // Tipul de nod 
    if (strncmp(linie, "AND", 3) == 0) {
        result[0][0] = 0;
    } else if (strncmp(linie, "OR", 2) == 0) {
        result[0][0] = 1;
    } else if (strncmp(linie, "NOT", 3) == 0) {
        result[0][0] = 2;
    } else {
        result[0][0] = -1; // Tip invalid 
    }

    // Intrari
    int contor = 0;
    char *p = linie;
    while(*p!='\0'){
        if(*p>='1' && *p<='9'){
            char *num = (char*)malloc(5*sizeof(char));
            int i = 0;
            while (*p >= '0' && *p <= '9')
                num[i++] = *p++;
            num[i]='\0';
            result[1][contor]=atoi(num);
            free(num);
            contor++;
        }
        p++;
    }
    result[0][2]=result[1][contor-1]; //Iesire
    result[0][1] = contor;
    return result;
}

int** node_to_out(nod t, int *nr_clauze,int *clauze_poarta){
    int **result = (int**)malloc(100*sizeof(int*));
    for (int i = 0; i < 100; i++)
    {
        result[i]=malloc(100*sizeof(int));
    }
    int c;
    switch (t->tip_nod)
    {
    case 0:
        //poarta AND
        c=0;
        // !A V !B V ... V out
        for (int i = 0; i < 100; i++)
        {
            if(t->intrari[i] == 0 || t->intrari[i]>100){
                result[0][i] = t->iesire;
                result[0][i+1] = -101;
                break;
            }
            result[0][i] = -t->intrari[i];
            c++;
        }
        // A V !C, B V !C, C V !out...
        for (int i = 1; i <= c; i++)
        {
            result[i][0] = t->intrari[i-1];
            result[i][1] = -t->iesire;
            result[i][2] = -101;
        }
        *nr_clauze+=c+1;
        *clauze_poarta = c+1;
        break;
    
    case 1:
        //poarta OR
        c=0;
        // A V B V ... V !out
        for (int i = 0; i < 100; i++)
        {
            if(t->intrari[i] == 0 || t->intrari[i]>100){
                result[0][i] = -t->iesire;
                result[0][i+1] = -101;
                break;
            }
            result[0][i] = t->intrari[i];
            c++;
        }
        // !A V out, !B V out, C V out...
        for (int i = 1; i <= c; i++)
        {
            result[i][0] = -t->intrari[i-1];
            result[i][1] = t->iesire;
            result[i][2] = -101;
        }
        *nr_clauze+=c+1;
        *clauze_poarta = c+1;
        break;
    
    case 2:
        //poarta NOT
        // !A V !out 
        //  A V out
        result[0][0] = -t->intrari[0];
        result[0][1] = -t->iesire;
        result[0][2] = -101;
        result[1][0] = t->intrari[0];
        result[1][1] = t->iesire;
        result[1][2] = -101;
        *nr_clauze+=2;
        *clauze_poarta=2;
        break;
    default:
        break;
    }
        return result;

}
