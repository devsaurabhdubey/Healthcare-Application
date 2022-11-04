
#include "stdafx.h"
#include "ConnectAllergy.h"
#include "../Allergy_Module/AllergyDetails.h"

void CConnectAllergy::Create()
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAllergyDetails cad;
	cad.DoModal();
}



CConnectAllergy::~CConnectAllergy()
{

}



