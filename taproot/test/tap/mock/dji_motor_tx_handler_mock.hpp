/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TAPROOT_DJI_MOTOR_TX_HANDLER_MOCK_HPP_
#define TAPROOT_DJI_MOTOR_TX_HANDLER_MOCK_HPP_

#include <gmock/gmock.h>

#include "tap/motor/dji_motor_tx_handler.hpp"

#include "modm/architecture/interface/can_message.hpp"

namespace tap
{
namespace mock
{
class DjiMotorTxHandlerMock : public tap::motor::DjiMotorTxHandler
{
public:
    DjiMotorTxHandlerMock(tap::Drivers *drivers);
    virtual ~DjiMotorTxHandlerMock();

    MOCK_METHOD(void, addMotorToManager, (tap::motor::DjiMotor * motor), (override));
    MOCK_METHOD(void, encodeAndSendCanData, (), (override));
    MOCK_METHOD(void, removeFromMotorManager, (const tap::motor::DjiMotor &motor), (override));
    MOCK_METHOD(
        const tap::motor::DjiMotor *,
        getCan1Motor,
        (tap::motor::MotorId motorId),
        (override));
    MOCK_METHOD(
        const tap::motor::DjiMotor *,
        getCan2Motor,
        (tap::motor::MotorId motorId),
        (override));
};  // class DjiMotorTxHandlerMock
}  // namespace mock
}  // namespace tap

#endif  //  TAPROOT_DJI_MOTOR_TX_HANDLER_MOCK_HPP_