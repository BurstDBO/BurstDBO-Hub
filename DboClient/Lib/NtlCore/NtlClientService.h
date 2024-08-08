/*****************************************************************************
*
* File			: NtlClientService.h
* Author		: 
* Copyright		: (��) NTL
* Date			:
* Abstract		: 
*****************************************************************************
* Desc          : 
*				eDBO_SERVICE_PUBLISHER Ÿ���� eDBO_SERVICE_PUBLISHER_NTL �� ����
*				GetServiceData() �Լ��� ������ �ʴ´�
*
*				eDBO_SERVICE_PUBLISHER Ÿ���� eDBO_SERVICE_PUBLISHER_CJI_KOR �� ����
*				0 : ���� IP
*				1 : ���� Port
*				2 : ���� ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
*				3 : ������ ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
*				4 : CP��Ű		- ���� ũ�⸦ NTL_MAX_SIZE_CP_COOKIE�� ��ƾ� �Ѵ�
*				5 : ������ ����(CP���ӵ�� ���)
*****************************************************************************/


#pragma once


#include "NtlService.h"


enum E_SEC_RET_FLAG
{
	E_SEC_RET_FLAG_INVALID					= 0x00000000,
	E_SEC_RET_FLAG_EXIT_APP					= 0x00000001,
	E_SEC_RET_FLAG_SEND_SERVER				= 0x00000002,
};


struct sSEC_RET_DATA
{
	DWORD									dwDataSize;
	void*									pData;
};

class INtlClientService
{
public:
	virtual ~INtlClientService( void ) { return; }

public:
	virtual bool							Begin( void* pData )				= 0;
	virtual void							End( void )							= 0;

	virtual eDBO_SERVICE_PUBLISHER			GetPublisherID( void )				= 0;

	virtual void*							GetServiceData( int nIndex )		= 0;

	virtual bool							CreateSecuritySolution( void )		= 0;
	virtual void							DeleteSecuritySolution( void )		= 0;
	virtual void							AttachSecuritySolutionWindow( HWND hWnd )				= 0;
	virtual void							AttachSecuritySolutionUserID( const char* pUserID )		= 0;
	virtual void							SecurityAuthServer( void* pData, int nSize )			= 0;
	virtual void							CheckGameMon( void )									= 0;
	virtual bool							IsEmptySecurityRetData( void )							= 0;
	virtual void							AddSecurityRetData( unsigned int uiRetFlag, unsigned int uiRetCode, sSEC_RET_DATA* pRetData )		= 0;
	virtual bool							PopSecurityRetData( unsigned int& uiRetFlag, unsigned int& uiRetCode, sSEC_RET_DATA** ppRetData )	= 0;
};


INtlClientService* GetServiceInterface( void );