# Linux Programming Interface Chapter 2 Notes

---

## 2.1 The Core Operating System: The Kernel

---

### Kernel Definition

**The kernel is the central part of an operating system that manages the computer’s hardware resources (CPU, memory, devices) and provides a software layer for programs to use those resources safely and efficiently.**

---

### Two Meanings of Operating System

1. **Broad meaning:**

   * The OS as a complete package including the kernel and standard tools (shells, GUIs, file utilities, editors).
2. **Narrow meaning:**

   * Only the central software (kernel) that manages and allocates hardware resources.

---

### Importance of the Kernel

* Simplifies programming and resource management.
* Acts as a software layer between hardware and programs.
* Increases the power and flexibility available to programmers.

---

### Linux Kernel Location and Naming

* Typically located at `/boot/vmlinuz`.
* Linux: `vmlinuz` (z = compressed executable)

---

## Tasks Performed by the Kernel

---

1. **Process Scheduling:**

   * Multitasking: Multiple programs can run simultaneously.
   * Preemptive: Kernel decides CPU allocation and duration.

2. **Memory Management:**

   * Allocates RAM efficiently among processes.
   * Uses virtual memory:

     * Isolation between processes and kernel.
     * Only part of process in RAM → more processes can run.

3. **Provision of a File System:**

   * Allows programs to create, read, update, delete files on disk.

4. **Creation and Termination of Processes:**

   * Loads programs into memory and provides resources.
   * Frees resources when process finishes.

5. **Access to Devices:**

   * Standard interface for programs to use devices (keyboard, mouse, disks, etc.).
   * Manages access conflicts.

6. **Networking:**

   * Sends and receives network packets for programs.
   * Routes packets to correct destination.

7. **System Call API:**

   * Processes request kernel tasks via system calls.
   * Main way programs interact with kernel.

8. **Multiuser Support:**

   * Provides each user a private environment:

     * Personal storage, CPU share, virtual address space, device/network access.
   * Kernel resolves hardware conflicts invisibly to users.

---

## Kernel Mode and User Mode

---

1. **Two CPU Modes:**

   * **User mode:** Regular programs run here. CPU can only access **user space memory**.
   * **Kernel mode (supervisor mode):** OS kernel runs here. CPU can access **both user and kernel memory**.

2. **Memory Separation:**

   * User space: memory accessible only by user programs.
   * Kernel space: memory used by the kernel.
   * If a program in user mode tries to access kernel memory → **hardware exception**.

3. **Operations Restricted to Kernel Mode:**

   * Stopping the system (`halt` instruction).
   * Accessing memory-management hardware.
   * Initiating device input/output operations.

4. **Purpose:**

   * This separation ensures **safety and stability**.
   * User processes cannot accidentally or maliciously access kernel instructions or data.
   * Prevents actions that could crash or destabilize the system.

---

## Process versus Kernel Views of the System

---

1. **Process Viewpoint:**

   * A process sees the system **from its own perspective**, unaware of most low-level details.
   * Many things happen **asynchronously** for a process:

     * It doesn’t know when it will next time out.
     * It doesn’t know which other processes will then be scheduled for the CPU or in what order.
     * Delivery of signals and interprocess communication events are mediated by the kernel and can occur at any time.
     * It doesn’t know where it is located in RAM.
     * It doesn’t know whether parts of its memory are currently in RAM or in swap.
     * It doesn’t know where on disk the files it accesses are physically located; it just uses file names.
   * A process operates in isolation:

     * Cannot directly communicate with other processes.
     * Cannot directly create or terminate processes.
     * Cannot access I/O devices directly.

2. **Kernel Viewpoint:**

   * The kernel **controls and knows everything** in the system.
   * Responsibilities of the kernel:

     * Decides which process runs on the CPU, when, and for how long.
     * Maintains **data structures** for all processes, tracking creation, state changes, and termination.
     * Maps virtual memory to physical memory and swap areas.
     * Maps file names to physical disk locations.
     * Provides all mechanisms for interprocess communication.
     * Creates and terminates processes on request.
     * Handles all direct communication with I/O devices through drivers.

3. **Key Takeaway:**

   * When we say in programming:

     * “A process creates another process”
     * “A process writes to a file”
     * “A process terminates with `exit()`”
   * What actually happens: **the process requests the kernel to perform these actions**, and the kernel executes them.

---

## 2.2 The Shell

---

1. **Definition:**

   * A shell is a **special program** that reads commands typed by a user and executes the appropriate programs.
   * Also called a **command interpreter**.

2. **Login Shell:**

   * The process created to run a shell when a user first logs in.

3. **Shell as a User Process in UNIX:**

   * On UNIX, the shell is **not part of the kernel**; it runs as a user process.
   * Different users or even the same user can use different shells simultaneously.

4. **Important Shells:**

   * **Bourne shell (`sh`)**
   * **C shell (`csh`)**
   * **Korn shell (`ksh`)**
   * **Bourne Again Shell (`bash`)**

5. **Shell Scripts:**

   * Shells interpret **shell scripts** with programming features: variables, loops, conditionals, I/O commands, functions.

---

## 2.3 Users and Groups

---

### Users

* Unique login name (username) and numeric user ID (UID).
* Defined in `/etc/passwd` with GID, home directory, login shell.
* Passwords in `/etc/passwd` or **shadow file** for security.

---

### Groups

* Organize users for access control.
* Users can belong to multiple groups.
* Defined in `/etc/group` with group name, GID, user list.

---

### Superuser

* User ID 0, usually `root`.
* Can bypass permission checks and access any file/process.

---

## 2.4 Single Directory Hierarchy, Directories, Links, and Files

---

* Linux uses a **single hierarchical directory structure** with the **root `/`** at the base.
* All files and directories are **children or descendants of root**.

---

### File Types

* Each file has a **type**:

  * **Regular files:** Ordinary data files (text, programs, images).
  * **Other types:** Directories, devices, pipes, sockets, symbolic links.

---

### Directories and Links

* **Directory:** Special file containing **filenames and references** to other files (links).
* Files can have **multiple links (names)**, possibly in different directories.
* Directories can contain links to **files and other directories**, forming the hierarchy.
* Every directory contains at least two entries:

  * `.` → link to itself
  * `..` → link to its parent directory
* Root directory (`/`) has `..` pointing to itself.

---

### Symbolic Links

* A **symbolic link (soft link)** is a special file that contains the **name of another file** (its target).
* The kernel **automatically follows the link** when accessed.
* Can happen **recursively** if the target is also a symbolic link.
* If the target file doesn’t exist, it is called a **dangling link**.
* **Terminology:** Hard link → normal link, Soft link → symbolic link.

---

### Filenames and Pathnames

**Filenames**

* Up to **255 characters** on most Linux filesystems.
* Can contain any character **except** `/` and `\0`.
* Recommended characters (portable set): `[-._a-zA-Z0-9]`.
* Avoid special characters (need escaping) and leading hyphens `-`.

**Pathnames**

* String of filenames separated by `/`.
* Directory part: all components before last slash.
* Base/file part: last component.
* `..` refers to parent directory.
* Absolute pathname: starts with `/` (e.g., `/home/mtk/.bashrc`).
* Relative pathname: relative to **current working directory** (e.g., `include/sys/types.h`).

---

### Current Working Directory (cwd)

* Each process has a cwd.
* Relative pathnames are interpreted from cwd.
* Inherited from parent process.
* Login shell starts in **user’s home directory**.
* Can be changed using `cd` command.

---

## 2.5 File Ownership and Permissions

---

1. **Ownership**

   * Every file has a **user ID (UID)** and **group ID (GID)**.
   * UID → file owner; GID → group owner.
   * Determines access rights for users.

2. **User Categories**

   * **Owner**: file owner.
   * **Group**: users in file’s group.
   * **Other**: everyone else.

3. **Permissions**

   * Three types: **read (r), write (w), execute (x)** for each category → total of nine permission bits.
   * Meaning for files:

     * Read → can read contents.
     * Write → can modify contents.
     * Execute → can run file if it’s a program or script.
   * Meaning for directories:

     * Read → can list filenames.
     * Write → can modify directory contents (add/remove files).
     * Execute → can access files within the directory (if permissions allow).

---

## 2.6 Programs

---

### Forms of Programs
* **Source code:** Human-readable text written in a programming language (e.g., C).  
* **Binary code:** Machine-readable instructions created from source code through **compiling and linking**.  
* **Scripts:** Special case – text files with commands interpreted directly by a program (like a shell).  
* Normally, “program” refers to the executable form (binary), since it is semantically equivalent to the source code.

---

### Filters
* A **filter** is a program that:
  - Reads input from **stdin**.
  - Performs some transformation.
  - Writes output to **stdout**.  
* Examples: `cat`, `grep`, `tr`, `sort`, `wc`, `sed`, `awk`.

---

### Command-line Arguments
* In C, programs can access arguments passed when the program is run.  
* Declaration of `main()` to access arguments:

```c
int main(int argc, char *argv[])
```

* `argc` → total number of arguments.  
* `argv[]` → array of strings for each argument.  
* `argv[0]` → name of the program itself.

---

## 2.7 Processes

---

### Definition
* A **process** is an **instance of an executing program**.  
* When a program runs:
  - The **kernel** loads its code into virtual memory.
  - Allocates space for **variables**.
  - Sets up **kernel bookkeeping** (process ID, user ID, group ID, termination status, etc.).
* From the kernel’s view, processes are entities among which resources like **CPU, memory, and network bandwidth** are shared.

---

### Process Memory Layout
A process’s memory is divided into **segments**:

1. **Text segment:** Program instructions.  
2. **Data segment:** Static variables.  
3. **Heap:** Dynamically allocated memory.  
4. **Stack:** Memory for local variables, function calls, and return addresses.

---

### Process Creation and Execution
* A process can create a new process using `fork()`.  
  - The **parent process** calls `fork()`.  
  - The **child process** is a duplicate of the parent:
    - Copies of **data, stack, and heap**.
    - Shares **read-only program text**.  

* After creation, the child process can:
  - Continue executing the same program with different behavior, or  
  - Use `execve()` to **load a new program**, which replaces:
    - Text, data, stack, and heap with the new program’s segments.  

* **C library functions** built on top of `execve()` (all start with `exec`) offer similar functionality.  
  - No function literally named `exec()` exists; it’s just shorthand.

---

### Process ID (PID) and Parent Process ID (PPID)
* **PID:** Unique integer identifier for each process.  
* **PPID:** PID of the process that created it (usually via `fork()`).  
* Allows the kernel (and user) to track process relationships.

---

### Process Termination and Termination Status
A process can terminate in two ways:

1. **Request its own termination** using `_exit()` (or `exit()` library function).  
2. **Be killed by a signal** sent to it (like `SIGKILL`).  

* When a process terminates, it yields a **termination status**:
  - A small nonnegative integer read by the parent using `wait()`.
  - `_exit(status)` sets the status explicitly.
  - If killed by a signal, status reflects the signal.

* **Exit convention:**
  - `0` → Success.
  - Nonzero → Error occurred.

* Most shells store the last program’s termination status in the `$?` variable.

---

## Process User and Group Identifiers (Credentials)

* Every process in UNIX/Linux has **user IDs (UIDs)** and **group IDs (GIDs)** to control access.

---

### Real User ID (RUID) and Real Group ID (RGID)
* Identify the user and group that own the process.  
* Inherited from parent process.  
* Login shell gets RUID and RGID from the system password file.

---

### Effective User ID (EUID) and Effective Group ID (EGID)
* Determine permissions for accessing files or resources.  
* Usually **EUID = RUID** and **EGID = RGID**.  
* Changing EUID/EGID allows process to assume privileges of another user/group.

---

### Supplementary Group IDs
* Identify additional groups the process belongs to.  
* Inherited from parent process.  
* Login shell gets supplementary groups from system group file.

---

### Privileged Processes
* **Privileged process:** **EUID = 0 (superuser)** → bypasses normal permission checks.  
* **Unprivileged process:** **EUID ≠ 0**, must follow normal permissions.

**How a process can become privileged:**
1. Created by another privileged process.  
2. **Set-user-ID (SUID) mechanism:** Process assumes EUID of program file owner during execution.

---

### Capabilities
* Linux divides **superuser privileges** into smaller units called **capabilities**.  
* Each privileged operation requires a **specific capability**.  
* Traditional superuser (EUID = 0) has all capabilities enabled.  
* Granting a **subset of capabilities** allows a process to perform some, but not all, superuser operations.  
* Capability names start with `CAP_` (e.g., `CAP_KILL`).

---

### The init Process
* Created by the kernel at **boot time** from `/sbin/init`.  
* Known as the **“parent of all processes”**, all processes descend from it.  
* Always has **PID = 1**, runs with **superuser privileges**.  
* Cannot be killed; terminates only on system shutdown.  
* **Main role:** create/manage essential system processes for a running system.

---

### Daemon Processes
* **Daemon:** Background process for special purposes.  
* **Characteristics:**  
  - Long-lived: runs from system boot until shutdown.  
  - No controlling terminal (runs in background).  
* **Examples:**  
  - `syslogd` – system logs.  
  - `httpd` – web server.

---

### Environment List
* Each process has an **environment list**, a set of **environment variables** (name-value pairs) stored in user-space memory.  
* **Inheritance:**  
  - `fork()` → copy of parent’s environment.  
  - `exec()` → new program can inherit or receive new environment.  
* **Creating variables in shells:**  
  - Bash: `$ export MYVAR='Hello world'`  
  - C shell: `setenv MYVAR 'Hello world'`  
* **Access in C programs:** `char **environ` or library functions.  
* **Common uses:**  
  - `HOME` → user’s login directory.  
  - `PATH` → directories to search for executables.


---

### Resource Limits

* Each process consumes **resources** such as open files, memory, and CPU time.  
* The `setrlimit()` system call allows a process to **set upper limits** on its resource usage.  

#### Resource Limit Types
* **Soft limit:** Maximum resource usage under normal conditions.  
* **Hard limit:** Ceiling for the soft limit; cannot be exceeded.  

#### Rules
* **Unprivileged processes:**  
  - Can change the soft limit **up to the hard limit**.  
  - Can **only lower the hard limit**.  
* **Inheritance:**  
  - Processes created via `fork()` inherit **copies of their parent’s resource limits**.  

#### Shell Usage
* Resource limits in shells can be adjusted using:  
  - `ulimit` command in **Bash**  
  - `limit` command in **C shell**  
* Child processes **inherit the shell’s resource limits** when executing commands.  

---
## 2.8 Memory Mappings
---

The `mmap()` system call creates a new memory mapping in the calling process’s virtual address space. Mappings allow direct memory access instead of using traditional read/write system calls.

#### Types of Mappings

1. **File Mapping**  
   * Maps a region of a file into the process’s memory.  
   * The file’s contents can be accessed like memory.  
   * Pages are loaded automatically from the file on demand.  

2. **Anonymous Mapping**  
   * Not linked to any file.  
   * Pages are initialized to zero.  

#### Sharing Between Processes

* Mappings can be shared with other processes either because:
  - Two processes map the same file region, or  
  - A child process created by `fork()` inherits its parent’s mapping.  
* **Private mapping:** Changes are local to the process; not reflected in the file or other processes.  
* **Shared mapping:** Changes are visible to other processes sharing the mapping and written to the underlying file.  

#### Common Uses

* Initialize a process’s text segment from an executable file.  
* Allocate new zero-filled memory.  
* Perform file I/O efficiently using memory-mapped I/O.  
* Enable interprocess communication via shared memory regions.

---
## 2.9 Static and Shared Libraries
---

### Object Library
An **object library** is a file containing compiled object code for a set of related functions.  
It simplifies program creation and maintenance. UNIX systems provide two main types of object libraries:
- **Static libraries**  
- **Shared libraries**

---

### Static Libraries
* Also called **archives**.  
* Early UNIX systems only had static libraries.  
* Composed of **compiled object modules**.  

**Usage:**
- Link the program with the static library during build.  
- The **linker extracts required object modules** and copies them into the executable.  
- The program becomes **statically linked**.  

**Disadvantages:**
1. **Disk space waste:** Each executable gets its own copy of library functions.  
2. **Memory waste:** Multiple running programs using the same function each have a copy in memory.  
3. **Maintenance overhead:** If a function is updated, all programs using it must be **relinked**.

---

### Shared Libraries
* Designed to solve static library issues.  

**Usage:**
- Linker records a reference in the executable instead of copying code.  
- At runtime, the **dynamic linker** loads required shared libraries and resolves function calls.

**Advantages:**
1. **Memory efficiency:** Single copy of the library code shared by all programs.  
2. **Disk space saving:** Only one compiled version exists.  
3. **Easy updates:** Rebuilding the shared library updates all programs automatically the next time they run.

---

### Key Takeaways
- **Static libraries:** faster startup, but duplicate code, higher memory use, more maintenance.  
- **Shared libraries:** memory and disk efficient, easier updates, uses **dynamic linking** at runtime.

---
## 2.10 Interprocess Communication and Synchronization
---

**Context:**   
- A Linux system runs many processes, mostly independent.  
- Some processes need to **cooperate**, requiring **communication** and **synchronization**.  

**Basic Idea:**  
- Processes can communicate by reading/writing files, but this is often **slow and inflexible**.  
- Linux provides multiple **Interprocess Communication (IPC) mechanisms** for efficiency and flexibility.

---

### IPC Mechanisms

1. **Signals**  
   - Indicate that an **event has occurred**.  
   - Example: `SIGINT` for interrupting a process.

2. **Pipes and FIFOs**  
   - Transfer data **between processes**.  
   - Pipes: temporary, usually parent → child.  
   - FIFOs (named pipes): persistent, unrelated processes can communicate.  
   - Familiar in shells via `|` operator.

3. **Sockets**  
   - Transfer data between processes **on the same host or across networked hosts**.  
   - Includes UNIX domain sockets and network sockets (TCP/UDP).

4. **File Locking**  
   - Allows a process to **lock regions of a file**.  
   - Prevents **other processes from reading or updating** locked regions.

5. **Message Queues**  
   - Exchange **messages (data packets)** between processes.  
   - Can be **asynchronous**, allowing independent process execution.

6. **Semaphores**  
   - Synchronize actions of processes.  
   - Useful to **coordinate access to shared resources** and prevent race conditions.

7. **Shared Memory**  
   - Allows two or more processes to **share a piece of memory**.  
   - Changes made by one process are **immediately visible** to others.

---

### Notes on IPC Variety

- UNIX provides multiple IPC mechanisms, sometimes overlapping in functionality.  
- Example:  
  - **FIFOs vs. UNIX domain sockets:** Both allow unrelated processes on the same system to exchange data.  
  - Both exist due to historical evolution:  
    - FIFOs → System V UNIX  
    - Sockets → BSD UNIX  

**Key Takeaway:**  
- IPC mechanisms evolved to meet **different UNIX standards** and **application requirements**, offering flexibility and performance for process communication and synchronization.

---
## 2.11 Signals
---

## Definition
- Signals are like **software interrupts**. They notify a process that an event or exceptional condition has occurred.
- Each signal has a **unique integer identifier**, usually defined as `SIGxxxx`.

### Sources of Signals
1. **Kernel**: 
   - User pressed **Ctrl-C**.
   - A child process terminated.
   - A timer/alarm expired.
   - Invalid memory access attempted.
2. **Other processes**: via `kill()` system call.
3. **Self**: a process can send a signal to itself.

### Signal Delivery Actions
When a process receives a signal, it may:
- **Ignore** it.
- **Be killed** by it.
- **Suspend** until resumed by a special signal.

### Custom Handling
- Programs can **override default actions** by:
  1. Ignoring the signal.
  2. Defining a **signal handler** – a function automatically invoked when the signal is received.

### Pending Signals
- If a signal is generated but not yet delivered, it is **pending**.
- Pending signals are delivered:
  - Immediately if the process is running.
  - When the process is next scheduled.
- Signals can also be **blocked** via the process’s signal mask. Blocked signals remain pending until unblocked.

---
## 2.12 Threads
---

### Definition
- A **thread** is a single execution flow within a process.  
- Modern UNIX systems allow a process to have **multiple threads** sharing the same virtual memory and other resources.

### Thread Memory Layout
- Threads share:
  - **Program code**
  - **Global data**
  - **Heap memory**
- Each thread has its **own stack** for:
  - Local variables
  - Function call information

### Communication and Synchronization
- Threads communicate via **shared global variables**.  
- **Threading API** provides:
  - **Mutexes** – for mutual exclusion
  - **Condition variables** – for signaling between threads
- Threads can also use **IPC mechanisms** (Section 2.10) for inter-thread communication.

### Advantages of Threads
- Easy **data sharing** between cooperating threads
- Some algorithms are **naturally multithreaded**
- Multithreaded programs can **utilize multiple processors** for parallel execution
- Lower overhead than creating multiple processes


---
## 2.13 Process Groups and Shell Job Control
---

### Process Groups
- Each program executed by the shell runs in a **new process**.  
- Processes in the same **pipeline** are placed in a **process group**.  
- Example pipeline:
```bash
$ ls -l | sort -k5n | less
```

### Process Groups
- All three commands run as **separate processes** but in **one process group**.  
- Each process group has a **process group ID (PGID)**, usually the **PID of the group leader**.

### Shell Job Control
- Most modern shells (except Bourne shell) provide **interactive job control**.  
- Job control allows the user to:
  - Execute **multiple commands simultaneously**.
  - **Suspend or resume commands**.  
- Job-control shells operate on **process groups**, sending **signals to all processes** in the group simultaneously.

---




