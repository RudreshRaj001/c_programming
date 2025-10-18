@echo off
echo [Compiler] Building %1...
gcc %1 -o bin/%~n1
echo [Compiler] Successfully created bin/%~n1.exe