
// mfcproject1Doc.cpp : implementation of the Cmfcproject1Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfcproject1.h"
#endif

#include "mfcproject1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cmfcproject1Doc

IMPLEMENT_DYNCREATE(Cmfcproject1Doc, CDocument)

BEGIN_MESSAGE_MAP(Cmfcproject1Doc, CDocument)
END_MESSAGE_MAP()


// Cmfcproject1Doc construction/destruction

Cmfcproject1Doc::Cmfcproject1Doc() noexcept
{
	// TODO: add one-time construction code here
	points = new Point[pointCapacity];
	lines = new Line[lineCapacity];
	rectangles = new GLRectangle[rectangleCapacity];
}

Cmfcproject1Doc::~Cmfcproject1Doc()
{
	delete[] points;
	delete[] lines;
	delete[] rectangles;
}

BOOL Cmfcproject1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cmfcproject1Doc serialization

void Cmfcproject1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cmfcproject1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cmfcproject1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cmfcproject1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cmfcproject1Doc diagnostics

#ifdef _DEBUG
void Cmfcproject1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cmfcproject1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cmfcproject1Doc commands
