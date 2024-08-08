/******************************************************************************
* File			: TMQBoardGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 7. 3
* Update		: 2007. 10.23
* Abstract		: 
*****************************************************************************
* Desc			: ���� ������ Ÿ�Ӹӽ� ����Ʈ�� ����Ʈ�� �����ش�
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// share
#include "NtlTimeQuest.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SurfaceGui.h"
#include "SlotGui.h"

struct sTIMEQUEST_TBLDAT;

class CTMQBoardGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	struct sTMQ_Senario
	{
		RwUInt32			uiTblIdx;
	};

	enum eDefinedValue
	{
		DV_SENARIO_NUM		= 4
	};

	CTMQBoardGui(const RwChar* pName);
	virtual ~CTMQBoardGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	VOID		Clear();

	SERIAL_HANDLE	GetNPCHandle();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

protected:
	CTMQBoardGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			UpdateList();
	VOID			SetRoomState(RwUInt8 byState);
	VOID			CheckInfoWindow();

	VOID			ClickedCloseButton(gui::CComponent* pComponent);
	VOID			ClickedPrivateReservation(gui::CComponent* pComponent);
	VOID			ClickedPartyReservation(gui::CComponent* pComponent);
	VOID			ClickedCancelReservation(gui::CComponent* pComponent);

	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnPaint();

protected:		
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotCloseButton;	
	gui::CSlot			m_slotPrivateReservationButton;
	gui::CSlot			m_slotPartyReservationButton;
	gui::CSlot			m_slotCancelReservationButton;

	gui::CStaticBox*	m_pLimitedLevel;			///< '���ѷ���'
	gui::CStaticBox*	m_pLimitedLevelText;		///< ���ѷ��� ǥ��	
	gui::CStaticBox*	m_pTitle;					///< TMQ ����

	gui::CStaticBox*	m_pDifficult;				///< '���̵�'
	gui::CStaticBox*	m_pStartTime;				///< '��߽ð�'	
	gui::CStaticBox*	m_pLimitedTime;				///< '���ѽð�'	
	gui::CStaticBox*	m_pDifficultText;			///< ���̵� ǥ��
	gui::CStaticBox*	m_pStartTimeText;			///< ��߽ð� ǥ��
	gui::CStaticBox*	m_pLimitedTimeText;			///< ���ѽð� ǥ��	

	gui::CStaticBox*	m_pReservationPeople;		///< ���� ������ �ο�

	gui::CStaticBox*	m_pNextTitle;				///< '���� Ÿ�Ӹӽ� ����Ʈ'
	gui::CStaticBox*	m_pNextTitle_Senario_1;		///< ���� ����Ʈ 1
	gui::CStaticBox*	m_pNextTitle_Senario_2;		///< ���� ����Ʈ 2
	gui::CStaticBox*	m_pNextTitle_Senario_3;		///< ���� ����Ʈ 3

	gui::CButton*		m_pExitButton;
	gui::CButton*		m_pPrivateReservationButton;///< ���� ���� ��ư
	gui::CButton*		m_pPartyReservationButton;	///< ��Ƽ ���� ��ư
	gui::CButton*		m_pCancelReservationButton;	///< ������� ��ư

	CRegularSlotGui			m_NeedItem;

	SERIAL_HANDLE		m_hNPCSerial;
	sTMQ_Senario		m_Senario[DV_SENARIO_NUM];
	RwUInt8				m_byRoomState;

	sTIMEQUEST_TBLDAT*	m_pTIMEQUEST_TBLDAT;		///< ���� ���� �ִ� �Խ����� TMQ ���̺�
};