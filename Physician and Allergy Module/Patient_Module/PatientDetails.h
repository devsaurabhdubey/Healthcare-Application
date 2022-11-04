#pragma once
#include "afxwin.h"
#include <vector>

// CPatientDetails dialog
#define exportPatientDetails _declspec(dllexport)
class exportPatientDetails CPatientDetails : public CDialogEx
{
	DECLARE_DYNAMIC(CPatientDetails)

public:
	//CWnd* pParent = NULL;
	CPatientDetails(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatientDetails();

	//BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_PatientDetails
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);// DDX/DDV support
	void ResetListControl();
	DECLARE_MESSAGE_MAP()
protected:
	CBrush m_brush;

public:
	afx_msg void OnAddPatientDetail();
	afx_msg void OnSearchPatientDetail();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedCancelbutton();
	void SetPatientName(CString);
	void SetPatientEncounter(CString);
	void SetPatinetMrn(CString);
	void SetPatientDob(CString);
	void setPatientId(CString);
	void SetPatientGender(CString);
	BOOL OnAllergyDetailsSearch();
	CListCtrl m_PatientListControl;
	CStatic m_NameCtrl;
	CStatic m_DobCtrl;
	CStatic m_GenderCtrl;
	CStatic m_MrnCtrl;
	CStatic m_EncounterCtrl;
	CButton m_AddButtonCtrl;
	CString m_sPersonId;
	CListCtrl m_AllergyListCtrl;
	int nPatientRowCount;
	CButton m_btCancel;
};
