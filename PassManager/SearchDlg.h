#pragma once

#include "ListBoxEx.h"
#include "sqlite/dosql.h"
#include "afxwin.h"

// CSearchDlg �Ի���

class CSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(doSql * sql, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchDlg();


// �Ի�������
	enum { IDD = IDD_SEARCHDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	void CSearchDlg::SearchPass();
	doSql * m_sql;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CArray<CString, CString&> m_passArr;

private:
	CString m_strSearch;
	CListBoxEx m_SearchList;
public:
	afx_msg void OnPaint();
	afx_msg void OnClose();
private:
	CEdit m_EditInput;
public:
	virtual BOOL OnInitDialog();
};
