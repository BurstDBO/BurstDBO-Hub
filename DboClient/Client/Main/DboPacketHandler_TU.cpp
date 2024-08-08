/*****************************************************************************
* File			: DboPackethandler_TU.cpp
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2007. 1. 16
* Abstract		: 
*****************************************************************************
* Desc         : Ŀ�´�Ƽ ���� ��Ŷ �ڵ�
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboPacketHandler.h"

// simulation
#include "NtlNetSender.h"
#include "NtlSLEventFunc.h"
#include "NtlSLPacketGenerator.h"
#include "NtlBudokai.h"

// cleint
#include "PetitionManager.h"
#include "GMChatGui.h"
#include "DialogManager.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// chatting server packethandler

void PacketHandler_TSChatEnterRes(void *pPacket)
{
	sTU_ENTER_CHAT_RES *pEnterRes = (sTU_ENTER_CHAT_RES*)pPacket;

	if(pEnterRes->wResultCode != CHAT_SUCCESS)
	{
		CNtlSLEventGenerator::SysMsg(INVALID_SERIAL_ID, pEnterRes->wResultCode);
		return;
	}
}

void PacketHandler_TSChatDisconnectNfy(void *pPacket)
{
	// Ŀ�´�Ƽ ���� ������ ���� �ƹ��� ó���� ���� �ʱ�� �Ͽ���.
	// ���, õ�����Ϲ���ȸ, ä�� ���� ��������� �����
	//sTU_DISCONNECTED_NFY* pEnterRes = (sTU_DISCONNECTED_NFY*)pPacket; 

	SConnectData* pConnectData = GetDboGlobal()->GetConnectData();
	pConnectData->sChatCon.bBanishment = TRUE;
}

void PacketHandler_TSChatMsgSay(void *pPacket)
{
    sTU_CHAT_MESSAGE_SAY *pMsgSay = (sTU_CHAT_MESSAGE_SAY*)pPacket;
    
    // ������Ʈ(����) üũ 
    if(GetNtlSLGlobal()->GetSobAvatar()->GetBlackList()->GetMemberbyName(pMsgSay->awchSenderCharName))
        return;

	CDboEventGenerator::SayMessage(CHAT_TYPE_GENERAL, pMsgSay->awchSenderCharName, pMsgSay->wMessageLengthInUnicode, pMsgSay->awchMessage, pMsgSay->hSubject);
}

void PacketHandler_TSChatMsgShout(void *pPacket)
{
	sTU_CHAT_MESSAGE_SHOUT *pMsgShout = (sTU_CHAT_MESSAGE_SHOUT*)pPacket;

    // ������Ʈ(����) üũ 
    if(GetNtlSLGlobal()->GetSobAvatar()->GetBlackList()->GetMemberbyName(pMsgShout->awchSenderCharName))
        return;

	CDboEventGenerator::SayMessage(CHAT_TYPE_SHOUT, pMsgShout->awchSenderCharName, pMsgShout->wMessageLengthInUnicode, pMsgShout->awchMessage, pMsgShout->hSubject);
}

void PacketHandler_TSChatMsgWhisper(void *pPacket)
{
	sTU_CHAT_MESSAGE_WHISPER *pMsgWhisper = (sTU_CHAT_MESSAGE_WHISPER*)pPacket;

    // ������Ʈ(����) üũ 
    if(GetNtlSLGlobal()->GetSobAvatar()->GetBlackList()->GetMemberbyName(pMsgWhisper->awchSenderCharName))
        return;

	CDboEventGenerator::SayMessage(CHAT_TYPE_WHISPER, pMsgWhisper->awchSenderCharName, pMsgWhisper->wMessageLengthInUnicode, pMsgWhisper->awchMessage);
}

void PacketHandler_TSChatMsgWhisperFailNfy(void *pPacket)
{
	sTU_CHAT_MESSAGE_WHISPER_FAILED_NFY *pMsgWhisperFail = (sTU_CHAT_MESSAGE_WHISPER_FAILED_NFY*)pPacket;

	GetAlarmManager()->FormattedAlarmMessage( DST_CHAT_FAIL_TO_WHISPER_NO_TARGET, FALSE, NULL, pMsgWhisperFail->awchReceiverCharName );
}

void PacketHandler_TSChatMsgParty(void *pPacket)
{
	sTU_CHAT_MESSAGE_PARTY *pMsgParty = (sTU_CHAT_MESSAGE_PARTY*)pPacket;

    // ������Ʈ(����) üũ 
    if(GetNtlSLGlobal()->GetSobAvatar()->GetBlackList()->GetMemberbyName(pMsgParty->awchSenderCharName))
        return;

	CDboEventGenerator::SayMessage(CHAT_TYPE_PARTY, pMsgParty->awchSenderCharName, pMsgParty->wMessageLengthInUnicode, pMsgParty->awchMessage, pMsgParty->hSubject);

	if( pMsgParty->byChattingType == DBO_CHATTING_TYPE_PARTY_NOTICE )
		CDboEventGenerator::GroupNotify(GROUP_NOTIFY_PARTY, pMsgParty->awchMessage);
}

void PacketHandler_TSChatMsgGuild(void *pPacket)
{
	sTU_CHAT_MESSAGE_GUILD *pMsgGuild = (sTU_CHAT_MESSAGE_GUILD*)pPacket;

    // ������Ʈ(����) üũ 
    if(GetNtlSLGlobal()->GetSobAvatar()->GetBlackList()->GetMemberbyName(pMsgGuild->wszSenderCharName))
        return;

	CDboEventGenerator::SayMessage(CHAT_TYPE_GUILD, pMsgGuild->wszSenderCharName, pMsgGuild->wMessageLengthInUnicode, pMsgGuild->awchMessage);

	if( pMsgGuild->byChattingType == DBO_CHATTING_TYPE_GUILD_SCRAMBLE_NOTICE )
		CDboEventGenerator::GroupNotify(GROUP_NOTIFY_GUILD, pMsgGuild->awchMessage);
}

void PacketHandler_TSPetitionUserInsertRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_PETITION_USER_INSERT_RES);
	CDboEventGenerator::PetitionEvent(PETITON_ENABLE_PETITON_GUI);

	// ������ ���� ������ ���� ����� ����
	sTU_PETITION_USER_INSERT_RES* pResult = (sTU_PETITION_USER_INSERT_RES*)pPacket;

	if( pResult->wResultCode != GAME_GM_TOOL_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}
	
	GetPetitionManager()->SetPetitionID(pResult->petitionID);	
	CDboEventGenerator::PetitionEvent(PETITON_REQUEST_OK);
	CDboEventGenerator::PetitionEvent(PETITON_CLOSE_DILAOG);
}

void PacketHandler_TSPetitionModifyRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_PETITION_CONTENT_MODIFY_RES);
	CDboEventGenerator::PetitionEvent(PETITON_ENABLE_PETITON_GUI);

	// �̹� ���� ������ ���� ���
	sTU_PETITION_CONTENT_MODIFY_RES* pResult = (sTU_PETITION_CONTENT_MODIFY_RES*)pPacket;

	if( pResult->wResultCode != GAME_GM_TOOL_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}
	
	CDboEventGenerator::PetitionEvent(PETITON_MODIFY_OK);
	CDboEventGenerator::PetitionEvent(PETITON_CLOSE_DILAOG);
}

void PacketHandler_TSPetitionUserCancelRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_PETITION_USER_CANCEL_RES);

	// ���� ���
	sTU_PETITION_USER_CANCEL_RES* pResult = (sTU_PETITION_USER_CANCEL_RES*)pPacket;

	if( pResult->wResultCode != GAME_GM_TOOL_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}

	GetPetitionManager()->FinishPetition();
		
	CDboEventGenerator::PetitionEvent(PETITON_CANCEL);
	CDboEventGenerator::PetitionEvent(PETITON_CLOSE_DILAOG);
}

void PacketHandler_TSPetitionFinishNfy(void *pPacket)
{
	//sTU_PETITION_FINISH_NFY* pResult = (sTU_PETITION_FINISH_NFY*)pPacket;

	GetPetitionManager()->FinishPetition();

	CDboEventGenerator::PetitionEvent(PETITON_FINISH);
	CDboEventGenerator::PetitionEvent(PETITON_CLOSE_DILAOG);
}

void PacketHandler_TSPetitionChatStartReq(void *pPacket)
{
	// GM���� ���� GM ä�� ��û�� �޾Ҵ�.
	sTU_PETITION_CHAT_START_REQ* pResult = (sTU_PETITION_CHAT_START_REQ*)pPacket;
	
	GetPetitionManager()->StartGMChatting(pResult->petitionID, pResult->gmAccountID, pResult->awchGMCharName_Consult, pResult->bNeedSatisfactionRate);
	CDboEventGenerator::PetitionEvent(PETITON_CHATTING_START);
}

void PacketHandler_TSPetitionChatGMSayReq(void *pPacket)
{
	// GM���� ���� GM ä�� �޼����� �޾Ҵ�
	sTU_PETITION_CHAT_GM_SAY_REQ* pResult = (sTU_PETITION_CHAT_GM_SAY_REQ*)pPacket;

	if( GetPetitionManager()->GetChattingGMID() == INVALID_ACCOUNTID )
	{
		// TU_PETITION_CHAT_START_REQ��Ŷ�� ������ ���� ���� �ʾҴ�
		GetDboGlobal()->GetChatPacketGenerator()->SendPetitionChatGMSayRes(PETITION_NOT_STARTED_CLEINT_GM_CHAT, pResult->gmAccountID);
		return;
	}

	if( GetPetitionManager()->GetChattingGMID() != pResult->gmAccountID )
	{
		// �̹� ä������ GM�� ID�� �ƴϴ�
		GetDboGlobal()->GetChatPacketGenerator()->SendPetitionChatGMSayRes(PETITION_DIFFERENT_CHAATING_GM_ID, pResult->gmAccountID);
		return;
	}

	GetDboGlobal()->GetChatPacketGenerator()->SendPetitionChatGMSayRes(CHAT_SUCCESS, pResult->gmAccountID);

	CGMChatGui* pGMChatGui = reinterpret_cast<CGMChatGui*>( GetDialogManager()->GetDialog(DIALOG_GM_CHATTING) );
	if( !pGMChatGui )
		return;

	pGMChatGui->SetGMText( pResult->awchMessage );
}

void PacketHandler_TSPetitionChatUserSayRes(void *pPacket)
{
	// GM���� ���� �ڽ��� �޼����� ���
	sTU_PETITION_CHAT_USER_SAY_RES* pResult = (sTU_PETITION_CHAT_USER_SAY_RES*)pPacket;

	if( pResult->wResultCode != GAME_GM_TOOL_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );
		return;
	}
}

void PacketHandler_TSPetitionChatGMEndNfy(void *pPacket)
{
	// GM�� GM ä���� �����Ͽ���
	//sTU_PETITION_CHAT_GM_END_NFY* pResult = (sTU_PETITION_CHAT_GM_END_NFY*)pPacket;

	CDboEventGenerator::PetitionEvent(PETITON_CHATTING_END);
	GetPetitionManager()->EndGMChatting();
}

void PacketHandler_TUFreind_Add_Res( void* pPacket ) 
{
	API_GetSLPacketLockManager()->Unlock(TU_FRIEND_ADD_RES);

	sTU_FRIEND_ADD_RES* pResult = (sTU_FRIEND_ADD_RES*)pPacket;

    CNtlSLEventGenerator::FriendAddRes(pResult->wResultCode, pResult->wchName, pResult->targetID);
}

void PacketHandler_TUFriend_Del_Res( void* pPacket ) 
{
    API_GetSLPacketLockManager()->Unlock(TU_FRIEND_DEL_RES);

    sTU_FRIEND_DEL_RES* pResult = (sTU_FRIEND_DEL_RES*)pPacket;

    CNtlSLEventGenerator::FriendDelRes(pResult->wResultCode, pResult->targetID);
}

void PacketHandler_TUFriend_Move_Res( void* pPacket ) 
{
    API_GetSLPacketLockManager()->Unlock(TU_FRIEND_MOVE_RES);

    sTU_FRIEND_MOVE_RES* pResult = (sTU_FRIEND_MOVE_RES*)pPacket;

    CNtlSLEventGenerator::FriendMoveRes(pResult->wResultCode, pResult->targetID);
}

void PacketHandler_TUFriend_List_Info( void* pPacket ) 
{
    sTU_FRIEND_LIST_INFO* pResult = (sTU_FRIEND_LIST_INFO*)pPacket;

    CNtlSLEventGenerator::FriendListInfo(pResult->byCount, pResult->asInfo);
}

void PacketHandler_TUFriend_BlackAdd_Res( void* pPacket ) 
{
    API_GetSLPacketLockManager()->Unlock(TU_FRIEND_BLACK_ADD_RES);

    sTU_FRIEND_BLACK_ADD_RES* pResult = (sTU_FRIEND_BLACK_ADD_RES*)pPacket;

    CNtlSLEventGenerator::BlackListAddRes(pResult->wResultCode, pResult->wchName, pResult->targetID);
}

void PacketHandler_TUFriend_BlackDel_Res( void* pPacket ) 
{
    API_GetSLPacketLockManager()->Unlock(TU_FRIEND_BLACK_DEL_RES);

    sTU_FRIEND_BLACK_DEL_RES* pResult = (sTU_FRIEND_BLACK_DEL_RES*)pPacket;
   
    CNtlSLEventGenerator::BlackListDelRes(pResult->wResultCode, pResult->targetID);
}

void PacketHandler_TUFriend_Info( void* pPacket ) 
{
    sTU_FRIEND_INFO* pResult = (sTU_FRIEND_INFO*)pPacket;
    
    CNtlSLEventGenerator::FriendInfo(&pResult->sInfo, pResult->bIsFirst);
}

void PacketHandler_TUFriend_Info_Change( void* pPacket ) 
{
    sTU_FRIEND_INFO_CHANGE* pResult = (sTU_FRIEND_INFO_CHANGE*)pPacket;

    CNtlSLEventGenerator::FriendInfoChange(pResult->targetID, pResult->byChangeType, pResult->dwChangeValue);
}



void PacketHandler_TUChatMessagePrivateShopBusiness( void* pPacket ) 
{
	sTU_CHAT_MESSAGE_PRIVATESHOP_BUSINESS* pChat = (sTU_CHAT_MESSAGE_PRIVATESHOP_BUSINESS*)pPacket;

	CNtlSLEventGenerator::ChatMessagePrivateShopBusiness( pChat->awchSenderCharName, 
		pChat->wMessageLengthInUnicode,
		pChat->awchMessage );
}

void PacketHandler_TUBudokai_Notice_Nfy(void* pPacket)
{
	sTU_BUDOKAI_NOTICE_NFY* pNotify = (sTU_BUDOKAI_NOTICE_NFY*)pPacket;

	if( pNotify->byNoticeType == BUDOKAI_NOTICE_GM )
	{
		if( pNotify->sGmNotice.byNoticeLength > BUDOKAI_MAX_NOTICE_LENGTH )
			return;
		
		WCHAR awcBuffer[BUDOKAI_MAX_NOTICE_LENGTH+1];
		
		::CopyMemory( awcBuffer, pNotify->sGmNotice.wszNotice, sizeof(WCHAR) * pNotify->sGmNotice.byNoticeLength );
		awcBuffer[pNotify->sGmNotice.byNoticeLength/sizeof(WCHAR)] = L'\0';

		CDboEventGenerator::NotifyMessage( SDboEventNotify::NPC, awcBuffer );
	}

	CNtlSLEventGenerator::BudokaiNoticeNfy(pNotify->byNoticeType, pNotify->tblidxNotice, reinterpret_cast<void*>(pNotify->sGmNotice.wszNotice));
}

void PacketHandler_TUBudokaiTournamentIndividualListRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_BUDOKAI_TOURNAMENT_INDIVIDUAL_LIST_RES );

	sTU_BUDOKAI_TOURNAMENT_INDIVIDUAL_LIST_RES* pList = (sTU_BUDOKAI_TOURNAMENT_INDIVIDUAL_LIST_RES*)pPacket;

	if( pList->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pList->wResultCode, TRUE );
	}

	CDboEventGenerator::BudokaiTournamentIndividualList( pList->wEntryTeam, pList->byMatchDataCount, pList->wMatchData, &pList->sData );
}

void PacketHandler_TUBudokaiTournamentIndividualInfoRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_BUDOKAI_TOURNAMENT_INDIVIDUAL_INFO_RES );

	sTU_BUDOKAI_TOURNAMENT_INDIVIDUAL_INFO_RES* pInfo = (sTU_BUDOKAI_TOURNAMENT_INDIVIDUAL_INFO_RES*)pPacket;

	if( pInfo->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pInfo->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::BudokaiTournamentIndividualInfo( pInfo->awTeamType, &pInfo->sData );	
}

void PacketHandler_TUBudokaiTournamentTeamListRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_BUDOKAI_TOURNAMENT_TEAM_LIST_RES );

	sTU_BUDOKAI_TOURNAMENT_TEAM_LIST_RES* pList = (sTU_BUDOKAI_TOURNAMENT_TEAM_LIST_RES*)pPacket;

	if( pList->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pList->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::BudokaiTournamentTeamList( pList->wEntryTeam, pList->byMatchDataCount, pList->wMatchData, &pList->sData );	
}

void PacketHandler_TUBudokaiTournamentTeamInfoRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_BUDOKAI_TOURNAMENT_TEAM_INFO_RES );

	sTU_BUDOKAI_TOURNAMENT_TEAM_INFO_RES* pInfo = (sTU_BUDOKAI_TOURNAMENT_TEAM_INFO_RES*)pPacket;

	if( pInfo->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage( pInfo->wResultCode, TRUE );
		return;
	}

	CDboEventGenerator::BudokaiTournamentTeamInfo( pInfo->awTeamType, &pInfo->sData );
}
