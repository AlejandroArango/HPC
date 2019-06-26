
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <omp.h>
#include <chrono>


using namespace std;

double calcPiDartboardSchedulle(long n){
        long  hits=0, k, chunk=n/8;
        const double factor = 1.0 / RAND_MAX;
        double pi_approx;

        double x, y;
        int threadmasterId = 0, numThreads = 0;
        #pragma omp parallel private(x,y,k,threadmasterId,numThreads) shared(hits,chunk) //num_threads(8)
        {
            threadmasterId = omp_get_thread_num();
            if(threadmasterId == 0){
                numThreads = omp_get_num_threads();
                // printf("Thread master! with id %d\n",threadmasterId);
                // printf("Invoked threads number %d",numThreads);
            }
            #pragma omp for schedule(dynamic,chunk)
                for(k=0; k<n; ++k){
                    /* find two numbers within 0..1*/
                    x=rand()*factor;
                    y=rand()*factor;
                    if(x*x + y*y < 1.0){
                        ++hits;
                    }
                }


                }
                pi_approx= 4.0*hits/n;

            printf("Approximation of pi after %ld tosses %.20f %.9f %% \n", n, pi_approx, fabs(M_PI-pi_approx)*100/M_PI);
            }
void writeTime(float elapsed, long len){
    FILE *f =fopen("timesdartboardparallelschedulle.txt","a+");
    fprintf(f, "%ld  %.9f\n", len, elapsed);
    fclose(f);
}

int main (void){
    long n;
    while(1){
    cout<<"enter the no of tosses (or 0 to exit):";
    cin>>n;
    srand((int)clock());
    if(n<=0)
        break;
    auto startTime=chrono::high_resolution_clock::now();
    calcPiDartboardSchedulle(n);
    auto endTime=chrono::high_resolution_clock::now();
	chrono::duration<float>  elapsed = endTime - startTime;
	writeTime(elapsed.count(), n);
    }
    return 0;
}

