// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Planetary motion programView.h : interface of the CPlanetarymotionprogramView class
//

#pragma once


class CPlanetarymotionprogramView : public CView
{
	CWinThread* m_pCurrentThread;
	int m_iCounter_1;
	float m_iCounter_2;
	int radius1 = 200;
	int radius2 = 300;
	int PlanetRadius1 = 10;
	int PlanetRadius2 = 15;
	float pi = 3.14159;
	int sunX1 = 600;
	int sunX2 = 700;
	int sunY1 = 300;
	int sunY2 = 400;

protected: // create from serialization only
	CPlanetarymotionprogramView() noexcept;
	DECLARE_DYNCREATE(CPlanetarymotionprogramView)

// Attributes
public:
	int m_iCounter;
	CPlanetarymotionprogramDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPlanetarymotionprogramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonResume();
	static UINT StartThread(LPVOID Param);
};

#ifndef _DEBUG  // debug version in Planetary motion programView.cpp
inline CPlanetarymotionprogramDoc* CPlanetarymotionprogramView::GetDocument() const
   { return reinterpret_cast<CPlanetarymotionprogramDoc*>(m_pDocument); }
#endif

