#include "precomp_dboclient.h"
#include "ScouterGui.h"

// core
#include "NtlDebug.h"

// shared
#include "PCTable.h"
#include "ItemOptionTable.h"
#include "ItemTable.h"
#include "TextAllTable.h"
#include "TableContainer.h"

// sound
#include "GUISoundDefine.h"

// presetation
#include "NtlPLGuiManager.h"

// simulation
#include "NtlSLApi.h"
#include "NtlSLEventfunc.h"
#include "NtlSobItemAttr.h"
#include "NtlSobManager.h"
#include "NtlSobItem.h"
#include "NtlInventory.h"
#include "NtlSobAvatar.h"
#include "NtlSLGlobal.h"
#include "NtlSLLogic.h"

// dbo
#include "DboEvent.h"
#include "IconMoveManager.h"
#include "InfoWndManager.h"
#include "DialogManager.h"
#include "DboLogic.h"
#include "DboTableInfo.h"
#include "DisplayStringManager.h"
#include "DboEventGenerator.h"

CScouterGui::CScouterGui(const RwChar* pName)
:CNtlPLGui( pName )
,m_pPartsListBox(NULL)
,m_hScouterHandle(INVALID_SERIAL_ID)
{
	
}

CScouterGui::~CScouterGui()
{

}

RwBool CScouterGui::Create()
{
	NTL_FUNCTION( "CScouterGui::Create" );

	if(!CNtlPLGui::Create("", "gui\\Scouter.srf", "gui\\Scouter.frm"))
		NTL_RETURN(FALSE);

	CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

	m_pThis = (gui::CDialog*)GetComponent("dlgMain");

	CRectangle rect;

	m_pExitButton = (gui::CButton*)GetComponent("btnExit");
	m_slotExitButton = m_pExitButton->SigClicked().Connect(this, &CScouterGui::OnClicked_ExitButton);

	// ���� �ɼ� ����Ʈ�ڽ�
	m_pPartsListBox = (gui::CListBox*)GetComponent( "listParts" );
	m_pPartsListBox->SetTextColor( RGB(185, 227, 166) );
	m_pPartsListBox->SetSelectedMaskColor(0, 0, 0, 0);
	m_pPartsListBox->SetSelectedTextColor( RGB(185, 227, 166) );

	// sig
	m_slotCaptureWheelMove = GetNtlGuiManager()->GetGuiManager()->SigCaptureWheelMove().Connect( this, &CScouterGui::OnCaptureWheelMove );
	m_slotCaptureMouseDown = GetNtlGuiManager()->GetGuiManager()->SigCaptureMouseDown().Connect( this, &CScouterGui::OnCaptureMouseDown );

	LinkMsg(g_EventScouter);
	LinkMsg(g_EventSobInfoUpdate);

	Show(false);

	NTL_RETURN(TRUE);
}

VOID CScouterGui::Destroy()
{
	NTL_FUNCTION("CScouterGui::Destroy");

	UnLinkMsg(g_EventScouter);
	UnLinkMsg(g_EventSobInfoUpdate);

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy(); 

	NTL_RETURNVOID();
}

VOID CScouterGui::SetScouterInfo(RwUInt32 uiSerial)
{	
	RwBool bOpened = GetDialogManager()->IsOpenDialog(DIALOG_SCOUTER_INFO);

	// ��ī���� �ٵ� �ٲ���ٸ�
	if( m_hScouterHandle != INVALID_SERIAL_ID )
	{
		UnSetScouterInfo();		
	}

	m_hScouterHandle = uiSerial;

	CRectangle rect = m_pThis->GetScreenRect();

	// ��ī���͸� �ٸ� ������ ��ȯ���� ���� ���Ͽ� ���� ���̾�αװ� �������� ������
	// ��ī���� �ٵ� â�� �����ش�.
	if( bOpened )
	{				
		GetDialogManager()->OpenDialog(DIALOG_SCOUTER_INFO);
	}
	else
	{			
		GetDialogManager()->CloseDialog(DIALOG_SCOUTER_INFO);
	}
}

VOID CScouterGui::UnSetScouterInfo()
{
	if( m_hScouterHandle != INVALID_SERIAL_ID )
	{
		GetDialogManager()->CloseDialog(DIALOG_SCOUTER_INFO);

		m_pPartsListBox->ClearAllItems();		

		m_hScouterHandle = INVALID_SERIAL_ID;
	}
}

VOID CScouterGui::UpdatePartsInfo()
{
	if( m_hScouterHandle == INVALID_SERIAL_ID )
		return;

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	RwUInt32 uiSerial = pInventory->GetEquipItem(EQUIP_SLOT_TYPE_SCOUTER);
	CNtlSobItem* pScouterBody = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject(uiSerial));	
	
	RwInt32 iCurrentPower = 0;
	CNtlSobItem* pScouterParts;
	sITEM_TBLDAT* pPART_ITEM_TBLDAT;
	sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(m_hScouterHandle);
	if(!pITEM_TBLDAT)
		return;

	// �ϴ� ����Ʈ�ڽ��� ������ �����.
	m_pPartsListBox->ClearAllItems();

	m_mapPartsExplain.clear();

	for( RwInt32 i = 0 ; i < pITEM_TBLDAT->byBag_Size ; ++i )
	{
		// ��ī���� �ٵ���� �� ���Կ� ������ �ִٸ� 
		pScouterParts = pScouterBody->GetChildItem( i );
		if(pScouterParts)
		{
			// ������ ������ �о�ͼ�
			pPART_ITEM_TBLDAT = Logic_GetItemDataFromSob(pScouterParts->GetSerialID());
			if(pPART_ITEM_TBLDAT)
			{
				// ���� ������ �����Ѵ�
				ReadyPartsExplain(pPART_ITEM_TBLDAT->byScouter_Parts_Value, pPART_ITEM_TBLDAT->Item_Option_Tblidx);				

				// ������ ���� ��ġ
				iCurrentPower += pPART_ITEM_TBLDAT->wScouter_Watt;
			}			
		}
	}

	CNtlSLEventGenerator::ScouterEvent(SCOUTER_EVENT_CURRENT_POWER, iCurrentPower);

	// ���� ������ �����ش�
	DisplayPartsInfo();
}

VOID CScouterGui::ReadyPartsExplain(RwUInt32 uiPartsValue, RwUInt32 uiItemOptionTableIndex)
{
	sITEM_OPTION_TBLDAT* pItemOption = reinterpret_cast<sITEM_OPTION_TBLDAT*>(API_GetTableContainer()->GetItemOptionTable()->FindData(uiItemOptionTableIndex));

	// ���� ��ġ�� �÷��ִ� ������ �ƴ϶�� ������ �ɼ� ������ ���� ���� �ִ�
	if(!pItemOption)
		return;

	MAP_PARTS_EXPLAIN_ITER it = m_mapPartsExplain.find(pItemOption->byScouterInfo);
	if( it == m_mapPartsExplain.end() )
	{
		// ���ο� ���� ����

		if( pItemOption->byScouterInfo >= SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION )
		{
			// ��ī���� ������ ������ ���̺� �״�� ������ ���� ���� 0���� �ϰ������� �����Ѵ�
			// ������ ������ �ܰ迡�� first�� �� Ÿ�Կ� ���� �ش� �۱͸� �о�´�			
			m_mapPartsExplain[pItemOption->byScouterInfo] = 0;

			// ���������� SCOUTER_INFO_TRANSMITTER ����� �ִٸ�
			// ���� ����� SCOUTER_INFO_CONNECTOR ������ �������� �ʴ´�
			if( pItemOption->byScouterInfo == SCOUTER_INFO_TRANSMITTER)
			{
				m_mapPartsExplain.erase(SCOUTER_INFO_CONNECTOR);
			}
			else if( pItemOption->byScouterInfo == SCOUTER_INFO_CONNECTOR &&
					 m_mapPartsExplain.find(SCOUTER_INFO_TRANSMITTER) != m_mapPartsExplain.end() )
			{
				m_mapPartsExplain.erase(SCOUTER_INFO_CONNECTOR);
			}
		}
		else
		{			
			if( pItemOption->byScouterInfo < SCOUTER_INFO_BEGIN_ONLY_ALLPY_MAX )
			{
				// sITEM_OPTION_TBLDAT�� nValue[0]				
				if(pItemOption->bAppliedInPercent[0] == 0)
				{
					m_mapPartsExplain[pItemOption->byScouterInfo] = pItemOption->nValue[0];
				}
				else if(pItemOption->bAppliedInPercent[0] == 1)
				{	
					// ������ �����ִ� ��� �⺻ ��ġ�� ����� ������ ���Ѵ�			
					//RwUInt32 iMaxValue = GetDefaultValue(pItemOption->byScouterInfo);

					m_mapPartsExplain[pItemOption->byScouterInfo] = pItemOption->nValue[0];
				}	
			}
			else if( pItemOption->byScouterInfo < SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION )
			{
				// ���� ���� ��ġ �ϳ��� �����ϴ� ����
				// sITEM_TBLDAT�� byScouter_Parts_Value
				m_mapPartsExplain[pItemOption->byScouterInfo] = uiPartsValue;
			}			
		}				
	}
	else
	{
		// ���� ������ ������ �̹� ���� ���

		if( pItemOption->byScouterInfo < SCOUTER_INFO_BEGIN_ONLY_ALLPY_MAX )
		{
			// ������ ���� ������ ��ġ�� ���Ѵ�
			if(pItemOption->bAppliedInPercent[0] == 0)
			{
				it->second += pItemOption->nValue[0];
			}
			else if(pItemOption->bAppliedInPercent[0] == 1)
			{	
				// ������ �����ִ� ��� �⺻ ��ġ�� ����� ������ ���Ѵ�			
				//RwUInt32 iMaxValue = GetDefaultValue(pItemOption->byScouterInfo);

				it->second += pItemOption->nValue[0];
			}	
		}			
		else if( pItemOption->byScouterInfo < SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION )
		{
			// ���� ���� ������ �ϳ����� �����Ѵ�
			if( it->second < uiPartsValue )
				m_mapPartsExplain[pItemOption->byScouterInfo] = uiPartsValue;
		}

		// SPI_BEGIN_SPECIAL_FUNCTION���� Ŭ ���� �ܼ��� ������ �����ֱ⿡
		// �� ���� ������ ����Ͽ��� ������ ������ �ʴ´�.
		// ��, ���������� SCOUTER_INFO_TRANSMITTER ����� �ִٸ�
		// ���� ����� SCOUTER_INFO_CONNECTOR ������ �������� �ʴ´�		
	}
}

RwInt32 CScouterGui::GetDefaultValue(RwUInt32 uiType)
{
	// �ش� Ÿ�Ժ� �ƹ�Ÿ�� �⺻ ��ġ�� ���´�	
	sPC_TBLDAT* pPC_TBLDAT = reinterpret_cast<sPC_TBLDAT*>(API_GetTableContainer()->GetPcTable()->FindData(uiType));

	switch(uiType)
	{
	case SCOUTER_INFO_LP:						return pPC_TBLDAT->wBasic_LP;
	case SCOUTER_INFO_EP:						return pPC_TBLDAT->wBasic_EP;
	case SCOUTER_INFO_STR:						return pPC_TBLDAT->byStr;
	case SCOUTER_INFO_CON:						return pPC_TBLDAT->byCon;
	case SCOUTER_INFO_FOC:						return pPC_TBLDAT->byFoc;
	case SCOUTER_INFO_DEX:						return pPC_TBLDAT->byDex;
	case SCOUTER_INFO_SOL:						return pPC_TBLDAT->bySol;
	case SCOUTER_INFO_ENG:						return pPC_TBLDAT->byEng;
	case SCOUTER_INFO_ATTACK_SPEED:				return pPC_TBLDAT->wAttack_Speed_Rate;
	case SCOUTER_INFO_ATTACK_RATE:				return pPC_TBLDAT->wAttack_Rate;
	case SCOUTER_INFO_DODGE_RATE:				return pPC_TBLDAT->wDodge_Rate;
	case SCOUTER_INFO_BLOCK_RATE:				return pPC_TBLDAT->wBlock_Rate;
	case SCOUTER_INFO_CURSE_SUCCESS_RATE:		return pPC_TBLDAT->wCurse_Success_Rate;
	case SCOUTER_INFO_CURSE_TOLERANCE_RATE:		return pPC_TBLDAT->wCurse_Tolerance_Rate;
	default:
		{
			DBO_FAIL("Invalid scouter parts type" << uiType);
			break;
		}
	}

	return 0;
}

VOID CScouterGui::DisplayPartsInfo()
{	
	MAP_PARTS_EXPLAIN_ITER it = m_mapPartsExplain.begin();

	for( ; it != m_mapPartsExplain.end() ; ++it )
	{
		if( it->first < SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION )
		{
			// ��ī���� ������ ��ġ
            WCHAR awcBuffer[50] = {0,};
			RwUInt8 byPartsInfo = (RwUInt8)it->first;
			RwUInt32 iType = ConvertPartsInfotoStringTableIndex(byPartsInfo);

			if( SCOUTER_INFO_UPGRADE_RATE_UP		== byPartsInfo ||
				SCOUTER_INFO_ITEM_BREAK_RATE_DOWN	== byPartsInfo )
			{
				// avooo's commnet : ��ȹ�� �߰��� ����.. ���̺� �ִ� ��ġ�� ����������̴�
				// �� ) 23 -> 1.23�� �� ǥ���Ͽ��� �Ѵ�
				swprintf_s(awcBuffer, 50, GetDisplayStringManager()->GetString(iType), (RwReal)it->second/100.f + 1.f);
			}
			else
				swprintf_s(awcBuffer, 50, GetDisplayStringManager()->GetString(iType), it->second);

			// ������ �Է��Ѵ�.
			m_pPartsListBox->AddItem(awcBuffer);
		}
		else
		{
			// ��ī���� ������ ������ �Է��Ѵ�.
			RwUInt32 iType = ConvertPartsInfotoStringTableIndex(it->first);
			m_pPartsListBox->AddItem(GetDisplayStringManager()->GetString(iType));
		}		
	}	
}

RwUInt32 CScouterGui::ConvertPartsInfotoStringTableIndex(RwUInt32 iType)
{
	if( iType < SCOUTER_INFO_BEGIN_ONLY_ALLPY_MAX )
	{
		return DST_SCOUTERPARTS_NORMAL_START_LP + (iType - SCOUTER_INFO_BEGIN_DEFAULT_VALUE);
	}
	else if( iType < SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION )
	{
		return DST_SCOUTERPARTS_BEST_START + (iType - SCOUTER_INFO_BEGIN_ONLY_ALLPY_MAX);
	}
	
	return DST_SCOUTERPARTS_SPECIAL_START + (iType - SCOUTER_INFO_BEGIN_SPECIAL_FUNCTION);
}

VOID CScouterGui::OnCaptureWheelMove(RwInt32 nFlag, RwInt16 sDelta, CPos& pos)
{
	if( !IsShow() )
		return;

	if( m_pThis->GetParent()->GetChildComponentReverseAt( pos.x, pos.y ) != m_pThis )
		return;

	if( !m_pPartsListBox->HasScrollBar() )
		return;

	RwInt32 iCurIndex = m_pPartsListBox->GetTopVisibleItem();
	RwInt32 iMaxIndex = m_pPartsListBox->GetMaxVisibleItems();
	RwInt32 iDelta = iCurIndex - sDelta / GUI_MOUSE_WHEEL_DELTA;

	if( iDelta < 0 )
		iDelta = 0;
	else if( iDelta > iMaxIndex )
		iDelta = iMaxIndex;

	m_pPartsListBox->SetTopItem(iDelta);	
}

VOID CScouterGui::OnCaptureMouseDown(const CKey& key)
{
	CAPTURE_MOUSEDOWN_RAISE_TOP_LINKED(DIALOG_SCOUTER_BODY, key.m_fX, key.m_fY);
}

VOID CScouterGui::OnClicked_ExitButton(gui::CComponent* pComponent)
{	
	GetDialogManager()->CloseDialog(DIALOG_SCOUTER_BODY);
}

RwInt32 CScouterGui::SwitchDialog(bool bOpen)
{
	Show(bOpen);
	return 1;
}

VOID CScouterGui::HandleEvents( RWS::CMsg &msg )
{
	NTL_FUNCTION( "CScouterGui::HandleEvents" );

	if( msg.Id == g_EventScouter )
	{
		SDboEventScouter* pPacket = (SDboEventScouter*)msg.pData;
		switch(pPacket->iType)
		{
		case SCOUTER_EVENT_SET_SCOUTER:
			{					
				SetScouterInfo(pPacket->uiUserData);				
				break;
			}
		case SCOUTER_EVENT_UNSET_SCOUTER:
			{
				UnSetScouterInfo();
				break;
			}
		}
	}
	else if( msg.Id == g_EventSobInfoUpdate )
	{
		if( Logic_IsUpdateType(EVENT_AIUT_ITEM, msg.pData) == FALSE )
			NTL_RETURNVOID();

		SNtlEventSobInfoUpdate* pEvent = reinterpret_cast<SNtlEventSobInfoUpdate*>( msg.pData );
		if( Logic_GetAvatarHandle() != pEvent->hSerialId )
			NTL_RETURNVOID();


		UpdatePartsInfo();
	}

	NTL_RETURNVOID();
}