
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <string>
#include <iostream>
using namespace std;







            double calcPiDartboard(long n){
                long k,hits;
                const double factor=1.0/RAND_MAX;

                for (k=hits=0;k<n; k++){
                    double x=rand() * factor;
                    double y=rand() * factor;
                    if(x*x + y*y < 1.0)
                        ++hits;

                }
                double pi_approx=4.0* hits /n;
                cout << "Approximation of pi after"
                     << n <<"tosses: " << pi_approx
                     <<" (error="
                     << fabs(M_PI - pi_approx)*100/M_PI
                     <<"%)\n";
            }

void writeTime(float elapsed, long len){
    FILE *f =fopen("timesdartboard.txt","a+");
    fprintf(f, "%ld  %.9f\n", len, elapsed);
    fclose(f);
}


int main(void){
    long n;
    while(1){
    printf("enter the no of tosses (or 0 to exit):");
    scanf("%f",&n);
    srand((int)clock());
     if(n<=0)
        break;
    auto startTime=chrono::high_resolution_clock::now();
    calcPiDartboard(n);
    auto endTime=chrono::high_resolution_clock::now();
	chrono::duration<float>  elapsed = endTime - startTime;
	writeTime(elapsed.count(), n);
    }

    return 0;
}
