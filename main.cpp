#include "Company.h"
using namespace std;

int main()
{
	Company* C = new Company;
	C->simulate();

	delete C;
	return 0;
}