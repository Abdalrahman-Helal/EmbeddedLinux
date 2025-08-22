# 🧵 Producer-Consumer with Semaphores in C

This project demonstrates the **Producer-Consumer Problem** using:
- POSIX Threads (`pthread`)
- Semaphores
- Mutexes

---

## 📌 About
The program creates:
- A **Producer thread** → generates random numbers and adds them to a shared buffer.  
- A **Consumer thread** → removes numbers from the buffer and prints them.  

To avoid race conditions and buffer overflow/underflow:
- A **mutex** ensures only one thread accesses the buffer at a time.  
- **Semaphores** track the number of empty slots and filled slots in the buffer.  

---

## ⚙️ How It Works

### 🔹 Shared Resources
- `buffer[10]` → a fixed-size buffer (capacity = 10).  
- `count` → tracks how many items are currently in the buffer.  
- `mutexBuffer` → mutex lock for safe access.  
- `semEmpty` → counts **empty slots** in the buffer.  
- `semFull` → counts **filled slots** in the buffer.  

---

### 🔹 Initialization
```c
sem_init(&semEmpty, 0, 10);   // buffer starts with 10 empty slots
sem_init(&semFull, 0, 0);     // buffer starts with 0 filled slots
pthread_mutex_init(&mutexBuffer, NULL);
```
### 🔹 Producer Thread
```c
sem_wait(&semEmpty);          // wait if buffer is full
pthread_mutex_lock(&mutexBuffer); // locks the buffer

buffer[count] = x;            // add item
count++;

pthread_mutex_unlock(&mutexBuffer); // unlocks the buffer
sem_post(&semFull);           // signal: one more item available
```
---

### 🔹 Consumer Thread
```c
sem_wait(&semFull);           // wait if buffer is empty
pthread_mutex_lock(&mutexBuffer); // locks the buffer

y = buffer[count - 1];        // take item
count--;

pthread_mutex_unlock(&mutexBuffer); // unlocks the buffer
sem_post(&semEmpty);          // signal: one slot is free
```
---

