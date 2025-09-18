<div align="center">

#  CVFS  
### (Custom Virtual File System in C++)

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](#)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](#)
[![Status](https://img.shields.io/badge/Status-Active-success.svg)](#)
[![Contributions](https://img.shields.io/badge/Contributions-Welcome-orange.svg)](#)

A lightweight **Virtual File System** implementation that mimics Unix-like commands.  
Perfect for **students, system programmers, and OS enthusiasts** 🚀  

</div>

---

## ✨ Features
- 📝 Create & delete files in a simulated VFS  
- 📂 Open/Close files with **file descriptors**  
- 📖 Read & Write file contents with **permission checks**  
- 🎯 Seek operations (`lseek`) for pointer manipulation  
- 📊 Metadata management (inode, size, permissions, reference count)  
- ❌ Error handling with return codes  
- 📑 Built-in `man` & `help` for documentation  
- 🧹 Automatic cleanup on exit  

---

## 🛠️ Supported Commands

| Command | Description |
|---------|-------------|
| `creat fname perm` | Create file (`perm = 1: Read, 2: Write, 3: Read+Write`) |
| `open fname mode` | Open existing file (`mode = 1: Read, 2: Write, 3: Read+Write`) |
| `close fd` | Close file using FD |
| `read fd size` | Read `size` bytes |
| `write fd data` | Write `data` into file |
| `lseek fd offset whence` | Move file pointer (`0: Start, 1: Current, 2: End`) |
| `rm fname` | Remove file |
| `ls` | List all files |
| `stat` | Show file system status |
| `man cmd` | Manual page |
| `clear` | Clear console |
| `exit` | Exit CVFS |

---

## ⚙️ Installation & Run

```bash
# Clone repository
git clone https://github.com/KartikkxCode/Customised-Virtual-File-System.git
cd Customised-Virtual-File-System

# Compile
g++ cvfs.cpp -o cvfs

# Run
./cvfs
