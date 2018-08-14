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

/**
 * @class CxCarlist
 * @brief 車輛資訊類別
 *
 * 與伺服器連接取得車輛資訊，提供後續媒體串流或其他服務使用。
 */
class CxCarlist
{
public:
	CxCarlist();
	virtual ~CxCarlist();
	void	SetError(EEMRS eErr, LPTSTR szErrPtr = NULL);
	EEMRS	GetError();
	EEMRS	SetHost(LPCTSTR szHostPtr, int nHostPort);

protected:
	void	Initialize();
	virtual void ClassInTheEnd();
	
protected:
	int		m_nIndex;					//!< 當前車輛索引
	TCHAR	m_szHostIP[BUFF_SIZE_64];	//!< 主機 IP 位址
	int		m_nHostPort;				//!< 主機通訊埠(Port)
	char*	m_szVehicleDataPtr;			//!< 車輛資料字串緩衝區 (UTF-8)

	EEMRS	m_eErrCode;					//!< 錯誤碼
	TCHAR*	m_szErrorPtr;				//!< 錯誤說明存放位址
};

#endif // !__AXEEN_MRSTREAM_CARLIST_HH__
