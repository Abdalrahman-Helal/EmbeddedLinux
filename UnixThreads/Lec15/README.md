# 🎲 Dice Game with pthreads and Barriers

## 📌 Overview
This program demonstrates the use of **POSIX threads (pthreads)** and **barriers** to synchronize multiple threads with the main thread.  
- Each thread simulates rolling a dice.  
- The main thread waits until all threads finish rolling before calculating the winner.  
- After the winner is decided, threads print whether they won or lost.

---

## ⚙️ Execution Flow
1. **Thread Creation**  
   - Main creates `THREAD_NUM` threads.  
   - Each thread executes the function `RollDice()`.

2. **First Barrier (`barrierRolledRice`)**  
   - Each thread rolls a dice and then waits at the barrier.  
   - The main thread also waits at the same barrier.  
   - Once all (`THREAD_NUM + 1`) participants arrive, the barrier releases everyone.

3. **🏆 Winner Calculation (Main thread only)**  
   - After the **first barrier** is released:
     - **Main thread** continues to calculate the maximum dice value and fills the `status[]` array.  
     - **All other threads** immediately reach the **second barrier** (`barrierCalculated`) and wait there.  
   - This means:
     - While **main is busy** deciding the winner,  
     - The **8 worker threads are paused**, waiting for main to finish and join them at the second barrier.

4. **Second Barrier (`barrierCalculated`)**  
   - Main thread waits after updating results.  
   - Worker threads are already waiting here.  
   - Once all arrive, the barrier releases everyone.

5. **Result Printing**  
   - Each thread checks its `status[Index]` and prints **Won** or **Lost**.

---

## 🔑 Important Notes About Barriers
- A **barrier** is a synchronization point.  
- Threads **stop at the barrier** until the required number of participants has arrived.  
- When the last participant arrives, **all are released together**.

### Why `THREAD_NUM + 1`?
- Because the barrier must wait for:  
  - All worker threads (`THREAD_NUM`)  
  - **Plus the main thread** (which also participates in the synchronization)  
- Without the `+1`, only the threads would wait, but main would not, breaking synchronization.

---


