/**************************************************************************//**
 * @file	mrstream_struct.cc
 * @brief	MRStream Dynamic Library structure
 * @date	2018-08-01
 * @date	2018-08-01
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_MRSTREAM_STRUCT_HH__
#define __AXEEN_MRSTREAM_STRUCT_HH__

/**
 * @struct	MRCARINFO
 * @brief	車輛資訊結構
 * 
 * MRStream 車輛資訊結構列表 for MR8000 Server
 */
struct MRCARINFO {
	wchar_t RID[64];			//!< 設備 RID
	wchar_t DeviceSN[64];		//!< 裝置 Serial Number
	wchar_t CarNumber[64];		//!< 車牌號碼
	wchar_t IP[16];				//!< Host IP
	int     Httport;			//!< HTTP Port
	int     MessengerPort;		//!< Message Port (LOG Server Port ?)
	int     StreamPort;			//!< Stream Port
	double  Latitude;			//!< *** 尚未註解
	double  Longitude;			//!< *** 尚未註解
	float   Altitude;			//!< *** 尚未註解
	float   Speed;				//!< 行車速度
	float   Heading;			//!< *** 尚未註解 (標題??)
	int     CarStatus;			//!< 車輛狀態 (Vehicle status)
	int     CHNum;				//!< DVR Chennel count
	int     RelayNum;			//!< *** 尚未註解
	wchar_t NetType[64];		//!< 網路模式
	wchar_t Company[64];		//!< 所屬公司
	wchar_t Driver[64];			//!< 駕駛員
	wchar_t Version[64];		//!< 裝置版本
	unsigned int UTC;			//!< *** 尚未註解
	wchar_t Gateway[16];		//!< Gateway
	int		SatNum;				//!< *** 尚未註解
	int		Ign;				//!< *** 尚未註解
	int		Fix;				//!< *** 尚未註解
	int		Timezone;			//!< 時區
	wchar_t Model[64];			//!< *** 尚未註解
	wchar_t SystemTime[32];		//!< 系統時間, [SystemTime] db format: datetime
	int		Interval;			//!< *** 尚未註解
	int		FWStatus;			//!< 韌體資訊?
};
typedef MRCARINFO*	LPMRCARINFO;	//!< MRCARINFO 結構指標型別

/**
 * @struct	SSVEHICLEINFO
 * @brief	車輛資訊結構
 * 
 * MRStream 車輛資訊結構列表 for MR8000 Server \n
 */
struct SSVEHICLEINFO {
	TCHAR	DeviceRID[BUFF_SIZE_64];		//!< 設備 RID
	TCHAR	DeviceSN [BUFF_SIZE_64];		//!< 設備 Serial Number
	TCHAR	VehicleNumber[BUFF_SIZE_64];	//!< 車牌號碼
	TCHAR	HostIP[BUFF_SIZE_64];			//!< 主機 IP 位址 (預留 IPv6 空間)
	int		HostPort;						//!< 主機通訊序列埠(Port)
	int		MessagePort;					//!< 訊息通訊序列埠(Port)
	int		StreamPort;						//!< 媒體串流序列埠(Port)
	double  Latitude;						//!< *** 尚未註解
	double  Longitude;						//!< *** 尚未註解
	float   Altitude;						//!< *** 尚未註解
	float   DrivingSpeed;					//!< 行車速度
	float   Heading;						//!< *** 尚未註解 (標題??)
	int     VehicleStatus;					//!< 車輛狀態 (Vehicle status)
	int		ChannelNumber;					//!< DVR Channel Number
	int     RelayNum;						//!< *** 尚未註解
	TCHAR	NetType[BUFF_SIZE_64];			//!< 網路模式
	TCHAR	Company[BUFF_SIZE_64];			//!< 所屬公司
	TCHAR	Driver[BUFF_SIZE_64];			//!< 駕駛員
	TCHAR	Version[BUFF_SIZE_64];			//!< 裝置版本
	UINT	UTC;							//!< *** 尚未註解
	TCHAR	Gateway[BUFF_SIZE_64];			//!< Gateway
	int		SatNum;							//!< *** 尚未註解
	int		Ign;							//!< *** 尚未註解
	int		Fix;							//!< *** 尚未註解
	int		Timezone;						//!< 時區
	TCHAR	Model[BUFF_SIZE_64];			//!< *** 尚未註解
	TCHAR	SystemTime[BUFF_SIZE_64];		//!< 系統時間, [SystemTime] db format: datetime
	int		Interval;						//!< *** 尚未註解
	int		FWStatus;						//!< 韌體資訊?
};
typedef SSVEHICLEINFO*	LPSSVEHICLEINFO;	// !< SSCARINFO 結構指標型別

// MRStream 資料型別
typedef void*		HMRSTREAM;				// handle of mrstream
typedef LONG_PTR	MRSRESULT;				// mrstream error code

enum EEMRS {
	MRS_ERROR_OK = 0
	, MRS_ERROR_SUCCESS = 0			//!< 沒有錯誤 (成功)
	, MRS_ERROR_FAIL				//!< 錯誤
	, MRS_ERROR_INVALID_HANDLE		//!< 無效的 Handle
	, MRS_ERROR_INVALID_POINTER		//!< 無效的 Pointer
	, MRS_ERROR_INVALID_DATAPTR		//!< 無效的 Data pointer
	, MRS_ERROR_INVALID_INDEX		//!< 無效的索引
	, MRS_ERROR_NEW_OBJECT			//!< 建立物件失敗
	, MRS_ERROR_NEW_MEMORY			//!< 配置記憶體失敗
	, MRS_ERROR_NEW_ARRAY			//!< 配置陣列記憶體失敗
	, MRS_ERROR_THEEND				//!< 枚舉盡頭
};


#endif // !__AXEEN_MRSTREAM_STRUCT_HH__
