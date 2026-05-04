#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTOS 10
#define MAX_LONGITUD_NOMBRE 50

void ingresarDatos(char nombres[][MAX_LONGITUD_NOMBRE], float precios[], int cantidad);
float calcularTotal(float precios[], int cantidad);
void encontrarExtremos(char nombres[][MAX_LONGITUD_NOMBRE], float precios[], int cantidad);
float calcularPromedio(float precios[], int cantidad);
void buscarProducto(char nombres[][MAX_LONGITUD_NOMBRE], float precios[], int cantidad, char nombreBuscado[]);

int main() {
    char nombres[MAX_PRODUCTOS][MAX_LONGITUD_NOMBRE];
    float precios[MAX_PRODUCTOS];
    int cantidad = 0;
    char nombreBusqueda[MAX_LONGITUD_NOMBRE];
    char opcion;

    printf("--- GESTION DE INVENTARIO ---\n");
    
    do {
        printf("¿Cuantos productos desea registrar? (1 - %d): ", MAX_PRODUCTOS);
        if (scanf("%d", &cantidad) != 1) {
            printf("Error: Ingrese un numero entero.\n");
            while(getchar() != '\n'); // Limpiar buffer en caso de que metan letras
            continue;
        }
        if (cantidad < 1 || cantidad > MAX_PRODUCTOS) {
            printf("Cantidad fuera de rango. Intente de nuevo.\n");
        }
    } while (cantidad < 1 || cantidad > MAX_PRODUCTOS);

    ingresarDatos(nombres, precios, cantidad);

    printf("\n--- RESULTADOS GENERALES ---\n");
    printf("Precio total del inventario: $%.2f\n", calcularTotal(precios, cantidad));
    printf("Precio promedio: $%.2f\n", calcularPromedio(precios, cantidad));
    encontrarExtremos(nombres, precios, cantidad);

    do {
        printf("\n--- BUSQUEDA DE PRODUCTO ---\n");
        printf("Ingrese el nombre del producto a buscar: ");
        scanf("%s", nombreBusqueda);
        
        buscarProducto(nombres, precios, cantidad, nombreBusqueda);

        // Validación estricta de la respuesta 's' o 'n'
        do {
            printf("\n¿Desea buscar otro producto? (s/n): ");
            scanf(" %c", &opcion);
            opcion = tolower(opcion); // Normalizar a minúscula

            if (opcion != 's' && opcion != 'n') {
                printf("Opcion no valida. Por favor, ingrese 's' para si o 'n' para no.\n");
            }
        } while (opcion != 's' && opcion != 'n');

    } while (opcion == 's'); 

    printf("\nCerrando sistema... ¡Buen dia!\n");

    return 0;
}

void ingresarDatos(char nombres[][MAX_LONGITUD_NOMBRE], float precios[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("\nProducto %d:\n", i + 1);
        printf("  Nombre: ");
        scanf("%s", nombres[i]);
        
        // Validación de precio (no puede ser negativo)[cite: 1]
        do {
            printf("  Precio: ");
            if (scanf("%f", &precios[i]) != 1) {
                printf("    Error: Ingrese un valor numerico.\n");
                while(getchar() != '\n');
                precios[i] = -1; // Forzar repetición del ciclo
            } else if (precios[i] < 0) {
                printf("    El precio no puede ser negativo.\n");
            }
        } while (precios[i] < 0);
    }
}

float calcularTotal(float precios[], int cantidad) {
    float total = 0.0;
    for (int i = 0; i < cantidad; i++) {
        total += precios[i];
    }
    return total;
}

void encontrarExtremos(char nombres[][MAX_LONGITUD_NOMBRE], float precios[], int cantidad) {
    if (cantidad <= 0) return;
    int indiceMayor = 0, indiceMenor = 0;
    for (int i = 1; i < cantidad; i++) {
        if (precios[i] > precios[indiceMayor]) indiceMayor = i;
        if (precios[i] < precios[indiceMenor]) indiceMenor = i;
    }
    printf("Producto mas caro: %s ($%.2f)\n", nombres[indiceMayor], precios[indiceMayor]);
    printf("Producto mas barato: %s ($%.2f)\n", nombres[indiceMenor], precios[indiceMenor]);
}

float calcularPromedio(float precios[], int cantidad) {
    return (cantidad == 0) ? 0 : calcularTotal(precios, cantidad) / cantidad;
}

void buscarProducto(char nombres[][MAX_LONGITUD_NOMBRE], float precios[], int cantidad, char nombreBuscado[]) {
    int encontrado = 0;
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            printf(">> [ENCONTRADO] %s cuesta $%.2f\n", nombres[i], precios[i]);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf(">> [ERROR] El producto '%s' no existe.\n", nombreBuscado);
}