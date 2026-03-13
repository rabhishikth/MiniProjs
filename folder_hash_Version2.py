#!/usr/bin/env python3
"""
Usage: python folder_hash.py   (run from the folder you want to hash)
Computes a deterministic SHA-256 over all files in this folder tree.
Ignores metadata; changes only when file contents or relative paths change.
"""

import hashlib
from pathlib import Path

def hash_file(path: Path, chunk_size: int = 1_048_576) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        while chunk := f.read(chunk_size):
            h.update(chunk)
    return h.hexdigest()

def hash_folder(folder: Path) -> str:
    entries = [p for p in folder.rglob("*") if p.is_file()]
    entries.sort(key=lambda p: p.relative_to(folder).as_posix())  # deterministic order

    h = hashlib.sha256()
    for p in entries:
        rel = p.relative_to(folder).as_posix()
        file_hash = hash_file(p)
        h.update(f"{rel}\0{file_hash}\n".encode("utf-8"))  # include path + file hash
    return h.hexdigest()

def main():
    folder = Path(".").resolve()
    print(f"Hashing folder: {folder}")
    print(f"Folder SHA-256: {hash_folder(folder)}")

if __name__ == "__main__":
    main()