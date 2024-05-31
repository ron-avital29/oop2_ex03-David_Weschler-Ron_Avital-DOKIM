#include "Menu.h"
#include <iostream>

int main() try{

	Menu menu;
	menu.run();
	return EXIT_SUCCESS;
}
catch (std::exception& e) {
	std::cerr<<e.what();
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "UNKNOWN ERROR!\n";
	return EXIT_FAILURE;
}