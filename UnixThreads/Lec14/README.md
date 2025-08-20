#  pthread\_barrier Example

A simple C program demonstrating **barriers in multithreading** using `pthread_barrier_t`.

## 📌 What is a Barrier?

* A **synchronization point** for multiple threads.
* All threads must reach the barrier before any of them can proceed.
* Once the required number of threads arrives, the barrier "opens" and all waiting threads continue execution together.

## 📝 Key Information

* Initialized with `pthread_barrier_init(&barrier, NULL, count)` → `count` = number of threads required to pass.
* Threads call `pthread_barrier_wait(&barrier)` to wait at the barrier.
* If fewer threads arrive than expected, the program will **deadlock**.
* After all threads pass, the barrier **resets automatically** and can be reused.
* Destroy barrier with `pthread_barrier_destroy(&barrier)` when done.

## ⚡ Example Use Case
* Parallel computation: split work across threads, then synchronize before moving to the next phase.
