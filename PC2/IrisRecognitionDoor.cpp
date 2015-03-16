#include "IrisRecognitionDoor.h"

namespace mxnavi {

IrisRecognitionDoor::IrisRecognitionDoor(void)
{
	serial_command.data[4] = 0x31;
	part_name = "iris-recognition-door";
}


IrisRecognitionDoor::~IrisRecognitionDoor(void)
{

}

}