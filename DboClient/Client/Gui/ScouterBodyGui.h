/******************************************************************************
* File			: ScouterBodyGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 18
* Abstract		: 
*****************************************************************************
* Desc			: ScouterBodyGui
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

#include "NtlSLDef.h"

// dbo
#include "SlotGui.h"
#include "Windowby3.h"


struct sITEM_TBLDAT;

class CScouterBodyGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CScouterBodyGui(const RwChar* pName);
	virtual ~CScouterBodyGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close
	
	RwInt32		GetCurPower();						///< ��ī������ ���� ���뷮

protected:
	CScouterBodyGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	RwBool			SetScouterBody(SERIAL_HANDLE hSerial);	///< ��ī���� �ٵ� �´� ������ UI�� �����Ѵ�
	VOID			UnSetScouterBody();					///< ��ī���� �ٵ� �����Ѵ�.	

	RwInt32			GetPartsCount();
	VOID			UpdateParts();						///< ��ī���� ���Կ� ���� ������ ������Ʈ �Ѵ�.

	VOID			SetPower(RwInt32 iPower, RwInt32 iMaxPower);

	RwUInt8			PtinSlot(RwInt32 iX, RwInt32 iY);	///< ���콺�� ���� ������ ã�´�.
	
	VOID			ClickReleasePartsButton(gui::CComponent* pComponent);	///< ��ī���� ���� ��� ���� ��ư
	
	VOID			FocusEffect( RwBool bPush, RwUInt8 bySlot = INVALID_BYTE );
	VOID			SelectEffect( RwBool bPush, RwUInt8 bySlot = INVALID_BYTE );

	VOID			LocateComponent();
	VOID			ShowDisableSlot(RwBool bShow, RwUInt8 bySlot);
	VOID			CheckInfoWindow();

	VOID			OnPaint();

	VOID			OnClicked_OnMenuButton(gui::CComponent* pComponent);
	VOID			OnClicked_OffMenuButton(gui::CComponent* pComponent);
	VOID			OnClicked_RemoveAllPartsButton(gui::CComponent* pComponent);

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnResize(RwInt32 iOldW, RwInt32 iOldH);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnCaptureMouseDown(const CKey& key);

protected:	
	gui::CSlot			m_slotOnMenuButton;
	gui::CSlot			m_slotOffMenuButton;
	gui::CSlot			m_slotRemoveAllPartsButton;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotResize;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotCaptureMouseDown;

	RwUInt8				m_byMouseDownSlot;			///< ���콺�� ���� ������ �ε���
	RwUInt8				m_bySelectedSlot;			///< ����Ʈ ����Ʈ ����
	RwUInt8				m_byClickEffectedSlot;		///< ���� Ŭ�� ����Ʈ�� ���� ����
	
	gui::CButton*		m_pOnMenuButton;			///< ��ī���� �޴� Ű��
	gui::CButton*		m_pOffMenuButton;			///< ��ī���� �޴� ����
	gui::CButton*		m_pRemoveAllParts;			///< ��� ���� ���� ��ư

	gui::CStaticBox*	m_pScouterName;				///< ��ī���� �̸�
	gui::CStaticBox*	m_pPowerStatic;				///< ��ī���� ������
	gui::CProgressBar*	m_pPowerGauge;				///< ��ī���� ���� ������

	CWindowby3			m_BackPanel;				///< ��ī���� ���
	CSurfaceGui			m_FocusEffect;				///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;				///< ���� ����Ʈ ����Ʈ
	CSurfaceGui			m_srfSlot[4];				///< ���� �����̽�

	RwUInt8				m_byInfoWindowIndex;
	RwBool				m_bFocus;					///< ��Ŀ���� �����.

	CRegularSlotGui			m_ScouterSlot;				///< ������ �˾ƺ� ��ī������ ������ ����
	RwInt32				m_iScouterSlotCount;		///< ���� ��ī������ ���� ����
	CRegularSlotGui			m_Slot[NTL_MAX_SCOUTER_ITEM_SLOT];	///< ��ī������ ����	

	RwInt32				m_iCurPower;
};