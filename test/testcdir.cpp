#include "_freecplus.h"

int main(int argc, char *argv[])
{
	std::string currentPath = CDir::GetCurrentDir();
	std::cout << currentPath << '\n';

	return 0;
}
