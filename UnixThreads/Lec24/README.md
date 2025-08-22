# 🧵 Binary Semaphore Example in C

This project demonstrates the use of a **binary semaphore** in C with POSIX threads for thread synchronization.

---

## 📌 About

- A single worker thread (`rouitne`) increments a shared variable `Fuel`
- The main thread waits until the worker thread finishes before freeing the allocated memory
- Synchronization is achieved using a **binary semaphore** (`semFuel`)

---

## ⚙️ How It Works

### 🔹 Shared Resource
```c
int *Fuel;
```
- Dynamically allocated integer
- Starts at 50
- Worker thread increments it by 50

### 🔹 Semaphore Initialization
```c
sem_init(&semFuel, 0, 0);
```
- The semaphore is initialized to **0**
- This means the main thread will **block** at `sem_wait()` until the worker thread calls `sem_post()`

### 🔹 Worker Thread
```c
*Fuel += 50;
printf("Current Value is %d\n", *Fuel);
sem_post(&semFuel);   // Signal main thread
```
- Increases the value of `Fuel`
- Signals (`sem_post`) the main thread that it can continue

### 🔹 Main Thread
```c
sem_wait(&semFuel);   // Block until worker signals
printf("Deallocating Fuel\n");
free(Fuel);
```
- Waits until the worker thread finishes updating `Fuel`
- Only then deallocates the memory safely

---

## 🔄 Execution Flow

1. **Main** creates the worker thread
2. **Main** waits at `sem_wait(&semFuel)` (blocked because initial value = 0)
3. **Worker thread** increments `Fuel` and signals with `sem_post()`
4. **Main** wakes up, frees memory, and joins the thread

---

## ✅ Binary Semaphore Concept

A **binary semaphore** can only take values **0** or **1**.

It is commonly used for:
- **Mutual exclusion** (like a mutex)
- **Signaling between threads** (like in this program)

---

## 🔁 Initialization Comparison

| Initialization | Meaning | Usage Pattern |
|---|---|---|
| `sem_init(&semFuel, 0, 0);` | Semaphore starts at **0** (locked)<br>First `sem_wait()` will **block** until another thread calls `sem_post()` | Used for **signaling**<br>(e.g., "wait until thread X finishes") |
| `sem_init(&semFuel, 0, 1);` | Semaphore starts at **1** (unlocked)<br>First `sem_wait()` passes **immediately** | Used for **mutual exclusion**<br>(acting like a mutex to protect critical section) |

---

## 🔑 Key Takeaways

- **Binary semaphore** (0/1) is a synchronization primitive
- **0 initialization** → Good for thread signaling (wait until event happens)
- **1 initialization** → Good for mutex-like behavior (only one thread in critical section)
- This example demonstrates the **signaling style** (0 initialization)

---

**Expected Output:**
```
Current Value is 100
Deallocating Fuel
```