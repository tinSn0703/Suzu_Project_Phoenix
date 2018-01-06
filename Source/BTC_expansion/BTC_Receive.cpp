
#include <BTC/BTC.h>
#include <BTC_expansion/BTC_Receive.h>

/************************************************************************/

namespace Bluetooth
{

namespace Bit24
{

/************************************************************************/

#define BIT_LED0 (1 << PB0)
#define BIT_LED1 (1 << PB1)
#define BIT_LED2 (1 << PB2)
#define BIT_LED3 (1 << PB3)
#define BIT_LED4 (1 << PB4)

#define PORT_LED PORTB

#define INIT_LED() (DDRB = 0x1f);	(PORT_LED = 0x00)

#define LED0_ON() (PORT_LED |= BIT_LED0)
#define LED1_ON() (PORT_LED |= BIT_LED1)
#define LED2_ON() (PORT_LED |= BIT_LED2)
#define LED3_ON() (PORT_LED |= BIT_LED3)
#define LED4_ON() (PORT_LED |= BIT_LED4)

#define LED_ON()	(PORT_LED |= 0x1f)

#define LED0_OFF() (PORT_LED &= ~BIT_LED0)
#define LED1_OFF() (PORT_LED &= ~BIT_LED1)
#define LED2_OFF() (PORT_LED &= ~BIT_LED2)
#define LED3_OFF() (PORT_LED &= ~BIT_LED3)
#define LED4_OFF() (PORT_LED &= ~BIT_LED4)

#define LED_OFF()	(PORT_LED &= 0xe0)

#define INIT_SW()	(DDRC = 0x00);	(PORTC = 0xff)

#define SW_READ() ((BluetoothNum)((~PINC) & 0xff))

/************************************************************************/

//----------------------------------------------------------------------//

ReceiveCircit::ReceiveCircit()
{
	_mem_read_data[0] = 0x3f;
	_mem_read_data[1] = 0x7f;
	_mem_read_data[2] = 0x8f;
	_mem_read_data[3] = 0xc0;
	
	INIT_SW();
	INIT_LED();
	
	LED0_ON();
}

//----------------------------------------------------------------------//

void ReceiveCircit::Initialize()
{	
	Bluetooth::Initialize();
	
	LED1_ON();
}

//----------------------------------------------------------------------//

void ReceiveCircit::Connect()
{
	uByte _num = CODE_PARTNER_SELECTION_UNFINISHED;
	
	do
	{
		_num = Bluetooth::Select_partner(_mem_bt_adrs, SW_READ());
	}
	while (_num == CODE_PARTNER_SELECTION_UNFINISHED);
	
	LED_OFF();
	
	if (_num & (1 << 0))	LED0_ON();
	if (_num & (1 << 1))	LED1_ON();
	if (_num & (1 << 2))	LED2_ON();
	if (_num & (1 << 3))	LED3_ON();
	
	Bluetooth::Connect_to_master(_mem_bt_adrs);
	
	LED_OFF();
}

//----------------------------------------------------------------------//

void ReceiveCircit::Reconnect()
{
	LED_ON();
	
	Bluetooth::Reconnect_to_master(_mem_bt_adrs);
	
	LED_OFF();
}

//----------------------------------------------------------------------//

void ReceiveCircit::Receive()
{
	Bluetooth::Read(_data_receive);
	
	if ((_data_receive[0] == '\r') || (_data_receive[0] == '+'))
	//"\r\n+LINK_LOST=" , "\r\n+DISCONNECTED=" , "+LINK_LOST="
	{
		Reconnect();
	}
	else
	{
		for (uByte i = 0; i < NUM_CONTROLLER_DATA_24BIT; i ++)
		{
			_mem_read_data[i] =
			(
				(Convert_char_to_hex(_data_receive[i * 2 + 0]) << 4) |
				(Convert_char_to_hex(_data_receive[i * 2 + 1]) << 0)
			);
		}
	}
}

//----------------------------------------------------------------------//

void ReceiveCircit :: Turn_on()
{
	LED_ON();
}

//----------------------------------------------------------------------//

void ReceiveCircit :: Turn_on(const uByte _num)
{
	PORT_LED |= (1 << _num);
}

//----------------------------------------------------------------------//

void ReceiveCircit :: Turn_off()
{
	LED_OFF();
}

//----------------------------------------------------------------------//

void ReceiveCircit :: Turn_off(const uByte _num)
{
	PORT_LED &= ~(1 << _num);
}

//----------------------------------------------------------------------//

void ReceiveCircit :: Check_read_data()
{
	LED_OFF();
	
	((_mem_read_data[0] == 0x3f) ? LED0_OFF() : LED0_ON());
	((_mem_read_data[1] == 0x7f) ? LED1_OFF() : LED1_ON());
	((_mem_read_data[2] == 0x8f) ? LED2_OFF() : LED2_ON());
	((_mem_read_data[3] == 0xc0) ? LED3_OFF() : LED3_ON());
}

//----------------------------------------------------------------------//

/************************************************************************/

};

};

/************************************************************************/
