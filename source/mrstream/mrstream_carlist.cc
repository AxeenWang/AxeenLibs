/**************************************************************************//**
 * @file	mrstream_carlist.cc
 * @brief	MRStream Dynamic Library - 車輛資訊類別, 成員函數
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#include "include/mrstream_carlist.hh"

//! CxCarlist 建構式
CxCarlist::CxCarlist()
	: m_nIndex(-1)
	, m_nHostPort(0)
	, m_szVehicleDataPtr(NULL) {
}

//! CxCarlist 解構式
CxCarlist::~CxCarlist() { this->ClassInTheEnd(); }

/**
 * 類別摧毀處理
 * 
 * 釋放所有配置記憶體，刪除於釋放所有物件配置
 */
void CxCarlist::ClassInTheEnd()
{
	SAFE_DELETE_ARRAY(m_szVehicleDataPtr);
	::memset((void*)m_szHostIP, 0, sizeof(m_szHostIP));
	m_nHostPort = 0;
	m_nIndex = -1;
}


