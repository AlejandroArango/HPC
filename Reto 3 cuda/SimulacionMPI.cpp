#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
# include <mpi.h>
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
                numDesplazamiento[0]++;
                arrayDeDesplazamiento[i] = 1;
     
                instanteDeTiempoAnterior[i - 1] = 2;
            }
        }
        
        if(i == 0)
        {
      
            if(instanteDeTiempoAnterior[0] == 0)
            {
       
                if(instanteDeTiempoAnterior[dimencionDelArray - 1] == 1 )
                {
                    numDesplazamiento[0]++;
                    arrayDeDesplazamiento[0] = 1;
                    arrayDeDesplazamiento[dimencionDelArray - 1] = 0;
                    instanteDeTiempoAnterior[dimencionDelArray - 1] = 2;
                }
            }

        }

    }

}



int main(int argc, char *argv[])
{

    int N = 10000000;
    srand(time(NULL));
    int *primerInstanteDeTiempo = new int[N];
    int *otroVector = new int[N];
    int aleatorio;
    int rank, size;
    int simulacion, simulacionTotal;
    int pruebaValores[10] = {0,1,1,0,1,0,1,1,0,1};
    const int master = 0;
    using millis = std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::steady_clock;
    auto t_seq_1 = steady_clock::now();
    MPI_Init(&argc, &argv);
    MPI_Comm_size ( MPI_COMM_WORLD, &size );
    MPI_Comm_rank ( MPI_COMM_WORLD, &rank );


   

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
    simulacionDeTrafico(N, primerInstanteDeTiempo, otroVector, numRecorridos);

    MPI_Reduce ( &simulacion, &simulacionTotal, 1, MPI_INT, MPI_SUM, master, 
    MPI_COMM_WORLD );
    auto t_seq_2 = steady_clock::now();
    cout << N << endl;
    cout << "El total de vehiculos que se movieron es: " << numRecorridos[0] << endl;
    auto time1 = duration_cast<millis>( t_seq_2 - t_seq_1 ).count();
    std::cout << "Tiempo: " << time1 << " milisegundos\n" << std::endl;

    MPI_Finalize ( );

    return 0;
}
