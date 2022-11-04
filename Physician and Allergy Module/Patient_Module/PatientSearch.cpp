// Patient_Search.cpp : implementation file
//

#include "stdafx.h"
#include "Patient_Module.h"
#include "PatientSearch.h"
#include "afxdialogex.h"
#include "../Patient_Module/PatientDetails.h"
#include "../Patient_Module/UIExport.h"
#include "../Patient_Module/Singleton.h"



IMPLEMENT_DYNAMIC(CPatientSearch, CDialogEx)

CPatientSearch::CPatientSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PATIENT_SEARCH, pParent)
{
}

CPatientSearch::~CPatientSearch()
{
}

//****OnInitDialog****
//purpose - this method will create the patient search window and set the focus on search name text box
//argument - void
//return - boolean
//preconditions - none
//postconditions - none
BOOL CPatientSearch::OnInitDialog()
{
	CDialog::OnInitDialog();
	CEdit* e = (CEdit*)GetDlgItem(IDC_SEARCHNAME);
	e->SetFocus();
	return FALSE;
}


void CPatientSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCHNAME, m_SearchNameCtrl);
	DDX_Control(pDX, IDC_Patient_Details, m_PatientDetailsCtrl);
}



BEGIN_MESSAGE_MAP(CPatientSearch, CDialogEx)
	ON_BN_CLICKED(IDSEARCH, &CPatientSearch::OnBnClickedSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_Patient_Details, &CPatientSearch::OnNMDblclkPatientDetails)
END_MESSAGE_MAP()


// CPatient_Search message handlers
//****OnBnClickedSearch****
//purpose - this method will search the patient details based on the patient name
//arguments - void
//returns - void
//preconditions - None
//postconditions - None
void CPatientSearch::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
	CString sMessage;
	CString sCaption;
	CString sColumnNameLoad;
	sColumnNameLoad.LoadString(IDS_PATIENTCOLUMNNAME);
	CString sDobColumnLoad;
	sDobColumnLoad.LoadString(IDS_PATIENTDOBCOLUMN);
	CString sGenderColumnLoad;
	sGenderColumnLoad.LoadString(IDS_PATIENTGENDERCOLUMN);
	CString sStatusColumnLoad;
	sStatusColumnLoad.LoadString(IDS_PATIENTSTATUSCOLUMN);
	CString sMrnColumnLoad;
	sMrnColumnLoad.LoadString(IDS_PATIENTMRNCOLUMN);
	CString sEncounterLoad;
	sEncounterLoad.LoadString(IDS_PATIENTENCOUNTERCOLUMN);
	CString sSqlString;

	CSingLeton* st;
	st = st->getInstance();

	CString sSearchName, sLastName, sFirstName, sDOB, sGender, sStatus, sMRN, sEncounter_Type;
	ResetListControl();
	CRecordset recest(st);
	int nRowCount = 0;
	ListView_SetExtendedListViewStyle(m_PatientDetailsCtrl, LVS_EX_FULLROWSELECT);
	m_PatientDetailsCtrl.InsertColumn(0, sColumnNameLoad, LVCFMT_CENTER, 200);
	m_PatientDetailsCtrl.InsertColumn(1, sDobColumnLoad, LVCFMT_CENTER, 200);
	m_PatientDetailsCtrl.InsertColumn(2, sGenderColumnLoad, LVCFMT_CENTER, 200);
	m_PatientDetailsCtrl.InsertColumn(3, sStatusColumnLoad, LVCFMT_CENTER, 200);
	m_PatientDetailsCtrl.InsertColumn(4, sMrnColumnLoad, LVCFMT_CENTER, 200);
	m_PatientDetailsCtrl.InsertColumn(5, sEncounterLoad, LVCFMT_CENTER, 200);

	int nNameLength = m_SearchNameCtrl.GetWindowTextLength();
	if (nNameLength > 0)
	{
		m_SearchNameCtrl.GetWindowText(sSearchName);
		sSqlString = L"Select * from Person_table where firstName = '" + sSearchName + L"'";
		recest.Open(CRecordset::forwardOnly, sSqlString, CRecordset::readOnly);
		while (!recest.IsEOF())
		{
			nRowCount++;
			if (nRowCount > 0)
			{
				recest.GetFieldValue(_T("Person_ID"), m_sPersonId);
				recest.GetFieldValue(_T("lastName"), sLastName);
				recest.GetFieldValue(_T("firstName"), sFirstName);
				recest.GetFieldValue(_T("DateOfBirth"), sDOB);
				recest.GetFieldValue(_T("Sex"), sGender);
				recest.GetFieldValue(_T("Status"), sStatus);
				recest.GetFieldValue(_T("MRN"), sMRN);
				recest.GetFieldValue(_T("Encounter_Type"), sEncounter_Type);

				CString name = sFirstName + _T(" ") + sLastName;

				int irec = m_PatientDetailsCtrl.InsertItem(0, name);
				m_PatientDetailsCtrl.SetItemText(irec, 1, sDOB);
				m_PatientDetailsCtrl.SetItemText(irec, 2, sGender);
				m_PatientDetailsCtrl.SetItemText(irec, 3, sStatus);
				m_PatientDetailsCtrl.SetItemText(irec, 4, sMRN);
				m_PatientDetailsCtrl.SetItemText(irec, 5, sEncounter_Type);
			}
			recest.MoveNext();
		}
		if (nRowCount == 0)
		{
			sMessage.LoadString(IDS_DATAWARNING);
			sCaption.LoadString(IDS_WARNINGCAPTION);
			::MessageBox(this->GetSafeHwnd(), sMessage, sCaption, MB_ICONWARNING);
		}
	}
	else
	{
		sMessage.LoadString(IDS_NAMEWARNING);
		sCaption.LoadString(IDS_WARNINGCAPTION);
		::MessageBox(this->GetSafeHwnd(), sMessage, sCaption, MB_ICONWARNING);
	}
}

//****ResetListControl****
//Purpose - This method will reset the list to print the details of the searched patient
//arguments - void
//returns - void
//preconditions - none
//postconditions - none
void CPatientSearch::ResetListControl()
{
	m_PatientDetailsCtrl.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_PatientDetailsCtrl.GetDlgItem(0);
	if (pHeader)
	{
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--)
	{
		m_PatientDetailsCtrl.DeleteColumn(i);
	}
}

//****OnNMDblclkPatientDetails****
//purpose - this method will select the double clicked rows from the list
//arguments - void
//returns - void
//preconditions - None
//postconditions - None
void CPatientSearch::OnNMDblclkPatientDetails(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString sMessage;
	CString sCaption;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int row = m_PatientDetailsCtrl.GetSelectionMark();
	if (row < 0)
	{
		sMessage.LoadString(IDS_WARNINGMESSAGE);
		sCaption.LoadString(IDS_WARNINGCAPTION);
	}
	m_sName = m_PatientDetailsCtrl.GetItemText(row, 0);
	m_sDob = m_PatientDetailsCtrl.GetItemText(row, 1);
	m_sGender = m_PatientDetailsCtrl.GetItemText(row, 2);
	m_sStatus = m_PatientDetailsCtrl.GetItemText(row, 3);
	m_sMrn = m_PatientDetailsCtrl.GetItemText(row, 4);
	m_sEncounter = m_PatientDetailsCtrl.GetItemText(row, 5);
	OutputDebugString(m_sName + m_sDob + m_sGender + m_sStatus + m_sMrn + m_sEncounter);
	EndDialog(0);
}

//****GetPatientName****
//Purpose - This method will return the patient name
//argument - None
//returns - CString 
//preconditions - None
//postconditions - None
CString CPatientSearch::GetPatientName()
{
	return m_sName;
}

//****GetPatientDob****
//Purpose - This method will return the patient date of birth
//argument - None
//returns - CString 
//preconditions - None
//postconditions - None
CString CPatientSearch::GetPatientDob()
{
	return m_sDob;
}

//****GetPatientGender****
//Purpose - This method will return the patient gender
//argument - None
//returns - CString 
//preconditions - None
//postconditions - None
CString CPatientSearch::GetPatientGender()
{
	return m_sGender;
}

//****GetPatientMrn****
//Purpose - This method will return the patient mrn and set the person_id
//argument - None
//returns - CString 
//preconditions - None
//postconditions - None
CString CPatientSearch::GetPatientMrn()
{
	int rowCount = 0;
	CSingLeton* st;
	CString id;
	st = st->getInstance();
	CString sSqlString = L"Select Person_ID from Person_table where MRN = '" + m_sMrn + L"'";
	CRecordset recest(st);
	recest.Open(CRecordset::forwardOnly, sSqlString, CRecordset::readOnly);
	while (!recest.IsEOF())
	{
		rowCount++;
		if (rowCount > 0)
		{
			recest.GetFieldValue(_T("Person_ID"), id);
		}
		recest.MoveNext();
	}
	m_sPersonId = id;
	return m_sMrn;
}

//****GetPatientEncounter****
//Purpose - This method will return the patient encounter
//argument - None
//returns - CString 
//preconditions - None
//postconditions - None
CString CPatientSearch::GetPatientEncounter()
{
	return m_sEncounter;
}

//****GetPatientName****
//Purpose - This method will return the patient id
//argument - None
//returns - CString 
//preconditions - None
//postconditions - None
CString CPatientSearch::GetPatientId()
{
	return m_sPersonId;
}