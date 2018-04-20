// Firend.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Firend.h"
#include "FirendDlg.h"
#include "debug_util.h"
#include "AutoDump.h"
#include "SimpleHttp.h"
string	g_softid="1000";

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int	TCP_SOCK_FreeSSL_System();

// CFirendApp

BEGIN_MESSAGE_MAP(CFirendApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFirendApp ����

CFirendApp::CFirendApp()
{

}


// Ψһ��һ�� CFirendApp ����

CFirendApp theApp;
 

// CFirendApp ��ʼ��

BOOL CFirendApp::InitInstance()
{
	DebugInit();
	extern CPGLogThread * g_pLogOutput;
	_bstr_t svaelogDir=CFirendDlg::GetStartPath();
	g_pLogOutput->SetLogCfg("IGLog", 15,(const char *)svaelogDir);

	CAutoDump dump;

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
 

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
 

	//����һ
	//::GetCommandLine();
	//����ȡ�� "C:/test/app.exe"  -1 -2
	//
	//������
	//for (int i=0;i<__argc;i++)
	//{
	//__argv[i];
	//�����εõ�C:/test/app.exe  -1  -2
	//}
	//
	//������
	//AfxGetApp()->m_lpCmdLine;
	//����ȡ�� -1 -2
	//
 

	map<int,_bstr_t> cmdlist;
	_bstr_t cmdparam="";
	for (int i=0;i<__argc;i++)
	{
		if(__argv!=NULL && __argv[i]!=NULL)
		{
			cmdparam=__argv[i];
		}
		else if(__wargv!=NULL && __wargv[i]!=NULL)
		{
			cmdparam=__wargv[i];
		}
		else
		{
			cmdparam="";
		}
		cmdlist[i]=cmdparam;
		//�����εõ�C:/test/app.exe  -1  -2
	}
	if(g_pLogOutput!=NULL)
	{
		g_pLogOutput->Start();
	}
	CFirendDlg dlg(cmdlist);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á� 
	if(g_pLogOutput!=NULL)
	{
		g_pLogOutput->Kill(-1);
	}
	DebugRelease();
	return FALSE;
}
