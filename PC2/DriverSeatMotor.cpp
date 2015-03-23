#include "DriverSeatMotor.h"

namespace mxnavi {

DriverSeatMotor::DriverSeatMotor(void)
{
	serial_command.data[4] = 0x23;
	part_name = "driver-seat-motor";
}


DriverSeatMotor::~DriverSeatMotor(void)
{
}

}