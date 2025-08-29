# Chapter 3: System Programming Concepts

This chapter gives the essential basics you need before starting real system programming in Linux/UNIX.

## System Calls

* The main way a program talks to the kernel (e.g., open a file, read from disk, create a new process).
* The book explains the steps that happen when a system call is executed.

## Library Functions

* Not everything directly uses the kernel.
* Sometimes library functions (like those in **glibc**) wrap system calls or provide extra features.
* The chapter shows the differences between system calls and library functions.

## Error Handling

* Always check the return value of a system call or library function.
* The book introduces standard ways to check errors (like using **errno**) and provides helper functions to report errors.

## Portability

* Writing code that can run on different UNIX/Linux systems.
* Requires **feature test macros** and using **standard system data types**.

---
## 3.1 System Calls
---

A **system call** is the official way for a program to ask the **kernel** to do something on its behalf. Programs can’t directly touch hardware or kernel memory, so they use system calls as a controlled entry point.

### What system calls do:

* Create new processes.
* Perform input/output (I/O).
* Set up communication between processes (like pipes).

### General rules:

* **User mode → Kernel mode:**
  When a system call happens, the CPU switches from user mode to kernel mode so the kernel can safely access protected resources.

* **Fixed set of calls:**
  The list of system calls is fixed, and each one has a unique number. (Programs usually use names, not numbers.)

* **Arguments transfer:**
  System calls often take arguments to send data from the program (user space) to the kernel (kernel space), and sometimes return results back.

👉 **In short:** a system call is the bridge between a user program and the kernel, making low-level system services accessible in a safe way.

---
## System Call Execution (x86-32 example)
---
From a programmer’s view, a system call looks like calling a normal C function. But internally, several hidden steps happen:

### 1. Wrapper Function (C Library)

* The program doesn’t call the kernel directly.
* Instead, it calls a wrapper function in the C library, which handles the low-level details.

### 2. Preparing Arguments

* The program passes arguments on the stack.
* The kernel expects them in specific CPU registers.
* The wrapper moves the arguments from the stack into those registers.

### 3. System Call Number

* Every system call has a unique number (e.g., read = 3, write = 4).
* The wrapper loads this number into the `%eax` register so the kernel knows which service is requested.

### 4. Trap Instruction

* The wrapper executes a trap instruction (`int 0x80`) to switch from user mode → kernel mode.
* This tells the CPU to jump to the kernel’s system call handler.
* On newer CPUs, `sysenter` is used instead of `int 0x80` (faster).

### 5. Inside the Kernel (system\_call routine)

When the CPU traps into the kernel (location `0x80`):

(a) Save registers onto the kernel stack.

(b) Validate the system call number.

(c) Find the right system call service routine from `sys_call_table` and:

* Validate arguments (e.g., check memory addresses).
* Perform the requested task (may transfer data between user and kernel memory).
* Return a result status.

(d) Restore registers from the kernel stack.

(e) Return to the wrapper function and switch back to user mode.

### 6. Wrapper Function (return handling)

* If the system call result = error → wrapper sets the global variable `errno`.
* Return value rules in Linux:

  * Success → nonnegative value.
  * Error → negative value (negated errno).
* Wrapper:

  * Negates the value, copies it into `errno`, and returns `-1` to the caller.

⚠️ Exception: some system calls (like `fcntl()` with `F_GETOWN`) can validly return negative values, but this usually doesn’t cause conflicts with error codes.

---
## Extra Notes on System Calls (execve example)
---

### Example with execve()
- On Linux/x86-32, `execve()` is system call number **11** (`__NR_execve`).  
- In the `sys_call_table`, entry **11** points to `sys_execve()`, the kernel routine that implements this call.  
- Service routines usually follow the naming format `sys_xyz()`.

### System call overhead
- Even a “simple” system call requires multiple steps, which means some overhead.  
- Example:  
  - `getppid()` → returns the parent process ID.  
  - On Linux 2.6.25 (x86-32), **10 million calls** took about **2.2 seconds** → ~0.3 microseconds per call.  
  - By comparison: **10 million plain C function calls** took only **0.11 seconds** (~20× faster).  
  - Most system calls cost even more than `getppid()`.

### Terminology in the book
- Saying “invoke the system call `xyz()`” usually means:  
  *Calling the C library wrapper that invokes the real system call routine.*

### Tracing system calls
- The `strace` tool can show which system calls a program makes (useful for debugging or investigation).

---

## Figure 3-1

Steps in the execution of a system call (example with `execve()`):

![Figure 3-1: Steps in the execution of a system call](./images/figure3-1.png)

---
## 3.2 Library Functions
---

* **Definition:**
  Functions provided by the **standard C library** (libc).

* **Purpose:**
  Handle diverse tasks like:

  * Opening files (`fopen`)
  * Converting time to readable format
  * Comparing strings (`strcmp`)
  * Allocating memory (`malloc`, `free`)

* **Relation to system calls:**

  * Some library functions **don’t use system calls** (e.g., string manipulation functions like `strlen`, `strcpy`).
  * Others are **wrappers around system calls**, offering a friendlier interface.

* **Examples:**

  * `fopen()` → uses the `open()` system call.
  * `printf()` → uses `write()` but adds formatting & buffering.
  * `malloc()` / `free()` → manage memory using the `brk()` system call, but add bookkeeping for ease.

* **Key Idea:**
Library functions often **abstract away low-level system calls** to make programming **simpler, safer, and more portable**.

---
## 3.3 The Standard C Library; The GNU C Library (glibc)
---

- **Standard C Library Implementations:**  
  - Different UNIX systems have different implementations.  
  - On Linux, the most common is **GNU C Library (glibc)** → [https://www.gnu.org/software/libc/](http://www.gnu.org/software/libc/).  
  - Other lightweight alternatives (mainly for embedded systems):  
    - **uClibc** → [http://www.uclibc.org/](http://www.uclibc.org/)  
    - **diet libc** → [http://www.fefe.de/dietlibc/](http://www.fefe.de/dietlibc/)  

- **glibc Maintainers:**  
  - Initially: **Roland McGrath**  
  - Later: **Ulrich Drepper**  

- **Why glibc?**  
  - Used by **most Linux applications**, so this book focuses on it.  

---

### Determining glibc Version  

1. **From shell (executing library):**  
   ```bash
   /lib/libc.so.6
   ```
   → Prints version info, copyright, compiler, extensions.

2. **If libc.so.6 is elsewhere:**  
   - Use `ldd` (list dynamic dependencies) on any dynamically linked program:  
     ```bash
     ldd /bin/ls | grep libc
     ```
     → Shows the path of `libc.so.6`.

3. **From source code:**  

   - **Compile-time check:**  
     - Macros:  
       - `__GLIBC__` → major version  
       - `__GLIBC_MINOR__` → minor version  
     - Example: glibc 2.12 → values `2` and `12`.  
     - ⚠️ Limitation: only reliable if compiled and run on the same system.  

   - **Run-time check:**  
     - `gnu_get_libc_version()` → returns version string (e.g., `"2.12"`).  
     - `confstr(_CS_GNU_LIBC_VERSION, ...)` → returns string (e.g., `"glibc 2.12"`).  
     
---
## 3.4 Handling Errors from System Calls and Library Functions
---

Most system calls and library functions return a value indicating **success or failure**.  
You should **always check this return value**.  
If the call failed → handle it (at least print an error message).  
Ignoring these checks wastes hours of debugging.

### System calls that (effectively) don’t fail
- `getpid()` → always returns the process ID.  
- `_exit()` → always terminates the process.

---

### Checking return values (typical pattern)
Most system calls indicate failure with **`-1`**.

```c
int fd = open(pathname, flags, mode); /* system call to open a file */
if (fd == -1) {
    /* Handle error */
}

if (close(fd) == -1) {
    /* Handle error */
}
```

## errno basics

- On failure, a system call sets the **global integer `errno`** to a **positive error code**.  
- Include `<errno.h>` to get the declaration of `errno` and the error constants (all start with `E`, e.g., `EINTR`, `EACCES`, `ENOENT`).  
- The **`ERRORS`** section of each man page lists possible `errno` values for that call.  

### Important rules
- A **successful call does not reset `errno`** to 0 → it may still hold an old nonzero value.  
- Standards permit a **successful function to set `errno`** (rare).  
- Therefore: **first check the function’s return value**. Only if it signals failure should you read `errno`.  

### Example (diagnosing `read` failures)
```c
cnt = read(fd, buf, numbytes);
if (cnt == -1) {
    if (errno == EINTR) {
        fprintf(stderr, "read was interrupted by a signal\n");
    } else {
        /* Some other error occurred */
    }
}
```

### Important Notes on `errno`

- A successful system call does **not** reset `errno` to 0.  
- Rarely, a successful system call may still change `errno`.  
- **Correct approach**:  
  - First check the return value.  
  - Only then check `errno`.  

### Special Case: System Calls Returning -1 Validly
Some system calls (e.g., `getpriority()`) can return **-1** as a valid result.  
To distinguish between a valid result and an error:  

```c
#include <errno.h>

errno = 0;    /* Clear errno before the call */
int result = getpriority(which, who);

if (result == -1 && errno != 0) {
    /* A real error occurred */
}
```

### Printing Error Messages

After a system call fails, you can print a descriptive message using `errno`.

### perror()
- Prints your custom message **+** description of `errno`.

```c
int fd = open(pathname, flags, mode);
if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
}
```
### strerror()
- Returns the error string corresponding to the error number given in its `errnum` argument.

```c
#include <string.h>
char *strerror(int errnum);
```

- The string returned may be **statically allocated**, meaning it could be **overwritten by subsequent calls** to `strerror()`.  
- If `errnum` specifies an unrecognized error number:  
  - Returns a string like `Unknown error nnn`.  
  - Some implementations may return `NULL`.  
- `perror()` and `strerror()` are **locale-sensitive**, so error descriptions are displayed in the local language.

---

### Handling Errors from Library Functions
- Library functions return **different data types** and **different values** to indicate failure.  
- Always check the **manual page** for each function.

#### Categories of Library Functions

1. **Functions that behave like system calls**  
   - Return `-1` on error.  
   - `errno` indicates the specific error.  
   - **Example:** `remove()` → removes a file (uses `unlink()`) or directory (uses `rmdir()`).  
   - Errors are diagnosed the same way as system calls.

2. **Functions that return other values on error but still set errno**  
   - **Example:** `fopen()` → returns `NULL` on error.  
   - `errno` indicates which underlying system call failed.  
   - Use `perror()` or `strerror()` to diagnose errors.

3. **Functions that don’t use errno**  
   - Error detection depends on the function itself.  
   - Do **not** use `errno`, `perror()`, or `strerror()` to diagnose these errors.  
   - Always consult the function’s manual page.




