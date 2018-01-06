
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline BOOL ControllerPush :: Is_enabled(const int _btn)
{
	return Is_true_the(_mem_is_pushed_btn, _btn);
}

//----------------------------------------------------------------------//

inline void ControllerPush :: Want_to_enable(const int _btn, const YesNo _yesno)
{
	_mem_is_pushed_btn &= ~(1 << _btn);
	_mem_is_pushed_btn |=  (Reversal_BOOL(_yesno) << _btn);
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push(const ControllerBtn _btn)
{
	const Btn _temp = ControllerGet :: operator [](_btn);
	const Btn _push = Is_enabled(_btn) & _temp;
	
	Want_to_enable(_btn, _temp);
	
	return _push;
}

//----------------------------------------------------------------------//

/************************************************************************/
