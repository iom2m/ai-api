// Firend.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



// CFirendApp:
// �йش����ʵ�֣������ Firend.cpp
//

class CFirendApp : public CWinApp
{
public:
	CFirendApp(); 

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFirendApp theApp;