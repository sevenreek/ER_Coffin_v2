#include "WirelessController.h"
const int WirelessController::REPEAT_COUNT = 1000;
WirelessController::WirelessController(int speed, int rx, int tx, int ptt, bool ptt_inv)
{
	driver = new RH_ASK(speed, rx, tx, ptt, ptt_inv);
	driver->init();
}
void WirelessController::sendMessage(Message *m, int repeatCount)
{
	uint8_t * mes = Message::toByteArray(m);
	int len = TOTAL_LENGTH-1;
	while (repeatCount--)
	{
		driver->send(mes,len);
		driver->waitPacketSent();
	}
	delete[] mes;
}
bool WirelessController::hasMessage(Message *& m)
{
	//Serial.println("Checking...");
	uint8_t buffer[TOTAL_LENGTH];
	uint8_t len = TOTAL_LENGTH;
	if ( driver->recv(buffer, &len) )
	{
		//Serial.println("Got something");
		if (len == TOTAL_LENGTH-1)
		{
			m = Message::fromByteArray(buffer);
			//Serial.print("Pointer is:");
			//Serial.println((int)m);
			return true;
		}
		else
			return false;
	}
	else 
		return false;
}