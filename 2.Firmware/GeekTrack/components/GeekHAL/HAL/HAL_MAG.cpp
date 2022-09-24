#include "HAL.h"
#include <stdlib.h>


uint8_t MAG_Init()
{
    return 0;
}

void MAG_Update()
{
    MAG_Info_t mag;
    mag.x = rand() % 1000 - 500;
    mag.y = rand() % 1000 - 500;
    mag.z = rand() % 1000 - 500;

}
