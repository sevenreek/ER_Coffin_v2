#include "BoardCoordinator.h"
const unsigned int BoardCoordinator::PARTIAL_UNLOCK_TIME = 25000; // ms
BoardCoordinator::BoardCoordinator(WirelessController * wireless, GPIOController * gpio)
{
	state = LOCKED;
	this->wireless = wireless;
	this->gpio = gpio;
	unlockTimer = 0;
}
void BoardCoordinator::finishPuzzle()
{
	unlockTimer = 0;
	Serial.println("Finished skeleton");
	Message* m = new Message(SNDR_COFFIN, MTYPE_STATE, CMD_COFFIN_COMPLETED, 0);
	wireless->sendMessage(m, WirelessController::REPEAT_COUNT);
	delete m;
	state = DONE;
}
void BoardCoordinator::onUpdate()
{
	Message * msg = 0;
	if (wireless->hasMessage(msg))
	{
		if (msg->sender == SNDR_MEGA && msg->command==CMD_COFFIN_UNLOCKED && state!=OPENED)
		{
			gpio->coffinTop.open();
			state = OPENED;	
		}
		delete msg;
}
	lastUpdate = millis();
	if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT)
	{
		if(state!=DONE) finishPuzzle();
	}
	else if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT-1 && lastUpdate != millis())
	{
		//Serial.println("add:");
		//Serial.println((millis() - lastUpdate));
		unlockTimer = unlockTimer + (millis() - lastUpdate);
	
		Serial.println(unlockTimer);
		if (unlockTimer >= PARTIAL_UNLOCK_TIME)
			if (state != DONE)
				finishPuzzle();
	}
	delay(1);
}
