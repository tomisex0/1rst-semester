#include <stdio.h>

int main()
{
    int p_act, p_obj, option, puerta, personas;
    p_act = 0;
    puerta = 0;
    int bandera = 1;

    while (bandera)
    { // Asensor personal, para persona  que necesita su asensor propio en su edificio

        printf("\nSeleccione su option: \n 1.Llamar al ascensor \n 2.Salir \n");
        scanf("%i", &option);
        switch (option)
        {
        case 1:
            printf("Cuantas personas van a subir?: ");
            scanf("%i", &personas);
            switch (personas)
            {
            case 1:
                printf("----Ascensor maximo 2 personas----");
                printf("\nSeleccione su piso: \n");
                printf("S2 S1 0\n1  2  3\n4  5  6\n7  8  9 \n   10 \n");
                scanf("%i", &p_obj);
                if (p_obj >= -2 && p_obj <= 10)
                {
                    if (p_obj == p_act)
                    {
                        printf("\nYa se encuentra en este piso %i", p_act);
                        continue;
                    }
                    if (p_act < p_obj)
                    {
                        for (int i = p_act; i <= p_obj; i++)
                        {
                            printf("\n Subiendo al piso:  %i", i);
                        }
                        p_act = p_obj;
                        printf("\nHa llegado a su destino..... %i", p_act);
                    }
                    else
                    {
                        for (int j = p_act; j >= p_obj; j--)
                        {
                            printf("\n Bajando al piso:  %i ", j);
                        }
                        p_act = p_obj;
                        printf("\nHa llegado a su destino.....%i", p_act);
                    }
                }
                else
                {
                    printf("\nNo valido\n");
                }

                continue;

            case 2:
                printf("----Ascensor maximo 2 personas----");
                for(int h=1; h<=2;h++){
                    printf("\nSeleccione su piso: \n");
                    printf("\n Escpja su piso persona N %i", h);
                    printf("\n1  2  3\n4  5  6\n7  8  9 \n   10 \n");
                    scanf("%i", &p_obj);
                    if (p_obj >= -2 && p_obj <= 10)
                    {
                        if (p_obj == p_act)
                        {
                            printf("\nYa se encuentra en este piso %i", p_act);
                            
                            continue;
                        }
                        if (p_act < p_obj)
                        {
                            for (int i = p_act; i <= p_obj; i++)
                            {
                                printf("\n Subiendo al piso:  %i", i);
                            }
                            p_act = p_obj;
                            printf("\nHa llegado a su destino..... %i", p_act);
                            printf("\nSe bajo la persona N %i", h);
                        }
                        else
                        {
                            for (int j = p_act; j >= p_obj; j--)
                            {
                                printf("\n Bajando al piso:  %i ", j);
                            }
                            p_act = p_obj;
                            printf("\nHa llegado a su destino.....%i", p_act);
                            printf("\n Se bajo la persona N %i", h);
                        }
                    }
                    else
                    {
                        printf("\nNo valido\n");
                    }
                }
                continue;
            default:
                printf("\n[ERROR]: '%i' es una cantidad invalida.", personas);
                printf("\nEl ascensor solo funciona con 1 o 2 personas por seguridad.\n");
                continue;
            }
        case 2:
            bandera = 0;
            printf("\nAdios");
            break;

        default:
            printf("\nNo valido");
            continue;
        }
    }
}
