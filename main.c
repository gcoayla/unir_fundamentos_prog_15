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
void imprimirRegistros(Gasolinera gasolineras[], int cantidad) {

// Función para mostrar los registros en formato de tabla
void mostrar_tabla(Gasolinera gasolineras[], int cantidad) {
    if (cantidad <= 0) {
        printf("No hay registros de gasolineras para mostrar.\n");
        return;  // Salida temprana si no hay registros
    }

    printf("=========================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-10s | %-25s | %-6s | %-20s | %-8s | %-8s | %-8s |\n",
           "ID", "Provincia", "Localidad", "C.Postal", "Dirección", "Margen", "Rótulo", "Gas95", "Gas98", "GasoleoA");
    printf("=========================================================================================================================\n");

    for (int i = 0; i < cantidad; i++) {
        printf("| %-5d | %-15.15s | %-20.20s | %-10.10s | %-25.25s | %-6s | %-20.20s | %-8.2f | %-8.2f | %-8.2f |\n",
               gasolineras[i].id,
               gasolineras[i].provincia,
               gasolineras[i].localidad,
               gasolineras[i].codigo_postal,
               gasolineras[i].direccion,
               gasolineras[i].margen,
               gasolineras[i].rotulo,
               gasolineras[i].gasolina95,
               gasolineras[i].gasolina98,
               gasolineras[i].gasoleoA);
    }

    printf("=========================================================================================================================\n");
}

int main() {
    Gasolinera gasolineras[] = {
        {1, "Madrid", "Madrid", "28001", "Calle Mayor", "D", "Repsol", 1.56, 1.65, 1.48},
        {2, "Barcelona", "Barcelona", "08001", "Rambla", "I", "Cepsa", 1.52, 1.62, 1.45}
    };

    int cantidad = sizeof(gasolineras) / sizeof(Gasolinera);

    printf("Tabla de registros de gasolineras:\n\n");
    mostrar_tabla(gasolineras, cantidad);

    return 0;
    }

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
