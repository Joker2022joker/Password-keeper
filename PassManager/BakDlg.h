#pragma once
#include "afxwin.h"
#include "sqlite/dosql.h"

// CBakDlg �Ի���

class CBakDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBakDlg)

public:
	CBakDlg(doSql * sql, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBakDlg();

// �Ի�������
	enum { IDD = IDD_BAKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	doSql * m_sql;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeBakdlgList();
private:
	CComboBox m_TypeList;
	CButton m_DelPass;
	CString CBakDlg::SelectPath();
public:
	afx_msg void OnBnClickedBakdlgSave();
	afx_msg void OnBnClickedBakdlgPass();
};
