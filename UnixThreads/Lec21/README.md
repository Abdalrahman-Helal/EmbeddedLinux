# 🔑 Semaphore Example in C (POSIX Threads)

This project demonstrates how to use **semaphores** with POSIX threads to control access to a shared resource.

---

## 📌 Code Summary
- We create **4 threads**.
- Semaphore initialized with value = **3** (`sem_init(&semaphore, 0, 3);`).
- Each thread:
  - Calls `sem_wait` → decrements semaphore (may block if value = 0).
  - Prints a message (simulated work with `sleep(1)`).
  - Calls `sem_post` → increments semaphore (wakes up a waiting thread if any).

---

## ⚙️ Mechanism

### `sem_init(&sem, pshared, value)`
- **`sem`** → the semaphore object.  
- **`pshared`** →  
  - `0` → semaphore shared **between threads** of the same process.  
  - `!= 0` → semaphore shared **between processes** (must be placed in shared memory).  
- **`value`** → initial counter.  
  - Example: `3` → up to **3 threads** can run the routine at the same time.  
  - Example: `1` → this is the most common case, called a **binary semaphore** or **mutex-like semaphore** (only 1 thread allowed at a time). ✅  

### `sem_wait(&sem)`
- **Decrements** the counter.  
- If counter > 0 → thread continues.  
- If counter = 0 → thread **blocks** until another thread posts.  

### `sem_post(&sem)`
- **Increments** the counter.  
- If threads are blocked in `sem_wait`, **one gets unblocked** and continues.  

---

## ✅ Example Walkthrough
Initial value = 3  
- T1 → wait → value 2 → runs.  
- T2 → wait → value 1 → runs.  
- T3 → wait → value 0 → runs.  
- T4 → wait → value = 0 → **blocked**.  

When one of T1/T2/T3 calls `sem_post`, T4 is unblocked and runs.  

---
