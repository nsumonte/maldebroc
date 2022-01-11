#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include<iostream>
#include <math.h>
#include <omp.h>
using namespace std;

int perteneceA(int maxiteration, complex<float> complexnum) {
    float realx, imagx, realc, imagc;
    complex<float> xn = complexnum;
    realc = real(complexnum);
    imagc = imag(complexnum);
    for (int iteration = 0; iteration<maxiteration; iteration++){
        xn = pow(xn,2);
        realx = real(xn);
        imagx = imag(xn);
        xn = decltype(xn)((float) realc + realx, (float) imagc + imagx);
        if( abs(xn) > 2 ) return 0;
    }
    return 1;
}

int main(){
    int max_n, count,threads;
    float real,imag, max_points;
    double start,end,times;
    start =  omp_get_wtime();
	count = 0;
    threads = 24;
    max_points = 10000000;
	max_n = 1640;
    int* array = (int*) calloc(threads, sizeof(int));
    complex<float> complexnum;
    complex<float>* c = (complex<float>*) calloc(max_points,sizeof(complex<float>));
    for(int p = 0; p < max_points; ++p){
            real = (float)rand() / (float)RAND_MAX;
            imag = (float)rand() / (float)RAND_MAX;
            complexnum = decltype(complexnum)((float)(real * 4) - 2, (float)(imag * 4) - 2);
            c[p] = complexnum;
            }
    #pragma omp parallel for num_threads(threads)
    for (int i= 0; i < max_points; ++i){
            int id = omp_get_thread_num();
            array[id] += perteneceA(max_n, c[i]);
            }

    for (int k=0;k<threads;k++) {
        count+= array[k];
    }
    end =  omp_get_wtime();
    times = end - start;
    printf("La aproximación de Pixel Counting es : %f\n", (count / max_points) * 16);
    printf("Este proceso demoró %f segundos.\n", times);
    free(array);
    free(c);
    return count;
}