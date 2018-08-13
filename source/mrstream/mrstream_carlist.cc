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
	, m_szVehicleDataPtr(NULL)
	, m_eErrCode(MRS_ERROR_SUCCESS)
	, m_szErrorPtr(NULL) {
	this->Initialize();
}

//! CxCarlist 解構式
CxCarlist::~CxCarlist() { this->ClassInTheEnd(); }

void CxCarlist::SetError(EEMRS eErr, LPTSTR szErrPtr)
{
	m_eErrCode = eErr;
	// TBD
}

EEMRS CxCarlist::GetError()
{
	return m_eErrCode;
}


/**
 * 初始化成員內容
 *
 * 不要在工作中進行初始化成員內容，除非確定有必要。 \n
 * 最好在物件被建立時才進行初始化作業。
 */
void CxCarlist::Initialize()
{
	this->ClassInTheEnd();

	for (;;) {
		auto p = new (std::nothrow) TCHAR[BUFF_SIZE_256];

		if (p == NULL) {
			this->SetError(MRS_ERROR_NEW_ARRAY);
			break;
		}
		m_szErrorPtr = p;
		break;
	}
}

/**
 * 類別釋放處理
 * 
 * 刪除所有物件與釋放記憶體配置
 */
void CxCarlist::ClassInTheEnd()
{
	SAFE_DELETE_ARRAY(m_szVehicleDataPtr);
	SAFE_DELETE_ARRAY(m_szErrorPtr);
	::memset((void*)m_szHostIP, 0, sizeof(m_szHostIP));
	m_nHostPort = 0;
	m_nIndex = -1;
}
