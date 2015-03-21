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
* along with WikiW.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "resource.h"
#include "CFlatButton.h"

void      xCheckVersion ( );
CRect     xGetMonitorWorkArea ( const CPoint& point );
CRect     xGetMonitorWorkArea ( CWnd* pWnd );
CRect     xGetMonitorRect ( CWnd* pWnd );
void      xCreateFastFont ( CFont& pFont, INT nHeight, INT nWeight, CString nFontName );
void      xInitFont ( CString nFontName );
CString   xGetTime ( );

/*
* Fonts: (xInitFont ( CString nFontName ))
*   Roboto
*     Roboto-Thin.ttf          # Roboto-ThinItalic.ttf          # Roboto Thin           # Roboto Thin Italic             # 100
*     Roboto-Light.ttf         # Roboto-LightItalic.ttf         # Roboto Light          # Roboto Light Italic            # 300
*     Roboto-Regular.ttf       # Roboto-Italic.ttf              # Roboto                # Roboto Italic                  # 400
*     Roboto-Medium.ttf        # Roboto-MediumItalic.ttf        # Roboto Medium         # Roboto Medium Italic           # 500
*     Roboto-Bold.ttf          # Roboto-BoldItalic.ttf          # Roboto Bold           # Roboto Bold Italic             # 700
*     Roboto-Black.ttf         # Roboto-BlackItalic.ttf         # Roboto Black          # Roboto Black Italic            # 900
*   Open Sans
*     OpenSans-Light.ttf       # OpenSans-LightItalic.ttf       # Open Sans Light       # Open Sans Light Italic         # 300
*     OpenSans-Regular.ttf     # OpenSans-Italic.ttf            # Open Sans             # Open Sans Italic               # 400
*     OpenSans-Semibold.ttf    # OpenSans-SemiboldItalic.ttf    # Open Sans Semibold    # Open Sans Semibold Italic      # 600
*     OpenSans-Bold.ttf        # OpenSans-BoldItalic.ttf        # Open Sans Bold        # Open Sans Bold Italic          # 700
*     OpenSans-ExtraBold.ttf   # OpenSans-ExtraBoldItalic.ttf   # Open Sans ExtraBold   # Open Sans Extrabold Italic     # 800
*/

class xWOptions
{
public:
	CString   m_wsPath;
	CString   m_wsVersion;
	WORD      m_wnVersion[ 4 ];

	INT       APP_WIDTH = 600;
	INT       APP_HEIGHT = 350;

	COLORREF APP_COLOR_BG = RGB ( 45, 45, 48 ); // wBase # 238, 239, 244
	CBrush   APP_COLOR_BORDER = RGB ( 0, 122, 204 ); // wBase # 75,82,92

	COLORREF APP_COLOR_TEXT = RGB ( 255, 255, 255 );
	COLORREF APP_COLOR_TEXT_BG = RGB ( 45, 45, 48 );

	struct sFlatBMainColors
	{
		CBrush   BORDER_NORMAL = RGB ( 0, 122, 204 );
		COLORREF   FILL_NORMAL = RGB ( 0, 122, 204 );
		COLORREF   TEXT_NORMAL = RGB ( 245, 245, 245 );
		CBrush   BORDER_HOVER = RGB ( 10, 132, 214 );
		COLORREF   FILL_HOVER = RGB ( 10, 132, 214 );
		COLORREF   TEXT_HOVER = RGB ( 255, 255, 255 );
		CBrush   BORDER_CDOWN = RGB ( 0, 112, 194 );
		COLORREF   FILL_CDOWN = RGB ( 0, 112, 194 );
		COLORREF   TEXT_CDOWN = RGB ( 235, 235, 235 );
	} FlatBMainColors;

	struct sFlatBGrayColors
	{
		CBrush   BORDER_NORMAL = RGB ( 50, 50, 53 );
		COLORREF   FILL_NORMAL = RGB ( 50, 50, 53 );
		COLORREF   TEXT_NORMAL = RGB ( 245, 245, 245 );
		CBrush   BORDER_HOVER = RGB ( 51, 51, 54 );
		COLORREF   FILL_HOVER = RGB ( 51, 51, 54 );
		COLORREF   TEXT_HOVER = RGB ( 255, 255, 255 );
		CBrush   BORDER_CDOWN = RGB ( 49, 49, 52 );
		COLORREF   FILL_CDOWN = RGB ( 49, 49, 52 );
		COLORREF   TEXT_CDOWN = RGB ( 235, 235, 235 );
	} FlatBGrayColors;
};

extern xWOptions so;
