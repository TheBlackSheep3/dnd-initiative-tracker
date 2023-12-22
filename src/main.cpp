#include <iostream>

#include "cmake_variables.hpp"

int main(int argc, char * argv[])
{
	std::cout << argv[0] << " version " << VERSION << std::endl;
	return 0;
}
