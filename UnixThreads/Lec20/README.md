# 🔁 Recursive Mutex in Pthreads

## 📌 What is a Recursive Mutex?
A **recursive mutex** allows the **same thread** to lock a mutex **multiple times** without causing a deadlock.  
- With a normal mutex → calling `pthread_mutex_lock()` twice by the same thread **blocks forever**.  
- With a recursive mutex → the thread can lock it multiple times, but must **unlock the same number of times**.

---

## ⚙️ How It Works
- A recursive mutex is initialized with the attribute `PTHREAD_MUTEX_RECURSIVE`.  
- This lets the same thread call `pthread_mutex_lock()` multiple times.  
- Each `lock` must have a corresponding `unlock`.  
- Without recursive type, the second `pthread_mutex_lock()` by the same thread would cause a **deadlock**.

---

## ✅ Key Takeaways
-  Use recursive mutex when the same thread may need to acquire the same lock multiple times.  
-  Always unlock as many times as you lock, or the mutex stays locked.  
-  Recursive mutexes are heavier than normal mutexes → use them only if neede.  
