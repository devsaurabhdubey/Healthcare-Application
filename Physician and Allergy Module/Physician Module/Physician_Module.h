
// Physician_Module.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhysician_ModuleApp:
// See Physician_Module.cpp for the implementation of this class
//

class CPhysician_ModuleApp : public CWinApp
{
public:
	CPhysician_ModuleApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPhysician_ModuleApp theApp;