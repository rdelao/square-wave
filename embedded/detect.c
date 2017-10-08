/**
  Description: Program to detect a hidden signal in white noise
  Author: Ryan De La O
*/

#include <stdio.h>
#include <stdlib.h>

char* usage() {
  return "\n \
      Usage: \n\
              ./white_noise_gen.out <FILE> <INT> \n";
};

int main( int argc, char** argv ) {
	if (argc != 3) {
        printf("Invalid arguments provided.\n");
        printf("%s", usage());
        return 1;
	};
	FILE *infile;
  infile = fopen(argv[1], "r");
  float hidden_amplitude = atof(argv[2]);
  int c;
  int new_data = 1;
  int max_digits = 10;
  char data[max_digits];
  long t;
  float a;
  float as[1000000];
  int i = 0;
  int first_sync_pulse = 0;
  long current_millisecond = 1;
  float *ptr;
  c = '~';
  // read csv into array of amplitudes (as)
  while (c != EOF) {
    if (c == '\n' || c == ',') {
      new_data = 1;
      i = 0;
    };
    if (new_data) {
      new_data = 0;
      i = 0;
      c = fgetc(infile);
      while (c != EOF && c != ',' && c != '\n') {
        data[i] = c;
        i++;
        c = fgetc(infile);
      };
      data[i] = '\0';

      if (c == ',') {
        t = atol(data);
        new_data = 1;
      } else if (c == '\n') {
        a = atof(data);
        as[t] = a;
        new_data = 1;
      };
      for (i = 0; i < max_digits; i++) {
        data[i] = '\0';
      };
    };
  };

  ptr = as;

  // find first sync pule and store pointer
  for(i = 0; i < 1000000; i++) {
    if (as[i] == hidden_amplitude && first_sync_pulse == 0) {
      first_sync_pulse = i;
      ptr = &as[i];
      break;
    };
  };
  if (first_sync_pulse == 0) {
    printf("Failed to discover hidden signal!\n\n");
  } else {
    printf("First sync pulse at microsecond: %d\n", first_sync_pulse);
    printf("Pointer to first millisecond of white noise: %p\n", ptr);
  };
	fclose(infile);
};
