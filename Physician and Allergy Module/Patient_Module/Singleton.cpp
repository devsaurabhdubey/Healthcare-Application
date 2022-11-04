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
		CString sConnectionString = L"Driver={Microsoft Access Driver (*.mdb)};dbq=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal\\CernerDb.mdb;defaultdir=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal;driverid=25;fil=MS Access;filedsn=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal\\CernerDb.mdb.dsn;pagetimeout=5;uid=admin;usercommitsync=Yes";
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
