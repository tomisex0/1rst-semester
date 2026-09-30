#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void deposito(int *saldo);
int main(void)
{
    srand(time(NULL));
    int saldo=100;
    deposito(&saldo);
}
void deposito(int *saldo)
{
    int cantidad;
    int b20, b10, b5;
    int mod;
    printf("\nIngrese cantidad a depositar\nMax: $4900\nMin: $5");
    printf("\n$");
    scanf("%d", &cantidad);
    if(cantidad>= 5&&cantidad<=4900 && cantidad%5==0)
    {
        b20= rand() %(cantidad/20+1);
        mod = cantidad-(b20*20);
        b10 = rand()%(mod/10+1);
        mod = mod-(b10*10);
        b5 = mod/5;
        *saldo = *saldo + cantidad;
        printf("\nBilletes de 20: %d", b20);
        printf("\nBilletes de 10: %d", b10);
        printf("\nBilletes de 5: %d", b5);
        printf("\nDeposito: $%d", cantidad);
        printf("\nSaldo actual: $%d", *saldo);
    }
    else
    {
        printf("\nCantidad invalida");
    }
}
