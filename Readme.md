mkdir src
mkdir bin

c_programming/
|-- src/
|-- bin/
`-- guess_the_number.c  (your old file)

move guess_the_number.c src/

gcc src/guess_the_number.c -o bin/guess_the_number

.\bin\guess_the_number