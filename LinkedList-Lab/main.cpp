#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "LinkedList.h"

const int NUM_FILES = 5; // the total number of files to be read from

const std::string fileArray[NUM_FILES] = { "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt" }; // the string aray containing the file names

 // This will take a string temp and a LinkedList object and will execute an instruction from the string
 // no return, but writes the results of the instruction into the ofs filestream
template <typename T>
void parse_instruction(std::string temp, std::ofstream &ofs, LinkedList<T>* aptr);

// This function is a platform independent way of reading files of various line ending types.
// It's definiton is at the bottom of the file, don't worry if you don't understand it.
namespace ta {
	std::istream& getline(std::istream& is, std::string& line);
}

// to determine the type of LL that will be used
//0 means LL of ints, 1 means LL of strings
//no other data types will be used
bool isString;

int main() {

	std::ifstream ifs; // create the stream to read in from the files
	std::ofstream ofs; // create the output stream to write to an output file
	std::string temp; // used to store the current instruction
	LinkedList<int>* iLL = NULL;//the integer linked list
	LinkedList<string>* sLL = NULL;//the string linked list

	for (int i = 0; i < NUM_FILES; i++) {
		ifs.open(fileArray[i]); // open the file to read from
		ofs.open("out_" + fileArray[i]); // open the file to write to

		if (!ifs.is_open()) { // if the file did not open, there was no such file
			std::cout << "File " << i + 1 << " could not open, please check your lab setup" << std::endl;
		}
		else {
			std::cout << "Reading file" << i + 1 << ".txt..." << std::endl;
		}

		ta::getline(ifs, temp); // get the first instruction
		if (temp == "STRING") { // first line of file determines the type of the linked list, either string or int
			isString = true;//set the isString to true
			sLL = new LinkedList<string>();
			std::cout << "'isString' flag set to true" << std::endl;
			std::cout << "The LinkedList for file " << i + 1 << " will contain strings" << std::endl;
		}
		else { //the LL will hold ints
			isString = false;
			iLL = new LinkedList<int>();
			std::cout << "'isString' flag set to false" << std::endl;
			std::cout << "The LinkedList for file " << i + 1 << " will contain ints" << std::endl;
		}

		std::cout << "Beginning out_file" << i + 1 << ".txt write" << std::endl;
		while (ta::getline(ifs, temp)) { // while there are more instructions to get,
			try {
				if (isString) {
					parse_instruction(temp, ofs, sLL); // parse the instructions using string LinkedList
				}
				else {
					parse_instruction(temp, ofs, iLL); // parse the instructions using int LinkedList
				}
			}
			catch (...) {
				std::cout << "An exception was thrown that shouldn't have been.\n";
				//return 0;//end the program
			}
		}
		std::cout << "File write complete" << std::endl << std::endl;
		if (iLL != NULL) {
			delete iLL;
			iLL = NULL;
		}
		if (sLL != NULL) {
			delete sLL;
			sLL = NULL;
		}
		ifs.close();
		ofs.close();
	}
	std::cout << "end" << std::endl; // indicate that the program has successfuly executed all instructions
	return 0;
}

template <typename T>
void parse_instruction(std::string temp, std::ofstream &ofs, LinkedList<T>* LLptr) {
	std::string command, listString;
	T val, insertionNode;
	int index, size;
	std::stringstream ss(temp);
	if (!(ss >> command)) { return; } // get command, but if string was empty, return
	if (command == "insertHead") { // command to add a new node as a head node
		ss >> val;
		LLptr->insertHead(val);//add the node to the list
		ofs << temp << std::endl;
	}
	else if (command == "insertTail") { // command to remove a fighter from the arena (given the fighters name)
		ss >> val;//grab the value
		LLptr->insertTail(val);//add the node to the list
		ofs << temp << std::endl;
	}
	else if (command == "insertAfter") { // command to return a pointer to a fighter (given the name of the fighter)
		ss >> val >> insertionNode; // get the value to add and the node to add after
		LLptr->insertAfter(val, insertionNode);//add the node to the list
		ofs << temp << std::endl;
	}
	else if (command == "remove") { // command to get the number of fighters in the arena
		ss >> val; // get the value to remove
		LLptr->remove(val);//remove the node from the list
		ofs << temp << std::endl;
	}
	else if (command == "clear") {
		LLptr->clear();//clear the list
		ofs << temp << std::endl;
	}
	else if (command == "at") { // command to print the results of a battle between two fighters
		ss >> index;//get the index to view
		try {
			T nodeVal = LLptr->at(index);
			ofs << temp << " " << nodeVal << std::endl;
		}
		catch (std::out_of_range) {// if an out_of_range exception was thrown, catch it!
			ofs << temp << " out_of_range" << std::endl;
		}
	}
	else if (command == "size") {
		size = LLptr->size();//get the size of the list
		ofs << temp << " " << size << std::endl;
	}
	else if (command == "printList") {
		listString = LLptr->toString();//print the list
		ofs << temp << std::endl << "  " << listString << std::endl;
	}
	else { // invalid command, wrong input file format
		std::cout << "Command: \"" << command << "\"" << std::endl;
		std::cout << "Invalid command.  Do you have the correct input file?" << std::endl;
	}
}

// Version of getline which does not preserve end of line characters
namespace ta {
	std::istream& getline(std::istream& in, std::string& line) {
		line.clear();

		std::istream::sentry guard(in, true); // Use a sentry to maintain the state of the stream
		std::streambuf *buffer = in.rdbuf();  // Use the stream's internal buffer directly to read characters
		int c = 0;

		while (true) { // Continue to loop until a line break if found (or end of file)
			c = buffer->sbumpc(); // Read one character
			switch (c) {
			case '\n': // Unix style, return stream for further parsing
				return in;
			case '\r': // Dos style, check for the following '\n' and advance buffer if needed
				if (buffer->sgetc() == '\n') { buffer->sbumpc(); }
				return in;
			case EOF:  // End of File, make sure that the stream gets flagged as empty
				in.setstate(std::ios::eofbit);
				return in;
			default:   // Non-linebreak character, go ahead and append the character to the line
				line.append(1, (char)c);
			}
		}
	}
}