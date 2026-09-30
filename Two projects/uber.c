#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

const int MAX = 15;

struct usuario
{
    int userid;
    int city;
    char nombre[20];
    char pasww[20];
    int estado;
};

struct chofer
{
    int choferid;
    int city;
    char nombre[20];
    char pasww[20];
    int estado;
    char placa[20];
};

struct Ciudad
{
    int id_ciudad;
    char nombre[50];
    float x;
    float y;
};
/* struct Viaje
{
    int id_viaje;
    int id_pasajero;
    int id_chofer;
    int id_origen;
    int id_destino;
    float distancia;
    float costo_total;
    int estado;
};*/
// --- PROTOTIPOS ---
struct usuario *datausers(struct usuario *lista, int *limite);
struct chofer *datadriver(struct chofer *lista, int *limite);
void mostrar_ciudades(struct Ciudad *mapa, int total);
float distancia(double Xo, double Yo, double Xf, double Yf);
void solicitar_viaje(struct usuario *pasajeros, int cont_users, struct chofer *choferes, int cont_choferes, struct Ciudad *mapa, int total_ciudades);
float calculopago(float distanciav);
void cancelar(struct usuario *pasajeros, int cont_users, struct chofer *choferes, int cont_choferes);
// --- MAIN ---
int main(void)
{

    struct Ciudad mapa[15] = {
        {1, "ESPE (Campus Sangolqui)", 0.0, 0.0},
        {2, "Sangolqui (Centro)", 1.0, -1.0},
        {3, "San Luis Shopping", 2.0, 1.5},
        {4, "Conocoto", -2.5, 3.0},
        {5, "Cumbaya", 5.0, 11.0},
        {6, "Quito (Centro Historico)", -12.0, 15.0},
        {7, "La Marin", -11.5, 14.5},
        {8, "El Panecillo", -12.5, 13.5},
        {9, "La Carolina", -11.0, 19.0},
        {10, "La Pradera", -11.0, 17.5},
        {11, "Pontificia Univ. Catolica", -11.2, 16.5},
        {12, "El Teleferico", -15.0, 17.0},
        {13, "Aeropuerto (Tababela)", 14.0, 22.0},
        {14, "El Quinche", 18.0, 28.0},
        {15, "Quitumbe (Terminal Sur)", -16.0, 5.0}};
    int total_ciudades = 15;
    struct usuario *lista_usuarios = NULL;
    int cont_users = 0;
    struct chofer *lista_choferes = NULL;
    int cont_choferes = 0;
    int opt, destino;

    do
    {
        printf("\n--- UBER ---\n");
        printf("1. Registrar Usuario\n");
        printf("2. Registrar Chofer\n");
        printf("3. Establecer un viaje\n");
        printf("4. Cancelar Viaje\n");
        printf("5. Salir\n");
        printf("Seleccionar opcion: ");
        scanf("%i", &opt);

        switch (opt)
        {
        case 1:
            mostrar_ciudades(mapa, total_ciudades);
            lista_usuarios = datausers(lista_usuarios, &cont_users);
            break;
        case 2:
            mostrar_ciudades(mapa, total_ciudades);
            lista_choferes = datadriver(lista_choferes, &cont_choferes);
            break;
        case 3:
            mostrar_ciudades(mapa, total_ciudades);
            solicitar_viaje(lista_usuarios, cont_users, lista_choferes, cont_choferes, mapa, total_ciudades);
            break;
        case 4:
            cancelar(lista_usuarios, cont_users, lista_choferes, cont_choferes);
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida.\n");
        }
    } while (opt != 5);
}

struct chofer *datadriver(struct chofer *lista, int *limite)
{
    (*limite)++;
    struct chofer *driver = realloc(lista, (*limite) * sizeof(struct chofer));
    if (driver == NULL)
    {
        printf("Error de memoria.\n");
        (*limite)--;
        return lista;
    }
    lista = driver;
    int i = *limite - 1;
    lista[i].choferid = *limite;
    lista[i].estado = 0;

    printf("\n--- Registro de Chofer ---\n");
    printf("Nombre: ");
    scanf("%s", lista[i].nombre);
    printf("Contraseña: ");
    scanf("%s", lista[i].pasww);
    printf("Placa: ");
    scanf("%s", lista[i].placa);
    printf("ID Ciudad Actual (1-15): ");
    scanf("%i", &lista[i].city);

    printf("\n>> Chofer registrado | Nombre: %s | ID: %03d | Placa: %s <<\n", lista[i].nombre, lista[i].choferid, lista[i].placa);
    return lista;
}

struct usuario *datausers(struct usuario *lista, int *limite)
{
    (*limite)++;
    struct usuario *user = realloc(lista, (*limite) * sizeof(struct usuario));
    if (user == NULL)
    {
        printf("Error de memoria.\n");
        (*limite)--;
        return lista;
    }
    lista = user;
    int i = *limite - 1;
    lista[i].userid = *limite;
    lista[i].estado = 0;

    printf("\n--- Registro de Usuario ---\n");
    printf("Nombre: ");
    scanf("%s", lista[i].nombre);
    printf("Contraseña: ");
    scanf("%s", lista[i].pasww);
    printf("ID Ciudad Actual (1-15): ");
    scanf("%i", &lista[i].city);

    printf("\n>> Usuario registrado | Nombre: %s | ID: %03d | Ubicacion ID: %i <<\n", lista[i].nombre, lista[i].userid, lista[i].city);
    return lista;
}

void mostrar_ciudades(struct Ciudad *mapa, int total)
{
    printf("\n=========================================================\n");
    printf("               CATALOGO DE DESTINOS DISPONIBLES            \n");
    printf("=========================================================\n");
    printf("%-6s | %-30s | %-12s\n", "ID", "Nombre del Destino", "Coordenadas (X, Y)");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < total; i++)
    {
        printf("[%03d] | %-32s | (%5.1f, %5.1f)\n",
               mapa[i].id_ciudad,
               mapa[i].nombre,
               mapa[i].x,
               mapa[i].y);
    }
    printf("=========================================================\n");
}
float distancia(double Xo, double Yo, double Xf, double Yf)
{

    return sqrt(pow(Xf - Xo, 2) + pow(Yf - Yo, 2));
}

void solicitar_viaje(struct usuario *pasajeros, int cont_users, struct chofer *choferes, int cont_choferes, struct Ciudad *mapa, int total_ciudades)
{

    printf("\n--- SOLICITUD DE VIAJE ---\n");

    if (cont_choferes == 0)
    {
        printf("Lo sentimos, no hay choferes registrados en el sistema aun.\n");
        return;
    }
    int indice_chofer_asignado = -1;
    for (int i = 0; i < cont_choferes; i++)
    {
        if (choferes[i].estado == 0)
        {
            indice_chofer_asignado = i;
            break;
        }
    }

    if (indice_chofer_asignado == -1)
    {
        printf("Todos los choferes estan ocupados. Intente mas tarde.\n");
        return;
    }

    int id_pasajero_input, id_destino;
    printf("Ingrese su ID de pasajero: ");
    scanf("%d", &id_pasajero_input);

    if (id_pasajero_input < 1 || id_pasajero_input > cont_users)
    {
        printf("Error: El ID de pasajero %03d no esta registrado en el sistema.\n", id_pasajero_input);
        return;
    }

    int indice_pasajero = id_pasajero_input - 1;

    if (pasajeros[indice_pasajero].estado == 1)
    {
        printf("Error: El pasajero %s ya se encuentra en un viaje activo.\n", pasajeros[indice_pasajero].nombre);
        return;
    }

    printf("Ingrese el ID de la ciudad destino  ");
    scanf("%d", &id_destino);
    if (id_destino < 1 || id_destino > total_ciudades)
    {
        printf("[!] Error: ID de destino invalido. Debe ser entre 1 y %d.\n", total_ciudades);
        return;
    }

    int origen_id = pasajeros[indice_pasajero].city;
    float x1 = mapa[origen_id - 1].x;
    float y1 = mapa[origen_id - 1].y;

    float x2 = mapa[id_destino - 1].x;
    float y2 = mapa[id_destino - 1].y;

    float distanciav = distancia(x1, y1, x2, y2);
    float total_pagar = calculopago(distanciav);

    pasajeros[indice_pasajero].estado = 1;
    choferes[indice_chofer_asignado].estado = 1;

    printf("\n--- RECIBO DE VIAJE ---\n");
    printf("Pasajero: %s\n", pasajeros[indice_pasajero].nombre);
    printf("Chofer asignado: %s (Placa: %s)\n", choferes[indice_chofer_asignado].nombre, choferes[indice_chofer_asignado].placa);
    printf("Distancia a recorrer: %.2f km\n", distanciav);
    printf("Total a pagar: $%.2f\n", total_pagar);
    printf("ESTADO: Viaje en curso...\n");
}

float calculopago(float distanciav)
{
    float tarifa_base = 1.50;
    float precio_por_km = 0.45;
    float tarifa_minima = 2.00;
    float multiplicador = 1.0;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int hora_actual = tm.tm_hour;

    if ((hora_actual >= 7 && hora_actual <= 9) || (hora_actual >= 17 && hora_actual <= 19))
    {
        multiplicador = 1.50;
        printf("\n[!] ALERTA: Tarifa Dinamica activa por alta demanda (%02d:%02d).\n", hora_actual, tm.tm_min);
    }

    float total = (tarifa_base + (distanciav * precio_por_km)) * multiplicador;

    if (total < tarifa_minima)
    {
        return tarifa_minima;
    }
    return total;
}
void cancelar(struct usuario *pasajeros, int cont_users, struct chofer *choferes, int cont_choferes)
{
    int id_pasajero_input;
    printf("Ingrese su ID de pasajero: ");
    scanf("%d", &id_pasajero_input);

    if (id_pasajero_input < 1 || id_pasajero_input > cont_users)
    {
        printf("Error: El ID de pasajero %03d no esta registrado en el sistema.\n", id_pasajero_input);
        return;
    }
    int indice_chofer_asignado = -1;
    for (int i = 0; i < cont_choferes; i++)
    {
        if (choferes[i].estado == 1)
        {
            indice_chofer_asignado = i;
            break;
        }
    }

    int indice_pasajero = id_pasajero_input - 1;

    if (pasajeros[indice_pasajero].estado == 0)
    {
        printf("El pasajero %s no tiene ningun viaje activo para cancelar.\n", pasajeros[indice_pasajero].nombre);
        return;
    }
    if (pasajeros[indice_pasajero].estado == 1)
    {
        pasajeros[indice_pasajero].estado = 0;
        choferes[indice_chofer_asignado].estado = 0;
    }

    printf("ESTADO:Cancelando...\n");
    printf("Pasajero: %s\n", pasajeros[indice_pasajero].nombre);
    printf("Chofer asignado: %s (Placa: %s)\n", choferes[indice_chofer_asignado].nombre, choferes[indice_chofer_asignado].placa);

    printf("Viaje cancelado\n");
}