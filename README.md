*This project has been created as part of the 42 curriculum by nd-abreu.*

# get_next_line

## Description

get_next_line is a C project that implements a function which reads and returns the next line from a file descriptor. The function reads from the file descriptor in fixed-size chunks (defined by `BUFFER_SIZE`) and returns one line at a time (including the terminating newline if present). The project includes a bonus version supporting multiple file descriptors simultaneously.

Goal: implement a robust, memory-safe `get_next_line` that handles arbitrary line lengths and ensures no leaks while satisfying the 42 project's constraints.

## Instructions

- Compile the mandatory single-fd version:

```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c -o gnl
```

- Compile the bonus (multi-fd) version:

```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

- Run the program reading from a file:

```
./gnl < giant_line.txt
# or
./gnl_bonus < giant_line.txt
```

- If a `gnl_test` helper or additional test harness exists in the repo, you can run it directly (make sure it's executable):

```
./gnl_test
```

Notes:
- Adjust `BUFFER_SIZE` at compile time using `-D BUFFER_SIZE=<n>` to test different chunk sizes.
- The provided compile examples assume a simple test harness or manual usage; adapt as needed for your environment.

## Resources

- POSIX `read(2)` manual and general C standard library documentation.
- 42 project subject and guidelines for `get_next_line`.
- Articles and tutorials on buffered I/O and safe dynamic memory handling in C.

AI usage:

- An AI assistant was used to draft this `README.md` and to help explain the algorithm and reasoning behind implementation choices. The actual implementation code (`get_next_line.c`, `get_next_line_bonus.c`, and utility files) was written by the student. The AI assisted with documentation, algorithm explanation, and example commands only.

## Algorithm Explanation and Justification

Overview:

- The `get_next_line` implementation reads from the given file descriptor in fixed-size chunks of `BUFFER_SIZE` bytes using `read()`.
- Data read from the descriptor is appended to a dynamically managed "storage" string that preserves leftover data between calls.
- On each call, the function searches the storage for a newline (`'\n'`). If a newline is found, the function extracts and returns the substring from the start up to and including the newline, and stores the remainder for the next call.
- If no newline is found, the function continues reading and appending until it either finds a newline or `read()` returns 0 (EOF) or -1 (error).

Why this algorithm:

- The problem requires returning one line at a time without prior knowledge of the file or line lengths. Reading in fixed chunks avoids trying to allocate extremely large buffers preemptively and maps naturally to how file I/O is performed.
- Storing leftover bytes between calls (the "storage box") makes it possible to return exactly one line per call while preserving the rest of the input.
- Using dynamic allocation for storage and substrings supports arbitrarily long lines and keeps memory usage proportional to input size.

Complexity:

- Time: each byte from the file is read and processed a constant number of times. In the worst case, building and copying storage substrings causes linear work relative to the data moved; overall amortized time per character is O(1), and returning a line of length L costs O(L) to allocate and copy.
- Space: the algorithm uses O(L) additional memory for a returned line (where L is the length of the longest pending data chunk), plus any buffered but-unreturned remainder. The storage size equals the number of unread bytes read but not yet returned.

Memory safety and edge cases:

- The code checks for `malloc` failures and returns `NULL` on allocation errors, freeing any allocated storage to avoid leaks.
- When `read()` returns -1, the implementation frees storage and returns `NULL` to signal an error.
- The function handles EOF correctly: if remaining storage contains bytes but no newline, it returns the final bytes as the last line; subsequent calls return `NULL`.
- The bonus version maintains a separate `static` storage per file descriptor (`storage_box[MAX_FD]`) so multiple descriptors can be read independently and interleaved.

Justification of choices:

- Using `read()` with `BUFFER_SIZE`: conforms to the project's constraints and gives predictable memory usage patterns.
- Keeping a dynamic storage string per fd: necessary to handle arbitrary line boundaries that don't align with chunk boundaries.
- Splitting returned data with `ft_substr` and updating storage: makes memory ownership clear and avoids in-place modification complexity.

## Usage Examples

- Read a file line-by-line (compiled `gnl` prints to stdout if used in a testing main):

```
./gnl < giant_line.txt
```

- Interleave reads from two files using the bonus implementation (conceptual):

```
# In a test harness: open fd1 = open("file1.txt"), fd2 = open("file2.txt");
# call get_next_line(fd1), get_next_line(fd2) in any order and both fds keep their own storage.
```

## Notes and Next Steps

- Run static analysis tools (e.g., `valgrind`) to ensure no memory leaks under all test cases.
- Consider adding a small test harness (`main.c`) that demonstrates reading from multiple file descriptors and edge cases.

---

If you want, I can also add a small `main.c` test harness, example Makefile, or a `valgrind` script to verify memory usage — tell me which you'd prefer.
