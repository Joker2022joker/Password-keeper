#pragma once

#include "sqlite/dosql.h"

// CRepassDlg �Ի���

class CRepassDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRepassDlg)

public:
	CRepassDlg(doSql * sql, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRepassDlg();

// �Ի�������
	enum { IDD = IDD_REPDLG };
	
private:
	doSql * m_sql;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_strPass;
public:
	afx_msg void OnBnClickedRepdlgOk();
};
