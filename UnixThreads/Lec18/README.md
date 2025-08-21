# 🧵 Static Initializers in Pthreads

This example demonstrates the use of **static initializers** for synchronization objects in POSIX threads:  
- `PTHREAD_MUTEX_INITIALIZER`  
- `PTHREAD_COND_INITIALIZER`

---

## 📌 What They Are

- **`PTHREAD_MUTEX_INITIALIZER`**  
  Creates and initializes a `pthread_mutex_t` with default attributes at **compile time**.  
  Equivalent to calling `pthread_mutex_init(&mutex, NULL)` at runtime.

- **`PTHREAD_COND_INITIALIZER`**  
  Creates and initializes a `pthread_cond_t` (condition variable) with default attributes at **compile time**.  
  Equivalent to calling `pthread_cond_init(&cond, NULL)` at runtime.

---

## ✅ Advantages (Pros)

- **Simplicity** → No need to explicitly call `pthread_mutex_init` or `pthread_cond_init`.
- **Readability** → Easy to see initialization at declaration.
- **Safety for globals/statics** → Useful for global/static mutexes and condition variables.
- **Less code** → Cleaner setup for default attributes.

---

## ⚠️ Limitations (Cons)

- **Default attributes only** → Cannot specify custom settings (e.g., recursive mutex, process-shared).
- **No error handling** → Unlike `pthread_mutex_init`, it doesn’t return an error code if something fails.
- **Not suitable for dynamic allocation** → If you `malloc` a mutex or condition variable, you must use the runtime init functions.
- **Optional destruction** → It’s **not mandatory** to call `pthread_mutex_destroy` or `pthread_cond_destroy` for statically initialized objects, but you **must** destroy them if reusing memory or dynamically allocating.
- **One-time use** → You cannot "reinitialize" with the static initializer after destruction.

---

## 📖 Example Code

```c
pthread_mutex_t mutexFuel = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condFuel = PTHREAD_COND_INITIALIZER;
