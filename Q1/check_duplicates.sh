#!/bin/bash

SUBMISSIONS_DIR="./submissions"
BACKUP_DIR="./backup_unique"
REPORT_FILE="report.txt"
ERROR_FILE="errors.txt"

mkdir -p "$SUBMISSIONS_DIR" "$BACKUP_DIR"

echo "student A work" > "$SUBMISSIONS_DIR/student1.txt"
echo "student B work" > "$SUBMISSIONS_DIR/student2.txt"
echo "student A work" > "$SUBMISSIONS_DIR/student3.txt"
echo "student C work" > "$SUBMISSIONS_DIR/student4.txt"

echo "=== Duplicate Submission Report ===" > "$REPORT_FILE"
echo "Generated on: $(date)" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

TOTAL=0
DUPLICATES=0
BACKED_UP=0

declare -A seen_hashes

for file in "$SUBMISSIONS_DIR"/*; do
    if [ ! -f "$file" ]; then
        echo "Skipping non-file: $file" >> "$ERROR_FILE" 2>&1
        continue
    fi

    TOTAL=$((TOTAL + 1))
    hash=$(md5sum "$file" 2>>"$ERROR_FILE" | awk '{print $1}')

    if [ -n "${seen_hashes[$hash]}" ]; then
        echo "DUPLICATE: $(basename $file) is a duplicate of ${seen_hashes[$hash]}" >> "$REPORT_FILE"
        DUPLICATES=$((DUPLICATES + 1))
    else
        seen_hashes[$hash]=$(basename "$file")
        cp "$file" "$BACKUP_DIR/" 2>>"$ERROR_FILE"
        BACKED_UP=$((BACKED_UP + 1))
    fi
done

echo "" >> "$REPORT_FILE"
echo "Total files processed : $TOTAL" >> "$REPORT_FILE"
echo "Duplicate files found : $DUPLICATES" >> "$REPORT_FILE"
echo "Unique files backed up: $BACKED_UP" >> "$REPORT_FILE"

cat "$REPORT_FILE"
