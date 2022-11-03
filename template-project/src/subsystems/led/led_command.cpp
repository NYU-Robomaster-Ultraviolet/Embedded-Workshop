#include "led_command.hpp"

LedCommand::LedCommand(src::Drivers * drivers) : drivers(drivers) {}

const char *LedCommand::getName() const {return "ledCommand";}

void LedCommand::initialize(){}

void LedCommand::execute(){
    float x = drivers->control_interface.getChassisXInput();
    float y = drivers->control_interface.getChassisYInput();

    drivers->leds.set(drivers->leds.Green, x != 0 || y != 0);
}

void LedCommand::end(bool){}

bool LedCommand::isFinished() const {return false;}

