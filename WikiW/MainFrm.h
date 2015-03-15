#pragma once
//#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual ~CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)
	CStatusBar        m_wndStatusBar;
	//CChildView    m_wndView;
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()
};
