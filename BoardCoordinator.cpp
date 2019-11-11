#include "BoardCoordinator.h"
const unsigned int BoardCoordinator::PARTIAL_UNLOCK_TIME = 25000; // ms
const unsigned int BoardCoordinator::IGNORE_NEW_MESSAGES_TIME = 1250; // ms
BoardCoordinator::BoardCoordinator(WirelessController * wireless, GPIOController * gpio)
{
	state = LOCKED;
	this->wireless = wireless;
	this->gpio = gpio;
	unlockTimer = 0;
	lastReceivedOpen = 0;
}
void BoardCoordinator::finishPuzzle()
{
	gpio->skeleton.killLEDs();
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
		if (msg->sender == SNDR_MEGA && msg->command==CMD_COFFIN_UNLOCKED && lastReceivedOpen + IGNORE_NEW_MESSAGES_TIME < millis() )
		{
			lastReceivedOpen = millis();
			gpio->coffinTop.open();
			gpio->skeleton.begin();
			state = OPENED;	
		}
		
	}
	if(msg)
		delete msg;
	lastUpdate = millis();

	if (state != DONE)
	{
		if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT)
		{
			finishPuzzle();
		}
		else if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT - 1 && lastUpdate != millis())
		{
			//Serial.println("add:");
			//Serial.println((millis() - lastUpdate));
			unlockTimer = unlockTimer + (millis() - lastUpdate);

			Serial.println(unlockTimer);
			if (unlockTimer >= PARTIAL_UNLOCK_TIME)	
				finishPuzzle();
		}
	}
	delay(1);
}
