#pragma once
#include "afxdialogex.h"


// PointDialog dialog

class PointDialog : public CDialog
{
	DECLARE_DYNAMIC(PointDialog)

public:
	PointDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PointDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float point_x;
	float point_y;
	afx_msg void OnBnClickedPointErase();
	float point_z;
	virtual void OnOK();
};
