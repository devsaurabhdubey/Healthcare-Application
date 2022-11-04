// PhysicianRegistrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Admin_Module.h"
#include "PhysicianRegistrationDlg.h"
#include "afxdialogex.h"
#include "Singleton.h"
#include "odbcinst.h"
#include "afxdb.h"


// CPhysicianRegistrationDlg dialog
//Enables Run Time Class Access Information
//Parameter (Derived Class, Base Class)
IMPLEMENT_DYNAMIC(CPhysicianRegistrationDlg, CDialogEx)

//Window Initialization
CPhysicianRegistrationDlg::CPhysicianRegistrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHYSICIANREGISTREATION, pParent)
{

}

CPhysicianRegistrationDlg::~CPhysicianRegistrationDlg()
{
}

BOOL CPhysicianRegistrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	CComboBox *e = (CComboBox*)GetDlgItem(IDC_COMBO1);
	e->SetFocus();
	CWnd * pwnd = GetDlgItem(IDC_POSITION);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
	lf.lfWeight = 5000;
	pfont->CreateFontIndirect(&lf);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_USERNAME);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_LASTNAME);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_PHYSICIANFIRSTNAME);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_PHYSICIANPASSWORD);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_CONFIRMPASS);
	pwnd->SetFont(pfont);
	return FALSE;
}

void CPhysicianRegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_PositionCtrl);
	DDX_Control(pDX, IDC_PHYSICIANLASTNAME, m_LastNameCtrl);
	DDX_Control(pDX, IDC_FIRSTNAME, m_FirstNameCtrl);
	DDX_Control(pDX, IDC_PHYSICIANUSERNAME, m_UserNameCtrl);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordCtrl);
	DDX_Control(pDX, IDC_CONFIRMPASSWORD, m_ConfirmPasswordCtrl);
	DDX_Control(pDX, IDC_POSITION, m_Position);
	DDX_Control(pDX, IDC_LASTNAME, m_LastName);
	DDX_Control(pDX, IDC_PHYSICIANFIRSTNAME, m_FirstName);
	DDX_Control(pDX, IDC_USERNAME, m_Username);
	DDX_Control(pDX, IDC_PHYSICIANPASSWORD, m_Password);
	DDX_Control(pDX, IDC_CONFIRMPASS, m_ConfmPassword);
}


BEGIN_MESSAGE_MAP(CPhysicianRegistrationDlg, CDialogEx)
	ON_BN_CLICKED(IDREGISTER, &CPhysicianRegistrationDlg::OnBnClickedRegister)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPhysicianRegistrationDlg::OnCbnSelchangePosition)
	ON_EN_CHANGE(IDC_PHYSICIANLASTNAME, &CPhysicianRegistrationDlg::OnEnChangePhysicianlastname)
	ON_EN_CHANGE(IDC_FIRSTNAME, &CPhysicianRegistrationDlg::OnEnChangeFirstname)
	ON_EN_CHANGE(IDC_PHYSICIANUSERNAME, &CPhysicianRegistrationDlg::OnEnChangePhysicianusername)
	ON_EN_CHANGE(IDC_PASSWORD, &CPhysicianRegistrationDlg::OnEnChangePassword)
	ON_EN_CHANGE(IDC_CONFIRMPASSWORD, &CPhysicianRegistrationDlg::OnEnChangeConfirmpassword)
END_MESSAGE_MAP()


// CPhysicianRegistrationDlg message handlers

HBRUSH CPhysicianRegistrationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CBrush m_brBack;
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT);
	hbr = ::CreateSolidBrush(RGB(50, 168, 92));
	return hbr;

}
void CPhysicianRegistrationDlg::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	//int nPosition, nLastNameLength, nFirstNameLength, nUserNameLength, nPassword;
	CString sSqlString, sMessage, sCaption;
	UpdateData(TRUE);


	//nPassword = m_PasswordCtrl.GetWindowTextLength();
	CString sPhysicianPosition = ToValidatePhysicianPosition();
	CString sPhysicianLastName = ToValidatePhysicianLastName();
	CString sPhysicianFirstName = ToValidatePhysicianFirstName();
	CString sPhysicianUserName = ToValidatePhysicianUserName();
	CString sPhysicianPassword = ToValidatePhysicianPassword();

	if (sPhysicianPosition.IsEmpty()==FALSE && sPhysicianFirstName.IsEmpty()==FALSE && sPhysicianLastName.IsEmpty()==FALSE && sPhysicianUserName.IsEmpty()==FALSE)
	{
		CString sEncryptPassword = ToEncyrptPassword();
		CSingleton *st;
		st = CSingleton::getInstance();
		try
		{
			sSqlString = L"INSERT INTO PRSNL_table  VALUES ('" + sPhysicianLastName + L"',' " + sPhysicianFirstName + L"','" + sPhysicianUserName + L"','" + sEncryptPassword + L"','" + sPhysicianPosition + L"')";
			OutputDebugString(sSqlString);
			st->ExecuteSQL(sSqlString);
			::MessageBox(NULL, _T("Successfully Registered"), _T("Success"), MB_OK);
			m_PositionCtrl.SetCurSel(-1);
			m_LastNameCtrl.SetWindowText(_T(""));
			m_FirstNameCtrl.SetWindowText(_T(""));
			m_UserNameCtrl.SetWindowText(_T(""));
			m_PasswordCtrl.SetWindowText(_T(""));
			m_ConfirmPasswordCtrl.SetWindowText(_T(""));
		}
		catch (CDBException* e)
		{
			OutputDebugString(e->m_strError);
		}
	}
	else
	{
		sMessage.LoadString(IDS_DETAILSWARNINGMESSAGE);
		sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
		::MessageBox(this->GetSafeHwnd(), sMessage, sCaption, MB_ICONWARNING);
		m_PasswordCtrl.SetWindowText(_T(""));
		m_ConfirmPasswordCtrl.SetWindowText(_T(""));
		//OutputDebugString(nPosition + L"");
	}
	
}

CString CPhysicianRegistrationDlg::ToValidatePhysicianPosition()
{
	//position validation
	int nPosition = m_PositionCtrl.GetCurSel();
	CString sPosition, sPositionLoad;
	if (nPosition < 0)
	{
		CComboBox *e = (CComboBox*)GetDlgItem(IDC_COMBO1);
		e->SetFocus();
		return _T("");
	}
	else if (nPosition == 0)
	{
		sPosition = _T("Clerk");
		sPositionLoad.LoadString(IDS_PHYSICIANPOSITION);
		sPositionLoad.FormatMessage(sPositionLoad, sPosition);
		return sPositionLoad;
	}
	else if (nPosition == 1)
	{
		sPosition = _T("DBA");
		sPositionLoad.LoadString(IDS_PHYSICIANPOSITION);
		sPositionLoad.FormatMessage(sPositionLoad, sPosition);
		return sPositionLoad;
	}
	else
	{
		sPosition = _T("Nurse");
		sPositionLoad.LoadString(IDS_PHYSICIANPOSITION);
		sPositionLoad.FormatMessage(sPositionLoad, sPosition);
		return sPositionLoad;
	}
}


CString CPhysicianRegistrationDlg::ToValidatePhysicianLastName()
{
	//Last Name validation
	int nLastNameLength = m_LastNameCtrl.GetWindowTextLength();
	CString sLastName, sMessage, sCaption;
	BOOL bValidation = FALSE;
	m_LastNameCtrl.GetWindowText(sLastName);
	if (nLastNameLength == 0)
	{
		CEdit *e = (CEdit*)GetDlgItem(IDC_PHYSICIANLASTNAME);
		e->SetFocus();
		return _T("");
	}
	else
	{
		for (int i = 0; i < nLastNameLength; i++)
		{
			if (!isalpha(sLastName[i]))
			{
				bValidation = TRUE;
				break;
			}
		}
		if (bValidation == TRUE)
		{
			CEdit *e = (CEdit*)GetDlgItem(IDC_PHYSICIANLASTNAME);
			e->SetFocus();
			sMessage.LoadString(IDS_PHYSICIANNAMEWARNING);
			sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
			::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
			bValidation = FALSE;
			return _T("");
			m_PasswordCtrl.SetWindowText(_T(""));
			m_ConfirmPasswordCtrl.SetWindowText(_T(""));
		}
		else
		{
			return sLastName;	
		}
	}
}


CString CPhysicianRegistrationDlg::ToValidatePhysicianUserName()
{
	//User Name Validation
	int nUserNameLength = m_UserNameCtrl.GetWindowTextLength();
	CString sUserName,sMessage,sCaption;
	m_UserNameCtrl.GetWindowText(sUserName);
	BOOL bValidation = FALSE;

	if (nUserNameLength == 0)
	{
		CEdit *e = (CEdit*)GetDlgItem(IDC_PHYSICIANUSERNAME);
		e->SetFocus();
		m_PasswordCtrl.SetWindowText(_T(""));
		m_ConfirmPasswordCtrl.SetWindowText(_T(""));
		return _T("");
	}

	else
	{
		for (int i = 0; i < nUserNameLength; i++)
		{
			if (!isalpha(sUserName[i]))
			{
				bValidation = TRUE;
				break;
			}
		}
		if (bValidation == TRUE)
		{
			CEdit *e = (CEdit*)GetDlgItem(IDC_PHYSICIANUSERNAME);
			e->SetFocus();
			sMessage.LoadString(IDS_PHYSICIANNAMEWARNING);
			sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
			::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
			bValidation = FALSE;
			m_PasswordCtrl.SetWindowText(_T(""));
			m_ConfirmPasswordCtrl.SetWindowText(_T(""));
			return _T("");
		}
		else
		{
			return sUserName;
		}
	}
}

CString CPhysicianRegistrationDlg::ToValidatePhysicianFirstName()
{
	//First Name Validation
	int nFirstNameLength = m_FirstNameCtrl.GetWindowTextLength();
	CString sFirstName,sMessage, sCaption;
	m_FirstNameCtrl.GetWindowText(sFirstName);
	BOOL bValidation = FALSE;
	if (nFirstNameLength == 0)
	{
		CEdit *e = (CEdit*)GetDlgItem(IDC_FIRSTNAME);
		e->SetFocus();
		return _T("");
	}
	else
	{ 
		for (int i = 0; i < nFirstNameLength; i++)
		{
			if (!isalpha(sFirstName[i]))
			{
				bValidation = TRUE;
				break;
			}
		}
		if (bValidation == TRUE)
		{
			CEdit *e = (CEdit*)GetDlgItem(IDC_PHYSICIANUSERNAME);
			e->SetFocus();
			sMessage.LoadString(IDS_PHYSICIANNAMEWARNING);
			sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
			::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
			bValidation = FALSE;
			m_PasswordCtrl.SetWindowText(_T(""));
			m_ConfirmPasswordCtrl.SetWindowText(_T(""));
			return _T("");
		}
		else
		{
			return sFirstName;
		}
	}
}

CString CPhysicianRegistrationDlg::ToValidatePhysicianPassword()
{
	//password validation
	CString sPassword, sConfirmPassword, sMessage, sCaption;
	int nPasswordLength = m_PasswordCtrl.GetWindowTextLength();
	bool bHasLower = FALSE;
	bool bHasUpper = FALSE;
	bool bHasDigit = FALSE;
	bool bHasSpecialChar = FALSE;
	m_PasswordCtrl.GetWindowText(sPassword);
	m_ConfirmPasswordCtrl.GetWindowText(sConfirmPassword);
	for (int i = 0; i < nPasswordLength; i++)
	{
		if (isupper(sPassword[i]))
		{
			bHasUpper = TRUE;
		}
		if (islower(sPassword[i]))
		{
			bHasLower = TRUE;
		}
		if (isdigit(sPassword[i]))
		{
			bHasDigit = TRUE;
		}
		if (ispunct(sPassword[i]))
		{
			bHasSpecialChar = TRUE;
		}
	}
	if (bHasLower && bHasUpper && bHasDigit && bHasSpecialChar && nPasswordLength > 8)
	{

		//password and confirm password verification
		if (sPassword != sConfirmPassword)
		{
			CEdit *e = (CEdit*)GetDlgItem(IDC_PASSWORD);
			e->SetFocus();
			sMessage.LoadString(IDS_PASSWORDWARNINGMESSAGE);
			sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
			::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
			m_PasswordCtrl.SetWindowText(_T(""));
			m_ConfirmPasswordCtrl.SetWindowText(_T(""));
			return _T("");
		}
		else
		{
			return sPassword;
		}

	}
	else
	{
		CEdit *e = (CEdit*)GetDlgItem(IDC_PASSWORD);
		e->SetFocus();
		sMessage.LoadString(IDS_PASSWORD);
		sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
		::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
		return _T("");
	}
}

CString CPhysicianRegistrationDlg::ToEncyrptPassword()
{
	CString temp;
	CString sEncryptPassword;
	int i = 0;
	m_PasswordCtrl.GetWindowText(temp);
	int nLength = temp.GetLength() + 1;
	LPTSTR lpsz = new TCHAR[nLength];
	_tcscpy_s(lpsz, nLength, temp);
	OutputDebugString(lpsz);
	for (i = 0; (i < temp.GetLength() && temp[i] != '\0'); i++)
	{
		lpsz[i] = temp[i] + 2;
	}
	sEncryptPassword = lpsz;
	OutputDebugString(temp);
	return sEncryptPassword;
}




void CPhysicianRegistrationDlg::OnCbnSelchangePosition()
{
	// TODO: Add your control notification handler code here
	CWnd * pwnd = GetDlgItem(IDC_POSITION);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_PositionCtrl.GetWindowTextLength();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Position:"));
	}
	else
	{
			lf.lfWeight = 5000;
			pfont->CreateFontIndirect(&lf);
			pwnd->SetFont(pfont);
			pwnd->SetWindowTextW(_T("Position*:"));
	}
}


void CPhysicianRegistrationDlg::OnEnChangePhysicianlastname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd * pwnd = GetDlgItem(IDC_LASTNAME);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_LastNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Last Name:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Last Name*:"));
	}
}


void CPhysicianRegistrationDlg::OnEnChangeFirstname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd * pwnd = GetDlgItem(IDC_PHYSICIANFIRSTNAME);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_FirstNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("First Name:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("First Name*:"));
	}
}


void CPhysicianRegistrationDlg::OnEnChangePhysicianusername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd * pwnd = GetDlgItem(IDC_USERNAME);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_UserNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Username:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Username*:"));
	}
}


void CPhysicianRegistrationDlg::OnEnChangePassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int nLength = m_PasswordCtrl.GetWindowTextLength();
	CWnd * pwnd = GetDlgItem(IDC_PHYSICIANPASSWORD);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; 
	pfont->GetLogFont(&lf);
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Password:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Password*:"));
	}
}


void CPhysicianRegistrationDlg::OnEnChangeConfirmpassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int nLength = m_ConfirmPasswordCtrl.GetWindowTextLength();
	CWnd * pwnd = GetDlgItem(IDC_CONFIRMPASS);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Confirm Password:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Confirm Password*:"));
	}
}
