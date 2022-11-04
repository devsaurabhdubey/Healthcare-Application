
// Admin_ModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Admin_Module.h"
#include "Admin_ModuleDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "PhysicianRegistrationDlg.h"
#include "Singleton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdmin_ModuleDlg dialog



CAdmin_ModuleDlg::CAdmin_ModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADMIN_MODULE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdmin_ModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMINUSERNAME, m_AdminUserNameCtrl);
	DDX_Control(pDX, IDC_ADMINPASSWORD, m_AdminPasswordCtrl);

	DDX_Control(pDX, IDC_USERNAME, staticUsername);
	DDX_Control(pDX, IDC_PASSWORD, staticPassword);
}

BEGIN_MESSAGE_MAP(CAdmin_ModuleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDLOGIN, &CAdmin_ModuleDlg::OnBnClickedLogin)
	ON_EN_CHANGE(IDC_ADMINPASSWORD, &CAdmin_ModuleDlg::OnEnChangeAdminpassword)
	ON_EN_CHANGE(IDC_ADMINUSERNAME, &CAdmin_ModuleDlg::OnEnChangeAdminusername)
	ON_BN_CLICKED(IDC_CLOSEBTN, &CAdmin_ModuleDlg::OnBnClickedClosebtn)
//	ON_NOTIFY(BCN_DROPDOWN, IDC_CLOSEBTN, &CAdmin_ModuleDlg::OnDropdownClosebtn)
END_MESSAGE_MAP()


// CAdmin_ModuleDlg message handlers

BOOL CAdmin_ModuleDlg::OnInitDialog()
{
	
		CDialogEx::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(30,144,255));
	CEdit *e = (CEdit*)GetDlgItem(IDC_ADMINUSERNAME);
	e->SetFocus();
	CWnd * pwnd = GetDlgItem(IDC_PASSWORD);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
	lf.lfWeight = 5000;
	pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_USERNAME);
	
		pwnd->SetFont(pfont);
		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);
	// Set small icon
	// TODO: Add extra initialization here
	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAdmin_ModuleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAdmin_ModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CAdmin_ModuleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CBrush m_brBack;
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT);
	hbr = ::CreateSolidBrush(RGB(160, 250,191));
	return hbr;
}

void CAdmin_ModuleDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sSqlString;
	int nRowCount = 0;
	CString sUsername, sPassword;
	CString sMessage;
	CString sCaption;
	m_AdminPasswordCtrl.GetWindowText(sPassword);
	m_AdminUserNameCtrl.GetWindowText(sUsername);
	

	if (!sUsername.IsEmpty() && !sPassword.IsEmpty())
	{
		try
		{
			CSingleton *st;
			st = CSingleton::getInstance();
			CRecordset recest(st);
			sSqlString = L"SELECT * from admin_credentials where admin_username='" + sUsername + L"' AND admin_password='" + sPassword + L"'";
			recest.Open(CRecordset::forwardOnly, sSqlString, CRecordset::readOnly);
			while (!recest.IsEOF())
			{
				nRowCount++;
				recest.MoveNext();
			}
			OutputDebugString(nRowCount + L"");
			if (nRowCount > 0)
			{
				EndDialog(0);
				nRowCount = 0;
				CPhysicianRegistrationDlg physicianDlg;
				physicianDlg.DoModal();
			}
			else
			{
				sMessage.LoadString(IDS_WARNINGMESSAGE);
				sCaption.LoadString(IDS_DETIALWARNINGCAPTION);
				::MessageBox(this->GetSafeHwnd(), sMessage, sCaption, MB_ICONWARNING);
			
				m_AdminUserNameCtrl.SetWindowText(_T(""));
				m_AdminPasswordCtrl.SetWindowText(_T(""));
			}
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
	}
}



void CAdmin_ModuleDlg::OnEnChangeAdminpassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
	int nLength = m_AdminPasswordCtrl.GetWindowTextLength();
	CWnd * pwnd = GetDlgItem(IDC_PASSWORD);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
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





void CAdmin_ModuleDlg::OnEnChangeAdminusername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd * pwnd = GetDlgItem(IDC_USERNAME);
	CFont * pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_AdminUserNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
ds		pfont->CreateFontIndirect(&lf);
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


void CAdmin_ModuleDlg::OnBnClickedClosebtn()
{
	CDialogEx::OnCancel();
	// TODO: Add your control notification handler code here
}


//void CAdmin_ModuleDlg::OnDropdownClosebtn(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}
