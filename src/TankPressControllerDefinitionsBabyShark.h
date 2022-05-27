#ifndef TANKPRESSCONTROLLERDEFINITIONSBABYSHARK_H
#define TANKPRESSCONTROLLERDEFINITIONSBABYSHARK_H

#include "TankPressControllerClass.h"
#include <array>
#include "pinList.h"


#define NUM_TANKPRESSCONTROLLERS 3

TankPressController HiPressTankController{3, 9, 10, 999, 5000};      //999 is to fake the vent for now
TankPressController LoxTankController{3, 6, 7, 4, 900};
TankPressController FuelTankController{3, 8, 9, 3, 900};

//
std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS> tankPressControllerArray{&HiPressTankController, &LoxTankController, &FuelTankController};

#endif