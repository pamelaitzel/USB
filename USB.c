include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_PATH_LENGTH 4096 // Aumentamos el tamaño del buffer para manejar rutas más largas

int main() {
    char filename[MAX_FILENAME_LENGTH];
    char usb_path[MAX_PATH_LENGTH];
    char trash_path[MAX_PATH_LENGTH];
    char destination_path[MAX_PATH_LENGTH];
    char command[MAX_PATH_LENGTH * 2]; // Duplicamos el tamaño del buffer para manejar comandos más largos

    // Solicitar al usuario el nombre del archivo a recuperar
    printf("Ingrese el nombre del archivo a recuperar: ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);

    // Eliminar el carácter de nueva línea ('\n') al final del nombre del archivo
    filename[strcspn(filename, "\n")] = 0;

    // Construir la ruta completa de la papelera de reciclaje
    const char* home_directory = getenv("HOME");
    if (home_directory == NULL) {
        printf("Error: no se pudo obtener la ruta del directorio de inicio del usuario.\n");
        return 1;
    }
    strncpy(trash_path, home_directory, sizeof(trash_path));
    strncat(trash_path, "/.Trash", sizeof(trash_path) - strlen(trash_path) - 1);

    // Solicitar al usuario la ruta de la unidad USB
    printf("Ingrese la ruta de la unidad USB (por ejemplo, /media/usb): ");
    fgets(usb_path, MAX_PATH_LENGTH, stdin);

    // Eliminar el carácter de nueva línea ('\n') al final de la ruta de la unidad USB
    usb_path[strcspn(usb_path, "\n")] = 0;

    // Construir la ruta completa del archivo en la papelera de reciclaje
    strncpy(destination_path, trash_path, sizeof(destination_path));
    strncat(destination_path, "/", sizeof(destination_path) - strlen(destination_path) - 1);
    strncat(destination_path, filename, sizeof(destination_path) - strlen(destination_path) - 1);

    // Construir el comando para mover el archivo desde la papelera de reciclaje a la unidad USB
    strncpy(command, "mv \"", sizeof(command));
    strncat(command, destination_path, sizeof(command) - strlen(command) - 1);
    strcat(command, "\" \"");
    strncat(command, usb_path, sizeof(command) - strlen(command) - 1);
    strcat(command, "\"");

    // Mover el archivo desde la papelera de reciclaje a la unidad USB
    printf("Recuperando archivo desde la papelera de reciclaje...\n");
    system(command);

    printf("Archivo recuperado en la ubicación: %s\n", destination_path);

    return 0;
}