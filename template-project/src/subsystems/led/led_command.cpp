#include "led_command.hpp"

LedCommand::LedCommand(tap::Drivers * drivers) : drivers(drivers) {}

void LedCommand::initialize(){}

void LedCommand::execute(){}

void LedCommand::end(bool){}

bool LedCommand::isFinished() const {return false;}