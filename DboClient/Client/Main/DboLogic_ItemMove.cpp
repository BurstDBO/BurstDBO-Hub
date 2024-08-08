/*****************************************************************************
* File			: DboLogic_String.h
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2007. 1. 12
* Abstract		: ������ �̵� ���� ������ ��Ƶд�
*****************************************************************************
* Desc         : 
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboLogic.h"


// shared
#include "NtlResultCode.h"
#include "ItemTable.h"
#include "ItemOptionTable.h"
#include "TextAllTable.h"
#include "TableContainer.h"

// core
#include "NtlDebug.h"

// sound
#include "GUISoundDefine.h"

// presention
#include "NtlPLGuiManager.h"

// simulation
#include "NtlSLDef.h"
#include "NtlSLLogic.h"
#include "NtlSLGlobal.h"
#include "NtlSLEventFunc.h"
#include "NtlSLPacketGenerator.h"
#include "NtlSobAvatar.h"
#include "NtlSobAvatarAttr.h"
#include "NtlSobManager.h"
#include "NtlSobItemAttr.h"
#include "NtlInventory.h"
#include "NtlSobItemIcon.h"
#include "NtlSobWorldItemAttr.h"
#include "NtlFSMStateBase.h"
#include "NtlSLLogic.h"
#include "NtlSLApi.h"

// dbo
#include "DialogManager.h"
#include "ChatGui.h"
#include "DboEventGenerator.h"
#include "DisplayStringManager.h"
#include "DboGlobal.h"
#include "IconMoveManager.h"
#include "WarehouseGui.h"
#include "TradeCart.h"

RwBool Logic_ItemMoveProc( SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace,
						   SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount/* = 1 */)
{
	RwUInt32 uiResult = DST_ITEM_CAN_NOT_MOVE_THERE;

	if( eSrcPlace == PLACE_EQUIP )
	{
		if( eDestPlace == PLACE_EQUIP )
			uiResult = Logic_ItemMoveSubProcEquipToEquip( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAGSLOT )
			uiResult = Logic_ItemMoveSubProcEquipToBagSlot( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcEquipToBagChild( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_SCOUTER_SLOT )
			uiResult = Logic_ItemMoveSubProcEquipToEquip( hSrcSerial, ucSrcSlotIdx, EQUIP_SLOT_TYPE_SCOUTER, uiStackCount );
		else if( eDestPlace == PLACE_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcEquipToWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx);
		else if( eDestPlace == PLACE_GUILD_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcEquipToGuildWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx );
	}
	else if( eSrcPlace == PLACE_BAGSLOT )
	{
		if( eDestPlace == PLACE_BAGSLOT )
			uiResult = Logic_ItemMoveSubProcBagSlotToBagSlot( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcBagSlotToBagChild( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcBagSlotToWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx);
		else if( eDestPlace == PLACE_GUILD_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcBagSlotToGuildWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx);
	}
	else if( eSrcPlace == PLACE_BAG )
	{
		if( eDestPlace == PLACE_EQUIP )
			uiResult = Logic_ItemMoveSubProcBagChildToEquip( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx, uiStackCount );		
		else if( eDestPlace == PLACE_BAGSLOT )
			uiResult = Logic_ItemMoveSubProcBagChildToBagSlot( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcBagChildToBagChild( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_SCOUTER )
			uiResult = Logic_ItemMoveSubProcBagChildToScouter( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx );
		else if( eDestPlace == PLACE_SCOUTER_SLOT )
			uiResult = Logic_ItemMoveSubProcBagChildToEquip( hSrcSerial, ucSrcSlotIdx, EQUIP_SLOT_TYPE_SCOUTER, uiStackCount );
		else if( eDestPlace == PLACE_PARTYCHARM )
			uiResult = Logic_ItemMoveSubProcBagChildToPartyCharmSlot( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx );
		else if( eDestPlace == PLACE_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcBagChildToWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx, uiStackCount);
		else if( eDestPlace == PLACE_GUILD_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcBagChildToGuildWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx, uiStackCount);		
	}
	else if( eSrcPlace == PLACE_SCOUTER )
	{
		if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcScouterToBagChild( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx );
		else if( eDestPlace == PLACE_SCOUTER )
			uiResult = Logic_ItemMoveSubProcScouterToScouter( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx );
		else if( eDestPlace == PLACE_SCOUTER_SLOT )
		{
			// peessi : �׳� ���� ���������� �ø���ó�� ó��.
			GetIconMoveManager()->IconMoveEnd();
			uiResult = INVALID_DWORD;
		}
		else if( eDestPlace == PLACE_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcScouterToWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx);
		else if( eDestPlace == PLACE_GUILD_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcScouterToGuildWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx);
	}
	else if( eSrcPlace == PLACE_SCOUTER_SLOT )
	{
		if( eDestPlace == PLACE_EQUIP )
			uiResult = Logic_ItemMoveSubProcEquipToEquip( hSrcSerial, EQUIP_SLOT_TYPE_SCOUTER, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAGSLOT )
			uiResult = Logic_ItemMoveSubProcEquipToBagSlot( hSrcSerial, EQUIP_SLOT_TYPE_SCOUTER, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcEquipToBagChild( hSrcSerial, EQUIP_SLOT_TYPE_SCOUTER, hDestParentSerial, ucDestSlotIdx, uiStackCount );		
		else if( eDestPlace == PLACE_SCOUTER_SLOT )
		{
			GetIconMoveManager()->IconMoveEnd();
			uiResult = INVALID_DWORD;
		}
		else if( eDestPlace == PLACE_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcEquipToWarehouse( hSrcSerial, EQUIP_SLOT_TYPE_SCOUTER, hDestParentSerial, ucDestSlotIdx );			
		else if( eDestPlace == PLACE_GUILD_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcEquipToGuildWarehouse( hSrcSerial, EQUIP_SLOT_TYPE_SCOUTER, hDestParentSerial, ucDestSlotIdx );		
	}
	else if( eSrcPlace == PLACE_QUESTBAG )
	{
		if( eDestPlace == PLACE_QUESTBAG )
			uiResult = Logic_ItemMoveSubProcQuestToQuest( ucSrcSlotIdx, ucDestSlotIdx );
	}
	else if( eSrcPlace == PLACE_WAREHOUSE )
	{
		if( eDestPlace == PLACE_EQUIP )
			uiResult = Logic_ItemMoveSubProcWarehouseToEquip( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx);
		else if( eDestPlace == PLACE_BAGSLOT )
			uiResult = Logic_ItemMoveSubProcWarehouseToBagSlot( hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx, uiStackCount );
		else if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcWarehouseToBagChild( hSrcSerial, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount);
		else if( eDestPlace == PLACE_SCOUTER )
			uiResult = Logic_ItemMoveSubProcWarehouseToScouter(hSrcSerial, ucSrcSlotIdx, ucDestSlotIdx);
		else if( eDestPlace == PLACE_SCOUTER_SLOT )
			uiResult = Logic_ItemMoveSubProcWarehouseToEquip( hSrcSerial, ucSrcSlotIdx, EQUIP_SLOT_TYPE_SCOUTER );
		else if( eDestPlace == PLACE_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcWarehouseToWarehouse( hSrcSerial, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount);
	}
	else if( eSrcPlace == PLACE_GUILD_WAREHOUSE )
	{
		if( eDestPlace == PLACE_EQUIP )
		uiResult = Logic_ItemMoveSubProcGuildWarehouseToEquip( hSrcSerial, eSrcPlace, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount);
		else if( eDestPlace == PLACE_BAGSLOT )
			uiResult = Logic_ItemMoveSubProcGuildWarehouseToBagSlot( hSrcSerial, eSrcPlace, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount);
		else if( eDestPlace == PLACE_BAG )
			uiResult = Logic_ItemMoveSubProcGuildWarehouseToBagChild( hSrcSerial, eSrcPlace, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount);
		else if( eDestPlace == PLACE_SCOUTER )
			uiResult = Logic_ItemMoveSubProcGuildWarehouseToScouter(hSrcSerial, eSrcPlace, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount);
		else if( eDestPlace == PLACE_SCOUTER_SLOT )
			uiResult = Logic_ItemMoveSubProcGuildWarehouseToEquip( hSrcSerial, eSrcPlace, ucSrcSlotIdx, PLACE_EQUIP, hDestParentSerial, EQUIP_SLOT_TYPE_SCOUTER, uiStackCount );
		else if( eDestPlace == PLACE_GUILD_WAREHOUSE )
			uiResult = Logic_ItemMoveSubProcGuildWarehouseToGuildWarehouse( hSrcSerial, ucSrcSlotIdx, hDestParentSerial, ucDestSlotIdx, uiStackCount);
	}
	// Zenny �̵� ���� ó��.
	else if( eSrcPlace == PLACE_SUB_BAG_ZENNY )
	{
		if( eDestPlace == PLACE_SUB_PARTYCHARM_ZENNY )
			uiResult = Logic_ItemMoveSubProcSubBagZennyToPartyCharmZenny( uiStackCount );		
		else if( eDestPlace == PLACE_SUB_WAREHOUSE_ZENNY )
			uiResult = Logic_ItemMoveSubProcSubBagZennyToWarehouseZenny( hDestParentSerial, uiStackCount );
		else if( eDestPlace == PLACE_SUB_GUILD_WAREHOUSE_ZENNY )
			uiResult = Logic_ItemMoveSubProcSubBagZennyToGuildWarehouseZenny( hDestParentSerial, uiStackCount );
		else if( eDestPlace == PLACE_SUB_TRADECART_ZENNY )
			uiResult = Logic_ItemMoveSubProcSubBagZennyToTradeCartZenny( hDestParentSerial, uiStackCount );
		else if( eDestPlace == PLACE_SUB_MAILSYSTEM_ZENNY )
			uiResult = Logic_ItemMoveSubProcSubBagZennyToMailSystemZenny( uiStackCount );
		else if( eDestPlace == PLACE_SUB_PARTYINVEN_ZENNY )
			uiResult = Logic_ItemMoveSubProcSubBagZennyPartyInvenZenny( ucDestSlotIdx, uiStackCount );
	}
	else if( eSrcPlace == PLACE_SUB_PARTYCHARM_ZENNY )
	{
		if( eDestPlace == PLACE_SUB_BAG_ZENNY )
			uiResult = Logic_ItemMoveSubProcPartyCharmZennyToSubBagZenny( uiStackCount );
	}
	else if( eSrcPlace == PLACE_SUB_WAREHOUSE_ZENNY )
	{
		if( eDestPlace == PLACE_SUB_BAG_ZENNY )
			uiResult = Logic_ItemMoveSubProcWareHouseZennyToSubBagZenny( uiStackCount );
	}
	else if( eSrcPlace == PLACE_SUB_GUILD_WAREHOUSE_ZENNY )
	{
		if( eDestPlace == PLACE_SUB_BAG_ZENNY )
			uiResult = Logic_ItemMoveSubProcGuildWareHouseZennyToSubBagZenny( uiStackCount );
	}
	else if( eSrcPlace == PLACE_SUB_TRADECART_ZENNY )
	{
		if( eDestPlace == PLACE_SUB_BAG_ZENNY )
			uiResult = Logic_ItemMoveSubProcTradeCartZennyToSubBagZenny( uiStackCount );
	}
	else if( eSrcPlace == PLACE_SUB_MAILSYSTEM_ZENNY )
	{
		if( eDestPlace == PLACE_SUB_BAG_ZENNY )
			uiResult = Logic_ItemMoveSubProcMailSystemZennyToSubBagZenny( uiStackCount );
	}
	
	if( uiResult == INVALID_DWORD )
		return TRUE;
	else
	{
		GetAlarmManager()->AlarmMessage( uiResult );
		return FALSE;
		//GetAlarmManager()->AlarmMessage(DST_ITEM_CAN_NOT_MOVE_THERE);
	}	
}

RwUInt32 Logic_ItemMoveSubProcEquipToEquip( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcEquipToEquip" );
	// �� ���� 
	// 1. ���� �����ΰ�� ��� 
	if( ucSrcSlotIdx == ucDestSlotIdx )
	{
		GetIconMoveManager()->IconMoveEnd();
		NTL_RETURN( INVALID_DWORD );
	}

	// 2. Pair(����,�Ͱ���)������ �̵��� ����
	RwInt16 usSrcSlotFlag, usDestSlotFlag;
	usSrcSlotFlag = Logic_ConvertEquipSlotIdxToFlag( ucSrcSlotIdx );
	usDestSlotFlag= Logic_ConvertEquipSlotIdxToFlag( ucDestSlotIdx );
	if( !Logic_EquipSlotTypeFlagCheck( usSrcSlotFlag, usDestSlotFlag ) )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );

	RwUInt8 srcType, destType;
	srcType = (RwUInt8)Logic_ConvertEquipSlotIdxToType( ucSrcSlotIdx );
	destType = (RwUInt8)Logic_ConvertEquipSlotIdxToType( ucDestSlotIdx );

	// 3. ���� ���Ⱓ üũ.
	SERIAL_HANDLE hDestSerial = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( ucDestSlotIdx );

	if( hSrcSerial != INVALID_SERIAL_ID )
	{
		CNtlSobItemAttr* pSrcItemAttr = Logic_GetItemSobAttrFromSobSerial( hSrcSerial );
		DBO_ASSERT( pSrcItemAttr, "Logic_ItemMoveSubProcEquipToEquip : Src Object is NULL" );

		if( pSrcItemAttr->IsExpired() )
			NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );		
	}	

	if( hDestSerial != INVALID_SERIAL_ID )
	{
		CNtlSobItemAttr* pDestItemAttr = Logic_GetItemSobAttrFromSobSerial( hDestSerial );
		DBO_ASSERT( pDestItemAttr, "Logic_ItemMoveSubProcEquipToEquip : Dest Object is NULL" );

		if( pDestItemAttr->IsExpired() )
			NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );
	}
	
	if( Logic_IsStackMovable( hSrcSerial, hDestSerial, uiStackCount ) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemStackMoveReq( CONTAINER_TYPE_EQUIP, srcType, CONTAINER_TYPE_EQUIP, destType, (RwUInt8)uiStackCount ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( CONTAINER_TYPE_EQUIP, srcType, CONTAINER_TYPE_EQUIP, destType ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

RwUInt32 Logic_ItemMoveSubProcEquipToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcEquipToBag" );

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	SERIAL_HANDLE hDestBagItem = pInventory->GetBagItem( ucDestSlotIdx ); 

	// �� ���� 
	// 1. ��ī������ ��� ���������, ������ �����ߴ����� ��.
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	if( pSrcItem->IsScouterItem() )
	{
		if( Logic_IsUsingScouter() )
			NTL_RETURN( DST_SCOUTER_WORKING );

		if( Logic_IsScouterHasParts() )
			NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
	}

	// 2. DestSlot�� ��������� ���
	if( hDestBagItem == INVALID_SERIAL_ID )
	{
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_NOT_BAG );
	}

	CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestBagItem ) ); 
	// 3. ������ �Ⱓ������ ����Ǿ����� ���
	CNtlSobItemAttr* pDestBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestBagItem->GetSobAttr() );
	if( pDestBagItemAttr->IsExpired() )
	{
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );
	}

	// 4. ������ �����ϳ� ��ĭ�� ������ ���.
	if( pDestBagItem->FullChild() )
	{
		NTL_RETURN( DST_ITEM_BAG_FULL );
	}		

	RwInt32 nEmptyBagChildSlot = pDestBagItem->FindEmptyChildSlot();

	NTL_RETURN( Logic_ItemMoveSubProcEquipToBagChild( hSrcSerial, ucSrcSlotIdx, hDestBagItem, (RwInt8)nEmptyBagChildSlot, uiStackCount ) );
}

RwUInt32 Logic_ItemMoveSubProcEquipToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcEquipToBagChild" );

	//CNtlSobAvatar *pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	//CNtlFSMStateBase *pStateBase = pAvatar->GetCurrentState();
	//RwUInt32 uiStateId = pStateBase->GetStateId();
	//if(uiStateId == NTL_FSMSID_SCOUTER)
	//{
	//	// ��ī���͸� ������Դϴ�
	//	NTL_RETURN( DST_SCOUTER_WORKING );
	//}

	// �� ���� 
	// 1. ��ī������ ��� ���������, ������ �����ߴ����� ��.
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	if( pSrcItem->IsScouterItem() )
	{
		if( Logic_IsUsingScouter() )
			NTL_RETURN( DST_SCOUTER_WORKING );

		if( Logic_IsScouterHasParts() )
			NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
	}

	// 2. ��â���� ��� üũ.
	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	RwInt32 nBagSlotIdx = pInventory->FindBagSlot( hDestParentSerial );
	DBO_ASSERT( ( nBagSlotIdx >= 0 ), "Bag is not found in BagSlot" );	

	if( !Logic_ItemMoveToNetStoreCheck( nBagSlotIdx ) )
	{
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NETPYSTORE );
	}

	// 3. ������ ���Ⱓ�� ����Ǿ����� ���
	CNtlSobItem* pBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestParentSerial ) );
	DBO_ASSERT( pBagItem, "Invalid DestBagItem" );
	CNtlSobItemAttr* pBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pBagItem->GetSobAttr() );
	DBO_ASSERT( pBagItemAttr, "Invalid DestBagItemAttr" );
	if( pBagItemAttr->IsExpired() )
	{
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );
	}	

	// 4. DestSlot�� ������� �ʴٸ� Equip���� �ű�� �ִ� ���������� Ȯ��
	if( pBagItem->IsValidChild( ucDestSlotIdx ) )
	{
		CNtlSobItem* pDestItem = pBagItem->GetChildItem( ucDestSlotIdx );
		DBO_ASSERT( pDestItem, "Inccorect ucDestSlotIdx" );
		CNtlSobItemAttr* pDestItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestItem->GetSobAttr() );
		DBO_ASSERT( pDestItemAttr, "Inccorect GetSobAttr" );

		// peessi : ����� �� ���ٸ� �޽����� ������ �����ִ� ������.
		if( !pDestItem->IsEquipItem() )
			NTL_RETURN( DST_ITEM_BAG_FULL );

		sITEM_TBLDAT* pDestItemTable = pDestItemAttr->GetItemTbl();
		DBO_ASSERT( pDestItemTable, "Equip ItemAttr has no ItemTable" );

		RwUInt16 usSrcSlotFlag = Logic_ConvertEquipSlotIdxToFlag( ucSrcSlotIdx );

		if( !Logic_EquipSlotTypeFlagCheck( usSrcSlotFlag, pDestItemTable->wEquip_Slot_Type_Bit_Flag ) )
			NTL_RETURN( DST_ITEM_BAG_FULL );
	}	

	eCONTAINER_TYPE eBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)nBagSlotIdx );
	eEQUIP_SLOT_TYPE srcType = Logic_ConvertEquipSlotIdxToType( ucSrcSlotIdx );

	SERIAL_HANDLE hDestSerial = pBagItem->GetChildSerial( ucDestSlotIdx );

	if( Logic_IsStackMovable( hSrcSerial, hDestSerial, uiStackCount ) )
	{ 
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemStackMoveReq(CONTAINER_TYPE_EQUIP, (RwUInt8)srcType, (RwUInt8)eBagType, ucDestSlotIdx, (RwUInt8)uiStackCount ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq((RwUInt8)CONTAINER_TYPE_EQUIP, (RwUInt8)srcType, (RwUInt8)eBagType, ucDestSlotIdx ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

RwUInt32 Logic_ItemMoveSubProcEquipToWarehouse(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcEquipToWarehouse" );

	// 1. ��ī������ ��� ���������, ������ �����ߴ����� ��.
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	if( pSrcItem->IsScouterItem() )
	{
		if( Logic_IsUsingScouter() )
			NTL_RETURN( DST_SCOUTER_WORKING );

		if( Logic_IsScouterHasParts() )
			NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
	}

	// src
	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
	CNtlSobItemAttr* pItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	DBO_ASSERT( pItemAttr, "Invalid Src ItemAttr" );

	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();
	SERIAL_HANDLE hCommonWarehouse = pWarehouse->GetSlotSerailID(NTL_COMMON_WAREHOUSE);
	if( hDestParentSerial == hCommonWarehouse &&
		Logic_IsCanSaveCommonWarehouse( pItemAttr ) == FALSE )
	{
		// ���� â�� ������ �� ���� ������		
		NTL_RETURN( DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE );
	}

	// dest	
	eCONTAINER_TYPE eDestContainerType = Logic_ConverWarehouseIdxToContainderType(pWarehouse->FindWarehouseSlot(hDestParentSerial));

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, CONTAINER_TYPE_EQUIP, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcEquipToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcEquipToGuildWarehouse" );

	// 1. ��ī������ ��� ���������, ������ �����ߴ����� ��.
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	if( pSrcItem->IsScouterItem() )
	{
		if( Logic_IsUsingScouter() )
			NTL_RETURN( DST_SCOUTER_WORKING );

		if( Logic_IsScouterHasParts() )
			NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
	}

	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
	CNtlSobItemAttr* pItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	DBO_ASSERT( pItemAttr, "Invalid Src ItemAttr" );

	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();

	// hDestParentSerial : �ڵ��� �ƴ϶� ��� â���� �ε����� �޾Ҵ� 
	eCONTAINER_TYPE eDestContainerType = Logic_ConverGuildWarehouseIdxToContainderType((RwUInt8)hDestParentSerial);

	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
		CONTAINER_TYPE_EQUIP, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagSlotToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagToBag" );
	// �� ���� 
	// 1. ���� �ڸ��̸� ���
	if( ucSrcSlotIdx == ucDestSlotIdx )
	{
		GetIconMoveManager()->IconMoveEnd();
		NTL_RETURN( INVALID_DWORD );
	}

	// 2. �ű���� ������ �⺻�����̸� ���, �������� �⺻�����̸� ���.
	if( ucSrcSlotIdx == 0 || ucDestSlotIdx == 0 )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BASICBAG );

	CNtlSobItem* pSrcBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcBagItem, "Invalid SrcSerial" );
	CNtlSobItemAttr* pSrcBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcBagItem->GetSobAttr() );
	DBO_ASSERT( pSrcBagItemAttr, "Invalid SrcSerialAttr" );

	// 3. �ű���� ������ ���Ⱓ�� ����Ǿ����� ���.
	if( pSrcBagItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );

	// 4. �ű���� ������ ������ ������� ������ ���.
	if( !pSrcBagItem->EmptyChild() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EMPTY_BAG );	

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	SERIAL_HANDLE hDestBagSerial = pInventory->GetBagItem( ucDestSlotIdx );

	if( hDestBagSerial != INVALID_SERIAL_ID )
	{
		CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestBagSerial ) );
		DBO_ASSERT( pDestBagItem, "Invalid DestBag" );
		CNtlSobItemAttr* pDestBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestBagItem->GetSobAttr() );
		DBO_ASSERT( pDestBagItemAttr, "Invalid DestBagAttr" );

		// 5. �������� ������ ���Ⱓ�� ����Ǿ����� ���.
		if( pDestBagItemAttr->IsExpired() )
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );		

		// 6. �������� ������ ���Ⱓ�� ����Ǿ����� ���.
		if( pDestBagItem->FullChild() )
			NTL_RETURN( DST_ITEM_BAG_FULL );
	}

	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( CONTAINER_TYPE_BAGSLOT, ucSrcSlotIdx, CONTAINER_TYPE_BAGSLOT, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagSlotToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagToBagChild" );
	// �� ���� 
	// 1. �ű���� ������ �⺻�����̸� ���
	if( ucSrcSlotIdx == 0 )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BASICBAG );

	CNtlSobItem* pSrcBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT( pSrcBagItem, "Invalid SrcSerial" );

	// 2. �ű���� ������ ������� �ʴٸ� ���
	if( !pSrcBagItem->EmptyChild() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EMPTY_BAG );

	// 3. �ڱ� �ڽ����� �ű���� ���
	if( hDestParentSerial == hSrcSerial )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_THERE );

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	RwInt32 nBagSlotIdx = pInventory->FindBagSlot( hDestParentSerial );
	DBO_ASSERT( ( nBagSlotIdx >= 0 ), "Bag is not found in BagSlot" );

	// 4. ��â���� ��� üũ.
	if( !Logic_ItemMoveToNetStoreCheck( nBagSlotIdx ) )
	{
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NETPYSTORE );
	}

	CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestParentSerial ) );
	NTL_ASSERT( pDestBagItem, "Invalid DestParentSerial" );
	CNtlSobItemAttr* pDestBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestBagItem->GetSobAttr() );
	DBO_ASSERT( pDestBagItemAttr, "Invalid DestBag ItemAttr" );

	// 5. �ű���� ������ ���Ⱓ�� ����Ǿ��ٸ� ���.
	if( pDestBagItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );	

	// 6. DestSlot�� ������� �������, �װ��� �������� ������ �ƴ϶�� ���.
	if( pDestBagItem->IsValidChild( ucDestSlotIdx ) )
	{
		CNtlSobItem* pDestItem = reinterpret_cast<CNtlSobItem*>( pDestBagItem->GetChildItem( ucDestSlotIdx ) );
		DBO_ASSERT( pDestItem, "Must be valid DestItem" );

		if( !pDestItem->IsBagItem() )
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_NOT_BAG );
	}	

	eCONTAINER_TYPE eDestBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)pInventory->FindBagSlot( hDestParentSerial ) );
	NTL_ASSERT( eDestBagType != CONTAINER_TYPE_NONE, "Invalid DestSlot Index" );

	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( CONTAINER_TYPE_BAGSLOT, ucSrcSlotIdx, (RwUInt8)eDestBagType, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagSlotToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagSlotToWarehouse" );

	// src
	CNtlSobItem* pSrcBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcBagItem, "Invalid SrcSerial" );

	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
	CNtlSobItemAttr* pItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcBagItem->GetSobAttr() );
	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();
	SERIAL_HANDLE hCommonWarehouse = pWarehouse->GetSlotSerailID(NTL_COMMON_WAREHOUSE);
	if( hDestParentSerial == hCommonWarehouse &&
		Logic_IsCanSaveCommonWarehouse( pItemAttr ) == FALSE )
	{
		// ���� â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE );
	}	

	// ������ ������� ������ ���.
	if( !pSrcBagItem->EmptyChild() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EMPTY_BAG );

	// dest
	eCONTAINER_TYPE eDestContainerType = Logic_ConverWarehouseIdxToContainderType(pWarehouse->FindWarehouseSlot(hDestParentSerial));

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, CONTAINER_TYPE_BAGSLOT, ucSrcSlotIdx,
		(RwUInt8)eDestContainerType, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagSlotToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagSlotToGuildWarehouse" );
	
	// src
	CNtlSobItem* pSrcBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcBagItem, "Invalid SrcSerial" );

	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
	
	CNtlSobItemAttr* pItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcBagItem->GetSobAttr() );
	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	// ������ ������� ������ ���.
	if( !pSrcBagItem->EmptyChild() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EMPTY_BAG );

	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();

	// hDestParentSerial : �ڵ��� �ƴ϶� ��� â���� �ε����� �޾Ҵ� 
	eCONTAINER_TYPE eDestContainerType = Logic_ConverGuildWarehouseIdxToContainderType((RwUInt8)hDestParentSerial);

	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
		CONTAINER_TYPE_BAGSLOT, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagChildToEquip( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToEquip" );
	// �� ���� 
	// 1. DestSlot���� ���� �ִ� �������ΰ� Ȯ��
	// 2. DestSlot�� ������� �ʴٸ� ��ȯ
	// 3. ���Ⱓ�� ����Ǿ� �ִ� �������̸� Equip�Ұ�. 
	// 4. DestItem �� ��ī���� �϶�, ��ī������ ������ Ȯ�� �� üũ.
	// peessi ��������� �۾���. �ϴ��� ������ �ñ��, ���н� �޽����� ���� �ٽ��ѹ� ����غ���. ���� �������� ������ �ñ�� ����.
	
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT( pSrcItem, "Invalid hSrcSerial" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	NTL_ASSERT( pSrcItemAttr, "Have No Attr" );

	// 1. ���Ⱓ�� ����Ǿ� �ִ� �������̸� Equip�Ұ�. 
	if( pSrcItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );

	sITEM_TBLDAT* pSrcItemTable = pSrcItemAttr->GetItemTbl();
	NTL_ASSERT( pSrcItemTable, "Have No Table" );

	RwUInt16 usDestSlotFlag = Logic_ConvertEquipSlotIdxToFlag( ucDestSlotIdx );
	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)pSrcItem->GetParentItemSlotIdx() );
	SERIAL_HANDLE hDestSerial = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( ucDestSlotIdx );

	// 2. Dest�� ��ī�����̰� �̹� ��ī���͸� �������� ���, 3,4�� ���� Ȯ��.
	if( ucDestSlotIdx == EQUIP_SLOT_TYPE_SCOUTER && hDestSerial != INVALID_SERIAL_ID )
	{
		CNtlSobItem* pDestItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestSerial ) );
		DBO_ASSERT( pDestItem, "Invalid DestItem" );

		if( pSrcItem->IsScouterItem() )
		{
			// 3. ��ī���Ͷ�� ��������� ���� Ȯ��.
			if( Logic_IsUsingScouter() )
				NTL_RETURN( DST_SCOUTER_WORKING );

			if( Logic_IsScouterHasParts() )
				NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
		}		
		else if( pSrcItem->IsScouterPartItem() )
		{
			// 4. ��ī���� ������� ��ī���ͼ����������. 
			RwInt32 nDestScouterIdx = pDestItem->FindEmptyChildSlot();
			if( nDestScouterIdx >= 0 )
				NTL_RETURN( Logic_ItemMoveSubProcBagChildToScouter( hSrcSerial, ucSrcSlotIdx, (RwUInt8)nDestScouterIdx ) );			

			NTL_RETURN( DST_SCOUTER_FULL );
		}
		else
		{
			if( !Logic_EquipSlotTypeFlagCheck( usDestSlotFlag, pSrcItemTable->wEquip_Slot_Type_Bit_Flag ) )
				NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
		}
	}
	else
	{
		// 5. ������ ����Ÿ�� �˻�.
		if( !Logic_EquipSlotTypeFlagCheck( usDestSlotFlag, pSrcItemTable->wEquip_Slot_Type_Bit_Flag ) )
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
	}

	if( Logic_IsStackMovable( hSrcSerial, hDestSerial, uiStackCount ) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemStackMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, CONTAINER_TYPE_EQUIP, ucDestSlotIdx, (RwUInt8)uiStackCount ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, CONTAINER_TYPE_EQUIP, ucDestSlotIdx ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

RwUInt32 Logic_ItemMoveSubProcBagChildToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToBag" );
	
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT( pSrcItem, "Invalid hSrcSerial" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	NTL_ASSERT( pSrcItemAttr, "Have No Attr" );

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	SERIAL_HANDLE hDestBagSerial = pInventory->GetBagItem( ucDestSlotIdx );
	RwInt32 nEmptyBagChildSlot = -1;

	// 1. DestSlot�� ������ �������� ������ üũ. 
	if( hDestBagSerial == INVALID_SERIAL_ID )
	{
		// 2. src�������� �����̶��.
		if( pSrcItem->IsBagItem() )
		{
			// 3. src ������ ���Ⱓ üũ.
			if( pSrcItemAttr->IsExpired() )
				NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );

			eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)( pSrcItem->GetParentItemSlotIdx() ) );

			if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, CONTAINER_TYPE_BAGSLOT, ucDestSlotIdx ) )
				NTL_RETURN( INVALID_DWORD )	
			else
				NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
		}
		else
		{
			// 4. ������ �ƴϰ�, dest�� ���浵 ���ٸ� ���.
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_NOT_BAG );
		}
	}
	else
	{
		SERIAL_HANDLE hSrcBagSerial = pSrcItem->GetParentItemSerial();

		// 5. src�� �����, dest������ ���� ���϶�. ���� ������ �����Ѱ�ó��.
		if( hSrcBagSerial == hDestBagSerial )
			NTL_RETURN( INVALID_DWORD );

		CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestBagSerial ) );
		NTL_ASSERT( pDestBagItem, "Invalid hDestBagSerial" );

		// 6. dest�� ������ �� á���� ���.
		if( pDestBagItem->FullChild() )
			NTL_RETURN( DST_ITEM_BAG_FULL );

		nEmptyBagChildSlot = pDestBagItem->FindEmptyChildSlot();

		// 7. �� ���� BagChildToBagChild�����������. 
		NTL_RETURN( Logic_ItemMoveSubProcBagChildToBagChild( hSrcSerial, ucSrcSlotIdx, hDestBagSerial, (RwUInt8)nEmptyBagChildSlot, uiStackCount ) );	
	}	
}

RwUInt32 Logic_ItemMoveSubProcBagChildToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToBagChild" );
	
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT( pSrcItem, "Invalid hSrcSerial" );
	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();

	RwUInt8 ucSrcBagIdx = (RwUInt8)pSrcItem->GetParentItemSlotIdx();
	RwUInt8 ucDestBagIdx= (RwUInt8)pInventory->FindBagSlot( hDestParentSerial );

	// 1. ���� ����, ���� �ڸ��� ��� ���	
	if( ucSrcBagIdx == ucDestBagIdx && ucSrcSlotIdx == ucDestSlotIdx )
	{
		GetIconMoveManager()->IconMoveEnd();
		NTL_RETURN( INVALID_DWORD );
	}		

	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( ucSrcBagIdx );
	eCONTAINER_TYPE eDestBagType= Logic_ConvertBagIdxToContainerType( ucDestBagIdx );

	CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestParentSerial ) );
	DBO_ASSERT( pDestBagItem, "Invalid DestBagItem" );
	CNtlSobItemAttr* pDestBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestBagItem->GetSobAttr() );
	DBO_ASSERT( pDestBagItemAttr, "Invalid DestBagItemAttr" );
	SERIAL_HANDLE hDestSerial = pDestBagItem->GetChildSerial( ucDestSlotIdx );

	// 2. dest ������ ��â���ΰ�� �˻�
	if( !Logic_ItemMoveToNetStoreCheck( ucDestBagIdx ) )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NETPYSTORE );

	// 3. dest ������ ���Ⱓ �˻�
	if( pDestBagItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );

	if( Logic_IsStackMovable( hSrcSerial, hDestSerial, uiStackCount ) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemStackMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, (RwUInt8)eDestBagType, ucDestSlotIdx, (RwUInt8)uiStackCount ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, (RwUInt8)eDestBagType, ucDestSlotIdx ) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

//RwUInt32 Logic_ItemMoveSubProcBagChildToScouterSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx)
//{
//	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToScouterSlot" );
//	// ������
//	// 0. ���Ⱓ üũ
//	// 1. ��ī���� �ٵ� �̵� �����ϴ�. 
//	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
//	DBO_ASSERT( pSrcItem, "Invalid SrcItem" );
//	CNtlSobItemAttr* pSrcItemAttr =reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
//	DBO_ASSERT( pSrcItemAttr, "Invalid SrcItemAttr" );
//
//	if( Logic_IsUsingScouter() )
//		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );
//
//	if( Logic_IsScouterHasParts() )
//		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_SCOUTER_HAS_PARTS );
//
//	if( pSrcItemAttr->IsExpired() )
//		NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );
//
//	if( !pSrcItem->IsScouterItem() )
//		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
//	
//	// �̵�		
//	RwUInt8 ucSrcBagIdx = (RwUInt8)pSrcItem->GetParentItemSlotIdx();
//	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( ucSrcBagIdx );
//
//	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, CONTAINER_TYPE_EQUIP, EQUIP_SLOT_TYPE_SCOUTER ) )
//		NTL_RETURN( INVALID_DWORD );
//	else
//		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND );
//}

RwUInt32 Logic_ItemMoveSubProcBagChildToPartyCharmSlot(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToPartyCharmSlot" );

	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	DBO_ASSERT( pSrcItemAttr, "Invalid Src ItemAttr" );

    RwUInt8 ucSrcBagIdx = (RwUInt8)pSrcItem->GetParentItemSlotIdx();
	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( ucSrcBagIdx );

	// 1. src�������� ���Ⱓ üũ. 
	if( pSrcItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );

	if( GetDboGlobal()->GetGamePacketGenerator()->SendPartyRegVictimItem((RwUInt8)eSrcBagType, ucSrcSlotIdx, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagChildToScouter( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToScouter" );

	// 1. ��ī���� ���� Ȯ��.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );

	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	DBO_ASSERT( pSrcItemAttr, "Invalid src ItemAttr" );

	// 2. ���Ⱓ üũ
	if( pSrcItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );

	// 3. ��ī���� ������ �̵� �����ϴ�. 
	if( !pSrcItem->IsScouterPartItem() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_SCOUTER_NOT_SCOUTERPARTS );	

	RwUInt32 hDestScouter = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( EQUIP_SLOT_TYPE_SCOUTER );
	CNtlSobItem* pDestScouter = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestScouter ) );
	DBO_ASSERT( pDestScouter, "INvalid Scouter. Critical Error" );
	CNtlSobItemAttr* pDestScouterAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestScouter->GetSobAttr() );

	// 4. ��ī���� ���Ⱓ üũ.
	if( pDestScouterAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_SCOUTER_EXPIRED_DURATION );

	// �̵�	
	RwUInt8 ucSrcBagIdx = (RwUInt8)pSrcItem->GetParentItemSlotIdx();
	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( ucSrcBagIdx );

	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( (RwUInt8)eSrcBagType, ucSrcSlotIdx, CONTAINER_TYPE_SCOUT, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcBagChildToWarehouse(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToWarehouse" );

	// src
	CNtlSobItem* pItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT(pItem, "Logic_ItemMoveSubProcBagChildToWarehouse, Not exist item : " << hSrcSerial);
	CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pItem->GetSobAttr());
	NTL_ASSERT(pSobItemAttr, "Logic_ItemMoveSubProcBagChildToWarehouse, Not exist item attr : " << hSrcSerial);	

	if( Logic_IsCanSaveWarehouse( pSobItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();
	SERIAL_HANDLE hCommonWarehouse = pWarehouse->GetSlotSerailID(NTL_COMMON_WAREHOUSE);
	if( hDestParentSerial == hCommonWarehouse && 
		Logic_IsCanSaveCommonWarehouse( pSobItemAttr ) == FALSE )
	{
		// ���� â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE );
	}

	RwUInt8 ucBagIdx = (RwUInt8)pItem->GetParentItemSlotIdx();
	NTL_ASSERT( ( ucBagIdx >= 0 ), "Bag is not found in BagSlot" );

	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)ucBagIdx );

	// dest
	eCONTAINER_TYPE eDestContainerType = Logic_ConverWarehouseIdxToContainderType(pWarehouse->FindWarehouseSlot(hDestParentSerial));

	// â�� NPC serial	
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	// for Logic_IsStackMovable
	CNtlSobItem* pDestParentItem = reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(hDestParentSerial));

	if( Logic_IsStackMovable(hSrcSerial, pDestParentItem->GetChildSerial(ucDestSlotIdx), uiStackCount) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMoveStack(hNPCHandle, (RwUInt8)eSrcBagType, ucSrcSlotIdx,
			(RwUInt8)eDestContainerType, ucDestSlotIdx, (RwUInt8)uiStackCount) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else 
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, (RwUInt8)eSrcBagType, ucSrcSlotIdx,
			(RwUInt8)eDestContainerType, ucDestSlotIdx) )
			NTL_RETURN( INVALID_DWORD )		
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

RwUInt32 Logic_ItemMoveSubProcBagChildToGuildWarehouse(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcBagChildToGuildWarehouse" );

	// src
	CNtlSobItem* pItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT(pItem, "Logic_ItemMoveSubProcBagChildToGuildWarehouse, Not exist item : " << hSrcSerial);
	CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pItem->GetSobAttr());
	NTL_ASSERT(pSobItemAttr, "Logic_ItemMoveSubProcBagChildToGuildWarehouse, Not exist item attr : " << hSrcSerial);	

	if( Logic_IsCanSaveWarehouse( pSobItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	RwUInt8 ucBagIdx = (RwUInt8)pItem->GetParentItemSlotIdx();
	NTL_ASSERT( ( ucBagIdx >= 0 ), "Bag is not found in BagSlot" );

	eCONTAINER_TYPE eSrcBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)ucBagIdx );

	// Dest
	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
	// hDestParentSerial : �ڵ��� �ƴ϶� ��� â���� �ε����� �޾Ҵ� 
	eCONTAINER_TYPE eDestContainerType = Logic_ConverGuildWarehouseIdxToContainderType((RwUInt8)hDestParentSerial);
	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem((RwUInt8)hDestParentSerial, ucDestSlotIdx);

	if( Logic_IsStackMovable_to_GuildWarehouse(pGuildWarehouseItem, hSrcSerial, uiStackCount) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveStackReq(pGuildWarehouse->GetNPCHandle(),
			(RwUInt8)eSrcBagType, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx, (RwUInt8)uiStackCount) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
			(RwUInt8)eSrcBagType, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

RwUInt32 Logic_ItemMoveSubProcScouterToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterToBagChild" );
	// ������
	
	// 1. ��ī���� ����߿��� ���.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	RwInt32 nDestBagSlotIdx = pInventory->FindBagSlot( hDestParentSerial );
	NTL_ASSERT( ( nDestBagSlotIdx >= 0 ), "DestBag is not found in BagSlot" );	
	
	// 2. Dest ������ ��â���ΰ�� �˻�
	if( !Logic_ItemMoveToNetStoreCheck( (RwUInt32)nDestBagSlotIdx ) )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NETPYSTORE );
	
	// 3. DestItem�� �����ϴ� ��� 
	CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestParentSerial ) );
	DBO_ASSERT( pDestBagItem, "Invalid Dest BagItem" );
	if( pDestBagItem->IsValidChild( ucDestSlotIdx ) )
	{
		CNtlSobItem* pDestItem = pDestBagItem->GetChildItem( ucDestSlotIdx );
		DBO_ASSERT( pDestItem, "Inavlid DestItem" );
		CNtlSobItemAttr* pDestItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestItem->GetSobAttr() );
		DBO_ASSERT( pDestItemAttr, "Invalid DestItemAttr" );

		// 4. ���Ⱓ
		if( pDestItemAttr->IsExpired() )
			NTL_RETURN( DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION );
		
		// 5. ��ī�����������߸� �Ѵ�.
		if( !pDestItem->IsScouterPartItem() )
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_SCOUTER_NOT_SCOUTERPARTS );
	}	

	eCONTAINER_TYPE eDestBagType = Logic_ConvertBagIdxToContainerType( (RwUInt8)nDestBagSlotIdx );

	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( CONTAINER_TYPE_SCOUT, ucSrcSlotIdx, (RwUInt8)eDestBagType, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcScouterToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterToWarehouse" );

	// 1. ��ī���� ����߿��� ���.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );	

	// src
	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
	CNtlSobItemAttr* pItemAttr = Logic_GetItemSobAttrFromSobSerial( hSrcSerial );
	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������		
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();
	SERIAL_HANDLE hCommonWarehouse = pWarehouse->GetSlotSerailID(NTL_COMMON_WAREHOUSE);
	if( hDestParentSerial == hCommonWarehouse && 
		Logic_IsCanSaveCommonWarehouse( pItemAttr ) == FALSE )
	{
		// ���� â�� ������ �� ���� ������		
		NTL_RETURN( DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE );
	}

	// dest
	eCONTAINER_TYPE eDestContainerType = Logic_ConverWarehouseIdxToContainderType(pWarehouse->FindWarehouseSlot(hDestParentSerial));

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, CONTAINER_TYPE_SCOUT, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcScouterToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterToGuildWarehouse" );

	// 1. ��ī���� ����߿��� ���.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );	

	// src
	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
	CNtlSobItemAttr* pItemAttr = Logic_GetItemSobAttrFromSobSerial( hSrcSerial );
	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������		
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	// Dest
	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();

	// hDestParentSerial : �ڵ��� �ƴ϶� ��� â���� �ε����� �޾Ҵ� 
	eCONTAINER_TYPE eDestContainerType = Logic_ConverGuildWarehouseIdxToContainderType((RwUInt8)hDestParentSerial);

	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(), CONTAINER_TYPE_SCOUT, ucSrcSlotIdx, (RwUInt8)eDestContainerType, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else 
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcScouterToScouter( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterToScouter" );

	// 1. ��ī���� ����߿��� ���.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );	

	// ������
	// 2. �����ڸ��� ����.
	if( ucSrcSlotIdx == ucDestSlotIdx )
	{
		GetIconMoveManager()->IconMoveEnd();
		NTL_RETURN( INVALID_DWORD );
	}

	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( CONTAINER_TYPE_SCOUT, ucSrcSlotIdx, CONTAINER_TYPE_SCOUT, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

// Peessi : ��ī���� ������ ���, Equip�� ���� �������� ó���Ѵ�.
//RwUInt32 Logic_ItemMoveSubProcScouterSlotToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx )
//{
//	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterSlotToBag" );
//	// �� ���� 
//
//	if( Logic_IsUsingScouter() )
//		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );
//
//	if( Logic_IsScouterHasParts() )
//		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_SCOUTER_HAS_PARTS );
//
//	//	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
//	RwUInt8 ucDestBagIdx = (RwUInt8)pInventory->FindBagSlot( hDestParentSerial );
//	eCONTAINER_TYPE eDestBagType = Logic_ConvertBagIdxToContainerType( ucDestBagIdx );
//
//	if( GetDboGlobal()->GetGamePacketGenerator()->SendItemMoveReq( 
//		CONTAINER_TYPE_EQUIP, EQUIP_SLOT_TYPE_SCOUTER, (RwUInt8)eDestBagType, ucDestSlotIdx) )
//		NTL_RETURN( INVALID_DWORD );
//	else
//		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND );
//}
//
//RwBool Logic_ItemMoveSubProcScouterSlotToWarehouse( SERIAL_HANDLE hSrcSerial, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
//{
//	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterSlotToWarehouse" );
//
//	if( Logic_IsMovableEquipedScouter() == FALSE )
//		NTL_RETURN( FALSE );
//
//	// src
//	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
//	CNtlSobItemAttr* pItemAttr = Logic_GetItemSobAttrFromSobSerial( hSrcSerial );
//	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
//	{
//		// â�� ������ �� ���� ������
//		GetAlarmManager()->AlarmMessage(DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE);
//		NTL_RETURN( FALSE );
//	}
//
//	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();
//	SERIAL_HANDLE hCommonWarehouse = pWarehouse->GetSlotSerailID(NTL_COMMON_WAREHOUSE);
//	if( hDestParentSerial == hCommonWarehouse &&
//		Logic_IsCanSaveCommonWarehouse( pItemAttr ) == FALSE )
//	{
//		// ���� â�� ������ �� ���� ������
//		GetAlarmManager()->AlarmMessage(DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE);
//		NTL_RETURN( FALSE );
//	}
//
//	// dest
//	eCONTAINER_TYPE eDestContainerType = Logic_ConverWarehouseIdxToContainderType(pWarehouse->FindWarehouseSlot(hDestParentSerial));
//
//	// â�� NPC Serial
//	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
//	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();
//
//	NTL_RETURN( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, CONTAINER_TYPE_EQUIP, EQUIP_SLOT_TYPE_SCOUTER,
//		(RwUInt8)eDestContainerType, ucDestSlotIdx) );
//}
//
//RwBool Logic_ItemMoveSubProcScouterSlotToGuildWarehouse( SERIAL_HANDLE hSrcSerial, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx)
//{
//	NTL_FUNCTION( "Logic_ItemMoveSubProcScouterSlotToGuildWarehouse" );
//
//	if( Logic_IsMovableEquipedScouter() == FALSE )
//		NTL_RETURN( FALSE );
//
//	// src
//	//sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hSrcSerial);
//	CNtlSobItemAttr* pItemAttr = Logic_GetItemSobAttrFromSobSerial( hSrcSerial );
//	if( Logic_IsCanSaveWarehouse( pItemAttr ) == FALSE )
//	{
//		// â�� ������ �� ���� ������
//		GetAlarmManager()->AlarmMessage(DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE);
//		NTL_RETURN( FALSE );
//	}
//
//	// Dest
//	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
//
//	// hDestParentSerial : �ڵ��� �ƴ϶� ��� â���� �ε����� �޾Ҵ� 
//	eCONTAINER_TYPE eDestContainerType = Logic_ConverGuildWarehouseIdxToContainderType((RwUInt8)hDestParentSerial);
//
//	NTL_RETURN( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
//		CONTAINER_TYPE_EQUIP, EQUIP_SLOT_TYPE_SCOUTER,(RwUInt8)eDestContainerType, ucDestSlotIdx) );
//}

RwUInt32 Logic_ItemMoveSubProcQuestToQuest( RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcQuestToQuest" );
	// ������
	// 1. �����ڸ��� ����.
	if( ucSrcSlotIdx == ucDestSlotIdx )
	{
		GetIconMoveManager()->IconMoveEnd();
		NTL_RETURN( INVALID_DWORD );
	}

	if( GetDboGlobal()->GetGamePacketGenerator()->SendQuestItemMoveReq( ucSrcSlotIdx, ucDestSlotIdx ) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcWarehouseToEquip( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcWarehouseToEquip" );

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();	

	// src
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(hSrcSerial));
	DBO_ASSERT( pSrcItem, "Invalid SrcItem" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	DBO_ASSERT( pSrcItemAttr, "Invalid SrcItemAttr" );
	sITEM_TBLDAT* pSrcItemTable = pSrcItemAttr->GetItemTbl();
	NTL_ASSERT( pSrcItemTable, "Have No Table" );

	RwUInt8 bySrcSlot = pWarehouse->FindWarehouseSlot(pSrcItem->GetParentItem()->GetSerialID());
	eCONTAINER_TYPE eSrcContainerType = Logic_ConverWarehouseIdxToContainderType(bySrcSlot);
	
	SERIAL_HANDLE hDestSerial = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( ucDestSlotIdx );
	RwUInt16 usDestSlotFlag = Logic_ConvertEquipSlotIdxToFlag( ucDestSlotIdx );

	// 0. ����� â�� ���������� �������� ���Ⱓ������ �ƴ�. �˻簡 �ʿ����.

	// 1. Dest�� ��ī�����̰� �̹� ��ī���͸� �������� ���, 2,3�� ���� Ȯ��.
	if( ucDestSlotIdx == EQUIP_SLOT_TYPE_SCOUTER && hDestSerial != INVALID_SERIAL_ID )
	{
		CNtlSobItem* pDestItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestSerial ) );
		DBO_ASSERT( pDestItem, "Invalid DestItem" );

		if( pSrcItem->IsScouterItem() )
		{
			// 2. ��ī���Ͷ�� ��������� ���� Ȯ��.
			if( Logic_IsUsingScouter() )
				NTL_RETURN( DST_SCOUTER_WORKING );

			if( Logic_IsScouterHasParts() )
				NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
		}		
		else if( pSrcItem->IsScouterPartItem() )
		{
			// 3. ��ī���� ������� ��ī���ͼ����������. 
			RwInt32 nDestScouterIdx = pDestItem->FindEmptyChildSlot();
			if( nDestScouterIdx >= 0 )
				NTL_RETURN( Logic_ItemMoveSubProcWarehouseToScouter( hSrcSerial, ucSrcSlotIdx, (RwUInt8)nDestScouterIdx ) );				

			NTL_RETURN( DST_SCOUTER_FULL );
		}
		else
		{
			if( !Logic_EquipSlotTypeFlagCheck( usDestSlotFlag, pSrcItemTable->wEquip_Slot_Type_Bit_Flag ) )
				NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
		}
	}
	else
	{
		// 5. ������ ����Ÿ�� �˻�.
		if( !Logic_EquipSlotTypeFlagCheck( usDestSlotFlag, pSrcItemTable->wEquip_Slot_Type_Bit_Flag ) )
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
	}	

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx, CONTAINER_TYPE_EQUIP, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcWarehouseToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcWarehouseToBagSlot" );

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();	

	// src
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	NTL_ASSERT( pSrcItem, "Invalid hSrcSerial" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	NTL_ASSERT( pSrcItemAttr, "Have No Attr" );

	RwUInt8 bySrcSlot = pWarehouse->FindWarehouseSlot(pSrcItem->GetParentItem()->GetSerialID());
	eCONTAINER_TYPE eSrcContainerType = Logic_ConverWarehouseIdxToContainderType(bySrcSlot);

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	SERIAL_HANDLE hDestBagSerial = pInventory->GetBagItem( ucDestSlotIdx );
	RwInt32 nEmptyBagChildSlot = -1;

	// 1. DestSlot�� ������ �������� ������ üũ. 
	if( hDestBagSerial == INVALID_SERIAL_ID )
	{
		// 2. src�������� �����̶��.
		if( pSrcItem->IsBagItem() )
		{
			// 3. src ������ ���Ⱓ üũ�� ���� �ʾƵ� �ȴ�. â�� �����ϴ� �͵��� ���Ⱓ�� ������ ����.
			if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove( hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx, CONTAINER_TYPE_BAGSLOT, ucDestSlotIdx ) )
				NTL_RETURN( INVALID_DWORD )	
			else
				NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
		}
		else
		{
			// 4. ������ �ƴϰ�, dest�� ���浵 ���ٸ� ���.
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_NOT_BAG );
		}
	}
	else
	{
		CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestBagSerial ) );
		NTL_ASSERT( pDestBagItem, "Invalid hDestBagSerial" );

		// 4. dest�� ������ �� á���� ���.
		if( pDestBagItem->FullChild() )
			NTL_RETURN( DST_ITEM_BAG_FULL );

		nEmptyBagChildSlot = pDestBagItem->FindEmptyChildSlot();

		// 5. �� ���� WarehouseToBagChild�����������. 
		NTL_RETURN( Logic_ItemMoveSubProcWarehouseToBagChild( hSrcSerial, ucSrcSlotIdx, PLACE_BAG, hDestBagSerial, ucDestSlotIdx, uiStackCount ) );
	}		
}

RwUInt32 Logic_ItemMoveSubProcWarehouseToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcWarehouseToBag" );

	// src
	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();	
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(hSrcSerial));
	RwUInt8 bySrcSlot = pWarehouse->FindWarehouseSlot(pSrcItem->GetParentItem()->GetSerialID());
	eCONTAINER_TYPE eSrcContainerType = Logic_ConverWarehouseIdxToContainderType(bySrcSlot);

	// dest
	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	RwUInt8 ucDestBagIdx = (RwUInt8)pInventory->FindBagSlot( hDestParentSerial );
	eCONTAINER_TYPE eDestBagType = Logic_ConvertBagIdxToContainerType( ucDestBagIdx );

	CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestParentSerial ) );
	DBO_ASSERT( pDestBagItem, "Invalid DestBagItem" );
	CNtlSobItemAttr* pDestBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestBagItem->GetSobAttr() );
	DBO_ASSERT( pDestBagItemAttr, "Invalid DestBagItemAttr" );
	SERIAL_HANDLE hDestSerial = pDestBagItem->GetChildSerial( ucDestSlotIdx );

	// 2. dest ������ ��â���ΰ�� �˻�
	if( !Logic_ItemMoveToNetStoreCheck( ucDestBagIdx ) )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NETPYSTORE );

	// 3. dest ������ ���Ⱓ �˻�
	if( pDestBagItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	if( Logic_IsStackMovable(hSrcSerial, hDestSerial, uiStackCount) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMoveStack(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx,
			(RwUInt8)eDestBagType, ucDestSlotIdx, (RwUInt8)uiStackCount) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx,
			(RwUInt8)eDestBagType, ucDestSlotIdx) )
			NTL_RETURN( INVALID_DWORD )		
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}	
}

RwUInt32 Logic_ItemMoveSubProcWarehouseToScouter( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcWarehouseToScouter" );

	// 1. ��ī���� ���� Ȯ��.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );

	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hSrcSerial ) );
	DBO_ASSERT( pSrcItem, "Invalid Src Item" );
	CNtlSobItemAttr* pSrcItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pSrcItem->GetSobAttr() );
	DBO_ASSERT( pSrcItemAttr, "Invalid src ItemAttr" );

	// 2. ��ī���� ������ �̵� �����ϴ�. 
	if( !pSrcItem->IsScouterPartItem() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_SCOUTER_NOT_SCOUTERPARTS );	

	RwUInt32 hDestScouter = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( EQUIP_SLOT_TYPE_SCOUTER );
	CNtlSobItem* pDestScouter = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestScouter ) );
	DBO_ASSERT( pDestScouter, "INvalid Scouter. Critical Error" );
	CNtlSobItemAttr* pDestScouterAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestScouter->GetSobAttr() );

	// 3. ��ī���� ���Ⱓ üũ.
	if( pDestScouterAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_SCOUTER_EXPIRED_DURATION );

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();	

	// src
	RwUInt8 bySrcSlot = pWarehouse->FindWarehouseSlot(pSrcItem->GetParentItem()->GetSerialID());
	eCONTAINER_TYPE eSrcContainerType = Logic_ConverWarehouseIdxToContainderType(bySrcSlot);

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx, CONTAINER_TYPE_SCOUT, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcWarehouseToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace,
													SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount )
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcWarehouseToWarehouse" );	

	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();	

	// src
	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(hSrcSerial));	
	NTL_ASSERT(pSrcItem, "Logic_ItemMoveSubProcWarehouseToWarehouse, Not exist item : " << hSrcSerial);
	CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSrcItem->GetSobAttr());
	NTL_ASSERT(pSobItemAttr, "Logic_ItemMoveSubProcWarehouseToWarehouse, Not exist item attr : " << hSrcSerial);	

	if( Logic_IsCanSaveWarehouse( pSobItemAttr ) == FALSE )
	{
		// â�� ������ �� ���� ������
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE );
	}

	SERIAL_HANDLE hCommonWarehouse = pWarehouse->GetSlotSerailID(NTL_COMMON_WAREHOUSE);
	if( hDestParentSerial == hCommonWarehouse &&
		Logic_IsCanSaveCommonWarehouse( pSobItemAttr ) == FALSE )
	{
		// ���� â�� ������ �� ���� ������		
		NTL_RETURN( DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE );
	}

	RwUInt8 bySrcSlot = pWarehouse->FindWarehouseSlot(pSrcItem->GetParentItem()->GetSerialID());
	eCONTAINER_TYPE eSrcContainerType = Logic_ConverWarehouseIdxToContainderType(bySrcSlot);

	// dest
	eCONTAINER_TYPE eDestContainerType = Logic_ConverWarehouseIdxToContainderType(pWarehouse->FindWarehouseSlot(hDestParentSerial));

	// â�� NPC Serial
	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();

	// ������
	// 1. �����ڸ��� ����.
	if( ucSrcSlotIdx == ucDestSlotIdx && eSrcContainerType == eDestContainerType)
	{
		GetIconMoveManager()->IconMoveEnd();
		NTL_RETURN( INVALID_DWORD );
	}

	// for Logic_IsStackMovable
	CNtlSobItem* pDestParentItem = reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(hDestParentSerial));

	if( Logic_IsStackMovable(hSrcSerial, pDestParentItem->GetChildSerial(ucDestSlotIdx), uiStackCount) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMoveStack(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx,
			(RwUInt8)eDestContainerType, ucDestSlotIdx, (RwUInt8)uiStackCount) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx,
			(RwUInt8)eDestContainerType, ucDestSlotIdx) )
			NTL_RETURN( INVALID_DWORD )		
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
	}
}

//RwBool Logic_ItemMoveSubProcWarehouseToScouterSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx)
//{
//	NTL_FUNCTION( "Logic_ItemMoveSubProcWarehouseToScouterSlot" );
//
//	if( Logic_IsMovableEquipedScouter() == FALSE )
//		NTL_RETURN( FALSE );
//
//	CNtlWarehouse* pWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetWarehouse();	
//
//	// src
//	CNtlSobItem* pSrcItem = reinterpret_cast<CNtlSobItem*>(GetNtlSobManager()->GetSobObject(hSrcSerial));
//	RwUInt8 bySrcSlot = pWarehouse->FindWarehouseSlot(pSrcItem->GetParentItem()->GetSerialID());
//	eCONTAINER_TYPE eSrcContainerType = Logic_ConverWarehouseIdxToContainderType(bySrcSlot);
//
//	// â�� NPC Serial
//	CWarehouseBarGui* pWarehouseBarGui = reinterpret_cast<CWarehouseBarGui*>(GetDialogManager()->GetDialog(DIALOG_WAREHOUSEBAR));
//	SERIAL_HANDLE hNPCHandle = pWarehouseBarGui->GetNPCSerial();
//
//	NTL_RETURN( GetDboGlobal()->GetGamePacketGenerator()->SendBankMove(hNPCHandle, (RwUInt8)eSrcContainerType, ucSrcSlotIdx,
//		CONTAINER_TYPE_EQUIP, EQUIP_SLOT_TYPE_SCOUTER) );
//}

RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToEquip(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcGuildWarehouseToEquip" );

	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem(hSrcSerial);
	NTL_ASSERT(pGuildWarehouseItem, "Logic_ItemMoveSubProcGuildWarehouseToBagSlot, Not exist guild warehouse item of handle << " << hSrcSerial);
	sITEM_TBLDAT* pSrcItemTable = pGuildWarehouseItem->pITEM_TBLDAT;
	NTL_ASSERT( pSrcItemTable, "Have No Table" );

	SERIAL_HANDLE hDestSerial = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( ucDestSlotIdx );
	RwUInt16 usDestSlotFlag = Logic_ConvertEquipSlotIdxToFlag( ucDestSlotIdx );

	// 0. ����� â�� ���������� �������� ���Ⱓ������ �ƴ�. �˻簡 �ʿ����.
	// 1. Dest�� ��ī�����̰� �̹� ��ī���͸� �������� ���, 2,3�� ���� Ȯ��.
	if( ucDestSlotIdx == EQUIP_SLOT_TYPE_SCOUTER && hDestSerial != INVALID_SERIAL_ID )
	{
		CNtlSobItem* pDestItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestSerial ) );
		DBO_ASSERT( pDestItem, "Invalid DestItem" );

		if( pSrcItemTable->byItem_Type == ITEM_TYPE_SCOUTER )
		{
			// 2. ��ī���Ͷ�� ��������� ���� Ȯ��.
			if( Logic_IsUsingScouter() )
				NTL_RETURN( DST_SCOUTER_WORKING );

			if( Logic_IsScouterHasParts() )
				NTL_RETURN( DST_SCOUTER_MUST_CLEAR_SCOUTER );
		}		
		else if( pSrcItemTable->byItem_Type == ITEM_TYPE_SCOUTER_PART )
		{
			// 3. ��ī���� ������� ��ī���ͼ����������. 
			RwInt32 nDestScouterIdx = pDestItem->FindEmptyChildSlot();
			if( nDestScouterIdx >= 0 )
				NTL_RETURN( Logic_ItemMoveSubProcGuildWarehouseToScouter( hSrcSerial, eSrcPlace, ucSrcSlotIdx, PLACE_SCOUTER, hDestSerial, (RwUInt8)nDestScouterIdx, uiStackCount ) );				

			NTL_RETURN( DST_SCOUTER_FULL );
		}
		else
		{
			if( !Logic_EquipSlotTypeFlagCheck( usDestSlotFlag, pSrcItemTable->wEquip_Slot_Type_Bit_Flag ) )
				NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
		}
	}
	else
	{
		// 5. ������ ����Ÿ�� �˻�.
		if( !Logic_EquipSlotTypeFlagCheck( usDestSlotFlag, pSrcItemTable->wEquip_Slot_Type_Bit_Flag ) )
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE );
	}	

	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
		pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, CONTAINER_TYPE_EQUIP, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToBagSlot(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcGuildWarehouseToBagSlot" );

	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem(hSrcSerial);
	NTL_ASSERT(pGuildWarehouseItem, "Logic_ItemMoveSubProcGuildWarehouseToBagSlot, Not exist guild warehouse item of handle << " << hSrcSerial);
	sITEM_TBLDAT* pSrcItemTable = pGuildWarehouseItem->pITEM_TBLDAT;
	NTL_ASSERT( pSrcItemTable, "Have No Table" );

	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	SERIAL_HANDLE hDestBagSerial = pInventory->GetBagItem( ucDestSlotIdx );
	RwInt32 nEmptyBagChildSlot = -1;

	// 1. DestSlot�� ������ �������� ������ üũ. 
	if( hDestBagSerial == INVALID_SERIAL_ID )
	{
		// 2. src�������� �����̶��.
		if( pSrcItemTable->byItem_Type == ITEM_TYPE_BAG )
		{
			// 3. src ������ ���Ⱓ üũ�� ���� �ʾƵ� �ȴ�. â�� �����ϴ� �͵��� ���Ⱓ�� ������ ����.
			if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
				pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, CONTAINER_TYPE_BAGSLOT, ucDestSlotIdx) )
				NTL_RETURN( INVALID_DWORD )	
			else
				NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
		}
		else
		{
			// 4. ������ �ƴϰ�, dest�� ���浵 ���ٸ� ���.
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_NOT_BAG );
		}
	}
	else
	{
		CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestBagSerial ) );
		NTL_ASSERT( pDestBagItem, "Invalid hDestBagSerial" );

		// 4. dest�� ������ �� á���� ���.
		if( pDestBagItem->FullChild() )
			NTL_RETURN( DST_ITEM_BAG_FULL );

		nEmptyBagChildSlot = pDestBagItem->FindEmptyChildSlot();

		// 5. �� ���� BagChildToBagChild�����������. 
		NTL_RETURN( Logic_ItemMoveSubProcGuildWarehouseToBagChild( hSrcSerial, eDestPlace, ucSrcSlotIdx, eDestPlace, hDestParentSerial, ucDestSlotIdx, uiStackCount ) );		
	}	
}

RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToBagChild(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcGuildWarehouseToBag" );

	// src
	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem(hSrcSerial);
	NTL_ASSERT(pGuildWarehouseItem, "Logic_ItemMoveSubProcGuildWarehouseToBagSlot, Not exist guild warehouse item of handle << " << hSrcSerial);

	// dest
	CNtlInventory* pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();
	RwUInt8 ucDestBagIdx = (RwUInt8)pInventory->FindBagSlot( hDestParentSerial );
	eCONTAINER_TYPE eDestBagType = Logic_ConvertBagIdxToContainerType( ucDestBagIdx );

	CNtlSobItem* pDestBagItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestParentSerial ) );
	DBO_ASSERT( pDestBagItem, "Invalid DestBagItem" );
	CNtlSobItemAttr* pDestBagItemAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestBagItem->GetSobAttr() );
	DBO_ASSERT( pDestBagItemAttr, "Invalid DestBagItemAttr" );
	SERIAL_HANDLE hDestSerial = pDestBagItem->GetChildSerial( ucDestSlotIdx );

	// 2. dest ������ ��â���ΰ�� �˻�
	if( !Logic_ItemMoveToNetStoreCheck( ucDestBagIdx ) )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_NETPYSTORE );

	// 3. dest ������ ���Ⱓ �˻�
	if( pDestBagItemAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION );

	if( Logic_IsStackMovable_from_GuildWarehouse(pGuildWarehouseItem, hDestSerial, uiStackCount) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveStackReq(pGuildWarehouse->GetNPCHandle(),
			pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, (RwUInt8)eDestBagType, ucDestSlotIdx, (RwUInt8)uiStackCount) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
			pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, (RwUInt8)eDestBagType, ucDestSlotIdx) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
	}
}

RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToScouter(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcGuildWarehouseToScouter" );

	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem(hSrcSerial);
	NTL_ASSERT(pGuildWarehouseItem, "Logic_ItemMoveSubProcGuildWarehouseToBagSlot, Not exist guild warehouse item of handle << " << hSrcSerial);
	sITEM_TBLDAT* pSrcItemTable = pGuildWarehouseItem->pITEM_TBLDAT;
	NTL_ASSERT( pSrcItemTable, "Have No Table" );

	// 1. ��ī���� ���� Ȯ��.
	if( Logic_IsUsingScouter() )
		NTL_RETURN( DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU );

	// 2. ��ī���� ������ �̵� �����ϴ�. 
	if( pSrcItemTable->byItem_Type != ITEM_TYPE_SCOUTER_PART )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_TO_SCOUTER_NOT_SCOUTERPARTS );	

	RwUInt32 hDestScouter = GetNtlSLGlobal()->GetSobAvatar()->GetInventory()->GetEquipItem( EQUIP_SLOT_TYPE_SCOUTER );
	CNtlSobItem* pDestScouter = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( hDestScouter ) );
	DBO_ASSERT( pDestScouter, "INvalid Scouter. Critical Error" );
	CNtlSobItemAttr* pDestScouterAttr = reinterpret_cast<CNtlSobItemAttr*>( pDestScouter->GetSobAttr() );

	// 3. ��ī���� ���Ⱓ üũ.
	if( pDestScouterAttr->IsExpired() )
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_SCOUTER_EXPIRED_DURATION );

	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
		pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, CONTAINER_TYPE_SCOUT, ucDestSlotIdx) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

//RwBool Logic_ItemMoveSubProcGuildWarehouseToScouterSlot(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
//{
//	NTL_FUNCTION( "Logic_ItemMoveSubProcGuildWarehouseToScouterSlot" );
//
//	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
//	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem(hSrcSerial);
//	NTL_ASSERT(pGuildWarehouseItem, "Logic_ItemMoveSubProcGuildWarehouseToBagSlot, Not exist guild warehouse item of handle << " << hSrcSerial);
//
//	NTL_RETURN( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
//				pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, CONTAINER_TYPE_EQUIP, EQUIP_SLOT_TYPE_SCOUTER) );
//}

RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToGuildWarehouse(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount)
{
	// src
	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();
	sGuildWarehouseSlot* pGuildWarehouseItem = pGuildWarehouse->GetItem(hSrcSerial);
	RwUInt8 bySrcIndex = (RwUInt8)(pGuildWarehouseItem->byServerPlace - CONTAINER_TYPE_GUILD_FIRST);
	NTL_ASSERT(pGuildWarehouseItem, "Logic_ItemMoveSubProcGuildWarehouseToBagSlot, Not exist guild warehouse item of handle << " << hSrcSerial);

	// ���� ������ �̵����� �ʴ´�
	if( bySrcIndex == hDestParentSerial )
	{
		if( ucSrcSlotIdx == ucDestSlotIdx )
		{
			GetIconMoveManager()->IconMoveEnd();
			NTL_RETURN( INVALID_DWORD );
		}
	}

	// Dest
	// hDestParentSerial : �ڵ��� �ƴ϶� ��� â���� �ε����� �޾Ҵ� 
	sGuildWarehouseSlot* pGuildWarehouseDestItem = pGuildWarehouse->GetItem((RwUInt8)hDestParentSerial, ucDestSlotIdx);
	eCONTAINER_TYPE eDestContainerType = Logic_ConverGuildWarehouseIdxToContainderType((RwUInt8)hDestParentSerial);

	if( Logic_IsStackMovable_from_GuildWarehouse(pGuildWarehouseItem, pGuildWarehouseDestItem, uiStackCount) )
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveStackReq(pGuildWarehouse->GetNPCHandle(),
			pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, (RwUInt8)eDestContainerType, ucDestSlotIdx, (RwUInt8)uiStackCount) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
	}
	else
	{
		if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseMoveReq(pGuildWarehouse->GetNPCHandle(),
			pGuildWarehouseItem->byServerPlace, pGuildWarehouseItem->byPos, (RwUInt8)eDestContainerType, ucDestSlotIdx) )
			NTL_RETURN( INVALID_DWORD )
		else
			NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Zenny �̵� ����

RwUInt32 Logic_ItemMoveSubProcSubBagZennyToPartyCharmZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcSubBagMoneyToPartyCharmZenny" );

	RwUInt32 uiUpdateZenny = -1 * ( GetNtlSLGlobal()->GetAdjustZennyInfo()->GetAdjustZenny(SAdjustZennyInfo::PARTY_CHARM ) - uiZenny);

	if( GetDboGlobal()->GetGamePacketGenerator()->SendPartyDeclareZennyReq(uiUpdateZenny) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcSubBagZennyToWarehouseZenny(SERIAL_HANDLE hNPCHandle, RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcSubBagMoneyToWarehouse" );

	// â��(����)�� ���� �ִ�
	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankZenny(hNPCHandle, uiZenny, true) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcSubBagZennyToGuildWarehouseZenny(SERIAL_HANDLE hNPCHandle, RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcSubBagMoneyToGuildWarehouse" );

	// ��� â��(����)�� ���� �ִ�
	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseZennyReq(hNPCHandle, uiZenny, true) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcSubBagZennyToTradeCartZenny(SERIAL_HANDLE hTargetHandle, RwUInt32 uiZenny)
{	
	NTL_FUNCTION( "Logic_ItemMoveSubProcSubBagZennyToTradeCartZenny" );

	RwUInt32 uiTradeZenny = -1 * ( GetNtlSLGlobal()->GetAdjustZennyInfo()->GetAdjustZenny(SAdjustZennyInfo::USER_TRADE ) - uiZenny);

	if( GetDboGlobal()->GetGamePacketGenerator()->SendTradeZennyUpdateReq(hTargetHandle, uiTradeZenny) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcSubBagZennyToMailSystemZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcSubBagZennyToMailSystemZenny" );

	GetNtlSLGlobal()->GetAdjustZennyInfo()->SetAdjustZenny( SAdjustZennyInfo::MAIL_BOX, GetNtlSLGlobal()->GetAdjustZennyInfo()->GetAdjustZenny(SAdjustZennyInfo::MAIL_BOX ) - uiZenny );
	
	GetIconMoveManager()->IconMoveEnd();
	NTL_RETURN( INVALID_DWORD );
}

RwUInt32 Logic_ItemMoveSubProcSubBagZennyPartyInvenZenny(RwUInt8 bySlot, RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcSubBagZennyPartyInvenZenny" );

	// ��Ƽ �κ��� ��ſ� ���� ���ϸ� ����
	if( GetDboGlobal()->GetGamePacketGenerator()->SendPartyInven_InvestZennyReq(bySlot, uiZenny) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcPartyCharmZennyToSubBagZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcPartyCharmZennyToSubBagZenny" );

	RwUInt32 uiUpdateZenny = -1 * (GetNtlSLGlobal()->GetAdjustZennyInfo()->GetAdjustZenny(SAdjustZennyInfo::PARTY_CHARM ) + uiZenny );

	if( GetDboGlobal()->GetGamePacketGenerator()->SendPartyDeclareZennyReq(uiUpdateZenny) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcWareHouseZennyToSubBagZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcWareHouseZennyToSubBagZenny" );

	CWarehouseCommonGui* pWarehouseCommonGui = reinterpret_cast<CWarehouseCommonGui*>( GetDialogManager()->GetDialog(DIALOG_WAREHOUSE_COMMON) );

	// â��(����)���� ���� ����
	if( GetDboGlobal()->GetGamePacketGenerator()->SendBankZenny(pWarehouseCommonGui->GetNPCHandle(), uiZenny, false) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcGuildWareHouseZennyToSubBagZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcGuildWareHouseZennyToSubBagZenny" );

	CNtlGuildWarehouse* pGuildWarehouse = GetNtlSLGlobal()->GetSobAvatar()->GetGuildWarehouse();

	// ��� â��(����)�� ���� ����
	if( GetDboGlobal()->GetGamePacketGenerator()->SendGuildWarehouseZennyReq(pGuildWarehouse->GetNPCHandle(), uiZenny, false) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )			
}

RwUInt32 Logic_ItemMoveSubProcTradeCartZennyToSubBagZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcTradeCartZennyToSubBagZenny" );

	RwUInt32 uiTradeZenny = -1 * (GetNtlSLGlobal()->GetAdjustZennyInfo()->GetAdjustZenny(SAdjustZennyInfo::USER_TRADE ) + uiZenny);
	CTradeCart* pGui = reinterpret_cast<CTradeCart*>( GetDialogManager()->GetDialog(DIALOG_TRADECART) );

	if( !pGui )
		NTL_RETURN( DST_ZENNY_CAN_NOT_MOVE_TO_TRADECART_NOT_VALID );

	RwUInt32 uiTargetSerial = pGui->GetTargetSerial();

	if( GetDboGlobal()->GetGamePacketGenerator()->SendTradeZennyUpdateReq(uiTargetSerial, uiTradeZenny) )
		NTL_RETURN( INVALID_DWORD )
	else
		NTL_RETURN( DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND )
}

RwUInt32 Logic_ItemMoveSubProcMailSystemZennyToSubBagZenny(RwUInt32 uiZenny)
{
	NTL_FUNCTION( "Logic_ItemMoveSubProcMailSystemZennyToSubBagZenny" );

	GetNtlSLGlobal()->GetAdjustZennyInfo()->SetAdjustZenny( SAdjustZennyInfo::MAIL_BOX, GetNtlSLGlobal()->GetAdjustZennyInfo()->GetAdjustZenny(SAdjustZennyInfo::MAIL_BOX ) + uiZenny );
	GetIconMoveManager()->IconMoveEnd();
	NTL_RETURN( INVALID_DWORD );
}

