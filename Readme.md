# Making Directories
mkdir src
mkdir bin

# Move Code to src
cd ./src/

# File Structure
c_programming/
|-- src/
|-- bin/
    |-- guess_the_number.c  (your code file)

# compile the code
gcc src/guess_the_number.c -o bin/guess_the_number

# run the code
.\bin\guess_the_number