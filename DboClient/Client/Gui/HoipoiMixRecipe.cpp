#include "precomp_dboclient.h"
#include "HoipoiMixRecipe.h"

// Debug
#include "NtlDebug.h"

// Shared
#include "TableContainer.h"
#include "NtlItem.h"
#include "ItemMixMachineTable.h"

// Simulation
#include "NTLSLApi.h"
#include "NtlSLGlobal.h"
#include "NtlSLHoipoiMix.h"
#include "NtlSobAvatar.h"
#include "NtlSobDynamicObject.h"
#include "NtlSobDynamicObjectAttr.h"
#include "NtlSobManager.h"

// Presentation
#include "ItemRecipeTable.h"
#include "TextAllTable.h"
#include "NtlPLGuiManager.h"

// Client
#include "HoipoiMixGui.h"
#include "DboEventGenerator.h"
#include "DisplayStringManager.h"
#include "InfoWndManager.h"

#define dRECIPE_DLG_ITEM_OFFSET_TOP		10		// ������ ����� ���� ���� ������
#define dRECIPE_DLG_ITEM_HEIGHT			72		// ������ ����� ����
#define dRECIPE_DLG_ITEM_HEIGHT_MARGIN	10		// ������ ����� ����
#define dRECIPE_DLG_ITEM_VIEW_NUM		5		// �� ȭ�鿡 ���̴� ������ ����

//////////////////////////////////////////////////////////////////////////
// CRecipeDlgItem
//////////////////////////////////////////////////////////////////////////

CRecipeDlgItem::CRecipeDlgItem()
{
	m_pThis = NULL;

	m_nIndex = -1;
	m_idxTbl = INVALID_TBLIDX;

	m_pStbRecipeName = NULL;
	m_pStbRequiredLevel = NULL;
	m_pStbZenny = NULL;
	m_pHoipoiMix = NULL;
	m_bSelect = FALSE;
}

CRecipeDlgItem::~CRecipeDlgItem()
{

}

RwBool CRecipeDlgItem::Create( RwInt32 nIndex, CHoipoiMixCapsuleGui* pParentGui, TBLIDX idxRecipeTbl, RwUInt8 byDiscountRate  )
{
	m_pHoipoiMix = pParentGui;
	m_nIndex = nIndex;
	m_idxTbl = idxRecipeTbl;

	// ���� ��� GUI ������Ʈ�� �θ� ������ ���Ǿ� Ŭ���� �Ӽ��� ������.

	// ������ �����ϰ� Recipe list Dialog�� ������ �޾��ش�.
	CRectangle rect;
	rect.SetRectWH( 16, (nIndex * (dRECIPE_DLG_ITEM_HEIGHT+dRECIPE_DLG_ITEM_HEIGHT_MARGIN)) + dRECIPE_DLG_ITEM_OFFSET_TOP, 278, 67 );
	m_pThis = NTL_NEW gui::CDialog( &rect, pParentGui->GetComponent("dlgRecipeList"), GetNtlGuiManager()->GetSurfaceManager() );
	m_pThis->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "HoipoiMix.srf", "srfRecipeSlot" ) );
	m_slotPaint = m_pThis->SigPaint().Connect( this, &CRecipeDlgItem::OnPaint );
	m_slotMove = m_pThis->SigMove().Connect( this, &CRecipeDlgItem::OnMove );
	m_slotEnterItem = m_pThis->SigMouseEnter().Connect( this, &CRecipeDlgItem::OnEnterItem );
	m_slotLeaveItem = m_pThis->SigMouseLeave().Connect( this, &CRecipeDlgItem::OnLeaveItem );
	m_slotMouseDown = m_pThis->SigMouseDown().Connect( this, &CRecipeDlgItem::OnMouseDown );
	m_slotMouseUp = m_pThis->SigMouseUp().Connect( this, &CRecipeDlgItem::OnMouseUp );
	m_slotMouseMove = m_pThis->SigMouseMove().Connect( this, &CRecipeDlgItem::OnMouseMove );
	
	m_pThis->SetClippingMode( true );

	m_pItemRecipeTblDat = (sITEM_RECIPE_TBLDAT*)API_GetTableContainer()->GetItemRecipeTable()->FindData( idxRecipeTbl );
	if( m_pItemRecipeTblDat == NULL )
	{
		DBO_FAIL( "CRecipeDlgItem::Create - Out of item recipe table index" );
		return FALSE;
	}

	// �����Ǵ� �������� ������ ����, ������ ���̺��� 0�� �ε����� ��ǥ �̹����̴�.
	m_Slot.Create( m_pThis, DIALOG_HOIPOIMIX_CAPSULE, REGULAR_SLOT_ITEM_TABLE, SDS_NONE );
	m_Slot.SetPosition_fromParent( 9, 17 );
	m_Slot.SetIcon( m_pItemRecipeTblDat->asCreateItemTblidx[0].itemTblidx );
	m_Slot.SetClippingMode( TRUE );
	
	// Recipe Name
	rect.SetRectWH( 57, 4 , 250, 20 );
	m_pStbRecipeName = NTL_NEW gui::CStaticBox( &rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager() );
	m_pStbRecipeName->CreateFontStd( DEFAULT_FONT, 95, DEFAULT_FONT_ATTR );

	sTEXT_TBLDAT* pTextTblDat = (sTEXT_TBLDAT*)API_GetTableContainer()->GetTextAllTable()->GetItemTbl()->FindData( m_pItemRecipeTblDat->dwName );
	if( pTextTblDat )
	{
		m_pStbRecipeName->SetText( pTextTblDat->wstrText.c_str() );
	}
	else
	{
		WCHAR awcErrBuffer[32];
		swprintf_s( awcErrBuffer, 32, L"(ITEM_T_TBL)%d", m_pItemRecipeTblDat->dwName );
		m_pStbRecipeName->SetText( awcErrBuffer );
	}
	m_pStbRecipeName->SetClippingMode( true );
	m_pStbRecipeName->Enable( false );
	
	// Required Level
	rect.SetRectWH( 58, 25, 200, 20 );
	m_pStbRequiredLevel = NTL_NEW gui::CStaticBox( &rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager() );
	m_pStbRequiredLevel->CreateFontStd( DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR );
	m_pStbRequiredLevel->SetTextColor( RGB( 148, 221, 255 ) );
	m_pStbRequiredLevel->Enable( false );

	WCHAR awcBuffer[256];
	swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( DST_HOIPOIMIX_REQUIRED_LEVEL ), m_pItemRecipeTblDat->byNeedMixLevel );
	m_pStbRequiredLevel->SetText( awcBuffer );
	m_pStbRequiredLevel->SetClippingMode( true );
	m_pStbRequiredLevel->Enable( false );

	// Zenny Price
	rect.SetRectWH( 58, 48, 200, 12 );
	m_pStbZenny = NTL_NEW gui::CStaticBox( &rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager() );
	m_pStbZenny->CreateFontStd( DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR );
	m_pStbZenny->SetTextColor( INFOCOLOR_7 );
	m_pStbZenny->SetClippingMode( true );
	swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( DST_HOIPOIMIX_REQUIRED_ZENNY ), Dbo_GetHoipoiMixFare( m_pItemRecipeTblDat->dwNeedMixZenny, byDiscountRate ) );
	m_pStbZenny->SetText( awcBuffer );
	m_pStbZenny->Enable( false );

	OnMove( 0, 0 );

	return TRUE;
}

VOID CRecipeDlgItem::Destroy()
{
	NTL_DELETE( m_pStbZenny );
	NTL_DELETE( m_pStbRequiredLevel );
	NTL_DELETE( m_pStbRecipeName );

	m_Slot.Destroy();

	NTL_DELETE( m_pThis );

}

RwUInt8 CRecipeDlgItem::GetRecipeType()
{
	return m_pItemRecipeTblDat->byRecipeType;
}

TBLIDX CRecipeDlgItem::GetRecipeTableIndex()
{
	return m_idxTbl;
}

VOID CRecipeDlgItem::OnPaint()
{
	if( m_pThis->IsVisible() )
		m_Slot.Paint();
}

VOID CRecipeDlgItem::OnMove( int nOldX, int nOldY )
{
	CRectangle rect = m_pThis->GetScreenRect();
	m_Slot.SetParentPosition( rect.left, rect.top );

	CRectangle rtClipping = m_pThis->GetClippingRect();
	m_Slot.SetClippingRect( rtClipping );
}

VOID CRecipeDlgItem::SetDiscountRate( RwUInt8 byDiscountRate )
{
	m_pStbZenny->SetText( (RwInt32)Dbo_GetHoipoiMixFare( m_pItemRecipeTblDat->dwNeedMixZenny, byDiscountRate ) );
}

VOID CRecipeDlgItem::RecipeItemDisposition( RwUInt32 uiIndex )
{
	m_nIndex = uiIndex;

	CRectangle rect;
	gui::CSurface sur = GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "HoipoiMix.srf", "srfRecipeSlot" );
	rect.SetRectWH( 16, 
		(uiIndex * (sur.m_Original.rtRect.GetHeight() + 5 + dRECIPE_DLG_ITEM_HEIGHT_MARGIN)) + dRECIPE_DLG_ITEM_OFFSET_TOP,
		sur.m_Original.rtRect.GetWidth(),
		sur.m_Original.rtRect.GetHeight() );

	m_pThis->SetPosition( rect );
	m_pThis->SetClippingMode( TRUE );

	rect = m_pThis->GetScreenRect();
	m_Slot.SetParentPosition( rect.left, rect.top );

	CRectangle rtClipping = m_pThis->GetClippingRect();
	m_Slot.SetClippingMode( TRUE );
	m_Slot.SetClippingRect( rtClipping );
	
	
	m_surIcon.SetClippingMode( TRUE );
	m_pStbRecipeName->SetClippingMode( TRUE );
	m_pStbRequiredLevel->SetClippingMode( TRUE );
	m_pStbZenny->SetClippingMode( TRUE );
}

VOID CRecipeDlgItem::Show( RwBool bShow )
{
	m_pThis->Show( B2b( bShow ) );
}

VOID CRecipeDlgItem::SelectItem( RwBool bSelect )
{
	m_bSelect = bSelect;

	if( m_bSelect )
	{
		m_pThis->GetSurface()->clear();
		m_pThis->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "HoipoiMix.srf", "srfRecipeSlotFocus" ) );
	}
	else
	{
		m_pThis->GetSurface()->clear();
		m_pThis->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "HoipoiMix.srf", "srfRecipeSlot" ) );
	}
}

VOID CRecipeDlgItem::OnEnterItem( gui::CComponent* pComponent )
{
	if( !m_bSelect )
	{
		m_pThis->GetSurface()->clear();
		m_pThis->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "HoipoiMix.srf", "srfRecipeSlotFocus" ) );
	}
}

VOID CRecipeDlgItem::OnLeaveItem( gui::CComponent* pComponent )
{
	if( !m_bSelect )
	{
		m_pThis->GetSurface()->clear();
		m_pThis->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "HoipoiMix.srf", "srfRecipeSlot" ) );
	}

	m_bMouseDown = FALSE;

	if( GetInfoWndManager()->GetRequestGui() == DIALOG_HOIPOIMIX_CAPSULE )
		GetInfoWndManager()->ShowInfoWindow( FALSE );
}

VOID CRecipeDlgItem::OnMouseDown( const CKey& key )
{
	if( key.m_nID != UD_LEFT_BUTTON )
		return;

	m_bMouseDown = TRUE;
}

VOID CRecipeDlgItem::OnMouseUp( const CKey& key )
{
	if( key.m_nID != UD_LEFT_BUTTON )
		return;

	if( m_bMouseDown )
	{
		m_bMouseDown = FALSE;

		// Select
		m_pHoipoiMix->SelectRecipe( this );
	}
}

VOID CRecipeDlgItem::OnMouseMove( RwInt32 nKeys,RwInt32 nX,RwInt32 nY )
{
	CRectangle rect = m_pThis->GetScreenRect();
	if( m_Slot.PtInRect( nX, nY ) )
	{
		sITEM_RECIPE_TBLDAT* pTblDat = (sITEM_RECIPE_TBLDAT*)API_GetTableContainer()->GetItemRecipeTable()->FindData( GetRecipeTableIndex() );
		if( pTblDat )
		{
			GetInfoWndManager()->ShowInfoWindow(TRUE, CInfoWndManager::INFOWND_RECIPE, 
				rect.left + m_Slot.GetX_fromParent(), rect.top + m_Slot.GetY_fromParent(), 
				(VOID*)pTblDat, 
				DIALOG_HOIPOIMIX_CAPSULE);
		}
		else
		{
			WCHAR awcBuffer[128];
			swprintf_s( awcBuffer, 128, L"Invalid recipe table idx %d", GetRecipeTableIndex() );
			GetInfoWndManager()->ShowInfoWindow(TRUE, CInfoWndManager::INFOWND_JUST_WTEXT, 
				rect.left + m_Slot.GetX_fromParent(), rect.top + m_Slot.GetY_fromParent(), 
				(VOID*)awcBuffer,
				DIALOG_HOIPOIMIX_CAPSULE);
		}
	}
	else
	{
		if( GetInfoWndManager()->GetRequestGui() == DIALOG_HOIPOIMIX_CAPSULE )
			GetInfoWndManager()->ShowInfoWindow( FALSE );
	}
}

// Built-in ���� ������ �� �ִ� �ִ� ������ ���
#define dRECIPE_DLG_ITEM_BUILTIN_NUM	3

//////////////////////////////////////////////////////////////////////////
// CHoipoiMixRecipe
//////////////////////////////////////////////////////////////////////////

CHoipoiMixRecipe::CHoipoiMixRecipe()
{
	m_pThis = NULL;
	m_pListDialog = NULL;
	m_pScbBar = NULL;
	m_pHoipoiMix = NULL;
	m_byDiscountRate = 0;
	m_pSelectDlgItem = NULL;
}

CHoipoiMixRecipe::~CHoipoiMixRecipe()
{ 
}

RwBool CHoipoiMixRecipe::Create( CHoipoiMixCapsuleGui* pParentGui )
{
	m_pHoipoiMix	= pParentGui;
	m_pThis			= (gui::CDialog*)pParentGui->GetComponent( "dlgRecipe" );
	m_pClipDialog	= (gui::CDialog*)pParentGui->GetComponent( "dlgRecipeClip" );
	m_pListDialog	= (gui::CDialog*)pParentGui->GetComponent( "dlgRecipeList" );
	m_pScbBar		= (gui::CScrollBar*)pParentGui->GetComponent( "scbScroll" );
	m_pBtnFilter[FILTER_TOTAL]	= (gui::CButton*)pParentGui->GetComponent("btnFilter1");
	m_pBtnFilter[FILTER_TOTAL]->SetText( GetDisplayStringManager()->GetString( DST_HOIPOIMIX_RECIPE_FILTER_TOTAL ) );
	m_pBtnFilter[FILTER_BUILTIN]	= (gui::CButton*)pParentGui->GetComponent("btnFilter2");
	m_pBtnFilter[FILTER_BUILTIN]->SetText( GetDisplayStringManager()->GetString( DST_HOIPOIMIX_RECIPE_FILTER_BUILT_IN ) );
	m_pBtnFilter[FILTER_NORMAL]	= (gui::CButton*)pParentGui->GetComponent("btnFilter3");
	m_pBtnFilter[FILTER_NORMAL]->SetText( GetDisplayStringManager()->GetString( DST_HOIPOIMIX_RECIPE_FILTER_NORMAL ) );
	m_pBtnFilter[FILTER_SPECIAL] = (gui::CButton*)pParentGui->GetComponent("btnFilter4");
	m_pBtnFilter[FILTER_SPECIAL]->SetText( GetDisplayStringManager()->GetString( DST_HOIPOIMIX_RECIPE_FILTER_SPECIAL ) );

	// ���� ��ư �� ���� ù��° ���͸� ���� ���·� �����Ѵ�.
	m_pBtnFilter[FILTER_TOTAL]->SetDown();
	m_pBtnFilter[FILTER_TOTAL]->ClickEnable( FALSE );
	
	m_slotScrollChanged			= m_pScbBar->SigValueChanged().Connect( this, &CHoipoiMixRecipe::OnScrollChanged );
	m_slotScrollSliderMoved		= m_pScbBar->SigSliderMoved().Connect( this, &CHoipoiMixRecipe::OnScrollChanged );
	m_slotToggledFilterTotal	= m_pBtnFilter[FILTER_TOTAL]->SigToggled().Connect( this, &CHoipoiMixRecipe::OnToggledFilter );
	m_slotToggledFilterBuiltIn	= m_pBtnFilter[FILTER_BUILTIN]->SigToggled().Connect( this, &CHoipoiMixRecipe::OnToggledFilter );
	m_slotToggledFilterNormal	= m_pBtnFilter[FILTER_NORMAL]->SigToggled().Connect( this, &CHoipoiMixRecipe::OnToggledFilter );
	m_slotToggledFilterSpecial	= m_pBtnFilter[FILTER_SPECIAL]->SigToggled().Connect( this, &CHoipoiMixRecipe::OnToggledFilter );
	m_slotAbsoluteMouseWheel	= GetNtlGuiManager()->GetGuiManager()->SigCaptureWheelMove().Connect( this, &CHoipoiMixRecipe::OnAbsoluteMouseWheel );

	// ������ ����Ʈ�� �����.
	// ���� : GUI�� �����Ǵ� ���������� �ƹ�Ÿ ��ü�� ������� ���� �ʾ����� NtlSLGLobal���� �����͸� �޾ƿ´�.
	CreateAvatarRecipeList();

	return TRUE;
}

VOID CHoipoiMixRecipe::Destroy()
{
	// Recipe Dialog���� �������ش�.
	DestroyAvatarRecipeList();
	DestroyBuiltInRecipeList();
}

VOID CHoipoiMixRecipe::Show( bool bShow )
{
	m_pThis->Show( bShow );

	if( bShow )
	{
		CreateRecipeFilterList();
		RecipeDispoisition();
	}
}

RwBool CHoipoiMixRecipe::IsShow()
{
	return m_pThis->IsVisible();
}

VOID CHoipoiMixRecipe::HandleEvents( RWS::CMsg& msg )
{
	if( msg.Id == g_EventHoipoiMixRecipeRegNfy )
	{
		SNtlEventHoipoiMixRecipeRegNfy* pNotify = reinterpret_cast<SNtlEventHoipoiMixRecipeRegNfy*>( msg.pData );

		CRecipeDlgItem* pItem = NTL_NEW CRecipeDlgItem();
		pItem->Create( 0, m_pHoipoiMix, pNotify->idxRecipeTbl, m_byDiscountRate );
		m_vecAvatarRecipe.push_back( pItem );

		if( m_pThis->IsVisible() )
		{
			CreateRecipeFilterList();
			RecipeDispoisition();
		}
	}
	else if( msg.Id == g_EventHoipoiMixJobResetRes )
	{
		//SNtlEventHoipoiMixJobResetRes* pResult = reinterpret_cast<SNtlEventHoipoiMixJobResetRes*>( msg.pData );

		DestroyAvatarRecipeList();
		CreateAvatarRecipeList();
		
		CreateRecipeFilterList();
		RecipeDispoisition();
	}
}

VOID CHoipoiMixRecipe::OnAbsoluteMouseWheel( RwInt32 nFlag, RwInt16 sDelta, CPos& pos )
{
	RwInt32 nOffset = (RwInt32)((RwReal)m_pScbBar->GetMaxValue() * 0.1f) * sDelta;
	CAPTURE_MOUSEWHEELMOVE_SCROLLBAR( IsShow(), m_pThis, m_pThis, m_pScbBar, nOffset, pos );
}

VOID CHoipoiMixRecipe::OnScrollChanged( RwInt32 nNewOffset )
{
	// Offset �� �����̱� ������ Dialog�� ũ�⸸ŭ Offset�� �ش�.
	CRectangle rtPos = m_pListDialog->GetPosition();
	m_pListDialog->SetPosition( rtPos.left, -nNewOffset );
}

RwBool CHoipoiMixRecipe::CreateAvatarRecipeList()
{
	DestroyAvatarRecipeList();

	// Avatar�� �ִٸ� Avatar���� ����Ʈ�� ����� Avatar�� �����Ǳ� ���̶�� NtlSLGlobal���� ������ �޾ƿͼ� ����Ʈ�� �����.
	CNtlSobAvatar* pSobAvatar = GetNtlSLGlobal()->GetSobAvatar();

	RwUInt8 byCount = 0;
	if( pSobAvatar )
	{		
		CNtlSLHoipoiMix* pHoipoiMix = pSobAvatar->GetHoipoiMix();
		byCount = (RwUInt8)pHoipoiMix->GetRecipeCount();
		
		CNtlSLHoipoiMix::MAPDEF_RECIPEDATA* pMapRecipeData = pHoipoiMix->GetRecipeData();

		int nIndex = 0;
		for each( std::pair< RwUInt32, sRECIPE_DATA* > pairData in (*pMapRecipeData) )
		{
			CRecipeDlgItem* pRecipeItem = NTL_NEW CRecipeDlgItem();
			pRecipeItem->Create( nIndex, m_pHoipoiMix, pairData.second->recipeTblidx, m_byDiscountRate );

			m_vecAvatarRecipe.push_back( pRecipeItem );
		}
	}
	else
	{
		// �ƹ�Ÿ�� ���� �������� �ʾ����� NtlSLGlobal���� ������ �޾ƿ´�.
		SAvatarRecipeInfo* pRecipeInfo = GetNtlSLGlobal()->GetAvatarRecipeInfo();

		byCount = pRecipeInfo->byCount;

		for( int i=0; i < pRecipeInfo->byCount; ++i )
		{
			CRecipeDlgItem* pRecipeItem = NTL_NEW CRecipeDlgItem();
			pRecipeItem->Create( i, m_pHoipoiMix, pRecipeInfo->asRecipeData[i].recipeTblidx, m_byDiscountRate );

			m_vecAvatarRecipe.push_back( pRecipeItem );
		}
	}

	return TRUE;
}

VOID CHoipoiMixRecipe::DestroyAvatarRecipeList()
{
	for each( CRecipeDlgItem* pItem in m_vecAvatarRecipe )
	{
		if( m_pSelectDlgItem == pItem )
			m_pSelectDlgItem = NULL;

		pItem->Destroy();
		NTL_DELETE( pItem );
	}

	m_vecAvatarRecipe.clear();
}

RwBool CHoipoiMixRecipe::CreateBuiltInRecipeList(TBLIDX idxTblHoipoiMix)
{
	DestroyBuiltInRecipeList();
	
	CItemMixMachineTable* pMixMachineTable = API_GetTableContainer()->GetItemMixMachineTable();
	sITEM_MIX_MACHINE_TBLDAT* pItemMixMachineDat = (sITEM_MIX_MACHINE_TBLDAT*)pMixMachineTable->FindData( idxTblHoipoiMix );
	if( pItemMixMachineDat == NULL )
	{
		DBO_FAIL( "Item Mix-MachineTable data index is invalid." << idxTblHoipoiMix );
		return FALSE;
	}

	for( int i=0; i < dRECIPE_DLG_ITEM_BUILTIN_NUM; ++i )
	{
		if( pItemMixMachineDat->aBuiltInRecipeTblidx[i] != INVALID_TBLIDX )
		{
			CRecipeDlgItem* pItem = NTL_NEW CRecipeDlgItem();
			pItem->Create( i, m_pHoipoiMix, pItemMixMachineDat->aBuiltInRecipeTblidx[i], m_byDiscountRate );
			m_vecBuiltInRecipe.push_back( pItem );
		}
	}

	return TRUE;
}

VOID CHoipoiMixRecipe::DestroyBuiltInRecipeList()
{
	for each( CRecipeDlgItem* pItem in m_vecBuiltInRecipe )
	{
		if( m_pSelectDlgItem == pItem )
			m_pSelectDlgItem = NULL;

		pItem->Destroy();
		NTL_DELETE( pItem );
	}

	m_vecBuiltInRecipe.clear();
}

VOID CHoipoiMixRecipe::OnToggledFilter( gui::CComponent* pComponent, bool bToggled )
{
	if( bToggled )
	{
		for( int i=0; i < NUM_FILTER; ++i )
		{
			if ( m_pBtnFilter[i] == pComponent )
			{
				m_pBtnFilter[i]->ClickEnable( FALSE );
			}
			else
			{
				m_pBtnFilter[i]->ClickEnable( TRUE );
				m_pBtnFilter[i]->SetDown( false );
			}
		}
	}
	
	CreateRecipeFilterList();
	RecipeDispoisition();
}

VOID CHoipoiMixRecipe::CreateRecipeFilterList()
{
	m_vecShowListRecipe.clear();

	RwBool bSelectFilter	= m_pBtnFilter[FILTER_TOTAL]->IsDown();
	RwBool bSelectBuiltIn	= m_pBtnFilter[FILTER_BUILTIN]->IsDown();
	RwBool bSelectNormal	= m_pBtnFilter[FILTER_NORMAL]->IsDown();
	RwBool bSelectSpecial	= m_pBtnFilter[FILTER_SPECIAL]->IsDown();

	// Built-In List
	for each( CRecipeDlgItem* pItem in m_vecBuiltInRecipe )
	{
		if( bSelectBuiltIn || bSelectFilter )
			m_vecShowListRecipe.push_back( pItem );
	}

	// Normal List
	for each( CRecipeDlgItem* pItem in m_vecAvatarRecipe )
	{
		if( pItem->GetRecipeType() == ITEM_RECIPE_TYPE_FOOD_DRINK )
		{
			if( bSelectNormal || bSelectFilter )
				m_vecShowListRecipe.push_back( pItem );
		}		
	}

	// Special
	for each( CRecipeDlgItem* pItem in m_vecAvatarRecipe )
	{
		if( pItem->GetRecipeType() != ITEM_RECIPE_TYPE_FOOD_DRINK )
		{
			if( bSelectSpecial || bSelectFilter )
				m_vecShowListRecipe.push_back( pItem );
		}
	}
}

VOID CHoipoiMixRecipe::RecipeDispoisition()
{
	if( !m_pThis->IsVisible() )
		return;

	for each( CRecipeDlgItem* pItem in m_vecBuiltInRecipe )
	{
		pItem->Show( FALSE );
	}

	for each( CRecipeDlgItem* pItem in m_vecAvatarRecipe )
	{
		pItem->Show( FALSE );
	}

	// ũ�� ����
	RwInt32 nDlgHeight = ( (RwInt32)m_vecShowListRecipe.size() * (dRECIPE_DLG_ITEM_HEIGHT+dRECIPE_DLG_ITEM_HEIGHT_MARGIN) ) + dRECIPE_DLG_ITEM_OFFSET_TOP;
	m_pListDialog->SetHeight( nDlgHeight );
	
	m_pScbBar->SetRange(0, nDlgHeight - m_pClipDialog->GetHeight() );
	m_pScbBar->SetValue(0);

	m_pListDialog->SetClippingMode( TRUE );	

	// ItemDisposition
	int nIndex = 0;
	for each( CRecipeDlgItem* pItem in m_vecShowListRecipe )
	{
		pItem->RecipeItemDisposition( nIndex++ );
		pItem->Show( TRUE );
	}
}

VOID CHoipoiMixRecipe::SelectRecipeItem( CRecipeDlgItem* pSelectItem )
{
	if( m_pSelectDlgItem )
	{
		// ���� ���õǾ� �ִ� Item�̶� ������ Item�� ���ٸ� ���� ó������ �ʿ䰡 ����.
		if( m_pSelectDlgItem == pSelectItem )
			return;
		else
		{
			m_pSelectDlgItem->SelectItem( FALSE );
			m_pSelectDlgItem = pSelectItem;
			m_pSelectDlgItem->SelectItem( TRUE );
		}
	}
	else
	{
		m_pSelectDlgItem = pSelectItem;
		m_pSelectDlgItem->SelectItem( TRUE );
	}
}

VOID CHoipoiMixRecipe::DeSelectRecipeItem()
{
	m_pSelectDlgItem = NULL;
}

VOID CHoipoiMixRecipe::SelectFirstItem()
{
	RwInt32 nCount = 0;
	for each( CRecipeDlgItem* pItem in m_vecShowListRecipe )
	{
		if( nCount == 0 )
			m_pHoipoiMix->SelectRecipe( pItem );
	}
}