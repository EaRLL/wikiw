/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: wBase.h
*
* WikiW is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* WikiW is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with WikiW.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <iostream>
#include <vector>

class CWikiBasePage : public CWnd
{
public:
	virtual BOOL PreCreateWindow ( CREATESTRUCT& cs );
	void CreateChildControls ( void );
};

class CWikiBase : public CFrameWnd
{
public:
	CWikiBase ( );
	virtual BOOL PreCreateWindow ( CREATESTRUCT& cs );
	virtual void CreateChildControls ( void );
	virtual ~CWikiBase ( );

	// { left menu
		CFlatButton b_lM_Opener, b_lM_Main, b_lM_User, b_lM_Stats; // Left menu buttons
		CFont f_blM_Opener, f_blM_Std; // Buttons font

		BOOL isLeftMenuVisible = false;

		void ShowLeftMenu ( );

		BOOL isLeftMenuMain = true;
		BOOL isLeftMenuUser = false;
		BOOL isLeftMenuStats = false;

		void OnBLMenuButtonClick ( UINT nID );  // Button click

		void LeftMenuClear ( );
		void LeftMenuSelectOpt ( );
	// } left menu

	BOOL isWindowMinimized = false;
	CFlatButton b_Options, b_Title, b_CloseApp, b_HideApp; // main
	CFont f_bTopMenu;
	CTabCtrl m_TabCtrl;

	CWnd *m_pActiveTab;
	int ActiveTabID;
	std::vector<CWnd *> m_pPages;
protected:
	HICON m_hIcon;
	DECLARE_DYNAMIC ( CWikiBase )
	void OnBHideAppClick ( void );
	void OnBCloseAppClick ( void );

	void OnSelchangingTab ( NMHDR* pNMHDR, LRESULT* pResult );
	void OnSelchangeTab ( NMHDR* pNMHDR, LRESULT* pResult );

	void OnPaint ( void );
	void OnWindowPosChanging ( WINDOWPOS* lpwndpos );
	BOOL OnEraseBkgnd ( CDC* pDC );
	LRESULT OnNcHitTest ( CPoint point );
	void OnSize ( UINT nType, int cx, int cy );
	HCURSOR OnQueryDragIcon ( )
	{
		return static_cast<HCURSOR>( m_hIcon );
	};
	DECLARE_MESSAGE_MAP()
};

class CWikiBasePage1 : public CWnd
{
public:
	CWikiBasePage1 ( );
	virtual ~CWikiBasePage1 ( );
	virtual BOOL PreCreateWindow ( CREATESTRUCT& cs );
	void CreateChildControls ( void );
	CFlatButton b_Options;
	CFont f_TitleButBig;
};

class CWikiBasePage2 : public CWnd
{
public:
	CWikiBasePage2 ( );
	virtual ~CWikiBasePage2 ( );
	virtual BOOL PreCreateWindow ( CREATESTRUCT& cs );
	void CreateChildControls ( void );
	CFlatButton b_Options;
	CFont f_TitleButBig;
};
