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
└── README.md
```

-----

## 🛠️ Development Workflow

Follow these steps to compile and run any project in this repository. All commands should be run from the root directory of the project (`c_programming/`).

### 1\. Write Your Code

Place your C source file (e.g., `my_project.c`) inside the `/src` directory.

### 2\. Compile the Code

Use the `gcc` compiler to build your program. The `-o` flag is used to specify the output path and filename for the executable, which should be in the `bin` folder.

**Generic Command:**

```bash
gcc src/<your_file_name>.c -o bin/<your_executable_name>
```

### 3\. Run the Program

Execute the compiled program from the `bin` directory. In PowerShell or Git Bash, you must prefix the command with `.\` to specify the current directory.

**Generic Command:**

```powershell
.\bin\<your_executable_name>
```

-----

## ✨ Example: `guess_the_number` Project

Here is how to compile and run the `guess_the_number` project as an example.

**1. Compilation:**

```bash
gcc src/guess_the_number.c -o bin/guess_the_number
```

**2. Execution:**

```powershell
.\bin\guess_the_number
```