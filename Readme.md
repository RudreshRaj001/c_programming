# C Programming Playground 🚀

This repository is a collection of my C programming projects, created for learning and practice. Each project is organized with a clean separation between source code and compiled executables.

-----

## 📂 Project Structure

The repository uses a simple **`src`** (source) and **`bin`** (binary) folder structure to keep things organized. All C source files should be placed in the `src` directory, and the compiled programs will be placed in the `bin` directory.

```
c-programming/
├── src/
│   └── project_name.c
├── bin/
│   └── (compiled executables will go here)
├── build.bat
└── README.md
```

-----

## 🛠️ Manual Development Workflow

Follow these steps to manually compile and run any project. All commands should be run from the root directory.

### 1\. Write Your Code

Place your C source file (e.g., `my_project.c`) inside the `/src` directory.

### 2\. Compile the Code

Use `gcc` to build your program. The `-o` flag specifies the output path.

```bash
# Generic command
gcc src/<your_file_name>.c -o bin/<your_executable_name>

# Example
gcc src/guess_the_number.c -o bin/guess_the_number
```

### 3\. Run the Program

Execute the compiled program from the `bin` directory. Remember to use `.\` in PowerShell or Git Bash.

```powershell
# Generic command
.\bin\<your_executable_name>

# Example
.\bin\guess_the_number
```

-----

## ⚡ Automated Compilation (File Watching)

To automatically re-compile your code every time you save a file, you can use the `chokidar-cli` file watcher.

### 1\. Create a Build Script

First, create a helper script named **`build.bat`** in the root of your project. This script will handle the compilation command.

**`build.bat`**

```batch
@echo off
echo [Compiler] Building %1...
gcc %1 -o bin/%~n1
echo [Compiler] Successfully created bin/%~n1.exe
```

### 2\. Install the File Watcher

You'll need Node.js and npm installed for this step. Install `chokidar-cli` globally from your terminal.

```powershell
npm install -g chokidar-cli
```

### 3\. Start the Watcher

Run the following command in your terminal. It will watch all `.c` files in the `src` folder and run the `build.bat` script whenever a change is detected.

```powershell
chokidar "src/**/*.c" -c "build.bat {path}"
```

Now, just save your C file, and the new executable will be created in the `bin` folder instantly\!