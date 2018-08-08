/**************************************************************************//**
 * @file	mrstream_carlist.hh
 * @brief	MRStream Dynamic Library - 車輛資訊類別
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_MRSTREAM_CARLIST_HH__
#define __AXEEN_MRSTREAM_CARLIST_HH__
#include "mrstream_define.hh"

class CxCarlist
{
public:
	CxCarlist();
	virtual ~CxCarlist();

protected:
	void	ClassInTheEnd();
	
protected:
	int		m_nIndex;					//!< 當前車輛索引
	TCHAR	m_szHostIP[BUFF_SIZE_256];	//!< 主機 IP 位址
	int		m_nHostPort;				//!< 主機通訊埠(Port)
	char*	m_szVehicleDataPtr;			//!< 車輛資料字串緩衝區 (UTF-8)
};

#endif // !__AXEEN_MRSTREAM_CARLIST_HH__
