# Using Mutex in C 

### What is a Mutex?
A **mutex** (short for *mutual exclusion*) is a synchronization primitive used to protect shared data from being accessed by multiple threads at the same time.  
It ensures that **only one thread can enter a critical section at a time**, preventing race conditions.

---

### Example Code

```c
void *routine(void)
{
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex);   // Acquire the lock
        mails++;                      // Critical section (shared variable update)
        pthread_mutex_unlock(&mutex); // Release the lock
    }
}
