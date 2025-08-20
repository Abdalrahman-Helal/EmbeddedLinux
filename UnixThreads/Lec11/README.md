# Fuel Threads Example Update: Broadcast vs Signal

This update continues from the previous example that used `pthread_cond_signal`. The focus here is on demonstrating **`pthread_cond_broadcast`** and its behavior with multiple threads.

---

## Key Notes on Broadcast

* `pthread_cond_broadcast(&CondFuel)` wakes **all waiting threads** instead of just one.
* This allows multiple Car threads to wake up and check fuel availability simultaneously.
* Important when multiple threads may be able to proceed after a condition is met.

**Comparison:**

| Function                        | Effect                                                              |
| ------------------------------- | ------------------------------------------------------------------- |
| `pthread_cond_signal(&cond)`    | Wakes **one waiting thread**. Only one thread proceeds per signal.  |
| `pthread_cond_broadcast(&cond)` | Wakes **all waiting threads**. Each thread re-checks the condition. |

**Behavior in this code:**

* 4 Car threads wait for fuel.
* Fuel\_Filling thread increases fuel and broadcasts.
* All waiting Car threads wake and check fuel.
* Mutex ensures safe access to shared `Fuel`, preventing race conditions.

**Important:**

* Always use a **while loop** around `pthread_cond_wait` to handle spurious wake-ups.
* Mutex is required to protect shared resources.
* Using broadcast is necessary when multiple threads may consume the resource concurrently.
