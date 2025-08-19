# Race Conditions in Operating Systems

A **race condition** occurs in an Operating System when **two or more processes/threads access shared data or resources at the same time, and the final outcome depends on the timing of their execution**.

This usually leads to:
- Unexpected behavior  
- Inconsistent results  
- Incorrect program output  

### Example
Two threads incrementing a shared counter without synchronization:
```c
// Shared variable
int counter = 0;

// Thread A
counter = counter + 1;

// Thread B
counter = counter + 1;
