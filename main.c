#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_RECORDS 1000

typedef struct {
    int id;
    char provincia[50];
    char localidad[50];
    char codigo_postal[10];
    char direccion[100];
    char margen[2];
    char rotulo[50];
    float gasolina95;
    float gasolina98;
    float gasoleoA;
} Gasolinera;

// ----------------- Funciones de utilidad

int cargar_datos(const char *filename, Gasolinera gasolineras[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No se pudo abrir el archivo: %s. Verifique que existe y tiene permisos de lectura.\n", filename);
        return -1;
    }

    char buffer[MAX_LINE];
    int count = 0;

    while (fgets(buffer, MAX_LINE, file) && count < MAX_RECORDS) {
        if (count == 0) {
            count++;
            continue;
        }

        sscanf(buffer, "%d,%49[^,],%49[^,],%9[^,],%99[^,],%1[^,],%49[^,],%f,%f,%f",
               &gasolineras[count - 1].id,
               gasolineras[count - 1].provincia,
               gasolineras[count - 1].localidad,
               gasolineras[count - 1].codigo_postal,
               gasolineras[count - 1].direccion,
               gasolineras[count - 1].margen,
               gasolineras[count - 1].rotulo,
               &gasolineras[count - 1].gasolina95,
               &gasolineras[count - 1].gasolina98,
               &gasolineras[count - 1].gasoleoA);

        count++;
    }

    fclose(file);
    return count - 1;
}

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
    Gasolinera gasolineras[MAX_RECORDS];
    char ruta[256];
    printf("Ingrese la ruta del archivo CSV: ");
    scanf("%255s", ruta);

    int total_gasolineras = cargar_datos(ruta, gasolineras);
    if (total_gasolineras < 0) {
        return 1;
    }

    printf("Archivo cargado correctamente. Total de registros: %d\\n", total_gasolineras);
    return 0;
}
