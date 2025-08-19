# Multithreaded Prime Sum Calculator

## Description
This project demonstrates the use of **POSIX threads (pthreads)** in C for concurrent computation. The program calculates sums of prime numbers in parallel using multiple threads, then aggregates these results into a total sum. It illustrates thread creation, joining, and safe memory handling.

## Features
- Multithreading with `pthread_create` and `pthread_join`
- Local sum calculation inside threads
- Aggregation of results into a global sum
- Dynamic memory allocation with proper cleanup
- Simple example for learning thread-safe programming in C

## Code Overview
- `primes[10]`: Array of the first 10 prime numbers.
- `routine(void *arg)`: Thread function that calculates the sum of 5 consecutive primes starting at the given index. The result is returned to the main thread.
- `main()`: 
  - Creates two threads to process the prime numbers array.
  - Waits for threads to finish using `pthread_join`.
  - Aggregates the sums returned by threads into `GlobalSum`.
  - Frees dynamically allocated memory.