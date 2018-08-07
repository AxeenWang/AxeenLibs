/**************************************************************************//**
 * @file	wframe_struct.hh
 * @brief	Win32 Frame library 資料結構
 * @author	Swang
 * @date	2018-03-31
 * @date	2018-07-25
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WIN32FRAME_STRUCT_HH__
#define __AXEEN_WIN32FRAME_STRUCT_HH__

/**
 * @enum	EECTRLTYPE
 * @brief	列舉 Microsoft Windows 控制項索引
 */
enum EECTRLTYPE {
	ECtrlPassStart = 0,			//!< 起始識別符號
	ECtrlButton,				//!< 控制項 : Button
	ECtrlComboBox,				//!< 控制項 : Combo Box
	ECtrlEditBox,				//!< 控制項 : Edit control.
	ECtrlListBox,				//!< 控制項 : List box.
	ECtrlMDIClient,				//!< 控制項 : MDI client window.
	ECtrlScrollBar,				//!< 控制項 : Scroll bar.
	ECtrlStatic,				//!< 控制項 : Static control.

	ECtrlComboLBox,				//!< 控制項 : List box, list box contained in a combo box.
	ECtrlDDEMLEvent,			//!< Dynamic Data Exchange Management Library (DDEML) events.
	ECtrlMessage,				//!< Message-only window.
	ECtrlDu32768,				//!< 控制項 : Menu.
	ECtrlDu32769,				//!< 控制項 : Desktop window.
	ECtrlDialogBox,				//!< 控制項 : Dialog box. (32770)
	ECtrlDu32771,				//!< 控制項 : Task switch window.
	ECtrlDu32772,				//!< 控制項 : Icon titles.

	ECtrlToolbarWindow32,		//!< 控制項 : Toolbar
	ECtrlTooltips_class32,		//!< 控制項 : Tooltip
	ECtrlMsctls_statusbar32,	//!< 控制項 : Status bar
	ECtrlSysTreeView32,			//!< 控制項 : Tree view
	ECtrlSysListView32,			//!< 控制項 : List view
	ECtrlSysAnimate32,			//!< 控制項 : Animation
	ECtrlSysHeader32,			//!< 控制項 : Header
	ECtrlMsctls_hotkey32,		//!< 控制項 : Hot-key
	ECtrlMsctls_progress32,		//!< 控制項 : Progress bar
	ECtrlRICHEDIT,				//!< 控制項 : Rich edit
	ECtrlMsctls_updown32,		//!< 控制項 : Up-down
	ECtrlSysTabControl32,		//!< 控制項 : Tab
	ECtrlPassEnd,				//!< 結束識別符號
	ECtrlEmpty = -1				//!< 錯誤識別符號
};


/**
 * @struct	SSLVCOLUMN
 * @brief	建立 Listview 控制項， Column 資訊設定
 * @details	ListView REPORT style Column 文字顯示與對齊方式
 */
struct SSLVCOLUMN {
	int				iWidth;			//!< 寬度
	int				iAlign;			//!< 對齊方式 參照 LVCOLUMN_ALIGN_LEFT、LVCOLUMN_ALIGN_RIGHT、LVCOLUMN_ALIGN_CENTER
	const TCHAR*	pszText;		//!< 字串指標 for column
};
typedef SSLVCOLUMN*	LPSSLVCOLUMN;	//!< SSLVCOLUMN 結構指標型別
#define LVCOLUMN_ALIGN_LEFT		0	//!< ListView Column 顯示位置靠左
#define LVCOLUMN_ALIGN_RIGHT	1	//!< ListView Column 顯示位置靠右
#define LVCOLUMN_ALIGN_CENTER	2	//!< ListView Column 顯示位置居中
#define LVCOLUMN_ALIGN_PASSEND	3	//!< ListView Column 結尾識別


/**
 * @struct	SSCTRL
 * @brief	建立控制項之結構
 * @details 依照結構定義內容建立控制項
 */
struct SSCTRL {
	EECTRLTYPE		eType;		//!< conctrller type, see "EmCTRLS" enumlator
	HINSTANCE		hInstance;	//!< the handle of module
	HWND			hParent;	//!< handle of parent window
	WNDPROC			fnWndProc;	//!< pointer of callback function

	const TCHAR*	szNamePtr;	//!< conctrller item window text
	DWORD			dwStyle;	//!< conctrller item style
	DWORD			dwExStyle;	//!< conctrller item extern style
	int				iPosx;		//!< start draw position (x-coordination)
	int				iPosy;		//!< start draw position (y-coordination)
	int				iWidth;		//!< the window width
	int				iHeight;	//!< the window height
	int				idItem;		//!< conctrller item id
	void*			vUnknowPtr;	//!< pointer of user data
};
typedef SSCTRL*		LPSSCTRL;		//!< SSCTRL 結構指標型別
#define SSCTRL_ITEMID_NIL	0		//!< Controller 子控制項代碼 (無效值)
#define SSCTRL_ITEMID_MIN	1		//!< Controller 子控制項代碼 (最小值)
#define SSCTRL_ITEMID_MAX	65535	//!< Controller 子控制項代碼 (最大值)


/**
 * @struct	SSCTRLPARAM
 * @brief	建立控制項額外資料
 * @note	使用 SetWindowLongPtr (GWLP_WNDPROC) 建立新訊息處理函式時 \n
 *			可先利用 SetWindowLongPtr (GWLP_USERDATA) 設定為此額外資料
 */
struct SSCTRLPARAM {
	void*	vObjPtr;	//!< 控制項類別物件指標
	void*	vParamPtr;	//!< 額外資料指標
	void*	Reserved1;	//!< 保留未來擴充，亦可任意使用資料。
	void*	Reserved2;	//!< 保留未來擴充，亦可任意使用資料。
};
typedef SSCTRLPARAM*	LPSSCTRLPARAM;	//!< SSCTRLPARAM 結構指標型別


/**
 * @struct	SSDIALOGPARAM
 * @brief	建立 Dialog 額外參數結構
 * @details	Dialog 被建立時會發出 WM_INITDIALOG 訊息
 *
 *	WM_INITDIALOG
 *	- wParam =	控制項接收默認鍵盤焦點的 HWND
 *	- lParam =	附加初始化數據。\n
 *				使用 CreateDialogIndirectParam、CreateDialogParam、DialogBoxIndirectParam、DialogBoxParam 功能建立 Dialog box \n
 *				該數據將作為 lParam 參數傳遞給系統 。\n
 *				對於屬性表，該參數是指向用於創建頁面的 PROPSHEETPAGE 結構的指標。\n
 *				如果使用其他對話框功能建立，則此參數為零。
 */
struct SSDIALOGPARAM {
	void* vDialogPtr;	//!< 存放物件指標 (this)
	void* vParamPtr;	//!< 存放其他資訊
};
typedef SSDIALOGPARAM*	LPSSDIALOGPARAM;	//!< SSDIALOGPARAM 結構指標型別


/**
 * @struct	SSFRAMEWINDOW
 * @brief	建立標準視窗框架結構
 * @details 依據結構內容，使用 WsFrameWindow 建立對應視窗框架
 */
struct SSFRAMEWINDOW {
	HINSTANCE	hInstance;		//!< set handle of instance (handle of process module)
	HWND		hWndParent;		//!< set handle of parent window
	WNDPROC		fnWndProc;		//!< set a window call-back function pointer
	LPCTSTR		pszClassName;	//!< pointer of class name
	LPCTSTR		pszTitleName;	//!< pointer of window's name
	int			iPosx;			//!< set display window x-coordinate
	int			iPosy;			//!< set display window y-coordinate
	int			iWidth;			//!< set window client-area width
	int			iHeight;		//!< set window client-area height
	UINT		uClassStyle;	//!< set register window class style
	HBRUSH		hBackground;	//!< set wndow background color
	HICON		hIcon;			//!< set handle of icon
	HICON		hIconSm;		//!< set handle of small icon
	HCURSOR		hCursor;		//!< set handle of cursor
	DWORD		dwStyle;		//!< set window style
	DWORD		dwExStyle;		//!< set window extend style
	HMENU		hMenuOrIdItem;	//!< set menu headle or item id
};
typedef SSFRAMEWINDOW*	LPSSFRAMEWINDOW;	//!< SSFRAMEWINDOW 結構指標型別
#define DEFAULT_SWND_CLASS      "AXEEN_SAMPLE_WINDOW"	//!< 預設視窗 Class 名稱 (for RegisterClass )
#define DEFAULT_SWND_TITLE      "Axeen Sample Window"	//!< 預設視窗標題
#define DEFAULT_SWND_WIDTH      1280					//!< 預設視窗寬度
#define DEFAULT_SWND_HEIGHT     720						//!< 預設視窗高度
#define DEFAULT_SWND_STYLE      (WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)	//!< 預設視窗風格

#define EVENT_IDTIMER_NIL		0		//!< 計時器ID 無效值
#define EVENT_IDTIMER_MIN		1		//!< 計時器ID 最小值
#define EVENT_IDTIMER_MAX		65535	//!< 計時器ID 最大值


#endif // !__AXEEN_WIN32FRAME_STRUCT_HH__
