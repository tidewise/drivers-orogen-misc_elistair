/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

#include <iodrivers_base/ConfigureGuard.hpp>
#include <misc_elistair/Driver.hpp>

using namespace misc_elistair;
using namespace std;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    unique_ptr<Driver> driver(new Driver());
    // Un-configure the device driver if the configure fails.
    // You MUST call guard.commit() once the driver is fully
    // functional (usually before the configureHook's "return true;"
    iodrivers_base::ConfigureGuard guard(this);
    if (!_io_port.get().empty())
        driver->openURI(_io_port.get());
    setDriver(driver.get());

    // This is MANDATORY and MUST be called after the setDriver but before you do
    // anything with the driver
    if (!TaskBase::configureHook())
        return false;

    // If some device configuration was needed, it must be done after the
    // setDriver and call to configureHook on TaskBase (i.e., here)

    m_driver = move(driver);
    guard.commit();
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::processIO() {
}
void Task::updateHook()
{
    TaskBase::updateHook();

    Command cmd;
    if (_cmd.read(cmd) != RTT::NoData) {
        m_driver->sendCommand(
            cmd.power_mode,
            cmd.torque_mode,
            cmd.torque
        );
        Status status = m_driver->read();
        _status.write(status);
    }
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
