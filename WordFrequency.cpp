//Rishi Govindan
//rigovind
//pa8

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
        	std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        	return(1);
    	}

	std::ifstream in(argv[1]);
    	if (!in.is_open()) {
        	std::cerr << "Unable to open file " << argv[1] << " for reading\n";
        	return(1);
    	}

	std::ofstream out(argv[2]);
    	if (!out.is_open()) {
        	std::cerr << "Unable to open file " << argv[2] << " for writing\n";
        	return(1);
    	}


	Dictionary Dict;
    	std::string L, T;
    	std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";


	while (getline(in, L)) {
        	size_t begin, end, len = L.length();
        	begin = L.find_first_not_of(delim, 0);

		while (begin < len) {
            		end = L.find_first_of(delim, begin);
            		T = L.substr(begin, end - begin);

			for (char& ch : T) {
                		ch = std::tolower(ch);
            		}

			if (!T.empty()) {
                		Dict.contains(T) ? Dict.setValue(T, Dict.getValue(T) + 1) : Dict.setValue(T, 1);
            		}


			begin = L.find_first_not_of(delim, end);
		}
	}
	out << Dict;
	in.close();
    	out.close();
	return(0);
}
