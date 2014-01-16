// InputPassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "InputPassDlg.h"
#include "afxdialogex.h"


// CInputPassDlg �Ի���

IMPLEMENT_DYNAMIC(CInputPassDlg, CDialog)

CInputPassDlg::CInputPassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputPassDlg::IDD, pParent)
{

}

CInputPassDlg::~CInputPassDlg()
{
}

void CInputPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputPassDlg, CDialog)
	ON_BN_CLICKED(IDC_PASSCANCEL, &CInputPassDlg::OnBnClickedPasscancel)
	ON_BN_CLICKED(IDC_PASSOK, &CInputPassDlg::OnBnClickedPassok)
END_MESSAGE_MAP()


// CInputPassDlg ��Ϣ�������


void CInputPassDlg::OnBnClickedPasscancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}

CString CInputPassDlg::getPassword()
{
	return m_strPass;
}

void CInputPassDlg::OnBnClickedPassok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szPass[36];
	GetDlgItemText(IDC_EDITPASS, szPass, 32);
	m_strPass = szPass;
	EndDialog(1);
}
