# MiniProjs

A collection of small, self-contained experiments in C, C++, Python, and Qt. The projects range from simple console games to GUI-based network utilities.

## Projects

| Path | Language(s) | Summary | How to run |
| --- | --- | --- | --- |
| `rockPaperScissor.cpp` | C++ | Console Rock–Paper–Scissors game vs. computer. | `g++ -std=c++11 rockPaperScissor.cpp -o rps && ./rps` |
| `udpPacketSender/` | C++ (Qt, QMake) | GUI tool to craft and send UDP packets with rate control, payload patterns, and live hex logging. | `cd udpPacketSender && qmake && make` (or open `udpPacketSender.pro` in Qt Creator) |
| `folder_hash_md5.py` | Python | Folder hashing helper (MD5) for quick integrity checks. | `python3 folder_hash_md5.py <directory>` |
| `folder_hash_Version2.py` | Python | Enhanced folder hashing script (e.g., additional hash or reporting). | `python3 folder_hash_Version2.py <directory>` |
| `HealthMonitoringApp/` | C/C++ | Placeholder app (sources in this folder); add details and run instructions here. |

> Tip: If a build or run command needs extra flags or dependencies, document them in the corresponding project folder’s README.

## Repository structure

```
MiniProjs/
├─ rockPaperScissor.cpp
├─ folder_hash_md5.py
├─ folder_hash_Version2.py
├─ udpPacketSender/
│  ├─ main.cpp, mainwindow.cpp/.h/.ui
│  ├─ Makefile, Makefile.Debug, Makefile.Release
│  ├─ udpPacketSender.pro (.user), readme.md
├─ HealthMonitoringApp/          # contents to document
└─ .vscode/, .gitignore
```

## Prerequisites

- **C/C++ toolchain**: GCC/Clang or MSVC; C++17 support recommended.
- **Qt 5 or Qt 6 + qmake** for `udpPacketSender`.
- **Python 3.8+** for hashing utilities.

## Quick start

```bash
# Rock–Paper–Scissors
g++ -std=c++11 rockPaperScissor.cpp -o rps && ./rps

# UDP Packet Sender (Qt)
cd udpPacketSender
qmake
make              # or build in Qt Creator

# Folder hash (MD5)
python3 folder_hash_md5.py /path/to/folder
```

## Contributing

1. Create a branch for your change.
2. Keep each mini-project self contained (code, sample data, mini README).
3. Run/verify the project before opening a PR; add usage notes if you changed the interface.
4. Open a PR with a short demo (gif/screenshot or console output) when possible.

## Roadmap

- Document and polish `HealthMonitoringApp`.
- Add automated lint/build checks per language.
- Add tests or sample data for hashing utilities.
- Package UDP sender binaries for Windows/Linux.

## License

Specify the license for this repo (e.g., MIT). If unsure, add a `LICENSE` file or clarify in issues.

---

*Last updated: 2026-03-13*