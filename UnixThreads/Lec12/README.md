# Multi-Chef Stove Simulation

This program simulates 10 **chefs (threads)** trying to use 4 stoves concurrently. Each stove has limited fuel, and chefs randomly consume fuel while demonstrating **mutex usage** for thread-safe access.

---

## Key Concepts
- **Threads (`pthread`)**: Each chef runs as a separate thread.
- **Mutex (`pthread_mutex_t`)**: Protects each stove from concurrent access.
- **Trylock (`pthread_mutex_trylock`)**: Checks stove availability without blocking.
- **Random numbers (`rand() % 30`)**: Determines fuel consumption for each chef.
- **Sleep (`usleep`)**: Simulates cooking time.

---

## Code Behavior
- Each chef thread loops over 4 stoves.
- If a stove is free (`trylock` succeeds):
  - Generates a random `FuelNeeded`.
  - If fuel is sufficient:
    - Deduct fuel.
    - Print remaining fuel.
    - Exit loop.
  - If fuel insufficient:
    - Print "No More Fuel. Going Home..."
- If all stoves are busy:
  - Print "No Stove Available yet, Waiting..."
  - Wait 0.3s (`usleep`) and retry from the first stove.

---

## Mutex Usage
| Action | Purpose |
|--------|---------|
| `pthread_mutex_trylock` | Attempts to acquire stove without blocking. |
| `pthread_mutex_unlock`  | Releases stove after use. |

---

## Summary
- Demonstrates **thread-safe resource access** with mutexes.
- Shows how **trylock** allows non-blocking access.
- Simulates **concurrent resource consumption** with random amounts.
- Useful for understanding **multi-threaded resource management**.
