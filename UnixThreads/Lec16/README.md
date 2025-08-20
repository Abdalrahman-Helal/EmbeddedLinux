# 🧵 pthread Example: Thread IDs

## 📌 About  
This program demonstrates how to create and manage threads using **POSIX threads (pthreads)** in C.  
- `pthread_create` → creates new threads.  
- `pthread_self` → gets the unique pthread ID (library-level).  
- `syscall(SYS_gettid)` → gets the Linux TID (kernel-level).  
- `pthread_join` → waits for threads to finish.  

---

## ⚙️ Code Flow  
1. Main creates `THREAD_NUM` threads.  
2. Each thread runs `routine`, which prints:  
   - `pthread ID`  
   - `Linux TID`  
3. Main waits for all threads to finish.  

---

