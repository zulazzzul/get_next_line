*This project has been created as part of the 42 curriculum by nd-abreu.*

# get_next_line

## Description

get_next_line is a project from the 42 cursus. The goal was to implement a function that reads a line from a file descriptor, one line at a time. Successive calls to `get_next_line()` return successive lines from the file until EOF.

The function works both with files and with standard input (fd = 0), and handles any `BUFFER_SIZE` value passed at compile time.

The bonus part extends the function to handle multiple file descriptors at the same time, without losing track of the reading state of each one.

---

## Algorithm

The implementation is based on a static variable `remainder` that persists between calls, storing any bytes read beyond the current line.

On each call, the function:

1. Reads from `fd` in chunks of `BUFFER_SIZE` bytes, accumulating bytes in `remainder` until a `\n` or EOF is found (`read_until_newline`).
2. Extracts the first complete line from `remainder` — up to and including the `\n` — and returns it (`extract_line`).
3. Saves what comes after the `\n` in `remainder` for the next call (`update_remainder`).

The key design choices were:

- **Static variable** — `remainder` is declared `static` inside `get_next_line`, which means it persists between calls without being a global variable.
- **ft_strdup("")** — on the first call, `remainder` is NULL. Before entering the read loop, it is initialised with an empty string so that `ft_strchr` and `ft_strjoin` never receive NULL.
- **read_loop** — extracted as a separate function to comply with the norminette's 25-line limit per function. It is declared in the header alongside the other auxiliary functions.
- **Auxiliary functions** — `ft_strlen`, `ft_strchr`, `ft_strdup`, `ft_strjoin` and `ft_substr` were reimplemented in `get_next_line_utils.c` because the use of libft is forbidden in this project.
- **Error handling** — whenever `malloc` or `read` fails, any memory already allocated is freed before returning `NULL`, to avoid leaks.

---

## Bonus

The bonus version supports reading from multiple file descriptors at the same time, alternating between them without losing track of each one's reading state.

- **Single static variable** — `static char *remainder[FD_MAX]` replaces the single `remainder` pointer with an array. Each file descriptor has its own remainder, stored at `remainder[fd]`. An array still counts as one static variable.
- **FD_MAX** — defines the maximum number of file descriptors that can be open at the same time, each with an independent remainder. Set to 1024, the typical per-process limit on Linux.
- **Validation** — `fd >= FD_MAX` is checked alongside `fd < 0`, preventing out-of-bounds access to the array.
- **Same logic, different file** — `read_loop`, `read_until_newline`, `extract_line` and `update_remainder` are identical to the mandatory part; only `get_next_line` changes, indexing everything by `fd`.

Bonus files: `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`.

---

## Instructions

| Command | What it does |
|---------|-------------|
| `cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl` | Compiles the mandatory part |
| `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl` | Compiles with a custom `BUFFER_SIZE` |
| `cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o bonus` | Compiles the bonus part |

---

## Resources

### Documentation
- `man 2 read` — read() syscall
- `man 3 malloc`, `man 3 free` — memory management
- `free(NULL)` is a no-op

### AI Usage

AI was used as a learning support tool, in accordance with 42's guidelines:

- **Tasks:** understanding the logic of static variables, debugging memory management issues (double free, invalid reads), understanding the difference between `static` local variables and global variables, working through edge cases such as empty files, files without a newline, and invalid file descriptors, and understanding how file descriptors work for the bonus implementation.
- **Parts of the project:** used throughout the project as a tutor to explain concepts step by step and to review the code for correctness.
