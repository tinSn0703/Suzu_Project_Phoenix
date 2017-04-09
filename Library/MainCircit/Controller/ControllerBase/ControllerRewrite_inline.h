
#pragma once

/************************************************************************/

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Want_to_rewrite (YesNo _arg_yes_no)
{	_mem_is_rewritten = _arg_yes_no;	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_R (DirecX _data)
{	Rewrite_base(STI_RIGHT_X,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_R (DirecY _data)
{	Rewrite_base(STI_RIGHT_Y,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_L (DirecX _data)
{	Rewrite_base(STI_LEFT_X,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_stick_L (DirecY _data)
{	Rewrite_base(STI_LEFT_Y,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_CROSS (DirecX _data)
{	Rewrite_base(BTN_CROSS_X,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite_CROSS (DirecY _data)
{	Rewrite_base(BTN_CROSS_Y,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite (ControllerBtn _bit, BOOL _data)
{	Rewrite_base(_bit,_data,1);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite (ControllerDirecX _bit, DirecX _data)
{	Rewrite_base(_bit,_data,3);	}

//----------------------------------------------------------------------//

inline void ControllerRewrite :: Rewrite (ControllerDirecY _bit, DirecY _data)
{	Rewrite_base(_bit,_data,3);	}

//----------------------------------------------------------------------//

/************************************************************************/
