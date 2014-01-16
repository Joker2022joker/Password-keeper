
// PassManager.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PassManager.h"
#include "PassManagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPassManagerApp

BEGIN_MESSAGE_MAP(CPassManagerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPassManagerApp ����

CPassManagerApp::CPassManagerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPassManagerApp ����

CPassManagerApp theApp;


// CPassManagerApp ��ʼ��

BOOL CPassManagerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("�������Ա Password Keeper Designed By Phithon"));

	// Enable DDE Execute open
	EnableShellOpen();

	CPassManagerDlg dlg;
	m_pMainWnd = &dlg;

	/*VERIFY( 1 == InitSkinMagicLib(AfxGetInstanceHandle(), NULL, NULL, NULL ));
	VERIFY( 1 == LoadSkinFile("SkinMagic/corona.smf"));
	VERIFY(1 == SetWindowSkin(m_pMainWnd->m_hWnd, "MainFrame"));*/
	//VERIFY(1 == SetDialogSkin("Dialog"));

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CPassManagerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	//ExitSkinMagicLib();

	return CWinApp::ExitInstance();
}
