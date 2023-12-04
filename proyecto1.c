// Estudiante: Pedro Arce H
// Proyecto 1: C

#include <stdio.h>
#include <stdlib.h>

#define CIUDADES_MAX 10

int tamanio_max_ciudades[CIUDADES_MAX][CIUDADES_MAX];

void iniciar_matriz(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Creamos una matriz diagonal
            tamanio_max_ciudades[i][j] = (i == j) ? 0 : -1;
        }
    }
}

void imprimir_matriz(int n) {
    // Se imprimen las distancias ingresadas previamente
    printf("Distancia entre ciudades:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d\t", tamanio_max_ciudades[i][j]);
        }
        printf("\n");
    }
}

void ciudades_ingresadas(int n) {
    printf("Ingrese las distancias entre ciudades (use -1 si no hay conexión):\n");

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int distancia;
            printf("Distancia entre la ciudad %d y la ciudad %d: ", i, j);
            scanf("%d", &distancia);
            tamanio_max_ciudades[i][j] = distancia;
            tamanio_max_ciudades[j][i] = distancia;  // La matriz es simétrica
        }
    }
}

void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void copiar_arreglo(int* src, int* dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int calcular_distancia(int* camino, int n) {
    int distancia_actual = 0;
    for (int i = 0; i < n - 1; i++) {
        int desde = camino[i];
        int hasta = camino[i + 1];
        if (tamanio_max_ciudades[desde][hasta] == -1) {
            return -1;  // No hay conexión directa
        }
        distancia_actual += tamanio_max_ciudades[desde][hasta];
    }
    return distancia_actual;
}

void encontrar_distancia_minima(int* camino, int tamanio, int n, int* camino_min, int* distancia_min) {
    if (tamanio == n) {
        int distancia_actual = calcular_distancia(camino, n);
        if (distancia_actual != -1 && distancia_actual < *distancia_min) {
            *distancia_min = distancia_actual;
            copiar_arreglo(camino, camino_min, n);
        }
        return;
    }

    for (int i = tamanio; i < n; i++) {
        intercambiar(&camino[i], &camino[tamanio]);
        encontrar_distancia_minima(camino, tamanio + 1, n, camino_min, distancia_min);
        intercambiar(&camino[i], &camino[tamanio]);  // Deshacer el intercambio para probar otras combinaciones

    }
}

int main() {
    int n, ciudad_inicial, ciudad_final;

    printf("Ingrese el número de ciudades (máximo %d) contando la ciudad 0 como la primer ciudad: ", CIUDADES_MAX);
    scanf("%d", &n);

    if (n <= 0 || n > CIUDADES_MAX) {
        printf("Número de ciudades no válido.\n");
        return 1;
    }

    iniciar_matriz(n);
    ciudades_ingresadas(n);
    imprimir_matriz(n);

    printf("Ingrese la ciudad de inicio (desde la 0 hasta la %d): ", n - 1);
    scanf("%d", &ciudad_inicial);

    printf("Ingrese la ciudad de llegada (desde la 0 hasta la %d): ", n - 1);
    scanf("%d", &ciudad_final);

    if (ciudad_inicial < 0 || ciudad_inicial >= n || ciudad_final < 0 || ciudad_final >= n) {
        printf("Ciudades de inicio o llegada no válidas.\n");
        return 1;
    }

    int camino[CIUDADES_MAX];
    int camino_minimo[CIUDADES_MAX];
    int distancia_minima = 999999;  // Inicializar con un valor grande

    for (int i = 0; i < n; i++) {
        camino[i] = i;
    }

    encontrar_distancia_minima(camino, 0, n, camino_minimo, &distancia_minima);

    printf("Camino óptimo: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", camino_minimo[i]);
    }
    printf("%d\n", camino_minimo[0]);  // Volver a la ciudad inicial

    printf("Distancia mínima: %d\n", distancia_minima);

    return 0;
}
