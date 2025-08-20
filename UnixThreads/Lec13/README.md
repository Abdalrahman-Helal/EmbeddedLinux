# 🎲 Multithreaded Dice Roller with pthread\_exit

A C program that demonstrates **multithreading with POSIX threads** and the usage of `pthread_exit`.

## 📌 Overview

* Spawns a single thread to roll a 6-sided dice.
* Uses `pthread_create` / `pthread_exit` for thread management.
* Thread returns its result dynamically using `malloc`.
* The main thread exits using `pthread_exit`, allowing worker threads to continue running.
* Randomness is seeded with `srand(time(NULL))`.

## 📝 Key Concepts

### 1️⃣ Thread Routine

```c
void *RollDice()
```

* Generates a random dice value.
* Allocates memory dynamically (`malloc`) to store the result.
* Uses `pthread_exit((void *) result)` to terminate the thread and return the pointer.
* `sleep(2)` simulates a delay to show asynchronous execution.
* Prints the result from inside the thread.

### 2️⃣ Main Thread

```c
pthread_exit(0);
```

* Exits the main thread **without terminating the entire process**.
* Allows worker threads to continue execution.
* Any code after `pthread_exit` in main **will not execute**.

### 3️⃣ Dynamic Memory for Thread Return Values

* Thread routines should not return addresses of local variables (would become invalid after thread ends).
* Allocate memory using `malloc` to safely return data to other threads.

### 4️⃣ Important Notes

* In this example, the `pthread_join` code **will never execute** because `pthread_exit` terminates main before reaching it.
* To receive the thread's return value, `pthread_join` must be called **before main thread exits**.
* Using `pthread_exit` in main is useful when you want the program to continue running while worker threads finish asynchronously.

## ⚠️ Takeaways

1. `pthread_exit` = terminate **current thread** safely and optionally return a value.
2. `pthread_join` = wait for a thread to finish and retrieve its return value.
3. Memory returned from a thread must be dynamically allocated to persist after thread termination.
4. Order matters: calling `pthread_exit` in main **before** `pthread_join` prevents receiving return values.
