#pragma once
#include "afxwin.h"

#define exportConnection _declspec(dllexport)
class exportConnection CUIExport
{
public:
	BOOL CreateComponent();
};

