// PatientDetails.cpp : implementation file
//

#include "stdafx.h"
#include "Patient_Module.h"
#include "PatientDetails.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "../Patient_Module/PatientRegistrationDlg.h"
#include "../Allergy_Module/AllergyDetails.h"
#include "../Allergy_Module/UIExportAllergy.h"
#include "../Patient_Module/PatientSearch.h"
#include "../Patient_Module/Singleton.h"

IMPLEMENT_DYNAMIC(CPatientDetails, CDialogEx)

CPatientDetails::CPatientDetails(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PatientDetails, pParent)
{
}



CPatientDetails::~CPatientDetails()
{

}

//****OnInitDialog****
//purpose - this method will create the patient information window
//argument - void
//return - boolean
//preconditions - none
//postconditions - none
BOOL CPatientDetails::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(30, 144, 255));
	return TRUE;
}



void CPatientDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Name, m_NameCtrl);
	DDX_Control(pDX, IDC_DOB, m_DobCtrl);
	DDX_Control(pDX, IDC_Gender, m_GenderCtrl);
	DDX_Control(pDX, IDC_MRN, m_MrnCtrl);
	DDX_Control(pDX, IDC_EncounterType, m_EncounterCtrl);
	DDX_Control(pDX, IDC_ALLERGYLIST, m_AllergyListCtrl);
	DDX_Control(pDX, IDC_ADD, m_AddButtonCtrl);
	DDX_Control(pDX, IDC_CancelButton, m_btCancel);
}


BEGIN_MESSAGE_MAP(CPatientDetails, CDialogEx)
	ON_COMMAND(ID_PatientDetails_ADD, &CPatientDetails::OnAddPatientDetail)
	ON_COMMAND(ID_PatientDetails_Search, &CPatientDetails::OnSearchPatientDetail)
	ON_BN_CLICKED(IDC_ADD, &CPatientDetails::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_CancelButton, &CPatientDetails::OnBnClickedCancelbutton)
END_MESSAGE_MAP()


// CPatientDetails message handlers
//****OnCtlColor****
//purpose - It will create a background color of the admin login dialog box
//arguments - CDC, CWnd, UINT
//returns - HBRUSH
//preconditions - none
//postconditions - none
HBRUSH CPatientDetails::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CBrush m_brBack;
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT);
	hbr = ::CreateSolidBrush(RGB(30, 144, 255));
	return hbr;
}

//****OnAddPatientDetail****
//Purpose - This method will call to create the patient registration window
//argument - None
//returns - None 
//preconditions - None
//postconditions - None
void CPatientDetails::OnAddPatientDetail()
{
	// TODO: Add your command handler code here
	CPatientRegistrationDlg patientReg;
	patientReg.DoModal();
}

//****OnSearchPatientDetail****
//Purpose - This method will call to create the patient search window and set the details to the respecting fields and also activate the add button
//argument - None
//returns - None 
//preconditions - None
//postconditions - None
void CPatientDetails::OnSearchPatientDetail()
{
	// TODO: Add your command handler code here
	CPatientSearch patientSearch;
	patientSearch.DoModal();
	SetPatientName(patientSearch.GetPatientName());
	SetPatientEncounter(patientSearch.GetPatientEncounter());
	SetPatientDob(patientSearch.GetPatientDob());
	SetPatientGender(patientSearch.GetPatientGender());
	SetPatinetMrn(patientSearch.GetPatientMrn());
	m_sPersonId = patientSearch.GetPatientId();
	setPatientId(m_sPersonId);
	m_AddButtonCtrl.EnableWindow(TRUE);
	m_AllergyListCtrl.GetSelectedColumn();
}



//****OnAllergyDetailsSearch****
//Purpose - This method will search the details of allergy of the selected person
//argument - None
//returns - boolean 
//preconditions - None
//postconditions - None
BOOL CPatientDetails::OnAllergyDetailsSearch()
{
	CString sMessage;
	CString sCaption;
	int nAllergyRowCount = 0;
	int irec = 0;
	CString sAllergyId, sAllergyName, sCategory, sSeverity, sInfo_Source, sStatus, sPersonId;
	ResetListControl();
	sAllergyName.LoadString(IDS_ALLERGYNAME);
	sCategory.LoadString(IDS_ALLERGYCATEGORY);
	sSeverity.LoadString(IDS_ALLERGYSEVERITY);
	sInfo_Source.LoadString(IDS_ALLERGYSOURCE);
	sStatus.LoadString(IDS_ALLERGYSTATUS);
	ListView_SetExtendedListViewStyle(m_AllergyListCtrl, LVS_EX_GRIDLINES);
	m_AllergyListCtrl.InsertColumn(0, sAllergyName, LVCFMT_CENTER, 200);
	m_AllergyListCtrl.InsertColumn(1, sCategory, LVCFMT_CENTER, 200);
	m_AllergyListCtrl.InsertColumn(2, sSeverity, LVCFMT_CENTER, 200);
	m_AllergyListCtrl.InsertColumn(3, sInfo_Source, LVCFMT_CENTER, 200);
	m_AllergyListCtrl.InsertColumn(4, sStatus, LVCFMT_CENTER, 200);

	CSingLeton* st;
	st = CSingLeton::getInstance();
	if (!m_sPersonId.IsEmpty())
	{
		try
		{
			CRecordset recest(st);
			CString sSqlString = L"Select * from allergies_table where Person_ID = '" + m_sPersonId + L"'";
			recest.Open(CRecordset::forwardOnly, sSqlString, CRecordset::readOnly);
			while (!recest.IsEOF())
			{
				nAllergyRowCount++;
				if (nAllergyRowCount > 0)
				{
					recest.GetFieldValue(_T("Allergy_Id"), sAllergyId);
					recest.GetFieldValue(_T("Allergy_Name"), sAllergyName);
					recest.GetFieldValue(_T("Category"), sCategory);
					recest.GetFieldValue(_T("Severity"), sSeverity);
					recest.GetFieldValue(_T("Info_Source"), sInfo_Source);
					recest.GetFieldValue(_T("Person_ID"), sPersonId);
					recest.GetFieldValue(_T("Status"), sStatus);

					irec = m_AllergyListCtrl.InsertItem(0, sAllergyName);
					m_AllergyListCtrl.SetItemText(irec, 1, sCategory);
					m_AllergyListCtrl.SetItemText(irec, 2, sSeverity);
					m_AllergyListCtrl.SetItemText(irec, 3, sInfo_Source);
					m_AllergyListCtrl.SetItemText(irec, 4, sStatus);
					recest.MoveNext();
				}
			}
			if (nAllergyRowCount == 0)
			{
				sMessage.LoadString(IDS_ALLERGYDATA);
				sCaption.LoadString(IDS_WARNINGCAPTION);
				::MessageBox(this->GetSafeHwnd(), sMessage, sCaption, MB_ICONWARNING);
			}
		}
		catch (CDBException* e)
		{
			OutputDebugString(e->m_strError);
		}
	}
	return 0;
}

//****ResetListControl****
//Purpose - This method will reset the list of the allergy 
//argument - void
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::ResetListControl()
{
	m_AllergyListCtrl.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_AllergyListCtrl.GetDlgItem(0);
	if (pHeader)
	{
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--)
	{
		m_AllergyListCtrl.DeleteColumn(i);
	}
}

//****OnBnClickedAdd****
//Purpose - This method will send the person id first to the allergy detail class and then it will call UIExportAllergy class to create the allergy details window 
//argument - void
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::OnBnClickedAdd()
{
	CAllergyDetails allergyDetails;
	allergyDetails.OnGetPatientId(m_sPersonId);
	CUIExportAllergy exportAllergy;
	exportAllergy.CreateComponent();
	OnAllergyDetailsSearch();
}

//****OnBnClickedCancelbutton****
//Purpose - This method will close the patient information window
//argument - void
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::OnBnClickedCancelbutton()
{
	/* TODO: Add your control notification handler code here*/
	EndDialog(0);
}

//****SetPatientName****
//Purpose - This method will set the patient name in the patient information
//argument - CString
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::SetPatientName(CString sPatient)
{
	m_NameCtrl.SetWindowText(sPatient);
}

//****SetPatientEncounter****
//Purpose - this method will set the patient encounter type in the patient information
//argument - CString
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::SetPatientEncounter(CString sEncounter)
{
	m_EncounterCtrl.SetWindowText(sEncounter);
}

//****SetPatientMrn****
//Purpose - this method will set the patient mrn in the patient information
//argument - CString
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::SetPatinetMrn(CString sMrn)
{
	m_MrnCtrl.SetWindowText(sMrn);
}

//****SetPatientDob****
//Purpose - this method will set the patient date of birth in the patient information
//argument - CString
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::SetPatientDob(CString sDob)
{
	m_DobCtrl.SetWindowText(sDob);
}

//****SetPatientGender****
//Purpose - this method will set the patient gender in the patient information
//argument - CString
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::SetPatientGender(CString sGender)
{
	m_GenderCtrl.SetWindowText(sGender);
}

//****setPatientId****
//Purpose - this method will send the person id to search the details of allergy
//argument - CString
//returns - void 
//preconditions - None
//postconditions - None
void CPatientDetails::setPatientId(CString sPersonId)
{
	OnAllergyDetailsSearch();
}
