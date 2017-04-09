

#include <akilcd/akilcd.h>
#include <Others/Others.h>
#include <MainCircit/Motor/MotorBase/MotorBase.h>

#include <math.h>

namespace ClassMotor
{

/************************************************************************/
/*	MotorBase															*/
/************************************************************************/

//----------------------------------------------------------------------//

MotorBase :: MotorBase ()
{	
	_mem_data._0._all = 0x000;
	_mem_data._1._all = 0x000;
	
	_mem_data._0._sub._num_data = MD_DATA_0;
	_mem_data._1._sub._num_data = MD_DATA_1;
}

//----------------------------------------------------------------------//

void MotorBase :: Initialize 
(
	const MdcNum	_arg_num_mdc, 
	const MdNum		_arg_num_md
)
{
	_mem_data._0._all = 0x000;
	_mem_data._1._all = 0x000;
	
	_mem_data._0._sub._num_data = MD_DATA_0;
	_mem_data._1._sub._num_data = MD_DATA_1;
	
	_mem_data._0._sub._num_mdc = _arg_num_mdc;
	_mem_data._1._sub._num_mdc = _arg_num_mdc;
	
	_mem_data._0._sub._num_md = _arg_num_md;
	_mem_data._1._sub._num_md = _arg_num_md;
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorRead															*/
/************************************************************************/

//----------------------------------------------------------------------//

MotorGet :: MotorGet ()	{}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorOperate														*/
/************************************************************************/

//----------------------------------------------------------------------//

MotorOperate :: MotorOperate ()	{}

//----------------------------------------------------------------------//

void MotorOperate :: Set (const Signal _arg_sig)
{
	Set_direct(_arg_sig);
	
	if (Is_Signal_stop(_arg_sig))
	{
		Set_direct(0);
	}
}

//----------------------------------------------------------------------//

void MotorOperate :: Set (const Pwm _arg_pwm)
{
	if (Is_Signal_rotation(Get_sig()))
	{
		Set_direct(To_within(_arg_pwm + _mem_pwm_adjustment, 31, 0));
	}
	else
	{
		Set_direct(0);
	}
}

//----------------------------------------------------------------------//

void MotorOperate :: Set_pwm_P
(
	const int		_target_value, 
	const int		_current_value,
	const double	_p_constant,
	const YesNo		_is_reverse /* = NO */
)
{
	if (_target_value != _current_value)
	{
		const Pwm _pwm = ((_target_value - _current_value) * _p_constant);
		
		if (_pwm > 0)
		{
			Set(Want_to_make_reverse(_is_reverse), _pwm,  TRUE);
		}
		else if (_pwm < 0)
		{
			Set(Want_to_make_forward(_is_reverse), _pwm * -1,  TRUE);
		}
		else
		{
			Set(SIGNAL_BREAK);
		}
	}
	else
	{
		Set(SIGNAL_BREAK);
	}
}

//----------------------------------------------------------------------//

/************************************************************************/
/*	MotorLCD															*/
/************************************************************************/

//----------------------------------------------------------------------//

MotorLCD :: MotorLCD ()	{}

//----------------------------------------------------------------------//

};