
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Want_to_rewrite (const YesNo _yes_no)
{
	_mem_is_rewritten = _yes_no;
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_R (const DirecX _data)
{
	Rewrite(STI_RIGHT_X, _data);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_R (DirecY _data)
{
	Rewrite(STI_RIGHT_Y, _data);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_L (DirecX _data)
{
	Rewrite(STI_LEFT_X, _data);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_L (DirecY _data)
{
	Rewrite(STI_LEFT_Y, _data);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_cross (DirecX _data)
{
	Rewrite(BTN_CROSS_X, _data);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_cross (DirecY _data)
{
	Rewrite(BTN_CROSS_Y, _data);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite (ControllerBtn _bit, BOOL _data)
{
	Rewrite_base(_bit, _data, 1);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite (ControllerDirecX _bit, DirecX _data)
{
	Rewrite_base(_bit, _data, 3);
}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite (ControllerDirecY _bit, DirecY _data)
{
	Rewrite_base(_bit, _data, 3);
}

//----------------------------------------------------------------------//

/************************************************************************/
