#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    // printf("Soy el proceso hijo \n");
    printf("Mi PID es: %d\n", getpid());
    // printf("Argumento 1: %s\n", argv[1]);

    while (1)
    {
        int tipo_llamada = rand() % 2;
        switch (tipo_llamada)
        {
            case 0:
            {
                printf("%d - W\n", getpid());
                break;
            }
            case 1:
            {
                printf("%d - R\n", getpid());
                break;
            }
        }
        int tiempo_espera = rand() % 2 + 1;
        sleep(tiempo_espera);
    }
}