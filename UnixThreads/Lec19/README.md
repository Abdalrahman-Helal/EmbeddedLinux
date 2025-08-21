# Deadlock Example in C with Pthreads

## Overview
This project demonstrates the concept of a **deadlock** using multiple threads in C. Deadlocks occur when two or more threads are waiting indefinitely for resources held by each other, preventing further execution.

## How It Works
- Two shared resources: `Fuel` and `Water`.
- Two mutexes protect these resources: `mutexFuel` and `mutexWater`.
- Each thread randomly locks the mutexes in different orders:
  - Some threads lock `mutexFuel` first, then `mutexWater`.
  - Others lock `mutexWater` first, then `mutexFuel`.
- This can lead to a situation where threads **wait forever** for each other to release a mutex, causing a deadlock.

## Key Concepts
- **Mutex:** A mutual exclusion lock used to protect shared resources.
- **Deadlock:** A situation where threads are stuck waiting for each other, halting progress.

