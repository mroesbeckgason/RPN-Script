//============================================================================
// Name        : script.h
//
// Desc		   : stack h file, defining stack class
//
// Author      : Mason Groesbeck
//============================================================================
#ifndef SCRIPT
#define SCRIPT

#include <iostream>
#include "queue.h"
#include "stack.h"

class Script {

    int    line_count;
    Queue *lines;

    bool halted;
    int  current_line;

    Queue data_queue;
    Stack data_stack;

    Queue line_queue;


    void read_char();
    void write_char();
    void read_int();
    void write_int();
    void line();
    void halt();


    // You probably shouldn't change these methods,
    // unless you are advised otherwise.
    void remove_comments();
    void convert_string_literals();
    void check_grammar();
    void replace_word(std::string from, std::string into);
    void convert_labels();
    void preprocess();

    bool run_command(std::string command);


    public:

    Script(std::string path);
    Script(std::string path,bool verbose);
    ~Script();
    void step();
    bool is_halted();

};

#endif // SCRIPT
