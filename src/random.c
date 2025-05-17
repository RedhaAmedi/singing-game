#include "esp_system.h"


int getRandomRange(int min, int max)
{

	return (esp_random() % (max- min) ) +min;
}
