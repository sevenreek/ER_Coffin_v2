#include "BoardCoordinator.h"
BoardCoordinator::BoardCoordinator(WirelessController * wireless, GPIOController * gpio)
{
	opened = true;
	this->wireless = wireless;
	this->gpio = gpio;
}
void BoardCoordinator::onUpdate()
{
	Message * msg = 0;
	if (!opened && wireless->hasMessage(msg))
	{

		Serial.print("Then pointer is:");
		Serial.println((int)msg);
		Serial.print(msg->sender);Serial.print(" = ");Serial.println(SNDR_MEGA);
		Serial.print(msg->command);;Serial.print(" = ");Serial.println(CMD_COFFIN_UNLOCKED);
		if (msg->sender == SNDR_MEGA && msg->command==CMD_COFFIN_UNLOCKED)
		{
			Serial.println("Unlocking coffin...");
			gpio->coffinTop.open();
			opened = true;
		}
		delete msg;
	}
	if (opened)
	{
		if (gpio->skeleton.getCorrectCount() == 5)
		{
			Serial.println("Finished skeleton");
			Message * m = new Message(SNDR_COFFIN, MTYPE_STATE, CMD_COFFIN_COMPLETED, 0);
			wireless->sendMessage(m,WirelessController::REPEAT_COUNT);
			delete m;
		}
	}
}
