/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* This file is part of "ABIX Project" <https://github.com/EaRLL/> (abix.group@gmail.com) (c).
*
* File: CFlatButton.h
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

class CFlatButton : public CButton
{
protected:
	void OnMouseMove ( UINT nFlags, CPoint point );
	LRESULT OnMouseLeave ( WPARAM wParam, LPARAM lParam );
	void OnLButtonDown ( UINT nFlags, CPoint point );
	void OnLButtonDblClk ( UINT nFlags, CPoint point );
	void OnLButtonUp ( UINT nFlags, CPoint point );
	BOOL OnSetCursor ( CWnd* pWnd, UINT nHitTest, UINT message );
	DECLARE_MESSAGE_MAP ( )

public:
	CFlatButton ( );
	virtual ~CFlatButton ( );
	virtual void DrawItem ( LPDRAWITEMSTRUCT /*lpDrawItemStruct*/ );

	bool m_bMouseInHouse;
	bool m_bClicked;
	HCURSOR m_Hand;

	BOOL     set_cross_onmove = TRUE;

	struct sColors
	{
		CBrush   BORDER_NORMAL;
		COLORREF   FILL_NORMAL;
		COLORREF   TEXT_NORMAL;
		CBrush   BORDER_HOVER;
		COLORREF   FILL_HOVER;
		COLORREF   TEXT_HOVER;
		CBrush   BORDER_CDOWN;
		COLORREF   FILL_CDOWN;
		COLORREF   TEXT_CDOWN;
	} *b_Colors;

	bool Draggable; // drag window {
	bool m_bMoveWindow;
	CPoint curPos;
	int aCpl;
	int aCpT; // } drag window

	bool IsClicked ( ) const
	{
		return m_bClicked;
	}
	bool IsMouseInHouse ( ) const
	{
		return m_bMouseInHouse;
	}
};
