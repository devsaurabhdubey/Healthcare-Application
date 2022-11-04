// Allergy_Module.h : main header file for the Allergy_Module DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAllergy_ModuleApp
// See Allergy_Module.cpp for the implementation of this class
//

class CAllergy_ModuleApp : public CWinApp
{
public:
	CAllergy_ModuleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
