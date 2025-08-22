# 🎯 Thread Pool with Function Pointers

This project demonstrates a **flexible thread pool** that can execute **different types of tasks** using **function pointers**.

---

## 📌 About

- **4 worker threads** process different task types
- **Function pointers** allow dynamic task execution
- **100 tasks** alternating between sum and product operations
- **Generic task structure** supports any function with `(int, int)` signature

---

## ⚙️ Code Structure

### 🔹 Generic Task Definition
```c
typedef struct Task {
    void (*taskFunction)(int, int);   // Function pointer
    int arg1, arg2;                   // Arguments for the function
} Task;
```

### 🔹 Available Task Functions
```c
void sum(int a, int b) {
    usleep(50000);
    int sum = a + b;
    printf("Sum of %d and %d is %d\n", a, b, sum);
}

void prod(int a, int b) {
    usleep(50000);
    int prod = a * b;
    printf("Product of %d and %d is %d\n", a, b, prod);
}

void sumAndProduct(int a, int b) {
    int sum = a + b;
    int prod = a * b;
    printf("Sum and Product of %d and %d is %d and %d respectively\n", a, b, sum, prod);
}
```

### 🔹 Task Execution
```c
void executeTask(Task* task) {
    task->taskFunction(task->arg1, task->arg2);  // Call function via pointer
}
```

### 🔹 Task Submission with Function Selection
```c
void submitTask(Task task) {
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}
```

---

## 🔄 Execution Flow

### 🔹 Task Creation Pattern
```c
for(i = 0; i < 100; i++) {
    Task t = {
        .taskFunction = i % 2 == 0 ? &sum : &prod,  // Alternate functions
        .arg1 = rand() % 100,
        .arg2 = rand() % 100
    };
    submitTask(t);
}
```

**Task Distribution:**
- **Even indices** (0, 2, 4, 6...): `sum()` function
- **Odd indices** (1, 3, 5, 7...): `prod()` function

### 🔹 Worker Thread Processing
```c
while(1) {
    pthread_mutex_lock(&mutexQueue);
    while(taskCount == 0) {
        pthread_cond_wait(&condQueue, &mutexQueue);  // Wait for tasks
    }
    
    task = taskQueue[0];              // Get first task
    // Shift queue...
    taskCount--;
    
    pthread_mutex_unlock(&mutexQueue);
    executeTask(&task);               // Execute whatever function is stored
}
```

---

## 🎯 Function Pointer Benefits

| **❌ Fixed Task Type** | **✅ Function Pointers** |
|----------------------|-------------------------|
| Only one operation type | **Multiple operation types** |
| Hardcoded task logic | **Dynamic task execution** |
| Need separate queues | **Single unified queue** |
| Limited flexibility | **Easy to add new functions** |

---

## 🔧 Adding New Task Types

### 🔹 Easy Extension
```c
// 1. Define new function
void divide(int a, int b) {
    if(b != 0) {
        printf("Division of %d and %d is %.2f\n", a, b, (float)a/b);
    }
}

// 2. Submit task with new function
Task t = {
    .taskFunction = &divide,
    .arg1 = 20,
    .arg2 = 5
};
submitTask(t);
```

**No changes needed** to worker threads or queue management!

---

## 📊 Sample Output
```
Sum of 45 and 23 is 68
Product of 67 and 89 is 5963
Sum of 12 and 34 is 46  
Product of 78 and 56 is 4368
Sum of 91 and 15 is 106
...
```

---

## 🔐 Synchronization Details

### 🔹 Same Pattern as Before
- **Mutex** protects shared task queue
- **Condition variable** eliminates busy waiting
- **FIFO processing** maintains task order
- **Thread-safe** task submission and retrieval

### 🔹 Function Pointer Safety
```c
task->taskFunction(task->arg1, task->arg2);  // Safe function call
```
- Function pointer stored in task structure
- Arguments passed correctly to any function
- **Type safety** ensured by function signature `void (*)(int, int)`

---

## 🔑 Key Takeaways

- **Function pointers** make thread pools **highly flexible**
- **Same infrastructure** handles different task types
- **Easy to extend** with new operations
- **Generic task structure** supports various functions
- **Dynamic execution** based on stored function pointer
- **Perfect pattern** for heterogeneous task processing
- **Worker threads** don't need to know what functions they're executing