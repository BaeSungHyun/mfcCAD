// LineDialog.cpp : implementation file
//

#include "pch.h"
#include "mfcproject1.h"
#include "afxdialogex.h"
#include "LineDialog.h"
#include "mfcproject1View.h"
#include "mfcproject1Doc.h"
#include "GLprimitive.h"
#include "MainFrm.h"

// LineDialog dialog

IMPLEMENT_DYNAMIC(LineDialog, CDialog)

LineDialog::LineDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LINE, pParent)
	, lineX(0)
	, lineY(0)
	, lineZ(0)
{
}

LineDialog::~LineDialog()
{
}

void LineDialog::createDialog() {
	Cmfcproject1Doc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Line* temp = new Line[pDoc->lineCapacity + 1];
	for (int i = 0; i < pDoc->lineCapacity; ++i) {
		temp[i] = pDoc->lines[i];
	}
	delete[] pDoc->lines; // member variable point* gets deleted which is still connected to 
	// temp[i] in above line
	pDoc->lines = temp;
	++(pDoc->lineCapacity);
}

void LineDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE_X, lineX);
	DDX_Text(pDX, IDC_LINE_Y, lineZ);
	DDX_Text(pDX, IDC_LINE_Z, lineY);
}


BEGIN_MESSAGE_MAP(LineDialog, CDialog)
	ON_BN_CLICKED(IDC_LINE_ERASE, &LineDialog::OnBnClickedLineErase)
END_MESSAGE_MAP()


// LineDialog message handlers
// Always think that super class is bypassed because
// we're calling by heap and 'new' and 'create'

void LineDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	Cmfcproject1Doc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// CDialog::OnOK();
	// Mandatory to override. 
	UpdateData(TRUE); // Activate DDX directly and manually

	Point newPoint;
	newPoint.setPoint(lineX, lineY, lineZ);

	pDoc->lines[pDoc->lineCapacity - 1].pushPoint(newPoint);

	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
}


void LineDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	// CDialog::OnCancel();
	DestroyWindow();
}


void LineDialog::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	pView->pLinedlg = NULL;
	delete this;
	// CDialog::PostNcDestroy();
}


void LineDialog::OnBnClickedLineErase()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);

	lineX = 0;
	lineY = 0;
	lineZ = 0;
}
