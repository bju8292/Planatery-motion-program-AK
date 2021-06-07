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

// Planetary motion programView.cpp : implementation of the CPlanetarymotionprogramView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Planetary motion program.h"
#endif

#include "Planetary motion programDoc.h"
#include "Planetary motion programView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetarymotionprogramView

IMPLEMENT_DYNCREATE(CPlanetarymotionprogramView, CView)

BEGIN_MESSAGE_MAP(CPlanetarymotionprogramView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetarymotionprogramView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPlanetarymotionprogramView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CPlanetarymotionprogramView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CPlanetarymotionprogramView::OnButtonResume)
END_MESSAGE_MAP()

// CPlanetarymotionprogramView construction/destruction

CPlanetarymotionprogramView::CPlanetarymotionprogramView() noexcept
{
	m_pCurrentThread = NULL;
	m_iCounter_1 = 0;
	m_iCounter_2 = 0;
	// TODO: add construction code here

}

CPlanetarymotionprogramView::~CPlanetarymotionprogramView()
{
}

BOOL CPlanetarymotionprogramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetarymotionprogramView drawing

void CPlanetarymotionprogramView::OnDraw(CDC* pDC)
{
	CPlanetarymotionprogramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	int sunCentreX = (sunX1 + sunX2) / 2;
	int sunCentreY = (sunY1 + sunY2) / 2;
	pDC->Ellipse(sunCentreX - radius2, sunCentreY - radius2, sunCentreX + radius2, sunCentreY + radius2);
	pDC->Ellipse(sunCentreX - radius1, sunCentreY - radius1, sunCentreX + radius1, sunCentreY + radius1);
	pDC->Ellipse(sunX1, sunY1, sunX2, sunY2);

	if (m_iCounter_1 >= 0 && m_iCounter_1 <= 360)
	{
		double P_1x = sunCentreX + (cos(m_iCounter_1 * (pi / 180)) * radius1);
		double P_1y = sunCentreY + (sin(m_iCounter_1 * (pi / 180)) * radius1);
		pDC->Ellipse(P_1x - PlanetRadius1, P_1y - PlanetRadius1, P_1x + PlanetRadius1, P_1y + PlanetRadius1);
	}
	else
	{
		m_iCounter_1 = 0;
	}
	if (m_iCounter_2 >= 0 && m_iCounter_2 <= 360)
	{
		double P_2x = sunCentreX + (cos(m_iCounter_2 * (pi / 180)) * radius2);
		double P_2y = sunCentreY + (sin(m_iCounter_2 * (pi / 180)) * radius2);
		pDC->Ellipse(P_2x - PlanetRadius2, P_2y - PlanetRadius2, P_2x + PlanetRadius2, P_2y + PlanetRadius2);
	}
}


// CPlanetarymotionprogramView printing


void CPlanetarymotionprogramView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetarymotionprogramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetarymotionprogramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetarymotionprogramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetarymotionprogramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetarymotionprogramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetarymotionprogramView diagnostics

#ifdef _DEBUG
void CPlanetarymotionprogramView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetarymotionprogramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetarymotionprogramDoc* CPlanetarymotionprogramView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetarymotionprogramDoc)));
	return (CPlanetarymotionprogramDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetarymotionprogramView message handlers


void CPlanetarymotionprogramView::OnButtonStart()
{
	// TODO: Add your command handler code 
	m_pCurrentThread = AfxBeginThread(CPlanetarymotionprogramView::StartThread, this);
}


void CPlanetarymotionprogramView::OnButtonStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CPlanetarymotionprogramView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CPlanetarymotionprogramView::StartThread(LPVOID Param)
{
	CPlanetarymotionprogramView* pView = (CPlanetarymotionprogramView*)Param;
	while (true)
	{
		pView->m_iCounter_1++;
		pView->m_iCounter_2=pView->m_iCounter_2 + 0.75;
		pView->Invalidate();
		Sleep(100);
	}
	// TODO: Add your implementation code here.
	return 0;
}
