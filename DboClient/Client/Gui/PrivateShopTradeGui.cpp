#include "precomp_dboclient.h"

// core
#include "NtlDebug.h"
#include "CEventHandler.h"

// presentation
#include "NtlPLGui.h"
#include "NtlPLGuiManager.h"

// framework
#include "NtlApplication.h"

// simulation
#include "NtlSLEvent.h"
#include "NtlSLGlobal.h"
#include "NtlSLApi.h"
#include "NtlSLLogic.h"
#include "NtlSLEventFunc.h"
#include "InputActionMap.h"
#include "NtlSobAvatar.h"
#include "NtlSobPlayer.h"
#include "NtlSobPlayerAttr.h"

// table
#include "TableContainer.h"
#include "TextAllTable.h"
#include "ItemTable.h"

// dbo
#include "DboGlobal.h"
#include "DboDef.h"
#include "DboEvent.h"
#include "DboLogic.h"
#include "DboEventGenerator.h"
#include "DboPacketGenerator.h"
#include "InfoWndManager.h"
#include "DisplayStringManager.h"
#include "DialogManager.h"
#include "SayFilter.h"

// privateShop Trade Gui
#include "PrivateShopGui.h"
#include "PrivateShopTradeGui.h"

#define dPRIVATESHOP_COLOR_TALK_I		RGB(255, 255, 255)
#define dPRIVATESHOP_COLOR_TALK_YOU		RGB(255, 255, 128)

//////////////////////////////////////////////////////////////////////////
// CPrivateShopTradeGui
//////////////////////////////////////////////////////////////////////////

/**
* \brief ������
*/
CPrivateShopTradeGui::CPrivateShopTradeGui(const RwChar* pName)
:CNtlPLGui(pName)
,m_pStbTitle(NULL)
,m_pBtnClose(NULL)
,m_pStbTradeItemTitle(NULL)
,m_pDlgTradeItem(NULL)
,m_pStbTradeItemName(NULL)
,m_pStbTradeItemPriceTitle(NULL)
,m_pStbTradeItemPrice(NULL)
,m_pStbChattingTitle(NULL)
,m_pOpbChatting(NULL)
,m_pIpbChatting(NULL)
,m_pStbIME(NULL)
,m_pBtnAction(NULL)
,m_uiShopOwner(0)
,m_uiTradeType(0)
,m_uiBusinessPrice(0)
,m_pShopGui(NULL)
,m_uiFluctuationCount(0)
{
	memset( m_awcTargetName, 0, sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME_UNICODE );
}

/**
* \brief �Ҹ���
*/
CPrivateShopTradeGui::~CPrivateShopTradeGui()
{
}

/**
* \brief Create
*/
RwBool CPrivateShopTradeGui::Create()
{
	NTL_FUNCTION("CPrivateShopTradeGui::Create");

	if (!CNtlPLGui::Create("", "gui\\PrivateShopTrade.srf", "gui\\PrivateShopTrade.frm"))
		NTL_RETURN(FALSE);

	CNtlPLGui::CreateComponents(GetNtlGuiManager()->GetGuiManager());

	// Components
	m_pThis						= (gui::CDialog*)GetComponent("dlgMain");
	m_pStbTitle					= (gui::CStaticBox*)GetComponent("stbTitle");
	m_pBtnClose					= (gui::CButton*)GetComponent("btnClose");
	m_pStbTradeItemTitle		= (gui::CStaticBox*)GetComponent("stbTradeItemTitle");
	m_pDlgTradeItem				= (gui::CDialog*)GetComponent("dlgTradeItem");
	m_pStbTradeItemName			= (gui::CStaticBox*)GetComponent("stbTradeItemName");
	m_pStbTradeItemPriceTitle	= (gui::CStaticBox*)GetComponent("stbTradeItemPriceTitle");
	m_pStbTradeItemPrice		= (gui::CStaticBox*)GetComponent("stbTradeItemPrice");
	m_pStbChattingTitle			= (gui::CStaticBox*)GetComponent("stbChattingTitle");
	m_pOpbChatting				= (gui::COutputBox*)GetComponent("opbChatting");
	m_pIpbChatting				= (gui::CInputBox*)GetComponent("ipbChatting");
	m_pStbIME					= (gui::CStaticBox*)GetComponent("stbIME");
	m_pBtnAction				= (gui::CButton*)GetComponent("btnAction");

	// Priority
	m_pThis->SetPriority( dDIALOGPRIORITY_PRIVATE_BUSINESS );

	// ���� ���� ������ ����
	m_sgTradeItem.Create(m_pDlgTradeItem, DIALOG_PRIVATESHOP_TRADE, REGULAR_SLOT_ITEM_TABLE, SDS_COUNT);

	// Signals
	m_slotIMEChanged		= m_pIpbChatting->SigIMEChanged().Connect(this, &CPrivateShopTradeGui::OnIMEChanged);
	m_slotMoveDlgTradeItem	= m_pDlgTradeItem->SigMove().Connect(this, &CPrivateShopTradeGui::OnMoveDlgTradeItem);
	m_slotPaintDlgTradeItem	= m_pDlgTradeItem->SigPaint().Connect(this, &CPrivateShopTradeGui::OnPaintDlgTradeItem);
	m_slotGotFocus			= m_pIpbChatting->SigGotFocus().Connect(this, &CPrivateShopTradeGui::OnGotFocus);
	m_slotLostFocus			= m_pIpbChatting->SigLostFocus().Connect(this, &CPrivateShopTradeGui::OnLostFocus);
	m_slotClickedBtnAction	= m_pBtnAction->SigClicked().Connect(this, &CPrivateShopTradeGui::OnClickedBtnAction);
	m_slotClickedBtnClose	= m_pBtnClose->SigClicked().Connect(this, &CPrivateShopTradeGui::OnClickedBtnClose );
	m_slotChatReturn		= m_pIpbChatting->SigReturnPressed().Connect(this, &CPrivateShopTradeGui::OnChatReturn);

	m_pStbTitle->SetPosition(DBOGUI_DIALOG_TITLE_X, DBOGUI_DIALOG_TITLE_Y);
	m_pStbTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_TITLE ) );
	m_pStbTradeItemTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_ITEMTITLE ) );
	m_pStbTradeItemPriceTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_ITEMPRICE ) );
	m_pStbChattingTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_CHAT ) );

	// ��ǲ �ڽ��� NativeMode�� �ʱ�ȭ���ְ�,
	m_pIpbChatting->SetNativeMode();
	OnIMEChanged(m_pIpbChatting->GetCurrentIMEState());

	// ���� �������̽��� �ʱ�ȭ�Ѵ�.
	ClearUserInterface();
	
	Show(false);

	// Link
	LinkMsg( g_EventChatMessagePrivateShopBusiness, 0 );
	LinkMsg( g_EventPrivateShopBusinessPricefluctuationsRes, 0 );
	LinkMsg( g_EventPrivateShopBusinessPricefluctuationsNfy, 0 );
	LinkMsg( g_EventPrivateShopBusinessStart, 0 );
	LinkMsg( g_EventPrivateShopBusinessCloseWindow, 0 );
	LinkMsg( g_EventMsgBoxResult, 0 );
		
	NTL_RETURN(TRUE);
}

/**
* \brief Destroy
*/
void CPrivateShopTradeGui::Destroy()
{
	NTL_FUNCTION("CPrivateShopTradeGui::Destroy");

	// UnLink
	UnLinkMsg( g_EventChatMessagePrivateShopBusiness );
	UnLinkMsg( g_EventPrivateShopBusinessPricefluctuationsRes );
	UnLinkMsg( g_EventPrivateShopBusinessPricefluctuationsNfy );
	UnLinkMsg( g_EventPrivateShopBusinessStart );
	UnLinkMsg( g_EventPrivateShopBusinessCloseWindow );
	UnLinkMsg( g_EventMsgBoxResult );

	m_sgTradeItem.Destroy();

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();

	NTL_RETURNVOID();
}

/**
* \brief HandleEvents
*/
void CPrivateShopTradeGui::HandleEvents(RWS::CMsg& msg)
{
	NTL_FUNCTION("CPrivateShopTradeGui::HandleEvents");

	// ���λ��� ���� ������ �̺�Ʈ	
	if( msg.Id == g_EventPrivateShopBusinessStart )
	{
		SDboEventPrivateShopBusinessStart* pData =
			reinterpret_cast<SDboEventPrivateShopBusinessStart*>(msg.pData);

		// Interface Setting 
		SetInterface( pData->uiType, pData->uiShopOwner, pData->awcTargetName, pData->pPrivateShopItemData );
		m_uiBusinessPrice = pData->pPrivateShopItemData->dwZenny;	// ����
		m_pShopGui = reinterpret_cast<CPrivateShopGui*>(pData->pGui);

		// Open Dialog
		if( FALSE == GetDialogManager()->IsOpenDialog( DIALOG_PRIVATESHOP_TRADE ) )
		{
			GetDialogManager()->OpenDialog( DIALOG_PRIVATESHOP_TRADE );

			// Chatting â�� Focus
			m_pIpbChatting->SetFocus();
		}
	}
	// Todo( Ŀ�´�Ƽ �������� TU_CHAT_MESSAGE_PRIVATESHOP_BUSINESS )
	// 1. �׻���� �̸��� : �޽����� �ѷ���� �Ѵ�.
	else if( msg.Id == g_EventChatMessagePrivateShopBusiness )
	{
		SNtlEventChatMessagePrivateShopBusiness* pChat =
			reinterpret_cast<SNtlEventChatMessagePrivateShopBusiness*>(msg.pData);

		// Outâ�� ä�� ���
		WCHAR awcBuffer[512];
		swprintf_s( awcBuffer, 512, L"[%s] : %s", pChat->pwchSenderCharName, pChat->awcMessage );

		// �̸��� ���� ���
		if( !wcscmp( Logic_GetAvatarName(), pChat->pwchSenderCharName ) )
		{
			AddChattingString( ePRIVATESHOP_TRADE_TALK_TYPE_I, awcBuffer );
		}
		// �ٸ� ���
		else
		{
			AddChattingString( ePRIVATESHOP_TRADE_TALK_TYPE_YOU, awcBuffer );
		}
	}
	// Todo(������ UG_PRIVATESHOP_BUSINESS_PRICEFLUCTUATIONS_RES )
	// 1. ������ ����ȴ�.
	// 2. ������ ����Ǿ��ٴ� ��ȭ���ڸ� ����.
	// 3. ������ OK �� �ϸ� ��ȭ���ڴ� off�ǰ� ���� â�� ������ ����ȴ�.
	else if( msg.Id == g_EventPrivateShopBusinessPricefluctuationsRes )
	{
		SNtlEventPrivateShopBusinessPricefluctuationsRes* pResult =
			reinterpret_cast<SNtlEventPrivateShopBusinessPricefluctuationsRes*>(msg.pData);

		m_pStbTradeItemPrice->SetText( pResult->dwAfterZenny );
		m_uiBusinessPrice = pResult->dwAfterZenny;	// ����

		//CDboEventGenerator::MsgBoxShow( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_APPLYPRICE ), 
		//	MBW_NONE, MBTF_OK, TRUE );
		GetAlarmManager()->AlarmMessage( DST_PRIVATESHOP_BUSINESS_TRADE_APPLYPRICE );
	}
	// Todo(���� ���� �մ��� UG_PRIVATESHOP_BUSINESS_PRICEFLUCTUATIONS_NFY)
	// 1. ������ ����ȴ�.
	// 2. ������ ����Ǿ��ٴ� ��ȭ���ڸ� ����.
	// 3. �մ��� OK �� �ϸ� ��ȭ���ڴ� off�ǰ� ���� â�� ������ ����ȴ�.
	else if( msg.Id == g_EventPrivateShopBusinessPricefluctuationsNfy )
	{
		SNtlEventPrivateShopBusinessPricefluctuationsNfy* pResult =
			reinterpret_cast<SNtlEventPrivateShopBusinessPricefluctuationsNfy*>(msg.pData);

		m_pStbTradeItemPrice->SetText( pResult->dwAfterZenny );
		m_uiBusinessPrice = pResult->dwAfterZenny;

		// �մ��̶�� ī��Ʈ�� ���������ش�.
		m_uiFluctuationCount++;

		//CDboEventGenerator::MsgBoxShow( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_APPLYNOTIFY ),
		//	MBW_NONE, MBTF_OK, TRUE );
		GetAlarmManager()->AlarmMessage( DST_PRIVATESHOP_BUSINESS_TRADE_APPLYNOTIFY );
	}
	else if( msg.Id == g_EventMsgBoxResult )
	{
		SDboEventMsgBoxResult* pMsgBoxResult = reinterpret_cast<SDboEventMsgBoxResult*>(msg.pData);

		// �޽��� �ڽ��� ���
		switch (pMsgBoxResult->uiWorkId)
		{
		case MBW_PRIVATESHOP_BUSINESS_IMMEDIATE:	// ��� ���Ÿ� ������ ���
			{
				// ���� �����Ͻðڽ��ϱ�? -> OK
				if( pMsgBoxResult->eResult == MBR_OK )
				{
					GetDboGlobal()->GetGamePacketGenerator()->SendPrivateShopBusinessImmediateItemBuyingReq( m_uiShopOwner, m_uiFluctuationCount );
				}
			}
			break;
		}
	}
	else if( msg.Id == g_EventPrivateShopBusinessCloseWindow )
	{
		//SDboEventPrivateShopBusinessCloseWindowNfy* pNotify = reinterpret_cast<SDboEventPrivateShopBusinessCloseWindowNfy*>( msg.pData );

		m_bCloseNotify = TRUE;

		if( GetDialogManager()->IsOpenDialog( DIALOG_PRIVATESHOP_TRADE ) )
			GetDialogManager()->CloseDialog( DIALOG_PRIVATESHOP_TRADE );
	}

	NTL_RETURNVOID();
}

RwInt32 CPrivateShopTradeGui::SwitchDialog(bool bOpen)
{
	Show(bOpen);

	if (!bOpen)
	{
		// ���� ���� ���ε� ESC�� ��Ÿ �ٸ� ���ο� ���Ͽ� ���� â�� �ݱ�ٸ�,
		if( m_pShopGui )
		{
			if( m_pShopGui->GetShopBusiness() )
			{
				RwUInt32 uiAvatarSerial = GetNtlSLGlobal()->GetSobAvatar()->GetSerialID();

				if( m_bCloseNotify )
				{
					m_pShopGui = NULL;
					return TRUE;
				}
				
				// �ڽ��� �մ��̶�ų� ���� ������ ���
				if( m_pShopGui->GetShopBusinessTarget() == uiAvatarSerial
					|| m_uiShopOwner == uiAvatarSerial )
				{
					// ��� ��û ��Ŷ�� ������.
					GetDboGlobal()->GetGamePacketGenerator()->SendPrivateShopBusinessCancelReq( m_uiShopOwner );
					m_pShopGui = NULL;

					//GetDialogManager()->CloseDialog( DIALOG_PRIVATESHOP_TRADE );
					return TRUE;
				}
			}
		}

		ClearUserInterface();
	}
	else
	{
		m_bCloseNotify = FALSE;
		m_pOpbChatting->Clear();
		m_pIpbChatting->Clear();
	}

	return TRUE;
}

/**
* \brief m_pIpbChatting�� IME ��尡 ����Ǿ��� ���� Callback
* \param eIMEState		IME�� ����
*/
void CPrivateShopTradeGui::OnIMEChanged(RwInt32 eIMEState)
{
	if (eIMEState == 0)
	{
		m_pStbIME->SetText( GetDisplayStringManager()->GetString( DST_CHAT_IME_ENG ) );
	}
	else
	{
		m_pStbIME->SetText( GetDisplayStringManager()->GetString( DST_CHAT_IME_KOR ) );
	}
}

void CPrivateShopTradeGui::OnMoveDlgTradeItem(RwInt32 iOldX, RwInt32 iOldY)
{
	CRectangle rect = m_pDlgTradeItem->GetScreenRect();
	m_sgTradeItem.SetParentPosition(rect.left, rect.top);
}

void CPrivateShopTradeGui::OnPaintDlgTradeItem()
{
	m_sgTradeItem.Paint();
}

/**
* \brief Imeâ�� Focus�� ����� ���
*/
VOID CPrivateShopTradeGui::OnGotFocus() 
{
	GetDboGlobal()->GetGameData()->bChatMode = TRUE;
}

/**
* \brief Imeâ�� Focus�� �Ҿ��� ���
*/
VOID CPrivateShopTradeGui::OnLostFocus() 
{
	GetDboGlobal()->GetGameData()->bChatMode = FALSE;
}

/**
* \brief Action ��ư�� Ŭ���Ͽ��� ��� ( ���� : ��������, �մ� : ��ñ��� )
*/
void CPrivateShopTradeGui::OnClickedBtnAction( gui::CComponent* pComponent ) 
{
	// ������ ���� ������ Ŭ���Ͽ��� ���
	if( m_uiTradeType == CPrivateShopGui::PRIVATESHOP_SELL )
	{
		CDboEventGenerator::PrivateShopBusinessFluctuations( CPrivateShopGui::PRIVATESHOP_SELL,
			const_cast<sPRIVATESHOP_ITEM_DATA*>(m_pPrivateShopItemData) , m_uiBusinessPrice);
	}
	// �մ��� ��� ���Ÿ� Ŭ���Ͽ��� ���
	else if( m_uiTradeType == CPrivateShopGui::PRIVATESHOP_BUY )
	{
		if( GetDialogManager()->IsOpenDialog( DIALOG_PRIVATESHOP_TRADE ) )
		{
			//CDboEventGenerator::MsgBoxShow( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_REALLYBUY ),
			//	MBW_PRIVATESHOP_BUSINESS_IMMEDIATE,
			//	MBTF_OK | MBTF_CANCEL, TRUE );
			GetAlarmManager()->AlarmMessage( DST_PRIVATESHOP_BUSINESS_TRADE_REALLYBUY );
		}
	}
}

void CPrivateShopTradeGui::OnClickedBtnClose( gui::CComponent* pComponent ) 
{
	// ��� ��û ��Ŷ
	GetDboGlobal()->GetGamePacketGenerator()->SendPrivateShopBusinessCancelReq( m_uiShopOwner );
}

/**
* \brief ä�� �Է�
// Todo( ���� â������ ä���� �Է����� ��� )
// 1. ��ȭ��û�ڰ� ��ȭ������� �̸����� �޽����� �����ش�.
//  -1. ��ȭ��û���� GUI�� �ڽ��� ä���� ǥ���Ѵ�.
//  -2. UT_CHAT_MESSAGE_PRIVATESHOP_BUSINESS(�޽����� ������.)
*/
void CPrivateShopTradeGui::OnChatReturn() 
{
	if( m_pIpbChatting->GetLength() )
	{
		// ä�� ����
		const WCHAR *pText = m_pIpbChatting->GetText();
		CChatPacketGenerator *pChatPacketGenerator = CDboGlobal::GetInstance()->GetChatPacketGenerator();

		// �弳 ���͸�
		std::wstring strFilterText = GetChattingFilter()->Filtering( pText );


		// �ڽ��� ä�� ���� ��Ŷ�� �޾Ƽ� ó���ϴ� ������ �Ѵ�.
		
		//// OutPutâ�� ä�� ���
		//WCHAR awcBuffer[512];
		//swprintf_s( awcBuffer, 512, L"[%s] : %s", Logic_GetName( pSobAvatar ), strFilterText.c_str() );
		//AddChattingString( ePRIVATESHOP_TRADE_TALK_TYPE_I, awcBuffer );

		// Ŀ�´�Ƽ ������ ä�� ������ ������
		pChatPacketGenerator->SendChatMessagePrivateShopBusiness( m_awcTargetName, (RwUInt16)strFilterText.size(), strFilterText.c_str() );
		
		// Input Box�� ������ �����ش�.
		m_pIpbChatting->Clear();
	}
}

/**
* \brief �մ��̳� ���ο� �˸��� �������̽� ����
* �մ��̶�� ��� ���� ��ư�� ����
* �����̶�� ���� ���� ��ư�� ����
*/
void CPrivateShopTradeGui::SetInterface( RwUInt8 uiType, RwUInt32 uiShopOwner, WCHAR* pwcTargetName, const sPRIVATESHOP_ITEM_DATA* pPrivateShopItemData ) 
{
	// �մ�
	if( uiType == CPrivateShopGui::PRIVATESHOP_BUY )
	{
		m_pBtnAction->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_IMMEDIATE ) );
	}
	// ����
	else if( uiType == CPrivateShopGui::PRIVATESHOP_SELL )
	{
		m_pBtnAction->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADE_FLUCTUATIONS ) );
	}
	else
		return;

	m_uiFluctuationCount = 0;
	m_uiShopOwner = uiShopOwner;
	m_uiTradeType = uiType;
	swprintf_s( m_awcTargetName, NTL_MAX_SIZE_CHAR_NAME_UNICODE+1, L"%s", pwcTargetName );
	

	// �������̽��� �� �������� ����
	SetTradeItem( pPrivateShopItemData );
}

/**
* \brief �������̽��� �ʱ�ȭ
* ������ �����̳� �̸�, Outputâ�� Ŭ�����Ѵ�.
*/
void CPrivateShopTradeGui::ClearUserInterface()
{
	m_sgTradeItem.SetIcon(INVALID_TBLIDX);
	m_pStbTradeItemPrice->Clear();
	m_pStbTradeItemName->Clear();
	m_pOpbChatting->Clear();
	m_pIpbChatting->Clear();
	m_pShopGui = NULL;
	m_uiFluctuationCount = 0;

	// �������̽� �� ���� ȸ��
	GetDboGlobal()->GetGameData()->bChatMode = FALSE;
}

/**
* \brief ���� ���� �������� ����
* \param pPrivateShopItemData		���λ��� ������ ����Ÿ
*/
void CPrivateShopTradeGui::SetTradeItem(const sPRIVATESHOP_ITEM_DATA* pPrivateShopItemData)
{
	DBO_ASSERT(pPrivateShopItemData != NULL && pPrivateShopItemData->byPrivateShopInventorySlotPos != PRIVATESHOP_ITEMPOS_INVALID,"CPrivateShopTradeBoxGui::SetTradeItem Invalid Param");
	m_pPrivateShopItemData = pPrivateShopItemData;

	sITEM_TBLDAT* pItemTable = Logic_GetItemDataFromTable( m_pPrivateShopItemData->sItem.itemNo );
	if( pItemTable == NULL )
	{
		DBO_FAIL( "pItemTable is NULL" );
		return;
	}

	if ( m_pPrivateShopItemData->sItem.bNeedToIdentify )
	{
		m_sgTradeItem.Clear();
		m_sgTradeItem.SetSerialType( REGULAR_SLOT_ITEM_NOT_IDENTIFICATION );
		m_sgTradeItem.SetIcon( pPrivateShopItemData->sItem.itemNo, pPrivateShopItemData->sItem.byStackcount);
		m_pStbTradeItemName->SetText(GetDisplayStringManager()->GetString(DST_PRIVATESHOP_ITEM_NOT_IDENTIFICATION));
	}
	else
	{
		m_sgTradeItem.Clear();
		m_sgTradeItem.SetSerialType( REGULAR_SLOT_ITEM_TABLE );
		m_sgTradeItem.SetIcon( pPrivateShopItemData->sItem.itemNo, pPrivateShopItemData->sItem.byStackcount);
		m_pStbTradeItemName->SetText(m_sgTradeItem.GetItemTable()->wszNameText);
	}

	m_pStbTradeItemPrice->SetText((RwUInt32)pPrivateShopItemData->dwZenny); 
	memcpy(&m_sTradeItemData, &pPrivateShopItemData->sItem, sizeof(sITEM_DATA));
}

/**
* \brief ä�� Outputâ�� �۾� ���
* \param pwcString		���ڿ�
* \param uiColor		�۾� ����
*/
void CPrivateShopTradeGui::AddChattingString(const WCHAR* pwcString, RwUInt32 uiColor)
{
	m_pOpbChatting->AddText(pwcString, uiColor);
}

/**
* \brief ä�� Outputâ�� �۾� ���
* \param eTalkType		�ڽ�, ���
* \param pwcString		���ڿ�
*/
void CPrivateShopTradeGui::AddChattingString(ePRIVATESHOP_TRADE_TALK_TYPE eTalkType, const WCHAR* pwcString)
{
	// eTalkType�� ���� �˸��� (define ��) ������ �������༭ ����Ѵ�.
	switch (eTalkType)
	{
	case ePRIVATESHOP_TRADE_TALK_TYPE_I:
		AddChattingString(pwcString, dPRIVATESHOP_COLOR_TALK_I);
		break;
	case ePRIVATESHOP_TRADE_TALK_TYPE_YOU:
		AddChattingString(pwcString, dPRIVATESHOP_COLOR_TALK_YOU);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// CPrivateShopTradeBoxGui
//////////////////////////////////////////////////////////////////////////

/**
* \brief ������
*/
CPrivateShopTradeBoxGui::CPrivateShopTradeBoxGui(const RwChar* pName)
:CNtlPLGui(pName)
,m_pStbTitle(NULL)
,m_pStbSubTitle(NULL)
,m_pBtnClose(NULL)
,m_pDlgTradeItem(NULL)
,m_pStbTradeItemPricePrevTitle(NULL)
,m_pStbTradeItemPricePrev(NULL)
,m_pStbTradeItemPriceNextTitle(NULL)
,m_pStbTradeItemPriceNext(NULL)
,m_pBtnSubmit(NULL)
,m_uiPrice(0)
{
} 

/**
* \brief �Ҹ���
*/
CPrivateShopTradeBoxGui::~CPrivateShopTradeBoxGui()
{
}

/**
* \brief Create
*/
RwBool CPrivateShopTradeBoxGui::Create()
{
	NTL_FUNCTION("CPrivateShopTradeBoxGui::Create");

	if (!CNtlPLGui::Create("", "gui\\PrivateShopTradeBox.srf", "gui\\PrivateShopTradeBox.frm"))
		NTL_RETURN(FALSE);

	CNtlPLGui::CreateComponents(GetNtlGuiManager()->GetGuiManager());

	// Components
	m_pThis							= (gui::CDialog*)GetComponent("dlgMain");
	m_pStbTitle						= (gui::CStaticBox*)GetComponent("stbTitle");
	m_pStbSubTitle					= (gui::CStaticBox*)GetComponent("stbSubTitle");
	m_pBtnClose						= (gui::CButton*)GetComponent("btnClose");
	m_pDlgTradeItem					= (gui::CDialog*)GetComponent("dlgTradeItem");
	m_pStbTradeItemPricePrevTitle	= (gui::CStaticBox*)GetComponent("stbTradeItemPricePrevTitle");
	m_pStbTradeItemPricePrev		= (gui::CStaticBox*)GetComponent("stbTradeItemPricePrev");
	m_pStbTradeItemPriceNextTitle	= (gui::CStaticBox*)GetComponent("stbTradeItemPriceNextTitle");
	m_pStbTradeItemPriceNext		= (gui::CStaticBox*)GetComponent("stbTradeItemPriceNext");
	m_pBtnSubmit					= (gui::CButton*)GetComponent("btnSubmit");
	m_pBtnCancel					= (gui::CButton*)GetComponent("btnCancel");
	m_pBtnPrice						= (gui::CButton*)GetComponent("btnTradeItemPriceNext");

	// Priority
	m_pThis->SetPriority( dDIALOGPRIORITY_PRIVATE_BUSINESS_PRICE );

	m_sgTradeItem.Create(m_pDlgTradeItem, DIALOG_PRIVATESHOP_TRADEBOX, REGULAR_SLOT_ITEM_TABLE, SDS_COUNT);

	// Signals
	m_slotMoveDlgTradeItem	= m_pDlgTradeItem->SigMove().Connect(this, &CPrivateShopTradeBoxGui::OnMoveDlgTradeItem);
	m_slotPaintDlgTradeItem	= m_pDlgTradeItem->SigPaint().Connect(this, &CPrivateShopTradeBoxGui::OnPaintDlgTradeItem);
	m_slotClickedBtnSubmit = m_pBtnSubmit->SigClicked().Connect(this, &CPrivateShopTradeBoxGui::OnClickedBtnSubmit);
	m_slotClickedBtnCancel = m_pBtnCancel->SigClicked().Connect(this, &CPrivateShopTradeBoxGui::OnClickedBtnCancel);
	m_slotClickedBtnClose = m_pBtnCancel->SigClicked().Connect(this, &CPrivateShopTradeBoxGui::OnClickedBtnCancel);
	m_slotClickedBtnPrice = m_pBtnPrice->SigClicked().Connect(this, &CPrivateShopTradeBoxGui::OnClickedBtnPrice );

	m_pStbTitle->SetPosition(DBOGUI_DIALOG_TITLE_X, DBOGUI_DIALOG_TITLE_Y);
	m_pStbTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADEBOX_TITLE ) );
	m_pStbSubTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADEBOX_FLUCTUATIONS ) );
	m_pStbTradeItemPricePrevTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADEBOX_PREVPRICE ) );
	m_pStbTradeItemPricePrev->SetText(L"0");
	m_pStbTradeItemPriceNextTitle->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADEBOX_NEXTPRICE ) );
	m_pStbTradeItemPriceNext->SetText(L"0");
	m_pBtnSubmit->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADEBOX_ACCEPT ) );
	m_pBtnCancel->SetText( GetDisplayStringManager()->GetString( DST_PRIVATESHOP_BUSINESS_TRADEBOX_CANCEL ) );

	LinkMsg( g_EventPrivateShopBusinessFluctuations, 0 );
	LinkMsg( g_EventCalcPopupResult, 0 );

	ClearUserInterface();
	Show(false);
	NTL_RETURN(TRUE);
}

/**
* \brief Destroy
*/
void CPrivateShopTradeBoxGui::Destroy()
{
	NTL_FUNCTION("CPrivateShopTradeBoxGui::Destroy");

	UnLinkMsg( g_EventCalcPopupResult );
	UnLinkMsg( g_EventPrivateShopBusinessFluctuations );

	m_sgTradeItem.Destroy();

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();

	NTL_RETURNVOID();
}


/**
* \brief HandleEvents
*/
void CPrivateShopTradeBoxGui::HandleEvents(RWS::CMsg& msg)
{
	NTL_FUNCTION("CPrivateShopTradeBoxGui::HandleEvents");

	// ���� ���� â�� ����.
	if( msg.Id == g_EventPrivateShopBusinessFluctuations )
	{
		SDboEventPrivateShopBusinessFluctuations* pFluctuations
			= reinterpret_cast<SDboEventPrivateShopBusinessFluctuations*>(msg.pData);

		SetTradeItem( pFluctuations->pPrivateShopItemData, pFluctuations->uiStartPrice );
		
		if( FALSE == GetDialogManager()->IsOpenDialog( DIALOG_PRIVATESHOP_TRADEBOX ) )
		{
			GetDialogManager()->OpenDialog( DIALOG_PRIVATESHOP_TRADEBOX );
			RaiseTop();
		}
	}
	// ����� ������ �Է����� ���
	else if (msg.Id == g_EventCalcPopupResult)
	{
		SDboEventCalcPopupResult* pPopupResult = reinterpret_cast<SDboEventCalcPopupResult*>(msg.pData);
		if (pPopupResult->nSrcPlace == PLACE_PRIVATESHOP_TRADEBOX)
		{
			WCHAR awcBuffer[256];
			swprintf_s( awcBuffer, 256, L"%u", pPopupResult->uiValue );
			m_pStbTradeItemPriceNext->SetText( awcBuffer );
			m_uiPrice = pPopupResult->uiValue;
		}
	}


	NTL_RETURNVOID();
}

RwInt32 CPrivateShopTradeBoxGui::SwitchDialog(bool bOpen)
{
	Show(bOpen);

	if (!bOpen)
	{
		ClearUserInterface();
	}

	return TRUE;
}

void CPrivateShopTradeBoxGui::OnMoveDlgTradeItem(RwInt32 iOldX, RwInt32 iOldY)
{
	CRectangle rect = m_pDlgTradeItem->GetScreenRect();
	m_sgTradeItem.SetParentPosition(rect.left, rect.top);
}

void CPrivateShopTradeBoxGui::OnPaintDlgTradeItem()
{
	m_sgTradeItem.Paint();
}

/**
* \brief ���� ��ư�� Ŭ��
* ������ ������ �����Ѵ�.
*/
void CPrivateShopTradeBoxGui::OnClickedBtnSubmit( gui::CComponent* pComponent ) 
{
	// ������ ������ ������ ������.
	GetDboGlobal()->GetGamePacketGenerator()->SendPrivateShopBusinessPricefluctuationsReq( m_uiPrice );
	GetDialogManager()->CloseDialog( DIALOG_PRIVATESHOP_TRADEBOX );
}

/**
* \brief ��� ��ư�� Ŭ��
* ���� ���� â�� �ݴ´�.
*/
void CPrivateShopTradeBoxGui::OnClickedBtnCancel( gui::CComponent* pComponent ) 
{
	GetDialogManager()->CloseDialog( DIALOG_PRIVATESHOP_TRADEBOX );
}

/**
* \brief ������ ������ �����ϱ� ���� ���� ��ư�� Ŭ������ ��
*/
void CPrivateShopTradeBoxGui::OnClickedBtnPrice( gui::CComponent* pComponent ) 
{
	CRectangle rect = pComponent->GetScreenRect();
	CDboEventGenerator::CalcPopupShow(TRUE, m_pPrivateShopItemData->byPrivateShopInventorySlotPos, PLACE_PRIVATESHOP_TRADEBOX,
		rect.left - dPRIVATESHOP_UI_CALC_OFFSET, rect.top, dPRIVATESHOP_ITEM_PRICE_MAX);
}

/**
* \brief ���� ���� ���� �������� ����
*/
void CPrivateShopTradeBoxGui::SetTradeItem(const sPRIVATESHOP_ITEM_DATA* pPrivateShopItemData, RwUInt32 uiStartPrice)
{
	DBO_ASSERT(pPrivateShopItemData != NULL && pPrivateShopItemData->byPrivateShopInventorySlotPos != PRIVATESHOP_ITEMPOS_INVALID,"CPrivateShopTradeBoxGui::SetTradeItem Invalid Param");
	m_pPrivateShopItemData = pPrivateShopItemData;
	
	sITEM_TBLDAT* pItemTable = Logic_GetItemDataFromTable( m_pPrivateShopItemData->sItem.itemNo );
	if( pItemTable == NULL )
	{
		DBO_FAIL( " pItemTable is NULL " );
		return;
	}
		
	if ( m_pPrivateShopItemData->sItem.bNeedToIdentify )
	{
		m_sgTradeItem.Clear();
		m_sgTradeItem.SetSerialType( REGULAR_SLOT_ITEM_NOT_IDENTIFICATION );
		m_sgTradeItem.SetIcon( pPrivateShopItemData->sItem.itemNo, pPrivateShopItemData->sItem.byStackcount);
	}
	else
	{
		m_sgTradeItem.Clear();
		m_sgTradeItem.SetSerialType( REGULAR_SLOT_ITEM_TABLE );
		m_sgTradeItem.SetIcon( pPrivateShopItemData->sItem.itemNo, pPrivateShopItemData->sItem.byStackcount);
	}
	
	m_pStbTradeItemPricePrev->SetText((RwUInt32)uiStartPrice);
	m_pStbTradeItemPriceNext->SetText( uiStartPrice );
	m_uiPrice = uiStartPrice;

	memcpy(&m_sTradeItemData, &pPrivateShopItemData->sItem, sizeof(sITEM_DATA));
}

void CPrivateShopTradeBoxGui::ClearUserInterface()
{
	m_sgTradeItem.Clear();
	m_pStbTradeItemPricePrev->Clear();
	m_pStbTradeItemPriceNext->Clear();
	m_uiPrice = 0;
}