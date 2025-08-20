# 🎲 Multithreaded Dice Roller

A C program that demonstrates **multithreading with POSIX threads** by rolling dice in parallel.

## 📌 Overview

* Spawns **8 threads**, each rolling a 6-sided dice.
* Uses `pthread_create` / `pthread_join` for thread management.
* Returns results from threads using **dynamic memory allocation (`malloc`)**.
* Each thread returns a pointer to its result, which is collected in `main`.
* Memory is freed after reading the results to avoid leaks.
* Randomness seeded with `srand(time(NULL))`.

## 📝 Key Points

1. **Dynamic Return from Threads:**

   * Thread routines cannot safely return addresses of local variables.
   * Instead, allocate memory on the heap using `malloc`.
   * Return the pointer (`void *`) from the thread routine.

2. **Collecting Results in `main`:**

   * Use `pthread_join` to get the returned pointer.
   * Dereference the pointer to get the value.
   * Free memory after use.

3. **Example:**

```c
int *res;
pthread_join(thread, (void **)&res);
printf("Result: %d\n", *res);
free(res);
```
