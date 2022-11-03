#ifndef LED_COMMAND_HPP_
#define LED_COMMAND_HPP_

#include "tap/control/command.hpp"
#include "drivers.hpp"
#include "controls/standard/control_interface.hpp"
#include "led_subsystem.hpp"

class LedCommand : public tap::control::Command{
public:
    LedCommand(src::Drivers *  drivers);

    ~LedCommand() = default;

    const char *getName() const;

    //this is called when the Command starts
    void initialize() override;

    //this is called continously as long as the Command is running
    void execute() override;

    //this is called when the subsystem ends
    void end(bool) override;

    bool isFinished() const override;



private:
    src::Drivers* drivers;
}; //LedCommand

#endif