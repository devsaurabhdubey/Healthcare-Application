#include "stdafx.h"
#include "UIExport.h"
#include "../Patient_Module/PatientDetails.h"

//****CreateComponent****
//purpose - it will create the allergy details registration window 
//arguments - void
// returns - Boolean
//preconditions - none
//postconditions - none
BOOL CUIExport::CreateComponent()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CPatientDetails cp;
	cp.DoModal();
	return TRUE;
}
