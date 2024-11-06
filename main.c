#include <stdio.h>
#include <string.h>
#include <time.h>
#include "menu.h"

int autenticarUsuario(char* usuario);
void registrarBitacora(const char* usuario, const char* accion);

int main() {
    char usuario[50], clave[50];
    int autentificado = 0;

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", usuario);

    autentificado = autenticarUsuario(usuario);

    if (!autentificado) {
        printf("Ingreso fallido: usuario/clave erroneo.\n");
        registrarBitacora(usuario, "Ingreso fallido usuario/clave erroneo");
        return 1;
    }

    registrarBitacora(usuario, "Ingreso exitoso al sistema");
    
    int opcion;
    char repetir;

    do {
        printf("\nSeleccione una opcion:\n");
        printf("1. Calculo de area y perimetro (Figuras 2D)\n");
        printf("2. Calculo de superficie y volumen (Figuras 3D)\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: 
                registrarBitacora(usuario, "Accedio a Figuras 2D");
                menu2D(); 
                break;
            case 2: 
                registrarBitacora(usuario, "Accedio a Figuras 3D");
                menu3D(); 
                break;
            case 3: 
                registrarBitacora(usuario, "Salida del sistema");
                printf("Saliendo del programa...\n"); 
                return 0;
            default: 
                printf("Opcion no valida. Intente nuevamente.\n");
        }

        printf("\n¿Desea realizar el analisis de otra figura geometrica? (s/n): ");
        scanf(" %c", &repetir);

    } while(repetir == 's' || repetir == 'S');
    registrarBitacora(usuario, "Salida del sistema");
    printf("Saliendo del programa...\n"); 
    return 0;
}

int autenticarUsuario(char* usuario) {
    FILE *archivo;
    char linea[100], usuarioArchivo[50], claveArchivo[50];
    char claveIngresada[50];

    archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de usuarios.\n");
        return 0;
    }

    printf("Ingrese su clave: ");
    scanf("%s", claveIngresada);

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%s %s", usuarioArchivo, claveArchivo);
        if (strcmp(usuarioArchivo, usuario) == 0 && strcmp(claveArchivo, claveIngresada) == 0) {
            fclose(archivo);
            return 1; 
        }
    }

    fclose(archivo);
    return 0;  
}

void registrarBitacora(const char* usuario, const char* accion) {
    FILE *bitacora;
    bitacora = fopen("bitacora.txt", "a");
    if (bitacora == NULL) {
        printf("Error al abrir el archivo de bitacora.\n");
        return;
    }

    time_t tiempo = time(NULL);
    struct tm *tlocal = localtime(&tiempo);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y/%m/%d", tlocal);

    fprintf(bitacora, "%s: %s – %s\n", fecha, usuario, accion);
    fclose(bitacora);
}
