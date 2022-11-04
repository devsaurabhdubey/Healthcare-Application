// Patient_Module.h : main header file for the Patient_Module DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPatient_ModuleApp
// See Patient_Module.cpp for the implementation of this class
//
#define exportPatientModule _declspec(dllexport)

class exportPatientModule CPatient_ModuleApp : public CWinApp
{
public:
	CPatient_ModuleApp();

	// Overrides
public:
	virtual BOOL InitInstance();
	CStatic m_StaticCtrl;
	CEdit m_TextBoxCtrl;
	CButton m_ButtonCtrl;
	DECLARE_MESSAGE_MAP()
};
