#!/bin/bash

LOG_FILE="system.log"
REPORT_FILE="error_report.txt"

echo "=== ERROR Report: $(date) ===" > "$REPORT_FILE"

# tail -f streams new lines in real time
# grep filters only ERROR lines
# tee appends to report file
# > /dev/null suppresses terminal clutter
tail -f "$LOG_FILE" | grep --line-buffered "ERROR" | tee -a "$REPORT_FILE" > /dev/null &

echo "Monitor running in background. PID=$!"
echo "Errors are being saved to $REPORT_FILE"
