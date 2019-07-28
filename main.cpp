#include <iostream>
#include <string>
#include "inc/System.h"

using SystemCalls::System;
using std::string;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	string s = System::getFile("main.cpp");
	printf("print:\n %s", s.c_str());
	
	return 0;
}
