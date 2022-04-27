#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
    int tareaID;
    char *descripcion;
    int duracion;
} typedef Tarea;

void cargarTareas(Tarea** listadoTareas, int cantidadTareas);
void cargarTarea(Tarea* tarea, int idTarea);
void mostrarTareas(Tarea** listadoTareas, int cantidadTareas, Tarea** listadoTareasRealizadas);
void mostrarTarea(Tarea* tarea);
void mostrarTareasRealizadas(Tarea** listadoTareasRealizadas, int cantidadTareas);
void mostrarTareasPendientes(Tarea** listadoTareas, int cantidadTareas);
void liberarMemoria(Tarea** listadoTareas, Tarea** listadoTareasRealizadas, int cantidadTareas);
Tarea* busquedaPorPalabra(Tarea** listadoTareas, Tarea** listadoTareasRealizadas, int cantidadTareas, char *palabraClave);
Tarea* busquedaPorId(Tarea** listadoTareas, Tarea** listadoTareasRealizadas, int cantidadTareas, int idTarea);

int main() {

    srand((int) time(NULL));

    int cantidadTareas, idTareaABuscar;
    Tarea** listadoTareas;
    Tarea** listadoTareasRealizadas;

    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);
    fflush(stdin);

    listadoTareas = (Tarea**) malloc( sizeof(Tarea*) * cantidadTareas );
    listadoTareasRealizadas = (Tarea**) malloc( sizeof(Tarea*) * cantidadTareas );

    cargarTareas(listadoTareas, cantidadTareas);

    mostrarTareas(listadoTareas, cantidadTareas, listadoTareasRealizadas);

    mostrarTareasRealizadas(listadoTareasRealizadas, cantidadTareas);
    
    mostrarTareasPendientes(listadoTareas, cantidadTareas);

    // Búsqueda por id
    printf("\nIngrese el id de la tarea que desea buscar: ");
    scanf("%d", &idTareaABuscar);
    fflush(stdin);
    
    if (busquedaPorId(listadoTareas, listadoTareasRealizadas, cantidadTareas, idTareaABuscar)) {
        printf("\nLa tarea de id \'%d\' es:", idTareaABuscar);
        mostrarTarea(busquedaPorId(listadoTareas, listadoTareasRealizadas, cantidadTareas, idTareaABuscar));
    } else {
        printf("No se ha encontrado una tarea con ID \'%d\'", idTareaABuscar);
    };

    // Búsqueda por palabra clave
    if (busquedaPorPalabra(listadoTareas, listadoTareasRealizadas, cantidadTareas, "Desarrollar")) {
        printf("\nLa tarea que contiene la palabra \'Desarrollar\' es:");
        mostrarTarea(busquedaPorPalabra(listadoTareas, listadoTareasRealizadas, cantidadTareas, "Desarrollar"));
    } else {
        printf("No se ha encontrado una tarea con esa palabra");
    };

    liberarMemoria(listadoTareas, listadoTareasRealizadas, cantidadTareas);
    
    return 0;
};

void cargarTareas(Tarea** listadoTareas, int cantidadTareas) {

    for (int i = 0; i < cantidadTareas; i++) {

        listadoTareas[i] = (Tarea*) malloc( sizeof(Tarea) );

        cargarTarea(listadoTareas[i], i);
    };
};

void cargarTarea(Tarea* tarea, int idTarea) {

    char* Buff = (char*) malloc( sizeof(char) * 100 );

    tarea->tareaID = idTarea;

    printf("Ingrese la descripcion de la tarea: ");
    gets(Buff);
    tarea->descripcion = (char*) malloc( sizeof(char*) * (strlen(Buff) + 1) );
    strcpy(tarea->descripcion, Buff);

    tarea->duracion = 10 + rand()%91;

    free(Buff);
};

void mostrarTareas(Tarea** listadoTareas, int cantidadTareas, Tarea** listadoTareasRealizadas) {

    for (int i = 0; i < cantidadTareas; i++) {
        
        int realizada = 0;

        mostrarTarea(listadoTareas[i]);

        printf("La tarea fue realizada? (1: SI 0: NO): ");
        scanf("%d", &realizada);

        if ( realizada == 1 ) {
            listadoTareasRealizadas[i] = listadoTareas[i];
            listadoTareas[i] = NULL;
        } else {
            listadoTareasRealizadas[i] = NULL;
        };
    };
};

void mostrarTarea(Tarea* tarea) {

    printf("\n------------------------------\n");

    printf("ID Tarea: %d\n", tarea->tareaID);
    printf("Descripcion: %s\n", tarea->descripcion);
    printf("Duracion: %d\n", tarea->duracion);
};

void mostrarTareasRealizadas(Tarea** listadoTareasRealizadas, int cantidadTareas) {

    printf("\n\n========== Listado de Tareas Realizadas ==========");

    for (int i = 0; i < cantidadTareas; i++) {
        if (listadoTareasRealizadas[i] != NULL) {
            mostrarTarea(listadoTareasRealizadas[i]);
        };
    };
};

void mostrarTareasPendientes(Tarea** listadoTareas, int cantidadTareas) {
    printf("\n\n========== Listado de Tareas Pendientes ==========\n");

    for (int i = 0; i < cantidadTareas; i++) {
        if (listadoTareas[i] != NULL) {
            mostrarTarea(listadoTareas[i]);
        };
    };
};

void liberarMemoria(Tarea** listadoTareas, Tarea** listadoTareasRealizadas, int cantidadTareas) {
    
    for (int i = 0; i < cantidadTareas; i++) {

        if (listadoTareas[i] != NULL) {
            free(listadoTareas[i]->descripcion);
        };

        if (listadoTareasRealizadas[i] != NULL) {
            free(listadoTareasRealizadas[i]->descripcion);
        };
        
        free(listadoTareas[i]);
        free(listadoTareasRealizadas[i]);
    };

    free(listadoTareas);
    free(listadoTareasRealizadas);
};

Tarea* busquedaPorPalabra(Tarea** listadoTareas, Tarea** listadoTareasRealizadas, int cantidadTareas, char *palabraClave) {
    for (int i = 0; i < cantidadTareas; i++) {
        if (listadoTareas[i] != NULL && strstr(listadoTareas[i]->descripcion, palabraClave) != NULL) {
            return listadoTareas[i];
        } else if (listadoTareasRealizadas[i] != NULL && strstr(listadoTareasRealizadas[i]->descripcion, palabraClave) != NULL) {
            return listadoTareasRealizadas[i];
        };
    };

    return NULL;
};

Tarea* busquedaPorId(Tarea** listadoTareas, Tarea** listadoTareasRealizadas, int cantidadTareas, int idTarea) {
    for (int i = 0; i < cantidadTareas; i++) {
        if (listadoTareas[i] != NULL && listadoTareas[i]->tareaID == idTarea) {
            return listadoTareas[i];
        } else if (listadoTareasRealizadas[i] != NULL && listadoTareasRealizadas[i]->tareaID == idTarea) {
            return listadoTareasRealizadas[i];
        };
    };

    return NULL;
};
