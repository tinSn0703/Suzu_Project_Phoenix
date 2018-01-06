
#include <BTC/BTC.h>
#include <BTC/BTC_Base/BTC_define.h>

/************************************************************************/

#if		BLUETOOTH == BLUEMASTER
#	pragma message("Bluetooh select BlueMaster.")
#elif	BLUETOOTH == ROBOBA005
#	pragma message("Bluetooh select ROBOBA005.")
#else
#	error "Please define BLUEMASTER=0 or ROBOBA005=1. "
#endif

/************************************************************************/

namespace Bluetooth
{

/************************************************************************/

//----------------------------------------------------------------------//

inline void Set_adrs
(
	BluetoothAdrs		_str_adrs_written[], 
	const BluetoothAdrs	_bt_adrs[]
)
{
	for (usint i = 0; i < NUM_BT_ADRS_TAIL; i++)
	{
		_str_adrs_written[i] = _bt_adrs[i];
	}
	
	_str_adrs_written[NUM_BT_ADRS_TAIL] = '\0';
}

//----------------------------------------------------------------------//

void Read()
{
	char _temp = '\0';
	
	for (uByte i = 0; ! ((_temp == '\n') && (i > 1)); i++)
	{
		CTS_LOW();
		
		_temp = Uart::Receive_8bit(UART_NUM_BT);
		
		CTS_HIGH();
	}
}

//----------------------------------------------------------------------//

void Wait_until_matches(const char _str_comp[])
{
	uByte i = 0;
	
	char _temp = '\0';
	
	while (1)
	{
		CTS_LOW();
		
		_temp = Uart::Receive_8bit(UART_NUM_BT);
		
		CTS_HIGH();
		
		if (_str_comp[i] == _temp)
		{
			if ((_temp == '\n') && (i > 1))	break;
			
			i ++;
		}
		else
		{
			i = 0;
		}
	}
}

//----------------------------------------------------------------------//

void Wait_until_matches(const char _str_comp[], char _str_read[])
{
	do
	{
		Read(_str_read);
		
	} while (Str_comp(_str_comp, _str_read) == FALSE);
}

//----------------------------------------------------------------------//

inline void Wait_until_matches_OK()
{
	Wait_until_matches("\r\nOK\r\n");
}

//----------------------------------------------------------------------//

inline void Wait_until_matches_ACK()
{
	Wait_until_matches("\r\nACK\r\n");
}

//----------------------------------------------------------------------//

/************************************************************************/

//----------------------------------------------------------------------//

void Initialize()
{
	DDR_CTS |=  CTS_BIT;
	DDR_RSE |=  RSE_BIT;
	DDR_RTS &= ~RTS_BIT;
	
	CTS_HIGH();
	RSE_HIGH();
	RTS_LOW();
	
	Uart::Initialize_details(UART_NUM_BT, 0x0a, 0x00);
	
	Uart::Enable_transmit(UART_NUM_BT);
	Uart::Enable_receive(UART_NUM_BT);
	
	Wait_until_matches_OK();
}

//----------------------------------------------------------------------//

uByte Select_partner(BluetoothAdrs _bt_adrs[], const Byte _num_bt)
{
	switch (_num_bt)
	{
		
#if BLUETOOTH == BLUEMASTER
		//BlueMaster
		case  1:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_01);	return 1;
		case  2:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_02);	return 2;
		case  3:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_03);	return 3;
		case  4:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_04);	return 4;
		case  5:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_05);	return 5;
		case  6:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_06);	return 6;
		case  7:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_07);	return 7;
		case  8:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_08);	return 8;
		case  9:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_09);	return 9;
		case 10:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_10);	return 10;
		case 11:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_11);	return 11;
		case 12:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_12);	return 12;
		case 13:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_13);	return 13;
		case 14:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_14);	return 14;
		case 15:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_15);	return 15;
		case 16:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_16);	return 16;
		
#elif BLUETOOTH == ROBOBA005
		//ROBOBA005
		case  0:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_00);	return 0;
		case  1:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_01);	return 1;
		case  2:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_02);	return 2;
		case  3:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_03);	return 3;
		case  4:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_04);	return 4;
		case  5:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_05);	return 5;
		case  6:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_06);	return 6;
		case  7:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_07);	return 7;
		case  8:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_08);	return 8;
		case  9:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_09);	return 9;
		case 10:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_10);	return 10;
		case 11:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_11);	return 11;
		case 12:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_12);	return 12;
		case 13:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_13);	return 13;
		case 14:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_14);	return 14;
		case 15:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_15);	return 15;
		
#endif
		
	};
	
	return CODE_PARTNER_SELECTION_UNFINISHED;
}

//----------------------------------------------------------------------//

uByte Select_partner(BluetoothAdrs _bt_adrs[], const BluetoothNum _num_bt)
{
	switch (_num_bt)
	{
		
#if BLUETOOTH == BLUEMASTER
		//BlueMaster
		case BLUEMASTER_01:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_01);	return 1;
		case BLUEMASTER_02:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_02);	return 2;
		case BLUEMASTER_03:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_03);	return 3;
		case BLUEMASTER_04:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_04);	return 4;
		case BLUEMASTER_05:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_05);	return 5;
		case BLUEMASTER_06:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_06);	return 6;
		case BLUEMASTER_07:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_07);	return 7;
		case BLUEMASTER_08:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_08);	return 8;
		case BLUEMASTER_09:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_09);	return 9;
		case BLUEMASTER_10:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_10);	return 10;
		case BLUEMASTER_11:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_11);	return 11;
		case BLUEMASTER_12:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_12);	return 12;
		case BLUEMASTER_13:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_13);	return 13;
		case BLUEMASTER_14:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_14);	return 14;
		case BLUEMASTER_15:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_15);	return 15;
		case BLUEMASTER_16:	Set_adrs(_bt_adrs, ADRS_BLUEMASTER_16);	return 16;
		
#elif BLUETOOTH == ROBOBA005
		//ROBOBA005
		case ROBOBA005_00:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_00);	return 0;
		case ROBOBA005_01:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_01);	return 1;
		case ROBOBA005_02:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_02);	return 2;
		case ROBOBA005_03:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_03);	return 3;
		case ROBOBA005_04:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_04);	return 4;
		case ROBOBA005_05:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_05);	return 5;
		case ROBOBA005_06:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_06);	return 6;
		case ROBOBA005_07:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_07);	return 7;
		case ROBOBA005_08:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_08);	return 8;
		case ROBOBA005_09:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_09);	return 9;
		case ROBOBA005_10:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_10);	return 10;
		case ROBOBA005_11:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_11);	return 11;
		case ROBOBA005_12:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_12);	return 12;
		case ROBOBA005_13:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_13);	return 13;
		case ROBOBA005_14:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_14);	return 14;
		case ROBOBA005_15:	Set_adrs(_bt_adrs, ADRS_ROBOBA005_15);	return 15;
		
#endif
		
	};
	
	return CODE_PARTNER_SELECTION_UNFINISHED;
}

//----------------------------------------------------------------------//

void Write(const char _str_write[])
{
	for (uByte i = 0; _str_write[i] != '\0'; i++)
	{
		while (RTS_READ());
		
		Uart::Transmit_8bit(UART_NUM_BT, _str_write[i]);
	}
}

//----------------------------------------------------------------------//

void Read(char _str_read[])
{
	uByte i = 0;
	
	while (1)
	{
		CTS_LOW();
		
		_str_read[i] = Uart::Receive_8bit(UART_NUM_BT);
		
		CTS_HIGH();
		
		if ((_str_read[i] == '\n') && (i > 1))	break;
		
		i++;
	}
	
	_str_read[i + 1] = '\0';
}

//----------------------------------------------------------------------//

void Connect_to_slave(const BluetoothAdrs _bt_adrs[])
{
	char _str_read[40] = {};
	
	char _str_conmaster[32] = "AT+CONMASTER=1,000190xxxxxx\r\n";
	char _str_connected[32] = "\r\n+CONNECTED=000190xxxxxx\r\n";
	
	for (usint i = 0; i < NUM_BT_ADRS_TAIL; i++)
	{
		_str_conmaster[15 + i] = _bt_adrs[i];
		_str_connected[13 + i] = _bt_adrs[i];
	}
	
	Go_start_connect:
	
	Write(_str_conmaster);
	
	Wait_until_matches_ACK();
	
	do
	{
		Read(_str_read);
		
		if (Str_comp("\r\nTIMEOUT\r\n", _str_read))
		{
			goto Go_start_connect;
		}
	}
	while (Str_comp(_str_connected, _str_read) != TRUE);
	
	Wait_until_matches_OK();
	
	CTS_LOW();
}

//----------------------------------------------------------------------//

void Connect_to_master(const BluetoothAdrs _bt_adrs[])
{
	char _str_read[40] = {};
	
	char _str_connecting[33] = "\r\n+CONNECTING=000190xxxxxx\r\n";
	char _str_connected[32]  = "\r\n+CONNECTED=000190xxxxxx\r\n";
	
	for (uByte i = 0; i < NUM_BT_ADRS_TAIL; i++)
	{
		_str_connecting[14 + i] = _bt_adrs[i];
		_str_connected[13 + i]  = _bt_adrs[i];
	}
	
	Write("AT+CONSLAVE=1,0\r\n");
	
	Wait_until_matches_ACK();
	
	Wait_until_matches(_str_connecting);
	
	Wait_until_matches("\r\n+ACCEPT?\r\n");
	
	Go_start_connect:
	
	Write("AT+RESCON=1\r\n");
	
	do
	{
		Read(_str_read);
		
		if (Str_comp("\r\nTIMEOUT\r\n", _str_read))
		{
			goto Go_start_connect;
		}
	}
	while (Str_comp(_str_connected, _str_read) != TRUE);
	
	Wait_until_matches_OK();
	
	CTS_LOW();
}

//----------------------------------------------------------------------//

void Reconnect_to_slave(const BluetoothAdrs _bt_adrs[])
{
	Read();
	
	Set_to_command_mode();
	
	Wait_until_matches_OK();
	
	Connect_to_slave(_bt_adrs);
}

//----------------------------------------------------------------------//

void Reconnect_to_master(const BluetoothAdrs _bt_adrs[])
{
	Set_to_command_mode();
	
	Wait_until_matches_OK();
	
	Connect_to_master(_bt_adrs);
}

//----------------------------------------------------------------------//

void Read_bt_adrs(char _ret_bt_adrs[])
{
	Write("AT+GETADDR\r\n");
	
	Read(_ret_bt_adrs);
	
	char *_temp = &_ret_bt_adrs[8];
	
	_ret_bt_adrs = _temp;
	
	_ret_bt_adrs[NUM_BT_ADRS_TAIL] = '\0';
}

//----------------------------------------------------------------------//

void Set_to_command_mode()
{
	CTS_LOW();
	RSE_LOW();	_delay_ms(15);
	RSE_HIGH();	_delay_ms(15);
}

//----------------------------------------------------------------------//

/************************************************************************/

};

/************************************************************************/

