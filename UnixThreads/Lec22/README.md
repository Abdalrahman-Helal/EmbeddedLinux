# 🔑 Semaphore Example: Login Queue Simulation (POSIX Threads)

This project demonstrates how to use **semaphores** with POSIX threads to simulate a **Login Queue** system, controlling how many users can log in at the same time.

---

## 📌 Code Summary
- We create **16 threads** (representing 16 users).  
- Semaphore initialized with value = **8** (`sem_init(&semaphore, 0, 8);`).  
  - This means **only 8 users can log in simultaneously**.  
- Each thread:
  - Prints: waiting in the login queue.  
  - Calls `sem_wait` → waits if the login “slots” are full.  
  - Prints: logged in.  
  - Simulates work with `sleep(rand() % 5 + 1)`.  
  - Prints: logged out.  
  - Calls `sem_post` → releases the login slot for other waiting users.  

---

## ⚙️ Mechanism

### `sem_init(&sem, pshared, value)`
- **`sem`** → the semaphore object.  
- **`pshared`** →  
  - `0` → semaphore shared **between threads** of the same process.  
- **`value`** → initial counter.  
  - Example: `8` → up to **8 users can log in simultaneously**.  


### `sem_wait(&sem)`
- **Decrements** the counter.  
- If counter > 0 → thread continues and logs in.  
- If counter = 0 → thread **blocks** until another user logs out (calls `sem_post`).  

### `sem_post(&sem)`
- **Increments** the counter.  
- If threads are blocked in `sem_wait`, **one gets unblocked** and can log in.  

---

## ✅ Example Walkthrough
Initial value = 8 → 8 login slots available  

- Users 0–7 → `sem_wait` succeeds → log in immediately.  
- Users 8–15 → `sem_wait` blocks → wait in the queue.  
- When a logged-in user calls `sem_post` → next user in the queue is unblocked and logs in.  
- This continues until all users have logged in and out.  

---

