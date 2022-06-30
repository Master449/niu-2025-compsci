//**************************************
//
// scc.cpp
// CSCI 241 Assignment 9
//
// Created by David Flowers II (z1942130)
//
//**************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>

#include "sml.h"
#include "inpost.h"

using namespace std;

/**
 *
 * Symbol table entry.
 *
 */

struct table_entry
{
    int symbol;
    char type;
    int location;
};

/**
 *
 * Simple compiler.
 *
 */
class scc {
public:

    // Data members
    static const int MEMORY_SIZE = 100;
    static const int SYMBOL_TABLE_SIZE = 1000;

    // Member functions
    scc();
    void first_pass();
    void second_pass();
    void print_program() const;

private:

    // Data members
    int memory[MEMORY_SIZE];    // Program memory.
    int data[MEMORY_SIZE];      // Input data values.
    int ndata = 0;              // Number of input data values.

    table_entry symbol_table[SYMBOL_TABLE_SIZE];     // Symbol table.
    
    int flags[MEMORY_SIZE];     // Array of flags to mark partial
                                // instructions.

    int next_instruction_addr = 0;    // Address of next instruction.
    int next_const_or_var_addr = MEMORY_SIZE - 1;
    int next_symbol_table_idx = 0;

    // Member functions

    void memory_check() const;
    void data_check() const;
    void stack_space_check(int) const;

    int get_symbol_location(const string&);
    int search_symbol_table(int, char) const;

    void handle_input(istringstream&);
    void handle_data(istringstream&);
	void handle_let(istringstream&, string);
	void handle_goto(istringstream&);
	void handle_if(istringstream&);
	void handle_print(istringstream&);
    void handle_end();
};

/**
 * Compiles a Simple program to SML and
 * prints it to standard output.
 */
int main() {
    scc compiler;

    compiler.first_pass();

    compiler.second_pass();

    compiler.print_program();

    return 0;
}

/**
 * Constructor - initializes memory and flags arrays.
 */
scc::scc() {
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 7777;
        flags[i] = -1;
    }
}

/**
 * Performs first pass of compilation.
 */
void scc::first_pass() {
    string buffer1, buffer2, command;
    int line_number;

    while (getline(cin, buffer1))
    {
        buffer2 = buffer1;         // buffer2 used for 'let'
        istringstream ss(buffer1);

        ss >> line_number;

        // Add line_number to symbol table with type 'L'.
        symbol_table[next_symbol_table_idx].symbol = line_number;
        symbol_table[next_symbol_table_idx].type = 'L';
        symbol_table[next_symbol_table_idx].location = next_instruction_addr;
        next_symbol_table_idx++;

        ss >> command;

        if (command == "input")
        {
            handle_input(ss);
        }
        else if (command == "data")
        {
            handle_data(ss);
        }
        else if (command == "let")
        {
            handle_let(ss, buffer2);
        }
        else if (command == "goto")
        {
            handle_goto(ss);
        }
        else if (command == "if")
        {
            handle_if(ss);
        }
        else if (command == "print")
        {
            handle_print(ss);
        }
        else if (command == "rem")
        {
            // Nothing
        }
        else
        {
            handle_end();
        }
    }
}

/**
 * Performs second pass of compilation.
 */
void scc::second_pass() {
	int index = next_const_or_var_addr - 1;

	// Loop through flags and memory arrays.
	for (int i = 0; i < next_instruction_addr; i++) {
		if (flags[i] != -1) {
			if (flags[i] > 0)
			{
				int location = search_symbol_table(flags[i], 'L');
				memory[i] += symbol_table[location].location;
			} 
			else if (flags[i] == -2)
			{
				memory[i] += next_const_or_var_addr;
			} 
			else if (flags[i] < -2) 
			{
				int n = -3 - flags[i];
				stack_space_check(index - n);
				memory[i] += index - n;
			}
		}
	}
}

/**
 * Prints memory and data for the compiled SML program.
 */
void scc::print_program() const {
    cout << setfill('0') << internal << showpos;

    // Print the entire memory array.
    for (int i = 0; i < MEMORY_SIZE; i++) {
        cout << setw(5) << memory[i] << endl;
	}

    // Print the "end of instructions" sentinel value.
    cout << -99999 << endl;

    // Print the input data values.
    for (int i = 0; i < ndata; i++) {
        cout << noshowpos << data[i] << endl;
	}
}

/**
 * Checks whether there is room in the memory array to add
 * another instruction.
 */
void scc::memory_check() const {
    if (next_instruction_addr >= MEMORY_SIZE || 
        next_instruction_addr > next_const_or_var_addr)
    {
        cout << "*** ERROR: ran out of Simplesim memory ***\n";
        exit(1);
    }
}

/**
 * Checks whether there is room in the data array to add
 * another data item.
 */
void scc::data_check() const {
    if (ndata == MEMORY_SIZE - 1)
    {
        cout << "*** ERROR: too many data lines ***\n";
        exit(1);
    }
}

/**
 * Checks whether the top of the stack has crossed into
 * the region of the memory array that contains instructions.
 *
 * @param location Location of the top of the stack.
 */
void scc::stack_space_check(int location) const {
    // If top of the stack has hit the instructions...
    if (location < next_instruction_addr)
    {
        cout << "*** ERROR: insufficient stack space ***\n";
        exit(1);
    }
}

/**
 * Gets the location of a constant or variable, adding it
 * to the symbol table and memory if necessary.
 *
 * @param token The symbol to locate.
 *
 * @return The symbol's location.
 */
int scc::get_symbol_location(const string& token) {
    int location, symbol;
    char type;

    if (islower(token[0]))
    {
        // This is a variable.
        symbol = token[0];
        type = 'V';
    }
    else
    {
        // This is an integer constant.
        symbol = stoi(token);
        type = 'C';
    }

    int index = search_symbol_table(symbol, type);

    if (index == -1)
    {
        // This symbol is not in the symbol table yet.
        
        // Add this symbol to the symbol table and memory.
        location = next_const_or_var_addr;

        // Add symbol to symbol table.
        symbol_table[next_symbol_table_idx].symbol = symbol;
        symbol_table[next_symbol_table_idx].type = type;
        symbol_table[next_symbol_table_idx].location = location;
        next_symbol_table_idx++;

        // Add this constant or variable to memory.
        memory_check();
        if (type == 'V')
            memory[location] = 0;
        else
            memory[location] = symbol;

        next_const_or_var_addr--;
    }
    else
    {
        // This symbol is in the symbol table at element
        // index.
        location = symbol_table[index].location;
    }

    return location;
}

/**
 * Searches the symbol table for a symbol with a particular
 * type.
 *
 * @param symbol The symbol to search for.
 * @param type The type of the symbol to search for.
 *
 * @return The location of the symbol or -1 if the search
 *         failed.
 *
 * @note Uses the linear search algorithm.
 */
int scc::search_symbol_table(int symbol, char type) const {
    for (int i = 0; i < next_symbol_table_idx; i++)
    {
        if (symbol == symbol_table[i].symbol && type ==
            symbol_table[i].type)
            return i;
    }

    return -1;
}

/**
 * Generates code for a "input" instruction.
 *
 * @param ss Input string stream from which to read.
 */
void scc::handle_input(istringstream& ss) {
    string token;

    ss >> token;

    int location = get_symbol_location(token);

    memory_check();
    memory[next_instruction_addr] = READ * 100 + location;
    next_instruction_addr++;
}

/**
 * Generates code for a "data" instruction.
 *
 * @param ss Input string stream from which to read.
 */
void scc::handle_data(istringstream& ss) {
    int number;

	ss >> number;

	if (ndata == MEMORY_SIZE - 1)
    {
        cout << "*** ERROR: too many data lines ***\n";
        exit(1);
    }
    data_check();
    data[ndata] = number;
    ndata++;
}

/**
 * Generates code for a "let" instruction.
 *
 * @param ss Input string stream from which to read.
 */
void scc::handle_let(istringstream& ss, string buffer2){
	string left_var;
	int location_left;

	ss >> left_var;
	location_left = get_symbol_location(left_var);

	size_t sub = buffer2.find_first_of("=");
	string infix = buffer2.substr(sub + 2);
	string postfix = convert( infix );

	istringstream ss_post(postfix);

	int next_stack_idx = 0;
	string eval;
	while(ss_post >> eval){
		if(islower(eval[0]) || isdigit(eval[0])){
			int loc = get_symbol_location(eval);
			memory_check();

			memory[next_instruction_addr] = LOAD * 100 + loc;
			next_instruction_addr++;

			memory_check();
			memory[next_instruction_addr] = STORE * 100;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;
			next_stack_idx++;
		}

		if (eval == "+") {
			memory[next_instruction_addr] = LOAD * 100;     // omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;

			memory[next_instruction_addr] = ADD * 100;      // for addition, omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;

			memory[next_instruction_addr] = STORE * 100;    // omit address
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_stack_idx++;
			next_instruction_addr++;
		} else if (eval == "*") {
			memory[next_instruction_addr] = LOAD * 100;     // omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;

			memory[next_instruction_addr] = MULTIPLY * 100;      // for addition, omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;

			memory[next_instruction_addr] = STORE * 100;    // omit address
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_stack_idx++;
			next_instruction_addr++;
		} else if (eval == "-") {
			memory[next_instruction_addr] = LOAD * 100;        // omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = STORE * 100;       // omit address
			flags[next_instruction_addr] = -2;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = LOAD * 100;        // omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = SUBTRACT * 100;    // for subtraction, omit address
			flags[next_instruction_addr] = -2;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = STORE * 100;       // omit address
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_stack_idx++;
			next_instruction_addr++;
		} else if (eval == "/") {
			memory[next_instruction_addr] = LOAD * 100;        // omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = STORE * 100;       // omit address
			flags[next_instruction_addr] = -2;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = LOAD * 100;        // omit address
			next_stack_idx--;
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = DIVIDE * 100;    // for subtraction, omit address
			flags[next_instruction_addr] = -2;
			next_instruction_addr++;
			
			memory[next_instruction_addr] = STORE * 100;       // omit address
			flags[next_instruction_addr] = -3 - next_stack_idx;
			next_stack_idx++;
			next_instruction_addr++;
		}
	}
	

	memory[next_instruction_addr] = LOAD * 100;
	flags[next_instruction_addr] = -3;
	next_instruction_addr++;

	memory[next_instruction_addr] = STORE * 100 + location_left;
	next_instruction_addr++;
}

/**
 * Generates code for a "goto" instruction.
 *
 * @param ss Input string stream from which to read.
 */
void scc::handle_goto(istringstream& ss) {
	memory_check();

    int token;
    ss >> token;

	int location = search_symbol_table(token, 'L');

	if(location == -1) {
		memory[next_instruction_addr] = BRANCH * 100;
		flags[next_instruction_addr] = token;
		next_instruction_addr++;
	} else {
    	memory[next_instruction_addr] = BRANCH * 100 + symbol_table[location].location;
		next_instruction_addr++;
	}
}

/**
 * Generates code for a "if" instruction.
 *
 * @param ss Input string stream from which to read.
 */
void scc::handle_if(istringstream& ss){
	string left_operand, 
		 relation, 
		 right_operand, 
		 the_goto;

	int line_number, 
	   buffer,
	   location_left,
	   location_right;
	
	ss >> left_operand;
	location_left = get_symbol_location(left_operand);

	ss >> relation;

	ss >> right_operand;
	location_right = get_symbol_location(right_operand);

	ss >> the_goto;
	ss >> line_number;

	buffer = search_symbol_table(line_number, 'L');
	
	memory_check();
	memory[next_instruction_addr] = LOAD * 100;
    next_instruction_addr++;

	memory_check();
	memory[next_instruction_addr] = SUBTRACT * 100;
    next_instruction_addr++;

	memory_check();
	if (relation == "!=") {
		memory[next_instruction_addr] = BRANCHZERO * 100 + next_instruction_addr + 2;
		next_instruction_addr++;
	} else if (relation != "!="){
		if (buffer == -1){
			memory[next_instruction_addr] = 0;
			flags[next_instruction_addr] = line_number;
			next_instruction_addr++;
		} else {
			memory[next_instruction_addr] = symbol_table[buffer].location;
			next_instruction_addr++;
		}
	}
	
	if (relation == "<") {
		memory[next_instruction_addr - 3] += location_left;
		memory[next_instruction_addr - 2] += location_right;
		memory[next_instruction_addr - 1] += BRANCHNEG * 100;
	}
	
	if (relation == "<=") {
		memory[next_instruction_addr - 3] += location_left;
		memory[next_instruction_addr - 2] += location_right;
		memory[next_instruction_addr - 1] += BRANCHNEG * 100;
		
		memory_check();

		if(buffer == -1){
			memory[next_instruction_addr] = BRANCHZERO * 100;
			flags[next_instruction_addr] = line_number;
			next_instruction_addr++;
		} else {
			memory[next_instruction_addr] = BRANCHZERO * 100 + symbol_table[buffer].location;
			next_instruction_addr++;
		}
	}

	if (relation == ">") {
		memory[next_instruction_addr - 3] += location_right;
		memory[next_instruction_addr - 2] += location_left;
		memory[next_instruction_addr - 1] += BRANCHNEG * 100;
	}
	
	if (relation == ">=") {
		memory[next_instruction_addr - 3] += location_right;
		memory[next_instruction_addr - 2] += location_left;
		memory[next_instruction_addr - 1] += BRANCHNEG * 100;
		
		memory_check();

		if(buffer == -1){
			memory[next_instruction_addr] = BRANCHZERO * 100;
			flags[next_instruction_addr] = line_number;
			next_instruction_addr++;
		} else {
			memory[next_instruction_addr] = BRANCHZERO * 100 + symbol_table[buffer].location;
			next_instruction_addr++;
		}
	}
	
	if (relation == "==") {
		memory[next_instruction_addr - 3] += location_left;
		memory[next_instruction_addr - 2] += location_right;
		memory[next_instruction_addr - 1] += BRANCHZERO * 100;

	}
	
	if (relation == "!=") {
		memory[next_instruction_addr - 3] += location_left;
		memory[next_instruction_addr - 2] += location_right;
		memory_check();

		if(buffer == -1){
			memory[next_instruction_addr] = BRANCH * 100;
			flags[next_instruction_addr] = line_number;
			next_instruction_addr++;
		} else {
			memory[next_instruction_addr] = BRANCH * 100 + symbol_table[buffer].location;
			next_instruction_addr++;
		}
	}
}

/**
 * Generates code for a "print" instruction.
 *
 * @param ss Input string stream from which to read.
 */
void scc::handle_print(istringstream& ss) {
    string token;

    ss >> token;

    int location = get_symbol_location(token);

    memory_check();
    memory[next_instruction_addr] = WRITE * 100 + location;
    next_instruction_addr++;
}

/**
 * Generates code for an "end" instruction.
 */
void scc::handle_end() {
    memory_check();
    memory[next_instruction_addr] = HALT * 100;
    next_instruction_addr++;
}
