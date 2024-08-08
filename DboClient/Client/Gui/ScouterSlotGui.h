/******************************************************************************
* File			: ScouterGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 28
* Abstract		: 
*****************************************************************************
* Desc			: ȭ�� �ϴܿ� ��ī���Ͱ� �� ����
*				  �ܼ��� ��ī���� �ٵ��� ������ ���� ��ī���� ���濭�� ������
*			      ��ɸ��� �ִ�
*				  ��ī������ ������ �� �������� ǥ���ȴ�
*				  �ϳ��� �������ͽ� �������̰� �ϳ��� ȭ���ϴ��� 5���� ����
*				  ���Կ��̴�. ������ �̺�Ʈ�� �ٸ� �ʿ��� �˷��־�� �ϱ⿡
*				  g_EventScouter �̺�Ʈ�� ���ؼ� ��ī���� �ٵ� �ٲ� ���θ�
*				  �� �� �ְ� �Ͽ���.
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SlotGui.h"


class CScouterSlotGui : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	CScouterSlotGui(const RwChar* pName);
	virtual ~CScouterSlotGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetScouterBody(SERIAL_HANDLE hHandle);	///< ��ī������ �ٵ� ������ ����Ǹ� ó��
	VOID		UnSetScouterBody();						///< ��ī������ �ٵ� ������ �����.

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

protected:
	CScouterSlotGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

	VOID			ShowIconDestination();				
	///< ����ȿ��� ��ī���� ������ �����ٸ� ��ī���� ���Կ� ����Ʈ ����Ʈ�� �����ش�.

	VOID			ShowDisableSlot(RwBool bShow);
	VOID			CheckInfoWindow();

	VOID			OnPaint();

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);

protected:	
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;

	RwInt32				m_iMouseDownSlot;			///< ���콺�� ���� ������ �ε���

	CRegularSlotGui		m_slot;						///< ����

	CSurfaceGui			m_FocusEffect;				///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;				///< ���� ����Ʈ ����Ʈ

	RwBool				m_bFocus;					///< ��Ŀ���� �����.
	RwBool				m_bIconMoveClickEvent;		///< ���濡�� ��ī���� �ٵ� ������ �� �̺�Ʈ
	RwBool				m_bSelected;				///< ������ �Ǿ���.
	RwBool				m_bClickEffect;				///< ���� Ŭ�� ���
};