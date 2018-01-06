
#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <AVR/IO/IO.h>
#include <MainCircit/Signal.h>
#include <MainCircit/Motor/MotorRotationOnly.h>

/************************************************************************/

//----------------------------------------------------------------------//

MotorRotationOnly::MotorRotationOnly()
{
	_mem_is_io_set = NO;
	
	_mem_is_signal_reverse = NO;
	
	_mem_signal = SIGNAL_FREE;
}

//----------------------------------------------------------------------//

MotorRotationOnly::MotorRotationOnly
(
	const IoNum _adrs, 
	const IoBit _bit_side_f, 
	const IoBit _bit_side_r
)
{
	_mem_is_signal_reverse = NO;
	
	MotorRotationOnly::Reset(_adrs, _bit_side_f, _bit_side_r);
}

//----------------------------------------------------------------------//

MotorRotationOnly::MotorRotationOnly
(
	const IoNum _adrs_side_f, 
	const IoBit _bit_side_f, 
	const IoNum _adrs_side_r, 
	const IoBit _bit_side_r
)
{
	_mem_is_signal_reverse = NO;
	
	MotorRotationOnly::Reset(_adrs_side_f, _bit_side_f, _adrs_side_r, _bit_side_r);
}

//----------------------------------------------------------------------//

void MotorRotationOnly::Write()
{
	if (_mem_is_io_set)
	{
		_mem_io_side_reverse.Write(Is_true_the(_mem_signal, 0));
		_mem_io_side_forward.Write(Is_true_the(_mem_signal, 1));
	}
}

//----------------------------------------------------------------------//

void MotorRotationOnly::Write_clear()
{
	if (_mem_is_io_set)
	{
		_mem_io_side_reverse.Write(NO);
		_mem_io_side_forward.Write(NO);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
