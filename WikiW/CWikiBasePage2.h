/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: CWikiBasePage2.h
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
