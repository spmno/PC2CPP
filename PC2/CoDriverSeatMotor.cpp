#include "CoDriverSeatMotor.h"

namespace mxnavi {

CoDriverSeatMotor::CoDriverSeatMotor(void)
{
	serial_command.data[4] = 0x28;
	part_name = "co-driver-seat-motor";
}


CoDriverSeatMotor::~CoDriverSeatMotor(void)
{
}

}