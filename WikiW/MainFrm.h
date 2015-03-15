#pragma once

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CMainFrame();
protected:
	HICON m_hIcon;
	DECLARE_DYNAMIC ( CMainFrame )
	void OnPaint ( void );
	HCURSOR OnQueryDragIcon ( )
	{
		return static_cast<HCURSOR>( m_hIcon );
	};
	CStatusBar        m_wndStatusBar;
	DECLARE_MESSAGE_MAP()
};
