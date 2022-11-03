#include "led_command.hpp"

LedCommand::LedCommand(src::Drivers *drivers) : drivers(drivers) {}

const char *LedCommand::getName() const { return "ledCommand"; }

void LedCommand::initialize() {}

void LedCommand::execute() {
    float rightX = drivers->control_interface.chassisXInput();
    float rightY = drivers->control_interface.chassisYInput();

    bool turnLEDOn = rightX != 0 || rightY != 0;
    drivers->leds.set(drivers->leds.Green, turnLEDOn);
}

void LedCommand::end(bool) {}

bool LedCommand::isFinished() const { return false; }
