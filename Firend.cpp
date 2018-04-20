// Firend.cpp : 定义应用程序的类行为。
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


// CFirendApp 构造

CFirendApp::CFirendApp()
{

}


// 唯一的一个 CFirendApp 对象

CFirendApp theApp;
 

// CFirendApp 初始化

BOOL CFirendApp::InitInstance()
{
	DebugInit();
	extern CPGLogThread * g_pLogOutput;
	_bstr_t svaelogDir=CFirendDlg::GetStartPath();
	g_pLogOutput->SetLogCfg("IGLog", 15,(const char *)svaelogDir);

	CAutoDump dump;

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
 

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
 

	//方法一
	//::GetCommandLine();
	//将获取到 "C:/test/app.exe"  -1 -2
	//
	//方法二
	//for (int i=0;i<__argc;i++)
	//{
	//__argv[i];
	//将依次得到C:/test/app.exe  -1  -2
	//}
	//
	//方法三
	//AfxGetApp()->m_lpCmdLine;
	//将获取到 -1 -2
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
		//将依次得到C:/test/app.exe  -1  -2
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
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。 
	if(g_pLogOutput!=NULL)
	{
		g_pLogOutput->Kill(-1);
	}
	DebugRelease();
	return FALSE;
}
