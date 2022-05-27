#ifndef TANKPRESSCONTROLLERDEFINITIONSRENEGADESF_H
#define TANKPRESSCONTROLLERDEFINITIONSRENEGADESF_H

#include "TankPressControllerClass.h"
#include <array>
#include "pinList.h"


#define NUM_TANKPRESSCONTROLLERS 3

TankPressController HiPressTankController{2, 0, 1, 999, 5000};
TankPressController LoxTankController{3, 5, 6, 4, 900};
TankPressController FuelTankController{3, 8, 9, 7, 900};

//
std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS> tankPressControllerArray{&HiPressTankController, &LoxTankController, &FuelTankController};

#endif