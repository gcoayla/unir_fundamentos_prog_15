#include <stdio.h>
#define NOMBRE_FICHERO "gasolina.csv"

typedef struct {
    int id;
    char provincia[20];
    char localidad[20];
    char postal[4];
    char direccion[60];
    char margen;
    char rotulo[60];
    float gasolina95;
    float gasolina98;
    float gasoleoA;
} RegistroGasolina;

// ----------------- Funciones de utilidad

// Solicita un numero al usuario y se asegura que el valor introducido sea un numero entero
int obtenerEntero() {

}

// Solicita un numero al usuario y se asegura que el valor introducido sea un numero flotante
int obtenerFlotanteO1Negativo() {

}

// ----------------- Problemas
// Problema 1 imprimir todos los registros de la tabla
void imprimirRegistros() {

}

// Problema 2 imprimir registro por ID
void imprimirRegistroPorId() {

}

// Problema 3 modificar registro por ID
void modificarRegistroPorId() {

}

// Problema 4 calcular el precio maximo (gasolina 95)
void calcularPrecioMaximo() {

}

// Problema 5 calcular el precio minimo (gasolina 95)
void calcularPrecioMinimo() {

}

// Problema 6 imprimir todos los registros ordenados por precio
void imprimirRegistrosOrdenados() {

}

int main(void) {
    FILE *fichero;
    fichero = fopen(NOMBRE_FICHERO, "r");

    RegistroGasolina registros[180];

    if (fichero == NULL) {
        printf("Error al abrir el fichero");
        return -1;
    } else {

    }

    fclose(fichero);
    return 0;
}
