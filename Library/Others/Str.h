

#pragma once

#include <string.h>

#include "BOOL.h"

/************************************************************************/

#ifdef __cplusplus	//C++‚ÌŽž—p

	extern "C"	{

#endif /*__cplusplus*/

/************************************************************************/

inline uint Str_size (const char * _str);

inline BOOL Str_comp (const char * _str_base, const char * _str_comp);

inline char * Str_copy (char * _str, const char * _str_copy);

inline char * Str_add (char _str[], const char _str_add[]);

inline char Convert_hex_to_char (const Byte _num);

inline Byte Convert_char_to_hex (const char _char);

/************************************************************************/

#ifdef __cplusplus	//C++‚ÌŽž—p

	}

#endif /*__cplusplus*/

/************************************************************************/

#include "Str/Str_imp.h"
