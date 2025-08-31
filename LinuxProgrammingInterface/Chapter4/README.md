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

# Chapter 4: File I/O – The Universal I/O Model

We now look at the system call API, starting with files, since they are central to the UNIX philosophy.

---

## The Universal I/O Model

UNIX uses the **same four system calls** to perform I/O on all types of files, including devices like terminals:

* `open()`
* `read()`
* `write()`
* `close()`

This universality ensures that programs using these calls work with any file type.

---
