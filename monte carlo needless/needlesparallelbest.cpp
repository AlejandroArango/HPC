#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <string>
#include <iostream>
#define PI 3.1415926535
#define RAD(x) (x * PI/180.0)

using namespace std;

double calcPiNeedlessBest(long attempts) {

    double x; /* the center of needle to the closest line */
    double y; /* l/2*sin(DEG) */
    double deg; /* Angle degree of a needle */
    double P; /* Probabillity */
    double a_pi; /* Calculated Pi */
    int events = 0;
    double l = .8; /* Lenghts of a needle */
    int t_len = 2; /* Lenghts between lines */
    int i;
    int threadmasterId = 0, numThreads = 0;
    #pragma omp parallel private(deg,x,i,threadmasterId, numThreads) shared(events)
    {
        //threadmasterId = omp_get_thread_num();
          //  if(threadmasterId == 0){
            //    numThreads = omp_get_num_threads();
            //}
            #pragma omp for schedule(dynamic)
                for(i=0; i<=attempts; i++) {
                    x = (double)rand()/((double)RAND_MAX * (double)t_len);
                    deg = RAD(rand() % 360);

                    if(x <= ((l/2.0)*(sin(deg)))) {
                    //printf("Positive: %d\t P=%f\t x=%f\t deg=%f\n", i, (double)events/(double)i, x, deg);
                    events++;
                    }
                }

    }

        P = (double)events/(double)attempts;
        printf("There have been %d positive trials out of %d attempts\n", events, attempts);
        printf("Input parameters: t = %d; l = %f; P = %f;\n", t_len, l, P);
        a_pi = (2*l)/(t_len*P);
        printf("Calculated Pi = %.10f\n", a_pi);



}


void writeTime(float elapsed, long len){
    FILE *f =fopen("timesneedlessbest.txt","a+");
    fprintf(f, "%ld  %.9f\n", len, elapsed);
    fclose(f);
}

int main (void){
    long attempts;
    while(1){
    cout<<"enter the no of tosses (or 0 to exit):";
    cin>>attempts;
    srand((int)clock());
    if(attempts<=0)
        break;
    auto startTime=chrono::high_resolution_clock::now();
    calcPiNeedlessBest(attempts);
    auto endTime=chrono::high_resolution_clock::now();
	chrono::duration<float>  elapsed = endTime - startTime;
	writeTime(elapsed.count(), attempts);
    }
    return 0;
}

