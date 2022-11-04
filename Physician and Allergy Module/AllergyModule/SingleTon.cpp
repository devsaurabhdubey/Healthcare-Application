#include "stdafx.h"
#include "SingleTon.h"


BOOL CSingleTon::bInstanceFlag = FALSE;
CSingleTon* CSingleTon::instance = NULL;


CSingleTon::CSingleTon()
{
}

//****getInstance****
//purpose - it will allow to create only one object of the class to connect the database
//arguments - none
//returns - CSingleTon *
//precondition - none
//postcondition - none
CSingleTon* CSingleTon::getInstance()
{
	if (!bInstanceFlag)
	{
		CString sConnectionString = L"Driver={Microsoft Access Driver (*Add Your String";
		instance = new CSingleTon();
		bInstanceFlag = TRUE;
		instance->Open(NULL, false, false, sConnectionString);
		return instance;
	}
	else
	{
		return instance;
	}
}

BOOL CSingleTon::OnConnectAllergyDetails(CString, CString)
{
	return 0;
}


CSingleTon::~CSingleTon()
{
	bInstanceFlag = FALSE;
}
