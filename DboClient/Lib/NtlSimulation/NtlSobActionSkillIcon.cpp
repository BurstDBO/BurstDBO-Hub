#include "precomp_ntlsimulation.h"
#include "NtlSobActionSkillIcon.h"

// shared
#include "NtlSkill.h"
#include "ActionTable.h"
#include "NtlMovement.h"
#include "NtlResultCode.h"

// simulation
#include "NtlSLGlobal.h"
#include "TableContainer.h"
#include "NtlSLEvent.h"
#include "NtlSLEventFunc.h"
#include "NtlSobActionSkill.h"
#include "NtlSobActionSkillAttr.h"
#include "NtlSobManager.h"
#include "NtlSLLogic.h"
#include "NtlSobAvatar.h"

// peessitemp : table data�� �ٲ� ����.
#define MAX_ACTION_COOLTIME	3.0f

DEFINITION_MEMORY_POOL(CNtlSobActionSkillIcon)

CNtlSobActionSkillIcon::CNtlSobActionSkillIcon() 
{
	SetClassID(SLCLASS_ACTIONSKILL_ICON);
	SetClassName(SLCLASS_NAME_ACTIONSKILL_ICON);

	m_byIconState = ICON_STATE_USEABLE;
	m_fCoolTime = 0.0f;
	m_fMaxCoolTime = 0.0f;
}

CNtlSobActionSkillIcon::~CNtlSobActionSkillIcon() 
{

}

void CNtlSobActionSkillIcon::HandleEvents(RWS::CMsg &pMsg)
{
	if(pMsg.Id == g_EventSobCreate)
	{
		CNtlSobActionSkill *pSobActionSkill = reinterpret_cast<CNtlSobActionSkill*>(m_pSobObj);
		CNtlSobActionSkillAttr *pSobActionSkillAttr = reinterpret_cast<CNtlSobActionSkillAttr*>(pSobActionSkill->GetSobAttr());
		sACTION_TBLDAT* pActionSkillTbl = pSobActionSkillAttr->GetActionSkillTbl();
		m_fMaxCoolTime = MAX_ACTION_COOLTIME;
		CreateImage(pActionSkillTbl->szIcon_Name);
	}
}

RwBool CNtlSobActionSkillIcon::IsDragAndDropPossible(void) 
{
	NTL_FUNCTION("CNtlSobActionSkillIcon::IsDragAndDropPossible");

	NTL_RETURN(TRUE);
}

RwBool CNtlSobActionSkillIcon::IsUsePossible(void)
{
	NTL_FUNCTION("CNtlSobActionSkillIcon::IsUsePossible");

	// ����Ŭ, ���Ǵ׾������϶��� �׼ǽ�ų�� ������� ���Ѵ�
	if(Logic_IsTransform(GetNtlSLGlobal()->GetSobAvatar()))
	{
		BYTE byAspectStateID = GetNtlSLGlobal()->GetSobAvatar()->GetAspectState()->sAspectStateBase.byAspectStateId;
		switch(byAspectStateID)
		{
		case ASPECTSTATE_SPINNING_ATTACK:
			m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_SPINNING_ATTACK;
			NTL_RETURN(FALSE);
		case ASPECTSTATE_VEHICLE:
			m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_VEHICLE;
			NTL_RETURN(FALSE);		
		}
	}

	NTL_RETURN(TRUE);
}

RwBool CNtlSobActionSkillIcon::Use(SERIAL_HANDLE hTargetSerialId, RwUInt32 uiRPBonusType)
{
	NTL_FUNCTION("CNtlSobActionSkillIcon::Use");

	CNtlSobActionSkill *pSobAction = reinterpret_cast<CNtlSobActionSkill*>( m_pSobObj );
	CNtlSobActionSkillAttr *pSobActionAttr = reinterpret_cast<CNtlSobActionSkillAttr*>( pSobAction->GetSobAttr() );
	sACTION_TBLDAT *pActionTblData = pSobActionAttr->GetActionSkillTbl();

	NTL_ASSERT(pActionTblData, "CNtlSobActionSkillIcon::Use => table data is not exist");

	// ��Ÿ�� �˻�. 
	if( m_byIconState == ICON_STATE_COOLING )
	{
		CNtlSLEventGenerator::SysMsg( m_pSobObj->GetOwnerID(), GAME_SKILL_NOT_READY_TO_BE_CAST );
		NTL_RETURN( FALSE );
	}

	if(!IsUsePossible())
	{
		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), m_uiErrorMsg);
		NTL_RETURN(FALSE);
	}

	if( pActionTblData->byAction_Type == ACTION_TYPE_SOCIAL_ACTION )
	{
		CNtlSLEventGenerator::ActionMapSocialUse(pActionTblData->tblidx);
	}
	else 
	{
        switch(pActionTblData->byETC_Action_Type)
        {
        case ACTION_FUNC_TYPE_PC_SHOP_OPEN:
            // 10M �̳��� ���λ����� �ִ��� ����� �ִٸ� ���λ����� ���� ���ϰ� �Ѵ�.
            if ( Logic_IsCanCreatePrivateShop() )
            {
                CNtlSLEventGenerator::ActionMapPrivateShopOpen();	
            }		
            break;
        case ACTION_FUNC_TYPE_SCOUTER_USE:
            CNtlSLEventGenerator::ActionMapScouterUse();
            break;
        case ACTION_FUNC_TYPE_NORMAL_DICE_OPEN:
            CNtlSLEventGenerator::ActionMapDice();
            break;
        case ACTION_FUNC_TYPE_BASIC_ATTACK:
            CNtlSLEventGenerator::ActionFuncBasicAttack();
            break;
        case ACTION_FUNC_TYPE_ASSIST:
            CNtlSLEventGenerator::ActionFuncAssist();
            break;
        case ACTION_FUNC_TYPE_GET_ITEM:
            CNtlSLEventGenerator::ActionFuncGetItem();
            break;
        case ACTION_FUNC_TYPE_RELAX_ACTION:
            CNtlSLEventGenerator::ActionFuncSitAndStand();
            break;
        default:
            NTL_ASSERTFAIL( "CNtlSobActionSkillIcon::Use : Invalid ActionTblData->byETC_Action_Type" );
            break;
        }		
	}	
	
	NTL_RETURN(TRUE);
}
