/*****************************************************************************
* File			: DboPackethandler_GUParty.cpp
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2007. 1. 16
* Abstract		: ��Ƽ ���� ��Ŷ �ڵ�
*****************************************************************************
* Desc         : 
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboPacketHandler.h"

// shared
#include "ItemTable.h"

// sound
#include "GUISoundDefine.h"

// simulation
#include "NtlNetSender.h"
#include "NtlSLEventFunc.h"
#include "NtlSLPacketGenerator.h"

// dbo
#include "IconMoveManager.h"
#include "DiceManager.h"

void PacketHandler_GSPartyCreateRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CREATE_RES );

	// �ڽ��� ��û�� ��Ƽ ���� ����� �˷��ش�.
	sGU_PARTY_CREATE_RES* pResult = (sGU_PARTY_CREATE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlSobAvatarAttr* pAvatarAttr = reinterpret_cast<CNtlSobAvatarAttr*>(pAvatar->GetSobAttr());

	// ��Ƽ ����
	CNtlSLEventGenerator::PartyCreate(pResult->wszPartyName);

	// ��Ƽ ����Ʈ�� �ڽ��� �߰���Ų��
	CNtlSLEventGenerator::PartyMemberAdd(pAvatar->GetSerialID(), (WCHAR*)pAvatarAttr->GetName());

	// �ڽ��� ��Ƽ���̴�
	CNtlSLEventGenerator::PartyLeaderChange(pAvatar->GetSerialID());

	// ���� �й� ���
	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, NTL_PARTY_ZENNY_LOOTING_GREEDILY);

	// ������ �й� ���
	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, NTL_PARTY_ITEM_LOOTING_GREEDILY);

	// ��Ƽ �κ��� ����Ǵ� �������� ���
	CDboEventGenerator::PartyInventory(PINVEN_CHANGE_SAVED_ITEM_GRADE, 0, INVALID_SERIAL_ID, 0, DBO_PARTY_INVEN_DEFAULT_ITEM_RANK);

	// ��Ƽ ����Ʈ
	CNtlSLEventGenerator::TSParty();
}

void PacketHandler_GSPartyDisbandRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DISBAND_RES );

	// �ڽ��� ��Ƽ�� �ػ��� ����� �˷��ش�.
	sGU_PARTY_DISBAND_RES* pResult = (sGU_PARTY_DISBAND_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyDisband();
}

void PacketHandler_GSPartyDisbandNfy(void *pPacket)
{
	// ��Ƽ�� �ػ�Ǿ����� ��Ƽ���� �ƴ� �ɹ��鿡�� �˷��ش�.
	//sGU_PARTY_DISBANDED_NFY* pResult = (sGU_PARTY_DISBANDED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyDisband();
}

void PacketHandler_GSPartyInviteRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVITE_RES );

	// ��Ƽ �������� ��Ƽ �ʴ� ����� �˷��ش�.	
	sGU_PARTY_INVITE_RES* pResult = (sGU_PARTY_INVITE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}	

	// %s���� ��Ƽ�� �ʴ��Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVITE_SUCCESS, FALSE, NULL, pResult->wszTargetName);
}

void PacketHandler_GSPartyInviteNfy(void *pPacket)
{
	// �ʴ� ��󿡰� �޼����� ������.
	sGU_PARTY_INVITE_NFY* pResult = (sGU_PARTY_INVITE_NFY*)pPacket;

	if( pResult->bFromPc )
	{
		// %s ���� ��Ƽ�� �����Ͻðڽ��ϱ�?
		GetAlarmManager()->FormattedAlarmMessage( DST_PARTY_PARTY_INVITE_WITHOUT_PARTY, FALSE, NULL, pResult->wszInvitorPcName );
	}
	else
	{
		// %s ��Ƽ�� �����Ͻðڽ��ϱ�?
		GetAlarmManager()->FormattedAlarmMessage( DST_PARTY_PARTY_INVITE, FALSE, NULL, pResult->wszInvitorPartyName );
	}
}

void PacketHandler_GSPartyResponseInvitationRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_RESPONSE_INVITATION_RES );

	// ��Ƽ �ʴ��� ���信 ���� ����� �������� ������.
	sGU_PARTY_RESPONSE_INVITATION_RES* pResult = (sGU_PARTY_RESPONSE_INVITATION_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}	
}

void PacketHandler_GSPartyMemberJoinedNfy(void *pPacket)
{
	// ���ο� ��Ƽ���� ���������� �˷��ش�.
	sGU_PARTY_MEMBER_JOINED_NFY* pResult = (sGU_PARTY_MEMBER_JOINED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyMemberAdd(pResult->memberInfo.hHandle, pResult->memberInfo.awchMemberName,
		pResult->memberInfo.byRace, pResult->memberInfo.byClass, pResult->memberInfo.byLevel,
		pResult->memberInfo.wCurLP, pResult->memberInfo.wMaxLP, pResult->memberInfo.wCurEP,
		pResult->memberInfo.wMaxEP, pResult->memberInfo.worldTblidx, pResult->memberInfo.worldId,
		pResult->memberInfo.vCurLoc.x, pResult->memberInfo.vCurLoc.y, pResult->memberInfo.vCurLoc.z);

	// %s���� ��Ƽ�� �����̽��ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_NEW_MEMBER, FALSE, NULL, pResult->memberInfo.awchMemberName);
}

void PacketHandler_GSPartyInfo(void *pPacket)
{
	// ���� ������ ��Ƽ���� ��Ƽ������ �޴´�.
	sGU_PARTY_INFO* pResult = (sGU_PARTY_INFO*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	// ��Ƽ�� �����Ѵ�
	CNtlSLEventGenerator::PartyCreate(pResult->awchPartyName);

	for(RwInt32 i = 0 ; i < pResult->byMemberInfoCount ; ++i )
	{		
		CNtlSLEventGenerator::PartyMemberAdd(pResult->memberInfo[i].hHandle, pResult->memberInfo[i].awchMemberName,
			pResult->memberInfo[i].byRace, pResult->memberInfo[i].byClass,
			pResult->memberInfo[i].byLevel, pResult->memberInfo[i].wCurLP,
			pResult->memberInfo[i].wMaxLP, pResult->memberInfo[i].wCurEP,
			pResult->memberInfo[i].wMaxEP,
			pResult->memberInfo[i].worldTblidx, pResult->memberInfo[i].worldId,
			pResult->memberInfo[i].vCurLoc.x, pResult->memberInfo[i].vCurLoc.y, pResult->memberInfo[i].vCurLoc.z);
	}	

	// ��Ƽ ����Ʈ�� �ڽ��� �߰���Ų��	
	CNtlSobAvatarAttr* pAvatarAttr = reinterpret_cast<CNtlSobAvatarAttr*>(pAvatar->GetSobAttr());
	CNtlSLEventGenerator::PartyMemberAdd(pAvatar->GetSerialID(), (WCHAR*)pAvatarAttr->GetName());

	// ��Ƽ���� �����Ѵ�
	CNtlSLEventGenerator::PartyLeaderChange(pResult->hLeader);

	// ������ �й� ���
	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, pResult->byItemLootingMethod);

	// ���� �й� ���
	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, pResult->byZennyLootingMethod);

	// ��Ƽ ���� ����
	CDboEventGenerator::PartyCharm(PCET_ACTIVATE, 0, pResult->registeredCharmTblidx[0]);
	CDboEventGenerator::PartyCharm(PCET_ACTIVATE, 1, pResult->registeredCharmTblidx[1]);

	for( RwUInt8 i = 0 ; i < NTL_PARTY_CHARM_INVENTORY_COUNT ; ++i )
	{
		CNtlSLEventGenerator::PartyCharmActivity(PCAT_ACTIVE, i, pResult->registeredCharmTblidx[i], (RwReal)pResult->adwRemainingTime[i]);
	}

    // ���� Ÿ�� ������    
    CNtlSLEventGenerator::PartyShareTargetNfy(pResult->sharetargetInfo);

	// ��Ƽ ���� ����
	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_STATE, INVALID_SERIAL_ID, pResult->eDiff);	

	// ��Ƽ �κ��� ������ ������ ���
	CDboEventGenerator::PartyInventory(PINVEN_CHANGE_SAVED_ITEM_GRADE, 0, INVALID_SERIAL_ID, 0, pResult->byItemRank);
}

void PacketHandler_GSPartyInventoryInfo(void *pPacket)
{
	// ���� ���� ��Ƽ �ɹ����� ��Ƽ �κ� ������ �˷��ش�
	sGU_PARTY_INVENTORY_INFO* pResult = (sGU_PARTY_INVENTORY_INFO*)pPacket;

	for(RwInt32 i = 0 ; i < pResult->bySlotInfoCount ; ++i )
	{
		CDboEventGenerator::PartyInventory(PINVEN_ADD_ITEM, pResult->inventorySlotInfo[i].bySlotIndex,
			pResult->inventorySlotInfo[i].itemInfo.tblidx,
			pResult->inventorySlotInfo[i].itemInfo.byStackCount,
			pResult->inventorySlotInfo[i].itemInfo.byRank,
			pResult->inventorySlotInfo[i].itemInfo.aOptionTblidx[0],
			pResult->inventorySlotInfo[i].itemInfo.aOptionTblidx[1],

			pResult->inventorySlotInfo[i].itemInfo.bNeedToIdentify,
			pResult->inventorySlotInfo[i].itemInfo.byGrade);
	}	
}

void PacketHandler_GSPartyOpenedCharmInventoryInfo(void *pPacket)
{
	// ���� ���� ��Ƽ �ɹ����� ������ ��Ƽ ����â ������ �˷��ش�
	sGU_PARTY_OPENED_CHARM_INVENTORY_INFO* pResult = (sGU_PARTY_OPENED_CHARM_INVENTORY_INFO*)pPacket;

	// ���� ���
	if( pResult->victimItemInfo.itemTblidx != INVALID_SERIAL_ID )
	{
		CDboEventGenerator::PartyVictim(PVI_REG_CHARM, pResult->victimItemInfo.itemTblidx, pResult->victimItemInfo.bySlotIndex);

		for(RwInt32 i = 0 ; i < pResult->byVictimInfoCount ; ++i )
		{
			// ����
			if( pResult->aVictimInfo[i].dwZenny > 0 )
				CDboEventGenerator::PartyVictim(PVI_ZENNY, pResult->aVictimInfo[i].hMember, pResult->aVictimInfo[i].dwZenny);
		}
	}

	// ���� ���� �ִ� ����â
	if( 0 <= pResult->byCharmInventoryIndex && pResult->byCharmInventoryIndex < NTL_PARTY_CHARM_INVENTORY_COUNT )
	{
		CNtlSLEventGenerator::PartyUpdate(PMT_LEADER_CHARM_OPEN);
		CDboEventGenerator::PartyCharm(PCET_OPEN, pResult->byCharmInventoryIndex);
	}	
}

void PacketHandler_GSPartyInviteDeclinedNfy(void *pPacket)
{
	// �ʴ��� ����� �����ߴ�.
	sGU_PARTY_INVITATION_DECLINED_NFY* pResult = (sGU_PARTY_INVITATION_DECLINED_NFY*)pPacket;	

	// %s���� �ʴ븦 �����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVITE_DECLINE, FALSE, NULL, pResult->wszPlayerName);
}

void PacketHandler_GSPartyInviteExpiredNfy(void *pPacket)
{
	// ��Ƽ �ʴ븦 ������ ���� �ð����� ������ ������.
	sGU_PARTY_INVITATION_EXPIRED_NFY* pResult = (sGU_PARTY_INVITATION_EXPIRED_NFY*)pPacket;

	// %s���� �ʴ븦 �����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVITE_DECLINE, FALSE, NULL, pResult->wszPlayerName);
}

void PacketHandler_GSPartyLeaveRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_LEAVE_RES );

	// �ڽ��� ��û�� ��Ƽ Ż���� ����� �˷��ش�.
	sGU_PARTY_LEAVE_RES* pResult = (sGU_PARTY_LEAVE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyDisband();
}

void PacketHandler_GSPartyMemberLeftNfy(void *pPacket)
{
	// �ڽ��� ��Ƽ���� ������.
	sGU_PARTY_MEMBER_LEFT_NFY* pResult = (sGU_PARTY_MEMBER_LEFT_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText	= pMember->wszMemberName;

	// %s���� ��Ƽ���� Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_LEAVE, FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyMemberDel(pResult->hMember);
}

void PacketHandler_GSPartyKickOutRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_KICK_OUT_RES );

	// ��Ƽ �ɹ� ���� ���
	sGU_PARTY_KICK_OUT_RES* pResult = (sGU_PARTY_KICK_OUT_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hTargetMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hTargetMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_LEAVE, FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyMemberDel(pResult->hTargetMember);
}

void PacketHandler_GSPartyMemberKickedOutNfy(void *pPacket)
{
	// ��Ƽ �ɹ��� ����� ���� �����ִ� ��Ƽ������ �˷��ش�.
	sGU_PARTY_MEMBER_KICKED_OUT_NFY* pResult = (sGU_PARTY_MEMBER_KICKED_OUT_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_LEAVE, FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyMemberDel(pResult->hMember);
}

void PacketHandler_GSPartyChangeLeaderRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHANGE_LEADER_RES );

	// ��Ƽ �������� ���� ���� ��û�� ����� �˷��ش�.
	sGU_PARTY_CHANGE_LEADER_RES* pResult = (sGU_PARTY_CHANGE_LEADER_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hNewLeader) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hNewLeader);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_CHANGE_LEADER, FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyLeaderChange(pResult->hNewLeader);
}

void PacketHandler_GSPartyChangedLeaderNfy(void *pPacket)
{
	// ��Ƽ ������ ����Ǿ����� ��Ƽ �ɹ����� �˷��ش�
	sGU_PARTY_LEADER_CHANGED_NFY* pResult = (sGU_PARTY_LEADER_CHANGED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hNewLeader) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hNewLeader);
		return;
	}	

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_CHANGE_LEADER, FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyLeaderChange(pResult->hNewLeader);
}

void PacketHandler_GSPartyLevelUp(void* pPacket)
{
	// ��Ƽ���� �������� �Ͽ���
	sGU_PARTY_MEMBER_LEVELED_UP_NFY* pResult = (sGU_PARTY_MEMBER_LEVELED_UP_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_LEVEL, pResult->hMember, pResult->byLevel);
	CNtlSLEventGenerator::PartyUpdate(PMT_LP, pResult->hMember, pMember->wCurLP, pResult->wMaxLP);
	CNtlSLEventGenerator::PartyUpdate(PMT_EP, pResult->hMember, pMember->wCurEP, pResult->wMaxEP);	
}

void PacketHandler_GSPartyChangeClass(void* pPacket)
{
	// ��Ƽ���� Ŭ������ �ٲ����
	sGU_PARTY_MEMBER_CLASS_CHANGED_NFY* pResult = (sGU_PARTY_MEMBER_CLASS_CHANGED_NFY*)pPacket;
	CNtlSLEventGenerator::PartyUpdate(PMT_CLASS, pResult->hMember, pResult->byNewClass);
}

void PacketHandler_GSPartyMember_LocationNfy(void* pPacket)
{
	// ��Ƽ �ɹ��� ��ġ�� ������Ʈ �Ѵ�
	sGU_PARTY_MEMBER_LOCATION_NFY* pResult = (sGU_PARTY_MEMBER_LOCATION_NFY*)pPacket;

	RwV3d vPos;
	vPos.x = pResult->vCurLoc.x;
	vPos.y = pResult->vCurLoc.y;
	vPos.z = pResult->vCurLoc.z;

	CNtlSLEventGenerator::PartyMemberLocation(pResult->hMember, pResult->worldId, pResult->worldTblidx, vPos);
}

void PacketHandler_GSPartyMemberGainedItemNfy(void *pPacket)
{
	// ��Ƽ �ɹ��� �������� ���� ���� �˷��ش�
	sGU_PARTY_MEMBER_GAINED_ITEM_NFY* pResult = (sGU_PARTY_MEMBER_GAINED_ITEM_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	if(pResult->itemTblidx == INVALID_SERIAL_ID)
	{
		// %s���� ��Ȯ�� �������� ȹ���Ͽ����ϴ�
		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVEN_ADD_UNDEFINED_ITEM_OTHER, FALSE, NULL, pwcText);
	}
	else
	{
		// %s���� ȹ�� ������ %s
		sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable(pResult->itemTblidx);
		if( !pITEM_TBLDAT )
		{
			DBO_FAIL("Not exist item table of index : " << pResult->itemTblidx);
			return;
		}

		memset((char*)awcPacketMessageBuffer, 0, sizeof(WCHAR) * dPACKET_MEESAGE_LENGTH);

		CTextTable* pItemTextTable = API_GetTableContainer()->GetTextAllTable()->GetItemTbl();
		std::wstring& strItemName = pItemTextTable->GetText(pITEM_TBLDAT->Name);		

		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_GET_ITEM, FALSE, NULL, pwcText, strItemName.c_str());
	}
}

void PacketHandler_GSPartyMemberGainedZennyNfy(void *pPacket)
{
	// ���ϸ� �й�޾Ҵٴ� �޼���
	sGU_PARTY_MEMBER_GAINED_ZENNY_NFY* pResult = (sGU_PARTY_MEMBER_GAINED_ZENNY_NFY*)pPacket;

	if( pResult->bIsShared )
	{
		// �ٸ� ��Ƽ���� ���ϸ� �־ �й�޾Ҵ�
		// %d�� %d ���ϸ� �й�޾ҽ��ϴ�
        if(pResult->dwBonusZenny == 0)
        {
		    GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_GET_ZENNY, FALSE, NULL, pResult->dwOriginalZenny, pResult->dwZenny);
        }
        else    // PC�� �߰� ȹ��
        {
            GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_GET_ZENNY_AND_BONUS, FALSE, NULL, pResult->dwOriginalZenny, pResult->dwAcquisitionZenny, pResult->dwBonusZenny);
        }
	}
	else
	{
		// �ٸ� ��Ƽ���� ���ϸ� �־���
		CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
		if( !pAvatar )
		{
			DBO_FAIL("Not exist avatar instance");
			return;
		}

		CNtlParty*		pParty	= pAvatar->GetParty();
		sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
		if( !pMember )
		{
			DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
			return;
		}

		// %s���� %d ���ϸ� ȹ���Ͽ����ϴ�
        if(pResult->dwBonusZenny == 0)
        {
		    GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_GET_ZENNY_OTHER, FALSE, NULL, pMember->wszMemberName, pResult->dwZenny);
        }
        else    // PC�� �߰� ȹ��
        {
            GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_GET_ZENNY_OTHER_AND_BONUS, FALSE, NULL, pMember->wszMemberName, pResult->dwAcquisitionZenny, pResult->dwBonusZenny);
        }
	}
}

void PacketHandler_GSPartyChangeZennyLootinMethodRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES );

	// ���� �й� ��� ���� ����� ��Ƽ�忡�� �˷��ش�
	sGU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES* pResult = (sGU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )	
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);	

	// ���� �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_CHANGE_ZENNY_DIVISION, FALSE, NULL, GetDisplayStringManager()->GetString(DST_PARTYGUI_ZENNY_LOOTING_PICKUP_PERSON + pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyZennyLootingMethodChangedNfy(void *pPacket)
{
	// ��Ƽ���� ������ �ɹ��鿡�� ���� �й� ��� ���� �˸���
	sGU_PARTY_ZENNY_LOOTING_METHOD_CHANGED_NFY* pResult = (sGU_PARTY_ZENNY_LOOTING_METHOD_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);

	// ���� �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_CHANGE_ZENNY_DIVISION, FALSE, NULL, GetDisplayStringManager()->GetString(DST_PARTYGUI_ZENNY_LOOTING_PICKUP_PERSON + pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyChangeItemLootinMethodRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES );

	// ������ �й� ��� ���� ����� ��Ƽ�忡�� �˷��ش�
	sGU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES* pResult = (sGU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);

	// ������ �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_CHANGE_ITEM_DIVISION, FALSE, NULL, GetDisplayStringManager()->GetString(DST_PARTYGUI_ITEM_LOOTING_PICKUP_PERSON + pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyItemLootingMethodChangedNfy(void *pPacket)
{
	// ��Ƽ���� ������ �ɹ��鿡�� ���� ������ �й� ��� ���� �˸���
	sGU_PARTY_ITEM_LOOTING_METHOD_CHANGED_NFY* pResult = (sGU_PARTY_ITEM_LOOTING_METHOD_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);

	// ������ �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_CHANGE_ITEM_DIVISION, FALSE, NULL, GetDisplayStringManager()->GetString(DST_PARTYGUI_ITEM_LOOTING_PICKUP_PERSON + pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyInven_ItemAddedNfy(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_ITEM_PICK_RES );

	// ��Ƽ �κ��丮�� �������� ���Դ�
	sGU_PARTY_INVENTORY_ITEM_ADDED_NFY* pResult = (sGU_PARTY_INVENTORY_ITEM_ADDED_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_ADD_ITEM, pResult->bySlotIndex, pResult->newLoot.tblidx, pResult->newLoot.byStackCount,
		pResult->newLoot.byRank, pResult->newLoot.aOptionTblidx[0], pResult->newLoot.aOptionTblidx[1], pResult->newLoot.bNeedToIdentify,
		pResult->newLoot.byGrade, pResult->newLoot.byBattleAttribute);

	if(pResult->newLoot.bNeedToIdentify)
	{
		GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_ADD_UNDEFINED_ITEM);
	}
	else
	{
		// ��Ƽ �κ��丮�� %s ȹ��
		sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable(pResult->newLoot.tblidx);		
		if( !pITEM_TBLDAT )
		{
			DBO_FAIL("Not exist item table of index : " << pResult->newLoot.tblidx);
			return;
		}

		memset((char*)awcPacketMessageBuffer, 0, sizeof(WCHAR) * dPACKET_MEESAGE_LENGTH);
		
		CTextTable* pItemTextTable = API_GetTableContainer()->GetTextAllTable()->GetItemTbl();
		std::wstring& strItemName = pItemTextTable->GetText(pITEM_TBLDAT->Name);

		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVEN_ADD_ITEM, FALSE, NULL, strItemName.c_str());
	}	
}

void PacketHandler_GSPartyInven_ItemRemovedNfy(void *pPacket)
{
	// ��Ƽ �κ��丮�� �������� �����Ǿ���
	sGU_PARTY_INVENTORY_ITEM_REMOVED_NFY* pResult = (sGU_PARTY_INVENTORY_ITEM_REMOVED_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DEL_ITEM, pResult->byPos, 0, 0, 0, 0, pResult->bIsYourItem);
}

void PacketHandler_GSPartyInven_RankSetRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_ITEM_RANK_SET_RES );

	// ��Ƽ�忡�� ��Ƽ �κ��� �����Ǵ� �������� ����� �ٲ������ �˸���
	sGU_PARTY_INVEN_ITEM_RANK_SET_RES* pResult = (sGU_PARTY_INVEN_ITEM_RANK_SET_RES*)pPacket;	

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_CHANGE_SAVED_ITEM_GRADE, 0, INVALID_SERIAL_ID, 0, pResult->byItemRank);

	const WCHAR* pwcItemRankNane = GetDisplayStringManager()->GetString(DST_ITEM_GRADE_NORMAL + pResult->byItemRank - 1);
	if( pwcItemRankNane )
		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVEN_CHANGE_ITEM_GRADE, FALSE, NULL, pwcItemRankNane);
}

void PacketHandler_GSPartyInven_RankSetNfy(void *pPacket)
{
	// ��Ƽ������ ��Ƽ �κ��� �����Ǵ� �������� ����� �ٲ������ �˸���
	sGU_PARTY_INVEN_ITEM_RANK_SET_NFY* pResult = (sGU_PARTY_INVEN_ITEM_RANK_SET_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_CHANGE_SAVED_ITEM_GRADE, 0, INVALID_SERIAL_ID, 0, pResult->byItemRank);

	const WCHAR* pwcItemRankNane = GetDisplayStringManager()->GetString(DST_ITEM_GRADE_NORMAL + pResult->byItemRank - 1);
	if( pwcItemRankNane )
		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_INVEN_CHANGE_ITEM_GRADE, FALSE, NULL, pwcItemRankNane);
}

void PacketHandler_GSPartyInven_InvestZennyRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEST_ZENNY_RES );	
	GetIconMoveManager()->IconMoveEnd();

	// �ڽ��� ��Ƽ �κ��� ��ſ� ������ ����� �˷��ش�
	sGU_PARTY_INVEST_ZENNY_RES* pResult = (sGU_PARTY_INVEST_ZENNY_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_INVEST_NOTIFY, pResult->byPos, Logic_GetAvatarHandle(), pResult->dwInvestedZenny);
}

void PacketHandler_GSPartyInven_InvestZennyNfy(void *pPacket)
{
	// ��Ƽ �κ��� ��ſ� ���� ���� ���� ������ ������ �޴´�
	sGU_PARTY_INVEST_ZENNY_NFY* pResult = (sGU_PARTY_INVEST_ZENNY_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_INVEST_NOTIFY, pResult->byPos, pResult->hMember, pResult->dwInvestedZenny);
}

void PacketHandler_GSPartyInven_LockRes(void *pPacket)
{
	// ��Ƽ �κ��� �������� ��� ���� ���� ���θ� ��Ƽ�忡�� �˷��ش�
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_LOCK_RES );

	sGU_PARTY_INVEN_LOCK_RES* pResult = (sGU_PARTY_INVEN_LOCK_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_LOCK, 0, INVALID_SERIAL_ID, 0, 0,
									   INVALID_TBLIDX, INVALID_TBLIDX, pResult->bIsOpen);

	if( pResult->bIsOpen )
		GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_OCTION_LOCK);
	else
		GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_OCTION_UNLOCK);
}

void PacketHandler_GSPartyInven_LockNfy(void *pPacket)
{
	// ��Ƽ �κ��� �������� ��� ���� ���� ���θ� ��Ƽ������ �˷��ش�
	sGU_PARTY_INVEN_LOCK_NFY* pResult = (sGU_PARTY_INVEN_LOCK_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_LOCK, 0, INVALID_SERIAL_ID, 0, 0,
									   INVALID_TBLIDX, INVALID_TBLIDX, pResult->bIsOpen);

	if( pResult->bIsOpen )
		GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_OCTION_LOCK);
	else
		GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_OCTION_UNLOCK);
}

void PacketHandler_GSPartyInven_ResetRes(void *pPacket)
{
	// ��Ƽ�忡�� ��Ƽ �κ��� ��� ������ �ʱ�ȭ�� ���� ����� �˷��ش�
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_RESET_RES );

	sGU_PARTY_INVEN_RESET_RES* pResult = (sGU_PARTY_INVEN_RESET_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_RESET, 0);
	GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_OCTION_RESET);
}

void PacketHandler_GSPartyInven_ResetNfy(void *pPacket)
{
	// ��Ƽ������ ��Ƽ �κ��� ��� ������ �ʱ�ȭ �Ǿ����� �˸���
	//sGU_PARTY_INVEN_RESET_NFY* pResult = (sGU_PARTY_INVEN_RESET_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_RESET, 0);
	GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_OCTION_RESET);
}

void PacketHandler_GSPartyInven_AcceptedRes(void *pPacket)
{
	// ��Ƽ�忡�� ��� ������ �� ����� �˷��ش�
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_ACCEPTED_RES );

	sGU_PARTY_INVEN_ACCEPTED_RES* pResult = (sGU_PARTY_INVEN_ACCEPTED_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_SUCCESSFUL_BID, pResult->byItemSlot, pResult->hTarget);
}

void PacketHandler_GSPartyInven_AcceptedNfy(void *pPacket)
{
	// ��Ƽ������ ��Ű� �����Ǿ����� �˸���
	sGU_PARTY_INVEN_ACCEPTED_NFY* pResult = (sGU_PARTY_INVEN_ACCEPTED_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_OCTION_SUCCESSFUL_BID, pResult->byItemSlot, pResult->hTarget);
}

void PacketHandler_GSPartyInven_GiveRes(void *pPacket)
{
	// ��Ƽ �κ��� �������� ��Ƽ���� ���� �й��� ����� ��Ƽ�忡�� �˷��ش�
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_GIVE_RES );

	sGU_PARTY_INVEN_GIVE_RES* pResult = (sGU_PARTY_INVEN_GIVE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_LEADER, pResult->byItemSlot, pResult->hTarget);
}

void PacketHandler_GSPartyInven_GiveNfy(void *pPacket)
{
	// ��Ƽ �κ��� �������� ��Ƽ���� ���� �й��� ��� ��Ƽ������ �˷��ش�
	sGU_PARTY_INVEN_GIVE_NFY* pResult = (sGU_PARTY_INVEN_GIVE_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_LEADER, pResult->byItemSlot, pResult->hTarget);
}

void PacketHandler_GSPartyInven_DiceStartRes(void *pPacket)
{
	// ��Ƽ���� ��Ƽ �κ��� �������� �ֻ��� �����⸦ ������ ����� �˷��ش�
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_DICE_START_RES );

	sGU_PARTY_INVEN_DICE_START_RES* pResult = (sGU_PARTY_INVEN_DICE_START_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_DICE_START, pResult->byItemSlot);
	GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_START_DICE);
}

void PacketHandler_GSPartyInven_DiceStartNfy(void *pPacket)
{
	// ��Ƽ������ ��Ƽ �κ��� �������� �ֻ��� �����⸦ ���������� �˸���
	sGU_PARTY_INVEN_DICE_START_NFY* pResult = (sGU_PARTY_INVEN_DICE_START_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_DICE_START, pResult->byItemSlot);
	GetAlarmManager()->AlarmMessage(DST_PARTY_INVEN_START_DICE);
}

void PacketHandler_GSPartyInven_DiceRollRes(void *pPacket)
{
	// ��Ƽ �κ��� �������� �й踦 ���� �ڽ��� ���� �ֻ����� ����� �˷��ش�
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVEN_DICE_ROLL_RES );

	sGU_PARTY_INVEN_DICE_ROLL_RES* pResult = (sGU_PARTY_INVEN_DICE_ROLL_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::DiceResult(Logic_GetAvatarHandle(), DICE_WORKD_ID_PARTY_INVEN_DICE, pResult->byRet);
}

void PacketHandler_GSPartyInven_DiceRollNfy(void *pPacket)
{
	// ��Ƽ �κ��� �������� �й踦 ���� ��Ƽ���� ���� �ֻ����� ����� �˷��ش�
	sGU_PARTY_INVEN_DICE_ROLL_NFY* pResult = (sGU_PARTY_INVEN_DICE_ROLL_NFY*)pPacket;

	CDboEventGenerator::DiceResult(pResult->handle, DICE_WORKD_ID_PARTY_INVEN_DICE, pResult->byRet);
}

void PacketHandler_GSPartyInven_DiceEndNfy(void *pPacket)
{
	// ��Ƽ �κ��� ������ �й踦 ���� ��Ƽ �ֻ��� �����⸦ �� ����� �˷��ش�
	sGU_PARTY_INVEN_DICE_END_NFY* pResult = (sGU_PARTY_INVEN_DICE_END_NFY*)pPacket;

	CDboEventGenerator::PartyInventory(PINVEN_DIVIDE_BY_DICE_RESULT, 0, pResult->hTarget);
}

void PacketHandler_GSPartyCharm_OpenRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_OPEN_CHARM_SLOT_RES );

	// ��Ƽ ������ �ڽ��� ��Ƽ ����â�� ������
	sGU_PARTY_OPEN_CHARM_SLOT_RES* pResult = (sGU_PARTY_OPEN_CHARM_SLOT_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_LEADER_CHARM_OPEN);
	CDboEventGenerator::PartyCharm(PCET_OPEN, pResult->byCharmInventoryIndex);
}

void PacketHandler_GSPartyCharm_OpenedNfy(void *pPacket)
{
	// ��Ƽ ������ ��Ƽ ����â�� ��� �ɹ��鵵 ���� ������
	sGU_PARTY_CHARM_SLOT_OPENED_NFY* pResult = (sGU_PARTY_CHARM_SLOT_OPENED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_LEADER_CHARM_OPEN);
	CDboEventGenerator::PartyCharm(PCET_OPEN, pResult->byCharmInventoryIndex);
}

void PacketHandler_GSPartyCharm_CloseRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CLOSE_CHARM_SLOT_RES );

	// ��Ƽ ������ �ڽ��� ��Ƽ ����â�� �ݾҴ�
	sGU_PARTY_CLOSE_CHARM_SLOT_RES* pResult = (sGU_PARTY_CLOSE_CHARM_SLOT_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_LEADER_CHARM_CLOSE);
	CDboEventGenerator::PartyCharm(PCET_CLOSE);
}

void PacketHandler_GSPartyCharm_CloseNfy(void *pPacket)
{
	// ��Ƽ ������ ��Ƽ ����â�� �ݾƼ� �ɹ��鵵 ���� ������
	//sGU_PARTY_CHARM_SLOT_CLOSED_NFY* pResult = (sGU_PARTY_CHARM_SLOT_CLOSED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_LEADER_CHARM_CLOSE);
	CDboEventGenerator::PartyCharm(PCET_CLOSE);
}

void PacketHandler_GSPartyCharm_RegVictimItemRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_REGISTER_VICTIM_ITEM_RES );

	// ���� ����� ��Ƽ ���� �������� ��� ó�� ����� ���� ������ ���� �Ǵ�.
	sGU_PARTY_REGISTER_VICTIM_ITEM_RES* pResult = (sGU_PARTY_REGISTER_VICTIM_ITEM_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}		

	GetIconMoveManager()->IconMoveEnd();

	// UI�� ���
	RwInt8 iBagIndex = Logic_ConvertContainerTypeToBagIdx(pResult->bySrcPlace);

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlInventory* pInventory = pAvatar->GetInventory();
	SERIAL_HANDLE hBagHandle = pInventory->GetBagItem(iBagIndex);
	CNtlSobItem* pBag = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject(hBagHandle));

	if( !pBag )
	{
		DBO_FAIL("Not exist sob item of handle : " << hBagHandle);
		return;
	}
	
	SERIAL_HANDLE hItemHandle = pBag->GetChildSerial(pResult->bySrcPos);
	sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromSob(hItemHandle);
	if( !pITEM_TBLDAT )
	{
		DBO_FAIL("Not exist item table of index : " << hItemHandle);
		return;
	}

	CDboEventGenerator::PartyVictim(PVI_REG_CHARM, pITEM_TBLDAT->tblidx,
		pResult->byDestSlotIndex, iBagIndex, pResult->bySrcPos, TRUE);

	// %s���� %s ���
	const WCHAR* pwcText = Logic_GetAvatarName();	
	CTextTable* pItemTextTable = API_GetTableContainer()->GetTextAllTable()->GetItemTbl();	
	std::wstring& strItemName = pItemTextTable->GetText(pITEM_TBLDAT->Name);

	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_REG_VICTIM_ITEM, FALSE, NULL, pwcText, strItemName.c_str());
}

void PacketHandler_GSPartyCharm_RegVictimItemNfy(void *pPacket)
{
	// ��Ƽ ���� �������� ����� �Ǿ���.
	sGU_PARTY_VICTIM_ITEM_REGISTERED_NFY* pResult = (sGU_PARTY_VICTIM_ITEM_REGISTERED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;	

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember	= reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable(pResult->itemInfo.itemTblidx);	
	if( !pITEM_TBLDAT )
	{
		DBO_FAIL("Not exist item table of index : " << pResult->itemInfo.itemTblidx);
		return;
	}

	// ���� ���
	CDboEventGenerator::PartyVictim(PVI_REG_CHARM, pResult->itemInfo.itemTblidx, pResult->itemInfo.bySlotIndex);

	CTextTable* pItemTextTable = API_GetTableContainer()->GetTextAllTable()->GetItemTbl();
	std::wstring& strItemName = pItemTextTable->GetText(pITEM_TBLDAT->Name);
	
	// %s���� %s ���
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_REG_VICTIM_ITEM, FALSE, NULL, pwcText, strItemName.c_str());
}

void PacketHandler_GSPartyCharm_UnRegVictimItemRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_UNREGISTER_VICTIM_ITEM_RES );

	// ���� ����ߴ� ��Ƽ ���� �Ǵ� ���� �������� ��� ���� ����� ���� ������ ���� �����Ѵ�.
	sGU_PARTY_UNREGISTER_VICTIM_ITEM_RES* pResult = (sGU_PARTY_UNREGISTER_VICTIM_ITEM_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	// ��Ƽ ���� ������ ������ ����
	CDboEventGenerator::PartyVictim(PVI_UNREG_CHARM, pResult->byDestSlotIndex);	
}

void PacketHandler_GSPartyCharm_UnRegVictimItemNfy(void *pPacket)
{
	// ��Ƽ ���� �Ǵ� ���� �������� �����Ǿ���.
	sGU_PARTY_VICTIM_ITEM_UNREGISTERED_NFY* pResult = (sGU_PARTY_VICTIM_ITEM_UNREGISTERED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;	

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember	= reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}	

	// %s���� %s ��� ���(���� ����)
	sITEM_TBLDAT* pItem_TBLDAT = Logic_GetItemDataFromTable(pResult->itemTblidx);
	if( !pItem_TBLDAT )
	{
		DBO_FAIL("Not exist item table of handle : " << pResult->itemTblidx);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// ���� ������ ����
	CDboEventGenerator::PartyVictim(PVI_UNREG_CHARM, pResult->byDestSlotIndex);	

	CTextTable* pItemTextTable = API_GetTableContainer()->GetTextAllTable()->GetItemTbl();
	std::wstring& strItemName = pItemTextTable->GetText(pItem_TBLDAT->Name);
	GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_UNREG_VICTIM_ITEM, FALSE, NULL, pwcText, strItemName.c_str());
}

void PacketHandler_GSPartyCharm_DeclareZennyRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DECLARE_ZENNY_RES );

	// �ڽ��� ���� ����� ���� ���ϸ� ����ߴ�
	sGU_PARTY_DECLARE_ZENNY_RES* pResult = (sGU_PARTY_DECLARE_ZENNY_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	GetIconMoveManager()->IconMoveEnd();

	if( pResult->dwInitialZenny == pResult->dwFinalDeclaredZenny )
	{
		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_DECLARE_ZENNY, FALSE, NULL, pResult->dwFinalDeclaredZenny);
	}
	else
	{
		GetAlarmManager()->FormattedAlarmMessage(DST_PARTY_DECLARE_ZENNY_PART, FALSE, NULL, pResult->dwInitialZenny, pResult->dwFinalDeclaredZenny);
	}

	CDboEventGenerator::PartyVictim(PVI_ZENNY, Logic_GetAvatarHandle(), pResult->dwFinalDeclaredZenny);
}

void PacketHandler_GSPartyCharm_DeclareZennyNfy(void *pPacket)
{
	// ��Ƽ���� ���� ����� ���� ���ϸ� ����ߴ�
	sGU_PARTY_DECLARED_ZENNY_CHANGED_NFY* pResult = (sGU_PARTY_DECLARED_ZENNY_CHANGED_NFY*)pPacket;
	CDboEventGenerator::PartyVictim(PVI_ZENNY, pResult->hMember, pResult->dwDeclaredZenny);
}

void PacketHandler_GSPartyCharm_Activation_Failed_Nfy(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_ACTIVATE_CHARM_RES );

	// ��Ƽ �������� ��Ƽ�� �ߵ� ���и� �˸���
	sGU_PARTY_CHARM_ACTIVATION_FAILED_NFY* pResult = (sGU_PARTY_CHARM_ACTIVATION_FAILED_NFY*)pPacket;
	
	if( pResult->hMember == INVALID_SERIAL_ID )
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
	else
	{
		CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
		if( !pAvatar )
			return;	

		CNtlParty*		pParty	= pAvatar->GetParty();
		sPartyMember*	pMember	= reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
		if( !pMember )
		{
			DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
			return;
		}

		GetAlarmManager()->FormattedAlarmMessage(pResult->wResultCode, TRUE, NULL, pMember->wszMemberName);
	}
}

void PacketHandler_GSPartyCharm_ActivateRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_ACTIVATE_CHARM_RES );

	// ��Ƽ �������� ��Ƽ ���� �ߵ� ����� �˷��ش�
	sGU_PARTY_ACTIVATE_CHARM_RES* pResult = (sGU_PARTY_ACTIVATE_CHARM_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyCharm(PCET_ACTIVATE, pResult->byCharmInventoryIndex, pResult->registeredCharmTblidx);

	CNtlSLEventGenerator::PartyCharmActivity(PCAT_ACTIVE, pResult->byCharmInventoryIndex, pResult->registeredCharmTblidx, (RwReal)pResult->dwRemainingTime);
}

void PacketHandler_GSPartyCharm_ActivateNfy(void *pPacket)
{
	// ��Ƽ ������ �ߵ��Ǿ����� �˷��ش�
	sGU_PARTY_CHARM_ACTIVATED_NFY* pResult = (sGU_PARTY_CHARM_ACTIVATED_NFY*)pPacket;

	CDboEventGenerator::PartyCharm(PCET_ACTIVATE, pResult->byCharmInventoryIndex, pResult->registeredCharmTblidx);

	CNtlSLEventGenerator::PartyCharmActivity(PCAT_ACTIVE, pResult->byCharmInventoryIndex, pResult->registeredCharmTblidx, (RwReal)pResult->dwRemainingTime);
}

void PacketHandler_GSPartyCharm_DeActivateCharmRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DEACTIVATE_CHARM_RES );

	// ��Ƽ �������� ��Ƽ ������ ��ҵǾ����� �˸���
	sGU_PARTY_DEACTIVATE_CHARM_RES* pResult = (sGU_PARTY_DEACTIVATE_CHARM_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::PartyCharm(PCET_UNDISPLAY_CHARM_BUFF, pResult->byCharmInventoryIndex);

	CNtlSLEventGenerator::PartyCharmActivity(PCAT_RELEASE, pResult->byCharmInventoryIndex);
}

void PacketHandler_GSPartyCharm_DeActivateCharmNfy(void *pPacket)
{
	// ��Ƽ �ɹ��鿡�� ��Ƽ ������ ��ҵǾ����� �˸���
	sGU_PARTY_CHARM_DEACTIVATED_NFY* pResult = (sGU_PARTY_CHARM_DEACTIVATED_NFY*)pPacket;

	CDboEventGenerator::PartyCharm(PCET_UNDISPLAY_CHARM_BUFF, pResult->byCharmInventoryIndex);

	CNtlSLEventGenerator::PartyCharmActivity(PCAT_RELEASE, pResult->byCharmInventoryIndex);
}

void PacketHandler_GSPartyCharm_DiceStart_Nfy(void* pPacket)
{
	//sGU_PARTY_CHARM_DEACTIVATED_NFY* pResult = (sGU_PARTY_CHARM_DEACTIVATED_NFY*)pPacket;

	CDboEventGenerator::PartyVictim(PVI_START_CHARM_DICE);	
}

void PacketHandler_GSPartyCharm_DiceRolled_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHARM_DICE_ROLLED_RES );

	sGU_PARTY_CHARM_DICE_ROLLED_RES* pResult = (sGU_PARTY_CHARM_DICE_ROLLED_RES*)pPacket;

	CDboEventGenerator::DiceResult(Logic_GetAvatarHandle(), DICE_WORKD_ID_PARTY_CHARM_DICE, (RwUInt8)pResult->dwRet);
}

void PacketHandler_GSPartyCharm_DiceRolled_Nfy(void* pPacket)
{
	sGU_PARTY_CHARM_DICE_ROLLED_NFY* pResult = (sGU_PARTY_CHARM_DICE_ROLLED_NFY*)pPacket;

	CDboEventGenerator::DiceResult(pResult->handle, DICE_WORKD_ID_PARTY_CHARM_DICE, (RwUInt8)pResult->dwRet);
}

void PacketHandler_GSPartyCharm_DiceEnd_Nfy(void* pPacket)
{
	sGU_PARTY_CHARM_DICE_END_NFY* pResult = (sGU_PARTY_CHARM_DICE_END_NFY*)pPacket;

	if( pResult->bIsSuccess )
		CDboEventGenerator::FlashNotifyString("Lucky.swf");
	else
		GetAlarmManager()->AlarmMessage(DST_PARTY_CHARM_START_DICE_RESULT_FAIL);
}

// ��Ƽ ���� Ÿ�� ��û�� ���� ��� ��Ŷ
void PacketHandler_GSPartyShareTargetRes( void* pPacket ) 
{
    sGU_PARTY_SHARETARGET_RES* pData = (sGU_PARTY_SHARETARGET_RES*)pPacket;
    if( pData->wResultCode != GAME_SUCCESS )
    {
        GetAlarmManager()->AlarmMessage( pData->wResultCode, TRUE );
        return;
    }

    CNtlSLEventGenerator::PartyShareTargetRes(pData->wResultCode);
}

// ��Ƽ ���� Ÿ�� ���ÿ� ���� �˸� ��Ŷ
void PacketHandler_GSPartyShareTargetNfy( void* pPacket ) 
{
    sGU_PARTY_SHARETARGET_NFY* pData = (sGU_PARTY_SHARETARGET_NFY*)pPacket;

    CNtlSLEventGenerator::PartyShareTargetNfy(pData->sharetargetInfo);
}

void PacketHandler_GSPartyDungeonDiffRes(void *pPacket)
{
	// ��Ƽ�忡�� ��Ƽ ������ ���̵� ���� ����� �˸���
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DUNGEON_DIFF_RES );

	sGU_PARTY_DUNGEON_DIFF_RES* pResult = (sGU_PARTY_DUNGEON_DIFF_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_STATE, INVALID_SERIAL_ID, pResult->eDiff);	

	GetAlarmManager()->AlarmMessage(DST_PARTY_DUNGEON_CHANGE_NORMAL + pResult->eDiff);
}

void PacketHandler_GSPartyDungeonDiffNfy(void *pPacket)
{
	// ��Ƽ���鿡�� ��Ƽ ���� ���̵� ������ �˸���
	sGU_PARTY_DUNGEON_DIFF_NFY* pResult = (sGU_PARTY_DUNGEON_DIFF_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_STATE, INVALID_SERIAL_ID, pResult->eDiff);	
	
	GetAlarmManager()->AlarmMessage(DST_PARTY_DUNGEON_CHANGE_NORMAL + pResult->eDiff);
}

void PacketHandler_GSPartyDungeonInitRes(void *pPacket)
{
	// ��Ƽ�忡�� ��Ƽ ���� �ʱ�ȭ ����� �˸���
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DUNGEON_INIT_RES );

	sGU_PARTY_DUNGEON_INIT_RES* pResult = (sGU_PARTY_DUNGEON_INIT_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_INITIALIZE);

	GetAlarmManager()->AlarmMessage(DST_PARTY_DUNGEON_INITIALIZE);
}

void PacketHandler_GSPartyDungeonInitNfy(void *pPacket)
{
	// ��Ƽ������ ��Ƽ ���� �ʱ�ȭ�� �˸���
	//sGU_PARTY_DUNGEON_INIT_NFY* pResult = (sGU_PARTY_DUNGEON_INIT_NFY*)pPacket;

	GetAlarmManager()->AlarmMessage(DST_PARTY_DUNGEON_INITIALIZE);
}