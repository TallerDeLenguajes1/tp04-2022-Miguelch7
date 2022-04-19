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
void mostrarTareas(Tarea** listadoTareas, int cantidadTareas);
void mostrarTarea(Tarea* tarea);

int main() {

    srand((int) time(NULL));

    int cantidadTareas;
    Tarea** listadoTareas;

    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);
    fflush(stdin);

    listadoTareas = (Tarea**) malloc( sizeof(Tarea*) * cantidadTareas );

    cargarTareas(listadoTareas, cantidadTareas);

    mostrarTareas(listadoTareas, cantidadTareas);
    
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

void mostrarTareas(Tarea** listadoTareas, int cantidadTareas) {

    for (int i = 0; i < cantidadTareas; i++) {
        mostrarTarea(listadoTareas[i]);
    };
};

void mostrarTarea(Tarea* tarea) {

    printf("------------------------------\n");

    printf("ID Tarea: %d\n", tarea->tareaID);
    printf("Descripcion: %s\n", tarea->descripcion);
    printf("Duracion: %d\n", tarea->duracion);

    printf("------------------------------\n\n");
};
