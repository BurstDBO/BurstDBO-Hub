#include "precomp_ntlsimulation.h"
#include "NtlSobSkillIcon.h"

// shared
#include "NtlSkill.h"
#include "SkillTable.h"
#include "NtlResultCode.h"
#include "NtlMovement.h"


// simulation
#include "TableContainer.h"
#include "NtlSLEvent.h"
#include "NtlSLEventFunc.h"
#include "NtlSobSkill.h"
#include "NtlSobSkillAttr.h"
#include "NtlSobManager.h"
#include "NtlSLLogic.h"
#include "NtlSLGlobal.h"
#include "NtlSobAvatar.h"
#include "NtlSobProxy.h"
#include "DisplayStringDef.h"

DEFINITION_MEMORY_POOL(CNtlSobSkillIcon)

RwBool CNtlSobSkillIcon::m_bUseReq		= FALSE;
RwReal CNtlSobSkillIcon::m_fUseResTimeOut	= 0.0f;


CNtlSobSkillIcon::CNtlSobSkillIcon() 
{
	SetClassID(SLCLASS_SKILL_ICON);
	SetClassName(SLCLASS_NAME_SKILL_ICON);

	m_byIconState = ICON_STATE_USEABLE;
	m_fCoolTime = 0.0f;
	m_fMaxCoolTime = 0.0f;    
}

CNtlSobSkillIcon::~CNtlSobSkillIcon() 
{
	
}

void CNtlSobSkillIcon::HandleEvents(RWS::CMsg &pMsg)
{
	if(pMsg.Id == g_EventSobCreate)
	{
		CNtlEventSobSkillCreate *pSobItemCreate = reinterpret_cast<CNtlEventSobSkillCreate*>(pMsg.pData);
		{
			CNtlSobSkill *pSobSkill = reinterpret_cast<CNtlSobSkill*>(m_pSobObj);
			CNtlSobSkillAttr *pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>(pSobSkill->GetSobAttr());
			sSKILL_TBLDAT* pSkillTbl = pSobSkillAttr->GetSkillTbl();
			m_fMaxCoolTime = (RwReal)pSkillTbl->wCool_Time;

			if( pSobItemCreate->uiRemainTime > 0 )
			{
				SetSkillIconState( ICON_STATE_COOLING, INVALID_BYTE, FALSE, (RwReal)(m_fMaxCoolTime - ( pSobItemCreate->uiRemainTime * 0.001f) ) );
			}

			CreateImage(pSkillTbl->szIcon_Name);
		}
	}	
}

RwBool CNtlSobSkillIcon::IsDragAndDropPossible(void) 
{
	NTL_FUNCTION("CNtlSobSkillIcon::IsDragAndDropPossible");

	CNtlSobSkill *pSobSkill = reinterpret_cast<CNtlSobSkill*>(m_pSobObj);
	CNtlSobSkillAttr *pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>(pSobSkill->GetSobAttr());
	sSKILL_TBLDAT* pSkillTbl = pSobSkillAttr->GetSkillTbl();

	if(pSkillTbl->bySkill_Class == NTL_SKILL_CLASS_ACTIVE)
	{
		NTL_RETURN(TRUE);
	}

	NTL_RETURN(FALSE);
}

RwBool CNtlSobSkillIcon::IsUsePossible(void)
{
	NTL_FUNCTION("CNtlSobSkillIcon::IsUsePossible");

	CNtlSobSkill *pSobSkill = reinterpret_cast<CNtlSobSkill*>(m_pSobObj);
	CNtlSobSkillAttr *pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>(pSobSkill->GetSobAttr());
	sSKILL_TBLDAT* pSkillTbl = pSobSkillAttr->GetSkillTbl();

	if(pSkillTbl->bySkill_Class != NTL_SKILL_CLASS_ACTIVE)
	{
        m_uiErrorMsg = GAME_SKILL_NOT_ACTIVE_TYPE;
        NTL_RETURN(FALSE);
	}    

    // �������϶��� �Ϲ� ��ų�� ������� ���Ѵ�
    if(Logic_IsTransform(GetNtlSLGlobal()->GetSobAvatar()))
    {
        DWORD flag = pSkillTbl->dwTransform_Use_Info_Bit_Flag;        
        BYTE byAspectStateID = GetNtlSLGlobal()->GetSobAvatar()->GetAspectState()->sAspectStateBase.byAspectStateId;
        switch(byAspectStateID)
        {
        case ASPECTSTATE_SUPER_SAIYAN:
            if(!(flag & SKILL_TRANSFORM_USE_INFO_FLAG_ABLE_WHEN_SUPER_SAIYAN))
            {
                m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_SUPER_SAIYAN;
                NTL_RETURN(FALSE);
            }
            break;
        case ASPECTSTATE_PURE_MAJIN:
            if(!(flag & SKILL_TRANSFORM_USE_INFO_FLAG_ABLE_WHEN_PURE_MAJIN))
            {
                m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_PURE_MAJIN;
                NTL_RETURN(FALSE);
            }
            break;
        case ASPECTSTATE_GREAT_NAMEK:
            if(!(flag & SKILL_TRANSFORM_USE_INFO_FLAG_ABLE_WHEN_GREAT_NAMEK))
            {
                m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_GREAT_NAMEK;
                NTL_RETURN(FALSE);
            }            
            break;
        case ASPECTSTATE_KAIOKEN:
            if(!(flag & SKILL_TRANSFORM_USE_INFO_FLAG_ABLE_WHEN_KAIOKEN))
            {
                m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_KAIOKEN;
                NTL_RETURN(FALSE);
            }
            break;
        case ASPECTSTATE_SPINNING_ATTACK:
            if(!(flag & SKILL_TRANSFORM_USE_INFO_FLAG_ABLE_WHEN_SPINNING_ATTACK))
            {
                m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_SPINNING_ATTACK;
                NTL_RETURN(FALSE);
            }
            break;
        case ASPECTSTATE_VEHICLE:
            if(!(flag & SKILL_TRANSFORM_USE_INFO_FLAG_ABLE_WHEN_VEHICLE))
            {
                m_uiErrorMsg = GAME_SKILL_CANT_USE_SKILL_WHEN_VEHICLE;
                NTL_RETURN(FALSE);
            }
            break;
        }
    }

    NTL_RETURN(TRUE);	
}

RwBool CNtlSobSkillIcon::Use(SERIAL_HANDLE hTargetSerialId, RwUInt32 uiRPBonusType/* =0xFF */)
{
	NTL_FUNCTION("CNtlSobSkillIcon::Use");

	// Ʃ�丮�󿡼� ��ų ����� ���� ���� �ڵ�
	if ( m_pSobObj->GetOwnerID() == CNtlSLGlobal::GetInstance()->GetSobAvatar()->GetSerialID() )
	{
		if ( !Logic_CanAttack_in_Tutorial( ETL_ATTACK_TYPE_SKILL_ATTACK ) )
		{
			NTL_RETURN(FALSE);
		}
	}

	// ���� skill ��� ��û���̸�?
	if(m_bUseReq)
	{
		NTL_RETURN(FALSE);
	}

	if(!IsUsePossible())
	{
		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), m_uiErrorMsg);
		NTL_RETURN(FALSE);
	}

	//-----------------------------------------------------------------
	// casting �˻�.

	if(m_byIconState == ICON_STATE_COOLING)
	{
		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_NOT_READY_TO_BE_CAST);
		NTL_RETURN(FALSE);
	}

	CNtlSobSkill *pSobSkill = reinterpret_cast<CNtlSobSkill*>(m_pSobObj);
	CNtlSobSkillAttr *pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>(pSobSkill->GetSobAttr());
	sSKILL_TBLDAT* pSkillTbl = pSobSkillAttr->GetSkillTbl();

	NTL_ASSERT(pSkillTbl != NULL, "CNtlSobSkillIcon::Use => skill table pointer is null !!!");

	//-----------------------------------------------------------------
	// appoint target ��ȿ �˻�.
	//-----------------------------------------------------------------
	// self
	RwUInt8 byAppointTarget = pSkillTbl->byAppoint_Target;
	if(byAppointTarget == DBO_SKILL_APPOINT_TARGET_SELF)
	{
		if(pSobSkill->GetOwnerID() != hTargetSerialId)
		{
			hTargetSerialId = pSobSkill->GetOwnerID();
		}
	}
	// target
	else if(byAppointTarget == DBO_SKILL_APPOINT_TARGET_TARGET)
	{
		// �̷ο� skill�̸�?
		if(!Dbo_IsHarmfulEffectType(pSkillTbl->bySkill_Active_Type))
		{
			if(!Logic_IsSkillSystemEffectCode(pSkillTbl->tblidx, ACTIVE_WARP))
			{
				if( !ApplyTargetCheck( hTargetSerialId ) )
					hTargetSerialId = pSobSkill->GetOwnerID();				
			}
		}
		else if(hTargetSerialId == INVALID_SERIAL_ID)
		{
			CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_NO_TARGET_APPOINTED);
			NTL_RETURN(FALSE);
		}
		else
		{
			if( !ApplyTargetCheck( hTargetSerialId ) )
			{
				CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_INVALID_TARGET_APPOINTED);
				NTL_RETURN(FALSE);
			}
		}		
	}
	// point
	// peessi : ���� point ��ų�� ����. 
	else
	{
		NTL_RETURN(FALSE);
	}

	//-----------------------------------------------------------------
	// world rule �˻�.
	
	RwUInt32 uiResultCode;
	if(!GetNtlWorldConcept()->CanUseSkill(hTargetSerialId, uiResultCode))
	{
		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), uiResultCode);
		NTL_RETURN(FALSE);
	}

	// -----------------------------------------------------------------
	// LP/EP/RP check.
	CNtlSob *pOwnerSobObj = GetNtlSobManager()->GetSobObject(m_pSobObj->GetOwnerID());
	RwUInt32 uiCurrLp		= Logic_GetLp(pOwnerSobObj);
	RwUInt32 uiCurrEp		= Logic_GetEp(pOwnerSobObj);
	RwUInt32 uiCurrRpStock	= Logic_GetRpStock(pOwnerSobObj);

	if(uiCurrLp < (RwUInt32)pSkillTbl->wRequire_LP)
	{
		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_NOT_ENOUGH_LP);
		NTL_RETURN(FALSE);
	}

	if(uiCurrEp < (RwUInt32)pSkillTbl->wRequire_EP)
	{
		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_NOT_ENOUGH_EP);
		NTL_RETURN(FALSE);
	}

	// Rp �˻� ( wRequire_RP �� ���� �Ϲݽ�ų�� �����Ѵ�. )
 	if(uiCurrRpStock < (RwUInt32)pSkillTbl->byRequire_RP_Ball && uiRPBonusType != 0xFF )
 	{
 		CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_NOT_ENOUGH_RP_BALL);
 		NTL_RETURN(FALSE);
 	}


	// -----------------------------------------------------------------
	// item ���� �˻�.
	if(pSkillTbl->byRequire_Epuip_Slot_Type == EQUIP_SLOT_TYPE_SUB_WEAPON)
	{
		// �̰��� logic���� �Լ��� �ű��.		
		SERIAL_HANDLE hSubWeaponSerialId = Logic_GetEquipedSubWeaponItemSerial(pOwnerSobObj);
		if(hSubWeaponSerialId == INVALID_SERIAL_ID)
		{
			CNtlSLEventGenerator::SysMsg(m_pSobObj->GetOwnerID(), GAME_SKILL_NO_REQUIRED_ITEM);
			NTL_RETURN(FALSE);
		}
	}

    // ������Ʈ�� ���� ��Ŭ���� üũ. ������Ʈ�� ������ ������ ��ų��� �Ұ� (by agebreak 2009.07.20)
    CNtlSobActor* pTargetActor = (CNtlSobActor*)GetNtlSobManager()->GetSobObject(hTargetSerialId);
    NTL_ASSERT(pTargetActor, "Skil Target Actor is NULL!");
    if(!pTargetActor)
        NTL_RETURN(FALSE);
    
    // Ÿ�ٰ��� ���� �˻�
    if(Logic_isEnemyTargetOcclusion(pTargetActor->GetSerialID()))
        NTL_RETURN(FALSE);    
	
	//-----------------------------------------------------------------
	// apply target �˻�. (������ ���� �˻� ���Ѵ�)
	//-----------------------------------------------------------------

	RwUInt8 byApplyTarget = pSkillTbl->byApply_Target;
	// self
	if(byApplyTarget == DBO_SKILL_APPLY_TARGET_SELF)
	{
		// check ����.
	}
	// enemy
	else if(byApplyTarget == DBO_SKILL_APPLY_TARGET_ENEMY)
	{
		// check ����.
	}
	// alliance
	else if(byApplyTarget == DBO_SKILL_APPLY_TARGET_ALLIANCE)
	{
		// check ����.
	}
	// party
	else if(byApplyTarget == DBO_SKILL_APPLY_TARGET_PARTY)
	{
	}

	//-----------------------------------------------------------------
	// event ������.

	RwReal fSkillRange = Logic_GetSkillUseRange(pSkillTbl);
	

	/*RwUInt8 byApplyRPBonusType;
	if( pSobSkillAttr->m_bRPBonusAutoMode )
		byApplyRPBonusType = pSobSkillAttr->m_byRPBonusType;
	else
		byApplyRPBonusType = uiRPBonusType;*/

	CNtlSLEventGenerator::ActionMapSkillUse(pSobSkill->GetOwnerID(), TRUE, hTargetSerialId, m_pSobObj->GetSerialID(),
											fSkillRange, pSobSkill->GetSlotIdx(), (RwUInt8)uiRPBonusType);

	NTL_RETURN(TRUE);
}

void CNtlSobSkillIcon::SetSkillIconState( RwUInt8 byIconState, RwUInt8 byRpBonusType, RwBool bSpecialCoolTimeCheck /* = FALSE */, RwReal fCoolTime /* = 0.0f  */ )
{
	CNtlSobSkillAttr* pSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>( m_pSobObj->GetSobAttr() );
	sSKILL_TBLDAT* pSkillData = pSkillAttr->GetSkillTbl();

	// ��ų ��Ÿ���� ������ ���� �����ϴ� ���. �������� ���� ��Ŷ�� ������� �Ǿ� �ִ�. 
	if( bSpecialCoolTimeCheck && pSkillData->wFunction_Bit_Flag & SKILL_FUNCTION_FLAG_SPECIAL_COOL_TIME_RULE )
		return;

	m_fMaxCoolTime = (RwReal)pSkillData->wCool_Time;

	if( pSkillData->bySkill_Class == NTL_SKILL_CLASS_ACTIVE )
	{
		CNtlSobActor* pActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject( m_pSobObj->GetOwnerID() ) );
		m_fMaxCoolTime *= Logic_GetCoolingTimeFactor( pActor );
	}

	if( byRpBonusType == DBO_RP_BONUS_TYPE_COOL_TIME_MINUS )
	{
		for( RwInt32 i = 0 ; i < DBO_MAX_RP_BONUS_COUNT_PER_SKILL ; ++i )
		{
			if( pSkillData->abyRpEffect[i] == DBO_RP_BONUS_TYPE_COOL_TIME_MINUS )
			{
				m_fMaxCoolTime = m_fMaxCoolTime - pSkillData->adwRpEffectValue[i];
				if( m_fMaxCoolTime <= 0.0f )
					m_fMaxCoolTime = 0.0f;
				break;
			}
		}
	}	

	CNtlSobIcon::SetIconState( byIconState, fCoolTime );
}

RwBool CNtlSobSkillIcon::ApplyTargetCheck( RwUInt32 hTargetSerial )
{
	if( hTargetSerial == INVALID_SERIAL_ID )
	{
		return FALSE;			
	}
	else
	{
		CNtlSob* pSobObj = GetNtlSobManager()->GetSobObject( hTargetSerial );
		
		CNtlSobSkill *pSobSkill = reinterpret_cast<CNtlSobSkill*>( m_pSobObj );
		CNtlSobSkillAttr *pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>( pSobSkill->GetSobAttr() );
		sSKILL_TBLDAT* pData = pSobSkillAttr->GetSkillTbl();

		if( !pSobObj )
		{
			return FALSE;
		}

		if( pData->byApply_Range == DBO_SKILL_APPLY_RANGE_SINGLE )
		{
			if( pSobObj->GetClassID() == SLCLASS_AVATAR )
			{
				if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_SELF ||
					pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ALLIANCE ||
					pData->byApply_Target == DBO_SKILL_APPLY_TARGET_PARTY ||
					pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
					return TRUE;
				else
					return FALSE;
			}
			else if( pSobObj->GetClassID() == SLCLASS_NPC )							 
			{
				if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ALLIANCE ||
					pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
					return TRUE;
				else
					return FALSE;
			}
			else if( pSobObj->GetClassID() == SLCLASS_MONSTER )
			{
				if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ENEMY ||
					pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
					return TRUE;
				else
					return FALSE;
			}
			else if( pSobObj->GetClassID() == SLCLASS_PLAYER ||
				pSobObj->GetClassID() == SLCLASS_PET )
			{
				if( GetNtlWorldConcept()->IsEnemyTargetFromAvatarActor( NULL, hTargetSerial ) )
				{
					if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ENEMY ||
						pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
						return TRUE;
					else
						return FALSE;
				}
				else
				{
					if( pSobObj->GetClassID() == SLCLASS_PET )
					{
						if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ALLIANCE ||
							pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
							return TRUE;
						else
							return FALSE;		
					}
					else
					{
						if( Logic_IsMyPartyMember( hTargetSerial ) )
						{
							if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ALLIANCE ||
								pData->byApply_Target == DBO_SKILL_APPLY_TARGET_PARTY ||
								pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
								return TRUE;
							else 
								return FALSE;
						}
						else
						{
							if( pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ALLIANCE ||
								pData->byApply_Target == DBO_SKILL_APPLY_TARGET_ANY )
								return TRUE;
							else 
								return FALSE;
						}								
					}
				}
			}
		}
		else
		{
			return TRUE;
		}
	}
}