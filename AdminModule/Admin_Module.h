
// Admin_Module.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAdmin_ModuleApp:
// See Admin_Module.cpp for the implementation of this class
//

class CAdmin_ModuleApp : public CWinApp
{
public:
	CAdmin_ModuleApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedClosebtn();
};

extern CAdmin_ModuleApp theApp;