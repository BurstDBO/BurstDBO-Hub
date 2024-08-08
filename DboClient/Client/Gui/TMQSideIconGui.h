/******************************************************************************
* File			: TMQSideIconGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 7. 9
# Upddate		: 2007. 10. 29
* Abstract		: 
*****************************************************************************
* Desc			: Ÿ�Ӹӽ� ����Ʈ�� ������ ���̵� ������
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// share
#include "NtlTimeQuest.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "Windowby3.h"
#include "SideIconGui.h"
#include "SlotGui.h"

class CCounterGui;


class CTMQSideIconGui : public CSideIconBase, public RWS::CEventHandler
{
public:
	enum eIconImageType
	{
		IIT_NORMAL,
		IIT_EVENT,		
	};

	CTMQSideIconGui(const RwChar* pName);
	virtual ~CTMQSideIconGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	VOID		Clear();

	VOID		SetIconImageType(eIconImageType eType);

	virtual VOID	OnSideViewClosed();
	virtual VOID	OnIconButtonClicked(gui::CComponent* pComponent);	

protected:
	virtual VOID	HandleEvents( RWS::CMsg &msg );
	

	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnPaint();

protected:		
	gui::CSlot			m_slotIconButton;
	gui::CSlot			m_slotAskIconButton;
	gui::CSlot			m_slotEventIconButton;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;

	gui::CButton*		m_pIconButton;			///< �Ϲ� ������ ��ư
	gui::CButton*		m_pEventIconButton;		///< �̺�Ʈ ������ ��ư

	CCounterGui*		m_pCounterGui;

	eIconImageType		m_eIconImageType;	
};


class CTMQSideViewGui : public CSideViewBase, RWS::CEventHandler
{
public:
	CTMQSideViewGui(const RwChar* pName);
	virtual ~CTMQSideViewGui();

	RwBool		Create();
	VOID		Destroy();

	virtual VOID	OnPressESC();
	virtual VOID	OnSideViewOpen(const void* pData);
	virtual VOID	OnSideViewClose();
	virtual VOID	OnSideViewLocate(const CRectangle& rectSideIcon);	

protected:
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			SetViewContent(RwUInt8 byMode);			///< View â�� ������ �Ϻ� ��带 �����Ѵ�
	VOID			SetNeedItemState();
	VOID			CheckInfoWindow();

	VOID			OnExitClicked(gui::CComponent* pComponent);
	VOID			OnOKClicked(gui::CComponent* pComponent);
	VOID			OnCancelClicked(gui::CComponent* pComponent);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnPaint();

protected:		
	gui::CSlot			m_slotExitButton;
	gui::CSlot			m_slotOKButton;
	gui::CSlot			m_slotCancelButton;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;

	CWindowby3			m_BackPanel;		///< ���

	gui::CStaticBox*	m_pNotifyTitle;		///< �˸� ����
	gui::CStaticBox*	m_pMessage_1;		///< �޼��� 1
	gui::CStaticBox*	m_pMessage_1_Content;///< �޼��� 1 ����
	gui::CStaticBox*	m_pMessage_2;		///< �޼��� 2
	gui::CStaticBox*	m_pMessage_2_Content;///< �޼��� 2 ����
	gui::CStaticBox*	m_pMessage_3;		///< �޼��� 3
	gui::CStaticBox*	m_pMessage_3_Content;///< �޼��� 3 ����
	gui::CStaticBox*	m_pMessage_4;		///< �޼��� 4
	gui::CStaticBox*	m_pMessage_4_Content;///< �޼��� 4 ����

	gui::CButton*		m_pExitButton;		///< �ݱ� ��ư
	gui::CButton*		m_pOKButton;		///< Ȯ�� ��ư
	gui::CButton*		m_pCancelButton;	///< ��� ��ư

	CRegularSlotGui			m_NeedItem;

	RwInt32				m_iViewHeight;	
};