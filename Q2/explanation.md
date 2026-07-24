# Q2 Explanation

**fork()**
Creates a child process by duplicating the parent. Returns 0 in the child and the child's PID in the parent. Used here to simulate multiple concurrent web server worker processes.

**SIGCHLD + sigaction()**
Registers a signal handler so whenever a child exits, the parent immediately calls waitpid() to reap it. This prevents zombie processes from accumulating in the process table.

**waitpid(pid, &status, WNOHANG)**
Non-blocking check on a specific child. If it returns 0, the child is still running — treated as unresponsive after the timeout period.

**kill(pid, SIGTERM) then kill(pid, SIGKILL)**
SIGTERM gives the child a chance to clean up gracefully. If it still hasn't exited after 1 second, SIGKILL forcefully terminates it — mimicking how web servers handle stuck workers.

**How they work together:**
fork() creates workers, waitpid() monitors them with a timeout, SIGCHLD handler auto-reaps finished ones, and SIGTERM/SIGKILL terminate unresponsive ones. Together they form a complete process lifecycle manager.
