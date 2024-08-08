#include "stdafx.h"
#include "NtlLocalizeCJ.h"
#include "NMCrypt.h"


char* StrTok(const char* str, const char sep)
{
	// strtok()�� ���� ����� �Լ������� separator�� 1���� �ް�
	// ���ڰ� ����ִ� ��쵵 ���ڷ� ������

	static const int TOK_BUFSIZE = 1024*40;

	static char* pnow = NULL;
	static char buf[TOK_BUFSIZE];
	static char token[TOK_BUFSIZE];

	if(str) 
	{
		int slen = (int)strlen(str);
		strcpy_s(buf, TOK_BUFSIZE, str);
		pnow = buf;
	}

	if(!pnow || *pnow == 0)
		return NULL;

	int tlen = 0;
	char* porg = pnow;
	while(*pnow != 0)
	{
		if(*pnow == sep) {
			++pnow;
			break;
		}

		++tlen;
		++pnow;
	}

	if(tlen > 0) {
		strncpy_s(token, TOK_BUFSIZE, porg, tlen);
		token[tlen] = 0;
	}
	else {
		token[0] = 0;
	}

	return token;
}

bool DetectLocalConfig(SLocalConfig *pConfig, const char *pKey)
{
	//
	// # key�� �����(Command Line)���ڷ� �Ѿ���� ������ Ŭ�����忡 ����� 
	//   ���� �������ڸ� ��ȣȭ�ϱ� ���� Ű���̴�
	//
	// # Ŭ������ ���� ���� ��Ģ(������ ���ڴ� �ĸ�(,)�� ���еǸ� ���� ������ ������ ����)
	//   ���� ������ ���� : ServerIP,Port,AuthCookie,DataCookie,CpCookie,SpareParam (���ڴ� ��ȣȭ�Ǿ� �ִ�)
	//   - �ݸ��� ���ӿ����� CpCookie�� �������� �ʴ´�
	//   - CP ���ӿ����� AuthCookie, DataCookie�� �������� �ʴ´�(��� CP������ ����)
	//   - Extra ���ڴ� �����Ǳ⵵ �Ѵ�
	//

	char buf[1024*20] = {0,};	// ���۴� ����� ũ�� ��´�

	// Ŭ�����忡�� ���� �����͸� �о�´�(�ѹ� ������ ������)
	if(!GetNMClipData(buf, sizeof(buf)-1, pKey, true))
		return false;

	if(strlen(buf)==0)
		return false;

	char arg[6][1024*2] = {0,};

	int argcnt = 0;
	char* token = StrTok(buf, ',');
	while(token && argcnt < 6)
	{
		strcpy(arg[argcnt], token);
		argcnt++;
		token = StrTok(NULL, ',');
	}

	// ���ڰ� �ּ��� 5���� �Ǿ�� �Ѵ�
	if(argcnt < 5)
		return false;

	// IP�ּҰ� �ùٸ��� �˻�
	if(strlen(arg[0]) > 16)
		return false;

	// CP ������ �Ʒ��κ��� ���� ����
	strcpy_s(pConfig->chAddr, MAX_LOCAL_ADDR, arg[0]);  // ���� IP 
	pConfig->uiPort  = (unsigned int)::atoi(arg[1]);	// ���� Port

	// CP��Ű �� ����...
	strcpy(pConfig->uCP.chCJData, arg[4]);

//	g_AuthCookie = arg[2];					// ���� ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
//	g_DataCookie = arg[3];					// ������ ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
//	g_CpCookie   = arg[4];					// CP��Ű		- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
//	g_SpareParam = arg[5];					// ������ ����(CP���ӵ�� ���)
	
	return true;
}