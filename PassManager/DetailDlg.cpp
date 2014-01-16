// DetailDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "DetailDlg.h"
#include "afxdialogex.h"
#include "PassManagerDlg.h"


// CDetailDlg �Ի���

IMPLEMENT_DYNAMIC(CDetailDlg, CDialogEx)

CDetailDlg::CDetailDlg(CString strUser, CString strPass, CString strUrl, CString strMak, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDetailDlg::IDD, pParent)
{
	m_strUser = strUser;
	m_strPass = strPass;
	m_strUrl = strUrl;
	m_strMak = strMak;
	pPar = pParent;
}

CDetailDlg::~CDetailDlg()
{
}

void CDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDetailDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DETAIL_RETURN, &CDetailDlg::OnBnClickedDetailReturn)
	ON_BN_CLICKED(IDC_BTNDETAIL_USER, &CDetailDlg::OnBnClickedBtndetailUser)
	ON_BN_CLICKED(IDC_BTNDETAIL_PASS, &CDetailDlg::OnBnClickedBtndetailPass)
	ON_BN_CLICKED(IDC_BTNDETAIL_URL, &CDetailDlg::OnBnClickedBtndetailUrl)
	ON_BN_CLICKED(IDC_BTNDETAIL_MAK, &CDetailDlg::OnBnClickedBtndetailMak)
END_MESSAGE_MAP()


// CDetailDlg ��Ϣ�������


void CDetailDlg::OnBnClickedDetailReturn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE);
}


BOOL CDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_DETAILEDIT_USER, (LPCTSTR)m_strUser);
	SetDlgItemText(IDC_DETAILEDIT_PASS, (LPCTSTR)m_strPass);
	SetDlgItemText(IDC_DETAILEDIT_URL, (LPCTSTR)m_strUrl);
	SetDlgItemText(IDC_DETAILEDIT_MAK, (LPCTSTR)m_strMak);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//���ƺ���
void CDetailDlg::CopyStr(CString strCopy)
{
	CPassManagerDlg * p = (CPassManagerDlg *)pPar;
	if(!OpenClipboard())
	{
		p->OnSonDlgClose("���Ƴ���");
		return ;
	}
	EmptyClipboard();
	HANDLE hClip;
	hClip=GlobalAlloc(GMEM_MOVEABLE,strCopy.GetLength()+1);
	char *pBuf;
	pBuf=(char *)GlobalLock(hClip);
	strcpy(pBuf,strCopy.GetBuffer());
	GlobalUnlock(hClip);
	SetClipboardData(CF_TEXT,hClip);
	CloseClipboard();
	p->OnSonDlgClose("ѡ��������Ѹ���");
	OnBnClickedDetailReturn();
}

//�����û���
void CDetailDlg::OnBnClickedBtndetailUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_DETAILEDIT_USER, str);
	CopyStr(str);
}

//��������
void CDetailDlg::OnBnClickedBtndetailPass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_DETAILEDIT_PASS, str);
	CopyStr(str);
}

//����url
void CDetailDlg::OnBnClickedBtndetailUrl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_DETAILEDIT_URL, str);
	CopyStr(str);
}

//���Ʊ�ע
void CDetailDlg::OnBnClickedBtndetailMak()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_DETAILEDIT_MAK, str);
	CopyStr(str);
}
