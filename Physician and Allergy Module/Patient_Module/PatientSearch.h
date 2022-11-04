#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>

// CPatient_Search dialog
#define exportSearch _declspec(dllexport)
class exportSearch CPatientSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CPatientSearch)

public:
	CPatientSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatientSearch();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATIENT_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
	virtual BOOL OnInitDialog();
	void ResetListControl();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch();
	CString m_sPatientDetails;
	CString m_sName;
	CString m_sDob;
	CString m_sGender;
	CString m_sStatus;
	CString m_sMrn;
	CString m_sEncounter;
	CString m_sPersonId;
	CEdit m_SearchNameCtrl;
	CListCtrl m_PatientDetailsCtrl;
	afx_msg void OnNMDblclkPatientDetails(NMHDR* pNMHDR, LRESULT* pResult);
	std::vector <CString> vPatientDetails;
	CString GetPatientName();
	CString GetPatientDob();
	CString GetPatientGender();
	CString GetPatientMrn();
	CString GetPatientEncounter();
	CString GetPatientId();
};
