/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: CWikiBasePage1.h
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

//UINT threadGet ( LPVOID Param );

class CWikiBasePage1 : public CWnd
{
public:
	CWikiBasePage1 ( );
	virtual ~CWikiBasePage1 ( );

	virtual BOOL PreCreateWindow ( CREATESTRUCT& cs );
	void CreateChildControls ( void );

	CFlatButton b_Refresh;
	CFont f_TitleButBig, f_StatusLabel;
	CEdit cMc_Line;

	//params
	BOOL isConnected = false;
	LPCSTR api_url;
protected:
	BOOL OnEraseBkgnd ( CDC* pDC );
	void OnRefreshClick ( void );
	void OnGet1Click ( void );
	//HBRUSH OnCtlColor ( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
	DECLARE_MESSAGE_MAP ( )
};
