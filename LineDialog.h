#pragma once
#include "afxdialogex.h"



// LineDialog dialog
class Cmfcproject1View; // 참조 클래스 선언
class Cmfcproject1Doc;

class LineDialog : public CDialog
{
	DECLARE_DYNAMIC(LineDialog)

public:
	LineDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LineDialog();

	void createDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public: 
	Cmfcproject1View* pView{nullptr};
	float lineX;
	float lineY;
	float lineZ;
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedLineErase();
};
