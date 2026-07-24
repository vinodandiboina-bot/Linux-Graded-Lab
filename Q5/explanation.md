# Q5 Explanation — vi Recovery Mechanisms

## Scenario
A developer was editing config.conf in vi when the system crashed before saving.

---

## Mechanism 1: Swap Files (.swp) — MOST RELIABLE

When you open a file in vi, it immediately creates a hidden swap file (e.g. .config.conf.swp). Every edit is written to this swap file every 4 seconds automatically.

**Recovery command:**
vi -r config.conf

This opens vi in recovery mode, restoring all unsaved edits from the swap file. After verifying the content, save with :wq and delete the swap file with: rm .config.conf.swp

---

## Mechanism 2: Undo History (in-memory)

vi keeps an undo tree in RAM during the session. After crash recovery via swap file, press u to undo changes. However this is LOST if the process is killed — it does not survive crashes on its own.

---

## Mechanism 3: Registers

vi has named registers (a-z) that store yanked/deleted text during a session. If text was yanked before the crash and the session is recovered via swap, registers may still be accessible. Limitation: in-memory only, not persisted.

---

## Mechanism 4: Backup Files (~)

With "set backup" in .vimrc, vim creates config.conf~ — a copy of the file as it was BEFORE the current editing session. This is NOT unsaved changes — it is the last saved version only.

---

## Mechanism 5: Persistent Undo (undofile)

With "set undofile" in .vimrc, vim writes undo history to a .un~ file on disk. This survives crashes and reboots. Open the file normally and vim auto-applies the undo history.

---

## BEST STRATEGY: Swap File Recovery

Primary method: vi -r config.conf immediately after reboot.

Steps:
1. Run: vi -r config.conf
2. Verify the recovered content looks correct
3. Save with: :wq
4. Delete swap file: rm .config.conf.swp

Why it is best: The swap file is written continuously during editing, capturing changes up to 4 seconds before the crash. It is automatic with zero setup required and built into vi by default. Backup files only store pre-session state so they cannot recover unsaved edits.

Additional tip: Enable "set undofile" in .vimrc as a second layer of protection.
