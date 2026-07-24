# Q3 Explanation

**open(FILENAME, O_CREAT | O_RDWR | O_TRUNC, 0644)**
Opens or creates the file for reading and writing. O_TRUNC clears existing content. Returns a file descriptor — a low-level integer handle used by all subsequent operations. Permission 0644 makes it readable by all but writable only by owner.

**write(fd, emp, sizeof(Employee))**
Writes raw binary struct data directly to the file using a Linux system call. Unlike fwrite(), there is no C library buffering — gives precise byte-level control.

**lseek(fd, index * sizeof(Employee), SEEK_SET)**
Moves the file pointer to any record position in O(1) time. Multiplying index by struct size gives the exact byte offset, enabling random access without reading the whole file.

**read(fd, emp, sizeof(Employee))**
Reads exactly one record's worth of bytes from the current file position into the struct. Paired with lseek, this retrieves any specific record efficiently.

**close(fd)**
Releases the file descriptor back to the OS and flushes pending kernel buffers. Essential to prevent file descriptor leaks.

**Together:** open→write→lseek→write(update)→lseek→read form a complete buffer-free file I/O pipeline at the syscall level for security and precision.
