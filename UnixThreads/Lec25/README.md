# 🔒 Mutex vs Semaphore: Producer-Consumer Example

This project demonstrates the **critical difference** between **mutexes** and **semaphores** using a producer-consumer pattern.

---

## 📌 About

- **4 threads**: 2 consumers increment `Fuel`, 2 producers grant permission
- **Key Issue**: Mutex ownership rules make it wrong for this pattern

---

## ⚙️ Code Structure

### 🔹 Shared Resources
```c
int Fuel = 50;                    // Shared variable
sem_t semFuel;                    // Semaphore for signaling
```

### 🔹 Consumer Thread
```c
while(1) {
    sem_wait(&semFuel);           // Wait for permission
    Fuel += 50;                   // Update shared variable
    printf("Current Value is %d\n", Fuel);
}
```

### 🔹 Producer Thread
```c
while(1) {
    sem_post(&semFuel);           // Grant permission
    usleep(50000);                // 50ms delay
}
```

---

## 🔄 Execution Flow

1. Semaphore starts at 1
2. Consumer calls `sem_wait()` → decrements to 0
3. Next consumer blocks (semaphore = 0)  
4. Producer calls `sem_post()` → increments to 1
5. Blocked consumer unblocks and continues

---

## ⚖️ Mutex vs Semaphore

| **🔒 Mutex** | **🔢 Semaphore** |
|-------------|------------------|
| **Same thread** locks/unlocks | **Any thread** can wait/signal |
| Protects critical sections | Controls resource access |
| Binary (locked/unlocked) | Counter (0, 1, 2...) |

---

## ⚠️ Why Mutex Fails Here

```c
// Thread A (Consumer)
pthread_mutex_lock(&mutexFuel);    // Thread A locks

// Thread B (Producer) 
pthread_mutex_unlock(&mutexFuel);  // ❌ UNDEFINED BEHAVIOR!
```

**The Problem**: Only the thread that locks can unlock. Producer trying to unlock consumer's mutex = **undefined behavior**.

---

## ✅ Why Semaphore Works

```c
sem_wait(&semFuel);     // ✅ Any thread can wait
sem_post(&semFuel);     // ✅ Any thread can signal
```

**No ownership** - perfect for communication between different threads.

---

## 🔑 Key Takeaways

- **Mutex**: Same thread locks/unlocks (protect shared data)
- **Semaphore**: Different threads communicate (signaling/counting)  
- **Producer-consumer**: Always use semaphores, never mutexes