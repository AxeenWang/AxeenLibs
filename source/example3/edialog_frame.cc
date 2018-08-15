/**************************************************************************//**
 * @file	edialog_frame.cc
 * @brief	Example3 - main frame class member function
 * @date	2010-12-05
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#include "include/edialog_frame.hh"

//! CxExamaleDialog constructor
CxExamaleDialog::CxExamaleDialog()
	: CxFrameDialog()
	, m_cEdit(NULL)
	, m_cButton(NULL) {
}

//! CxExamaleDialog destructor
CxExamaleDialog::~CxExamaleDialog() { }


/**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details 虛擬函數，訊息處理函數
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c INT_PTR		訊息處理結果
 * @remark	MessageDisopse 為虛擬函示，由衍生者重載重新定義動作內容
 */
INT_PTR CxExamaleDialog::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_INITDIALOG:
		this->OnInitDialog(wParam, lParam);
		break;
	case WM_DESTROY:
		this->SysDestroyWindow();
		break;
	case WM_CLOSE:
		this->SysCloseWindow();
		break;
	case WM_COMMAND:
		this->OnCommand(wParam, lParam);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/**
 * @brief WM_INITDIALOG 訊息處理
 * @return 沒有返回值
 */
void CxExamaleDialog::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	CxFrameEditbox* edt = NULL;
	CxFrameButton*	btn = NULL;
	this->SetCenterPosition();

	for (;;) {
		if ((edt = new (std::nothrow) CxFrameEditbox()) == NULL) {
			this->SetError(E_POINTER);
			this->ShowError();
			this->LeaveWindow();
			break;
		}
		m_cEdit = edt;
		
		if (!edt->CreateEditBox(NULL, 10, 40, 78, 25, m_hWnd, 2001, NULL, NULL)) {
			this->ShowError();
			this->LeaveWindow();
			break;
		}
		edt->SetFont(this->GetFont());

		if ((btn = new (std::nothrow) CxFrameButton()) == NULL) {
			this->SetError(E_POINTER);
			this->ShowError();
			this->LeaveWindow();
			break;
		}
		m_cButton = btn;

		if (!btn->CreateButton(TEXT("自訂按鈕"), 10, 420, 120, 40, m_hWnd, 2002, NULL, NULL)) {
			this->ShowError();
			this->LeaveWindow();
			break;
		}
		m_cButton->SetFont(this->GetFont());

		break;
	}
}

/**
* @brief	WM_COMMAND 訊息處理
* @return	沒有返回值
* @remark	子控制項命令觸發, LOWORD wParam 為子項目的 ID
*/
void CxExamaleDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	const static TCHAR* aam[] = {
		TEXT("哈哈哈"),
		TEXT("呵呵呵"),
		TEXT("啦啦啦"),
		TEXT("嘎嘎嘎"),
		TEXT("嗚嗚嗚")
	};
	const static auto len = sizeof(aam) / sizeof(aam[0]);
	static size_t i = 0;

	auto btn = m_cButton;
	auto edt = m_cEdit;

	if (btn != NULL && edt != NULL) {
		int nCmd = static_cast<int>(LOWORD(wParam));

		if (nCmd == btn->GetControlID()) {
			edt->SetText(aam[i]);
			
			if (++i >= len) i = 0;
		}
	}
}

/**
 * 視窗結束處理 (釋放配置記憶體與成員物件)
 *
 * 此為虛擬函數, 由衍生類別繼承 \n
 * 視窗進入關閉階段時進行運作此一函數, 確保類別內所配置的物件與記憶體都被釋放.
 * 壁面物件或記憶體未釋放造成 memory leek.
 */
void CxExamaleDialog::WindowInTheEnd()
{
	// TODO: 結束視窗處理
	SAFE_DELETE(m_cButton);
	SAFE_DELETE(m_cEdit);
	CxFrameDialog::WindowInTheEnd();
}
