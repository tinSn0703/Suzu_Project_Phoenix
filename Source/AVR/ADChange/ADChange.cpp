
#include <avr/io.h>
#include <util/delay.h>
#include <Others/BOOL.h>
#include <AVR/ADChange/ADChange.h>

/************************************************************************/

#define RAD_PER_AD 0.006141921	//2ƒÎ/1023
#define DEG_PER_AD 0.351906158	//360/1023

/************************************************************************/

//----------------------------------------------------------------------//

ADChange::ADChange()
{
	
}

//----------------------------------------------------------------------//

ADChange::ADChange(const ADNum _num, const BOOL _is_pullup)
{
	Reset(_num, _is_pullup);
}

//----------------------------------------------------------------------//

void ADChange::Reset(const ADNum _num, const YesNo _is_pullup)
{
	_mem_ad_num = _num;
	
	ADMUX = 0;
	
	ADCSRA = 0;
	ADCSRB = 0;
	
	if (_mem_ad_num & (1 << 3))
	{
		DDRK &= ~(1 << (_mem_ad_num & 3));
		
		switch (_is_pullup)
		{
			case TRUE:	PORTK |=  (1 << (_mem_ad_num & 3));	break;
			case FALSE:	PORTK &= ~(1 << (_mem_ad_num & 3));	break;
		}
		
		DIDR1 |= (1 << (_mem_ad_num & 3));
	}
	else
	{
		DDRF &= ~(1 << (_mem_ad_num & 3));
		
		switch (_is_pullup)
		{
			case TRUE:	PORTF |=  (1 << (_mem_ad_num & 3));	break;
			case FALSE:	PORTF &= ~(1 << (_mem_ad_num & 3));	break;
		}
		
		DIDR0 |= (1 << (_mem_ad_num & 3));
	}
}

//----------------------------------------------------------------------//

ADData ADChange::Read()
{
	ADCSRA = (1 << ADEN);
	
	ADMUX   = ((_mem_ad_num & 3));
	ADCSRB  = (((_mem_ad_num >> 3) & 1) << MUX5);
	
	for (uByte i = 0; i < 2; i++)
	{
		ADCSRA |= (1 << ADSC);
		
		while (ADCSRA & (1 << ADSC));
		
		ADCSRA |= (1 << ADIF);
		
		_mem_data = ADCL;
		
		_mem_data |= (ADCH << 8);
		
		_delay_us(50);
	}
	
	ADCSRA = 0;
	
	return _mem_data;
}

//----------------------------------------------------------------------//

double ADChange::Get_deg()
{
	return ((double)_mem_data * DEG_PER_AD);
}

//----------------------------------------------------------------------//

double ADChange::Get_rad()
{
	return ((double)_mem_data * RAD_PER_AD);
}

//----------------------------------------------------------------------//

/************************************************************************/
