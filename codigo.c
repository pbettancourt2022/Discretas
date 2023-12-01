#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_INTERSECCIONES 100
#define INF 9999999 // Valor infinito para representar distancias desconocidas

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
    int distancias[MAX_INTERSECCIONES]; // Almacena las distancias más cortas
    bool visitado[MAX_INTERSECCIONES]; // Marca los nodos visitados
    int padres[MAX_INTERSECCIONES]; // Almacena los nodos padres

    // Inicializar distancias y nodos visitados
    for (int i = 0; i < grafo->numIntersecciones; ++i) {
        distancias[i] = INF;
        visitado[i] = false;
        padres[i] = -1; // Valor nulo para los nodos padres
    }

    // La distancia al nodo de inicio es 0
    distancias[inicio] = 0;

    for (int count = 0; count < grafo->numIntersecciones - 1; ++count) {
        // Encontrar el nodo con la distancia más corta aún no visitado
        int u, min_distancia = INF;
        for (int v = 0; v < grafo->numIntersecciones; ++v) {
            if (visitado[v] == false && distancias[v] <= min_distancia) {
                min_distancia = distancias[v];
                u = v;
            }
        }

        // Marcar el nodo seleccionado como visitado
        visitado[u] = true;

        // Actualizar las distancias a los nodos adyacentes si son menores a través de u
        for (int v = 0; v < grafo->numIntersecciones; ++v) {
            if (!visitado[v] && grafo->conexiones[u][v].distancia &&
                distancias[u] != INF && distancias[u] + grafo->conexiones[u][v].distancia < distancias[v]) {
                distancias[v] = distancias[u] + grafo->conexiones[u][v].distancia;
                padres[v] = u; // Actualizar el nodo padre
            }
        }
    }

    // Imprimir la ruta más corta si hay un camino desde el inicio al fin
    if (distancias[fin] != INF) {
        printf("La distancia más corta dessde %s hasta %s es: %d metros\n", grafo->intersecciones[inicio].nombre, grafo->intersecciones[fin].nombre, distancias[fin]);

        printf("La ruta más corta es:\n");
        int camino[MAX_INTERSECCIONES], longitud_camino = 0;
        for (int i = fin; i != -1; i = padres[i]) {
            camino[longitud_camino++] = i;
        }

        // Imprimir la ruta inversa (del fin al inicio)
        for (int i = longitud_camino - 1; i >= 0; --i) {
            printf("%s", grafo->intersecciones[camino[i]].nombre);
            if (i != 0) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("No hay ruta disponible desde %s hasta %s\n", grafo->intersecciones[inicio].nombre, grafo->intersecciones[fin].nombre);
    }
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