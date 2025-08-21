# 🧵 pthread_detach in C

## 📌 About
This project explains the difference between **`pthread_join`** and **`pthread_detach`** in POSIX threads.

By default, threads are **joinable**, meaning another thread must call `pthread_join()` to clean up their resources.  
If you don’t join, those resources stay allocated → memory leak.

`pthread_detach()` changes this behavior:
- Tells the system you **will not join** the thread.
- The OS will **clean up automatically** once the thread finishes.

---
## 🔹 Example Code

### Using `pthread_join`
```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* routine(void* arg) {
    sleep(1);
    printf("Thread finished\n");
    return NULL;
}

int main() {
    pthread_t t1;
    pthread_create(&t1, NULL, routine, NULL);

    // Wait for the thread to finish
    pthread_join(t1, NULL);

    printf("Main finished\n");
    return 0;
}
```

## 🔄 `pthread_join` vs `pthread_detach`

| Feature              | `pthread_join()`                        | `pthread_detach()`           |
|----------------------|------------------------------------------|-------------------------------|
| Who frees resources? | Caller thread (via join)                 | OS automatically              |
| Can wait for result? | ✅ Yes                                   | ❌ No                         |
| Synchronization      | ✅ Blocks until thread ends              | ❌ Non-blocking               |
| Use case             | Need result, sync threads               | Fire-and-forget threads       |

---

## ✅ Key Notes
- Use **`pthread_join`** when:
  - You need the thread’s result.  
  - You want to block until the thread finishes.  
- Use **`pthread_detach`** when:
  - You don’t care about the result.  
  - Threads run independently (fire-and-forget).  
- 🚨 Never call `pthread_join()` on a detached thread → it will fail.  
- If the main thread exits before detached threads finish, the process may still end unless you keep it alive (e.g., with `sleep()` or by doing other work).  

---

# 🧵 Detached Threads in C (Using `pthread_attr_t`)

## 📌 About

This project demonstrates how to create **detached threads** in C using **POSIX threads (pthreads)** and `pthread_attr_t`.

By default, when you create a thread with `pthread_create()`, the thread is **joinable**:

* Another thread (usually `main`) must call `pthread_join()` to clean up its resources.
* If you forget to join, the thread's resources stay allocated (memory leak).

In this code, we change the default and create threads as **detached**:

* The OS frees their resources automatically when they finish.
* No need to call `pthread_join()`.

---

## 🔹 Example Code

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 2

void* routine(void* args)
{
    sleep(1);
    printf("Finished Execution \n");
    return NULL; // explicit return for clarity
}

int main(void)
{
    pthread_t th[THREAD_NUM];

    // Attribute object to create threads in detached state
    pthread_attr_t detachedThread;
    pthread_attr_init(&detachedThread);
    pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0)
        {
            perror("Failed to Create Thread");
        }
    }

    pthread_attr_destroy(&detachedThread);

    // Keep the process alive until detached threads finish
    pthread_exit(0);
}
```

## 🔄 Joinable vs Detached Threads

| Feature              | Joinable (Default)                    | Detached (Explicit)         |
| -------------------- | ------------------------------------- | --------------------------- |
| Default state        | ✅ Yes                                 | ❌ No (must be set manually) |
| Who frees resources? | Caller thread via `pthread_join()`    | OS automatically            |
| Can wait for result? | ✅ Yes                                 | ❌ No                        |
| Synchronization      | ✅ Blocks until thread ends (via join) | ❌ Non-blocking              |
| Use case             | Need result / coordination            | Fire-and-forget tasks       |

---

## ✅ Key Notes

* Threads are **joinable by default** when created with `pthread_create()`.
* We explicitly switch them to **detached** using:

  ```c
  pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);
  ```
* Detached threads clean themselves up automatically when done.
* 🚨 You cannot `pthread_join()` a detached thread → it will fail.
* Use `pthread_exit(0)` in `main` to keep the process alive until all detached threads finish.

---

```






