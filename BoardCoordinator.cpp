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
	Serial.println("Finished skeleton");
	Message* m = new Message(SNDR_COFFIN, MTYPE_STATE, CMD_COFFIN_COMPLETED, 0);
	wireless->sendMessage(m, 1);
	delete m;
	state = DONE;
}
void BoardCoordinator::onUpdate()
{
	Message * msg = 0;
	if (state == LOCKED && wireless->hasMessage(msg))
	{

		//Serial.print("Then pointer is:");
		//Serial.println((int)msg);
		//Serial.print(msg->sender);Serial.print(" = ");Serial.println(SNDR_MEGA);
		//Serial.print(msg->command);;Serial.print(" = ");Serial.println(CMD_COFFIN_UNLOCKED);
		if (msg->sender == SNDR_MEGA && msg->command==CMD_COFFIN_UNLOCKED)
		{
			gpio->coffinTop.open();
			state = OPENED;
			
		}
		delete msg;
	}
	else if (state == OPENED)
	{
		lastUpdate = millis();
		if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT)
		{
			finishPuzzle();
		}
		else if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT-1 && lastUpdate != millis())
		{
			//Serial.println("add:");
			//Serial.println((millis() - lastUpdate));
			unlockTimer = unlockTimer + (millis() - lastUpdate);
	
			Serial.println(unlockTimer);
			if (unlockTimer >= PARTIAL_UNLOCK_TIME)
				finishPuzzle();
		}
		delay(1);
	}
}
