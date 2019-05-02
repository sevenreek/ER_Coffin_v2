#include "BoardCoordinator.h"
BoardCoordinator::BoardCoordinator(WirelessController * wireless, GPIOController * gpio)
{

	this->wireless = wireless;
	this->gpio = gpio;
}
void BoardCoordinator::onUpdate()
{
	Message * msg = 0;
	if (wireless->hasMessage(msg))
	{
		if (msg->sender == SNDR_MEGA && msg->command==CMD_COFFIN_UNLOCKED)
		{
			gpio->coffinTop.open();
			opened = true;
		}
		delete msg;
	}
	if (opened)
	{
		if (gpio->skeleton.getCorrectCount() == 5)
		{
			Message * m = new Message(SNDR_COFFIN, MTYPE_STATE, CMD_COFFIN_COMPLETED, 0);
			wireless->sendMessage(m,WirelessController::REPEAT_COUNT);
			delete m;
		}
	}
}
