# 🎲 Multithreaded Dice Roller  

A C program that demonstrates **multithreading with POSIX threads** by rolling dice in parallel.  

## 📌 Overview  
- Spawns **8 threads**, each rolling a 6-sided dice.  
- Uses `pthread_create` / `pthread_join` for thread management.  
- Returns results dynamically (`malloc`), then frees memory after use.  
- Randomness seeded with `srand(time(NULL))`.  


