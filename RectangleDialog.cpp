// RectangleDialog.cpp : implementation file
//

#include "pch.h"
#include "mfcproject1.h"
#include "afxdialogex.h"
#include "RectangleDialog.h"
#include "mfcproject1View.h"
#include "mfcproject1Doc.h"
#include "GLpolygon.h"


// RectangleDialog dialog

IMPLEMENT_DYNAMIC(RectangleDialog, CDialog)

RectangleDialog::RectangleDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RECTANGLE, pParent)
	, rectX(0)
	, rectY(0)
	, rectZ(0)
	, rectWidth(0)
	, rectHeight(0)
{
}

RectangleDialog::~RectangleDialog()
{
}

void RectangleDialog::createDialog() {
	Cmfcproject1Doc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	GLRectangle* temp = new GLRectangle[pDoc->rectangleCapacity + 1];
	for (int i = 0; i < pDoc->rectangleCapacity; ++i) {
		temp[i] = pDoc->rectangles[i];
	}

	delete[] pDoc->rectangles;
	pDoc->rectangles = temp;
	++(pDoc->rectangleCapacity);
}

void RectangleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECT_X, rectZ);
	DDX_Text(pDX, IDC_RECT_Y, rectX);
	DDX_Text(pDX, IDC_RECT_Z, rectY);
	DDX_Text(pDX, IDC_RECT_WIDTH, rectWidth);
	DDX_Text(pDX, IDC_RECT_HEIGHT, rectHeight);
	DDX_Control(pDX, IDC_RECT_NORMAL_X, rectNormalX);
	DDX_Control(pDX, IDC_RECT_NORMAL_Y, rectNormalY);
	DDX_Control(pDX, IDC_RECT_NORMAL_Z, rectNormalZ);
}


BEGIN_MESSAGE_MAP(RectangleDialog, CDialog)
	ON_BN_CLICKED(IDC_RECT_ERASE, &RectangleDialog::OnBnClickedRectErase)
END_MESSAGE_MAP()


// RectangleDialog message handlers


void RectangleDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	Cmfcproject1Doc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	UpdateData(TRUE);
	
	GLRectangle newRectangle;
	int axis;
	if (rectNormalX.GetCheck()) {
		axis = 0;
	}
	else if (rectNormalY.GetCheck()) {
		axis = 1;
	}
	else if (rectNormalZ.GetCheck()) {
		axis = 2;
	}
	else {
		MessageBox(_T("Please fill in all the needed informations."));
		return;
	}

	if (rectWidth <= 0 || rectHeight <= 0) {
		MessageBox(_T("Width and Height need to be bigger than 0."));
		return;
	}

	pDoc->rectangles[pDoc->rectangleCapacity - 1].setFourCorner(rectX, rectY, rectZ, rectWidth, rectHeight, axis);
	
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);

	createDialog();
} 


void RectangleDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	DestroyWindow();
}


void RectangleDialog::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	pView->pRectdlg = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


void RectangleDialog::OnBnClickedRectErase()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);

	rectX = 0;
	rectY = 0;
	rectZ = 0;
	rectWidth = 0;
	rectHeight = 0;
	rectNormalX.SetCheck(0);
	rectNormalY.SetCheck(0);
	rectNormalZ.SetCheck(0);
}
