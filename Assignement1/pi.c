/*
============================================================================
Filename    : pi.c
Author      : Mamie Robin Georges Francis & Montial Charline
SCIPER		: 275234 274902
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include <omp.h>

double calculate_pi (int num_threads, int samples);

int main (int argc, const char *argv[])
{

    int num_threads, num_samples;
    double pi;

    if (argc != 3) {
        printf("Invalid input! Usage: ./pi <num_threads> <num_samples> \n");
        return 1;
    } else {
        num_threads = atoi(argv[1]);
        num_samples = atoi(argv[2]);
    }

    set_clock();
    pi = calculate_pi (num_threads, num_samples);

    printf("- Using %d threads: pi = %.15g computed in %.4gs.\n", num_threads, pi, elapsed_time());

    return 0;
}


double calculate_pi (int num_threads, int samples)
{
    double pi;
    /* Your code goes here */
   
    double xi;
    double yi;
	rand_gen seed = init_rand();
	double samples_inside = 0;
    omp_set_dynamic(0); // Ensure that exactly num_threads threads will be used and not less
    omp_set_num_threads(num_threads); // set the number of threads
    #pragma omp parallel private(xi, yi)
    {
		for(size_t i = 0; i < samples / num_threads; ++i){
			xi = next_rand(seed); // yields a number between 0 and 1
			yi = next_rand(seed);
			if(xi * xi + yi * yi <= 1){
				#pragma omp atomic
				++samples_inside;
			}
		}
    
	}
	pi = 4. * (samples_inside / samples);
    return pi;
}
