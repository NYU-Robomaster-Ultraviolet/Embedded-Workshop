#ifndef LED_SUBSYSTEM_HPP_
#define LED_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "drivers.hpp"

class LedSubsystem : public tap::control::Subsystem{
public:
LedSubsystem(src::Drivers* drivers) : Subsystem(drivers) {}

private:
}; //class LedSubsystem

#endif