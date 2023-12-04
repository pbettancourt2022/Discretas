#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_INTERSECCIONES 112
#define INF 9999999 // Valor infinito para representar distancias desconocidas
#define V 112
typedef struct {
    char nombre[50];
    int numero;
} Interseccion;

typedef struct {
    int distancia; // Distancia en metros
} Conexion;

typedef struct {
    Interseccion intersecciones[MAX_INTERSECCIONES];
    Conexion conexiones[MAX_INTERSECCIONES][MAX_INTERSECCIONES];
    int numIntersecciones;
} GrafoDirigido;

int matriz[V][V]; // Matriz de adyacencia para representar el grafo dirigido
int distancia[V]; // Almacena la distancia más corta desde el vértice de origen
int visitado[V]; // Indica si un vértice ha sido visitado o no

// Función para encontrar el vértice con la distancia mínima
int minDistancia(int distancia[], int visitado[]) {
    int min = INT_MAX, min_indice;

    for (int v = 0; v < V; v++) {
        if (visitado[v] == 0 && distancia[v] <= min) {
            min = distancia[v];
            min_indice = v;
        }
    }
    return min_indice;
}

// Función para imprimir la solución (ruta más corta desde el vértice de origen)
void imprimirSolucion(int distancia[], int origen) {
    printf("Intersección \t Distancia desde el origen\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, distancia[i]);
    }
}

// Algoritmo de Dijkstra para encontrar la ruta más corta
void dijkstra(int matriz[V][V], int origen) {
    for (int i = 0; i < V; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = 0;
    }

    distancia[origen] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(distancia, visitado);
        visitado[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && matriz[u][v] && distancia[u] != INT_MAX &&
                distancia[u] + matriz[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + matriz[u][v];
            }
        }
    }

    imprimirSolucion(distancia, origen);
}

int obtenerNumeroInterseccion(Interseccion intersecciones[], int numIntersecciones, char nombre[]) {
    for (int i = 0; i < numIntersecciones; i++) {
        if (strcmp(intersecciones[i].nombre, nombre) == 0) {
            return intersecciones[i].numero;
        }
    }
    return -1; // Si no se encuentra la intersección
}

int main() {
    GrafoDirigido grafo;
    char entrada[50];
    char origen[50];
    char destino[50];
    char paso[50];
    int numOrigen, numDestino, numPaso;
    FILE *archivo = fopen("intersecciones.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de intersecciones");
        return EXIT_FAILURE;
    }

    Interseccion intersecciones[MAX_INTERSECCIONES];
    int numIntersecciones = 0;

    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = 0; // Elimina el carácter de nueva línea

        int numero = obtenerNumeroInterseccion(intersecciones, numIntersecciones, linea);
        if (numero == -1) {
            if (numIntersecciones < MAX_INTERSECCIONES) {
                strcpy(intersecciones[numIntersecciones].nombre, linea);
                intersecciones[numIntersecciones].numero = numIntersecciones;
                numIntersecciones++;
            } else {
                fprintf(stderr, "Demasiadas intersecciones. Ajusta MAX_INTERSECCIONES.\n");
                return EXIT_FAILURE;
            }
        }
    }

    fclose(archivo);
    int matriz [112][112];
    for (int j = 0; j < 111; j++){
        if(j==0){
            matriz[j][j+1]=1;
        }
        else if(((j>0)&&(j<13))&&(j%2!=0)){
            matriz[j][j-1]=1;
            matriz[j][j+1]=1;
            matriz[j][j+14]=1;
        }
        else if ((j<13)&&(j%2==0)){
            matriz[j][j-1]=1;
            matriz[j][j+1]=1;
        }
        else if(j==13){
            matriz[j][j-1]=1;
            matriz[j][j+14]=1;
        }
        //Filas 14 42 70 -------
        else if ((j==14)||(j==42)||(j==70)){
            matriz[j][j+1]=1;
            matriz[j][j-14]=1;
        }
        else if ((((j>14)&&(j<27))||((j>42)&&(j<55))||((j>70)&&(j<83)))&&(j%2!=0)&&(j!=21)&&(j!=49)&&(j!=81)){
            matriz[j][j+1]=1;
            matriz[j][j+14]=1;
        }
        else if ((j==21)){
            matriz[j][j+1]=1;
        }
        else if ((j==49)){
            matriz[j][j+14]=1;
        }
        else if ((j==81)){
            matriz[j][j+1]=1;
            matriz[j][j+14]=1;
            matriz[j][66]=1;
        }
        else if ((((j>14)&&(j<27))||((j>42)&&(j<55))||((j>70)&&(j<83)))&&(j%2==0)&&(j!=50)){
            matriz[j][j+1]=1;
            matriz[j][j-14]=1;
        }
        else if (j==50){
            matriz[j][j-14]=1;
        }
        else if ((j==27)||(j==55)){
            matriz[j][j+14]=1;
            matriz[j][j-14]=1;
        }
        else if (j==83){
            matriz[j][j+14]=1;
        }
        //-----------
        //Filas 28 56 84 -------
        else if ((j==28)||(j==56)||(j==84)){
            matriz[j][j-14]=1;
        }
        else if ((((j>28)&&(j<41))||((j>56)&&(j<69))||((j>84)&&(j<97)))&&(j%2!=0)&&(j!=35)){
            matriz[j][j-1]=1;
            matriz[j][j+14]=1;
        }
        else if (j==35){
            matriz[j][j-1]=1;
        }
        else if ((((j>28)&&(j<41))||((j>56)&&(j<69))||((j>84)&&(j<97)))&&(j%2==0)&&(j!=96)){
            matriz[j][j-1]=1;
            matriz[j][j-14]=1;
        }
        else if (j==96){
            matriz[j][j-1]=1;
            matriz[j][j-14]=1;
            matriz[j][81]=1;
        }
        else if ((j==41)||(j==69)){
            matriz[j][j-1]=1;
            matriz[j][j-14]=1;
            matriz[j][j+14]=1;
        }
        else if (j==97){
            matriz[j][j+14]=1;
        }
        //--------
        else if (j==98){
            matriz[j][j-14]=1;
            matriz[j][j+1]=1;
        }
        else if(((j>98)&&(j<111))&&(j%2!=0)){
            matriz[j][j-1]=1;
            matriz[j][j+1]=1;
        }
        else if(((j>98)&&(j<111))&&(j%2==0)){
            matriz[j][j-1]=1;
            matriz[j][j+1]=1;
            matriz[j][j-14]=1;
        }
        else if (j==111){
            matriz[j][j-1]=1;
            matriz[j][96]=1;
        }
    }
    printf("Ingrese tres lugares y sus números separados por espacios entre comillas (Ejemplo: \"Orompello 100\" \"Rengo 400\" \"Paicavi 600\"): ");
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "\"%s %d\" \"%s %d\" \"%s %d\"", origen, &numOrigen, destino, &numDestino, paso, &numPaso);

    dijkstra(matriz, 0);

    return 0;
}