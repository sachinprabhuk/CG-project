#include "../headers/utils.h"

int randomRange(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}
