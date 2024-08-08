/******************************************************************************
* File			: ScouterMenuGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 10. 30
* Update		: 2008. 3. 4
* Abstract		: 
*****************************************************************************
* Desc			: ScouterMenuGui
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// Shared
#include "NtlItem.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "InputHandler.h"

// dbo
#include "SlotGui.h"
		
enum eScouterMenuType
{
	SCOUTERMENU_MEASURE_POWER,					///< ������ ����
	SCOUTERMENU_IDENTIFICATION_ITEM,			///< ������ ����
	SCOUTERMENU_VIEW_PC_EQUIP_ITEM,				///< �ٸ� ��� ��� ����
	SCOUTERMENU_FIND_HIDDEN_OBJECT,				///< ������ ������Ʈ ã��
	SCOUTERMENU_QUEST_SEARCH,					///< �ֺ� ����Ʈ ã��

	NUM_SCOUTERMENU,

	INVALID_SCOUTERMENU
};

class CScouterMenuGui;

class CScouterMenuItem
{
public:
	CScouterMenuItem(CScouterMenuGui* pScounterMenuGui)
	:m_pFlashButton(NULL)
	,m_byMenuType(INVALID_SCOUTERMENU)
	,m_pScounterMenuGui(pScounterMenuGui)
	{}

	virtual ~CScouterMenuItem() {}

	RwBool			Create(gui::CComponent* pParent, RwUInt8 byMenuType, CRectangle& rt);
	VOID			Destroy();

	VOID			Update(RwReal fElapsed);

	VOID			Show(bool bOpen);

	RwUInt8			GetMenuType();

	VOID			SetPosition(CRectangle& rt);
	CRectangle		GetPosition();

	RwBool			IsShow();

protected:
	VOID			OnFSCallback(const char* pcParam, const char* pcParam2);

protected:
	gui::CSlot			m_slotFSCallback;

	gui::CFlash*		m_pFlashButton;
	RwUInt8				m_byMenuType;
	CScouterMenuGui*	m_pScounterMenuGui;
};

class CScouterMenuGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	typedef std::list<CScouterMenuItem*>				LIST_MENUITEM;
	typedef std::list<CScouterMenuItem*>::iterator		LIST_MENUITEM_ITER;

	CScouterMenuGui(const RwChar* pName);
	virtual ~CScouterMenuGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		Update(RwReal fElapsed);
	VOID		Clear();

	VOID		OnClick_MenuItem(RwUInt8 byMenuType);

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CScouterMenuGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			Menu_Update();						///< �޴� ������ ������Ʈ �Ѵ�
	RwBool			Menu_Add(RwUInt8 byMenuType);		///< ������ �޴��� ���ٸ� �ش� Ÿ���� �޴��� �߰��Ѵ�
	VOID			Menu_Del(RwUInt8 byMenuType);		///< �޴��� �����
	VOID			Menu_JugdeVisiblePreNextButton();

	VOID			ResizeDilaog();
	RwUInt8			PartsTypeToMenuIndex(RwUInt8 byType);				///< ������ ���̺��� ����Ÿ���� �޴� �ε����� ������

	VOID			ArrangeMenuButtons();

	RwInt32			KeyboardUpHandler(unsigned int uiKeyData);

	VOID			OnClicked_CloseButton(const char* pcParam, const char* pcParam2);
	VOID			OnClicked_PrePageButton(const char* pcParam, const char* pcParam2);
	VOID			OnClicked_NextButton(const char* pcParam, const char* pcParam2);

	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);

protected:		
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotPrePageButton;
	gui::CSlot			m_slotNextPageButton;
	gui::CSlot			m_slotMove;

	INPUT_HANDLE		m_handleKeyUp;

	gui::CFlash*		m_pFlashExitButton;
	gui::CFlash*		m_pFlashPrePageButton;			///< ���� �������� �ѱ� ��ư
	gui::CFlash*		m_pFlashNextPageButton;			///< ���� �������� �ѱ� ��ư

	RwUInt8				m_byVisibleMenuIndex;

	LIST_MENUITEM		m_listMenuItem;
};