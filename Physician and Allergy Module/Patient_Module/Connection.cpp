#include "stdafx.h"
#include "Connection.h"
#include "../Patient_Module/PatientDetails.h"


CConnection::CConnection()
{
}


CConnection::~CConnection()
{
}
BOOL CConnection::Create()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CPatientDetails cp;
	cp.DoModal();
	return TRUE;
}
