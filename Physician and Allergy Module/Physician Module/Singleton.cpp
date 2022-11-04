#include "..\Patient_Module\Singleton.h"
#include "stdafx.h"
#include "Singleton.h"

BOOL CSingleton::bInstanceFlag = FALSE;
CSingleton* CSingleton::instance = NULL;


CSingleton::CSingleton()
{
}

//****getInstance****
//purpose - it will allow to create only one object of the class
//arguments - none
//returns - Boolean
//precondition - none
//postcondition - none
CSingleton* CSingleton::getInstance()
{
	if (!bInstanceFlag)
	{
		CString sConnectionString = L"Add your String";
		instance = new CSingleton();
		bInstanceFlag = TRUE;
		instance->Open(NULL, false, false, sConnectionString);
		return instance;
	}
	else
	{
		return instance;
	}
}

BOOL CSingleton::PhysicianDb(CString, CString)
{
	return 0;
}


CSingleton::~CSingleton()
{
	bInstanceFlag = FALSE;
}
