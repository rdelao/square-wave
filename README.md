# square-wave
White noise in square wave


# Generate white noise data

In the `embedded` module, comple `white_noise_gen.c` program:

```bash
gcc white_noise_gen.c white_noise_gen.out -lm
```

This program will generate a file with x and y coordinates to the specified input file.

Example usage:

```bash
./white_noise_gen.out coordinates.txt
```

Each set of coordinates are written on a new line in the form `x,y`

Where `x` is the time elapsed in microseconds (starting at 0) and `y` is the recorded 
amplitude, truncated to 4 decimal places.

The amplitudes range from `[-10, 10]`.

Due to the amount of data being generated, some of the "white noise" data points 
will have the same amplitude as the "hidden signal".

The program will generate a total of 10ms of data, each datapoint representing
and observed microsend, with `1000` points representing
the "hidden signal", evenly spaced 1ms apart. The "hidden signal" has an offset between 
`[0, 1000]` microseconds before it's first impulse. The "hidden signal" amplitude 
is a random number generated at runtime between `[0, 10]` and is trunctated to 4
decimal places.


