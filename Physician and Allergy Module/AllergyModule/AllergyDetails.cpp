// AllergyDetails.cpp : implementation file
//

#include "stdafx.h"
#include "Allergy_Module.h"
#include "AllergyDetails.h"
#include "afxdialogex.h"
#include <string>
#include "../Patient_Module/Conversion.h"
#include "../Allergy_Module/SingleTon.h"


IMPLEMENT_DYNAMIC(CAllergyDetails, CDialogEx)

CAllergyDetails::CAllergyDetails(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALLERGY_DETAILS, pParent)
{

}

CAllergyDetails::~CAllergyDetails()
{
}



//****OnInitDialog****
//purpose - this method will create the allergy details window and set the focus on allergy name text box
//argument - void
//return - boolean
//preconditions - none
//postconditions - none
BOOL CAllergyDetails::OnInitDialog()
{
	CDialog::OnInitDialog();
	CEdit* e = (CEdit*)GetDlgItem(IDC_ALLERGY_NAME);
	e->SetFocus();
	CWnd* pwnd = GetDlgItem(IDC_AN);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
	lf.lfWeight = 5000;
	pfont->CreateFontIndirect(&lf);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_CAT);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_SEV);
	pwnd->SetFont(pfont);			// TODO: Add extra initialization here
	pwnd = GetDlgItem(IDC_IS);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_STAT);
	pwnd->SetFont(pfont);
	return FALSE;  // return TRUE  unless you set the focus to a control
}



void CAllergyDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CATEGORY, m_CategoryCtrl);
	DDX_Control(pDX, IDC_SEVERITY, m_SeverityCtrl);
	DDX_Control(pDX, IDC_INFO_SOURCE, m_InfoSourceCtrl);
	DDX_Control(pDX, IDC_STATUS, m_StatusCtrl);
	DDX_Control(pDX, IDC_ALLERGY_NAME, m_AllergyNameCtrl);
}


BEGIN_MESSAGE_MAP(CAllergyDetails, CDialogEx)
	ON_BN_CLICKED(IDADD, &CAllergyDetails::OnBnClickedAdd)
	ON_EN_CHANGE(IDC_ALLERGY_NAME, &CAllergyDetails::OnEnChangeAllergyName)
	ON_CBN_SELCHANGE(IDC_CATEGORY, &CAllergyDetails::OnCbnSelchangeCategory)
	ON_CBN_SELCHANGE(IDC_SEVERITY, &CAllergyDetails::OnCbnSelchangeSeverity)
	ON_CBN_SELCHANGE(IDC_INFO_SOURCE, &CAllergyDetails::OnCbnSelchangeInfoSource)
	ON_CBN_SELCHANGE(IDC_STATUS, &CAllergyDetails::OnCbnSelchangeStatus)
END_MESSAGE_MAP()


// CAllergyDetails message handlers

CString sPersonId;
void CAllergyDetails::OnGetPatientId(CString personId)
{
	sPersonId = personId;
}

//****OnBnClickedAdd****
//purpose - It will insert the allergy details of patients into the database
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CAllergyDetails::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_AllergyNameCtrl.GetWindowTextLength() == 0 || m_CategoryCtrl.GetCurSel() < 0 || m_SeverityCtrl.GetCurSel() < 0 || m_InfoSourceCtrl.GetCurSel() < 0 || m_StatusCtrl < 0)
	{
		m_sMesssge.LoadString(IDS_WARNINGMESSAGE);
		m_sCaption.LoadString(IDS_WARNINGCAPTION);
		::MessageBox(NULL, m_sMesssge, m_sCaption, MB_ICONWARNING);
	}
	else
	{
		CString sAllergyName;
		m_AllergyNameCtrl.GetWindowText(sAllergyName);
		CString sAllergyCategory;
		m_CategoryCtrl.GetWindowText(sAllergyCategory);
		CString sAllergySeverity;
		m_SeverityCtrl.GetWindowText(sAllergySeverity);
		CString sAllergyInfoSource;
		m_InfoSourceCtrl.GetWindowText(sAllergyInfoSource);
		CString sAllergyStatus;
		m_StatusCtrl.GetWindowText(sAllergyStatus);

		CSingleTon* stb;
		stb = CSingleTon::getInstance();
		try
		{
			std::string sSqlString = "INSERT INTO allergies_table VALUES ('" + ConvertCStringToString(sAllergyName) + "','" + ConvertCStringToString(sAllergyCategory) + "','" + ConvertCStringToString(sAllergySeverity) + "','" + ConvertCStringToString(sAllergyInfoSource) + "','" + ConvertCStringToString(sPersonId) + "','" + ConvertCStringToString(sAllergyStatus) + "')";
			stb->ExecuteSQL(ConvertStringToCString(sSqlString));
			EndDialog(0);
		}
		catch (CDBException* e)
		{
			OutputDebugString(e->m_strError);
		}
	}
}

//****OnEnChangeAllergyName****
//purpose - it will change the font of the allergy name label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CAllergyDetails::OnEnChangeAllergyName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_AN);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_AllergyNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Allergy Name:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Allergy Name*:"));
	}
}

//****OnCbnSelchangeCategory****
//purpose - It will change the font of the allergy category label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CAllergyDetails::OnCbnSelchangeCategory()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_CAT);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_CategoryCtrl.GetCurSel();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Category:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Category*:"));
	}
}

//****OnCbnSelchangeSeverity****
//purpose - It will change the font of the allergy severity label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CAllergyDetails::OnCbnSelchangeSeverity()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_SEV);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_SeverityCtrl.GetCurSel();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Severity:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Severity*:"));
	}
}

//****OnCbnSelchangeInfoSource****
//purpose - It will change the font of the allergy info source label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CAllergyDetails::OnCbnSelchangeInfoSource()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_IS);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_CategoryCtrl.GetCurSel();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Info_Source:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Info_Source*:"));
	}
}

//****OnCbnSelchangeStatus****
//purpose - It will change the font of the allergy status label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CAllergyDetails::OnCbnSelchangeStatus()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_STAT);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_StatusCtrl.GetCurSel();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Status:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Status*:"));
	}
}
