#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
    int tareaID;
    char *descripcion;
    int duracion;
} typedef Tarea;

struct TNodoTarea {
    Tarea tarea;
    struct TNodoTarea* siguiente;
} typedef TNodoTarea;

TNodoTarea* crearListaVacia();
TNodoTarea* crearTarea(int idTarea);
void insertarTarea(TNodoTarea** listadoTareas, TNodoTarea* tarea);
void eliminarTarea(TNodoTarea* listadoTareas, int idTarea);
void cargarTareas(TNodoTarea** listadoTareas, int cantidadTareas);
void consultarEstadosTareas(TNodoTarea** listadoTareasPendientes, TNodoTarea** listadoTareasRealizadas);
void mostrarTarea(Tarea tarea);
void mostrarTareas(TNodoTarea* listadoTareas);
TNodoTarea* buscarTareaPorID(TNodoTarea** listadoTareas, int idTarea);
TNodoTarea* buscarTareaPorPalabra(TNodoTarea** listadoTareas, char* palarbraClave);

int main() {

    srand((int) time(NULL));

    int cantidadTareas, idTareaABuscar;
    char* buffer;
    char* palabraClave;

    TNodoTarea* listadoTareasPendientes = crearListaVacia();
    TNodoTarea* listadoTareasRealizadas = crearListaVacia();    

    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);
    fflush(stdin);

    cargarTareas(&listadoTareasPendientes, cantidadTareas);

    consultarEstadosTareas(&listadoTareasPendientes, &listadoTareasRealizadas);

    printf("\n\n========== Listado de Tareas Realizadas ==========\n");
    mostrarTareas(listadoTareasRealizadas);

    printf("\n\n========== Listado de Tareas Pendientes ==========\n");    
    mostrarTareas(listadoTareasPendientes);

    // Búsqueda por ID
    printf("\nIngrese el id de la tarea que desea buscar: ");
    scanf("%d", &idTareaABuscar);
    fflush(stdin);

    printf("\nEl resultado de la busqueda por ID \'%d\' es:\n", idTareaABuscar);

    // Si el ID no se encuentra entre las tareas pendientes, buscara en las tareas realizadas.
    if ( buscarTareaPorID(&listadoTareasPendientes, idTareaABuscar) ) {
        
        mostrarTarea( buscarTareaPorID(&listadoTareasPendientes, idTareaABuscar)->tarea );

    } else if ( buscarTareaPorID(&listadoTareasRealizadas, idTareaABuscar) ) {
        
        mostrarTarea( buscarTareaPorID(&listadoTareasRealizadas, idTareaABuscar)->tarea );

    } else {
        printf("No se ha encontrado una tarea.\n");
    };

    // Búsqueda por palabra clave
    buffer = (char*) malloc( sizeof(char) * 50 );

    printf("\nIngrese la palabra clave de la tarea que desea buscar: ");
    gets(buffer);

    palabraClave = (char*) malloc( sizeof(char) * (strlen(buffer) + 1) );
    strcpy(palabraClave, buffer);
    free(buffer);
    
    printf("\nEl resultado de la busqueda \'%s\' es:\n", palabraClave);
    
    // Si el ID no se encuentra entre las tareas pendientes, buscara en las tareas realizadas.
    if ( buscarTareaPorPalabra(&listadoTareasPendientes, palabraClave) ) {

        mostrarTarea( buscarTareaPorPalabra(&listadoTareasPendientes, palabraClave)->tarea );

    } else if ( buscarTareaPorPalabra(&listadoTareasRealizadas, palabraClave) ) {

        mostrarTarea( buscarTareaPorPalabra(&listadoTareasRealizadas, palabraClave)->tarea );

    } else {
        printf("No se ha encontrado una tarea.\n");
    };

    return 0;
};

TNodoTarea* crearListaVacia() {
    return NULL;
};

TNodoTarea* crearTarea(int idTarea) {

    TNodoTarea* nuevaTarea = (TNodoTarea*) malloc( sizeof(TNodoTarea) );
    char* buff = (char*) malloc( sizeof(char) * 100 );

    nuevaTarea->tarea.tareaID = idTarea;

    printf("Ingrese la descripcion de la tarea: ");
    gets(buff);

    nuevaTarea->tarea.descripcion = (char*) malloc( sizeof(char) * ( strlen(buff) + 1 ) );
    strcpy(nuevaTarea->tarea.descripcion, buff);
    free(buff);

    nuevaTarea->tarea.duracion = 10 + rand() % 91;

    nuevaTarea->siguiente = NULL;

    return nuevaTarea;
};

void insertarTarea(TNodoTarea** listadoTareas, TNodoTarea* tarea) {

    tarea->siguiente = *listadoTareas;

    *listadoTareas = tarea;
};

void eliminarTarea(TNodoTarea* listadoTareas, int idTarea) {
    TNodoTarea* tarea = listadoTareas;
    TNodoTarea* tareaAnterior = listadoTareas;

    while (tarea && tarea->tarea.tareaID != idTarea) {
        tareaAnterior = tarea;
        tarea = tarea->siguiente;
    };

    if (tarea) {
        tareaAnterior->siguiente = tarea->siguiente;
    };
};

void cargarTareas(TNodoTarea** listadoTareas, int cantidadTareas) {
    for (int i = 0; i < cantidadTareas; i++) {
        insertarTarea(listadoTareas, crearTarea(i));
    };
};

void consultarEstadosTareas(TNodoTarea** listadoTareasPendientes, TNodoTarea** listadoTareasRealizadas) {

    TNodoTarea* tareaAux = *listadoTareasPendientes;

    while (tareaAux) {
        
        int realizada = 0;

        mostrarTarea(tareaAux->tarea);

        printf("La tarea fue realizada? (1: SI 0: NO): ");
        scanf("%d", &realizada);

        if ( realizada == 1 ) {
            TNodoTarea* tareaRealizadaAux = tareaAux;
            tareaAux = tareaAux->siguiente;
            eliminarTarea(*listadoTareasPendientes, tareaRealizadaAux->tarea.tareaID);
            insertarTarea(listadoTareasRealizadas, tareaRealizadaAux);
        } else {
            tareaAux = tareaAux->siguiente;
        };
    };
};

void mostrarTarea(Tarea tarea) {
    printf("\n------------------------------\n");

    printf("ID Tarea: %d\n", tarea.tareaID);
    printf("Descripcion: %s\n", tarea.descripcion);
    printf("Duracion: %d\n", tarea.duracion);
};

void mostrarTareas(TNodoTarea* listadoTareas) {

    TNodoTarea* tareaAux = listadoTareas;

    while (tareaAux) {
        mostrarTarea(tareaAux->tarea);

        tareaAux = tareaAux->siguiente;
    };
};

TNodoTarea* buscarTareaPorID(TNodoTarea** listadoTareas, int idTarea) {
    
    TNodoTarea* tareaAux = *listadoTareas;

    while (tareaAux && tareaAux->tarea.tareaID != idTarea) {
        tareaAux = tareaAux->siguiente;
    };

    return tareaAux;
};

TNodoTarea* buscarTareaPorPalabra(TNodoTarea** listadoTareas, char* palarbraClave) {
    
    TNodoTarea* tareaAux = *listadoTareas;

    while (tareaAux && !strstr(tareaAux->tarea.descripcion, palarbraClave)) {
        tareaAux = tareaAux->siguiente;
    };

    return tareaAux;
};