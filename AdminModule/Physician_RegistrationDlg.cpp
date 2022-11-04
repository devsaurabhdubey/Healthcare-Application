// Physician_RegistrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Admin_Module.h"
#include "Physician_RegistrationDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include <string.h>


// CPhysician_RegistrationDlg dialog

IMPLEMENT_DYNAMIC(CPhysician_RegistrationDlg, CDialogEx)

CPhysician_RegistrationDlg::CPhysician_RegistrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Physician_Registration, pParent)
	, m_sLastName(_T(""))
	, m_sFirstName(_T(""))
	, m_sUserName(_T(""))
	, m_sPassword(_T(""))
	, m_sConfirmPassword(_T(""))
{
	m_buttonCtrl.EnableWindow(FALSE);

}

CPhysician_RegistrationDlg::~CPhysician_RegistrationDlg()
{
}

void CPhysician_RegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Position, m_Position_control);
	DDX_Text(pDX, IDC_Last_Name, m_sLastName);
	DDX_Text(pDX, IDC_First_Name, m_sFirstName);
	DDX_Text(pDX, IDC_Username, m_sUserName);
	DDX_Text(pDX, IDC_Password, m_sPassword);
	DDX_Text(pDX, IDC_Confirm_Password, m_sConfirmPassword);
	DDX_Control(pDX, IDOK, m_buttonCtrl);
	DDX_Control(pDX, IDC_Confirm_Password, m_ConfirmPasswordctrl);
	DDX_Control(pDX, IDC_Password, m_PasswordCtrl);
	DDX_Control(pDX, IDC_Last_Name, m_LastNameCtrl);
	DDX_Control(pDX, IDC_First_Name, m_FirstnameCtrl);
	DDX_Control(pDX, IDC_Username, m_UserNameCtrl);
}

BOOL CPhysician_RegistrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

		m_buttonCtrl.EnableWindow(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPhysician_RegistrationDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPhysician_RegistrationDlg::OnBnClickedRegister)
	ON_EN_CHANGE(IDC_Confirm_Password, &CPhysician_RegistrationDlg::OnEnChangeConfirmPassword)
END_MESSAGE_MAP()


// CPhysician_RegistrationDlg message handlers

void CPhysician_RegistrationDlg::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	CDatabase dataBase;
	CString sSqlString;
	CString sConnectionString = L"ODBC;DSN=localdb;Integrated Security=True;Connect Timeout=15";
	dataBase.Open(NULL, TRUE, TRUE, sConnectionString);
	UpdateData(TRUE);
	m_nPosition = m_Position_control.GetCurSel();
	m_nLastNameLength = m_LastNameCtrl.GetWindowTextLength();
	m_nFirstNameLength = m_FirstnameCtrl.GetWindowTextLength();
	m_nUserNameLength = m_UserNameCtrl.GetWindowTextLength();
	BOOL bPhysicianPosition = ToValidatePhysicianPosition(m_nPosition);
	BOOL bPhysicianLastName = ToValidatePhysicianLastName(m_nLastNameLength);
	BOOL bPhysicianFirstName = ToValidatePhysicianFirstName(m_nFirstNameLength);
	BOOL bPhysicianUserName = ToValidatePhysicianUserName(m_nUserNameLength);
	BOOL bPhysicianPassword = ToValidatePhysicianPassword();
	OutputDebugString(m_nPosition+L"");
	if (m_nPosition >= 0)
	{
			if (bPhysicianPosition && bPhysicianLastName  && bPhysicianPassword && bPhysicianFirstName && bPhysicianUserName)
			{
				BOOL bEncrypt = ToEncyrptPassword();
				try
				{
					sSqlString = L"INSERT INTO PRSNL_table  VALUES ('" + m_sLastName + L"',' " + m_sFirstName + L"','" + m_sUserName + L"','" + m_sPassword + L"','" + m_sPosition + L"')";
					OutputDebugString(sSqlString);
					dataBase.ExecuteSQL(sSqlString);
					dataBase.Close();
				}
				catch (CDBException* e)
				{
					OutputDebugString(e->m_strError);
				}
			}
			else 
			{
				::MessageBox(NULL, _T("Enter the details properly"), _T("Warning"), MB_ICONWARNING);
			}
	}
	else
	{
		::MessageBox(NULL, _T("Enter  the position"), _T("Warning"), MB_ICONWARNING);
	}
	//CDialogEx::OnOK();
}

BOOL CPhysician_RegistrationDlg::ToValidatePhysicianPosition(int m_nPosition)
{
	//position validation
	if (m_nPosition == 0)
	{
		m_sPosition = _T("Clerk");
	}
	else if (m_nPosition == 1)
	{
		m_sPosition = _T("DBA");
	}
	else
	{
		m_sPosition = _T("Nurse");
	}
	return TRUE;
}

BOOL CPhysician_RegistrationDlg::ToValidatePhysicianLastName(int m_nLastNameLength)
{
	//Last Name validation

	if (m_nLastNameLength > 0)
	{
		for (int i = 0; i < m_nLastNameLength; i++)
		{
			if (!isalpha(m_sLastName[i]))
			{
				m_bValidation = TRUE;
				break;
			}
		}
		if (m_bValidation == TRUE)
		{
			::MessageBox(NULL, _T("Enter the characters only"), _T("Warning"), MB_ICONWARNING);
			m_bValidation = FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CPhysician_RegistrationDlg::ToValidatePhysicianUserName(int m_nUserNameLength)
{
	//User Name Validation
	if (m_nUserNameLength > 0)
	{
		for (int i = 0; i < m_nUserNameLength; i++)
		{
			if (!isalpha(m_sUserName[i]))
			{
				m_bValidation = TRUE;
				break;
			}
		}
		if (m_bValidation == TRUE)
		{
			::MessageBox(NULL, _T("Enter the characters only"), _T("Warning"), MB_ICONWARNING);
			m_bValidation = FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CPhysician_RegistrationDlg::ToValidatePhysicianFirstName(int m_nFirstNameLength)
{

	if (m_nFirstNameLength > 0)
	{
		for (int i = 0; i < m_nFirstNameLength; i++)
		{
			if (!isalpha(m_sFirstName[i]))
			{
				m_bValidation = TRUE;
				break;
			}
		}
		if (m_bValidation == TRUE)
		{
			::MessageBox(NULL, _T("Enter the characters only"), _T("Warning"), MB_ICONWARNING);
			m_bValidation = FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CPhysician_RegistrationDlg::ToValidatePhysicianPassword()
{
	//password validation
	int nPasswordLength = m_sPassword.GetLength();
	bool bHasLower = FALSE;
	bool bHasUpper = FALSE;
	bool bHasDigit = FALSE;
	bool bHasSpecialChar = FALSE;
	
	for (int i = 0; i < nPasswordLength; i++)
	{
		if (isupper(m_sPassword[i]))
		{
			bHasUpper = TRUE;
		}
		if (islower(m_sPassword[i]))
		{
			bHasLower = TRUE;
		}
		if (isdigit(m_sPassword[i]))
		{
			bHasDigit = TRUE;
		}
		if (ispunct(m_sPassword[i]))
		{
			bHasSpecialChar = TRUE;
		}
	}
	if (bHasLower && bHasUpper && bHasDigit && bHasSpecialChar && nPasswordLength > 8)
	{
		return TRUE;
	}
	else
	{
		::MessageBox(NULL, _T("Enter a password with a combination of lower, higher alphabets, number and special characters"), _T("Warning"), MB_ICONWARNING);
		return FALSE;
	}

	//password and confirm password verification
	if (m_sPassword != m_sConfirmPassword)
	{
		::MessageBox(NULL, _T("Password Doesn't match"), _T("Warning"), MB_ICONWARNING);
		return FALSE;
	}
}


void CPhysician_RegistrationDlg::OnEnChangeConfirmPassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString temp;
	m_ConfirmPasswordctrl.GetWindowText(temp);
	if (temp.GetLength()>0)
	{
		m_buttonCtrl.EnableWindow(TRUE);
	}
	else 
	{
		m_buttonCtrl.EnableWindow(FALSE);
	}
}

BOOL CPhysician_RegistrationDlg::ToEncyrptPassword()
{
	CString temp;
	int i = 0;
	m_PasswordCtrl.GetWindowText(temp);
	int nLength = temp.GetLength() + 1;
	char cString[256];
	LPTSTR lpsz = new TCHAR[nLength];
	_tcscpy_s(lpsz, nLength, temp);
	OutputDebugString(lpsz);
	
	for (i = 0; (i < temp.GetLength() && m_sPassword[i] != '\0'); i++)
	{
		lpsz[i] = m_sPassword[i] + 2;
	}
	m_sPassword = lpsz;
	OutputDebugString(m_sPassword);
	return 0;
}
