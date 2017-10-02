/**
  Description: Program to generate a hidden signal in white noise
  Author: Ryan De La O
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define global constants
#define minimum_amplitude -10.0
#define maximum_amplitude 10.0
#define amplitude_magnitude_granularity 4

// range of micros to offset a signal from start (between 0 and 1 ms)
#define minimum_micro_offset 0
#define maximum_micro_offset 1000

// One microsecond (unsure if this should vary)
#define minimum_singal_length 0.0000001
#define maximum_signal_length 0.0000001

// Give the hidden signal a period of 1 ms
#define hidden_micro_period (long) 1000

// Length of total captured signal in milliseconds
#define singal_milli_length 10


/**
  Generates a random floating point number between the min and max

  truncates to the specified number of decimal places.

  Able to handle negative min and max values.
  If the min and max values are identical, it will return that value.
*/
double rand_double(double min, double max, int decimal_places) {
	if (min == max) {
        return min;
	};
	double x = min + (double) rand() / (RAND_MAX / abs(max-min));
	int magnitude = pow(10.0, decimal_places);
	double trucated = trunc((magnitude * x)) / magnitude;
    return trucated;
};

/**
  Generates a random long between the min and max

  Able to handle negative min and max values.
  If the min and max values are identical, it will return that value.
*/
long rand_long(long min, long max) {
    if (min == max) {
        return min;
	};
	long x = min + (long) rand() / (RAND_MAX / abs(max-min));
    return x;
}

char* usage() {
  return "\n \
      Usage: \n\
              ./white_noise_gen.out <FILE> \n";
};

int main( int argc, char** argv ) {
	if (argc != 2) {
        printf("Invalid arguments provided.\n");
        printf("%s", usage());
        return 1;
	};
	FILE *outfile;
    outfile = fopen(argv[1], "w+");
    srand(time(NULL));
	// Generate random amplitude for 1 microsecond square wave
	double hiddin_amplitude = rand_double(0, maximum_amplitude, amplitude_magnitude_granularity);
	// generate random frame offset for the square wave
	long hidden_offset = rand_long(minimum_micro_offset, maximum_micro_offset);
    long t_max = singal_milli_length * ((long) 1000);
	long t;
	printf("Generated hidden signal offset: %li microsends\n", hidden_offset);
	printf("Generated hidden signal amplitude: %.9f\n", hiddin_amplitude);
    
	for (t = 0; t < t_max; t++) {
        if (((t - hidden_offset) % (long) 1000) == 0) {
        	// we need to write our hidden signal
      	    fprintf(outfile, "%li,%0.6f\n", t, hiddin_amplitude);
        } else {
            fprintf(
            	outfile,
            	"%li,%0.6f\n",
            	t,
            	rand_double(
            	    minimum_amplitude,
            	    maximum_amplitude,
            	    amplitude_magnitude_granularity
        	    )
    	    );
        };
	};
	fclose(outfile);
};
