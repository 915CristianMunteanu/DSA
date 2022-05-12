#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "IteratedList.h"
#include <exception>
int main() {
	testAll();
	testAllExtended();
	std::cout << "Finished LP Tests!" << std::endl;
	system("pause");
}
