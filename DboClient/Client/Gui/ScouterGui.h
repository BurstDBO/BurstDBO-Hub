/******************************************************************************
* File			: ScouterGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 14
* Abstract		: ��ī���� ������ ����� ǥ���Ѵ�
*****************************************************************************
* Desc			: Item_Option_Table�� Scouter_Info �׸� �����Ƿ� ǥ�õȴ�
*
*				��ī���� ������ ����� ǥ���ϴ� ����� �����ϴ�
*				���ο� ����� ������ �߰��� ������ ������ �۾� ������ �� ��Ű��
*
*				1. Item_Option_Table�� Scouter_Info�� ���� �����Ͽ� NtlItem.h
*				   �� eSCOUTER_INFO�� Ÿ���� �߰��Ѵ�
*
*				2. DisplayStringDef.h�� ǥ�õ� �۱͸� �߰��Ѵ�
*
*				3. ������ �⺻ ��ġ�� ���ϰ� �ϴ� ���� �ִٸ�
*				   CScouterGui::GetDefaultValue()�� eSCOUTER_INFO�� �߰���
*				   Ÿ���� �߰��Ѵ�
*
*				�˸�) �Ϻ� ����(eSCOUTER_INFO�� SCOUTER_INFO_BEGIN_ONLY_ALLPY_MAX����
*				   SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION���̴� ���� ���� ������ �ϳ����� ǥ���Ѵ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// share
#include "NtlItem.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SlotGui.h"



class CScouterGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	// ���� ������ ������ �ɷ�����, ���� �ɷ��� �÷��ִ� �͵��� ��ġ�� �ϳ��� ǥ���ϱ� ����
	// first  : sITEM_OPTION_TBLDAT�� byScouterInfo
	// second : sITEM_OPTION_TBLDAT�� nValue[0] or sITEM_TBLDAT�� byScouter_Parts_Value
	typedef std::map<RwUInt32, RwUInt32>				MAP_PARTS_EXPLAIN;
	typedef std::map<RwUInt32, RwUInt32>::iterator		MAP_PARTS_EXPLAIN_ITER;
	
	CScouterGui(const RwChar* pName);
	virtual ~CScouterGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	VOID		AddScouterParts();

protected:
	CScouterGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			SetScouterInfo(RwUInt32 uiSerial);	///< ��ī���� ���� ǥ��
	VOID			UnSetScouterInfo();					///< ��ī���� ���� �ʱ�ȭ

	VOID			UpdatePartsInfo();					///< ��ī���� ���� ���� ������Ʈ

	VOID			ReadyPartsExplain(RwUInt32 uiPartsValue, RwUInt32 uiItemOptionTableIndex);	///< ���� ������ �����Ѵ�
	VOID			DisplayPartsInfo();											///< ���� ������ �����ش�

	RwInt32			GetDefaultValue(RwUInt32 uiType);							///< ���� ���� ��ġ�� ����Ʈ ���� ���´�
	RwUInt32		ConvertPartsInfotoStringTableIndex(RwUInt32 iType);			///< ��Ʈ�� ���̺� �ε��� ã��

	VOID			OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );
	VOID			OnCaptureMouseDown(const CKey& key);
	VOID			OnClicked_ExitButton(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotCaptureMouseDown;
	gui::CSlot			m_slotExitButton;

	gui::CButton*		m_pExitButton;
	gui::CListBox*		m_pPartsListBox;			///< ���� �ɼ� ���� ����Ʈ

	SERIAL_HANDLE		m_hScouterHandle;
	MAP_PARTS_EXPLAIN	m_mapPartsExplain;			///< ���� ������ ���� �ӽ� �����
};