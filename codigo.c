#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_INTERSECCIONES 100

typedef struct {
    char nombre[50];
    double latitud;
    double longitud;
} InterseccionCoordenadas;

typedef struct {
    int distancia; // Distancia en metros
} Conexion;

typedef struct {
    InterseccionCoordenadas intersecciones[MAX_INTERSECCIONES];
    Conexion conexiones[MAX_INTERSECCIONES][MAX_INTERSECCIONES];
    int numIntersecciones;
} GrafoDirigido;

void inicializarGrafo(GrafoDirigido *grafo) {
    grafo->numIntersecciones = 0;
}

void agregarInterseccion(GrafoDirigido *grafo, char nombre[], double latitud, double longitud) {
    if (grafo->numIntersecciones < MAX_INTERSECCIONES) {
        strcpy(grafo->intersecciones[grafo->numIntersecciones].nombre, nombre);
        grafo->intersecciones[grafo->numIntersecciones].latitud = latitud;
        grafo->intersecciones[grafo->numIntersecciones].longitud = longitud;
        grafo->numIntersecciones++;
    } else {
        fprintf(stderr, "Demasiadas intersecciones. Ajusta MAX_INTERSECCIONES.\n");
        exit(EXIT_FAILURE);
    }
}

void leerInterseccionesDesdeArchivo(GrafoDirigido *grafo, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de intersecciones");
        exit(EXIT_FAILURE);
    }

    char nombre[50];
    double latitud, longitud;
    while (fscanf(archivo, "%s %lf %lf", nombre, &latitud, &longitud) == 3) {
        agregarInterseccion(grafo, nombre, latitud, longitud);
    }

    fclose(archivo);
}

void agregarConexion(GrafoDirigido *grafo, int indice1, int indice2, int distancia) {
    grafo->conexiones[indice1][indice2].distancia = distancia;
}

void leerConexionesDesdeArchivo(GrafoDirigido *grafo, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de conexiones");
        exit(EXIT_FAILURE);
    }

    char interseccion1[50], interseccion2[50];
    int distancia;

    while (fscanf(archivo, "%s %s %d", interseccion1, interseccion2, &distancia) == 3) {
        int indice1 = obtenerIndiceInterseccion(grafo, interseccion1);
        int indice2 = obtenerIndiceInterseccion(grafo, interseccion2);

        if (indice1 != -1 && indice2 != -1) {
            agregarConexion(grafo, indice1, indice2, distancia);
        } else {
            fprintf(stderr, "Error: Intersecciones no encontradas.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
}

void dijkstra(GrafoDirigido *grafo, int inicio, int fin) {
    // Implementación de Dijkstra
    // ...
}

void manejarCasosEspeciales(GrafoDirigido *grafo) {
    // Lógica específica para calles y direcciones del centro de Concepción
    // ...
}

void imprimirRuta(GrafoDirigido *grafo, int *padres, int inicio, int fin) {
    // Función para imprimir la ruta
    // ...
}

void solicitarArchivo(char *nombreArchivo, const char *tipo) {
    printf("Ingrese el nombre del archivo de %s: ", tipo);
    scanf("%s", nombreArchivo);
}

int obtenerIndiceInterseccion(GrafoDirigido *grafo, char nombre[]) {
    for (int i = 0; i < grafo->numIntersecciones; i++) {
        if (strcmp(grafo->intersecciones[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    GrafoDirigido grafo;
    inicializarGrafo(&grafo);

    char nombreArchivoIntersecciones[50];
    char nombreArchivoConexiones[50];
    char inicio[50], fin[50];

    solicitarArchivo(nombreArchivoIntersecciones, "intersecciones");
    solicitarArchivo(nombreArchivoConexiones, "conexiones");

    leerInterseccionesDesdeArchivo(&grafo, nombreArchivoIntersecciones);
    leerConexionesDesdeArchivo(&grafo, nombreArchivoConexiones);

    manejarCasosEspeciales(&grafo);

    printf("Ingrese el punto de inicio: ");
    scanf("%s", inicio);
    printf("Ingrese el punto de fin: ");
    scanf("%s", fin);

    int indiceInicio = obtenerIndiceInterseccion(&grafo, inicio);
    int indiceFin = obtenerIndiceInterseccion(&grafo, fin);

    if (indiceInicio == -1 || indiceFin == -1) {
        fprintf(stderr, "Error: Punto de inicio o fin no encontrado.\n");
        exit(EXIT_FAILURE);
    }

    dijkstra(&grafo, indiceInicio, indiceFin);

    return 0;
}