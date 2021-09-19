#include "_freecplus.h"

int main(int argc, char *argv[])
{
    int a = 4;
    int b = 1;
    printf("factor == %lld\n", maxCommonFactor(a, b));
    printf("multiple == %lld\n", minCommonMultiple(a, b));

	return 0;
}
