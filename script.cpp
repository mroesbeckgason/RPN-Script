#include "script.h"
#include <fstream>
#include <sstream>

// Functions for classifying characters - these match with the expected
// definitions of "whitespace" and "digit" for RPN, so you are strongly
// encouraged to use them.

// desc: Checks if string command fits with any of the given commands
// if so it runs the given command
// pre : takes string command
// post: returns true if command is proper command, throws error if not
bool Script::run_command(std::string command) {
	if (command == "add") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		data_stack.push(a + b);
		return true;
	} else if (command == "sub") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		data_stack.push(a - b);
		return true;
	} else if (command == "mul") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		data_stack.push(a * b);
		return true;
	} else if (command == "div") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		if (b == 0) {
			std::cout << "dividing-by-zero error" << std::endl;
			return false;
		} else {
			data_stack.push(a / b);
			return true;
		}
	} else if (command == "pop") {
		data_stack.pop();
		return true;
	} else if (command == "dup") {
		int a = data_stack.pop();
		data_stack.push(a);
		data_stack.push(a);
		return true;
	} else if (command == "swap") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		data_stack.push(b);
		data_stack.push(a);
		return true;
	} else if (command == "enq") {
		int a = data_stack.pop();
		data_queue.enqueue(a);
		return true;
	} else if (command == "deq") {
		int a = data_queue.dequeue();
		data_stack.push(a);
		return true;
	} else if (command == "equal") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		if (a == b) {
			data_stack.push(1);
		} else {
			data_stack.push(0);
		}
		return true;
	} else if (command == "neg") {
		int a = data_stack.pop();
		if (a < 0) {
			data_stack.push(1);
		} else {
			data_stack.push(0);
		}
		return true;
	} else if (command == "jump") {
		int a = data_stack.pop();
		if (a < 1 || a > line_count) {
			std::cerr << "Jump to invalid line " << a << std::endl;
			halted = true;
			return true;
		}
		current_line = a;
		return true;
	} else if (command == "branch") {
		int b = data_stack.pop();
		int a = data_stack.pop();
		if (b != 0) {
			if (a < 1 || a > line_count) {
				std::cerr << "Jump to invalid line " << a << std::endl;
				halted = true;
				return true;
			}
			current_line = a;
		}
		return true;
	} else if (command == "write_char") {
        write_char();
		return true;
    } else if (command == "read_char") {
        read_char();
		return true;
    } else if (command == "write_int") {
        write_int();
		return true;
    } else if (command == "read_int") {
        read_int();
		return true;
    } else if (command == "halt") {
        halt();
		return true;
    } else if (command == "line") {
        line();
		return true;
    } else {
        std::stringstream message;
        message << "Unrecognized operation '" << command << "'"
                << " on line " << current_line << std::endl;
        throw std::runtime_error(message.str());
    }
}

// desc: Returns true if the input is a whitespace character.
// pre : None
// post: None, aside from description.
bool is_whitespace(char c) {
    return (c==' ')||(c=='\n')||(c=='\t')||(c=='\r');
}

// desc: Returns true if the input is a digit.
// pre : None
// post: None, aside from description.
bool is_digit(char c) {
    return (c>='0') && (c<='9');
}

// desc: Converts a digit character to its corresponding integer value
// pre : The input must be a digit character under ASCII standards
// post: None, aside from description.
int value_from_digit(char c) {
    return c-'0';
}

// desc: Converts a value to its corresponding digit character
// pre : The input must be a value between 0 and 9 (inclusive)
// post: None, aside from description.
char digit_from_value(int value) {
    return '0'+value;
}

// desc: Reads a character in from the terminal and pushes its
//       integer value onto the data_stack
// pre : None
// post: None, aside from description.
void Script::read_char() {
    char c;
    std::cin.read(&c,1);
    data_stack.push(c);
}

// desc: Pops the top value off of the data_stack and prints it
//       as a character to the terminal.
// pre : The data_stack is non-empty
// post: None, aside from description.
void Script::write_char() {
    char c = data_stack.pop();
    std::cout.write(&c,1);
}

// desc: Reads an integer in from the terminal and pushes its
//       integer value onto the data_stack
// pre : None
// post: None, aside from description.
void Script::read_int() {
    int value;
    std::cin >> value;
    data_stack.push(value);
}

// desc: Pops the top value off of the data_stack and prints it
//       as an integer to the terminal.
// pre : The data_stack is non-empty
// post: None, aside from description.
void Script::write_int() {
    std::cout << data_stack.pop();
}

// desc: Pushes the current line's number onto the stack.
// pre : None
// post: None, aside from description.
void Script::line() {
    data_stack.push(current_line);
}

// desc: Sets the script as halted.
// pre : None
// post: None, aside from description.
void Script::halt() {
    halted = true;
}


// desc: Removes all text on or after a '#' in each
//       line of the script
// pre : None
// post: None, aside from descripton
void Script::remove_comments() {
    for (int i=0; i<line_count; i++) {
        Queue revised;
        Queue line = lines[i];
        bool in_comment = false;
        while (!line.is_empty()) {
            char c = line.dequeue();
            if (c=='#') {
                in_comment = true;
            }
            if (!in_comment) {
                revised.enqueue(c);
            }
        }
        lines[i] = revised;
    }
}

// desc: Removes the first '"' on each line in the script.
//       Any characters that appear after this removed '"'
//       are replaced with the pattern " X enq ", where
//       "X" is the ASCII value of the character, as a string
//       representation of a decimal integer.
// pre : None
// post: None, aside from descripton
void Script::convert_string_literals() {
    for (int i=0; i<line_count; i++) {
        Queue revised;
        Queue line = lines[i];
        bool in_string = false;
        while ( (!in_string) && !line.is_empty()) {
            char c = line.dequeue();
            if (c=='"') {
                in_string = true;
            }
            if (!in_string) {
                revised.enqueue(c);
            }
        }
	while ( !line.is_empty() ) {
            // Leading space to avoid accidentally breaking grammar rules
            revised.enqueue(' ');
            char c = line.dequeue();
            // Insert hundreds, then tens, then ones-place digit
            if (c>=100) {
                revised.enqueue('0'+(c/100));
            }
            if (c>=10) {
                revised.enqueue('0'+((c%100)/10));
            }
            revised.enqueue('0'+(c%10));
            revised.enqueue(' ');
            revised.enqueue('e');
            revised.enqueue('n');
            revised.enqueue('q');
            revised.enqueue(' ');
            // Trailing space to avoid accidentally breaking grammar rules
        }
        lines[i] = revised;
    }
}


// desc: Checks that fundamental grammar rules are being followed
// pre : None
// post: Throws an exception if any of the following grammar rules
//       are broken:
//       - colon followed by non-whitespace
//       - colon preceded by whitespace or digit
//       - digit adjacent to character
void Script::check_grammar() {

    for (int i=0; i<line_count; i++) {

        Queue line = lines[i];
        char previous = '\0';
        bool is_first = true;
        std::stringstream message("Grammar check failed : ");
        bool fail = false;

        while ((!fail) && !line.is_empty()) {

            char c = line.dequeue();
            if (is_first) {
                is_first = false;
            } else if (c==':') {
                if (is_whitespace(previous) || is_digit(previous)) {
                    message << "A colon on line "<<i<<" is preceded by a "
                            << "non-whitespace character.";
                    fail = true;
                }
            } else if (is_digit(c)) {
                if ((!is_whitespace(previous))&&(!is_digit(previous))) {
                    message << "A digit on line "<<i<<" is preceded by a "
                            << "non-digit, non-whitespace character.";
                    fail = true;
                }
            } else if (!is_whitespace(c)) {
                if ((previous==':')||is_digit(c)) {
                    message << "A non-digit, non-whitespace character "
                            << "on line "<<i<<" is preceded by a "
                            << "colon or digit.";
                    fail = true;
                }
            }
            previous = c;
        }
        if (fail) {
            throw std::runtime_error(message.str());
        }
    }
}


// desc: Replaces all instances of the string "from" with the
//       string "into" in the script. Any instances of that
//       string that are directly followed by a color (':')
//       are simply removed.
// pre : The "from" argument must not contain whitespace characters
// post: None, aside from descripton
void Script::replace_word(std::string from, std::string into) {
    for (int i=0; i<line_count; i++) {
        Queue line = lines[i];
        Queue revised;
        std::string word;
        bool done = false;
        while (!done) {
            char c = ' ';
            if (line.is_empty()) {
                done = true;
            } else {
                c = line.dequeue();
            }
            if (is_whitespace(c)) {
                if (word==from) {
                    word = into;
                } else if (word == (from+":")) {
                    word = "";
                }
                for (char word_char : word) {
                    revised.enqueue(word_char);
                }
                if(!done) {
                    revised.enqueue(c);
                }
                word = "";
            } else {
                word += c;
            }
        }
        lines[i] = revised;
    }
}

// desc: Finds all sequences of non-whitespace characters followed
//       directly by a colon. For each sequence "X" that is found,
//       all sequences of the form "X:" are removed and all not
//       followed by a colon are replaced with the line that "X:"
//       first appears on.
// pre : Grammar rules are followed by the lines in the script
// post: None, aside from descripton
void Script::convert_labels() {
    for (int i=0; i<line_count; i++) {
        bool line_converted = false;
        while (!line_converted) {
            Queue line = lines [i];
            Queue revised;
            bool in_word = false;
            bool replace_occurred = false;
            std::string word;
            while ((!replace_occurred) && (!line.is_empty())) {
                char c = line.dequeue();
                if (c==':' && in_word) {
                    replace_word(word,std::to_string(i+1));
                    replace_occurred = true;
                } else if (!is_whitespace(c)){
                    in_word = true;
                    word += c;
                } else {
                    in_word = false;
                    word = "";
                }
            }
            if (!replace_occurred) {
                line_converted = true;
            }
        }
        for (int i=0; i<line_count; i++) {
            Queue revised;
            Queue line = lines[i];
        }
    }
}

// desc: Performs pre-processing to convert RPN++ scripts to normal
//       RPN code.
// pre : The lines of the script follow the grammar rules of RPN++
// post: If one or more grammar rules are broken, an exception is
//       thrown.
void Script::preprocess() {
    remove_comments();
    convert_string_literals();
    check_grammar();
    convert_labels();
}


Script::Script(std::string path) {
    std::ifstream file(path);
    char c;
    line_count = 0;
    while (file.read(&c,1)) {
        if (c=='\n') {
            line_count ++;
        }
    }

    lines = new Queue[line_count];
    file.clear();
    file.seekg(0);
    int line_index = 0;
    while (file.read(&c,1)) {
        if (c=='\n') {
            line_index ++;
        } else {
        	lines[line_index].enqueue(c);
		}
	}

	preprocess();
	current_line = 1;
	line_queue = lines[current_line-1];
	halted = false;
}


Script::~Script() {
	delete[] lines;
}

// desc: reads one line of input from file, correctly understands
// what the input means and does proper functions if given commands
// pre : None
// post: updates current_line so next time its called its on the next
// line.
void Script::step() {
	std::string command;

	while(!line_queue.is_empty()) {
		char item = line_queue.dequeue();

		while (is_whitespace(item) && !line_queue.is_empty()) {
			item = line_queue.dequeue();
		}

		if (line_queue.is_empty() && is_whitespace(item)) {
			break;
		}

		if (is_digit(item)) {
			int saved = item - '0';

			while (!line_queue.is_empty()) {
				item = line_queue.dequeue();
				if (is_whitespace(item) || !is_digit(item)) {
					break;
				}
				saved = saved*10;
				saved += item - '0';
			}
			data_stack.push(saved);


		} else {
			std::string saved;
			saved += item;

			while (!line_queue.is_empty()) {
				item = line_queue.dequeue();
				if (is_whitespace(item)) {
					break;
				}
				saved += item;
			}
			if (saved != "") {
				int old_line = current_line;
				try {
					run_command(saved);
				} catch (const std::runtime_error& e) {
					std::cerr << e.what() << std::endl;

					while (!data_stack.is_empty()) {
						data_stack.pop();
					}
				}

				if (halted) {
					return;
				}

				if (old_line != current_line) {
					if (current_line < 1 || current_line > line_count) {
						halted = true;
						return;
					}
					line_queue = lines[current_line - 1];
					return;
				}
			}
		}
	}
	current_line++;
	if (current_line > line_count) {
		halted = true;
		return;
	}
	line_queue = lines[current_line-1];
}



bool Script::is_halted() {
	return halted;
}

