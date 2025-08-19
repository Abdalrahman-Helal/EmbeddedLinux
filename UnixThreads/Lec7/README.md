# Multithreaded Prime Number Printer – Passing Arguments to Threads

This program demonstrates **multithreading in C** using the POSIX Threads (pthreads) library.  
Each thread prints a single prime number from a predefined list, **with each thread receiving its index as a dynamically allocated argument**.

---

## Features
- Creates **10 threads**, one per prime number.  
- **Passes thread arguments dynamically** using `malloc` to ensure each thread gets a unique index.  
- Safely frees allocated memory inside each thread.  
- Uses `pthread_join` to wait for all threads to finish.