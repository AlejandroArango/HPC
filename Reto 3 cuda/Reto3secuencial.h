#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

void simulacionDeTrafico(int dimencionDelArray, int *instanteDeTiempoAnterior, int *arrayDeDesplazamiento, int * numDesplazamiento)
{
    for(int i = dimencionDelArray - 1; i >= 0; i--)
    {
        arrayDeDesplazamiento[i] = instanteDeTiempoAnterior[i];
		
        if(instanteDeTiempoAnterior[i] == 2)
        {
            arrayDeDesplazamiento[i] = 0;
        }

        else if(instanteDeTiempoAnterior[i] == 0)
        {
            if(instanteDeTiempoAnterior[i - 1] == 1)
            {
                arrayDeDesplazamiento[i] = 1;
                numDesplazamiento[0]++;
                instanteDeTiempoAnterior[i - 1] = 2;
            }
        }

        if(i == 0)
        {
            if(instanteDeTiempoAnterior[0] == 0)
            {
                if(instanteDeTiempoAnterior[dimencionDelArray - 1] == 1 )
                {
                    arrayDeDesplazamiento[0] = 1;
                    numDesplazamiento[0]++;
                    arrayDeDesplazamiento[dimencionDelArray - 1] = 0;
                    instanteDeTiempoAnterior[dimencionDelArray - 1] = 2;
                }
            }
        }
    }
}

void writeTime(float elapsed, long len,int carros, int recorridos){
    FILE *f =fopen("tiemposautomata.txt","a+");
    fprintf(f, "%ld  %.15f  %d  %d\n", len, elapsed,carros, recorridos);
    fclose(f);
}

int main(void)
{
    int N;
    while(1){
    cout<<"ingrese el tamaño del vector:";
    cin>>N;

    int *primerInstanteDeTiempo = new int[N];
    int *otroVector = new int[N];
    int aleatorio;
    int* pruebaValores;

    int i;
    int cont = 0;
    pruebaValores=(int*)malloc(N*sizeof(int));
    for( i=0; i < N; i++)
	{
		aleatorio = 0 + rand() % (2 - 0);
		pruebaValores[i] = aleatorio;
		if (pruebaValores[i] == 1){
            cont++;
        }
	}

    printf("\n Carros: %d \n", cont);
    srand((int)clock());

    for(int i = 0; i < N; i++)
    {
        aleatorio = rand() % 10 + 1;

        if(aleatorio % 2 == 0)
        {
            primerInstanteDeTiempo[i] = 0;
        }
        else
        {
            primerInstanteDeTiempo[i] = 1;
        }

    }

    int *numRecorridos = new int[1];
    numRecorridos[0] = 0;
    auto startTime=chrono::high_resolution_clock::now();
    simulacionDeTrafico(N, pruebaValores, otroVector, numRecorridos);
    auto endTime=chrono::high_resolution_clock::now();
	chrono::duration<float>  elapsed = endTime - startTime;
	writeTime(elapsed.count(), N,cont, numRecorridos[0]);

    cout << "\n" << "El total de vehiculos que se movieron es: " << numRecorridos[0];
    }
    return 0;
}
