// PointDialog.cpp : implementation file
//

#include "pch.h"
#include "mfcproject1.h"
#include "afxdialogex.h"
#include "PointDialog.h"


// PointDialog dialog

IMPLEMENT_DYNAMIC(PointDialog, CDialog)

PointDialog::PointDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_POINT, pParent)
	, point_x(0)
	, point_y(0)
	, point_z(0)
{

}

PointDialog::~PointDialog()
{
}

void PointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_POINT_X, point_z);
	DDX_Text(pDX, IDC_POINT_Y, point_x);
	DDX_Text(pDX, IDC_POINT_Z, point_y);
}


BEGIN_MESSAGE_MAP(PointDialog, CDialog)
	ON_BN_CLICKED(IDC_POINT_ERASE, &PointDialog::OnBnClickedPointErase)
END_MESSAGE_MAP()




void PointDialog::OnBnClickedPointErase()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	point_x = 0;
	point_y = 0;
	point_z = 0;
}


void PointDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::OnOK();
}
