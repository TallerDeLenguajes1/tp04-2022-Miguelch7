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


int main() {

    srand((int) time(NULL));

    int cantidadTareas;
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