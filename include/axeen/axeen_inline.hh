/**************************************************************************//**
 * @file	axeen_inline.hh
 * @brief	常用巨集 inline 化
 * @date	2000-10-10
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_AXEENINLINE_HH__
#define __AXEEN_AXEENINLINE_HH__

inline ULONG_PTR LoWord(ULONG_PTR value)
{
	return (value & 0xFFFF);
}


inline ULONG_PTR HiWord(ULONG_PTR value)
{
	return ((value >> 16) & 0xFFFF);
}

#endif	// !__AXEEN_AXEENINLINE_HH__
