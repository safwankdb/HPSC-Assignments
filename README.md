# High Performance Scientific Computing

This repository contains coding assignments of the **ME766**: High Performance Scientific Computing course at IIT Bombay.

## Assignment 1

- Write serial and parallel functions to integrate cos(x) in some range.
- Do a convergence study with number of samples / grid points.
- Test performance improvement with different number of threads.
  
    ### Usage

    ```bash
    $ make 
    Compiling Trapezoid Serial
    Compiling Trapezoid Parallel
    Compiling Monte Carlo Serial
    Compiling Monte Carlo Parallel

    Testing Trapezoid Serial

            Divisions = 100000000
            Integral = 2
            Time Elapsed = 897 ms



    Testing Trapezoid Parallel

    Threads = 2

            Divisions = 100000000
            Integral = 2
            Time Elapsed = 503 ms


    Threads = 4

            Divisions = 100000000
            Integral = 2
            Time Elapsed = 340 ms


    Threads = 6

            Divisions = 100000000
            Integral = 2
            Time Elapsed = 286 ms


    Threads = 8

            Divisions = 100000000
            Integral = 2
            Time Elapsed = 254 ms



    Testing Monte Carlo Serial

            Samples = 100000000
            Integral = 2.00005
            Time Elapsed = 3411 ms



    Testing Monte Carlo Parallel

    Threads = 2

            Samples = 100000000
            Integral = 1.99958
            Time Elapsed = 1825 ms


    Threads = 4

            Samples = 100000000
            Integral = 1.99985
            Time Elapsed = 1111 ms


    Threads = 6

            Samples = 100000000
            Integral = 1.99998
            Time Elapsed = 1144 ms


    Threads = 8

            Samples = 100000000
            Integral = 2.00008
            Time Elapsed = 1155 ms
    ```

---
