#include "precomp_dboclient.h"
#include "MultiDialogGui.h"

// core
#include "NtlDebug.h"

// shared
#include "NPCTable.h"
#include "TextAllTable.h"
#include "QuestTextDataTable.h"
#include "ObjectTable.h"
#include "MerchantTable.h"
#include "ItemTable.h"
#include "TableContainer.h"
#include "ItemMixMachineTable.h"

// sound
#include "GUISoundDefine.h"

// gui
#include "GuiUtil.h"
#include "AltarGui.h"
#include "NtlWorldConceptDBC.h"

// presentation
#include "NtlPLGuiManager.h"

// simulation
#include "NtlSLGlobal.h"
#include "NtlSLEvent.h"
#include "NtlSlEventFunc.h"
#include "NtlSLLogicDef.h"
#include "NtlSLLogic.h"
#include "NtlSLPacketGenerator.h"
#include "NtlSobManager.h"
#include "NtlSLApi.h"
#include "NtlSobNpc.h"
#include "NtlSobNpcAttr.h"
#include "NtlSobAvatar.h"
#include "NtlSobTriggerObject.h"
#include "NtlSobTriggerObjectAttr.h"
#include "NtlSobItem.h"
#include "NtlSobItemAttr.h"
#include "DboTSCQAgency.h"
#include "DboTSCTAgency.h"
#include "NtlSLApi.h"
#include "NtlGuild.h"
#include "NtlWareHouse.h"
#include "NtlWorldConcept.h"
#include "NtlCameraController.h"
#include "NtlWorldConcept.h"
#include "NtlFSMUtil.h"
#include "NtlSobDynamicObject.h"
#include "NtlSobDynamicObjectAttr.h"


// dbo
#include "DboEvent.h"
#include "DboEventGenerator.h"
#include "DialogManager.h"
#include "ChatBalloonManager.h"
#include "QuestGui.h"
#include "DisplayStringDef.h"
#include "DisplayStringManager.h"
#include "DboGlobal.h"
#include "SkillWindowGui.h"
#include "DojoInfoGui.h"
#include "DboLogic.h"
#include "AlarmManager.h"

//test
#include "NtlMath.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Size Define

#define COMMANDLIST_X					9
#define COMMANDLIST_Y					23	
#define COMMANDLIST_WIDTH				255
#define COMMANDLIST_HEIGHT				138

#define COMMANDLIST_LINE_HEIGHT			22
#define COMMANDLIST_LINE_MARGIN			7
#define COMMANDLIST_CHILD_XMARGIN		0
#define COMMANDLIST_SCROLLBAR_WIDTH		12
#define COMMANDLIST_SLIDER_HEIGHT		26

#define COMMANDNODE_X					0
#define COMMANDNODE_Y					0
#define COMMANDNODE_WIDTH				239
#define COMMANDNODE_HEIGHT				22

#define COMMANDTEXT_X					30

#define COMMANDNODEHTML_X				32				
#define COMMANDNODEHTML_Y				3	
#define COMMANDNODEHTML_WIDTH			217
#define COMMANDNODEHTML_HEIGHT			20

#define BRANCHCOMMANDNODEHTML_X			13				
#define BRANCHCOMMANDNODEHTML_Y			3	
#define BRANCHCOMMANDNODEHTML_WIDTH		226
#define BRANCHCOMMANDNODEHTML_HEIGHT	20

#define COMMANDNODEICON_X				15
#define COMMANDNODEICON_Y				12

#define COMMANDNODE_DOWNCOORD_DIFFX		1
#define COMMANDNODE_DOWNCOORD_DIFFY		1

#define SERVERSELECTNODE_USERCOUNT_X	193
#define SERVERSELECTNODE_USERCOUNT_Y	4

#define MULTIDIALOG_MSGBOX_Y_OFFSET		10

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMultiDialogGui

CMultiDialogGui::CMultiDialogGui(VOID)
: m_pCommandList( NULL ), m_hTargetSerialID( INVALID_SERIAL_ID ), m_pQuestGui( NULL ), m_pstbMsg( NULL )
{

}

CMultiDialogGui::CMultiDialogGui( const RwChar* pName )
: CNtlPLGui( pName ), m_pCommandList( NULL ), m_hTargetSerialID( INVALID_SERIAL_ID ), m_pQuestGui( NULL ), m_pstbMsg( NULL )
{

}

CMultiDialogGui::~CMultiDialogGui(VOID)
{

}

RwBool CMultiDialogGui::Create( CQuestGui* pQuestGui )
{
	NTL_FUNCTION( "CMultiDialogGui::Create" );

	if( !CNtlPLGui::Create( "", "gui\\MultiDialog.srf", "gui\\MultiDialog.frm" ) )
		NTL_RETURN( FALSE );

	CNtlPLGui::CreateComponents( GetNtlGuiManager()->GetGuiManager() );
	m_pThis = (gui::CDialog*)GetComponent( "dlgMain" );
	m_pstbMsg = (gui::CStaticBox*)GetComponent( "stbMsg" );
	m_MsgBackImage.SetType( CWindowby3::WT_HORIZONTAL );

	m_MsgBackImage.SetSurface( 0, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSecondTextBackup" ) );
	m_MsgBackImage.SetSurface( 1, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSecondTextBackCenter" ) );
	m_MsgBackImage.SetSurface( 2, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSecondTextBackDown" ) );

	m_slotCaptureMouseDown = GetNtlGuiManager()->GetGuiManager()->SigCaptureMouseDown().Connect( this, &CMultiDialogGui::OnCaptureMouseDown );
	m_slotCaptureWheelMove = GetNtlGuiManager()->GetGuiManager()->SigCaptureWheelMove().Connect( this, &CMultiDialogGui::OnCaptureWheelMove );

	m_slotMsgResize = m_pstbMsg->SigResize().Connect( this, &CMultiDialogGui::OnMsgResize );
	m_slotMsgMove = m_pstbMsg->SigMove().Connect( this, &CMultiDialogGui::OnMsgMove );
	m_slotPaint = m_pThis->SigPaint().Connect( this, &CMultiDialogGui::OnPaint );

	SetDialogType( TYPE_NONE );	

	Show( false );

	m_pCommandList = NTL_NEW CCommandList;
	CRectangle rect;
	rect.SetRectWH( COMMANDLIST_X, COMMANDLIST_Y, COMMANDLIST_WIDTH, COMMANDLIST_HEIGHT );
	if( !m_pCommandList->Create( rect, m_pThis, COMMANDLIST_LINE_HEIGHT, COMMANDLIST_LINE_MARGIN, COMMANDLIST_CHILD_XMARGIN, COMMANDLIST_SCROLLBAR_WIDTH, this ) )
		NTL_RETURN( FALSE );

	LinkMsg( g_EventSobNpcCommunity, 0 );
	LinkMsg( g_EventSobTriggerObjCommunity, 0 );
	LinkMsg( g_EventSobDynamicObjCommunity, 0 );
	LinkMsg( g_EventCharObjDelete, 0 );
	LinkMsg( g_EventMsgBoxResult, 0 );
	LinkMsg( g_EventTSMudosaTeleport_Req );
	LinkMsg( g_EventBudokaiMudosaInfoRes );
	LinkMsg( g_EventGambleAniEnd );
	LinkMsg( g_EventShopGambleBuyRes );

	m_pQuestGui = pQuestGui;

	NTL_RETURN( TRUE );
}

VOID CMultiDialogGui::Destroy(VOID)
{
	UnLinkMsg( g_EventSobNpcCommunity );
	UnLinkMsg( g_EventSobTriggerObjCommunity );
	UnLinkMsg( g_EventSobDynamicObjCommunity );
	UnLinkMsg( g_EventCharObjDelete );
	UnLinkMsg( g_EventMsgBoxResult );
	UnLinkMsg( g_EventTSMudosaTeleport_Req );
	UnLinkMsg( g_EventBudokaiMudosaInfoRes );
	UnLinkMsg( g_EventGambleAniEnd );
	UnLinkMsg( g_EventShopGambleBuyRes );

	if( m_pCommandList )
	{
		m_pCommandList->Destroy();
		NTL_DELETE( m_pCommandList );
	}	

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();
}

RwInt32 CMultiDialogGui::SwitchDialog( bool bOpen )
{
	// ������ �ݴ´�.
	m_pstbMsg->Show( false );	
	m_MsgBackImage.Show( false );

	if( bOpen )
	{
		if( m_stMultiDialogData.eBalloonType == sMultiDialogData::TYPE_NONE )
		{
			if( m_eDlgType == TYPE_NONE )	
			{
				//GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
				m_stMultiDialogData.Clear();
				m_hTargetSerialID = INVALID_SERIAL_ID;
				m_eDlgType = TYPE_NONE;	
				return -1;
			}
		}
		else
		{
			CNtlSob* pTargetObject = GetNtlSobManager()->GetSobObject( m_hTargetSerialID );		

			if( m_stMultiDialogData.eBalloonType == sMultiDialogData::TYPE_NPC_BALLOON )
			{
				if( pTargetObject )
				{
					GetBalloonManager()->AddNPCBalloon( pTargetObject, m_stMultiDialogData.wstrText.c_str(), BALLOON_NPC_DISPTIME, FALSE, m_stMultiDialogData.bTimeProc, 3 );					
				}
				else
				{
					SetMsgBox( m_stMultiDialogData.wstrText );					
					m_MsgBackImage.Show( true );
				}				
			}
			else if( m_stMultiDialogData.eBalloonType == sMultiDialogData::TYPE_QUEST_BALLOON )
			{
				if( pTargetObject )
				{
					GetBalloonManager()->AddQuestBalloon( pTargetObject, m_stMultiDialogData.wstrText, m_stMultiDialogData.uiQuestID, m_stMultiDialogData.bTimeProc );					
				}
				else
				{
					SetMsgBox( m_stMultiDialogData.wstrText );					
					m_MsgBackImage.Show( true );
				}							
			}
			else if( m_stMultiDialogData.eBalloonType == sMultiDialogData::TYPE_JUST_NPC_BALLOON )
			{
				if( pTargetObject )
				{
					GetBalloonManager()->AddNPCBalloon( pTargetObject, m_stMultiDialogData.wstrText.c_str(), BALLOON_NPC_DISPTIME, FALSE, m_stMultiDialogData.bTimeProc, 3 );
					//GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );					
				}				
				m_stMultiDialogData.Clear();
				m_hTargetSerialID = INVALID_SERIAL_ID;
				m_eDlgType = TYPE_NONE;	
				return -1;
			}
			else if( m_stMultiDialogData.eBalloonType == sMultiDialogData::TYPE_JUST_QUEST_BALLOON )
			{
				if( pTargetObject )
				{
					GetBalloonManager()->AddQuestBalloon( pTargetObject, m_stMultiDialogData.wstrText, m_stMultiDialogData.uiQuestID, m_stMultiDialogData.bTimeProc );
					//GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );					
				}				
				m_stMultiDialogData.Clear();
				m_hTargetSerialID = INVALID_SERIAL_ID;
				m_eDlgType = TYPE_NONE;	
				return -1;
			}			
			else if( m_stMultiDialogData.eBalloonType == sMultiDialogData::TYPE_JUST_MSG )
			{
				SetMsgBox( m_stMultiDialogData.wstrText );					
				m_MsgBackImage.Show( true );
			}
		}	

		m_stMultiDialogData.Clear();
		RaiseTop();
	}
	else
	{
		CNtlSob* pSobObject = GetNtlSobManager()->GetSobObject( m_hTargetSerialID );

		if( m_eDlgType == TYPE_NPCQUESTTALK )
		{
			CNtlSLEventGenerator::QuestNPCDialog_Res( m_pCommandList->GetTSKey() );

			if( pSobObject )
			{
				if( GetBalloonManager()->HasQuestBalloon( pSobObject ) )
					GetBalloonManager()->FadeOutBalloon( pSobObject, CBalloonGui::FIRST_TYPE_LAYER );
			}			
		}
		else if( m_eDlgType == TYPE_OBJQUESTTALK )
		{
			CNtlSLEventGenerator::QuestObjDialog_Res( m_pCommandList->GetTSKey() );
			if( pSobObject )
			{
				if( GetBalloonManager()->HasQuestBalloon( pSobObject ) )
					GetBalloonManager()->FadeOutBalloon( pSobObject, CBalloonGui::FIRST_TYPE_LAYER );
			}
		}		
		else if( m_eDlgType == TYPE_USERSELECT )
		{
			m_pCommandList->SendUserSelect( NTL_TS_TC_ID_INVALID, false );
			if( pSobObject )
			{
				if( GetBalloonManager()->HasQuestBalloon( pSobObject ) )
					GetBalloonManager()->FadeOutBalloon( pSobObject, CBalloonGui::FIRST_TYPE_LAYER );
			}			
		}
		else if( m_eDlgType == TYPE_NPCTALK || m_eDlgType == TYPE_QUESTCAT )
		{
			if( pSobObject )
			{
				if( GetBalloonManager()->HasNPCBalloon( pSobObject ) )
					GetBalloonManager()->FadeOutBalloon( pSobObject, CBalloonGui::FIRST_TYPE_LAYER );
			}			
		}
		// Gamble �� ��� �׺� Ȯ�� â�� �ݾ��ش�.
		else if( m_eDlgType == TYPE_GAMBLE )
		{
			if( pSobObject )
			{
				if( GetDialogManager()->IsOpenDialog( DIALOG_TBGAMBLERESULT ) )
					GetDialogManager()->CloseDialog( DIALOG_TBGAMBLERESULT );

				if( GetBalloonManager()->HasNPCBalloon( pSobObject ) )
					GetBalloonManager()->FadeOutBalloon( pSobObject, CBalloonGui::FIRST_TYPE_LAYER );
			}
		}

		m_stMultiDialogData.Clear();
		m_hTargetSerialID = INVALID_SERIAL_ID;
		m_eDlgType = TYPE_NONE;				
	}

	Show( bOpen );

	return 1;
}

VOID CMultiDialogGui::SendTriggerAction( vecdef_QUEST_INFO_LIST* pTriggerList, RwUInt8 eEventGenType, RwUInt32 uiOwnerID )
{
	RwInt32 nTriggerCount = (RwInt32)( pTriggerList->size() );
	if( nTriggerCount <= 0 )
		return;

	for( RwInt32 i = 0 ; i < nTriggerCount ; ++i )
	{
		CNtlSLEventGenerator::DoQuest( (*pTriggerList)[i], (eEVENT_GEN_TYPE)eEventGenType, uiOwnerID, TRUE );
	}
}

VOID CMultiDialogGui::ReserveDialog( std::wstring& wstrText, RwUInt32 uiQuestID, RwInt32 eType, RwBool bTimeProc )
{
	m_stMultiDialogData.eBalloonType = eType;
	m_stMultiDialogData.wstrText = wstrText;
	m_stMultiDialogData.bTimeProc = bTimeProc;
	m_stMultiDialogData.uiQuestID = uiQuestID;
}

VOID CMultiDialogGui::ReserveDialog( std::wstring& wstrText, RwInt32 eType, RwBool bTimeProc )
{
	m_stMultiDialogData.eBalloonType = eType;
	m_stMultiDialogData.wstrText = wstrText;
	m_stMultiDialogData.bTimeProc = bTimeProc;
}

VOID CMultiDialogGui::SetMsgBox( std::wstring& wstrText )
{
	m_pstbMsg->SetText( gui::GetHtmlFromMemoryString( wstrText.c_str(), wstrText.size() ).c_str() );
	m_pstbMsg->Show( true );
}

VOID CMultiDialogGui::HandleEvents( RWS::CMsg& msg )
{
	if( msg.Id == g_EventSobNpcCommunity )
	{
		SNtlEventSobNpcCommunity* pData = reinterpret_cast<SNtlEventSobNpcCommunity*>( msg.pData );

		// ��� Ʈ���� ���� â�� ���� ������ �ù����� ��Ƽ���̾�α׿��� ���´�. 
		// â�� ������ ���� ���� Ŭ���Ǵ� ���� ����
		if( GetDialogManager()->IsTriggerSystemDialogOpen() || m_hTargetSerialID == pData->hSerialId )
			return;

		CNtlSobNpc* pNPC = reinterpret_cast<CNtlSobNpc*>( GetNtlSobManager()->GetSobObject( pData->hSerialId ) );
		DBO_ASSERT( pNPC, "CSkillWindowGui::HandleEvents : Invalid NPC SerialID" );

		// ĳ������ ���¸� �ľ���.
		if( pNPC->IsClientUIDisable() )
			return;

		m_hTargetSerialID = pData->hSerialId;
		CNtlSobNpcAttr* pNPCAttr = reinterpret_cast<CNtlSobNpcAttr*>( pNPC->GetSobAttr() );
		sNPC_TBLDAT* pTableData = pNPCAttr->GetNpcTbl();

		// NPC ����Ʈ �� ���� üũ.
		RwUInt32	dwMultiDialogJobFlag = NPC_FUNC_FLAG_MERCHANT | NPC_FUNC_FLAG_SKILL_TRAINER | NPC_FUNC_FLAG_BANKER |
			NPC_FUNC_FLAG_GUILD_MANAGER | NPC_FUNC_FLAG_TIME_QUEST | NPC_FUNC_FLAG_PORTAL |
			NPC_FUNC_FLAG_BUDOHSI_MERCHANT | NPC_FUNC_FLAG_GAMBLE_MERCHANT |
			NPC_FUNC_FLAG_DOJO_MANAGER | NPC_FUNC_FLAG_DOJO_MERCHANT;
		RwBool		bEnableQuest = FALSE;	

		if ( NULL == GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency() ||
			NULL == GetNtlSLGlobal()->GetSobAvatar()->GetPCTriggerAgency() )
		{
			return;
		}

		SGET_QUEST_INFO* pGetQuestList = GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency()->GetQuestInfoList( (eEVENT_GEN_TYPE)pData->byInputType, pData->uiTriggerId );
		SGET_QUEST_INFO* pGetTriggerList = GetNtlSLGlobal()->GetSobAvatar()->GetPCTriggerAgency()->GetQuestInfoList( (eEVENT_GEN_TYPE)pData->byInputType, pData->uiTriggerId );

		vecdef_QUEST_INFO_LIST* vQuestList = &pGetQuestList->QuestInfoList;
		vecdef_QUEST_INFO_LIST* vTriggerList = &pGetTriggerList->QuestInfoList;

		if( vQuestList->size() > 0 )
		{
			bEnableQuest = TRUE;
		}
		else
		{
			SendTriggerAction( vTriggerList, pData->byInputType, pData->uiTriggerId );
		}

		if( pTableData->dwFunc_Bit_Flag & dwMultiDialogJobFlag || bEnableQuest )
		{
			// �������� üũ 2�� ���������� �������̸� 
			if( GetNtlWorldConcept()->IsActivePlayGrade( WORLD_CONCEPT_SECOND_GRADE ) )
			{
				// �������־��� TargetSerialID�� �����ϰ� WorldConcept �� ���õ� �޽����� ����Ѵ�.
				m_hTargetSerialID = INVALID_SERIAL_ID;
				Logic_WarnningWorldConceptActionMessage( WORLD_CONCEPT_SECOND_GRADE );
				return;
			}

			m_pCommandList->ClearNodes();			

			//! ����Ʈ�� ���� ����.
			if( bEnableQuest )
			{
				m_pCommandList->RegistCommand( CCommandList::QUEST_COMMAND );

				m_pCommandList->SetID( pData->uiTriggerId );
				m_pCommandList->SetInputType( pData->byInputType );
			}

			// ���� ��� ����
			if( pTableData->byJob == NPC_JOB_MIX_MASTER )
			{
				m_pCommandList->RegistCommand( CCommandList::HOIPOIMIX_SKILL_SET_COMMAND );
				m_pCommandList->RegistCommand( CCommandList::HOIPOIMIX_SKILL_RESET_COMMAND );
			}

			// ���� ��� �ʱ�ȭ

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_TIME_QUEST )
			{
				m_pCommandList->RegistCommand( CCommandList::TMQ_COMMAND );
			}

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_SKILL_TRAINER )
			{
				m_pCommandList->RegistCommand( CCommandList::SKILLTRAINER_COMMAND, pTableData->byJob );
			}

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_DOJO_MANAGER )
			{
				CNtlSobAvatar* pAvatar	= GetNtlSLGlobal()->GetSobAvatar();
				if( pAvatar )
				{
					CNtlGuild*	pGuild		= pAvatar->GetGuild();
					CNtlDojo*	pAvatarDojo	= pAvatar->GetDojo();
					sDOJO_INFO*	pDOJO_INFO	= pAvatarDojo->GetDojoInfo( pTableData->contentsTblidx );

					if( !pDOJO_INFO || INVALID_GUILDID == pDOJO_INFO->guildID )
					{
						m_pCommandList->RegistCommand( CCommandList::GUILD_DOJO_ESTABLISHMENT, pTableData->byJob );
					}
					else
					{
						m_pCommandList->RegistCommand( CCommandList::GUILD_DOJO_INFO, pTableData->byJob );
					}

					m_pCommandList->RegistCommand( CCommandList::GUILD_DOJO_POINTUSE, pTableData->byJob );

					if( pGuild->IsExistFunction(DBO_GUILD_FUNCTION_CAN_MAKE_DOJO_DOGI) )
						m_pCommandList->RegistCommand( CCommandList::GUILD_DOGI, pTableData->byJob );
				}
			}

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_MERCHANT ||
				pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_DOJO_MERCHANT )
			{
				// õ������ ����ȸ ������ NPC_FUNC_FLAG_MERCHANT�� NPC_FUNC_FLAG_BUDOHSI_MERCHANT �÷��׸� ������ �ִ�
				// NPC_FUNC_FLAG_BUDOHSI_MERCHANT �÷��� �˻������� RegistCommand �Լ��� ȣ������
				if( pTableData->byJob != NPC_JOB_BUDOHSI_MERCHANT )
				{
					m_pCommandList->RegistCommand( CCommandList::MERCHANT_COMMAND, pTableData->byJob );
				}
			}

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_BUDOHSI_MERCHANT )
			{
				m_pCommandList->RegistCommand( CCommandList::BUDOHSI_MERCHANT_COMMAND, pTableData->byJob );				
			}

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_BANKER )
			{
				CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
				if( pAvatar )
				{
					m_pCommandList->RegistCommand( CCommandList::BANKER_COMMAND );

					if( GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse()->CanUseGuileWarehouse() )
						m_pCommandList->RegistCommand( CCommandList::GUILD_BANK_COMMAND );

					m_pCommandList->RegistCommand( CCommandList::BUY_BANK_COMMAND );

					// ó�� â��NPC�� ��ȭ�� �ϸ� �ڽ��� â�� ������ �����κ��� �޴´�.
					// â�� ������ �˰� �־�� �ڽ��� �� �� �� �ִ� â�� �˾ƺ� �� �ִ�

					CNtlWarehouse* pWarehouse = pAvatar->GetWarehouse();
					if( pWarehouse->GetSlotSerailID(0) == INVALID_SERIAL_ID )
						GetDboGlobal()->GetGamePacketGenerator()->SendBankLoadReq( pNPC->GetSerialID() );

					if( NPC_JOB_DOJO_BANKER == pTableData->byJob )
					{
						m_pCommandList->RegistCommand( CCommandList::GUILD_DOJO_ACCOUNT, pTableData->byJob );
					}
				}								
			}

			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_GUILD_MANAGER )
			{
				m_pCommandList->RegistCommand( CCommandList::GUILD_COMMAND );				
			}

			if(pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_PORTAL)       // ��Ż��
			{
				m_pCommandList->RegistCommand( CCommandList::PORTAL_COMMAND );	
			}
			
			// Gamble ����� Merchant Table�� Need_Mileage �ʵ��� ���� �����ϴ� ������ �����Ѵ�.
			// -by Kell ( 09. 07. 22 )
			if(pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_GAMBLE_MERCHANT )
			{
				m_pCommandList->RegistCommand( CCommandList::GAMBLE_BUY_COMMNAD );	
				m_pCommandList->RegistCommand( CCommandList::EXIT_COMMAND );

				// Merchant Table�� ���� ù��° Index�� �����Ѵ�.
				if( pTableData->amerchant_Tblidx[0] == INVALID_TBLIDX )
				{
					DBO_FAIL( "[GAMBLE] NPC Table havn't merchant table index." << pTableData->tblidx );
					return;
				}
				
				sMERCHANT_TBLDAT* pMerchantTblDat = (sMERCHANT_TBLDAT*)API_GetTableContainer()->GetMerchantTable()->FindData( pTableData->amerchant_Tblidx[0] );
				if( !pMerchantTblDat )
				{
					DBO_FAIL( "[GAMBLE] Merchant table index is invalid." << pTableData->amerchant_Tblidx[0] );
					return;
				}

				WCHAR awcBuffer[256];
				swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( DST_GAMBLE_GUIDE ), pMerchantTblDat->dwNeedMileage );
				ReserveDialog( std::wstring(awcBuffer), sMultiDialogData::TYPE_JUST_MSG, FALSE );

				SetDialogType( TYPE_NPCTALK );
				if( GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() ) )
				{
					CNtlSLEventGenerator::CameraNpc( pData->hSerialId );
					GetNtlWorldConcept()->AddWorldPlayConcept( WORLD_PLAY_NPC_COMMU );

					// Npc handle ����( FSM ���� ��� )
					CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(GetNtlSLGlobal()->GetSobAvatar()->GetBehaviorData()); 
					SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff();
					pCtrlStuff->uExtra.sGamble.hGambleNpc = pData->hSerialId;
				}				

				return;
			}

			//! ���׷��̵�� ���� ���߿�.
			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_MERCHANT )
			{
				m_pCommandList->RegistCommand( CCommandList::UPGRADE_COMMAND );
			}

			// ������� �⺻.
			m_pCommandList->RegistCommand( CCommandList::EXIT_COMMAND );

			// Dialog������ �Է�.
			CTextTable* pNPCText = API_GetTableContainer()->GetTextAllTable()->GetNPCTbl();
			std::wstring wstrText;
			pNPCText->GetText( pTableData->Dialog_Script_Index, &wstrText );

			if ( NULL == GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency() )
				return;

			if( GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency()->HasEventNPCInProgressQuest( pTableData->tblidx ) )
				ReserveDialog( std::wstring(), sMultiDialogData::TYPE_NONE, FALSE );
			else
				ReserveDialog( wstrText, sMultiDialogData::TYPE_NPC_BALLOON, FALSE );			

			// Dialog ���
			SetDialogType( TYPE_NPCTALK );
			if( GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() ) )
			{
				CNtlSLEventGenerator::CameraNpc( pData->hSerialId );
				GetNtlWorldConcept()->AddWorldPlayConcept( WORLD_PLAY_NPC_COMMU );

				// npc handle ����(FSM���� ��� - ����)
				CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(GetNtlSLGlobal()->GetSobAvatar()->GetBehaviorData()); 
				SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff();
				pCtrlStuff->uExtra.sTeleport.hTeleportNpc = pData->hSerialId;
			}			
		}
		else
		{
			if( pTableData->Dialog_Script_Index == INVALID_TBLIDX )
				return;

			CTextTable* pNPCTextTable = API_GetTableContainer()->GetTextAllTable()->GetNPCTbl();
			std::wstring wstrText;
			pNPCTextTable->GetText( pTableData->Dialog_Script_Index, &wstrText );

			if ( NULL == GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency() )
				return;

			if( GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency()->HasEventNPCInProgressQuest( pTableData->tblidx ) )
				ReserveDialog( std::wstring(), sMultiDialogData::TYPE_NONE, FALSE );
			else
				ReserveDialog( wstrText, sMultiDialogData::TYPE_JUST_NPC_BALLOON, TRUE );

			// Dialog ��� ��������� ���� �����ڸ��� �ٷ� ������ NPCDialog���� �ݴ� �뵵�θ� ���ȴ�.
			SetDialogType( TYPE_NONE );
			GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );
		}


		// ���� �����̰� �ִ� npc�� ��� ��� (����)
		CNtlSobActor *pSobActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pData->hSerialId) );
		if(pSobActor)
		{
			if( pTableData->dwFunc_Bit_Flag & NPC_FUNC_FLAG_FACING )
				API_GetSLPacketGenerator()->SendCharTargetFacing(pData->hSerialId);
		}

	}
	else if( msg.Id == g_EventSobTriggerObjCommunity )
	{
		SNtlEventSobTriggerObjCommunity* pData = reinterpret_cast<SNtlEventSobTriggerObjCommunity*>( msg.pData );

		// ��� Ʈ���� ���� â�� ���� ������ �ù����� ��Ƽ���̾�α׿��� ���´�. 
		if( GetDialogManager()->IsTriggerSystemDialogOpen() || m_hTargetSerialID == pData->hSerialId )
			return;

		if ( NULL == GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency() ||
			NULL == GetNtlSLGlobal()->GetSobAvatar()->GetPCTriggerAgency() )
			return;

		SGET_QUEST_INFO* pGetQuestList = GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency()->GetQuestInfoList( (eEVENT_GEN_TYPE)pData->byInputType, pData->uiTriggerId );
		SGET_QUEST_INFO* pGetTriggerList = GetNtlSLGlobal()->GetSobAvatar()->GetPCTriggerAgency()->GetQuestInfoList( (eEVENT_GEN_TYPE)pData->byInputType, pData->uiTriggerId );

		vecdef_QUEST_INFO_LIST* vQuestList = &pGetQuestList->QuestInfoList;
		vecdef_QUEST_INFO_LIST* vTriggerList = &pGetTriggerList->QuestInfoList;

		if( vQuestList->size() > 0 )
		{
			m_pCommandList->SetID( pData->uiTriggerId );
			m_pCommandList->SetInputType( pData->byInputType );
			m_pCommandList->SendQuest();

			SetDialogType( TYPE_NPCTALK );
			GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );
		}
		else
		{
			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_BIND )
			{
				CNtlSobTriggerObject* pTriggerObj = reinterpret_cast<CNtlSobTriggerObject*>( GetNtlSobManager()->GetSobObject( pData->hSerialId ) );
				DBO_ASSERT( pTriggerObj, "CMultiDialogGui::HandleEvents : TriggerObj Serial( " << pData->hSerialId << " )�� �������� �ʽ��ϴ�." );
				CNtlSobTriggerObjectAttr* pTriggerObjAttr = reinterpret_cast<CNtlSobTriggerObjectAttr*>( pTriggerObj->GetSobAttr() );

				sMsgBoxData data;
				data.uiTblIdx = pTriggerObjAttr->GetTriggerObjectTbl()->tblidx;
				GetAlarmManager()->AlarmMessage( DST_BIND_TEXT, FALSE, &data );
			}

			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_PORTAL )
			{
				// ��Ż
			}

			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_SCOUTER )
			{

			}

			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_SELECTION )
			{

			}

			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_RANK_BATTLE )
			{
				CDboEventGenerator::NPCDialogOpen( pData->hSerialId, DIALOG_RBBOARD );
			}

			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_MAIL_BOX )
			{
				CDboEventGenerator::NPCDialogOpen( pData->hSerialId, DIALOG_MAILSYSTEM );
			}

			if((pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_NORMAL_DRAGONBALL) ||
				(pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_RAID_DRAGONBALL))
			{
				// �巡�ﺼ ��� ��ȯ
				GetNtlWorldConcept()->AddWorldPlayConcept(WORLD_PLAY_DRAGONBALL_COLLECT);
				CNtlWorldConceptDBC* pWorldConceptDBC = (CNtlWorldConceptDBC*)GetNtlWorldConcept()->GetWorldConceptController(WORLD_PLAY_DRAGONBALL_COLLECT);
				pWorldConceptDBC->SetAltarSerialID(pData->hSerialId);

				CAltarGui::CreateInstance();				
				GetDialogManager()->OpenDialog(DIALOG_DBC_ALTAR);
			}

			if( pGetTriggerList->dwType & eDBO_TRIGGER_OBJECT_FUNC_HOIPOIMIX )
			{
				m_hTargetSerialID = pData->hSerialId;
							
				m_pCommandList->ClearNodes();			

				m_pCommandList->RegistCommand( CCommandList::HOIPOIMIX_CREATE_COMMAND );

				// ������� �⺻.
				m_pCommandList->RegistCommand( CCommandList::EXIT_COMMAND );

				// Dialog ���
				SetDialogType( TYPE_NPCTALK );
				if( GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() ) )
				{
					CNtlSLEventGenerator::CameraNpc( pData->hSerialId );
					GetNtlWorldConcept()->AddWorldPlayConcept( WORLD_PLAY_NPC_COMMU );

					// npc handle ����(FSM���� ��� - ����)
					CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(GetNtlSLGlobal()->GetSobAvatar()->GetBehaviorData()); 
					SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff();
					pCtrlStuff->uExtra.sTeleport.hTeleportNpc = pData->hSerialId;
				}				
			}

			SendTriggerAction( vTriggerList, pData->byInputType, pData->uiTriggerId );
		}

		//
		API_GetSLPacketGenerator()->SendTSExcuteTriggerObject( GetNtlSLGlobal()->GetSobAvatar()->GetSerialID(), pData->hSerialId, pData->byInputType, 0xffffffff );
	}
	else if( msg.Id == g_EventQuestDirectForward )
	{
		// peessi : User Select�� ��쿡�� ���´�.

		SNtlEventQuestDirect_Forward* pData = reinterpret_cast<SNtlEventQuestDirect_Forward*>( msg.pData );
		SNtlEventQuestUserSelectDialog_Req* pReqData = &pData->sUserSelect;

		// peessi : MultiDialog�� �����ִٸ�, Ŀ�´�Ƽ ���� �̰ų�, ����Ʈ ���̾�α�, ���� ������ �ϳ� �̹Ƿ� ���.
		if( IsShow() )
		{
			SNtlEventQuestDirect_Echo stEcho;
			stEcho.sProposal.bResult = false;
			stEcho.sProposal.sTSKey	= pReqData->sTSKey;
			stEcho.eTDType = ETD_QuestUserSelect;
			stEcho.pTCUnit = pData->pTCUnit;

			CNtlSLEventGenerator::QuestTriggerDirectEcho( &stEcho );
			return;
		}

		// Serial �Է�.
		if( pReqData->uiTargetType == eUSER_SEL_TARGET_TYPE_NPC )
			m_hTargetSerialID = GetNtlSobManager()->GetNpcTriggerSerialFromId( pReqData->uiTargetTblIdx );
		else if( pReqData->uiTargetType == eUSER_SEL_TARGET_TYPE_OBJECT )
			m_hTargetSerialID = GetNtlSobManager()->GetObjectTriggerSerialFromId( pReqData->uiTargetTblIdx );

		// ���
		m_pCommandList->ClearNodes();
		m_pCommandList->SetTCUnit( pData->pTCUnit );
		m_pCommandList->SetTSKey( pReqData->sTSKey );

		CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable();
		sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( pReqData->uiConv ) );
		if( pQuestText )
		{
			ReserveDialog( pQuestText->wstrText, pReqData->uiConv, sMultiDialogData::TYPE_QUEST_BALLOON, FALSE );			
		}

		for( RwInt32 i = 0 ; i < pReqData->nBranchCnt ; ++i )
		{	
			m_pCommandList->RegistQuestCommand( pReqData->asBranchInfo[i].uiBranchText, pReqData->asBranchInfo[i].tcID );
		}
		m_pCommandList->RegistExitCommand( CCommandNode::BRANCHDIALOG_NODE );

		SetDialogType( TYPE_USERSELECT );	
		GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );
	}
	else if( msg.Id == g_EventQuestNPCDialog_Req )
	{
		SNtlEventQuestNPCDialog_Req* pData = reinterpret_cast<SNtlEventQuestNPCDialog_Req*>( msg.pData );

		// peessi : MultiDialog�� �����ִٸ�, Ŀ�´�Ƽ ���� �̰ų�, ����Ʈ ���̾�α�, ���� ������ �ϳ� �̹Ƿ� ���.
		if( IsShow() )
		{
			CNtlSLEventGenerator::QuestNPCDialog_Res( pData->sTSKey );
			return;
		}

		RwUInt32 hSerial = GetNtlSobManager()->GetNpcTriggerSerialFromId( pData->uiNPCIdx );
		if( hSerial == INVALID_SERIAL_ID )
		{
			CNtlSLEventGenerator::QuestNPCDialog_Res( pData->sTSKey );
			return;
		}

		m_hTargetSerialID = hSerial;

		if( pData->eNPCConvType == eNPCCONV_TYPE_DIALOGBOX )
		{
			m_pCommandList->ClearNodes();
			m_pCommandList->SetTSKey( pData->sTSKey );
			m_pCommandList->RegistExitCommand( CCommandNode::QUESTDIALOG_NODE );

			CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable()	;
			sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( pData->uiDesc ) );

			SetDialogType( TYPE_NPCQUESTTALK );

			if( pQuestTextTable )
				ReserveDialog( pQuestText->wstrText, pData->uiDesc, sMultiDialogData::TYPE_QUEST_BALLOON, FALSE );				
			else
				ReserveDialog( std::wstring( L"InvalidQuestText" ), pData->uiDesc, sMultiDialogData::TYPE_QUEST_BALLOON, FALSE );				
		}
		else if( pData->eNPCConvType == eNPCCONV_TYPE_TOOLTIP )
		{
			CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable();
			sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( pData->uiDesc ) );

			SetDialogType( TYPE_NONE );

			if( pQuestText )
				ReserveDialog( pQuestText->wstrText, pData->uiDesc, sMultiDialogData::TYPE_JUST_QUEST_BALLOON, TRUE );			
			else
				ReserveDialog( std::wstring( L"InvalidQuestText" ), pData->uiDesc, sMultiDialogData::TYPE_JUST_QUEST_BALLOON, TRUE );			

			CNtlSLEventGenerator::QuestNPCDialog_Res( pData->sTSKey );
		}		

		GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );
	}
	else if( msg.Id == g_EventQuestObjDialog_Req )
	{
		SNtlEventQuestObjDialog_Req* pData = reinterpret_cast<SNtlEventQuestObjDialog_Req*>( msg.pData );

		// peessi : MultiDialog�� �����ִٸ�, Ŀ�´�Ƽ ���� �̰ų�, ����Ʈ ���̾�α�, ���� ������ �ϳ� �̹Ƿ� ���.
		if( IsShow() )
		{
			CNtlSLEventGenerator::QuestObjDialog_Res( pData->sTSKey );
			return;
		}

		RwUInt32 hSerial = GetNtlSobManager()->GetObjectTriggerSerialFromId( pData->uiObjIdx );
		if( hSerial == INVALID_SERIAL_ID )
		{
			CNtlSLEventGenerator::QuestObjDialog_Res( pData->sTSKey );
			return;
		}

		m_hTargetSerialID = hSerial;

		if( pData->eObjConvType == eOBJCONV_TYPE_DIALOGBOX )
		{
			m_pCommandList->ClearNodes();
			m_pCommandList->SetTSKey( pData->sTSKey );
			m_pCommandList->RegistExitCommand( CCommandNode::QUESTDIALOG_NODE );

			CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable()	;
			sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( pData->uiDesc ) );

			SetDialogType( TYPE_OBJQUESTTALK );

			if( pQuestText )
				ReserveDialog( pQuestText->wstrText, pData->uiDesc, sMultiDialogData::TYPE_QUEST_BALLOON, FALSE );			
			else
				ReserveDialog( std::wstring( L"Invalid QuestText" ), pData->uiDesc, sMultiDialogData::TYPE_QUEST_BALLOON, FALSE );			
		}
		else if( pData->eObjConvType == eOBJCONV_TYPE_TOOLTIP )
		{
			CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable();
			sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( pData->uiDesc ) );

			SetDialogType( TYPE_NONE );	

			if( pQuestText )
				ReserveDialog( pQuestText->wstrText, pData->uiDesc, sMultiDialogData::TYPE_JUST_QUEST_BALLOON, TRUE );			
			else
				ReserveDialog( std::wstring( L"Invalid QuestText" ), pData->uiDesc, sMultiDialogData::TYPE_JUST_QUEST_BALLOON, TRUE );			

			CNtlSLEventGenerator::QuestObjDialog_Res( pData->sTSKey );
		}		

		GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );
	}
	else if( msg.Id == g_EventDialog )
	{
		SDboEventDialog* pData = reinterpret_cast<SDboEventDialog*>( msg.pData );
		if( pData->iType == DIALOGEVENT_NPC_BYEBYE && pData->iDestDialog == DIALOG_MULTIDIALOG )
		{
			if( m_eDlgType == TYPE_USERSELECT )
			{
				m_pCommandList->SendUserSelect( NTL_TS_TC_ID_INVALID, false );
			}
			else if( m_eDlgType == TYPE_SERVERSELECT )
			{
				CNtlSLEventGenerator::TSMudosaTeleport_Res( m_pCommandList->GetTSKey(), INVALID_BYTE, TRUE );				
			}
			else
			{
				CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
				GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
			}			

			GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );			
		}		
	}
	else if( msg.Id == g_EventCharObjDelete )
	{
		RwUInt32* pDeleteSerial = reinterpret_cast<RwUInt32*>( msg.pData );

		if( m_hTargetSerialID != INVALID_SERIAL_ID && *pDeleteSerial == m_hTargetSerialID )
		{
			if( m_eDlgType == TYPE_USERSELECT )
				m_pCommandList->SendUserSelect( NTL_TS_TC_ID_INVALID, false );
			else
			{
				CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
				GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
			}			

			GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );			
		}
	}
	else if( msg.Id == g_EventMsgBoxResult )
	{
		SDboEventMsgBoxResult *pMsgBoxResult = reinterpret_cast<SDboEventMsgBoxResult*>( msg.pData );

		if( pMsgBoxResult->uiWorkId == MBW_BIND_POPOSTONE )
		{
			if( pMsgBoxResult->eResult == MBR_OK )
				API_GetSLPacketGenerator()->SendCharBindReq( pMsgBoxResult->pData->uiTblIdx );		
		}
	}
	else if( msg.Id == g_EventUnregQuest_Nfy )
	{
		switch( m_eDlgType )
		{
		case TYPE_USERSELECT:			
		case TYPE_NPCQUESTTALK:
		case TYPE_OBJQUESTTALK:
			{
				SNtlEventUnregQuest_Nfy* pDeleteData = reinterpret_cast<SNtlEventUnregQuest_Nfy*>( msg.pData );

				if( pDeleteData->sTSKey.tID == m_pCommandList->GetTSKey().tID )
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
				}
			}
			break;
		case TYPE_QUESTCAT:
			{
				// ����Ʈ �����
				m_pCommandList->SendQuest();
			}
			break;
		default:
			return;
		}
	}
	else if( msg.Id == g_EventTSRemovingTMQQuest_Nfy )
	{
		switch( m_eDlgType )
		{
		case TYPE_USERSELECT:
		case TYPE_NPCQUESTTALK:
		case TYPE_OBJQUESTTALK:
			{
				SNtlEventTSRemovingTMQQuest_Nfy* pData = reinterpret_cast<SNtlEventTSRemovingTMQQuest_Nfy*>( msg.pData );

				if( pData->tRmvTSId == m_pCommandList->GetTSKey().tID )
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
				}
			}
			break;
		case TYPE_QUESTCAT:
			{
				// ����Ʈ �����
				m_pCommandList->SendQuest();
			}
			break;
		}
	}
	else if( msg.Id == g_EventTSMudosaTeleport_Req )
	{
		// ������ ����Ʈ �ȳ� ��Ŷ ���� ������ ��Ŷ �ް� �װɷ� ����
		SNtlEventTSMudosaTeleport_Req* pData = reinterpret_cast<SNtlEventTSMudosaTeleport_Req*>( msg.pData );
		m_pCommandList->SetTSKey( pData->sTSKey );

		GetDboGlobal()->GetGamePacketGenerator()->SendBudokaiMudosaInfoReq();
	}
	else if( msg.Id == g_EventBudokaiMudosaInfoRes )
	{
		SNtlEventBudokaiMudosaInfoRes* pData = reinterpret_cast<SNtlEventBudokaiMudosaInfoRes*>( msg.pData );

		m_pCommandList->ClearNodes();

		for( RwInt32 i = 0 ; i < pData->byMudosaCount ; ++i )
		{
			WCHAR awcBuffer[256];
			swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( DST_BUDOKAI_MUDOSA_INFO ), i );
			m_pCommandList->RegistServerSelectCommand( i, awcBuffer, pData->aMudosaInfo[i].wCurrentUserCount );			
		}		

		m_pCommandList->RegistExitCommand( CCommandNode::SERVERSELECT_MODE );

		SetDialogType( TYPE_SERVERSELECT );
		ReserveDialog( std::wstring( GetDisplayStringManager()->GetString( DST_BUDOKAI_MUDOSA_TELEPOR_INFO ) ), sMultiDialogData::TYPE_JUST_MSG, FALSE );		
		GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );
	}
	// �׺� NPC�� �ִϸ��̼��� ������ ��� ���� ���������� ��Ŷ�� ��û�ؾ� �Ѵ�.
	else if( msg.Id == g_EventGambleAniEnd )
	{
		SNtlEventGambleAniEnd* pData = reinterpret_cast<SNtlEventGambleAniEnd*>( msg.pData );

		GetDboGlobal()->GetGamePacketGenerator()->SendShopGambleBuyReq( pData->hGambleNpc );
	}
	else if( msg.Id == g_EventShopGambleBuyRes )
	{
		SDboEventShopGambleBuyRes* pResult = reinterpret_cast<SDboEventShopGambleBuyRes*>( msg.pData );

		m_hTargetSerialID = pResult->hHandle;

		CNtlSobNpc* pNPC = reinterpret_cast<CNtlSobNpc*>( GetNtlSobManager()->GetSobObject( GetTargetSerial() ) );
		DBO_ASSERT( pNPC, "CMultiDialogGui::HandleEvents - Invalid NPC SerialID" );

		m_pCommandList->ClearNodes();
		m_pCommandList->RegistCommand( CCommandList::GAMBLE_BUY_COMMNAD );	
		m_pCommandList->RegistCommand( CCommandList::EXIT_COMMAND );

		CNtlSobNpcAttr* pNPCAttr = reinterpret_cast<CNtlSobNpcAttr*>( pNPC->GetSobAttr() );
		sNPC_TBLDAT* pTableData = pNPCAttr->GetNpcTbl();

		// Merchant Table�� ���� ù��° Index�� �����Ѵ�.
		if( pTableData->amerchant_Tblidx[0] == INVALID_TBLIDX )
		{
			DBO_FAIL( "[GAMBLE] NPC Table havn't merchant table index." << pTableData->tblidx );
			return;
		}

		sMERCHANT_TBLDAT* pMerchantTblDat = (sMERCHANT_TBLDAT*)API_GetTableContainer()->GetMerchantTable()->FindData( pTableData->amerchant_Tblidx[0] );
		if( !pMerchantTblDat )
		{
			DBO_FAIL( "[GAMBLE] Merchant table index is invalid." << pTableData->amerchant_Tblidx[0] );
			return;
		}

		SetDialogType( TYPE_GAMBLE );
		WCHAR awcBuffer[256];
		swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( DST_GAMBLE_GUIDE ), pMerchantTblDat->dwNeedMileage );
		ReserveDialog( std::wstring(awcBuffer), sMultiDialogData::TYPE_JUST_MSG, FALSE );
		GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() );

		if( pResult->wResultCode != GAME_SUCCESS )
		{
			GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
			return;
		}

		CNtlSobItem* pSobItem =  reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(pResult->hItem));
		if( pSobItem == NULL )
		{
			DBO_ASSERT( pNPC, "CMultiDialogGui::HandleEvents - Invalid Item Handle" );
			return;
		}
	}
	else if( msg.Id == g_EventSobDynamicObjCommunity )
	{
		SNtlEventSobDynamicObjCommunity* pData = reinterpret_cast<SNtlEventSobDynamicObjCommunity*>( msg.pData );

		// ��� Ʈ���� ���� â�� ���� ������ �ù����� ��Ƽ���̾�α׿��� ���´�. 
		// â�� ������ ���� ���� Ŭ���Ǵ� ���� ����
		if( GetDialogManager()->IsTriggerSystemDialogOpen() || m_hTargetSerialID == pData->hSerialId )
			return;

		CNtlSobDynamicObject* pObj = reinterpret_cast<CNtlSobDynamicObject*>( GetNtlSobManager()->GetSobObject( pData->hSerialId ) );
		DBO_ASSERT( pObj, "CSkillWindowGui::HandleEvents : Invalid NPC SerialID" );

		m_hTargetSerialID = pData->hSerialId;
		CNtlSobDynamicObjectAttr* pObjAttr = reinterpret_cast<CNtlSobDynamicObjectAttr*>( pObj->GetSobAttr() );

		m_pCommandList->ClearNodes();

		RwUInt8 byDynamicObjectType = pObjAttr->GetDynamicObjectType();
		switch( byDynamicObjectType )
		{
		case eDBO_DYNAMIC_OBJECT_TYPE_HOIPOI_MIX_MACHINE:
			{
				// HoipoiMix Table
				CItemMixMachineTable* pMachineTable = API_GetTableContainer()->GetItemMixMachineTable();
				NTL_ASSERT( pMachineTable, "ItemMixMachine Table is null");

				sITEM_MIX_MACHINE_TBLDAT* pTblData = (sITEM_MIX_MACHINE_TBLDAT*)pMachineTable->FindData( pObjAttr->GetTableIndexForType() );
				NTL_ASSERT( pTblData, "ItemMixMachine Table index is invalid." << pObjAttr->GetTableIndexForType() );

				m_pCommandList->RegistCommand( CCommandList::HOIPOIMIX_CREATE_COMMAND );

				if( pTblData->byMachineType != eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NORMAL &&
					pObj->GetOwnerID() == GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() )
				{
					m_pCommandList->RegistCommand( CCommandList::HOIPOIMIX_DESTROY_MACHINE_COMMAND );
				}
			}
			break;
		case eDBO_DYNAMIC_OBJECT_TYPE_CAPSULE_HOUSE:
			{
			}
			break;
		default:
			{
			}
			break;
		}
			
		// ������� �⺻.
		m_pCommandList->RegistCommand( CCommandList::EXIT_COMMAND );

		// Dialog ���
		SetDialogType( TYPE_NPCTALK );
		if( GetDialogManager()->OpenDialog( DIALOG_MULTIDIALOG, GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() ) )
		{
			CNtlSLEventGenerator::CameraNpc( pData->hSerialId );
			GetNtlWorldConcept()->AddWorldPlayConcept( WORLD_PLAY_NPC_COMMU );

			// npc handle ����(FSM���� ��� - ����)
			CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(GetNtlSLGlobal()->GetSobAvatar()->GetBehaviorData()); 
			SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff();
			pCtrlStuff->uExtra.sTeleport.hTeleportNpc = pData->hSerialId;
		}
	}
}

//VOID CMultiDialogGui::OnClickExitButton( gui::CComponent* pComponent )
//{
//	GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
//}

VOID CMultiDialogGui::OnCaptureMouseDown( const CKey& key )
{
	CAPTURE_MOUSEDOWN_RAISE( DIALOG_MULTIDIALOG, key.m_fX, key.m_fY );
}

VOID CMultiDialogGui::OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos )
{
	CAPTURE_MOUSEWHEELMOVE_SCROLLBAR( IsShow(), m_pThis, m_pThis, m_pCommandList->GetScrollBar(), sDelta, pos );
}

VOID CMultiDialogGui::OnMsgResize( RwInt32 nOldCX, RwInt32 nOldCY )
{
	CRectangle rtMsg = m_pstbMsg->GetScreenRect();
	m_MsgBackImage.SetSize( rtMsg.GetWidth() + 10, rtMsg.GetHeight() + 9 );
	m_pstbMsg->SetPosition( 0, -( rtMsg.GetHeight() + MULTIDIALOG_MSGBOX_Y_OFFSET ) );
}

VOID CMultiDialogGui::OnMsgMove( RwInt32 nOldX, RwInt32 nOldY )
{
	CRectangle rtMsg = m_pstbMsg->GetScreenRect();

	m_MsgBackImage.SetPosition( rtMsg.left, rtMsg.top );
}

VOID CMultiDialogGui::OnPaint(VOID)
{
	m_MsgBackImage.Render();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCommandList

CCommandList::CCommandList(VOID)
: ClearProc( &CCommandList::ClearState_No ), m_uiId( 0xffffffff ), m_byInputType( 0xff ), m_pTCUnit( NULL )
{

}

CCommandList::~CCommandList(VOID)
{

}

RwBool CCommandList::Create( CRectangle& rect, gui::CComponent* pParent, RwInt32 nLineHeight, RwInt32 nLineMargin, RwInt32 nChildXMargin, RwInt32 nScrollBarWidth, CMultiDialogGui* pOwnerGui )
{
	if( !CGuiLineTree::Create( rect, pParent, nLineHeight, nLineMargin, nChildXMargin, nScrollBarWidth ) )
		return FALSE;

	m_pScroll->AddSurfaceLayout( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfScrollLayout" ) );
	m_pScroll->AddSurfaceSlider( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfScrollSmall" ) );
	m_pScroll->SetButtonSize( 0, 0 );
	m_pScroll->SetSliderSize( COMMANDLIST_SCROLLBAR_WIDTH, COMMANDLIST_SLIDER_HEIGHT );

	m_slotPaint = m_pLineTree->SigPaint().Connect( this, &CCommandList::OnClear );

	m_pOwnerGui = pOwnerGui;

	return TRUE;
}

VOID CCommandList::RegistCommand( RwInt32 nID, RwUInt8 ucJob /* = 0xFF  */)
{
	gui::CSurface	surface;
	std::wstring	wstrText;

	switch( nID )
	{
	case MERCHANT_COMMAND:
		switch( ucJob )
		{
		case NPC_JOB_WEAPON_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfWeaponMerchantIcon" ); break;
		case NPC_JOB_ARMOR_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfArmorMerchantIcon" ); break;
		case NPC_JOB_GOODS_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfMiscMerchantIcon" ); break;
		case NPC_JOB_SCOUTER_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfScouterMerchantIcon" ); break;
		case NPC_JOB_DOGI_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfDogiMerchantIcon" ); break;
		case NPC_JOB_SPECIAL_WEAPON_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSPWeaponMerchantIcon" ); break;
		case NPC_JOB_SPECIAL_ARMOR_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSPArmorMerchantIcon" ); break;
		case NPC_JOB_SPECIAL_GOODS_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSPMiscMerchantIcon" ); break;
		case NPC_JOB_SPECIAL_SCOUTER_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSPScouterMerchantIcon" ); break;
		case NPC_JOB_SPECIAL_FOODS_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSPFoodMerchantIcon" ); break;
		case NPC_JOB_SUB_WEAPON_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" ); break;
		case NPC_JOB_DOJO_MANAGER: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" ); break;
		case NPC_JOB_DOJO_MERCHANT: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" ); break;
		case NPC_JOB_DOJO_SEAL: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" ); break;
		case NPC_JOB_DOJO_BANKER: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" ); break;
		case NPC_JOB_MIX_MASTER: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" ); break; ///< �����ؾ���
		default: DBO_FAIL( "NPC Table Job, JobFlag Error" ); break;
		}
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_SHOP );
		break;
	case BUDOHSI_MERCHANT_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSubWeaponMerchantIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_SHOP );
		break;
	case SKILLTRAINER_COMMAND:
		if( ucJob >= NPC_JOB_SKILL_TRAINER_HFI && ucJob <= NPC_JOB_SKILL_TRAINER_MWO )
			surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfSkillMasterIcon" );
		else if( ucJob >= NPC_JOB_GRAND_SKILL_TRAINER_HFI && ucJob <= NPC_JOB_GRAND_SKILL_TRAINER_MWO )
			surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGrandSkillMasterIcon" );
		else
			DBO_FAIL( "NPC Table Job, JobFlag Error" );

		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_SKILL );
		break;
	case BANKER_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfWareHouseIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_BANK );
		break;
	case BUY_BANK_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfWareHouseIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_BUY_BANK );
		break;
	case GUILD_BANK_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfWareHouseIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_OPEN_GUILD_BANK );
		break;
	case QUEST_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfQuestIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_QUEST );
		break;
	case UPGRADE_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfWeaponMerchantIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_UPGRADE );
		break;
	case EXIT_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT );
		break;
	case GUILD_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGuildIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_GUILD );
		break;
	case TMQ_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfTimeMachineIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_TMQ );
		break;
	case PORTAL_COMMAND:    // ��Ż NPC
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfKeeperIcon" );        
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_PORTAL );
		break;
	case GAMBLE_BUY_COMMNAD:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_GAMBLE_COMMAND );
		break;
	case HOIPOIMIX_CREATE_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfHoipoiCreateIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_HOIPOIMIX_CREATE );
		break;
	case HOIPOIMIX_DESTROY_MACHINE_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfHoipoiDelete" );
		wstrText = GetDisplayStringManager()->GetString( DST_HOIPOIMIX_MACHINE_DEL );
		break;
	case GUILD_DOJO_ESTABLISHMENT:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_DOJO_ESTABLISHMENT );
		break;
	case GUILD_DOJO_INFO:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_DOJO_INFO );
		break;
	case GUILD_DOJO_POINTUSE:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_POINT_USE );
		break;
	case GUILD_DOJO_ACCOUNT:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_DOJO_ACCOUNT );
		break;
	case GUILD_DOGI:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
		wstrText = GetDisplayStringManager()->GetString( DST_DOGI_SETUP );
		break;
	case HOIPOIMIX_SKILL_SET_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfHoipoiMixJobSet" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_COMMAND );
		break;
	case HOIPOIMIX_SKILL_RESET_COMMAND:
		surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfHoipoiMixJobReset" );
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_RESET_COMMAND );
		break;
	default:
		return;
	}

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, nID, surface, wstrText, CCommandNode::MULTIDIALOG_NODE ) );
}

VOID CCommandList::RegistQuestCommand( RwUInt32 nTextID, RwUInt32 nTCID )
{
	gui::CSurface	surface;

	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfQuestIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, nTCID, surface, nTextID ) );
}

VOID CCommandList::RegistServerSelectCommand( RwInt32 nID, WCHAR* pText, RwUInt16 wCurrentUserCount )
{
	m_pRootNode->AddChildNode( NTL_NEW CServerSelectNode( this, nID, pText, wCurrentUserCount ) );
}

VOID CCommandList::RegistExitCommand( RwInt32 eNodeType )
{
	gui::CSurface surface = surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT ), (CCommandNode::NODE_TYPE)eNodeType ) );
}

VOID CCommandList::SetID( RwUInt32 uiId )
{
	m_uiId = uiId;
}

VOID CCommandList::SetInputType( RwUInt8 byInputType )
{
	m_byInputType = byInputType;
}

VOID CCommandList::SetTSKey( sTS_KEY& TSKey )
{
	m_TSKey = TSKey;
}

VOID CCommandList::SetTCUnit( CNtlTCUnit* pTCUnit )
{
	m_pTCUnit = pTCUnit;
}

RwUInt32 CCommandList::GetID(VOID)
{
	return m_uiId;
}

RwUInt8 CCommandList::GetInputType(VOID)
{
	return m_byInputType;
}

sTS_KEY& CCommandList::GetTSKey(VOID)
{
	return m_TSKey;
}

CNtlTCUnit* CCommandList::GetTCUnit(VOID)
{
	return m_pTCUnit;
}

VOID CCommandList::SelfClearNodes(VOID)
{
	ClearProc = &CCommandList::ClearState_Just;
}

VOID CCommandList::SendQuest(VOID)
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeQuest;
}

VOID CCommandList::SendGuild(VOID)
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeGuildMenu;
}

VOID CCommandList::SendGuildPoint(VOID)
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeGuildPointMenu;
}

VOID CCommandList::SendGuildContribution(VOID)
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeGuildContributionMenu;
}

VOID CCommandList::SendBuyBankMenu(VOID)
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeBuyBankMenu;
}

VOID CCommandList::SendHoipoiMixJobSetMenu( VOID )
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeHoipoiMixJobSetMenu;
}

VOID CCommandList::SendHoipoiMixJobResetMenu( VOID )
{
	ClearProc = &CCommandList::ClearState_ClearAndMakeHoipoiMixJobResetMenu;
}

VOID CCommandList::SendUserSelect( RwInt32 nSelectID, bool bResult )
{
	SNtlEventQuestUserSelectDialog_Res stResult;
	stResult.bResult	= bResult;
	stResult.sTSKey		= GetTSKey();
	stResult.tcSelID	= (NTL_TS_TC_ID)nSelectID;

	SNtlEventQuestDirect_Echo stEcho;
	stEcho.sUserSelect	= stResult;
	stEcho.eTDType		= ETD_QuestUserSelect;
	stEcho.pTCUnit		= GetTCUnit();

	if( stEcho.pTCUnit )
		CNtlSLEventGenerator::QuestTriggerDirectEcho( &stEcho );

	SetTCUnit( NULL );
}

VOID CCommandList::ClearState_No(VOID)
{

}

VOID CCommandList::ClearState_Just(VOID)
{
	CGuiLineTree::ClearNodes();

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeQuest(VOID)
{
	CGuiLineTree::ClearNodes();
	m_pOwnerGui->SetDialogType( CMultiDialogGui::TYPE_QUESTCAT );

	if ( NULL == GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency() )
		return;

	SGET_QUEST_INFO* pGetQuestList = GetNtlSLGlobal()->GetSobAvatar()->GetQuestAgency()->GetQuestInfoList( (eEVENT_GEN_TYPE)m_byInputType, m_uiId );
	vecdef_QUEST_INFO_LIST* vQuestList = &pGetQuestList->QuestInfoList;
	vecdef_QUEST_INFO_LIST::iterator it;

	for( it = vQuestList->begin() ; it != vQuestList->end() ; ++it )
	{
		sQUEST_INFO sQuestInfo = (*it);
		gui::CSurface surface;

		switch( sQuestInfo.eProgType )
		{
		case eQUEST_PROGRESS_TYPE_NEW: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfNewQuest" ); break;
		case eQUEST_PROGRESS_TYPE_PROGRESS: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfProgressQuest" ); break;
		case eQUEST_PROGRESS_TYPE_REWARD: surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfRewardQuest" ); break;
		}

		m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, sQuestInfo.sKey.tID, surface, sQuestInfo ) );		
	}

	gui::CSurface	surface;

	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT ), CCommandNode::QUESTCATALOG_NODE ) );	

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeGuildMenu(VOID)
{
	CGuiLineTree::ClearNodes();

	gui::CSurface	surface;
	std::wstring	wstrText;

	CNtlGuild* pGuild = GetNtlSLGlobal()->GetSobAvatar()->GetGuild();

	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGuildIcon" );
	wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_MAKE );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_MAKE, surface, wstrText, CCommandNode::GUILD_MODE ) );

	if( pGuild->IsBeingDisband() )
	{
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CANCEL_DISSOLVE );
		m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CANCEL_DISSOLVE, surface, wstrText, CCommandNode::GUILD_MODE ) );
	}
	else
	{
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_DISSOLVE );
		m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_DISSOLVE, surface, wstrText, CCommandNode::GUILD_MODE ) );
	}

	if( pGuild->IsHaveGroup() )
	{
		if( Logic_I_am_GuildLeader() )
		{			
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_POINT_USE );
		m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_POINTUSE, surface, wstrText, CCommandNode::GUILD_MODE ) );

		if( pGuild->IsExistFunction(DBO_GUILD_FUNCTION_CAN_CHANGE_NAME) )
		{
		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDFUNCTION_CHANGE_NAME );
		m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CHANGE_NAME, surface, wstrText, CCommandNode::GUILD_MODE ) );
		}

		}

		wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CONTIBUTION );
		m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CONTRIBUTION_ZENNY, surface, wstrText, CCommandNode::GUILD_MODE ) );

		if( pGuild->IsExistFunction(DBO_GUILD_FUNCTION_CAN_MAKE_DOGI) )
		{
			surface		= GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGambleIcon" );
			wstrText	= GetDisplayStringManager()->GetString( DST_DOGI_SETUP );

			m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_DOGI, surface, wstrText, CCommandNode::GUILD_MODE ) );
		}
	}

	wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT );
	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, wstrText, CCommandNode::GUILD_MODE ) );

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeGuildPointMenu(VOID)
{
	CGuiLineTree::ClearNodes();

	std::wstring	wstrText;
	gui::CSurface	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGuildIcon" );
	CNtlGuild* pGuild = GetNtlSLGlobal()->GetSobAvatar()->GetGuild();
	SERIAL_HANDLE hTarget = GetDboGlobal()->GetTargetSerial();
	CNtlSobNpc* pSobNPC = reinterpret_cast<CNtlSobNpc*>( GetNtlSobManager()->GetSobObject(hTarget) );
	if( NULL == pSobNPC )
	{
		DBO_ASSERT(false, "CCommandList::ClearState_ClearAndMakeGuildPointMenu, Not exist sob npc of handle : " << hTarget);
		return;
	}
	CNtlSobNpcAttr* pSobNPCAttr = reinterpret_cast<CNtlSobNpcAttr*>( pSobNPC->GetSobAttr() );
	sNPC_TBLDAT* pNPC_TBLDAT = pSobNPCAttr->GetNpcTbl();

	if( pNPC_TBLDAT->byJob == NPC_JOB_GUILD_MANAGER )
	{
		for(RwUInt8 i = DBO_GUILD_FUNCTION_MAX_MEMBER_20 ; i < DBO_GUILD_FUNCTION_COUNT ; ++i)
		{
			if( pGuild->EnableUIGuildFunction((eDBO_GUILD_FUNCTION)i) )
			{
				wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_20 + i );
				m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILDFUNCTION_MAX_MEMBER_20 + i, surface, wstrText, CCommandNode::GUILDPOINT_MODE ) );
			}
		}
	}
	else if( pNPC_TBLDAT->byJob == NPC_JOB_DOJO_MANAGER )
	{
		for(RwUInt8 i = DBO_GUILD_FUNCTION_MAX_MEMBER_20 ; i < DBO_GUILD_FUNCTION_COUNT ; ++i)
		{
			if( pGuild->EnableUIDojoFunction((eDBO_GUILD_FUNCTION)i) )
			{
				wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_20 + i );
				m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILDFUNCTION_MAX_MEMBER_20 + i, surface, wstrText, CCommandNode::GUILDPOINT_MODE ) );
			}
		}
	}	

	wstrText = GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT );
	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, wstrText, CCommandNode::GUILDPOINT_MODE ) );

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeGuildContributionMenu(VOID)
{
	CGuiLineTree::ClearNodes();

	std::wstring	wstrText;
	gui::CSurface	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfGuildIcon" );	
	WCHAR awcResult[128] = L"";

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CONTIBUTION_TITLE ), dGUILD_CONTRIBUTION_ZENNY_1000);
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CONTRIBUTION_CONTRIBUTION_1000 , surface, awcResult, CCommandNode::GUILDCONTRIBUTION_MODE ) );

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CONTIBUTION_TITLE ), dGUILD_CONTRIBUTION_ZENNY_5000);
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CONTRIBUTION_CONTRIBUTION_5000 , surface, awcResult, CCommandNode::GUILDCONTRIBUTION_MODE ) );

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CONTIBUTION_TITLE ), dGUILD_CONTRIBUTION_ZENNY_10000);
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CONTRIBUTION_CONTRIBUTION_10000 , surface, awcResult, CCommandNode::GUILDCONTRIBUTION_MODE ) );

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CONTIBUTION_TITLE ), dGUILD_CONTRIBUTION_ZENNY_50000);
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CONTRIBUTION_CONTRIBUTION_50000 , surface, awcResult, CCommandNode::GUILDCONTRIBUTION_MODE ) );

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_GUILDMENU_CONTIBUTION_TITLE ), dGUILD_CONTRIBUTION_ZENNY_100000);
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, GUILD_CONTRIBUTION_CONTRIBUTION_100000 , surface, awcResult, CCommandNode::GUILDCONTRIBUTION_MODE ) );

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT ));
	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, awcResult, CCommandNode::GUILDCONTRIBUTION_MODE ) );

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeBuyBankMenu(VOID)
{
	CGuiLineTree::ClearNodes();

	WCHAR wbuf[256] = { 0, };

	gui::CSurface	surface;
	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfWareHouseIcon" );

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();

	// ���ӿ� ó�� ���� â��NPC�� Ŭ���ϸ� �����κ��� â�� �����͸� �޴´�.
	// �� �����͸� ���� �ޱ� ���� �� �ڵ�� ���´ٸ� ����Ȯ�� ������ �����ڵ带 �������� �ʵ��� ����
	if( pWarehouse->IsRecieveData_from_Server() == FALSE )
	{
		GetAlarmManager()->AlarmMessage(DST_PLEASE_RETRY);
		GetDialogManager()->CloseDialog(DIALOG_MULTIDIALOG);
		CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
		GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
		return;
	}

	// avooo's command : ��ȹ�� �ǵ��� ���� â�� �ϳ��� �⺻������ ������ �ִ�.
	//					 ����, ������ �� �ִ� â���� �ε����� 1���� �����Ѵ�
	for( RwUInt8 i = 1 ; i < NTL_MAX_BANKSLOT_COUNT ; ++i )
	{
		SERIAL_HANDLE hWarehouseSlotHandle = pWarehouse->GetSlotSerailID( i );

		if( hWarehouseSlotHandle == INVALID_SERIAL_ID )
		{
			sNPC_TBLDAT* pNPC_TBLDAT = Logic_GetNPCDataFromSob( m_pOwnerGui->GetTargetSerial() );

			sMERCHANT_TBLDAT* pMERCHANT_TBLDAT = Logic_GetMerchantDataFromTable( pNPC_TBLDAT->amerchant_Tblidx[0] );
			DBO_ASSERT( pNPC_TBLDAT->amerchant_Tblidx[0] != INVALID_SERIAL_ID, "Not exist merchant index in NPC table");

			sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable( pMERCHANT_TBLDAT->aitem_Tblidx[i] );
			DBO_ASSERT( pMERCHANT_TBLDAT->aitem_Tblidx[i] != INVALID_SERIAL_ID, "Not exist item index in Merchant table");

			if( i < NTL_MAX_BANKSLOT_COUNT - 1 )
			{
				swprintf_s( wbuf, 256, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_BUYBANKMENU_BUYBANK ), i + 1, pITEM_TBLDAT->dwCost );	
				m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, i, surface, wbuf, CCommandNode::BUYBANK_MODE ) );
			}
			else
			{
				// ���� â��� ����ȭ�ϱ�� �Ͽ���. ����ȭ �۾������� ���Ƶ���
				//swprintf_s( wbuf, 256, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_BUYBANKMENU_BUYPUBLIC_BANK ), pITEM_TBLDAT->dwCost );
				//m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, BUY_PUBLIC_BAG, surface, wbuf, CCommandNode::BUYBANK_MODE ) );
			}			
		}
	}

	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT ), CCommandNode::BUYBANK_MODE ) );

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeHoipoiMixJobSetMenu( VOID )
{
	CGuiLineTree::ClearNodes();

	std::wstring	wstrText;
	gui::CSurface	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfHoipoiMixJobSet" );	
	WCHAR awcResult[128] = L"";

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_SET_FOOD_DRINK, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_FOOD_DRINK ),
		CCommandNode::HOIPOIMIX_SET_MODE ) );

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_SET_MAIN_WEAPON, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_MAIN_WEAPON ),
		CCommandNode::HOIPOIMIX_SET_MODE ) );

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_SET_ARMOR, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_ARMOR ),
		CCommandNode::HOIPOIMIX_SET_MODE ) );

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_SET_ACCESSORY, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_ACCESSORY ),
		CCommandNode::HOIPOIMIX_SET_MODE ) );

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_SET_SCOUTER, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_SCOUTER ),
		CCommandNode::HOIPOIMIX_SET_MODE ) );

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_SET_SUB_WEAPON, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_SET_SUB_WEAPON ),
		CCommandNode::HOIPOIMIX_SET_MODE ) );
	
	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT ));
	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, awcResult, CCommandNode::HOIPOIMIX_SET_MODE ) );

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::ClearState_ClearAndMakeHoipoiMixJobResetMenu( VOID )
{
	CGuiLineTree::ClearNodes();

	std::wstring	wstrText;
	gui::CSurface	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfHoipoiMixJobReset" );	
	WCHAR awcResult[128] = L"";

	/*m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_RESET_NORAML, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_RESET_NORMAL ),
		CCommandNode::HOIPOIMIX_RESET_MODE ) );*/

	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, HOIPOIMIX_SKILL_RESET_SPECIAL, 
		surface, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_HOIPOIMIX_RESET_SPECIAL ),
		CCommandNode::HOIPOIMIX_RESET_MODE ) );

	swprintf_s(awcResult, 128, GetDisplayStringManager()->GetString( DST_MULTIDIALOG_MENU_EXIT ));
	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfExitIcon" );
	m_pRootNode->AddChildNode( NTL_NEW CCommandNode( this, EXIT_COMMAND, surface, awcResult, CCommandNode::HOIPOIMIX_RESET_MODE ) );

	ClearProc = &CCommandList::ClearState_No;
}

VOID CCommandList::OnClear(VOID)
{
	(this->*ClearProc)();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCommandNode

CCommandNode::CCommandNode( CGuiLineTree* pTree, RwInt32 nID, gui::CSurface surface, std::string strText, NODE_TYPE eType )
: CGuiLineTreeNode( pTree, nID ), m_pbtnCommand( NULL ), m_ppnlIcon( NULL ), m_eNodeType( eType )
{
	// gui component���� �� surface ����.
	CRectangle rect;
	rect.SetRectWH( COMMANDNODE_X ,COMMANDNODE_Y, COMMANDNODE_WIDTH, COMMANDNODE_HEIGHT );
	m_pbtnCommand = NTL_NEW gui::CButton( rect, strText, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_pbtnCommand->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnDown" ) );
	m_pbtnCommand->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnFoc" ) );
	m_pbtnCommand->SetTextDownColor( RGB( 113, 113, 113 ) );
	m_pbtnCommand->SetTextFocusColor( RGB( 255, 255, 255 ) );
	m_pbtnCommand->SetTextUpColor( RGB( 220, 220, 220 ) );
	m_pbtnCommand->SetTextDownCoordDiff( COMMANDNODE_DOWNCOORD_DIFFX, COMMANDNODE_DOWNCOORD_DIFFY );
	m_pbtnCommand->SetTextCoord( COMMANDTEXT_X, 0 );
	m_pbtnCommand->SetTextStyle( COMP_TEXT_LEFT );
	m_pbtnCommand->ApplyText();

	rect.SetCenterRect( COMMANDNODEICON_X, COMMANDNODEICON_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_posIcon.SetPos( rect.left, rect.top );
	m_ppnlIcon = NTL_NEW gui::CPanel( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager(), surface );
	m_ppnlIcon->Enable( false );

	m_slotClickCommand = m_pbtnCommand->SigClicked().Connect( this, &CCommandNode::OnClickCommand );
	m_slotPressedCommand = m_pbtnCommand->SigPressed().Connect( this, &CCommandNode::OnPressedCommand );
	m_slotReleasedCommand = m_pbtnCommand->SigReleased().Connect( this, &CCommandNode::OnReleasedCommand );
}

CCommandNode::CCommandNode( CGuiLineTree* pTree, RwInt32 nID, gui::CSurface surface, std::wstring wstrText, NODE_TYPE eType )
: CGuiLineTreeNode( pTree, nID ), m_pbtnCommand( NULL ), m_ppnlIcon( NULL ), m_eNodeType( eType )
{
	// gui component���� �� surface ����.
	CRectangle rect;
	rect.SetRectWH( COMMANDNODE_X ,COMMANDNODE_Y, COMMANDNODE_WIDTH, COMMANDNODE_HEIGHT );
	m_pbtnCommand = NTL_NEW gui::CButton( rect, wstrText, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_pbtnCommand->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnDown" ) );
	m_pbtnCommand->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnFoc" ) );
	m_pbtnCommand->SetTextDownColor( RGB( 113, 113, 113 ) );
	m_pbtnCommand->SetTextFocusColor( RGB( 255, 255, 255 ) );
	m_pbtnCommand->SetTextUpColor( RGB( 220, 220, 220 ) );
	m_pbtnCommand->SetTextDownCoordDiff( COMMANDNODE_DOWNCOORD_DIFFX, COMMANDNODE_DOWNCOORD_DIFFY );
	m_pbtnCommand->SetTextCoord( COMMANDTEXT_X, 0 );
	m_pbtnCommand->SetTextStyle( COMP_TEXT_LEFT );
	m_pbtnCommand->ApplyText();

	rect.SetCenterRect( COMMANDNODEICON_X, COMMANDNODEICON_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_posIcon.SetPos( rect.left, rect.top );
	m_ppnlIcon = NTL_NEW gui::CPanel( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager(), surface );
	m_ppnlIcon->Enable( false );

	m_slotClickCommand = m_pbtnCommand->SigClicked().Connect( this, &CCommandNode::OnClickCommand );
	m_slotPressedCommand = m_pbtnCommand->SigPressed().Connect( this, &CCommandNode::OnPressedCommand );
	m_slotReleasedCommand = m_pbtnCommand->SigReleased().Connect( this, &CCommandNode::OnReleasedCommand );
}

CCommandNode::CCommandNode( CGuiLineTree* pTree, RwInt32 nID, gui::CSurface surface, RwInt32 nTextID )
: CGuiLineTreeNode( pTree, nID ), m_pbtnCommand( NULL ), m_ppnlIcon( NULL )
{
	// gui component���� �� surface ����.
	CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable();
	sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( nTextID ) );
	std::wstring wstrText;

	if( pQuestText )
		wstrText = gui::GetHtmlFromMemoryString( pQuestText->wstrText.c_str(), pQuestText->wstrText.size() );
	else
	{
		WCHAR buf[64];
		swprintf_s( buf, 64, L"QuestTextTable %d is not present!", nTextID );
		wstrText = buf;
	}

	CRectangle rect;
	rect.SetRectWH( COMMANDNODE_X ,COMMANDNODE_Y, COMMANDNODE_WIDTH, COMMANDNODE_HEIGHT );
	m_pbtnCommand = NTL_NEW gui::CButton( rect, wstrText, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_pbtnCommand->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnDown" ) );
	m_pbtnCommand->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnFoc" ) );
	m_pbtnCommand->SetTextDownColor( RGB( 113, 113, 113 ) );
	m_pbtnCommand->SetTextFocusColor( RGB( 255, 255, 255 ) );
	m_pbtnCommand->SetTextUpColor( RGB( 220, 220, 220 ) );
	m_pbtnCommand->SetTextDownCoordDiff( COMMANDNODE_DOWNCOORD_DIFFX, COMMANDNODE_DOWNCOORD_DIFFY );
	m_pbtnCommand->SetTextCoord( COMMANDTEXT_X, 0 );
	m_pbtnCommand->SetTextStyle( COMP_TEXT_LEFT );
	m_pbtnCommand->ApplyText();
	rect.SetRectWH( BRANCHCOMMANDNODEHTML_X ,BRANCHCOMMANDNODEHTML_Y, BRANCHCOMMANDNODEHTML_WIDTH, BRANCHCOMMANDNODEHTML_HEIGHT );

	rect.SetCenterRect( COMMANDNODEICON_X, COMMANDNODEICON_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_posIcon.SetPos( rect.left, rect.top );
	m_ppnlIcon = NTL_NEW gui::CPanel( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager(), surface );
	m_ppnlIcon->Enable( false );

	m_slotClickCommand = m_pbtnCommand->SigClicked().Connect( this, &CCommandNode::OnClickCommand );
	m_slotPressedCommand = m_pbtnCommand->SigPressed().Connect( this, &CCommandNode::OnPressedCommand );
	m_slotReleasedCommand = m_pbtnCommand->SigReleased().Connect( this, &CCommandNode::OnReleasedCommand );

	// Type����.
	m_eNodeType = BRANCHDIALOG_NODE;
}

CCommandNode::CCommandNode( CGuiLineTree* pTree, RwInt32 nID, gui::CSurface surface, sQUEST_INFO sData )
: CGuiLineTreeNode( pTree, nID ), m_pbtnCommand( NULL ), m_ppnlIcon( NULL )
{
	// gui component���� �� surface ����.
	CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable();
	sQUEST_TEXT_DATA_TBLDAT* pQuestText = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( sData.dwQuestTitle ) );
	std::wstring wstrText;

	if( pQuestText )
		wstrText = gui::GetHtmlFromMemoryString( pQuestText->wstrText.c_str(), pQuestText->wstrText.size() );
	else
	{
		WCHAR buf[64];
		swprintf_s( buf, 64, L"QuestTextTable %u is not present", sData.dwQuestTitle );
		wstrText = buf;
	}

	CRectangle rect;
	rect.SetRectWH( COMMANDNODE_X ,COMMANDNODE_Y, COMMANDNODE_WIDTH, COMMANDNODE_HEIGHT );
	m_pbtnCommand = NTL_NEW gui::CButton( rect, wstrText, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_pbtnCommand->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnDown" ) );
	m_pbtnCommand->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnFoc" ) );
	m_pbtnCommand->SetTextDownColor( RGB( 113, 113, 113 ) );
	m_pbtnCommand->SetTextFocusColor( RGB( 255, 255, 255 ) );
	m_pbtnCommand->SetTextUpColor( RGB( 220, 220, 220 ) );
	m_pbtnCommand->SetTextDownCoordDiff( COMMANDNODE_DOWNCOORD_DIFFX, COMMANDNODE_DOWNCOORD_DIFFY );
	m_pbtnCommand->SetTextCoord( COMMANDTEXT_X, 0 );
	m_pbtnCommand->SetTextStyle( COMP_TEXT_LEFT );
	m_pbtnCommand->ApplyText();
	rect.SetRectWH( BRANCHCOMMANDNODEHTML_X ,BRANCHCOMMANDNODEHTML_Y, BRANCHCOMMANDNODEHTML_WIDTH, BRANCHCOMMANDNODEHTML_HEIGHT );

	rect.SetCenterRect( COMMANDNODEICON_X, COMMANDNODEICON_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_posIcon.SetPos( rect.left, rect.top );
	m_ppnlIcon = NTL_NEW gui::CPanel( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager(), surface );
	m_ppnlIcon->Enable( false );

	m_slotClickCommand = m_pbtnCommand->SigClicked().Connect( this, &CCommandNode::OnClickCommand );
	m_slotPressedCommand = m_pbtnCommand->SigPressed().Connect( this, &CCommandNode::OnPressedCommand );
	m_slotReleasedCommand = m_pbtnCommand->SigReleased().Connect( this, &CCommandNode::OnReleasedCommand );

	// Type����.
	m_eNodeType = QUESTCATALOG_NODE;
	m_sData		= sData;
}


CCommandNode::~CCommandNode(VOID)
{
	NTL_DELETE( m_pbtnCommand );
	NTL_DELETE( m_ppnlIcon );
}

VOID CCommandNode::ShowProc(VOID)
{
	CGuiLineTreeNode::ShowProc();

	m_pbtnCommand->Show( true );
	m_pbtnCommand->SetPosition( m_nPosX + COMMANDNODE_X, m_nPosY + COMMANDNODE_Y );

	if( m_ppnlIcon )
	{
		m_ppnlIcon->Show( true );
		m_ppnlIcon->SetPosition( m_nPosX + m_posIcon.x, m_nPosY + m_posIcon.y );
	}	
}

VOID CCommandNode::HideProc(VOID)
{
	CGuiLineTreeNode::HideProc();

	m_pbtnCommand->Show( false );

	if( m_ppnlIcon )
		m_ppnlIcon->Show( false );
}

VOID CCommandNode::OnClickCommand( gui::CComponent* pComponent )
{	
	CCommandList* pNodeMgr = reinterpret_cast<CCommandList*>( m_pMgr );

	if( m_eNodeType == MULTIDIALOG_NODE )
	{
		if( m_nID == CCommandList::QUEST_COMMAND )
		{
			pNodeMgr->SendQuest();
		}
		else if( m_nID == CCommandList::GUILD_COMMAND )
		{
			pNodeMgr->SendGuild();
		}
		else if( m_nID == CCommandList::BUY_BANK_COMMAND )
		{
			pNodeMgr->SendBuyBankMenu();
		}
		else
		{
			SERIAL_HANDLE hSerialID = pNodeMgr->GetOwnerGui()->GetTargetSerial();			
			DBO_ASSERT(hSerialID != INVALID_SERIAL_ID, "CCommandNode::OnClickCommand, Invalid NPC serial ID");

			switch( m_nID )
			{
			case CCommandList::MERCHANT_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_NPCSHOP );
					break;
				}
			case CCommandList::BUDOHSI_MERCHANT_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_NPCSHOP );
					break;
				}
			case CCommandList::SKILLTRAINER_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_SKILL_TRAINER );
					break;
				}				
			case CCommandList::BANKER_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_WAREHOUSEBAR );
					break;
				}
			case CCommandList::GUILD_BANK_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseStart_Req(hSerialID);
					break;
				}
			case CCommandList::UPGRADE_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_ITEMUPGRADE );
					break;
				}		
			case CCommandList::TMQ_COMMAND:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_TMQBOARD );
					break;
				}
			case CCommandList::PORTAL_COMMAND:
				{
					GetDialogManager()->CloseDialog(DIALOG_MULTIDIALOG, FALSE);
					CDboEventGenerator::NPCDialogOpen(hSerialID, DIALOG_PORTAL);
					break;
				}
			case CCommandList::GAMBLE_BUY_COMMNAD:
				{
					if( !Logic_FindEmptyItemSlot() )
					{
						GetAlarmManager()->AlarmMessage( DST_ITEM_BAG_FULL );
						return;
					}

					CNtlSobNpc* pNPC = reinterpret_cast<CNtlSobNpc*>( GetNtlSobManager()->GetSobObject( pNodeMgr->GetOwnerGui()->GetTargetSerial() ) );
					DBO_ASSERT( pNPC, "CMultiDialogGui::OnClickCommand : Invalid NPC SerialID" );

					CNtlSobNpcAttr* pNPCAttr = reinterpret_cast<CNtlSobNpcAttr*>( pNPC->GetSobAttr() );
					sNPC_TBLDAT* pTableData = pNPCAttr->GetNpcTbl();

					// Merchant Table�� ���� ù��° Index�� �����Ѵ�.
					if( pTableData->amerchant_Tblidx[0] == INVALID_TBLIDX )
					{
						DBO_FAIL( "[GAMBLE] NPC Table havn't merchant table index." << pTableData->tblidx );
						return;
					}

					sMERCHANT_TBLDAT* pMerchantTblDat = (sMERCHANT_TBLDAT*)API_GetTableContainer()->GetMerchantTable()->FindData( pTableData->amerchant_Tblidx[0] );
					if( !pMerchantTblDat )
					{
						DBO_FAIL( "[GAMBLE] Merchant table index is invalid." << pTableData->amerchant_Tblidx[0] );
						return;
					}

					// ������ ����Ʈ�� ���ڶ�� ���ڶ��ٰ� �Ѵ�.
					if( Logic_GetMudosaPoint() < pMerchantTblDat->dwNeedMileage )
					{
						GetAlarmManager()->AlarmMessage( DST_GAMBLE_NOT_ENOUGH_MUDOSA_POINT );
						return;
					}

					CNtlSLEventGenerator::GambleAniStart( pNodeMgr->GetOwnerGui()->GetTargetSerial() );
					GetDialogManager()->CloseDialog(DIALOG_MULTIDIALOG, FALSE );


					break;
				}
			case CCommandList::HOIPOIMIX_CREATE_COMMAND:
				{
					GetDialogManager()->CloseDialog(DIALOG_MULTIDIALOG, FALSE);
					CDboEventGenerator::NPCDialogOpen(hSerialID, DIALOG_HOIPOIMIX_CAPSULE);
				}
				break;
			case CCommandList::HOIPOIMIX_DESTROY_MACHINE_COMMAND:
				{
					CNtlSob* pSob = GetNtlSobManager()->GetSobObject( hSerialID );
					if( pSob->GetOwnerID() != GetNtlSLGlobal()->GetSobAvatar()->GetSerialID() )
					{
						DBO_FAIL("CCommandNode::OnClickCommand - Invalid owner ID" );
						break;
					}

					GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixItemMachineDelReq( hSerialID );

					CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
					GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );

					/*CNtlSLEventGenerator::HoipoiMixItemMachineDel();					*/
					break;
				}
				break;
			case CCommandList::GUILD_DOJO_ESTABLISHMENT:
				{
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );				

					GetAlarmManager()->FormattedAlarmMessage(DST_DOJO_ASK_ESTABLISHMENT, FALSE, NULL, g_aGuildFunctionInfo[DBO_GUILD_FUNCTION_CAN_HAVE_DOJO].dwRequiredZenny );
					break;
				}
			case CCommandList::GUILD_DOJO_INFO:
				{
					CDboEventGenerator::DialogEvent(DIALOGEVENT_CREATE_DOJO_GUI);

					CDojoInfoGui* pDojoInfoGui = reinterpret_cast<CDojoInfoGui*>( GetDialogManager()->GetDialog( DIALOG_DOJO_INFO ) );
					DBO_ASSERT(pDojoInfoGui, "CCommandNode::OnClickCommand, Not exist CDojoInfoGui instance");
					pDojoInfoGui->SetPageType( CDojoInfoGui::TAB_PAGE_INFO );

					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_DOJO_INFO );
					break;
				}
			case CCommandList::GUILD_DOJO_POINTUSE:
				{					
					pNodeMgr->SendGuildPoint();	
					break;
				}
			case CCommandList::GUILD_DOJO_ACCOUNT:
				{
					CDboEventGenerator::DialogEvent(DIALOGEVENT_CREATE_DOJO_GUI);

					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_DOJO_ACCOUNT );
					break;
				}
			case CCommandList::GUILD_DOGI:
				{
					CDboEventGenerator::DialogEvent(DIALOGEVENT_CREATE_DOJO_GUI);

					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
					CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_DOGI );
					break;
				}
			case CCommandList::EXIT_COMMAND:
				{
					CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
					GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
					GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );					
					break;
				}
			case CCommandList::HOIPOIMIX_SKILL_SET_COMMAND:
				{
					pNodeMgr->SendHoipoiMixJobSetMenu();
					break;
				}
			case CCommandList::HOIPOIMIX_SKILL_RESET_COMMAND:
				{
					pNodeMgr->SendHoipoiMixJobResetMenu();
					break;
				}
			default:
				{
					DBO_FAIL("Wrong command Type : " << m_eNodeType << "ID : " << m_nID);
					break;
				}
			}	
		}
	}
	else if( m_eNodeType == QUESTCATALOG_NODE )
	{	
		if( m_nID == CCommandList::EXIT_COMMAND )
		{
			CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
			GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
			GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
		}
		else
		{
			if( m_sData.bVisitOP )
			{
				// visit quest event
				CDboEventGenerator::QuestMessage( &m_sData, (eEVENT_GEN_TYPE)pNodeMgr->GetInputType(), pNodeMgr->GetID() );
			}
			else
			{
				// normal quest event
				CNtlSLEventGenerator::DoQuest( m_sData, (eEVENT_GEN_TYPE)pNodeMgr->GetInputType(), pNodeMgr->GetID(), TRUE );
			}

			GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
		}		
	}
	else if( m_eNodeType == QUESTDIALOG_NODE )
	{
		if( m_nID == CCommandList::EXIT_COMMAND )
		{
			GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
		}
	}
	else if( m_eNodeType == BRANCHDIALOG_NODE )
	{
		if( m_nID == CCommandList::EXIT_COMMAND )
		{
			pNodeMgr->SendUserSelect( NTL_TS_TC_ID_INVALID, false );			
		}
		else
		{
			pNodeMgr->SendUserSelect( m_nID, true );			
		}		

		GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
	}
	else if( m_eNodeType == GUILD_MODE )
	{
		SERIAL_HANDLE hSerialID = pNodeMgr->GetOwnerGui()->GetTargetSerial();			

		switch( m_nID )
		{
		case CCommandList::GUILD_MAKE:
			{
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
				GetAlarmManager()->AlarmMessage( DST_GUILD_DO_MAKE );				
				break;
			}				
		case CCommandList::GUILD_DISSOLVE:
			{
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
				GetAlarmManager()->AlarmMessage( DST_GUILD_DO_DISSOLVE );				
				break;
			}		
		case CCommandList::GUILD_CANCEL_DISSOLVE:
			{
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
				GetAlarmManager()->AlarmMessage( DST_GUILD_CANCEL_DISSOLVE );
				break;
			}
		case CCommandList::GUILD_POINTUSE:
			{
				pNodeMgr->SendGuildPoint();		
				break;
			}
		case CCommandList::GUILD_CHANGE_NAME:
			{
				sMsgBoxData msgExData;
				msgExData.hHandle = hSerialID;

				GetAlarmManager()->AlarmMessage( DST_GUILD_CHANGE_GUILD_NAME, FALSE, &msgExData );
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );				
				break;
			}
		case CCommandList::GUILD_CONTRIBUTION_ZENNY:
			{
				pNodeMgr->SendGuildContribution();	
				break;
			}
		case CCommandList::GUILD_DOGI:
			{
				CDboEventGenerator::DialogEvent(DIALOGEVENT_CREATE_DOJO_GUI);
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG, FALSE );
				CDboEventGenerator::NPCDialogOpen( hSerialID, DIALOG_DOGI );
				break;
			}
		case CCommandList::EXIT_COMMAND:
			{
				CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
				GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
				break;
			}				
		}		
	}
	else if( m_eNodeType == GUILDPOINT_MODE )
	{
		switch( m_nID )
		{
		case CCommandList::EXIT_COMMAND:
			{
				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
				CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
				GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
				break;
			}		
		default:
			{				
			 	SERIAL_HANDLE hNPC = GetDboGlobal()->GetTargetSerial();
				sNPC_TBLDAT* pNPC_TBLDAT = Logic_GetNPCDataFromSob(hNPC);

				if( pNPC_TBLDAT )
				{
					sMsgBoxData msgExData;
					msgExData.byIndex = (RwUInt8)(m_nID - CCommandList::GUILDFUNCTION_START);

					if( pNPC_TBLDAT->dwFunc_Bit_Flag & NPC_FUNC_FLAG_GUILD_MANAGER )
					{
						GetAlarmManager()->FormattedAlarmMessage( DST_GUILD_ADD_FUNCTION, FALSE, &msgExData, GetDisplayStringManager()->GetString(msgExData.byIndex + DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_20) );
					}
					else if( pNPC_TBLDAT->dwFunc_Bit_Flag & NPC_FUNC_FLAG_DOJO_MANAGER )
					{
						switch(msgExData.byIndex)
						{
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_1:
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_2:
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_3:
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_4:
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_5:
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_6:
						case DBO_GUILD_FUNCTION_DOJO_UPGRADE_7:
							{
								CDboEventGenerator::DialogEvent(DIALOGEVENT_CREATE_DOJO_GUI);
								GetDialogManager()->OpenDialog(DIALOG_DOJO_UPGRADE);
								break;
							}
						default:
							{
								GetAlarmManager()->FormattedAlarmMessage( DST_DOJO_ADD_FUNCTION, FALSE, &msgExData, GetDisplayStringManager()->GetString(msgExData.byIndex + DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_20) );
								break;
							}
						}						
					}
					else
					{
						DBO_FAIL("Invalid NPC function");
					}
				}
				else
				{
					DBO_FAIL("Not exist NPC table of handle : " << hNPC);
				}

				GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
				break;
			}
		}
	}
	else if( m_eNodeType == GUILDCONTRIBUTION_MODE )
	{
		//const WCHAR* pwcMessage = GetDisplayStringManager()->GetString(DST_GUILD_CONTRIBUTION_ZENNY);
		//WCHAR awcBuffer[256] = L"";
		sMsgBoxData msgExData;

		switch( m_nID )
		{
		case CCommandList::GUILD_CONTRIBUTION_CONTRIBUTION_1000:
			{
				msgExData.uiParam = dGUILD_CONTRIBUTION_ZENNY_1000;
				//swprintf_s(awcBuffer, 256, pwcMessage, dGUILD_CONTRIBUTION_ZENNY_1000);
				//CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_GUILD_CONTRIBUTION, MBTF_OK | MBTF_CANCEL, FALSE, 0.f, &msgExData);
				GetAlarmManager()->FormattedAlarmMessage( DST_GUILD_CONTRIBUTION_ZENNY, FALSE, &msgExData, dGUILD_CONTRIBUTION_ZENNY_1000 );
				break;
			}
		case CCommandList::GUILD_CONTRIBUTION_CONTRIBUTION_5000:
			{
				msgExData.uiParam = dGUILD_CONTRIBUTION_ZENNY_5000;
				//swprintf_s(awcBuffer, 256, pwcMessage, dGUILD_CONTRIBUTION_ZENNY_5000);
				//CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_GUILD_CONTRIBUTION, MBTF_OK | MBTF_CANCEL, FALSE, 0.f, &msgExData);
				GetAlarmManager()->FormattedAlarmMessage( DST_GUILD_CONTRIBUTION_ZENNY, FALSE, &msgExData, dGUILD_CONTRIBUTION_ZENNY_5000 );
				break;
			}
		case CCommandList::GUILD_CONTRIBUTION_CONTRIBUTION_10000:
			{
				msgExData.uiParam = dGUILD_CONTRIBUTION_ZENNY_10000;
				//swprintf_s(awcBuffer, 256, pwcMessage, dGUILD_CONTRIBUTION_ZENNY_10000);
				//CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_GUILD_CONTRIBUTION, MBTF_OK | MBTF_CANCEL, FALSE, 0.f, &msgExData);
				GetAlarmManager()->FormattedAlarmMessage( DST_GUILD_CONTRIBUTION_ZENNY, FALSE, &msgExData, dGUILD_CONTRIBUTION_ZENNY_10000 );
				break;
			}
		case CCommandList::GUILD_CONTRIBUTION_CONTRIBUTION_50000:
			{
				msgExData.uiParam = dGUILD_CONTRIBUTION_ZENNY_50000;
				//swprintf_s(awcBuffer, 256, pwcMessage, dGUILD_CONTRIBUTION_ZENNY_50000);
				//CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_GUILD_CONTRIBUTION, MBTF_OK | MBTF_CANCEL, FALSE, 0.f, &msgExData);
				GetAlarmManager()->FormattedAlarmMessage( DST_GUILD_CONTRIBUTION_ZENNY, FALSE, &msgExData, dGUILD_CONTRIBUTION_ZENNY_50000 );
				break;
			}
		case CCommandList::GUILD_CONTRIBUTION_CONTRIBUTION_100000:
			{
				msgExData.uiParam = dGUILD_CONTRIBUTION_ZENNY_100000;
				//swprintf_s(awcBuffer, 256, pwcMessage, dGUILD_CONTRIBUTION_ZENNY_100000);
				//CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_GUILD_CONTRIBUTION, MBTF_OK | MBTF_CANCEL, FALSE, 0.f, &msgExData);
				GetAlarmManager()->FormattedAlarmMessage( DST_GUILD_CONTRIBUTION_ZENNY, FALSE, &msgExData, dGUILD_CONTRIBUTION_ZENNY_100000 );
				break;
			}
		case CCommandList::EXIT_COMMAND:
			{
				CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
				GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
				break;
			}
		}

		GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
	}
	else if( m_eNodeType == BUYBANK_MODE )
	{
		switch( m_nID )
		{
		case CCommandList::EXIT_COMMAND:
			{
				CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
				GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
				break;
			}
		case CCommandList::BUY_PUBLIC_BAG:
			{
				sNPC_TBLDAT* pNPC_TBLDAT = Logic_GetNPCDataFromSob( pNodeMgr->GetOwnerGui()->GetTargetSerial() );

				sMERCHANT_TBLDAT* pMERCHANT_TBLDAT = Logic_GetMerchantDataFromTable( pNPC_TBLDAT->amerchant_Tblidx[0] );
				DBO_ASSERT( pMERCHANT_TBLDAT, "Not exist merchant index in NPC table");

				// avooo's comment : ������ ���̺� ���� ���� â��� 3�� ����Ų��
				sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable( pMERCHANT_TBLDAT->aitem_Tblidx[3] );
				DBO_ASSERT( pITEM_TBLDAT, "Not exist item index in Merchant table");

				SERIAL_HANDLE hNPCHandle = pNodeMgr->GetOwnerGui()->GetTargetSerial();

				// ���� â��(%d ����)�� �����Ͻðڽ��ϱ�?
				sMsgBoxData data;
				data.hHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_WAREHOUSE_WANT_YOU_BUY_COMMON, FALSE, &data, pITEM_TBLDAT->dwCost );

				//wchar_t awcBuffer[256] = L"";
				//swprintf_s(awcBuffer, 256, GetDisplayStringManager()->GetString(DST_WAREHOUSE_WANT_YOU_BUY_COMMON), pITEM_TBLDAT->dwCost);

				//CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_BUY_COMMON_WAREHOUSE, MBT_OKCANCEL, FALSE, 0.f, (VOID*)&hNPCHandle);

				break;
			}
		default:
			{
				sNPC_TBLDAT* pNPC_TBLDAT = Logic_GetNPCDataFromSob( pNodeMgr->GetOwnerGui()->GetTargetSerial() );

				sMERCHANT_TBLDAT* pMERCHANT_TBLDAT = Logic_GetMerchantDataFromTable( pNPC_TBLDAT->amerchant_Tblidx[0] );
				DBO_ASSERT( pMERCHANT_TBLDAT, "Not exist merchant index in NPC table");

				RwUInt8 byIndex = (RwUInt8)GetID();
				sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable( pMERCHANT_TBLDAT->aitem_Tblidx[byIndex] );
				DBO_ASSERT( pITEM_TBLDAT, "Not exist item index in Merchant table");



				SERIAL_HANDLE hNPCHandle = pNodeMgr->GetOwnerGui()->GetTargetSerial();

				// â��(%d ����)�� �����Ͻðڽ��ϱ�?
				sMsgBoxData data;
				data.hHandle = hNPCHandle;
				data.byIndex = byIndex;
				GetAlarmManager()->FormattedAlarmMessage( DST_WAREHOUSE_WANT_YOU_BUY, FALSE, &data, pITEM_TBLDAT->dwCost );

				//wchar_t awcBuffer[256] = L"";				
				//swprintf_s(awcBuffer, 256, GetDisplayStringManager()->GetString(DST_WAREHOUSE_WANT_YOU_BUY), pITEM_TBLDAT->dwCost);

				//if( byIndex == 1)
				//	CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_BUY_WAREHOUSE_2, MBT_OKCANCEL, FALSE, 0.0f, (VOID*)&hNPCHandle);
				//else if( byIndex == 2)
				//	CDboEventGenerator::MsgBoxShow(awcBuffer, MBW_BUY_WAREHOUSE_3, MBT_OKCANCEL, FALSE, 0.0f, (VOID*)&hNPCHandle);

				break;
			}
		}

		GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
	}
	else if( m_eNodeType == SERVERSELECT_MODE )
	{
		// �����̵��� ServerSelectNode���� ó��.
		if( GetID() == CCommandList::EXIT_COMMAND )
		{
			CNtlSLEventGenerator::TSMudosaTeleport_Res( pNodeMgr->GetTSKey(), (RwUInt8)GetID(), TRUE );
			GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );				
		}
	}
	else if( m_eNodeType == HOIPOIMIX_SET_MODE )
	{
		SERIAL_HANDLE hNPCHandle = pNodeMgr->GetOwnerGui()->GetTargetSerial();

		switch( m_nID )
		{
		case CCommandList::HOIPOIMIX_SKILL_SET_FOOD_DRINK:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_FOOD_DRINK;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_SET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_FOOD_DRINK ),
					Dbo_GetHoipoiMixNeedLevelForJobSet( ITEM_RECIPE_TYPE_FOOD_DRINK),
					Dbo_GetHoipoiMixNeedZennyForJobSet( ITEM_RECIPE_TYPE_FOOD_DRINK ));
				/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobSetReq( hNPCHandle, ITEM_RECIPE_TYPE_FOOD_DRINK );*/
			}
			break;
		case CCommandList::HOIPOIMIX_SKILL_SET_MAIN_WEAPON:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_MAIN_WEAPON;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_SET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_MAIN_WEAPON ),
					Dbo_GetHoipoiMixNeedLevelForJobSet( ITEM_RECIPE_TYPE_MAIN_WEAPON ),
					Dbo_GetHoipoiMixNeedZennyForJobSet( ITEM_RECIPE_TYPE_MAIN_WEAPON ) );
			/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobSetReq( hNPCHandle, ITEM_RECIPE_TYPE_MAIN_WEAPON );*/
			}
			break;
		case CCommandList::HOIPOIMIX_SKILL_SET_ARMOR:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_ARMOR;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_SET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_ARMOR ),
					Dbo_GetHoipoiMixNeedLevelForJobSet( ITEM_RECIPE_TYPE_ARMOR ),
					Dbo_GetHoipoiMixNeedZennyForJobSet( ITEM_RECIPE_TYPE_ARMOR )  );
				/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobSetReq( hNPCHandle, ITEM_RECIPE_TYPE_ARMOR );*/
			}
			break;
		case CCommandList::HOIPOIMIX_SKILL_SET_ACCESSORY:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_ACCESSORY;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_SET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_ACCESSORY ),
					Dbo_GetHoipoiMixNeedLevelForJobSet( ITEM_RECIPE_TYPE_ACCESSORY ),
					Dbo_GetHoipoiMixNeedZennyForJobSet( ITEM_RECIPE_TYPE_ACCESSORY ) );
			/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobSetReq( hNPCHandle, ITEM_RECIPE_TYPE_ACCESSORY );*/
			}
			break;
		case CCommandList::HOIPOIMIX_SKILL_SET_SCOUTER:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_SCOUTER;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_SET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_SCOUTER ),
					Dbo_GetHoipoiMixNeedLevelForJobSet( ITEM_RECIPE_TYPE_SCOUTER),
					Dbo_GetHoipoiMixNeedZennyForJobSet( ITEM_RECIPE_TYPE_SCOUTER ) );
				/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobSetReq( hNPCHandle, ITEM_RECIPE_TYPE_SCOUTER );*/
			}
			break;
		case CCommandList::HOIPOIMIX_SKILL_SET_SUB_WEAPON:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_SUB_WEAPON;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_SET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_SUB_WEAPON ),
					Dbo_GetHoipoiMixNeedLevelForJobSet( ITEM_RECIPE_TYPE_SUB_WEAPON ),
					Dbo_GetHoipoiMixNeedZennyForJobSet( ITEM_RECIPE_TYPE_SUB_WEAPON ) );
			/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobSetReq( hNPCHandle, ITEM_RECIPE_TYPE_SUB_WEAPON );*/
			}
			break;
		case CCommandList::EXIT_COMMAND:
			break;
		default:
			break;
		}

		CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
		GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
		GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
	}
	else if( m_eNodeType == HOIPOIMIX_RESET_MODE )
	{
		SERIAL_HANDLE hNPCHandle = pNodeMgr->GetOwnerGui()->GetTargetSerial();

		switch( m_nID )
		{
		case CCommandList::HOIPOIMIX_SKILL_RESET_NORAML:
			{
				sMsgBoxData sData;
				sData.byIndex = ITEM_RECIPE_TYPE_FOOD_DRINK;
				sData.hExtendHandle = hNPCHandle;
				GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_RESET_MSGBOX,
					FALSE,
					&sData,
					Logic_GetHoipoiMixSkillName( ITEM_RECIPE_TYPE_FOOD_DRINK ) );
				/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobResetReq( hNPCHandle, ITEM_RECIPE_TYPE_FOOD_DRINK );*/
			}
			
			break;
		case CCommandList::HOIPOIMIX_SKILL_RESET_SPECIAL:
			{
				CNtlSobAvatar* pSobAvatar = GetNtlSLGlobal()->GetSobAvatar();
				if( !pSobAvatar )
				{
					DBO_FAIL( "Not exist avatar instance" );
					return;
				}

				CNtlSLHoipoiMix* pHoipoiMix = pSobAvatar->GetHoipoiMix();
				if( !pHoipoiMix )
				{
					DBO_FAIL( "Not exist hoipoi mix instance" );
					return;
				}

				if( !pHoipoiMix->IsSpecialStart() )
				{
					// ���� Ư�� ����� ����� �ʾҽ��ϴ�.
					GetAlarmManager()->AlarmMessage( GAME_ITEM_RECIPE_CANNOT_RESET_CAUSE_NOT_STARTED_YET, TRUE );
				}
				else
				{
					sMsgBoxData sData;
					sData.byIndex = pHoipoiMix->GetSpecialType();
					sData.hExtendHandle = hNPCHandle;
					GetAlarmManager()->FormattedAlarmMessage( DST_HOIPOIMIX_SKILL_RESET_MSGBOX,
						FALSE,
						&sData,
						Logic_GetHoipoiMixSkillName( pHoipoiMix->GetSpecialType() ) );

					/*GetDboGlobal()->GetGamePacketGenerator()->SendHoipoiMixJobResetReq( hNPCHandle, pHoipoiMix->GetSpecialType() );*/
				}
			}
			break;
		case CCommandList::EXIT_COMMAND:
			break;
		default:
			break;
		}

		CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
		GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
		GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
	}
}

VOID CCommandNode::OnPressedCommand( gui::CComponent* pComponent )
{
	CRectangle rect;

	if( m_ppnlIcon )
	{
		rect = m_ppnlIcon->GetPosition();
		m_ppnlIcon->SetPosition( rect.left + COMMANDNODE_DOWNCOORD_DIFFX, rect.top + COMMANDNODE_DOWNCOORD_DIFFY );		
	}
}

VOID CCommandNode::OnReleasedCommand( gui::CComponent* pComponent )
{
	CRectangle rect;

	if( m_ppnlIcon )
	{
		rect = m_ppnlIcon->GetPosition();
		m_ppnlIcon->SetPosition( rect.left - COMMANDNODE_DOWNCOORD_DIFFX, rect.top - COMMANDNODE_DOWNCOORD_DIFFY );				
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CServerSelectNode

CServerSelectNode::CServerSelectNode( CGuiLineTree* pTree, RwInt32 nID, WCHAR* pText, RwInt32 nCurrentUserCount )
: CGuiLineTreeNode( pTree, nID ), m_pbtnCommand( NULL ), m_ppnlIcon( NULL ), m_ppnlUserCountBack( NULL ), m_ppgbUserCount( NULL )
{
	// gui component���� �� surface ����.
	CRectangle rect;
	rect.SetRectWH( COMMANDNODE_X ,COMMANDNODE_Y, COMMANDNODE_WIDTH, COMMANDNODE_HEIGHT );
	m_pbtnCommand = NTL_NEW gui::CButton( rect, pText, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_pbtnCommand->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnDown" ) );
	m_pbtnCommand->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfBtnFoc" ) );
	m_pbtnCommand->SetTextDownColor( RGB( 113, 113, 113 ) );
	m_pbtnCommand->SetTextFocusColor( RGB( 255, 255, 255 ) );
	m_pbtnCommand->SetTextUpColor( RGB( 220, 220, 220 ) );
	m_pbtnCommand->SetTextDownCoordDiff( COMMANDNODE_DOWNCOORD_DIFFX, COMMANDNODE_DOWNCOORD_DIFFY );
	m_pbtnCommand->SetTextCoord( COMMANDTEXT_X, 0 );
	m_pbtnCommand->SetTextStyle( COMP_TEXT_LEFT );
	m_pbtnCommand->ApplyText();

	gui::CSurface surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfTimeMachineIcon" );
	rect.SetCenterRect( COMMANDNODEICON_X, COMMANDNODEICON_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_posIcon.SetPos( rect.left, rect.top );
	m_ppnlIcon = NTL_NEW gui::CPanel( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager(), surface );
	m_ppnlIcon->Enable( false );

	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfUserCountBack" );
	rect.SetRectWH( SERVERSELECTNODE_USERCOUNT_X, SERVERSELECTNODE_USERCOUNT_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_posUserCount.SetPos( rect.left, rect.top );
	m_ppnlUserCountBack = NTL_NEW gui::CPanel( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager(), surface );
	m_ppnlUserCountBack->Enable( false );

	surface = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "MultiDialog.srf", "srfUserCount" );
	rect.SetRectWH( SERVERSELECTNODE_USERCOUNT_X, SERVERSELECTNODE_USERCOUNT_Y, surface.m_SnapShot.rtRect.GetWidth(), surface.m_SnapShot.rtRect.GetHeight() );
	m_ppgbUserCount = NTL_NEW gui::CProgressBar( rect, pTree->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_ppgbUserCount->AddSurface( surface );
	m_ppgbUserCount->SetRange( 0, BUDOKAI_MAX_MUDOSA_PLAYER_COUNT );
	m_ppgbUserCount->SetPos( nCurrentUserCount );
	m_ppgbUserCount->Enable( false );

	m_slotClickCommand = m_pbtnCommand->SigClicked().Connect( this, &CServerSelectNode::OnClickCommand );
	m_slotPressedCommand = m_pbtnCommand->SigPressed().Connect( this, &CServerSelectNode::OnPressedCommand );
	m_slotReleasedCommand = m_pbtnCommand->SigReleased().Connect( this, &CServerSelectNode::OnReleasedCommand );
}

CServerSelectNode::~CServerSelectNode(VOID)
{
	NTL_DELETE( m_pbtnCommand );
	NTL_DELETE( m_ppnlIcon );
	NTL_DELETE( m_ppnlUserCountBack );
	NTL_DELETE( m_ppgbUserCount );
}

VOID CServerSelectNode::ShowProc(VOID)
{
	CGuiLineTreeNode::ShowProc();

	m_pbtnCommand->Show( true );
	m_pbtnCommand->SetPosition( m_nPosX + COMMANDNODE_X, m_nPosY + COMMANDNODE_Y );

	m_ppnlIcon->Show( true );
	m_ppnlIcon->SetPosition( m_nPosX + m_posIcon.x, m_nPosY + m_posIcon.y );

	m_ppnlUserCountBack->Show( true );
	m_ppnlUserCountBack->SetPosition( m_nPosX + m_posUserCount.x, m_nPosY + m_posUserCount.y );

	m_ppgbUserCount->Show( true );
	m_ppgbUserCount->SetPosition( m_nPosX + m_posUserCount.x, m_nPosY + m_posUserCount.y );
}

VOID CServerSelectNode::HideProc(VOID)
{
	CGuiLineTreeNode::HideProc();

	m_pbtnCommand->Show( false );

	m_ppnlIcon->Show( false );

	m_ppnlUserCountBack->Show( false );
	m_ppgbUserCount->Show( false ); 
}

VOID CServerSelectNode::OnClickCommand( gui::CComponent* pComponent )
{
	CCommandList* pNodeMgr = reinterpret_cast<CCommandList*>( m_pMgr );

	CNtlSLEventGenerator::TSMudosaTeleport_Res( pNodeMgr->GetTSKey(), (RwUInt8)GetID(), FALSE );
	GetDialogManager()->CloseDialog( DIALOG_MULTIDIALOG );
}

VOID CServerSelectNode::OnPressedCommand( gui::CComponent* pComponent )
{
	CRectangle rect;

	rect = m_ppnlIcon->GetPosition();
	m_ppnlIcon->SetPosition( rect.left + COMMANDNODE_DOWNCOORD_DIFFX, rect.top + COMMANDNODE_DOWNCOORD_DIFFY );			
	m_ppnlUserCountBack->SetPosition( rect.left + COMMANDNODE_DOWNCOORD_DIFFX, rect.top + COMMANDNODE_DOWNCOORD_DIFFY );			
	m_ppgbUserCount->SetPosition( rect.left + COMMANDNODE_DOWNCOORD_DIFFX, rect.top + COMMANDNODE_DOWNCOORD_DIFFY );			
}

VOID CServerSelectNode::OnReleasedCommand( gui::CComponent* pComponent )
{
	CRectangle rect;

	rect = m_ppnlIcon->GetPosition();
	m_ppnlIcon->SetPosition( rect.left - COMMANDNODE_DOWNCOORD_DIFFX, rect.top - COMMANDNODE_DOWNCOORD_DIFFY );					
	m_ppnlUserCountBack->SetPosition( rect.left + COMMANDNODE_DOWNCOORD_DIFFX, rect.top + COMMANDNODE_DOWNCOORD_DIFFY );			
	m_ppgbUserCount->SetPosition( rect.left + COMMANDNODE_DOWNCOORD_DIFFX, rect.top + COMMANDNODE_DOWNCOORD_DIFFY );			
}