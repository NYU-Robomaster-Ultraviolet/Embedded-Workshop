#include "led_command.hpp"

LedCommand::LedCommand(src::Drivers * drivers) : drivers(drivers) {}

const char *LedCommand::getName() const {return "ledCommand";}

void LedCommand::initialize(){}

void LedCommand::execute(){}

void LedCommand::end(bool){}

bool LedCommand::isFinished() const {return false;}