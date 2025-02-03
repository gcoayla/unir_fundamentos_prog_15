#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024
#define MAX_RECORDS 1000
#define FILE_NAME "../gasolineras.txt"

void menu();

//Objeto Gasolinera para almacenar la informacion
typedef struct {
    int id;
    char provincia[50];
    char localidad[50];
    int codigo_postal;
    char direccion[100];
    char margen[2];
    char rotulo[50];
    float gasolina95;
    float gasolina98;
    float gasoleoA;
} Gasolinera;

// ----------------- Funciones de utilidad

int cargar_datos(const char *filename, Gasolinera gasolineras[]) {

    FILE *file = fopen(FILE_NAME, "r");


    if (file == NULL) {
        printf("No se pudo abrir el archivo: %s. Verifique que existe y tiene permisos de lectura.\n", FILE_NAME);
        return -1;
    }

    int num_registros = 0;
    char linea[1000];
    while (fgets(linea, sizeof(linea), file) != NULL) {
        num_registros++;
    }

    rewind(file);

    int i = 0;
    while (fgets(linea, sizeof(linea), file) != NULL) {
        char* token = strtok(linea, ";");

        gasolineras[i].id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(gasolineras[i].provincia, token);

        token = strtok(NULL, ";");
        strcpy(gasolineras[i].localidad, token);

        token = strtok(NULL, ";");
        gasolineras[i].codigo_postal = atoi(token);

        token = strtok(NULL, ";");
        strcpy(gasolineras[i].direccion, token);

        token = strtok(NULL, ";");
        strcpy(gasolineras[i].margen, token);

        token = strtok(NULL, ";");
        strcpy(gasolineras[i].rotulo, token);

        token = strtok(NULL, ";");
        gasolineras[i].gasolina95 = atof(token);

        token = strtok(NULL, ";");
        gasolineras[i].gasolina98 = atof(token);

        token = strtok(NULL, ";");
        gasolineras[i].gasoleoA = atof(token);

        i++;
    }


    fclose(file);
    return num_registros;
}

// Función para verificar si una cadena contiene solo dígitos
bool contieneSoloDigitos(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false; // Carácter no es un dígito
        }
    }
    return true; // Todos los caracteres son dígitos
}

// Solicita un numero al usuario y se asegura que el valor introducido sea un numero entero positivo
int obtenerEntero() {
    char input[20];
    int num;

    while (true) {
        if (scanf("%19s", input) != 1) {
            // Limpiar el buffer de entrada en caso de error de lectura
            while (getchar() != '\n');
            printf("Entrada invalida.\n");
            continue;
        }

        if (!contieneSoloDigitos(input)) {
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }

        if (sscanf(input, "%d", &num) != 1) {
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }

        if (num <= 0) {
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }

        return num;
    }
}

// Función para verificar si una cadena contiene solo dígitos y un punto decimal
bool contieneSoloDigitosYUnPunto(const char *str) {
    int puntos = 0;

    if (str[0] == '-') {
        str++; // Avanzar al siguiente carácter
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            puntos++;
            if (puntos > 1) {
                return false;
            }
        } else if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

// Solicita un numero al usuario y se asegura que el valor introducido sea un numero flotante
float obtenerFlotanteO1Negativo() {
    char input[30];
    float num;

    while (true) {
        printf("Ingrese un numero flotante positivo o -1: ");
        if (scanf("%29s", input) != 1) {
            while (getchar() != '\n');
            printf("Entrada invalida. Intente de nuevo \n");
            continue;
        }

        if (!contieneSoloDigitosYUnPunto(input)) {
            printf("Entrada invalida. Ingrese solo digitos y un punto decimal o -1.\n");
            continue;
        }

        if (sscanf(input, "%f", &num) != 1) {
            printf("Entrada invalida. No se pudo convertir a flotante.\n");
            continue;
        }

        if (num > 0 || num == -1) {
            return num;
        } else {
            printf("Entrada invalida. Ingrese un numero positivo o -1.\n");
        }
    }
}

// ----------------- Problemas
// Problema 1 imprimir todos los registros de la tabla

// Función para mostrar los registros en formato de tabla
void mostrar_tabla(Gasolinera gasolineras[], int cantidad) {
    if (cantidad <= 0) {
        printf("No hay registros de gasolineras para mostrar.\n");
        return;  // Salida temprana si no hay registros
    }

    printf("=========================================================================================================================\n");
    printf("| %-5s | %-15s | %-20s | %-5s | %-50s | %-6s | %-20s | %-8s | %-8s | %-8s |\n",
           "ID", "Provincia", "Localidad", "C.Postal", "Dirección", "Margen", "Rótulo", "Gas95", "Gas98", "GasoleoA");
    printf("=========================================================================================================================\n");

    for (int i = 0; i < cantidad; i++) {
        printf("| %-5d | %-15.15s | %-20.20s | %-d | %-50.50s | %-6s | %-20.20s | %-8.5f | %-8.5f | %-8.5f |\n",
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


// Problema 2 imprimir registro por ID
void imprimirRegistroPorId(Gasolinera gasolineras[], int count, int id) {
    for (int i = 0; i < count; i++) {  // bucle para recorrer la lista
        if (gasolineras[i].id == id) {
            printf("\nN.o %d: %s\n", gasolineras[i].id, gasolineras[i].rotulo);
            printf("• %s (%s, %s).\n", gasolineras[i].direccion, gasolineras[i].localidad, gasolineras[i].provincia);
            printf("• Gasolina 95: %.6f\n", gasolineras[i].gasolina95);
            printf("• Gasolina 98: %.6f\n", gasolineras[i].gasolina98);
            printf("• Gasoleo A: %.6f\n", gasolineras[i].gasoleoA);
            printf("--------------------------------- \n");
            return;
        }
    }
}
// Problema 3 modificar registro por ID
void modificarRegistroPorId(Gasolinera gasolineras[], int cantidad, int id) {
    for (int i = 0; i < cantidad; i++) {
        if (gasolineras[i].id == id) {
            // Si encontramos la gasolinera por ID, solo se permiten modificaciones en los precios de los combustibles
            printf("Gasolinera encontrada: %d\n", gasolineras[i].id);
            printf("Dirección: %s\n", gasolineras[i].direccion);
            printf("Rótulo: %s\n", gasolineras[i].rotulo);

            // Solicitar los nuevos registros
            printf("Introduzca el nuevo precio para Gasolina95 (actual: %.6f): ", gasolineras[i].gasolina95);
            scanf("%f", &gasolineras[i].gasolina95);

            printf("Introduzca el nuevo precio para Gasolina98 (actual: %.6f): ", gasolineras[i].gasolina98);
            scanf("%f", &gasolineras[i].gasolina98);

            printf("Introduzca el nuevo precio para Gasóleo A (actual: %.6f): ", gasolineras[i].gasoleoA);
            scanf("%f", &gasolineras[i].gasoleoA);

            printf("Registro de la gasolinera con ID %d modificado correctamente.\n", id);
            printf("--------------------------------- \n");
            return;
        }
    }

}

// Problema 4 calcular el precio maximo (gasolina 95)
void calcularPrecioMaximo(Gasolinera gasolineras[], int cantidad) {
    float maximo = -1; // Inicializamos con un valor bajo

    for (int i = 0; i < cantidad; i++) {
        if (gasolineras[i].gasolina95 > maximo) { // Buscar el valor más alto
            maximo = gasolineras[i].gasolina95;
        }
    }

    if (maximo == -1) {
        printf("No se encontraron valores válidos en la lista de gasolineras.\n");
    } else {
        printf("El valor más alto de la gasolina 95 es: %.2f\n", maximo);
    }
    printf("--------------------------------- \n");
}


// Problema 5 calcular el precio minimo (gasolina 95)
void calcularPrecioMinimo(Gasolinera gasolineras[], int cantidad) {
    float minimo = 1024; // Inicializamos con un valor alto

    for (int i = 0; i < cantidad; i++) {
        if (gasolineras[i].gasolina95 > 0 && gasolineras[i].gasolina95 < minimo) {
            minimo = gasolineras[i].gasolina95; // Buscar el valor más bajo
        }
    }

    if (minimo == 1024) {
        printf("No se encontraron valores válidos en la lista de gasolineras.\n");
    } else {
        printf("El valor más bajo de la gasolina 95 es: %.2f\n", minimo);
    }
    printf("--------------------------------- \n");
}

// Problema 6 imprimir todos los registros ordenados por precio
void imprimirRegistrosOrdenados(Gasolinera gasolineras[], int cantidad) {

}

void menu(Gasolinera gasolineras[], int cantidad) {
    printf("Seleccione una opcion, ingrese un numero entero entre 1 - 7 \n");
    printf("1- Mostrar todos los registros \n");
    printf("2- Mostrar registro a partir de su ID \n");
    printf("3- Modificar registro a partir de su ID \n");
    printf("4- Calcular el precio maximo (gasolina 95) \n");
    printf("5- Calcular el precio minimo (gasolina 95) \n");
    printf("6- Mostrar todos los registros ordenados por precio (gasolina 95) \n");
    printf("7- Salir \n");

    int input = 0;

    while (input < 1 || input > 8) {
        printf("Ingrese un numero entero entre 1 - 7 \n");
        input = obtenerEntero();
    }

    if (input == 1) {
        mostrar_tabla(gasolineras, cantidad);
        menu(gasolineras, cantidad);
    } else if (input == 2) {
        int id = 0;
        while (id < 1 || id > cantidad) {
            printf("Ingrese un id entero entre 1 - %d \n", cantidad);
            id = obtenerEntero();
        }

        imprimirRegistroPorId(gasolineras, cantidad, id );
        menu(gasolineras, cantidad);
    } else if (input == 3) {
        int id = 0;
        while (id < 1 || id > cantidad) {
            printf("Ingrese un id entero entre 1 - %d \n", cantidad);
            id = obtenerEntero();
        }

        modificarRegistroPorId(gasolineras, cantidad, id );
        menu(gasolineras, cantidad);
    } else if (input == 4) {
        calcularPrecioMaximo(gasolineras, cantidad);
        menu(gasolineras, cantidad);
    } else if (input == 5) {
        calcularPrecioMinimo(gasolineras, cantidad);
        menu(gasolineras, cantidad);
    } else if (input == 6) {
        imprimirRegistrosOrdenados(gasolineras, cantidad);
        menu(gasolineras, cantidad);
    } else if (input == 7) {
        return;
    }
}

int main(void) {
    Gasolinera gasolineras[MAX_RECORDS];
    char ruta[256];
    printf("Ingrese la ruta del archivo txt: ");
    scanf("%255s", ruta);

    int total_gasolineras = cargar_datos(ruta, gasolineras);

    if (total_gasolineras == -1) {
        return -1;
    }

    menu(gasolineras, total_gasolineras);

    return 0;
}
