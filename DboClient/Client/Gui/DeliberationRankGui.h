/*****************************************************************************
* File			: DeliberationRankGui.h
* Author		: Hong Sungbock
* Copyright		: (��)NTL
* Date			: 2009. 8. 18
* Abstract		: DBO contract gui.
*****************************************************************************
* Desc          : ���� ����� ǥ���ϱ� ���� GUI Ŭ����
*
*				  1. Ÿ��Ʋ ȭ�鿡 ǥ��
*				  2. ������ ���� �ð� �������� ��� ���� ǥ��
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"


class CDeliberationRankGui : public CNtlPLGui
{
public:
	CDeliberationRankGui(const RwChar* pName);
	virtual ~CDeliberationRankGui();

	RwBool			Create(RwBool bGameStage);
	VOID			Destroy();

	VOID			HandleEvents( RWS::CMsg &msg );

protected:
	CDeliberationRankGui() {}

	VOID			LocateComponent(RwInt32 iWidth, RwInt32 iHeight);

protected:
	gui::CSlot			m_slotMove;
	RwBool				m_bGameStage;

};


class CDeliberationRankContainer : public RWS::CEventHandler
{
	struct sALARM_INFO
	{
		RwBool		bGameStage;
		RwReal		fElapsed;
		RwReal		fShowTime;
	};

public:
	CDeliberationRankContainer();
	virtual ~CDeliberationRankContainer();

	RwBool			Create();
	VOID			Update(RwReal fElapsed);
	VOID			Destroy();

protected:
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			CreateGui();
	VOID			DestroyGui();

protected:
	CDeliberationRankGui*	m_pDeliberationRank;
	
	sALARM_INFO			m_tALARM_INFO;
};