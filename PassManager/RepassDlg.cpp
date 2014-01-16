// RepassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "PassManagerDlg.h"
#include "RepassDlg.h"
#include "afxdialogex.h"

// CRepassDlg �Ի���

IMPLEMENT_DYNAMIC(CRepassDlg, CDialogEx)

CRepassDlg::CRepassDlg(doSql * sql, CWnd* pParent /*=NULL*/)
	: CDialogEx(CRepassDlg::IDD, pParent)
	, m_strPass(_T(""))
{
	m_sql = sql;
}

CRepassDlg::~CRepassDlg()
{
}

void CRepassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_REPDLG_INPUT, m_strPass);
}


BEGIN_MESSAGE_MAP(CRepassDlg, CDialogEx)
	ON_BN_CLICKED(IDC_REPDLG_OK, &CRepassDlg::OnBnClickedRepdlgOk)
END_MESSAGE_MAP()


// CRepassDlg ��Ϣ�������


void CRepassDlg::OnBnClickedRepdlgOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CPassManagerDlg * p = (CPassManagerDlg *)GetParent();
	int rc = m_sql->reKey(m_strPass.GetBuffer(), m_strPass.GetLength());
	m_strPass.ReleaseBuffer();
	if (rc)
	{
		p->OnSonDlgClose("�޸�����ɹ������μ����룬�������뽫�޷��һأ�");
	}else
	{
		p->OnSonDlgClose("�޸�����ʧ��");
	}
	SendMessage(WM_CLOSE);
}
