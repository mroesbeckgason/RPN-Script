RPN Script Interpreter
Overview

This project is an interpreter for a Reverse Polish Notation (RPN) scripting language. It evaluates arithmetic and logical expressions, manages control flow, and supports basic input/output using stack and queue data structures.

Scripts are executed line by line, with each line interpreted as an RPN expression.

How It Works

The program reads a script file passed as a command-line argument

Each line of the script is stored as a queue of characters

Execution uses:

an integer stack for computation

an integer queue for enqueue/dequeue operations

Numbers are pushed onto the stack

Operations manipulate the stack, queue, or control flow

Execution continues until the script finishes or a halt instruction is encountered

Supported Operations

Arithmetic and stack operations:

add, sub, mul, div

pop, dup, swap

equal, neg

Queue operations:

enq, deq

Control flow:

jump, branch, line, halt

Input / Output:

read_char, write_char

read_int, write_int

Invalid operations or insufficient operands produce descriptive errors.

RPN++ Support

An optional preprocessing step supports:

Comments (#)

String literals ("...")

Named jump labels (label:)

Scripts without these features are executed as standard RPN.

Project Structure
--------------------------
p5.cpp
script.h / script.cpp
stack.h  / stack.cpp
queue.h  / queue.cpp
--------------------------

--------------------------
Running the Program
./p5 path/to/script.txt
--------------------------
Notes

Uses dynamically implemented stack and queue classes

Designed to be memory-safe and valgrind-clean

Unknown operations or invalid runtime states are handled gracefully
