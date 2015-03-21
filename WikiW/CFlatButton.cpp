/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* This file is part of "ABIX Project" <https://github.com/EaRLL/> (abix.group@gmail.com) (c).
*
* File: CFlatButton.cpp
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
#include "stdafx.h"
#include "wCore.h"
#include "wApp.h"
#include "CFlatButton.h"

BEGIN_MESSAGE_MAP ( CFlatButton, CButton )
	ON_WM_LBUTTONDOWN ( )
	ON_WM_LBUTTONDBLCLK ( )
	ON_WM_LBUTTONUP ( )
	ON_WM_SETCURSOR ( )
	ON_WM_MOUSEMOVE ( )
	ON_MESSAGE ( WM_MOUSELEAVE, OnMouseLeave )
END_MESSAGE_MAP ( )

CFlatButton::CFlatButton ( )
{
	m_bMouseInHouse = false;
	m_bClicked = false;
	Draggable = false;
	m_bMoveWindow = false;
}

CFlatButton::~CFlatButton ( )
{
}

BOOL CFlatButton::OnSetCursor ( CWnd* pWnd, UINT nHitTest, UINT message )
{
	::SetCursor ( AfxGetApp ( )->LoadStandardCursor ( IDC_HAND ) );
	return TRUE;
}

void CFlatButton::OnLButtonDblClk ( UINT nFlags, CPoint point )
{
	if ( m_bMouseInHouse && !m_bClicked )
	{
		m_bClicked = true;
		RedrawWindow ( );
		Invalidate ( );
	}
	CButton::OnLButtonDblClk ( nFlags, point );
}

void CFlatButton::OnLButtonDown ( UINT nFlags, CPoint point )
{
	m_bMoveWindow = ( Draggable ) ? true : false;

	if ( m_bMoveWindow )
	{
		GetCursorPos ( &curPos );
		aCpl = curPos.x - theApp.WindowLeft;
		aCpT = curPos.y - theApp.WindowTop;
	}

	if ( m_bMouseInHouse && !m_bClicked )
	{
		m_bClicked = true;
		RedrawWindow ( );
		Invalidate ( );
	}
	CButton::OnLButtonDown ( nFlags, point );
}

void CFlatButton::OnLButtonUp ( UINT nFlags, CPoint point )
{
	if ( m_bMoveWindow && set_cross_onmove )
	{
		::SetCursor ( AfxGetApp ( )->LoadStandardCursor ( IDC_HAND ) );
		GetParentFrame ( )->RedrawWindow ( );
	}

	m_bMoveWindow = false;

	if ( m_bMouseInHouse && m_bClicked )
	{
		m_bClicked = false;
		RedrawWindow ( );
		Invalidate ( );
	}

	CButton::OnLButtonUp ( nFlags, point );
}

void CFlatButton::OnMouseMove ( UINT nFlags, CPoint point )
{
	if ( m_bMoveWindow )
	{
		if ( set_cross_onmove )
			::SetCursor ( AfxGetApp ( )->LoadStandardCursor ( IDC_SIZEALL ) );

		GetCursorPos ( &curPos );

		theApp.WindowLeft = curPos.x - aCpl;
		theApp.WindowTop = curPos.y - aCpT;

		GetParentFrame ( )->SetWindowPos ( NULL, theApp.WindowLeft, theApp.WindowTop, theApp.WindowWidth, theApp.WindowHeight,
										   SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING );
		GetParentFrame ( )->UpdateWindow ( );
	}

	if ( !m_bMouseInHouse )
	{
		m_bMouseInHouse = true;

		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof( tme );
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;

		TrackMouseEvent ( &tme );
		RedrawWindow ( );

		Invalidate ( );
	}

	CButton::OnMouseMove ( nFlags, point );
}

LRESULT CFlatButton::OnMouseLeave ( WPARAM wParam, LPARAM lParam )
{
	ASSERT ( m_bMouseInHouse );

	m_bMouseInHouse = false;
	m_bClicked = false;
	RedrawWindow ( );
	Invalidate ( );

	return 0;
}

void CFlatButton::DrawItem ( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CDC *pDC = CDC::FromHandle ( lpDrawItemStruct->hDC );
	CRect r = lpDrawItemStruct->rcItem;

	CString text;
	GetWindowText ( text );

	bool bFocus = ( lpDrawItemStruct->itemState & ODS_FOCUS ) != 0;

	if ( IsMouseInHouse ( ) == false && IsClicked ( ) == false )
	{
		// normal
		pDC->FillSolidRect ( &r, b_Colors->FILL_NORMAL );
		pDC->SetTextColor ( b_Colors->TEXT_NORMAL );
		pDC->DrawText ( text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		pDC->FrameRect ( &r, &b_Colors->BORDER_NORMAL );

	}
	else if ( IsMouseInHouse ( ) && !IsClicked ( ) )
	{
		// hover
		pDC->FillSolidRect ( &r, b_Colors->FILL_HOVER );
		pDC->SetTextColor ( b_Colors->TEXT_HOVER );
		pDC->DrawText ( text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		pDC->FrameRect ( &r, &b_Colors->BORDER_HOVER );
	}
	else if ( IsMouseInHouse ( ) && IsClicked ( ) )
	{
		// clicked
		pDC->FillSolidRect ( &r, b_Colors->FILL_CDOWN );
		pDC->SetTextColor ( b_Colors->TEXT_CDOWN );
		pDC->DrawText ( text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		pDC->FrameRect ( &r, &b_Colors->BORDER_CDOWN );
	}
}
