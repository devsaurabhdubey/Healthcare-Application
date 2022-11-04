#include "stdafx.h"
#include "UIExportAllergy.h"
#include "../Allergy_Module/AllergyDetails.h"

//****CreateComponent****
//purpose - it will create the allergy details registration window 
//arguments - void
// returns - void
//preconditions - none
//postconditions - none
void CUIExportAllergy::CreateComponent()
{
	CString sAllergy;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAllergyDetails allergyDetails;
	allergyDetails.DoModal();
}
