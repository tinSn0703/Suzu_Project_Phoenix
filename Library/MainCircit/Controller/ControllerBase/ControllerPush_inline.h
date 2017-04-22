
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
	const Btn _temp = ControllerGet :: Get(_btn);
	const Btn _push = Is_enabled(_btn) & _temp;
	
	Want_to_enable(_btn, _temp);
	
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_right_0()
{
	const Btn _push = Is_enabled(0) & ControllerGet :: Get_right_0();
	Want_to_enable(0, ControllerGet :: Get_right_0());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_right_1()
{
	const Btn _push = Is_enabled(1) & ControllerGet :: Get_right_1();
	Want_to_enable(1, ControllerGet :: Get_right_1());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_left_0()
{
	const Btn _push = Is_enabled(2) & ControllerGet :: Get_left_0();
	Want_to_enable(2, ControllerGet :: Get_left_0());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_left_1()
{
	const Btn _push = Is_enabled(3) & ControllerGet :: Get_left_1();
	Want_to_enable(3, ControllerGet :: Get_left_1());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_other_0()
{
	const Btn _push = Is_enabled(4) & ControllerGet :: Get_other_0();
	Want_to_enable(4, ControllerGet :: Get_other_0());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_other_1()
{
	const Btn _push = Is_enabled(5) & ControllerGet :: Get_other_1();
	Want_to_enable(5, ControllerGet :: Get_other_1());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_START()
{
	const Btn _push = Is_enabled(6) & ControllerGet :: Get_START();
	Want_to_enable(6, ControllerGet :: Get_START());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_SELECT()
{
	const Btn _push = Is_enabled(7) & ControllerGet :: Get_SELECT();
	Want_to_enable(7, ControllerGet :: Get_SELECT());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_btn_North()
{
	const Btn _push = Is_enabled(8) & ControllerGet :: Get_btn_North();
	Want_to_enable(8, ControllerGet :: Get_btn_North());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_btn_South()
{
	const Btn _push = Is_enabled(9) & ControllerGet :: Get_btn_South();
	Want_to_enable(9, ControllerGet :: Get_btn_South());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_btn_East()
{
	const Btn _push = Is_enabled(10) & ControllerGet :: Get_btn_East();
	Want_to_enable(10, ControllerGet :: Get_btn_East());
	return _push;
}

//----------------------------------------------------------------------//

inline Btn ControllerPush :: Push_btn_West()
{
	const Btn _push = Is_enabled(11) & ControllerGet :: Get_btn_West();
	Want_to_enable(11, ControllerGet :: Get_btn_West());
	return _push;
}

//----------------------------------------------------------------------//

/************************************************************************/
