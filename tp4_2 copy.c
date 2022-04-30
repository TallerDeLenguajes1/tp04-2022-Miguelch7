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

TNodoTarea* CrearNodo(int idTarea);
void insertarNodo(TNodoTarea** Start, int Valor);

int main() {

    int cantidadTareas, idTareaABuscar;

    TNodoTarea* listadoTareasPendientes = NULL;
    TNodoTarea* listadoTareasRealizadas = NULL;    

    // printf("Ingrese la cantidad de tareas a realizar: ");
    // scanf("%d", &cantidadTareas);
    // fflush(stdin);

    // Cargar Tareas
    for (int i = 0; i < cantidadTareas; i++) {
        insertarNodo(&listadoTareasPendientes, i);
    };

    // MostrarTareas

    // for (int i = 0; i < 2; i++)
    // {
    //     printf("\n===== La tarea %d es: =====\n", listadoTareasPendientes->tarea.tareaID);
    //     printf("Descripcion: %s\n", listadoTareasPendientes->tarea.descripcion);
    //     printf("Duracion: %s\n", listadoTareasPendientes->tarea.duracion);
    //     listadoTareasPendientes = listadoTareasPendientes->siguiente;
    // }

    return 0;
};

TNodoTarea* CrearNodo(int idTarea) {

    TNodoTarea* nuevaTarea = (TNodoTarea*) malloc( sizeof(TNodoTarea) );
    
    char* buffer = (char*) malloc(50 * sizeof(char));
    printf("Ingrese la descripcion de la tarea a realizar: ");
    gets(buffer);

    nuevaTarea->tarea.tareaID = idTarea;
    nuevaTarea->tarea.descripcion = (char*) malloc( sizeof(char) * (strlen(buffer) + 1));
    strcpy(nuevaTarea->tarea.descripcion, buffer);
    nuevaTarea->tarea.duracion = 10 + rand() % 91;

    free(buffer);

    return nuevaTarea;
};

void insertarNodo(TNodoTarea** Start, int idTarea) {
    TNodoTarea* nuevaTarea = CrearNodo(idTarea);
    nuevaTarea->siguiente = *Start;
    *Start = nuevaTarea;
};