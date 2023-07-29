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

void RectangleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECT_X, rectX);
	DDX_Text(pDX, IDC_RECT_Y, rectY);
	DDX_Text(pDX, IDC_RECT_Z, rectZ);
	DDX_Text(pDX, IDC_RECT_WIDTH, rectWidth);
	DDX_Text(pDX, IDC_RECT_HEIGHT, rectHeight);
	DDX_Control(pDX, IDC_RECT_NORMAL_X, rectNormalX);
	DDX_Control(pDX, IDC_RECT_NORMAL_Y, rectNormalY);
	DDX_Control(pDX, IDC_RECT_NORMAL_Z, rectNormalZ);
}


BEGIN_MESSAGE_MAP(RectangleDialog, CDialog)
END_MESSAGE_MAP()


// RectangleDialog message handlers
