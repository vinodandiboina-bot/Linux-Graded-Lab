# Q1 Explanation

**mkdir -p submissions backup_unique**
Created input and backup directories. The -p flag prevents errors if they already exist.

**md5sum "$file"**
Generates an MD5 hash for each file to detect identical content regardless of filename. Two files with the same hash are duplicates.

**declare -A seen_hashes**
Used a Bash associative array to track already-seen hashes, allowing fast duplicate detection.

**cp "$file" "$BACKUP_DIR/"**
Copies only unique files to the backup directory.

**Redirection operators:**
- > overwrites report.txt with the report header
- >> appends subsequent lines to report.txt
- 2>> redirects stderr (error messages) to errors.txt separately

**File handling:**
md5sum computes content-based fingerprints. Associative array tracks uniqueness in memory. Separate error log via stderr redirection keeps output clean.
