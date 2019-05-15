#include <string>
#include <iostream>
#include <algorithm>


int main() {
	std::string string_in;

	std::cout << "Enter a word: " << string_in << std::endl;
	std::cin >> string_in;
	
	std::string string_out = string_in;
	std::reverse(string_in.begin(), string_in.end());
	
	std::cout << "Reversed string is: " << string_in << std::endl;

	if (string_in == string_out) {
		std::cout << string_in << " is palindrome." << std::endl;
	}
	else {
		std::cout << string_in << " is not palindrome." << std::endl;
	}

	return 0;
}