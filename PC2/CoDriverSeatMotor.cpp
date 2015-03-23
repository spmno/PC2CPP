#include "CoDriverSeatMotor.h"

namespace mxnavi {

CoDriverSeatMotor::CoDriverSeatMotor(void)
{
	serial_command.data[3] = 0x28;
	part_name = "co-driver-seat-motor";
}


CoDriverSeatMotor::~CoDriverSeatMotor(void)
{
}

}