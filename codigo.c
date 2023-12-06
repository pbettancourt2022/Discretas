#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX_INTERSECCIONES 112
#define V 112
#define NUM_CALLES 23
#define MAX_NOMBRE_CALLE 100

typedef struct {
    char nombre[50];
    int numero;
} Interseccion;

typedef struct {
    int distancia; 
} Conexion;

typedef struct {
    char nombre[MAX_NOMBRE_CALLE];
    int numero;
} Calle;

int matriz[V][V];
int distancia[V]; 
int visitado[V]; 

// Función para encontrar el vértice con la distancia mínima
int minDistancia(int distancia[], bool visitado[]) {
    int min = INT_MAX, min_indice;

    for (int v = 0; v < V; v++) {
        if (visitado[v] == false && distancia[v] <= min) {
            min = distancia[v];
            min_indice = v;
        }
    }
    return min_indice;
}

// Función para imprimir la ruta más corta desde el vértice de origen hasta el vértice de destino
void imprimirRuta(Interseccion intersecciones[], int padre[], int destino) {
    if (padre[destino] == -1) {
        printf("%s ", intersecciones[destino].nombre);
        return;
    }
    imprimirRuta(intersecciones, padre, padre[destino]);
    printf(" --> %s ", intersecciones[destino].nombre);
}

// Algoritmo de Dijkstra para encontrar la ruta más corta entre dos vértices
void dijkstra(Interseccion intersecciones[], int origen, int destino) {
    int distancia[V];
    bool visitado[V];
    int padre[V];

    for (int i = 0; i < V; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = false;
        padre[i] = -1;
    }

    distancia[origen] = 0;
    int contador = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(distancia, visitado);
        visitado[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && matriz[u][v] && distancia[u] != INT_MAX && distancia[u] + matriz[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + matriz[u][v];
                padre[v] = u;
                if ((u == 111 && v == 96) || (u == 96 && v == 81) || (u == 81 && v == 66)) {
                    contador++;
                }
            }
        }
    }


    if (distancia[destino] == INT_MAX) {
        printf("No hay ruta entre el origen y el destino\n");
        return;
    }

    printf("Ruta mas corta entre %s y %s: ", intersecciones[origen].nombre, intersecciones[destino].nombre);
    imprimirRuta(intersecciones, padre, destino);
    
    printf("\nDistancia: %d metros\n", ((distancia[destino] * 100 + contador * 41)));
}

int obtenerNumeroInterseccion(Interseccion intersecciones[], int numIntersecciones, char nombre[]) {
    for (int i = 0; i < numIntersecciones; i++) {
        if (strcmp(intersecciones[i].nombre, nombre) == 0) {
            return intersecciones[i].numero;
        }
    }
    return -1; // Si no se encuentra la intersección
}

// Función para asignar números a calles basadas en sus nombres
int obtenerNumeroCalle(const char nombreCalle[], Calle calles[], int numCalles) {
    for (int i = 0; i < numCalles; ++i) {
        if (strcmp(nombreCalle, calles[i].nombre) == 0) {
            return calles[i].numero;
        }
    }
    return -1; // Si el nombre de la calle no se encuentra
}

int obtenerNumeroVertice(int numcallegrafo, int numlugar){
    for(int i=0; i<=22;i++){
        
        if(numcallegrafo==i){
            if(i==22){
                for(int j=100;j<=400;j=j+100){
                    
                    if(((numlugar>=j)&&(numlugar<(j+100)))){
                        int a=((111)-(15*((j-100)/100)));
                        return a;
                    }
                }
            }
            else if (i<=13){
                
                for(int j=100;j<800;j=j+100){
                    
                    if(((numlugar>=j)&&(numlugar<(j+100)))){
                        int a=((112+i)-(14*(j/100)));
                        return a;
                    }
                }
            }
            else if (i>13){
                for(int j=0;j<1300;j=j+100){
                    if(((numlugar>=j)&&(numlugar<(j+100)))){
                        int a=((14*(i-14))+(j/100));
                        return a;
                    }
                }
            }
            
            
        }
    }
    return -1;
}

int main() {
    char entrada[50];
    char origen[50];
    char destino[50];
    char paso[50];
    int numOrigen, numDestino, numPaso;

    FILE *archivoCalles = fopen("Calles.txt", "r");
    if (archivoCalles == NULL) {
        perror("Error al abrir el archivo de calles");
        return EXIT_FAILURE;
    }

    Calle calles[NUM_CALLES];

    // Leer los nombres de las calles del archivo y asignar números a las calles
    for (int i = 0; i < NUM_CALLES; ++i) {
        if (fscanf(archivoCalles, "%s", calles[i].nombre) != 1) {
            printf("Error al leer el archivo de calles.\n");
            fclose(archivoCalles);
            return EXIT_FAILURE;
        }
        calles[i].numero = i; 
    }

    fclose(archivoCalles);

    FILE *archivo = fopen("intersecciones.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de intersecciones");
        return EXIT_FAILURE;
    }

    Interseccion intersecciones[MAX_INTERSECCIONES];
    int numIntersecciones = 0;

    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = 0; 

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
    for (int j = 0; j < 112; j++){
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
    
    printf("Ingrese lugar de origen y de destino, (es opcional colocar un lugar de paso, en el ejemplo es \"Paicavi 600\") y sus numeros separados por espacios entre comillas (Ejemplo: \"Orompello 100\" \"Rengo 400\" \"Paicavi 600\"): ");
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "\"%s %d\" \"%s %d\" \"%s %d\"", origen, &numOrigen, destino, &numDestino, paso, &numPaso);
    if (strcmp(destino, "Pedro_Aguirre_Cerda") == 0){
        numDestino=numDestino*10;
        
    }
    
    printf("\n");
    // Obtener el número de la calle basado en el nombre
    int calleorigen = obtenerNumeroCalle(origen, calles, NUM_CALLES);
    if (calleorigen == -1) {
        printf("Nombre de calle no válido origen.\n");
        return EXIT_FAILURE;
    }
    int calledestino = obtenerNumeroCalle(destino, calles, NUM_CALLES);
    if (calledestino == -1) {
        printf("Nombre de calle no válido destino.\n");
        return EXIT_FAILURE;
    }
    
    // Calcular el vértice correspondiente
    int verticeOrigen = obtenerNumeroVertice(calleorigen, numOrigen);
    int verticeDestino= obtenerNumeroVertice(calledestino, numDestino);

     int callepaso = obtenerNumeroCalle(paso, calles, NUM_CALLES);
    if (callepaso != -1) {
        int verticePaso= obtenerNumeroVertice(callepaso, numPaso);
        dijkstra(intersecciones, verticeOrigen, verticePaso);
        dijkstra(intersecciones, verticePaso, verticeDestino);
    }
    else{
        dijkstra(intersecciones, verticeOrigen, verticeDestino);
    }
    

    return 0;
}