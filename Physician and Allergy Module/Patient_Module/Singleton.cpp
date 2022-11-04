#include "stdafx.h"
#include "SingLeton.h"

BOOL CSingLeton::bInstanceFlag = FALSE;
CSingLeton* CSingLeton::instance = NULL;

CSingLeton::CSingLeton()
{
}

//****getInstance****
//purpose - it will allow to create only one object of the class
//arguments - none
//returns - CSingLeton *
//precondition - none
//postcondition - none
CSingLeton* CSingLeton::getInstance()
{
	if (!bInstanceFlag)
	{
		CString sConnectionString = L"Driver=Add your String";
		instance = new CSingLeton();
		bInstanceFlag = TRUE;
		instance->Open(NULL, false, false, sConnectionString);
		return instance;
	}
	else
	{
		return instance;
	}
}

BOOL CSingLeton::PatientDb(CString, CString)
{
	return 0;
}


CSingLeton::~CSingLeton()
{
	bInstanceFlag = FALSE;
}
