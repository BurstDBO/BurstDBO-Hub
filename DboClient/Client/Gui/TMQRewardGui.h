/******************************************************************************
* File			: TMQRewardGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 7. 30
* Last update	: 2008. 11. 24 by hong sungbock
* Abstract		: 
*****************************************************************************
* Desc			: TMQ ����â
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// share
#include "NtlTimeQuest.h"

// ts
#include "DboTSCoreDefine.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"
#include "NtlSLEvent.h"

// dbo
#include "SurfaceGui.h"
#include "SlotGui.h"
#include "NumberGui.h"
#include "NumberGui_Helper.h"


struct sTIMEQUEST_TBLDAT;
class CResultNarrationGui;
class CCounterGui;


#define TMQ_REWARD					8
#define dTIMER_NUMBER				4	// �ð��� ��Ÿ���� �� ���̴� ���� 4�ڸ�

class CTMQRewardGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	struct sReward
	{
		CRegularSlotGui			SlotGui;
		sREWARD_INFO		RewardInfo;
		CSurfaceGui			srfSlot;
	};

	enum eTurnOnType
	{
		TURNON_BEGIN,

		TURNON_TEXT,
		TURNON_CLEAR_TIME,

		TURNON_CAPSULE_1,
		TURNON_CAPSULE_2,
		TURNON_CAPSULE_3,
		TURNON_CAPSULE_4,
		TURNON_CAPSULE_5,
		TURNON_CAPSULE_6,
		TURNON_CAPSULE_7,
		TURNON_CAPSULE_8,

		INVALID_TURNON
	};

	CTMQRewardGui(const RwChar* pName);
	virtual ~CTMQRewardGui();

	static VOID		CreateInstance();
	static VOID		DestroyInstance();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CTMQRewardGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			CheckInfoWindow();

	VOID			Init();

	VOID			RegContents(const SNtlEventQuestDirect_Forward* pData);
	VOID			RegReward(sReward& reward, const sREWARD_INFO* pReward, RwInt32 iPosX, RwInt32 iPosY);

	VOID			NextSchedule();
	VOID			LoadFlash(const char* pcFileName, gui::CFlash* pFlash);
	VOID			GetReadyCapsule(RwUInt8 byFlashCapsulePlayIndex);
	
	RwInt8			PtinSlot(RwInt32 iX, RwInt32 iY);
	VOID			FocusEffect( RwBool bPush, RwInt32 iSlotIdx = -1);
	VOID			SelectEffect( RwBool bPush, RwInt32 iSlotIdx = -1 );

	VOID			OnConfirmButton(gui::CComponent* pComponent);
	VOID			OnMovieEnd_Capsule(gui::CComponent* pComponent);
	VOID			OnFrameCallback_Result(const char* pcParam, const char* pcParam2);
	RwInt32			OnCallback_NumberScaleEffect();

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnPaint();

protected:		
	static CTMQRewardGui*	m_pInstance;

	gui::CSlot			m_slotConfirmButton;
	gui::CSlot			m_slotMovieEndCapsule;
	gui::CSlot			m_slotFrameCallbackResult;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	
	gui::CButton*		m_pConfirmButton;				///< �߰� ���� Ȯ�� ��ư

	gui::CStaticBox*	m_pLimitedTime;					///< '���ѽð�'

	gui::CFlash*		m_pFlashBackground;				///< ��� �÷���
	gui::CFlash*		m_pFlashResult;					///< TMQ ��� �÷���
	gui::CFlash*		m_pFlashCapsule;

	CSurfaceGui			m_FocusEffect;					///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;					///< ���� ����Ʈ ����Ʈ		
	CSurfaceGui			m_srfBonusNumColon;
	CSurfaceGui			m_srfBestLapNumColon;
	CSurfaceGui			m_srfTimeNumColon;
	
	CNumberGui			m_BonusTimeGui[dTIMER_NUMBER];
	CNumberGui			m_BestLapTimeGui[dTIMER_NUMBER];
	CNumberGui			m_ClearTimeGui[dTIMER_NUMBER];

	CNumberGui_ZoomHelper	m_NumberZoomHelper;

	CResultNarrationGui*	m_pNarrationGui;			///< NPC �����̼�
	CCounterGui*		m_pCounterGui;					///< ���ο���� ���ư������ �����ð�
	
	RwInt32				m_iMouseDownSlot;
	RwBool				m_bFocus;
	RwInt8				m_byInfoWindowIndex;

	RwReal				m_fLimitedTime;					///< ���ѽð�
	RwUInt8				m_byClearGrade;
	RwUInt32			m_uiBonusTime;
	RwBool				m_bDayRecord;
	RwBool				m_bBestRecord;
	RwUInt8				m_byTurnOn;

	sReward				m_Reward[TMQ_REWARD];			///< ����
	SNtlEventQuestDirect_Echo	m_stEcho;				///< ���ú��� ����
};