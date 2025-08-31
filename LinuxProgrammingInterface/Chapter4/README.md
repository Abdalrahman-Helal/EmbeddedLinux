# Chapter 4: File I/O – The Universal I/O Model

## 4.1 Overview
- In UNIX, **everything is treated as a file** (regular files, devices, sockets, pipes, terminals).  
- The **universal I/O model** is built on a small set of system calls:  
  - `open()`  
  - `read()`  
  - `write()`  
  - `close()`  
- These calls allow programs to access all types of files in a uniform way.  
- The C standard library (`stdio`) provides higher-level functions (e.g., `fopen`, `fgets`, `fprintf`) built on top of these system calls.  
- A **file descriptor** is the key abstraction:  
  - A small integer returned by `open()`.  
  - Identifies an open file within a process.  
  - Each process has its own private set of file descriptors.  
- This model ensures portability: a program written using these system calls can work with different types of files without modification.  

---

## File Descriptors
- Small nonnegative integers used by processes to refer to open files.  
- Apply to all file types: regular files, devices, sockets, pipes, FIFOs, and terminals.  
- Each process has its own set of file descriptors.  

### Standard File Descriptors (always open by default via the shell)
- `0` → Standard Input (`STDIN_FILENO`, `stdin`)  
- `1` → Standard Output (`STDOUT_FILENO`, `stdout`)  
- `2` → Standard Error (`STDERR_FILENO`, `stderr`)  

---

## I/O Redirection
- Shell can modify these descriptors before launching a program.  
- Example: `freopen()` can reassign `stdin`, `stdout`, `stderr` to other files.  

---

## Core System Calls for File I/O
Used indirectly via libraries in most programs:  

### `open(pathname, flags, mode)`
- Opens a file and returns a file descriptor.  
- **flags**: controls read/write mode, create/truncate behavior.  
- **mode**: file permissions if a new file is created.  

### `read(fd, buffer, count)`
- Reads up to *count* bytes into buffer.  
- Returns number of bytes actually read.  
- Returns `0` on end-of-file (EOF).  

### `write(fd, buffer, count)`
- Writes up to *count* bytes from buffer to file.  
- Returns number of bytes written (may be less than count).  

### `close(fd)`
- Releases the file descriptor and associated kernel resources.  

---

## Example: Listing 4-1 (`copy.c`)
A simplified version of the `cp` command.  

### Steps:
1. Open source file (`open` with `O_RDONLY`).  
2. Open/create destination file (`O_CREAT | O_WRONLY | O_TRUNC`) with permissions `rw-rw-rw-`.  
3. Loop: `read` from input → `write` to output until EOF.  
4. Close both files.  

### Sample Code Snippet
```c
int inputFd, outputFd;
ssize_t numRead;
char buf[1024];

/* Open source file for reading */
inputFd = open("source.txt", O_RDONLY);

/* Open (or create) destination file for writing */
outputFd = open("dest.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

while ((numRead = read(inputFd, buf, sizeof(buf))) > 0) {
    if (write(outputFd, buf, numRead) != numRead) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

/* Close both files */
close(inputFd);
close(outputFd);
```

### Notes:
- Proper error handling is essential (`errExit`, `fatal`).  
- Buffer size (`BUF_SIZE`) controls efficiency (default: 1024).  
- `close()` must be called to free system resources.  


## 4.2 Universality of I/O

The **UNIX I/O model** is based on the idea of **universality**:  
the same system calls — `open()`, `read()`, `write()`, and `close()` — are used for all types of files, including devices like terminals.

### Why It Matters
- A program written with these four calls works on **any file type**.  
- Device-specific details are hidden inside the **kernel**.  
- Application developers can usually ignore differences between files and devices.

### Example Usages
```bash
$ ./copy test test.old        # Copy a regular file
$ ./copy a.txt /dev/tty       # Copy file to terminal
$ ./copy /dev/tty b.txt       # Copy input from terminal to file
$ ./copy /dev/pts/16 /dev/tty # Copy input from another terminal
```

### Special Cases
When a program needs access to **extra device-specific features**, it uses the `ioctl()` system call.  
This call provides an interface to functionality **beyond the universal I/O model**.

---
## The Universal I/O Model

UNIX uses the **same four system calls** to perform I/O on all types of files, including devices like terminals:

* `open()`
* `read()`
* `write()`
* `close()`

This universality ensures that programs using these calls work with any file type.

---
## 4.3 Opening a File: `open()`

```c
#include <sys/stat.h>
#include <fcntl.h>

int fd = open(const char *pathname, int flags, ... /* mode_t mode */);
```

* Returns a **file descriptor** on success, or `-1` on error.
* Creates a new file if it doesn’t exist (depending on flags).
* Symbolic links are automatically dereferenced.
* File permissions can be specified as a number (octal) or by ORing constants (e.g., `S_IRUSR | S_IWUSR`).

### Examples

```c
// Open existing file for reading
fd = open("startup", O_RDONLY);
if (fd == -1) errExit("open");

// Open new/existing file for read/write, truncating; owner read+write
fd = open("myfile", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
if (fd == -1) errExit("open");

// Open new/existing file for writing, always append to end
fd = open("w.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
if (fd == -1) errExit("open");
```

### File Access Modes

| Access Mode | Description                                |
| ----------- | ------------------------------------------ |
| O\_RDONLY   | Open the file for reading only             |
| O\_WRONLY   | Open the file for writing only             |
| O\_RDWR     | Open the file for both reading and writing |


## File Descriptors

A **file descriptor** is an integer representing an open file.

| Descriptor | Standard Stream |
| ---------- | --------------- |
| 0          | Standard input  |
| 1          | Standard output |
| 2          | Standard error  |

SUSv3 specifies that `open()` uses the **lowest-numbered unused file descriptor**. This can be used to control which descriptor is assigned.

Example:

```c
if (close(STDIN_FILENO) == -1) // Close fd 0
    errExit("close");
fd = open(pathname, O_RDONLY); // Guaranteed to use fd 0
if (fd == -1)
    errExit("open");
```

### Notes

* File permissions depend on **mode argument**, process **umask**, and optionally the **default ACL** of the parent directory.
* Using file descriptors, programs can interact with files and devices in a **uniform way**, a cornerstone of UNIX design.
* Advanced control over file descriptors can be achieved using `dup2()` and `fcntl()`.

---
## 4.3.1 The `open()` Flags Argument
---

The **flags argument** in `open()` can include additional bits beyond the access mode, such as `O_CREAT`, `O_TRUNC`, and `O_APPEND`. Flags can be **bitwise ORed (`|`)**.

### Common Flags

| Flag         | Purpose                                            | SUS? |
| ------------ | -------------------------------------------------- | ---- |
| O\_RDONLY    | Open for reading only                              | v3   |
| O\_WRONLY    | Open for writing only                              | v3   |
| O\_RDWR      | Open for reading and writing                       | v3   |
| O\_CLOEXEC   | Set close-on-exec flag                             | v4   |
| O\_CREAT     | Create file if it doesn’t exist                    | v3   |
| O\_DIRECT    | File I/O bypasses buffer cache                     |      |
| O\_DIRECTORY | Fail if pathname is not a directory                | v4   |
| O\_EXCL      | With O\_CREAT: create file exclusively             | v3   |
| O\_LARGEFILE | Open large files (32-bit systems)                  |      |
| O\_NOATIME   | Don’t update file last access time on read         |      |
| O\_NOCTTY    | Don’t let pathname become the controlling terminal | v3   |
| O\_NOFOLLOW  | Don’t dereference symbolic links                   | v4   |
| O\_TRUNC     | Truncate existing file to zero length              | v3   |
| O\_APPEND    | Writes always append to end of file                | v3   |
| O\_ASYNC     | Signal when I/O is possible                        |      |
| O\_DSYNC     | Synchronized I/O data integrity                    | v3   |
| O\_NONBLOCK  | Open in nonblocking mode                           | v3   |
| O\_SYNC      | Make file writes synchronous                       | v3   |

### Flags Categories

The constants in Table 4-3 are divided into the following groups:

* **File access mode flags:** `O_RDONLY`, `O_WRONLY`, `O_RDWR`. They can be retrieved using `fcntl()` with the `F_GETFL` operation.
* **File creation flags:** Control the behavior of the `open()` call and options for subsequent I/O. These flags cannot be retrieved or changed after the file is opened (`O_CREAT`, `O_EXCL`, `O_TRUNC`).
* **Open file status flags:** The remaining flags that control I/O options (`O_APPEND`, `O_NONBLOCK`, `O_SYNC`, etc.). They can be retrieved and modified using `fcntl()` with `F_GETFL` and `F_SETFL`. Sometimes called file status flags.

Since Linux kernel 2.6.22, the files in `/proc/PID/fdinfo` can be read to get information about open file descriptors. Each file corresponds to a descriptor number. The `pos` field shows the current file offset, and the `flags` field shows the file access mode and status flags in octal. Decoding these requires checking the numeric values in the C library headers.

### Detailed Flags Description

* **O\_APPEND:** Writes are appended to the end of the file. Useful for logging.
* **O\_ASYNC:** Enables signal-driven I/O for terminals, FIFOs, and sockets. Needs `fcntl()` to activate on Linux.
* **O\_CLOEXEC:** Automatically closes the file on `exec()` calls, preventing race conditions in multithreaded programs.
* **O\_CREAT:** Creates the file if it doesn’t exist. Requires a `mode` argument to set permissions.
* **O\_DIRECT:** Bypasses the buffer cache, useful for high-performance applications needing direct disk access.
* **O\_DIRECTORY:** Fails if the path is not a directory, useful for implementing `opendir()` safely.
* **O\_DSYNC:** Ensures synchronized data writes, preventing data loss in case of crashes.
* **O\_EXCL:** Guarantees exclusive creation with `O_CREAT`. Useful for safely creating temporary files.
* **O\_LARGEFILE:** Allows large file support on 32-bit systems.
* **O\_NOATIME:** Prevents updating last access time, reducing disk activity for indexing and backup programs.
* **O\_NOCTTY:** Stops terminal files from becoming controlling terminals.
* **O\_NOFOLLOW:** Prevents following symbolic links, improving security in privileged programs.
* **O\_NONBLOCK:** Enables nonblocking mode for file reads and writes.
* **O\_SYNC:** Ensures synchronous I/O, guaranteeing that writes reach the disk before returning.
* **O\_TRUNC:** Truncates existing files to zero length, effectively clearing them when opening.

---
## 4.3.2 Errors from `open()`
---
If an error occurs while trying to open a file, `open()` returns `-1`, and `errno` identifies the cause. Some common errors include:

* **EACCES:** File permissions don’t allow access in the specified mode. Could also be due to directory permissions or inability to create the file.
* **EISDIR:** The target is a directory and was opened for writing. Reading a directory is sometimes allowed.
* **EMFILE:** Process reached the resource limit on open file descriptors (`RLIMIT_NOFILE`).
* **ENFILE:** System-wide limit on open files has been reached.
* **ENOENT:** File does not exist and `O_CREAT` was not specified, or a component of the pathname does not exist (dangling symbolic link).
* **EROFS:** File resides on a read-only filesystem and cannot be opened for writing.
* **ETXTBSY:** The file is an executable currently running and cannot be modified until the program terminates.

> Note: The above list is illustrative. Complete error reasons for `open()` can be found in the `open(2)` manual page. This section highlights that system calls may fail for multiple reasons, and checks for these errors are essential for robust programs.

---
## 4.3.3 The `creat()` System Call
---

In early UNIX implementations, `open()` had only two arguments and could not create a new file. The `creat()` system call was used instead to create and open a new file.

```c
#include <fcntl.h>
int creat(const char *pathname, mode_t mode);
```

* Returns a **file descriptor**, or `-1` on error.
* Creates and opens a new file with the specified pathname. If the file exists, it truncates it to zero length.

Calling `creat()` is equivalent to:

```c
fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

> Note: The `open()` flags argument provides more control (e.g., `O_RDWR` instead of `O_WRONLY`). Therefore, `creat()` is now considered obsolete, though it may still appear in older programs.

---
## 4.4 Reading from a File: `read()`
---

The `read()` system call reads data from an open file referred to by the file descriptor `fd`.

```c
#include <unistd.h>
ssize_t read(int fd, void *buffer, size_t count);
```

* **Returns:**

  * Number of bytes read
  * `0` on end-of-file (EOF)
  * `-1` on error

* **Parameters:**

  * `fd`: File descriptor of the open file.
  * `buffer`: Pointer to memory where input data will be stored. Must be at least `count` bytes long.
  * `count`: Maximum number of bytes to read.

## Notes

* System calls do **not allocate memory**; the caller must provide a buffer.
* `read()` may return **fewer bytes** than requested, especially near EOF or when reading from pipes, terminals, or sockets.
* `read()` **does not append a null terminator** to character data. If reading strings, you must add it manually:

```c
#define MAX_READ 20
char buffer[MAX_READ + 1]; // make buffer 1-byte larger
ssize_t numRead;

numRead = read(STDIN_FILENO, buffer, MAX_READ);
if (numRead == -1)
    errExit("read");

buffer[numRead] = '\0'; // add null terminator
printf("The input data was: %s\n", buffer);
```

* The buffer size should be **one byte larger** than the expected input to accommodate the null terminator.
* `ssize_t` is a **signed integer** type used to hold a byte count or `-1` for errors.
---