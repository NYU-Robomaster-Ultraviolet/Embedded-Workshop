#ifndef GIMBAL_SUBSYSTEM_HPP_
#define GIMBAL_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "modm/math/filter/pid.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"
#include "controls/standard/standard_constants.hpp"
#include "tap/util_macros.hpp"
#include "tap/algorithms/math_user_utils.hpp"
#include "drivers.hpp"

using namespace tap::algorithms;

namespace gimbal{
class GimbalSubsystem : public tap::control::Subsystem
{
public:
    GimbalSubsystem(tap::Drivers *drivers)
    : tap::control::Subsystem(drivers), 
    yawMotor(drivers,
               tap::motor::MOTOR5,
               tap::can::CanBus::CAN_BUS2,
               false,
               "Yaw Motor"),
      pitchMotor(drivers,
                 tap::motor::MOTOR6,
                 tap::can::CanBus::CAN_BUS2,
                 false,
                 "Pitch Motor"),
      targetYaw(0.0f),
      targetPitch(0.0f),
      currentYawMotorSpeed(0.0f),
      currentPitchMotorSpeed(0.0f),
      lastPitchMotorOutput(0.0f),
      yawPid(gimbalPid.YAW_GYRO_ABSOLUTE_PID_KP, gimbalPid.YAW_GYRO_ABSOLUTE_PID_KI, gimbalPid.YAW_GYRO_ABSOLUTE_PID_KD, 
      gimbalPid.YAW_GYRO_ABSOLUTE_PID_MAX_IOUT, gimbalPid.YAW_GYRO_ABSOLUTE_PID_MAX_OUT),
      pitchPid(gimbalPid.PITCH_GYRO_ABSOLUTE_PID_KP, gimbalPid.PITCH_GYRO_ABSOLUTE_PID_KI, gimbalPid.PITCH_GYRO_ABSOLUTE_PID_KD, 
      gimbalPid.PITCH_GYRO_ABSOLUTE_PID_MAX_IOUT, gimbalPid.PITCH_GYRO_ABSOLUTE_PID_MAX_OUT),
      yawSpeedPid(gimbalPid.YAW_SPEED_PID_KP, gimbalPid.YAW_SPEED_PID_KI, gimbalPid.YAW_SPEED_PID_KD,
      gimbalPid.YAW_SPEED_PID_MAX_IOUT, gimbalPid.YAW_SPEED_PID_MAX_OUT),
      pitchSpeedPid(gimbalPid.PITCH_SPEED_PID_KP, gimbalPid.PITCH_SPEED_PID_KI, gimbalPid.PITCH_SPEED_PID_KD,
      gimbalPid.PITCH_SPEED_PID_MAX_IOUT, gimbalPid.PITCH_SPEED_PID_MAX_OUT)
      {}

    void initialize() override;
    void refresh() override;

    const char* getName() override {return "gimbal subsystem";}

    void setYawOutput(float output);
    void setPitchOutput(float output);

    static inline float wrappedEncoderValueToRadians(int64_t encoderValue);

    void setYawAngle(float angle) { targetYaw = angle; }
    void setPitchAngle(float angle) {targetPitch = limitVal<float>(angle, constants.PITCH_MIN_ANGLE, constants.PITCH_MAX_ANGLE);}

    float getYawMotorRPM() const {return yawMotor.isMotorOnline() ? yawMotor.getShaftRPM() : 0.0f; }
    float getPitchMotorRPM() const {return pitchMotor.isMotorOnline() ? pitchMotor.getShaftRPM() : 0.0f; }

    //value in degrees, Yaw = Pitch and Pitch = Roll cause taproot
    float getYaw() const {return drivers->bmi088.getPitch();}
    float getPitch() const {return drivers->bmi088.getRoll();}

    //these methods will update both PID calculators and set motor speeds
    void updateYawPid();
    void updatePitchPid();

    /*these methods cover the three posibilities of gimbal position:
    either controller inputs, CV inputs, or no inputs*/
    void controllerInput(float yawInput, float pitchInput);
    void cvInput(float yawInput, float pitchInput);
    void noInputs();

    //this methods will take into consideration the current pitch of the gimbal and return a float value that will lock it in place
    float stabalizePitch();

private:
    tap::motor::DjiMotor yawMotor;
    tap::motor::DjiMotor pitchMotor;

    //starting angle
    float startingPitch;
    //target angle, given in a value between -1 and 1
    float targetYaw;
    float targetPitch;
    //motor speed given in revolutions / min
    float currentYawMotorSpeed;
    float currentPitchMotorSpeed;
    float lastPitchMotorOutput;

    modm::Pid<float> yawPid;
    modm::Pid<float> pitchPid; //angle

    modm::Pid<float> yawSpeedPid;
    modm::Pid<float> pitchSpeedPid;

    //current angles in radians
    float currentYaw;
    float currentPitch;

    //desired error angles
    float yawError;
    float pitchError;

    //desired output values for motors in current
    float yawMotorOutput;
    float pitchMotorOutput;
    //PID constancts
    GIMBAL_PID gimbalPid;
    //all other gimbal constants
    GIMBAL_CONSTANTS constants;
    //Gimbal PID output to motor speed error factor
    float motorSpeedFactor;

    bool inputsFound = false;
}; //class GimbalSubsystem
}//namespace gimbal


#endif