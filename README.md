# square-wave
White noise in square wave


# Running the Demo

```bash
./bin/demo.sh
```

# Generate white noise data

## compiling

In the `embedded` module, compile `white_noise_gen.c` program:

```bash
gcc white_noise_gen.c -o white_noise_gen -lm
```

This program will generate a file with x and y coordinates to the specified input file.

## running

Example usage:

```bash
./bin/white_noise_gen data.txt
```

Each set of coordinates are written on a new line in the form `x,y`

Where `x` is the time elapsed in microseconds (starting at 0) and `y` is the recorded 
amplitude, truncated to 4 decimal places.

The amplitudes range from `[-10, 10]`.

Due to the amount of data being generated, some of the "white noise" data points 
will have the same amplitude as the "hidden signal".

The program will generate a total of 10ms of data, each datapoint representing
and observed microsend, with `10` points representing
the "hidden signal", evenly spaced 1ms apart. The "hidden signal" has an offset between 
`[0, 1000]` microseconds before it's first impulse. The "hidden signal" amplitude 
is a random number generated at runtime between `[0, 10]` and is trunctated to 4
decimal places.

# Detect hidden signal in white noise data

## compiling

In the `embedded` module, compile `detect.c` program:

```bash
gcc detect.c -o detect
```


## running

Example usage:

```bash
./bin/detect data.txt <hidden amplitude>
```

This program will find the provided hidden amplitude in the
provided data parsed from the provided file.

It will print the microsecond where the first wave pulse is found
and a pointer to the location in the data array that the first
millisecond of the wave begins.

if not signal is found, it exits with a message.



