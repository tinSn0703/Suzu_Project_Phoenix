

#pragma once

/************************************************************************/

#include "BOOL.h"

/************************************************************************/

typedef enum
{
	SIGNAL_FREE		= 0b00,	//�t���[
	SIGNAL_REVERSE	= 0b01,	//�t��]
	SIGNAL_FORWARD	= 0b10,	//����]
	SIGNAL_BREAK	= 0b11	//�u���[�L
}
Signal;

/************************************************************************/

//----------------------------------------------------------------------//

inline Signal Want_to_make_forward(const YesNo _yes_no)
{
	return (_yes_no ? SIGNAL_FORWARD : SIGNAL_REVERSE);
}

//----------------------------------------------------------------------//

inline Signal Want_to_make_reverse(const YesNo _yes_no)
{
	return (_yes_no ? SIGNAL_REVERSE : SIGNAL_FORWARD);
}

//----------------------------------------------------------------------//

inline Signal To_Signal (const int _data)
{
	return (Signal)(_data & 3);
}

//----------------------------------------------------------------------//

inline Signal Reversal_Signal (const Signal _sig)
{
	return
	(
		(_sig == SIGNAL_FORWARD) ? SIGNAL_REVERSE :
		(_sig == SIGNAL_REVERSE) ? SIGNAL_FORWARD :
		_sig
	);
}

//----------------------------------------------------------------------//

inline BOOL Is_Signal_rotation (const Signal _sig)
{
	return Is_true_the(0b0110, _sig);
}

//----------------------------------------------------------------------//

inline BOOL Is_Signal_stop (const Signal _sig)
{
	return Is_true_the(0b1001, _sig);
}

//----------------------------------------------------------------------//

/************************************************************************/
