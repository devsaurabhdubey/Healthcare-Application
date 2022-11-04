#pragma once
#include "afxwin.h"


// CAllergyDetails dialog
#define exportAllergyDetails _declspec(dllexport)
class exportAllergyDetails CAllergyDetails : public CDialogEx
{
	DECLARE_DYNAMIC(CAllergyDetails)

public:
	CAllergyDetails(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAllergyDetails();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALLERGY_DETAILS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	void OnGetPatientId(CString personId);
	CString m_sMesssge;
	CString m_sCaption;
	CComboBox m_CategoryCtrl;
	CComboBox m_SeverityCtrl;
	CComboBox m_InfoSourceCtrl;
	CComboBox m_StatusCtrl;
	CEdit m_AllergyNameCtrl;
	afx_msg void OnEnChangeAllergyName();
	afx_msg void OnCbnSelchangeCategory();
	afx_msg void OnCbnSelchangeSeverity();
	afx_msg void OnCbnSelchangeInfoSource();
	afx_msg void OnCbnSelchangeStatus();
};
