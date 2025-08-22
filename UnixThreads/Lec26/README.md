# 📊 Semaphore Value Monitoring Example

This project demonstrates **semaphore value tracking** and the importance of **timing in concurrent execution**.

---

## 📌 About

- **4 threads** compete for a semaphore initialized to **4**
- Each thread **monitors semaphore value** before and after operations
- **Sleep timing** creates visible differences in execution order

---

## ⚙️ Code Structure

### 🔹 Semaphore Setup
```c
sem_t sem;
sem_init(&sem, 0, 4);             // Start with 4 resources available
```

### 🔹 Thread Function
```c
void * rouitne (void* args) {
    int Index = *(int*)args;
    
    sem_wait(&sem);               // Acquire resource
    sleep(Index + 1);             // Hold resource for different times
    
    sem_getvalue(&sem, &semVal);  // Check current value
    printf("(%d) Before wait: %d\n", Index, semVal);
    
    sem_post(&sem);               // Release resource
    sem_getvalue(&sem, &semVal);  // Check value again
    printf("(%d) After post: %d\n", Index, semVal);
}
```

---

## 🔄 Execution Flow (With Sleep)

### 🔹 What Actually Happens

| Time | Thread | Action | Semaphore Value |
|------|--------|--------|----------------|
| T0 | All 4 | `sem_wait()` | 4→3→2→1→0 |
| T0 | All 4 | Start sleeping | 0 |
| T1 | Thread 0 | Wake up, `sem_post()` | 0→1 |
| T2 | Thread 1 | Wake up, `sem_post()` | 1→2 |
| T3 | Thread 2 | Wake up, `sem_post()` | 2→3 |
| T4 | Thread 3 | Wake up, `sem_post()` | 3→4 |

**Key Point**: All threads acquire the semaphore immediately (since 4 resources available), then sleep controls the **release order**.

---

## ⚠️ What Happens Without Sleep?

### 🔹 Problem: Race Condition
```c
// Without sleep(Index + 1):
sem_wait(&sem);
// No delay here!
sem_post(&sem);
```

**Issues:**
- **All threads execute too fast** - hard to see semaphore changes
- **Unpredictable order** - threads finish randomly
- **Values change rapidly** - difficult to observe the counting behavior
- **Less educational** - can't see how semaphore manages resources over time

---

## 🕐 Why `Index + 1`?

### 🔹 Creates Staggered Timing
```c
Thread 0: sleep(0 + 1) = 1 second
Thread 1: sleep(1 + 1) = 2 seconds  
Thread 2: sleep(2 + 1) = 3 seconds
Thread 3: sleep(3 + 1) = 4 seconds
```

**Benefits:**
- **Predictable order** - Thread 0 finishes first, Thread 3 last
- **Observable changes** - Can see semaphore value decrease/increase step by step
- **Clear demonstration** - Shows how semaphore tracks available resources
- **Avoids `+0`** - Thread 0 gets 1 second instead of 0 (instant execution)

---

## 📈 Understanding `sem_getvalue()`

### 🔹 What It Shows
```c
sem_getvalue(&sem, &semVal);      // Get current semaphore count
```

- **Remaining resources** available for other threads
- **After `sem_wait()`**: Shows how many resources are left (checked before wait but shows post-wait state)
- **After `sem_post()`**: Shows resources returned to the pool
---

## 🔑 Key Takeaways

- **`sem_getvalue()`** shows **remaining resources** in semaphore
- **Sleep timing** makes concurrent behavior **visible and predictable**
- **Without sleep**: Race conditions make output unpredictable
- **`Index + 1`**: Creates staggered execution (1s, 2s, 3s, 4s)
- **Semaphore counting**: Perfect for managing limited resources (like database connections, file handles)