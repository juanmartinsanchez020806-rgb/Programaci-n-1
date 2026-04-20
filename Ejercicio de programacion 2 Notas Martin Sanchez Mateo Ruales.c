#include <stdio.h>
#define ESTUDIANTES 5
#define ASIGNATURAS 3

int main() {

    float notas[ESTUDIANTES][ASIGNATURAS];
    float promedioEst[ESTUDIANTES];
    float promedioAsig[ASIGNATURAS];
    float maxEst[ESTUDIANTES];
    float minEst[ESTUDIANTES];
    float maxAsig[ASIGNATURAS];
    float minAsig[ASIGNATURAS];
    int aprobados[ASIGNATURAS] = {0};
    int reprobados[ASIGNATURAS] = {0};
    int i, j;

    printf("INGRESO DE NOTAS:\n");
    for(i = 0; i < ESTUDIANTES; i++) {
        for(j = 0; j < ASIGNATURAS; j++) {
            do {
                printf("Nota estudiante %d asignatura %d: ", i+1, j+1);
                scanf("%f", &notas[i][j]);
                if(notas[i][j] < 0 || notas[i][j] > 10) {
                    printf("Error: Nota debe estar entre 0 y 10\n");
                }
            } while(notas[i][j] < 0 || notas[i][j] > 10);

        }
    }

    for(i = 0; i < ESTUDIANTES; i++) {
        float suma = 0;
        maxEst[i] = notas[i][0];
        minEst[i] = notas[i][0];
        for(j = 0; j < ASIGNATURAS; j++) {
            suma += notas[i][j];
            if(notas[i][j] > maxEst[i])
                maxEst[i] = notas[i][j];
            if(notas[i][j] < minEst[i])
                minEst[i] = notas[i][j];
        }
        promedioEst[i] = suma / ASIGNATURAS;
    }

    for(j = 0; j < ASIGNATURAS; j++) {
        float suma = 0;
        maxAsig[j] = notas[0][j];
        minAsig[j] = notas[0][j];
        for(i = 0; i < ESTUDIANTES; i++) {
            suma += notas[i][j];
            if(notas[i][j] > maxAsig[j])
                maxAsig[j] = notas[i][j];
            if(notas[i][j] < minAsig[j])
                minAsig[j] = notas[i][j];
            if(notas[i][j] >= 6)
                aprobados[j]++;
            else
                reprobados[j]++;
        }
        promedioAsig[j] = suma / ESTUDIANTES;
    }

    printf("\n--- PROMEDIO POR ESTUDIANTE ---\n");
    for(i = 0; i < ESTUDIANTES; i++) {
        printf("Estudiante %d Promedio: %.2f\n",
               i+1, promedioEst[i]);
        printf("   Maxima: %.2f\n", maxEst[i]);
        printf("   Minima: %.2f\n", minEst[i]);
    }
    printf("\n--- PROMEDIO POR ASIGNATURA ---\n");
    for(j = 0; j < ASIGNATURAS; j++) {
        printf("Asignatura %d Promedio: %.2f\n",
               j+1, promedioAsig[j]);
        printf("   Maxima: %.2f\n", maxAsig[j]);
        printf("   Minima: %.2f\n", minAsig[j]);
        printf("\n--- NUMERO DE APROBADOS Y REPROBADOS ---\n");
        printf("   Aprobados: %d\n", aprobados[j]);
        printf("   Reprobados: %d\n", reprobados[j]);
    }

    return 0;
}