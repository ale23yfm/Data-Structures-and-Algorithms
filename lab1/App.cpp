#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>


using namespace std;

int main() {
	testAll();
	testAllExtended();

	//int* leak = new int[100];
	//_CrtDumpMemoryLeaks(); 

	cout << "Test end" << endl;
	system("pause");
}