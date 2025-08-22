# 🏊‍♂️Thread Pool with Condition Variables

This project demonstrates an **efficient thread pool** using **condition variables** to eliminate busy waiting.

---

## 📌 About

- **12 worker threads** wait efficiently for tasks
- **100 tasks** submitted for processing
- **Condition variables** replace busy waiting
- **50ms task simulation** with `usleep(50000)`

---

## ⚙️ Code Structure

### 🔹 Synchronization Objects
```c
pthread_mutex_t mutexQueue;       // Protects queue access
pthread_cond_t condQueue;         // Signals when tasks available
Task taskQueue[256];              // Shared task queue
int taskCount = 0;                // Current number of tasks
```

### 🔹 Task Submission
```c
void submitTask(Task task) {
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;    // Add to queue
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);  // Wake up waiting thread
}
```

### 🔹 Worker Thread Function
```c
void * startThread(void* args) {
    while(1) {
        pthread_mutex_lock(&mutexQueue);
        
        while(taskCount == 0) {
            pthread_cond_wait(&condQueue, &mutexQueue);  // Sleep until signal
        }
        
        task = taskQueue[0];          // Take first task
        // Shift remaining tasks left
        for(i = 0; i < taskCount-1; i++) {
            taskQueue[i] = taskQueue[i+1];
        }
        taskCount--;
        
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);           // Process task (50ms)
    }
}
```

---

## 🔄 Execution Flow

1. **Pool Creation**: 12 worker threads start and wait for tasks
2. **Initial State**: All threads call `pthread_cond_wait()` and **sleep**
3. **Task Submission**: Main thread submits 100 tasks rapidly
4. **Thread Wakeup**: Each `submitTask()` calls `pthread_cond_signal()`
5. **Task Processing**: Threads wake up, grab tasks, process them (50ms each)
6. **Efficient Waiting**: When no tasks, threads sleep instead of spinning

---

## ⚡ Key Improvements Over Previous Version

| **❌ Busy Waiting Version** | **✅ Condition Variables** |
|---------------------------|--------------------------|
| `while(1) { check queue }` | `pthread_cond_wait()` - **sleeps** |
| **100% CPU usage** while waiting | **0% CPU usage** while waiting |
| Continuous mutex locking | Only locks when **signaled** |
| Wastes system resources | **Efficient resource usage** |

---

## 🔐 Synchronization Details

### 🔹 Condition Variable Pattern
```c
// Producer (submitTask)
pthread_mutex_lock(&mutexQueue);
// Add task to queue
pthread_mutex_unlock(&mutexQueue);
pthread_cond_signal(&condQueue);     // Wake up one waiting thread

// Consumer (startThread)  
pthread_mutex_lock(&mutexQueue);
while(taskCount == 0) {
    pthread_cond_wait(&condQueue, &mutexQueue);  // Sleep + unlock, then lock on wakeup
}
// Process task
pthread_mutex_unlock(&mutexQueue);
```

### 🔹 Why `while` not `if`?
```c
while(taskCount == 0) {              // ✅ Use while loop
    pthread_cond_wait(&condQueue, &mutexQueue);
}
```
**Spurious Wakeups**: Thread might wake up even when no signal sent. `while` ensures we check the condition again.

---

## 🕐 Performance Analysis

### 🔹 Timeline Example
```
Time 0: All 12 threads sleeping in pthread_cond_wait()
Time 1: submitTask() signals → Thread 1 wakes up, processes task
Time 1.05: submitTask() signals → Thread 2 wakes up, processes task  
Time 1.1: submitTask() signals → Thread 3 wakes up, processes task
...
Time 5: All 100 tasks submitted, 12 threads processing in parallel
Time 10: All tasks completed, threads back to sleeping
```

**Benefits**: 12 threads can work in parallel, completing 100 tasks much faster than sequential processing.

---

## 🔑 Key Takeaways

- **Condition variables** eliminate CPU waste from busy waiting
- **`pthread_cond_wait()`** automatically unlocks mutex while sleeping
- **`pthread_cond_signal()`** wakes up exactly one waiting thread
- **Thread pool** provides excellent performance for batch processing
- **12 threads** can process multiple tasks simultaneously
- **Still has infinite loop issue** - threads never exit gracefully