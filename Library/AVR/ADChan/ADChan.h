
#pragma once

#if defined(__cplusplus)

typedef usint AdData;

typedef enum
{
	AD_NUM_0 = 0x00,
	AD_NUM_1 = 0x01,
	AD_NUM_2 = 0x02,
	AD_NUM_3 = 0x03,
	AD_NUM_4 = 0x04,
	AD_NUM_5 = 0x05,
	AD_NUM_6 = 0x06,
	AD_NUM_7 = 0x07,
	AD_NUM_8 = 0x20,
	AD_NUM_9 = 0x21,
	AD_NUM_A = 0x22,
	AD_NUM_B = 0x23,
	AD_NUM_C = 0x24,
	AD_NUM_D = 0x25,
	AD_NUM_E = 0x26,
	AD_NUM_F = 0x27,
}
AdNum;

struct Mux
{
	union MuxBit
	{
		Byte _0_to_4	:5;
		Byte _5			:1;
	}
	_sub;
	
	AdNum _all :6;
};


class ADChan
{
protected:
	
	Mux _mem_mux;
	
public:
	
	ADChan(AdNum _num, BOOL _is_pullup);
	
	AdData Read ();	
};

inline ADChan :: ADChan (AdNum _ad_num, BOOL _is_pullup)
{
	static BOOL _sta_flag = FALSE;
	
	_mem_mux._all = _ad_num;
	
	if (_sta_flag == FALSE)
	{
		ADMUX  = 0x00;
		ADCSRA = ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
		ADCSRB = 0;
		
		_sta_flag = TRUE;
	}

	if (_mem_mux._sub._5)
	{
		DDRK &= ~(1 << _mem_mux._sub._0_to_4);
		
		switch (_is_pullup)
		{
			case TRUE:	PORTK |=  (1 << _mem_mux._sub._0_to_4);	break;
			case FALSE:	PORTK &= ~(1 << _mem_mux._sub._0_to_4);	break;
		}
	}
	else
	{
		DDRF &= ~(1 << _mem_mux._sub._0_to_4);
		
		switch (_is_pullup)
		{
			case TRUE:	PORTF |=  (1 << _mem_mux._sub._0_to_4);	break;
			case FALSE:	PORTF &= ~(1 << _mem_mux._sub._0_to_4);	break;
		}
	}
}

inline AdData ADChan :: Read()
{
	AdData _ret = 0;
	
	ADMUX += _mem_mux._sub._0_to_4;
	ADCSRB = (_mem_mux._sub._5 << MUX5);
	
	for (usint i = 0; i < 2; i++)
	{
		ADCSRA |= (1 << ADSC);
		
		while (ADCSRA & (1 << ADSC));
		
		_ret = ADC;
	}
	
	ADMUX  = 0x00;
	ADCSRB = 0x00;
	
	return _ret;
} 

#else



#endif
