# 42_get_next_line

A C function that reads a file line by line, designed as part of the 42 School curriculum. This project implements a function that allows reading from file descriptors one line at a time, making it perfect for processing large files efficiently.

## 📖 About

`get_next_line` is a crucial project in the 42 School curriculum that teaches file I/O operations, static variables, and memory management. The goal is to create a function that reads a file descriptor line by line, returning one line at a time on each call. This approach is memory-efficient and allows processing files of any size without loading the entire content into memory.

## 🚀 Features

This implementation provides:

- **Line-by-line reading** - Reads files one line at a time
- **Multiple file descriptor support** - Handles up to 4096 concurrent file descriptors
- **Memory efficient** - Configurable buffer size (default: 20 bytes)
- **Static variable management** - Maintains state between function calls
- **Comprehensive error handling** - Handles edge cases and invalid inputs
- **Cross-platform compatibility** - Works with files, stdin, and other file descriptors
- **Memory leak prevention** - Proper cleanup and memory management
- **42 School compliant** - Follows norminette standards

## 🔧 Function Prototype

```c
int get_next_line(const int fd, char **line);
```

### Parameters

- `fd`: File descriptor to read from (0 for stdin, or file descriptor from `open()`)
- `line`: Double pointer to store the line read (memory allocated by the function)

### Return Values

- `1`: A line has been read successfully
- `0`: End of file (EOF) has been reached
- `-1`: An error occurred (invalid fd, memory allocation failure, read error)

## ⚙️ Configuration

The buffer size can be customized by modifying the `BUFF_SIZE` macro in `get_next_line.h`:

```c
#define BUFF_SIZE 20  // Default buffer size
```

**Buffer Size Impact:**

- **Smaller buffer** (1-10): More system calls, slower but uses less memory
- **Larger buffer** (1000+): Fewer system calls, faster but uses more memory
- **Optimal range**: 20-100 for most use cases

## 🏗️ Build Instructions

### Prerequisites

- GCC compiler
- Make (for libft compilation)

### Compilation

#### Basic Compilation

```bash
# Compile with libft
cd libft && make && cd ..
gcc -Wall -Wextra -Werror get_next_line.c libft/src/*.c -I libft/includes -o gnl_test
```

#### With Test Program

```bash
# Compile the test program
gcc -Wall -Wextra -Werror main.c get_next_line.c libft/src/*.c -I libft/includes -o test_gnl
```

#### Custom Buffer Size

```bash
# Compile with custom buffer size
gcc -Wall -Wextra -Werror -D BUFF_SIZE=100 get_next_line.c libft/src/*.c -I libft/includes -o gnl_test
```

## 📝 Usage

### Basic File Reading

```c
#include "get_next_line.h"
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    char *line;
    int ret;

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    while ((ret = get_next_line(fd, &line)) == 1) {
        printf("Line: %s\n", line);
        free(line);  // Always free the line!
    }

    if (ret == -1) {
        printf("Error reading file\n");
    } else {
        printf("End of file reached\n");
    }

    close(fd);
    return 0;
}
```

### Reading from stdin

```c
#include "get_next_line.h"

int main() {
    char *line;
    int ret;

    printf("Enter lines (Ctrl+D to end):\n");
    while ((ret = get_next_line(0, &line)) == 1) {
        printf("You entered: %s\n", line);
        free(line);
    }

    return 0;
}
```

### Multiple File Descriptors

```c
#include "get_next_line.h"
#include <fcntl.h>

int main() {
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1, *line2;

    // Read from both files alternately
    while (get_next_line(fd1, &line1) == 1 &&
           get_next_line(fd2, &line2) == 1) {
        printf("File1: %s\n", line1);
        printf("File2: %s\n", line2);
        free(line1);
        free(line2);
    }

    close(fd1);
    close(fd2);
    return 0;
}
```

## 🧪 Testing

### Test with Provided Program

```bash
# Read from stdin
./test_gnl

# Read from file
./test_gnl filename.txt

# Test with sample files
./test_gnl 2600-0.txt
./test_gnl m83.txt
```

### Edge Case Testing

```bash
# Test with empty file
touch empty.txt && ./test_gnl empty.txt

# Test with single character file
echo -n "a" > single.txt && ./test_gnl single.txt

# Test with no newline at end
echo -n "line without newline" > no_newline.txt && ./test_gnl no_newline.txt

# Test with only newlines
printf "\n\n\n" > newlines.txt && ./test_gnl newlines.txt
```

## 📁 Project Structure

```
42_get_next_line/
├── get_next_line.c          # Main implementation
├── get_next_line.h          # Header file with prototypes
├── main.c                   # Test program
├── libft/                   # Custom C library dependency
│   ├── includes/
│   │   └── libft.h          # Library header
│   ├── src/
│   │   └── *.c              # Library function implementations
│   └── Makefile             # Library build configuration
├── 2600-0.txt              # Large test file
├── m83.txt                 # Sample test file
├── author                  # Author information
└── README.md               # Project documentation
```

## 🔍 Implementation Details

### Core Algorithm

1. **Static Storage**: Uses a static array to store partial lines for each file descriptor
2. **Buffer Reading**: Reads data in chunks of `BUFF_SIZE` bytes
3. **Line Extraction**: Searches for newline characters and extracts complete lines
4. **Memory Management**: Dynamically allocates memory for each line returned

### Key Functions

#### `get_next_line(const int fd, char **line)`

Main function that orchestrates the line reading process:

- Validates input parameters
- Manages static storage array
- Reads data in chunks until newline is found
- Calls helper function to extract the line

#### `ft_new_line(char **str, char **line, int fd)`

Helper function that extracts a line from the buffer:

- Finds the position of the newline character
- Allocates memory for the line
- Updates the remaining buffer content
- Handles end-of-file scenarios

### Memory Management Strategy

- **Static Array**: Maintains state for up to 4096 file descriptors
- **Dynamic Allocation**: Each line is dynamically allocated
- **Cleanup**: Automatically frees memory when EOF is reached
- **Error Handling**: Proper cleanup on allocation failures

### Error Handling

The implementation includes comprehensive error checking:

```c
#define PRE_ERRORS() if (fd < 0 || fd > 4096 || !line) return (-1);
#define POST_ERRORS() if (ret < 0) return (-1);
#define ENDFILE() if (ret == 0 && (!str[fd] || str[fd][0] == '\0')) return (0);
```

- **Invalid file descriptors**: fd < 0 or fd > 4096
- **NULL pointer**: line parameter is NULL
- **Memory allocation failures**: Returns -1 on malloc failure
- **Read errors**: Returns -1 on read() failure

## 📊 Performance Characteristics

| Buffer Size  | Memory Usage | System Calls | Performance |
| ------------ | ------------ | ------------ | ----------- |
| 1            | Very Low     | Very High    | Slow        |
| 20 (default) | Low          | Moderate     | Good        |
| 100          | Moderate     | Low          | Fast        |
| 1000+        | High         | Very Low     | Very Fast   |

## 🎯 42 School Standards

This project adheres to the strict 42 School norminette standards:

- ✅ **Maximum 25 lines per function**
- ✅ **Maximum 80 characters per line**
- ✅ **No for loops** (while loops only)
- ✅ **Limited variables per function**
- ✅ **Specific formatting conventions**
- ✅ **No global variables** (static variables allowed)
- ✅ **Proper error handling**
- ✅ **Memory leak prevention**
- ✅ **No forbidden functions**

## 🔗 Dependencies

This project uses a custom `libft` library that provides:

### String Functions

- `ft_strlen` - Calculate string length
- `ft_strdup` - Duplicate string
- `ft_strjoin` - Join two strings
- `ft_strsub` - Extract substring
- `ft_strchr` - Locate character in string
- `ft_strnew` - Create new string
- `ft_strdel` - Delete string

### Memory Functions

- `ft_memalloc` - Allocate and zero memory
- `ft_memdel` - Free memory and set pointer to NULL

### Output Functions

- `ft_putendl` - Output string with newline

## 🎓 About 42 School

42 is a global education initiative that proposes a new way of learning technology: no courses, no teachers, no tuition fees. The peer-to-peer learning allows students to unleash their creativity through project-based learning.

---

\_
The `get_next_line` project is fundamental to understanding:

- File I/O operations in C
- Static variable management
- Memory allocation and deallocation
- Buffer management strategies
- Error handling techniques

This project serves as preparation for more complex projects that require efficient file processing and memory management skills.
