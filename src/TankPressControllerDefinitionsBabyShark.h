#ifndef TANKPRESSCONTROLLERDEFINITIONSBABYSHARK_H
#define TANKPRESSCONTROLLERDEFINITIONSBABYSHARK_H

#include "TankPressControllerClass.h"
#include <array>
#include "pinList.h"


#define NUM_TANKPRESSCONTROLLERS 3

TankPressController HiPressTankController{1, 3, 5000};
TankPressController LoxTankController{2, 3, 900};
TankPressController FuelTankController{3, 3, 900};

//
std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS> tankPressControllerArray{&HiPressTankController, &LoxTankController, &FuelTankController};

#endif