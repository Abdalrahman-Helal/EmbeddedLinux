# Mutex Trylock vs Lock (C - Pthreads)

This program demonstrates **non-blocking mutex access** using `pthread_mutex_trylock` with multiple threads in C.

---

## Overview
- Creates **4 threads** that attempt to acquire a shared mutex.  
- Threads print whether they **successfully got the lock** or **failed**.  
- Shows the difference between `trylock` and `lock`:

|          Function        |                    Behavior                        |
|--------------------------|----------------------------------------------------|
| `pthread_mutex_trylock`  | Non-blocking; returns immediately if locked.       |
| `pthread_mutex_lock`     | Blocking; waits until the mutex becomes available. |

---

## How It Works
1. Initialize a global mutex.  
2. Create 4 threads, each running `routine()`.  
3. Each thread tries `pthread_mutex_trylock`:
   - On success: prints `"Got Lock"` and unlocks.  
   - On failure: prints `"Didn't Get Lock"`.  
4. Main thread waits for all threads to finish using `pthread_join`.

---


