# Unix Threads in C: A Comprehensive Guide

This repository serves as a practical companion to a series of lectures on Unix Threads (pthreads) in C programming. It provides hands-on examples and code implementations for various threading concepts, designed to deepen understanding and facilitate practical application.

## Topics Covered

This folder contains code examples corresponding to the following topics from the associated YouTube playlist:

1.  **Introduction to pthreads**: Basic concepts and creation of threads.
2.  **Processes vs. Threads**: Understanding the fundamental differences and use cases.
3.  **Race Conditions**: Identifying and mitigating common concurrency issues.
4.  **Mutexes (pthread_mutex)**: Synchronization primitives for protecting shared resources.
5.  **Thread Creation in Loops (pthread_create)**: Managing multiple threads efficiently.
6.  **Retrieving Return Values (pthread_join)**: Synchronizing thread termination and collecting results.
7.  **Passing Arguments to Threads**: Sending data to thread functions.
8.  **Practical Examples**: Real-world applications of threading concepts (e.g., summing numbers from an array).
9.  **Trylock vs. Lock**: Differences in mutex acquisition.
10. **Condition Variables**: Signaling and waiting for specific conditions.
11. **Signaling Condition Variables (pthread_cond_signal vs pthread_cond_broadcast)**: Different methods for waking up waiting threads.
12. **Practical Example for pthread_mutex_trylock**: Advanced mutex usage.
13. **pthread_exit**: Terminating threads gracefully.
14. **Barriers (pthread_barrier)**: Synchronizing multiple threads at a specific point.
15. **Practical Example to Barriers**: Demonstrating barrier usage.
16. **pthread_t**: Understanding thread identifiers.
17. **Detached Threads**: Threads that do not require joining.
18. **Static Initializers in PTHREAD API**: Initializing synchronization objects.
19. **Deadlocks**: Preventing and resolving deadlocks in multithreaded applications.
20. **Recursive Mutexes**: Mutexes that can be locked multiple times by the same thread.
21. **Semaphores**: General-purpose synchronization mechanisms.
22. **Practical Example using Semaphores (Login Queue)**: Applying semaphores to a real-world problem.
23. **Producer-Consumer Problem**: Classic concurrency problem solved with threading.
24. **Binary Semaphores**: Semaphores with a maximum value of 1.
25. **Difference between Binary Semaphores and Mutexes**: Clarifying their distinct roles.
26. **Getting the Value of a Semaphore**: Inspecting semaphore state.
27. **Parallelism vs. Concurrency**: Distinguishing between simultaneous execution and managing multiple tasks.
28. **Thread Pools**: Efficiently managing a collection of worker threads.
29. **Thread Pools with Function Pointers**: Advanced thread pool implementation.

## Getting Started

To explore the code examples, clone this repository:

```bash
git clone https://github.com/Abdalrahman-Helal/EmbeddedLinux.git
cd EmbeddedLinux/UnixThreads
```

Each `Lec` folder contains the source code (`.c` files) for the corresponding lecture.

## Resources

For a detailed explanation of these concepts, please refer to the full YouTube playlist:

[Unix Threads in C Playlist](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=VfKpeqymMzCrIym5)
