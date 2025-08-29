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

---
## 3.5 Notes on Example Programs

## 3.5.1 Command-Line Options and Arguments
---
Many example programs rely on command-line options to control behavior.

### UNIX style options

* Start with a single hyphen `-` followed by a letter (e.g., `-a`).
* May include an optional argument.

### GNU style options

* Start with two hyphens `--` followed by a word (e.g., `--help`).
* May also include an optional argument.

Programs usually provide a help option (`--help`) that prints usage instructions.

To parse command-line options, the programs use the standard C library function `getopt()`.

---
## 3.5.2 Common Functions and Header Files
---

* Most example programs include a common header file with frequently used definitions and functions.
* **Purpose of the header file:**

  * Includes other header files often needed.
  * Defines a Boolean type.
  * Provides macros for min and max calculations.
  * Helps make example programs shorter and cleaner.

**Example header file (`lib/tlpi_hdr.h`):**

```c
#ifndef TLPI_HDR_H
#define TLPI_HDR_H /* Prevent double inclusion */

#include <sys/types.h>   /* Common type definitions */
#include <stdio.h>       /* Standard I/O */
#include <stdlib.h>      /* Standard library functions + EXIT_SUCCESS/EXIT_FAILURE */
#include <unistd.h>      /* System call prototypes */
#include <errno.h>       /* errno and error constants */
#include <string.h>      /* String-handling functions */
#include "get_num.h"     /* Functions for numeric arguments (getInt(), getLong()) */
#include "error_functions.h" /* Error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif
```

* Using this file reduces repetitive code in programs.


## Error-Diagnostic Functions

* To simplify error handling, example programs use a set of error-diagnostic functions.
* Declared in the header file: `lib/error_functions.h`.

**Example declarations:**

```c
#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char *format, ...);

#ifdef __GNUC__
/* Stops 'gcc -Wall' warning about control reaching end of non-void function */
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char *format, ...) NORETURN;
void err_exit(const char *format, ...) NORETURN;
void errExitEN(int errnum, const char *format, ...) NORETURN;
void fatal(const char *format, ...) NORETURN;
void usageErr(const char *format, ...) NORETURN;
void cmdLineErr(const char *format, ...) NORETURN;

#endif
```

* Functions with `NORETURN` terminate the program and never return.
* Using these functions makes error handling consistent and simpler across programs.


### 1. errMsg()

* Prints an error message to **standard error**.
* Works like `printf()`, but automatically appends a **newline**.
* Prints:

  * The error name (e.g., `EPERM`)
  * Error description from `strerror()`
  * Formatted message from arguments.
* **Does not terminate** the program.

### 2. errExit()

* Operates like `errMsg()`, **but terminates the program**.
* Termination:

  * Normally calls `exit()`.
  * If the environment variable `EF_DUMPCORE` is defined and non-empty, calls `abort()` to produce a **core dump** for debugging.

### 3. err\_exit()

* Similar to `errExit()`, but differs in two key ways:

  1. **Does not flush standard output** before printing the error message.
  2. Calls `_exit()` instead of `exit()`.

     * Terminates the process **immediately**, without flushing stdio buffers or calling exit handlers.
* Useful for **child processes in libraries** that need to terminate due to errors **without affecting the parent’s output buffers or exit handlers**.

### 4. errExitEN(int errnum, ...)

* Similar to `errExit()`, but prints the error text for a **specific error number `errnum`** instead of the current `errno`.
* Mainly used with **POSIX threads**, where functions return an **error number** instead of –1 on failure (0 indicates success).

---

### Diagnosing Errors in POSIX Threads

* Traditional approach (using `errno`):

```c
errno = pthread_create(&thread, NULL, func, &arg);
if (errno != 0)
    errExit("pthread_create");
```

* **Problem:** Inefficient in threaded programs

  * `errno` is a macro that expands into a function call returning a **modifiable lvalue**.
  * Each use of `errno` triggers a function call.

* **Better approach using `errExitEN()`:**

```c
int s;
s = pthread_create(&thread, NULL, func, &arg);
if (s != 0)
    errExitEN(s, "pthread_create");
```

* `errExitEN()` uses the **returned error number** directly, avoiding extra function calls.

### Additional Notes

* In C, an **lvalue** refers to a storage location (e.g., a variable or `*p`).
* In POSIX threads, `errno` is redefined as a function returning a **thread-specific storage pointer**, making direct use less efficient.


### Other Error-Diagnostic Functions

To diagnose errors not related to system calls or errno, we use the following functions:

```c
#include "tlpi_hdr.h"
void fatal(const char *format, ...);
void usageErr(const char *format, ...);
void cmdLineErr(const char *format, ...);
```

### 1. fatal()

* Diagnoses **general errors**, including errors from library functions that do not set `errno`.
* Works like `printf()`, automatically appends a **newline**.
* Prints to **standard error** and then **terminates the program** (like `errExit()`).

### 2. usageErr()

* Diagnoses **errors in command-line argument usage**.
* Prints **`Usage:`** followed by the formatted message.
* Terminates the program using `exit()`.
* Some examples use an extended version named `usageError()`.

### 3. cmdLineErr()

* Similar to `usageErr()`, but specifically for **command-line argument errors**.
* Prints **`Command-line usage error:`** followed by the formatted message.
* Terminates the program using `exit()`.

**Implementations** of these functions are provided in `lib/error_functions.c`.

---

## `ename.c.inc` – Symbolic Names for `errno`

* **Purpose:**

  * Defines an array of strings `ename[]` mapping **error numbers** to their **symbolic names** (e.g., `EPERM`, `ENOENT`).
  * Used by error-handling functions (`errMsg()`, `errExit()`, etc.) to print **human-readable error names**.
  * Workaround: `strerror()` provides only descriptions, not symbolic names.

* **Architecture-Specific:**

  * `errno` values differ across Linux hardware architectures.
  * The example shown is for **Linux 2.6/x86-32**.
  * Can regenerate for a specific platform using `lib/Build_ename.sh`.

* **Notes on `ename[]` array:**

  * Some strings are empty → correspond to **unused error values**.
  * Some strings contain **two names separated by a slash** → when two symbolic names share the same numeric value.

    * Example: `"EAGAIN/EWOULDBLOCK"`

      * `EAGAIN`: System V, for nonblocking I/O, semaphores, message queues, file locks (`fcntl()`).
      * `EWOULDBLOCK`: BSD, for nonblocking file locks (`flock()`) and socket calls.
      * SUSv3 permits either for **nonblocking socket calls**; for others, only `EAGAIN` is specified.

* **Array example (partial):**

```c
static char *ename[] = {
    /* 0 */ "",
    /* 1 */ "EPERM", "ENOENT", "ESRCH", "EINTR", "EIO", "ENXIO", "E2BIG",
    /* 8 */ "ENOEXEC", "EBADF", "ECHILD", "EAGAIN/EWOULDBLOCK", "ENOMEM",
    /* 13 */ "EACCES", "EFAULT", "ENOTBLK", "EBUSY", "EEXIST", "EXDEV",
    ...
};
#define MAX_ENAME 132
```

* **Usage:**

  * Error-handling functions look up `ename[err]` to print the **symbolic name** along with `strerror(err)` for easier reference to **manual pages**.







