# 📄 get_next_line

## 🧠 Overview

`get_next_line` is a function that reads and returns a file descriptor content **line by line**.

This project is part of the 42 curriculum and introduces advanced concepts such as:

- Static variables
- Buffered file reading
- Dynamic memory management
- File descriptor handling
- Persistent state between function calls

The function allows efficient reading from files or standard input without loading the entire file into memory.

---

# 🎯 Function Prototype

```c
char *get_next_line(int fd);
```

### Behavior

- Returns **one line per call**
- Includes the newline (`\n`) when present
- Returns `NULL` when:
  - End Of File (EOF) is reached
  - An error occurs

---

# 🚀 Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
```

---

# ⭐ Bonus Part — Multiple File Descriptors

The bonus implementation supports reading from **multiple file descriptors simultaneously**.

Example:

```c
get_next_line(fd1);
get_next_line(fd2);
```

Each file descriptor keeps its own internal buffer using:

```c
static char *stash[OPEN_MAX];
```

This allows independent reading from multiple files without data corruption.

---

# ⚙️ Compilation

```bash
make
```

Clean object files:

```bash
make clean
```

Remove all compiled files:

```bash
make fclean
```

Recompile:

```bash
make re
```

---

# 📂 Project Structure

```
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line_bonus.c
├── get_next_line_bonus_utils.c
├── get_next_line.h
└── Makefile
```

---

# 🔁 How It Works

### 1️⃣ Buffered Reading

Data is read using:

```c
read(fd, buffer, BUFFER_SIZE);
```

instead of reading the full file at once.

---

### 2️⃣ Persistent Storage

A static buffer stores unread data between function calls:

```c
static char *stash[OPEN_MAX];
```

This ensures continuity between reads.

---

### 3️⃣ Line Extraction Process

Each function call:

1. Reads data into a buffer
2. Appends it to stored content
3. Extracts one complete line
4. Returns the line
5. Saves remaining data for the next call

---

# 🧪 Edge Cases Handled

✅ Different `BUFFER_SIZE` values  
✅ Very small buffers  
✅ Large files  
✅ Files without newline at EOF  
✅ Empty files  
✅ Reading from stdin  
✅ Multiple file descriptors (bonus)  
✅ Memory leak prevention  

---

# 🛠 Allowed Functions

- `read`
- `malloc`
- `free`

---

# 🧹 Memory Management

- Each returned line must be freed by the caller.
- Internal buffers are properly maintained.
- No memory leaks when tested with `valgrind`.

---

# 🎯 Objectives

- Understand static variable lifetime
- Handle partial reads safely
- Manage dynamic memory efficiently
- Implement buffered I/O logic
- Support concurrent file descriptor reading

---

# 🏁 Final Result

`get_next_line` provides an efficient and reusable solution for reading input line-by-line from any file descriptor.

This function becomes essential in later 42 projects such as:

- pipex
- minishell
- cub3d
- webserv

---

