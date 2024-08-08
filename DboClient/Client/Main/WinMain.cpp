#include "precomp_dboclient.h"
#include "DboApplication.h"
#include "NtlDebug.h"
#include "DboCompileOpt.h"
#include "DboDef.h"
#include "NtlClientService.h"

BOOL IsMultiOpen(const char *pExeName)
{
	HANDLE hMutex = ::CreateMutex(NULL, FALSE, pExeName);
	if(NULL == hMutex)
		return FALSE;

	if(GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;
	return TRUE;
}

BOOL IsLimitDirectory(void)
{
	RwChar chCurrDir[1024];
	memset(chCurrDir, 0, 1024);

	GetCurrentDirectory(1024, chCurrDir);

	RwInt32 iLen = (RwInt32)strlen(chCurrDir);
	if(iLen >= 200)
		return FALSE;

	return TRUE;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpCmdLine,
                     int       nCmdShow)
{

#ifdef MUTEX_CHECK
	if ( NULL == lpCmdLine && strcmp( lpCmdLine, "nomutex" ) > 0 )
	{
		if(!IsMultiOpen("DragonBall"))
		{
			::MessageBox(NULL, "DragonBall is already opened !!!", "DragonBall", MB_OK);
			return 1;
		}
	}
#endif

	NtlClientNetSetPrintFlag( 0 );

	// ���� ����
	if ( !GetServiceInterface()->Begin( lpCmdLine ) )
	{
		::MessageBox(NULL, "Wrong service information.", "DragonBall", MB_OK);
		return 1;
	}

	eDBO_SERVICE_PUBLISHER eService = GetServiceInterface()->GetPublisherID();
	if( eDBO_SERVICE_PUBLISHER_CJI_KOR == eService )
	{
		for( RwUInt8 i = 0 ; i < 4 ; ++i )
		{
			RwChar* pcData = (RwChar*)GetServiceInterface()->GetServiceData(i);

			if( !pcData || strlen(pcData) == 0 )
			{
				::MessageBox(NULL, "Wrong service data", "DragonBall", MB_OK);
				return 1;
			}
		}
	}

	if(!IsLimitDirectory())
	{
		::MessageBox(NULL, "A directory name length must not exceed 200 letters", "DragonBall", MB_OK);
		return 1;
	}

	// ���� �ַ�� ����
	// - ���� �ַ���� ���� �߾ ������ ����ɶ����� �������� �ʰ� ����ϰ� �ִٰ� �����Ų��
	GetServiceInterface()->CreateSecuritySolution();

	CDboApplication app;
	
	app.Init();

#ifdef NDEBUG
	
	if(!app.Create(hInstance, 0, 0, EXTRA_SCREEN_WIDTH, EXTRA_SCREEN_HEIGHT, TRUE))
	{
		NTL_ASSERTE("Application create failed!!!");
		return 1;
	}

#else

	if(!app.Create(hInstance, 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, NTL_DEBUG_WINDOW_MODE))
	{
		NTL_ASSERTE("Application create failed!!!");
		return 1;
	}

#endif

	// ���� �ַ�ǿ� �����츦 �����Ѵ�
	GetServiceInterface()->AttachSecuritySolutionWindow( app.GetHWnd() );

	app.MessagePump();
	app.Destroy();

	// ���� �ַ�� ����
	GetServiceInterface()->DeleteSecuritySolution();

	// ���� ����
	GetServiceInterface()->End();

	return 1;
}


