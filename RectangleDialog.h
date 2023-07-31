#pragma once
#include "afxdialogex.h"

class Cmfcproject1View;
class Cmfcproject1Doc;
// RectangleDialog dialog

class RectangleDialog : public CDialog
{
	DECLARE_DYNAMIC(RectangleDialog)

public:
	RectangleDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RectangleDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECTANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	Cmfcproject1View* pView{ nullptr };
	float rectX;
	float rectY;
	float rectZ;
	float rectWidth;
	float rectHeight;
	CButton rectNormalX;
	CButton rectNormalY;
	CButton rectNormalZ;
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedRectErase();

	void createDialog();
};
