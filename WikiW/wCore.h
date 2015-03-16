/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: wCore.h
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
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "resource.h"
#include "CFlatButton.h"

void      xCheckVersion ( );
CRect     xGetMonitorWorkArea ( const CPoint& point );
CRect     xGetMonitorWorkArea ( CWnd* pWnd );
CRect     xGetMonitorRect ( CWnd* pWnd );
void      xCreateFastFont ( CFont& pFont, INT nHeight, INT nWeight, CString nFontName );
CString   xGetTime ( );

class xWOptions
{
public:
	CString   m_wsPath;
	CString   m_wsVersion;
	WORD      m_wnVersion[ 4 ];

	INT       APP_WIDTH = 600;
	INT       APP_HEIGHT = 350;

	COLORREF SKIN_COLOR_APP_BG = RGB ( 45, 45, 48 ); // wBase
	CBrush   SKIN_COLOR_APP_BORDER = RGB ( 0, 122, 204 ); // wBase

	BOOL     OPT_FBTN_SET_CROSS_ONMOVE     = TRUE; // CFlatButton
	CBrush   SKIN_COLOR_FBTN_BORDER_NORMAL = RGB ( 0, 122, 204 ); // CFlatButton
	COLORREF   SKIN_COLOR_FBTN_FILL_NORMAL = RGB ( 0, 122, 204 ); // CFlatButton
	COLORREF   SKIN_COLOR_FBTN_TEXT_NORMAL = RGB ( 245, 245, 245 ); // CFlatButton
	CBrush   SKIN_COLOR_FBTN_BORDER_HOVER  = RGB ( 10, 132, 214 ); // CFlatButton
	COLORREF   SKIN_COLOR_FBTN_FILL_HOVER  = RGB ( 10, 132, 214 ); // CFlatButton
	COLORREF   SKIN_COLOR_FBTN_TEXT_HOVER  = RGB ( 255, 255, 255 ); // CFlatButton
	CBrush   SKIN_COLOR_FBTN_BORDER_CDOWN  = RGB ( 0, 112, 194 ); // CFlatButton
	COLORREF   SKIN_COLOR_FBTN_FILL_CDOWN  = RGB ( 0, 112, 194 ); // CFlatButton
	COLORREF   SKIN_COLOR_FBTN_TEXT_CDOWN  = RGB ( 235, 235, 235 ); // CFlatButton
};

extern xWOptions so;