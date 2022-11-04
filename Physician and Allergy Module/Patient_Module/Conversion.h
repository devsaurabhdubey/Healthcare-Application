#pragma once
#include "afxwin.h"
#include <string>

#define exportConvert _declspec(dllexport)
std::string exportConvert ConvertCStringToString(CString csTempCString)
{
	CT2CA pszTempZeroTerminatedStringPointer(csTempCString);
	std::string sTempString(pszTempZeroTerminatedStringPointer);
	return sTempString;
}

CString exportConvert ConvertStringToCString(std::string sTempString)
{
	CString csTempCString(sTempString.c_str());
	return csTempCString;
}

CString exportConvert ConvertIntToCString(int iTempInt)
{
	CString csTempCString;
	csTempCString.Format(_T("%d"), iTempInt);
	return csTempCString;
}