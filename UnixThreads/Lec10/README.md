# Condition Variables Example in C

This project demonstrates the use of **condition variables** in C with **POSIX threads (pthread)**.
It shows how threads can **wait for a condition** and be **notified when the condition is met**.

---

## Key Concepts

### 1. Condition Variables

* Allow a thread to **wait until a specific condition occurs**.
* Main functions:

  * `pthread_cond_wait(&cond, &mutex)`

    * Releases the mutex and puts the thread to sleep until it receives a signal.
    * Re-acquires the mutex upon waking and continues execution.
  * `pthread_cond_signal(&cond)`

    * Wakes up **one waiting thread**.
  * `pthread_cond_broadcast(&cond)`

    * Wakes up **all waiting threads**.
* **Important:** Always use **mutex** with condition variables to protect shared resources.

### 2. Mutex

* Protects **shared data** from race conditions.
* Ensures only one thread modifies shared data at a time.

---

## Code Overview

### Global Variables

```c
int Fuel = 0;
pthread_mutex_t MutexFuel;
pthread_cond_t CondFuel;
```

* `Fuel`: shared resource representing the amount of fuel.
* `MutexFuel`: protects access to `Fuel`.
* `CondFuel`: condition variable to signal when fuel is available.

---

### Thread 1: Fuel\_Filling

```c
for(int i = 0; i < 5; i++)
{
    pthread_mutex_lock(&MutexFuel);
    Fuel += 15;
    printf("Filling Fuel %d \n", Fuel);
    pthread_mutex_unlock(&MutexFuel);
    pthread_cond_signal(&CondFuel);
    sleep(1);
}
```

* Adds **15 units of fuel** per iteration.
* Signals the waiting car thread after filling fuel.
* Mutex ensures **safe updates** to `Fuel`.

---

### Thread 2: Car

```c
pthread_mutex_lock(&MutexFuel);
while(Fuel < 40)
{
    printf("No Fuel. Waiting...\n");
    pthread_cond_wait(&CondFuel, &MutexFuel);
}
Fuel -= 40;
printf("Got Fuel. Now Left %d \n", Fuel);
pthread_mutex_unlock(&MutexFuel);
```

* Checks if fuel is less than 40.
* If yes, **waits** using `pthread_cond_wait` until `Fuel_Filling` signals availability.
* Once enough fuel is available, consumes 40 units.
* **Important:** `while` is used instead of `if` to **re-check the condition** after waking up.

---

## Execution Flow

1. **Car thread** starts and waits if fuel < 40.
2. **Fuel\_Filling thread** adds fuel incrementally and signals the car thread.
3. Once fuel ≥ 40, **Car thread consumes fuel** and prints remaining fuel.
4. Mutex + condition variable ensures **safe synchronization** and prevents busy waiting.

---

## Important Points

* Condition variables **avoid busy waiting**.
* Always pair `pthread_cond_wait` with a **mutex**.
* Use **`while`** instead of `if` for condition checks to handle spurious wake-ups or multiple threads.
* **Mutex** protects shared resources; **condition variable** coordinates threads based on conditions.
