
#pragma once

/************************************************************************/

typedef double  LolitaCycle;
typedef DataBit16 LolitaData;

/************************************************************************/

class Lolita
{
//variable
private:
	
	UartReceive _mem_uart;
	
	YesNo _mem_is_make_round :1;
	
	LolitaData _mem_memory :10;
	
	LolitaData _mem_data :10;
	
//function
private:
	
	void Check_round();
	
public:
	
	Lolita();
	Lolita(UartNum _uart_num);
	
	void Initialize();
	
	void Receive();
	
	YesNo Is_make_round();
	
	LolitaData Get();
};

/************************************************************************/

//----------------------------------------------------------------------//

inline YesNo Lolita :: Is_make_round()
{
	return _mem_is_make_round;
}

//----------------------------------------------------------------------//

inline LolitaData Lolita :: Get()
{
	return (_mem_data);
}

//----------------------------------------------------------------------//

/************************************************************************/
