
// Physician_ModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Physician_Module.h"
#include "PhysicianModuleDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "../Patient_Module/UIExport.h"
#include "../Physician_Module/Singleton.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CPhysician_ModuleDlg dialog



CPhysicianModuleDlg::CPhysicianModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHYSICIAN_MODULE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhysicianModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Username, m_UsernameCtrl);
	DDX_Control(pDX, IDC_Password, m_PasswordCtrl);
}

BEGIN_MESSAGE_MAP(CPhysicianModuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDLOGIN, &CPhysicianModuleDlg::OnBnClickedLogin)
	ON_EN_CHANGE(IDC_Username, &CPhysicianModuleDlg::OnEnChangeUsername)
	ON_EN_CHANGE(IDC_Password, &CPhysicianModuleDlg::OnEnChangePassword)
END_MESSAGE_MAP()


/* CPhysician_ModuleDlg message handlers*/
//****OnInitDialog****
//purpose - this method will create the physician login window.
//argument - void
//return - boolean
//preconditions - none
//postconditions - none
BOOL CPhysicianModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(30, 144, 255));
	CWnd* pwnd = GetDlgItem(IDC_PHYUSERNAME);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf;
	pfont->GetLogFont(&lf);
	lf.lfWeight = 5000;
	pfont->CreateFontIndirect(&lf);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_PHYPASSWORD);
	pwnd->SetFont(pfont);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPhysicianModuleDlg::OnPaint()
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
HCURSOR CPhysicianModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//****OnCtlColor****
//purpose - It will create a background color of the admin login dialog box
//arguments - CDC, CWnd, UINT
//returns - HBRUSH
//preconditions - none
//postconditions - none
HBRUSH CPhysicianModuleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CBrush m_brBack;
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT);
	hbr = ::CreateSolidBrush(RGB(30, 144, 255));
	return hbr;
}

// ***OnBnClickedLogin***
//Purpose:- This function Handles the login authentication of admin window.
//Arguments:- void
//Return Values:- void
//Preconditions:- the admin has to give all the details
//postconditions:- successful authentication will launch the patient information window
void CPhysicianModuleDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	int nRowCount = 0;
	UpdateData(TRUE);
	CString sUsername, sMessage, sCaption;
	m_UsernameCtrl.GetWindowText(sUsername);
	CString sPassword;
	m_PasswordCtrl.GetWindowText(sPassword);
	if (!sUsername.IsEmpty() && !sPassword.IsEmpty())
	{
		CString sEncryptPassword = OnEncyrptPassword(sPassword);
		CSingleton* st;
		st = st->getInstance();
		CRecordset recest(st);
		CString sSqlString = L"SELECT * from PRSNL_table where UserName='" + sUsername + L"' AND Password='" + sEncryptPassword + L"'";
		recest.Open(CRecordset::forwardOnly, sSqlString, CRecordset::readOnly);
		while (!recest.IsEOF())
		{
			nRowCount++;
			recest.MoveNext();
		}
		if (nRowCount > 0)
		{
			EndDialog(0);
			CUIExport uiexport;
			uiexport.CreateComponent();
		}
		else
		{
			sMessage.LoadString(IDS_WARNINGMESSAGE);
			sCaption.LoadString(IDS_WARNINGCAPTION);
			::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
			m_UsernameCtrl.SetWindowText(_T(""));
			m_PasswordCtrl.SetWindowText(_T(""));

		}
	}
	else
	{
		sMessage.LoadString(IDS_WARNINGMESSAGE);
		sCaption.LoadString(IDS_WARNINGCAPTION);
		::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
		m_UsernameCtrl.SetWindowText(_T(""));
		m_PasswordCtrl.SetWindowText(_T(""));

	}
}

//****OnEncyrptPassword****
//purpose - it will encrypt the physician given password.
//argument - CString password
//return - CString encrypted password
//preconditions - none
//postconditions - none
CString CPhysicianModuleDlg::OnEncyrptPassword(CString sPassword)
{
	int i = 0;
	int nLength = sPassword.GetLength() + 1;
	LPTSTR lpsz = new TCHAR[nLength];
	_tcscpy_s(lpsz, nLength, sPassword);
	OutputDebugString(lpsz);
	for (i = 0; (i < sPassword.GetLength() && sPassword[i] != '\0'); i++)
	{
		lpsz[i] = sPassword[i] + 2;
	}
	sPassword = lpsz;
	OutputDebugString(sPassword);
	return sPassword;
}

//****OnEnChangeUsername****
//purpose - It will change the font of the username label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPhysicianModuleDlg::OnEnChangeUsername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_PHYUSERNAME);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_UsernameCtrl.GetWindowTextLength();
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

//****OnEnChangePassword****
//purpose - It will change the font of the password label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPhysicianModuleDlg::OnEnChangePassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_PHYPASSWORD);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_PasswordCtrl.GetWindowTextLength();
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
