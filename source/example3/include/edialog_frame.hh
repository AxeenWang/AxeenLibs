/**************************************************************************//**
 * @file	edialog_frame.hh
 * @brief	Example3 - main frame class
 * @date	2010-12-05
 * @date	2018-08-05
 * @author	Swang
 *****************************************************************************/
#ifndef __AXEEN_EXAMPLE3_EDIALOG_FRAME_HH__
#define __AXEEN_EXAMPLE3_EDIALOG_FRAME_HH__
#include "edialog_define.hh"

class CxExamaleDialog : public CxFrameDialog
{
public:
	CxExamaleDialog();
	virtual ~CxExamaleDialog();

protected:
	virtual	INT_PTR MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam) override;
	void OnInitDialog(WPARAM wParam, LPARAM lParam);
	void OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void WindowInTheEnd() override;

protected:
	CxFrameEditbox*		m_cEdit;
	CxFrameButton*		m_cButton;
};

#endif // !__AXEEN_EXAMPLE3_EDIALOG_FRAME_HH__
