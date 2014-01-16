#pragma once
#include "afxcmn.h"


// CFastKeyDlg �Ի���

class CFastKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFastKeyDlg)

public:
	CFastKeyDlg(CString strIniName, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFastKeyDlg();

// �Ի�������
	enum { IDD = IDD_DLGFAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CWnd * m_Parent;
	CString m_strIniPath;

public:
	CHotKeyCtrl m_ShowKey;
	afx_msg void OnBnClickedFastdlgOk();
	afx_msg void OnBnClickedFastdlgCancel();
	CHotKeyCtrl m_SearchKey;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedFastdlgClear();
};
