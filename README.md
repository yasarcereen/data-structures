# Data Structures

This repository contains assignments of the course BLG223E - Data Structures, 2022-2023 Fall Term at Istanbul Technical University.

---

### Tools & technologies used:
- C++
- Docker
- Valgrind
- Calico
- Visual Studio Code

---

### Compilation

In the directory where the C++ file is located, run:
`g++ file.cpp -o file.out`

`./file.out` to run.

---

### Memory Leak

`valgrind --leak-check=yes ./file.out`

If necessary, add command line parameters after the name of the executable file.  
Use `--log-file=<filename>` to write to a file.

Pretty much everything you will need to know about memory leaks (for the scope of this course) is in **[this](https://stackoverflow.com/a/44989219)** great stackoverflow entry.

---

### Testing

`calico testfile.yaml`

For more detailed output, also add `--debug`.
