/*
Andres Sedo Esquivel B66740
Esta propuesta para el problema 3 realiza un manejo dinamico de la memoria, considera
el valor n y m mas alto para reservar memoria para un matriz de tamano nmax x mmax
esto se va haciendo de forma dinamica hasta insertar el caracter de finalizacion de 
pares de numeros. 
Finalmente imprime la matriz antes y despues de insertar los valores y el puntero de
cada elemento de las filas 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//funcion  para elevar a un exponente un  numero base
int power(int base, int exponente) {
    int resultado = 1;
    while (exponente != 0) { //condicion de para, cuando es cero ya se ha recorrido todo
        resultado = resultado * base;
        exponente = exponente - 1;
    }
    return resultado; // regresa int resultado
}

int concatenarNumeros(int x, int y) {
    // Calcular el número de dígitos en y
    int temp = y;
    int numDigits = 0; // cantidad de digitos para mover x y luego sumarlo con y
    while (temp > 0) {
        temp = temp / 10;
        numDigits++;   // num de digitos a mover x
    }
    if (y==0){
        numDigits=1;
    }
    // Multiplicar x por 10 elevado a la potencia de los dígitos en y y luego sumar para sumar los numeros
    return x * power(10, numDigits) + y;
}

int reservarMemoria(int*** matriz, int n, int m) {
    // funcion para reservar memoria de forma dinamica, considerando la direccion nxm mas alta
    *matriz = (int**)malloc(n * sizeof(int*));  // reserva de memoria para filas 
    if (*matriz == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        (*matriz)[i] = (int*)malloc(m * sizeof(int)); // reserva de memoria para columnas
        if ((*matriz)[i] == NULL) {
            // Si hay un error al reservar, liberar la memoria ya reservada
            for (int j = 0; j < i; j++) {
                free((*matriz)[j]); // liberar memoria 
            }
            free(*matriz); //liberar memoria
            return -1; // Error al reservar memoria para las columnas
        }
    }
    return 0; // Indica 0 si no hay errores
}


void imprimirMatriz(int** matriz, int n, int m) {
    // funcion para imprimir matriz, la recorre e imprime
    printf("Matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void insertarEnMatriz(int** matriz, int n, int m, int* vector, int tamano) {
    // funcion para insertar valores nm en las coordenadas nxm
    for (int i = 0; i < tamano; i++) {
        int fila = vector[i * 2];   // par
        int columna = vector[i * 2 + 1]; // impar       
        int numero = concatenarNumeros(fila, columna); // concatenar n y m 

        // Verificar si las coordenadas están dentro de los límites de la matriz
        if (fila >= 0 && fila < n && columna >= 0 && columna < m) {
            matriz[fila][columna] = numero;  
        } else {
            // manejo  si n y m si estan fuera de los limites. Este caso fue para debug
            printf("Coordenadas (%d, %d) fuera de los límites de la matriz.\n", fila, columna);
        }
    }
}

int main() {
    // declaracion de variables 
    int n, m;
    int *vector = NULL;
    int tamano = 0;
    int nmax = 0;
    int mmax = 0;

    while (1) { // mantener while hasta poner condicion de parada
        printf("Ingrese 'd' para caso default o digite pares de números separados por coma a la vez de la forma n,m. Luego, ingrese -,- para continuar. o ): ");

        // Leer la entrada del usuario
        char entrada[10];
        scanf("%s", entrada);

        // Comprobar si se ingresó "d" para caso default
        if (entrada[0] == 'd') {
            printf("El caso default genera 5 pares de numeros alestorios de 0-9\n");
            srand(time(NULL));

            // Asignar memoria para el vector
            vector = realloc(vector, (tamano + 5) * sizeof(int) * 2);

            // Generar y mostrar 6 pares de números aleatorios entre 0 y 19
            printf("Valores generados:\n");
            for (int i = tamano; i < tamano + 5; i++) {
                int numeroAleatorioN = rand() % 10;  // Genera números entre 0 y 19
                int numeroAleatorioM = rand() % 10;  // Genera números entre 0 y 19
                vector[i * 2] = numeroAleatorioN;
                vector[i * 2 + 1] = numeroAleatorioM;
                printf("(%d, %d)\n", vector[i * 2], vector[i * 2 + 1]); // imprime numeros generados
            }

            tamano += 5;  // Actualizar el tamaño del vector

            // Actualizar los máximos si es necesario para caso default
            for (int i = 0; i < tamano; i++) {
                n = vector[i * 2];
                m = vector[i * 2 + 1];

                if (n > nmax) { //nmax
                    nmax = n;
                }
                if (m > mmax) { //mmax
                    mmax = m;
                }
            }
            printf("Ingrese -,- para continuar\n\n"); // indicacion para ejecutar el programa
        }

        // Comprobar si se ingresó "-,-" para continuar, condicion de parada del while
        if (entrada[0] == '-' && entrada[1] == ',' && entrada[2] == '-') {
            break;
        }

        // Convertir la entrada a números enteros
        sscanf(entrada, "%d,%d", &n, &m); // char --> int

        // Actualizar los máximos si es necesario
        if (n > nmax){
             nmax = n;
        }
        if (m > mmax){
            mmax = m;
        }
        // Incrementar el tamaño del vector
        tamano++;

        // Append en vector dinámico. En C no existe funcion de append
        vector = realloc(vector, tamano * sizeof(int) * 2);
        vector[(tamano - 1) * 2] = n;
        vector[(tamano - 1) * 2 + 1] = m;
    }

    int **matriz;
    // llamado a funcion para reservar memoria 
    int resultado = reservarMemoria(&matriz, nmax + 1, mmax + 1); // Sumar 1 para incluir el 0

    if (resultado == 0) {
        printf("Memoria reservada exitosamente.\n");

        // Imprimir la matriz antes de insertar los valores
        printf("Matriz antes de insertar valores:\n");
        imprimirMatriz(matriz, nmax + 1, mmax + 1);

        // Insertar valores en la matriz desde el vector
        insertarEnMatriz(matriz, nmax + 1, mmax + 1, vector, tamano);

        // Imprimir la matriz después de insertar los valores
        printf("Matriz después de insertar valores:\n");
        imprimirMatriz(matriz, nmax + 1, mmax + 1);

        // Mostrar las direcciones de memoria de cada fila
        printf("Direcciones de memoria de cada fila:\n");
        for (int i = 0; i < nmax + 1; i++) {
            printf("Fila %d: %p\n", i, (void*)matriz[i]);
        }

        // Liberar la memoria al finalizar
        for (int i = 0; i < nmax + 1; i++) {
            free(matriz[i]);
        }
        free(matriz);
    } else {
        printf("Error al reservar memoria.\n");
    }

    free(vector);
    return 0;
}
