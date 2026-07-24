# Q4 Explanation

**tail -f system.log**
Continuously streams new lines appended to the log file in real time. This is the core of live monitoring — it blocks and waits, outputting each new line as it arrives.

**grep "ERROR"**
Filters the stream, passing only lines containing ERROR downstream through the pipe. --line-buffered ensures grep outputs each match immediately rather than waiting for a buffer to fill.

**tee -a error_report.txt**
Splits the stream: writes matched ERROR lines to the report file in append mode AND passes them forward. This lets us log and display simultaneously.

**> /dev/null**
Suppresses terminal output. /dev/null is a special Linux device that discards everything written to it — used to silence unnecessary output without losing data (already saved by tee).

**grep "ERROR" system.log | wc -l**
Pipes filtered ERROR lines into wc -l which counts the number of lines, giving a quick total error count.

**How pipes improve efficiency:**
Each command runs as a separate process. The pipe connects stdout of one to stdin of the next, creating a streaming pipeline with no intermediate temp files. Memory-efficient for large log files.
