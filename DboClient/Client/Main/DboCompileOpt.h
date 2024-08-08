/****************************************************************************
*
* File			: DboCompileOpt.h
* Author		: HyungSuk, Jang
* Copyright	: (��)NTL
* Date			: 2005. 9. 28	
* Abstract		: DBO compile option.
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __DBO_COMPILE_OPT_H___
#define __DBO_COMPILE_OPT_H___

#define DATA_MODE_XML	0		// xml
#define DATA_MODE_BIN	1		// bin
#define DATA_MODE_ENC	2		// enc

//-----------------------------------------------------------------------------
// server network sync mode	

#define NET_SERVER_SYNC

//#define MUTEX_CHECK //Ŭ���̾�Ʈ �ϳ��� Ű��

#define LOAD_DATA_MODE		DATA_MODE_BIN

#define USE_PACK_DATA //�� ��뿩��

#define GAME_DEBUG

//#define COLLISION_VIEW

#define _UICONFIG

// �����̸� ��� ����
#ifdef NDEBUG

#ifndef NET_SERVER_SYNC
#define NET_SERVER_SYNC
#endif

#ifndef MUTEX_CHECK
#define MUTEX_CHECK
#endif

#ifndef USE_PACK_DATA
#define USE_PACK_DATA
#endif

#ifdef LOAD_DATA_MODE
#undef LOAD_DATA_MODE
#define LOAD_DATA_MODE		DATA_MODE_BIN
#endif

#endif	// NDEBUG



#endif