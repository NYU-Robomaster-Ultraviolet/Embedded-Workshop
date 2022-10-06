#ifndef CHASSIS_MOVEMENT_COMMAND_HPP_
#define CHASSIS_MOVEMENT_COMMAND_HPP_

#include "tap/control/command.hpp"

#include "chassis_subsystem.hpp"
#include "drivers.hpp"
namespace chassis{

class ChassisMovementCommand : public tap::control::Command{
public:
    /**
     * Initializes the command with the passed in ChassisSubsystem.  Must not
     * be nullptr.
     *
     * @param[in] chassis a pointer to the chassis to be passed in that this
     *      Command will interact with.
     */
    ChassisMovementCommand(ChassisSubsystem *const chassis, src::Drivers *drivers);

    ChassisMovementCommand(const ChassisMovementCommand &other) = delete;

    ChassisMovementCommand &operator=(const ChassisMovementCommand &other) = delete;

    void initialize() override;

    const char *getName() const { return "chassis drive command"; }

    void execute() override;

    void end(bool) override;

    bool isFinished() const override;
private:
    ChassisSubsystem *const chassis;

    src::Drivers *drivers;
}; //class ChassisMovementCommand : public tap::control::Command
} //namespace Chassis
#endif //CHASSIS_MOVEMENT_COMMAND_HPP_ 