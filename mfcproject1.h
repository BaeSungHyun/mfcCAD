
// mfcproject1.h : main header file for the mfcproject1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cmfcproject1App:
// See mfcproject1.cpp for the implementation of this class
//

class Cmfcproject1App : public CWinApp
{
public:
	Cmfcproject1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cmfcproject1App theApp;
