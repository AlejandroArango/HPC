//concurrencia y normalito XD
// dio mio aiuda

#include <omp.h>
#include <iostream>
#include <stdio>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){

  int a, b, c ,d ,e, f, num=1;

  cout << "introduzca dimenciones de la matriz A y B" << '\n';
  cin >> a;
  //cin >> b;

  //cout << "introduzca dimenciones de la matriz B" << '\n';
  //cin >> c;
  //cin >> d;

  // matriz [filas][columnas]

  int matrizA [a][a];
  int matrizB [a][a];
  //llenar
  for(e = 0; e <= a; e++)
  {
    for (f = 0; i <= a; f++)
    {
      matrizA[e][f]=num;
      matrizB[e][f]=num;
    }
  }
  //mostrar
  for(e = 0; e <= a; e++)
  {
    for (f = 0; i <= a; f++)
    {
      cout << "matriz A" << '\n';

      matrizA[e][f]=num;
      matrizB[e][f]=num;
    }
  }
}
