#ifndef ENGINECONTROLLERDEFINITIONSBABYSHARK_H
#define ENGINECONTROLLERDEFINITIONSBABYSHARK_H

#include "EngineControllerClass.h"
#include <array>
#include "ALARApinDefines.h"

#define NUM_ENGINECONTROLLERS 1

EngineController Engine1{1, 2};

//
std::array<EngineController*, NUM_ENGINECONTROLLERS> engineControllerArray{&Engine1};

#endif