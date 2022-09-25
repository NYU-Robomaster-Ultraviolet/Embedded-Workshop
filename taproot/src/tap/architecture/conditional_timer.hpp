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

#ifndef TAPROOT_CONDITIONAL_TIMER_HPP_
#define TAPROOT_CONDITIONAL_TIMER_HPP_

#include <cstdint>

#include "timeout.hpp"

namespace tap
{
namespace arch
{
/**
 * A timeout that will only run while the given `Check` functor is true.
 * Resets the timer if the condition is checked and returns false.
 *
 * @param Time: A timeout object that implements the interface described in
 *        `timeout.hpp`
 */
template <class Timeout>
class ConditionalTimer
{
public:
    /**
     * @param[in] timeout: the timeout for this timer to use
     */
    explicit ConditionalTimer(uint32_t timeout) : timeout(timeout) {}

    /**
     * Set the timer to expire `this->timeout` units of time away from the time at
     * which this function was called.
     */
    inline void restart() { timer.restart(timeout); }

    /**
     * Similar to `restart()` but redefine the period of the timer.
     *
     * @param[in] period: the new period to use for this `PeriodicTimer`
     */
    inline void restart(uint32_t newTimeout)
    {
        timeout = newTimeout;
        timer.restart(newTimeout);
    }

    /**
     * Stop the timer.
     */
    inline void stop() { timer.stop(); }

    /**
     * Returns `true` if the `condition` is true and the timer has expired
     * If the `condition` parameter is false then the timer is reset and this function
     * returns `false`
     *
     * @param[in] condition: the condition for whether or not the timer should run. If
     *      `false` then the timer is reset.
     * @return `true` if the timer has expired (timeout has been reached) since last `restart()`
     */
    inline bool execute(bool condition)
    {
        if (!condition)
        {
            timer.restart(timeout);
        }
        return timer.isExpired();
    }

    inline bool isStopped() { return timer.isStopped(); }

private:
    Timeout timer;
    uint32_t timeout;
};

using ConditionalMilliTimer = ConditionalTimer<MilliTimeout>;

}  // namespace arch

}  // namespace tap

#endif
