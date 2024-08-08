#include "precomp_ntlsimulation.h"
#include "NtlBehaviorCharGroundMove.h"

// shared 
#include "NtlMovement.h"

// sound
#include "NtlSoundDefines.h"
#include "NtlSoundManager.h"

// framework
#include "NtlCamera.h"

// presentation
#include "NtlPLEvent.h"
#include "NtlPLPropertyContainer.h"

// simulation
#include "NtlSobActor.h"
#include "NtlSLLogic.h"
#include "NtlSobCharProxy.h"
#include "NtlSLVisualDeclear.h"
#include "NtlFSMDef.h"
#include "NtlSobManager.h"
#include "NtlCameraManager.h"
#include "NtlSLEventFunc.h"
#include "NtlSlApi.h"
#include "NtlSLPacketGenerator.h"
#include "NtlCameraController.h"

#define FRAME_2 (2.0f / 30.0f)


DEFINITION_MEMORY_POOL(CNtlBehaviorCharGroundMove)

CNtlBehaviorCharGroundMove::CNtlBehaviorCharGroundMove()
{
    SetBehaviorId(NTL_BEID_CHAR_GROUNDMOVE);
    SetBehaviorName(NTL_BENAME_CHAR_GROUNDMOVE);

    m_bSlowMove				= FALSE;
    m_fSlowMoveTime			= 0.0f;
    m_byDashState			= DASH_STATE_MOVE;
    m_pDashEffect			= NULL;
    m_pDashLine				= NULL;
    m_pDashEffectSmoke		= NULL;
    m_fEffectSmokeTime		= 0.0f;
    m_bDashCameraEnable		= FALSE;
    m_fPosChangeTime		= 0.0f;
    m_byPosChangeCnt		= 0;
    m_byCollMoveImpossCnt	= 0;

    m_bServerSyncPos		= FALSE;
    m_bSyncSendCheck		= TRUE;
    m_fSyncSendTime         = MOVE_SYNC_SEND_TIME;

    m_fInterAnimTime        = 0.0f;    

    m_bNotAnimChange        = FALSE;
}

CNtlBehaviorCharGroundMove::~CNtlBehaviorCharGroundMove()
{
    DestroyEndDashCamera();
    DestroyDashEffect();
    DestroyDashEffectSmoke();
}


void CNtlBehaviorCharGroundMove::Enter(void)
{
    CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData());     
    memcpy(&m_MoveStuff, pBeData->GetMoveStuff(), sizeof(SMoveStuff));

    if(IsInMoveRound())
    {
        Finish();
        return;
    }

    SetPathNode();
    SetTransform();	
    CreateStartDashCamera();

    m_fDefaultWalkSpeed = Logic_GetDefaultFrontWalkSpeed(m_pActor);
    m_fDefaultRunSpeed	= Logic_GetDefaultFrontRunSpeed(m_pActor);
    m_fDefaultBackSpeed = Logic_GetDefaultBackSpeed(m_pActor);	

    SetServerSyncPosition(m_MoveStuff.vCurrLoc);

    if(!IsMoveSyncState())
    {
        SetAnim(m_MoveStuff.byMoveFlags);
        // Idle -> Run ���� �ִϸ��̼�
        SetIdle2RunAnim();

        //m_fSyncSendTime = MOVE_SYNC_SEND_TIME;
    }
    else
    {
        //m_fSyncSendTime = MOVE_SYNC_SEND_TIME;
    }


    // ���߿� base class enter�� ȣ���Ѵ�.
    CNtlBehaviorBase::Enter(); 
}

void CNtlBehaviorCharGroundMove::SetIdle2RunAnim( void ) 
{
    if(m_bNotAnimChange || Logic_IsTransformSpinAttack(m_pActor))
        return;

    // ���Žÿ��� ���� �ִϸ��̼��� ���Ѵ�.
    if(Logic_GetPlayerRace(m_pActor) == RACE_NAMEK && Logic_IsTransform(m_pActor))
        return;

    // Idle �ִϸ��̼� ���϶��� ��ȯ�Ѵ�.
    if(!IsIdleAnimationPlaying())
        return;

    // Idle -> Run ���� �ִϸ��̼�
    if(m_MoveStuff.byMoveFlags == NTL_MOVE_F || m_MoveStuff.byType == NTL_MOVETARGET_LOC || m_MoveStuff.byType == NTL_MOVETARGET_ACTOR)
    {
        if(m_pActor->GetClassID() == SLCLASS_AVATAR)
        {
            CNtlSobCharProxy *pSobProxy = reinterpret_cast<CNtlSobCharProxy*>(m_pActor->GetSobProxy());            
            sITEM_TBLDAT *pItemTblData = Logic_GetEquipedWeaponItemTableData(m_pActor);
            if(pItemTblData && Logic_IsEquipedStaffWeapon(pItemTblData))    // �������� ��� ������
            {
                pSobProxy->SetBaseAnimation(NML_STAFF_IDLE_RUN_FRONT, FALSE);
            }
            else    // �ƹ��͵� ��� ���� ������
            {
                pSobProxy->SetBaseAnimation(IDLE_RUN_FRONT, FALSE);   
            }
            m_bInterAnimEnd = FALSE;
        }
    }
}

void CNtlBehaviorCharGroundMove::Exit(void)
{
    DestroyEndDashCamera();
    DestroyDashEffect();
    DestroyDashEffectSmoke();

    if(m_pActor->GetClassID() == SLCLASS_PLAYER)
    {
        CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
        if(pBeData)
        {
            SMoveSyncStuff* pMoveSyncStuff = pBeData->GetMoveSyncStuff();
            pMoveSyncStuff->Clear();
        }        
    }
    

    // ���߿� base class enter�� ȣ���Ѵ�.
    CNtlBehaviorBase::Exit(); 
}

void CNtlBehaviorCharGroundMove::Update(RwReal fElapsed)
{
    fElapsed = min(fElapsed, 0.2f);

    if(IsFinish() && !m_bNotAnimChange) // �ִϸ��̼� ����ȵǴ� ���¿����� ������ �ʴ´�. (ȸ�������� ����)
        return;

    // ���� �ִϸ��̼� ó�� (2Frame �ĺ��� �̵��Ѵ�)
    if(!m_bInterAnimEnd)
    {
        if(m_fInterAnimTime < FRAME_2)
        {
            m_fInterAnimTime += fElapsed;
            return;
        }        
        else
        {
            m_bInterAnimEnd = TRUE;
            m_fInterAnimTime = 0.0f;            
        }
    }

    UpdateServerSyncPosition(fElapsed);

    RwBool bFinish = FALSE;
    switch(m_MoveStuff.byType)
    {
    case NTL_MOVETARGET_DIR:                
        bFinish = UpdateDirectionMove(fElapsed);        
        break;
    case NTL_MOVETARGET_LOC:
        bFinish = UpdateLocationMove(fElapsed);
        break;
    case NTL_MOVETARGET_ACTOR:
        if(!Logic_IsTransformSpinAttack(m_pActor))  // ���� �����϶��� Ÿ�� ���긦 ���� �ʴ´�.
        {
            bFinish = UpdateTargetMove(fElapsed);        
        }        
        break;
    case NTL_MOVETARGET_DASH:
        UpdateDashMove(fElapsed);
        break;
    case NTL_MOVETARGET_DASH_ACTOR:
        bFinish = UpdateDashTargetMove(fElapsed);
        break;
    default:
        bFinish = TRUE;
    }	

    // Move Sync�� ������. 
    UpdateSendSyncCheck(fElapsed);

    UpdateAnimSpeed();

    if(bFinish && !Logic_IsTransformSpinAttack(m_pActor))
    {
        Finish();        
    }
}

RwUInt32 CNtlBehaviorCharGroundMove::HandleEvents(RWS::CMsg &pMsg)
{
    NTL_FUNCTION("CNtlBehaviorCharGroundMove::HandleEvents");

    if(pMsg.Id == g_EventAnimFootStep)
    {
        if(!m_sHStuff.bWaterAttr || m_sHStuff.fWorldHeight > m_sHStuff.fWaterHeight)
        {
            FootStepMaterialProc(pMsg);
        }
        else
        {
            RwV3d vPos = m_pActor->GetPosition();
            CNtlSobProxy *pSobProxy = m_pActor->GetSobProxy();
            vPos.y = m_sHStuff.fWaterHeight;
            pSobProxy->CreatePLEffect(NTL_VID_WATER_FOOT, &vPos);
        }
    }

    else if(pMsg.Id == g_EventSobEquipChange)
    {
        RwUInt8 byMoveType = m_MoveStuff.byType;
        if(byMoveType == NTL_MOVETARGET_DIR || byMoveType == NTL_MOVETARGET_LOC ||
            byMoveType == NTL_MOVETARGET_ACTOR)
        {
            SetAnim(m_MoveStuff.byMoveFlags);
        }
    }
    else if(pMsg.Id == g_EventAnimEnd)
    {
        SNtlEventAnimEnd *pAnimEnd = reinterpret_cast<SNtlEventAnimEnd*>( pMsg.pData );
        RwUInt32 uiAnimKey = pAnimEnd->uiBaseAnimKey;

        if(uiAnimKey == IDLE_RUN_FRONT || uiAnimKey == NML_STAFF_IDLE_RUN_FRONT) // ���� �ִϸ��̼� �Ϸ� ó��
        {
            SetAnim(m_MoveStuff.byMoveFlags);                
            m_bInterAnimEnd = TRUE; 
        }        

        if(m_byDashState == DASH_STATE_LANDING || m_byDashState == DASH_STATE_END)
        {

            if( uiAnimKey == NML_DASH_FRONT_LANDING || uiAnimKey == NML_DASH_BACK_LANDING || 
                uiAnimKey == NML_DASH_LEFT_LANDING || uiAnimKey == NML_DASH_RIGHT_LANDING)
            {
                Finish();
            }
        }
    }
    else if(pMsg.Id == g_EventSobAdjustMovePosition)
    {
        SNtlEventSobAdjustMovePosition *pAdjustMovePos = reinterpret_cast<SNtlEventSobAdjustMovePosition*>( pMsg.pData );
        SetServerSyncPosition(pAdjustMovePos->vAdjustPos);
    }    
    else if(pMsg.Id == g_EventTransform)
    {
        SNtlEventTransform* pEvent = (SNtlEventTransform*)pMsg.pData;
        if(pEvent->sApsectState.sAspectStateBase.byAspectStateId == ASPECTSTATE_INVALID)     // ���� ����
        {
            SetAnim(m_MoveStuff.byMoveFlags);
        }
    }

    NTL_RETURN(CNtlBehaviorCharMove::HandleEvents(pMsg));
}

void CNtlBehaviorCharGroundMove::UpdateData(void)
{
    CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
    SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
    memcpy(&m_MoveStuff, pMoveStuff, sizeof(SMoveStuff));

    SetAnim(m_MoveStuff.byMoveFlags);

    m_fSyncSendTime = MOVE_SYNC_SEND_TIME;    
    UpdateSendSyncCheck(m_fSyncSendTime);
    m_fSyncSendTime = MOVE_SYNC_SEND_TIME;  // �� �Լ� ȣ���� �ٽ� 0.0�� �Ǳ� ������ �ٽ� ���� �����Ѵ�.
}

void CNtlBehaviorCharGroundMove::FootStepMaterialProc(RWS::CMsg &pMsg)
{
    RwV3d			vPos		= m_pActor->GetPosition();

    if(m_pActor->GetClassID() == SLCLASS_AVATAR || m_pActor->GetClassID() == SLCLASS_MONSTER)
    {
        SNtlEventFootStep*			pData		= reinterpret_cast<SNtlEventFootStep*>(pMsg.pData);
        SEventFootStep*             pEvent      = reinterpret_cast<SEventFootStep*>(pData->pData);
        CNtlPLEntity*				pEntity;
        RwChar						cSoundResoureName[64];
        RwChar						cEffectResoureName[64];

        BYTE						byMaterial	= 0;
        RwReal						fHeight		= 0.0f;

        // Cz : CNtlPLGlobal::m_pWHEntity ���强�� ������ GetWorldHeight�� ȣ���մϴ�.
        //		Performance�� ������ �� ������ ������ �����Ƿ� ����ϱ�� �Ͽ����ϴ�.
        //		������ ������ ���� ��� �����̸� ȣ���� �ּ���.
        if (!(GetSceneManager()->GetWorldHeight(&vPos, fHeight, NULL) && CNtlPLGlobal::m_pWHEntity))
        {
            byMaterial = GetSceneManager()->GetWorldMaterialAttribute(vPos);
        }

        if(pEvent->eFootStepMobType == FOOT_TYPE_LARGE || (m_pActor->GetFlags() & SLFLAG_LARGE_FOOT_SOUND)) // ���� �� ���ڱ� �Ҹ�
        {
            sprintf_s(cSoundResoureName, 64, "%s_L_%u.wav", NAMING_SOUND_FOOTSTEP, NtlRandomNumber(0, 3));

            sNtlSoundPlayParameta tSoundParam;
            tSoundParam.iChannelGroup	= CHANNEL_GROUP_EFFECT_SOUND;
            tSoundParam.pcFileName		= cSoundResoureName;
            tSoundParam.bLoop			= FALSE;
            tSoundParam.fVolume			= NtlRandomNumber(0.7f, 1.0f);
            tSoundParam.fPitch			= NtlRandomNumber(0.97f, 1.03f);
            tSoundParam.fXPos			= vPos.x;
            tSoundParam.fYPos			= vPos.y;
            tSoundParam.fZPos			= vPos.z;
            tSoundParam.fMinDistance	= 10.0f;
            tSoundParam.fMaxDistance	= 25.0f;

            GetSoundManager()->Play(&tSoundParam);
        }
        else    // �Ϲ� �� ���ڱ� �Ҹ�
        {
            sprintf_s(cSoundResoureName, 64, "%s_%u_%u.wav", NAMING_SOUND_FOOTSTEP, byMaterial, NtlRandomNumber(0, 3));

            sNtlSoundPlayParameta tSoundParam;
            tSoundParam.iChannelGroup	= CHANNEL_GROUP_EFFECT_SOUND;
            tSoundParam.pcFileName		= cSoundResoureName;
            tSoundParam.bLoop			= FALSE;
            tSoundParam.fVolume			= NtlRandomNumber(0.7f, 1.0f);
            tSoundParam.fPitch			= NtlRandomNumber(0.97f, 1.03f);
            tSoundParam.fXPos			= vPos.x;
            tSoundParam.fYPos			= vPos.y;
            tSoundParam.fZPos			= vPos.z;
            tSoundParam.fMinDistance	= 4.0f;
            tSoundParam.fMaxDistance	= 10.0f;

            GetSoundManager()->Play(&tSoundParam);
        }

        sprintf_s(cEffectResoureName, 64, "%s_%u_%c_%u", NAMING_EFFECT_FOOTSTEP, byMaterial, (pEvent->eFootStepType ? 'R' : 'L'), NtlRandomNumber(0, 1)); 	 	
        if (CNtlPLPropertyContainer::GetInstance()->GetProperty(PLENTITY_EFFECT, cEffectResoureName))
        {
            pEntity	= m_pActor->GetSobProxy()->CreatePLEffect(cEffectResoureName, &vPos);
            if (pEntity)
            {
                pEntity->SetRotate(0.0f, CNtlMath::LineToAngleY(&m_pActor->GetDirection()), 0.0f);
            }
        }		
    }
}

RwBool CNtlBehaviorCharGroundMove::IsInDestMoveRound(void)
{
    RwV3d vPos = m_pActor->GetPosition(); 
    RwV3d vDir;
    RwV3dSub(&vDir, &m_MoveStuff.vDest, &vPos);
    vDir.y = 0.0f;
    RwReal fLen = RwV3dLength(&vDir);
    if(fLen < 0.05f)
        return TRUE;

    return FALSE;
}

RwBool CNtlBehaviorCharGroundMove::IsInFollowMoveRound(void)
{
    CNtlSobActor *pTargetActor = reinterpret_cast<CNtlSobActor*>(GetNtlSobManager()->GetSobObject(m_MoveStuff.hFollowSerialId));
    if(pTargetActor == NULL)
        return TRUE;

    RwV3d vPos = m_pActor->GetPosition();
    RwV3d vDestPos = pTargetActor->GetPosition(); 
    // ���� ���� ���� ���� ����ٴϴ� ��ü�� ���.
    if(pTargetActor->GetFlags() & SLFLAG_CAN_GROUND_FLY)
        vDestPos.y -= Logic_GetGroundFlyHeight(pTargetActor);

    RwV3d vDir;
    RwV3dSub(&vDir, &vDestPos, &vPos); 

    // ���� ���� �Ÿ��� ���Ѵ�.
    RwReal fCurrLen = RwV3dLength(&vDir);

    RwReal fInRange = m_MoveStuff.fFollowRange*FOLLOW_ERROR_RANGE;

    if(fCurrLen <= fInRange)
        return TRUE;

    // 2d �Ÿ��� Ȯ���� ����.
    vDir.y = 0.0f;
    fCurrLen = RwV3dLength(&vDir);
    if(fCurrLen <= fInRange / 2.0f)
        return TRUE;

    return FALSE;
}

RwBool CNtlBehaviorCharGroundMove::IsInMoveRound(void)
{
    if(m_MoveStuff.byType == NTL_MOVETARGET_LOC)
        return IsInDestMoveRound();
    else if(m_MoveStuff.byType == NTL_MOVETARGET_ACTOR || m_MoveStuff.byType == NTL_MOVETARGET_DASH_ACTOR)
        return IsInFollowMoveRound();

    return FALSE;
}

void CNtlBehaviorCharGroundMove::LimitPositionChangeCheck(RwReal fElapsed)
{
    m_fPosChangeTime += fElapsed;
    m_byPosChangeCnt++;
    if(m_fPosChangeTime >= MOVE_POSITION_CHANGE_CHECK_TIME)
    {
        if(m_byPosChangeCnt >= 3)
        {
            RwV3d vPos = m_pActor->GetPosition();
            RwV3d vSub;
            RwV3dSub(&vSub, &vPos, &m_vChangeOldPos);
            if(RwV3dLength(&vSub) <= MOVE_POSITION_CHANGE_LIMIT_RANGE)
                Finish();
            else
                RwV3dAssign(&m_vChangeOldPos, &vPos);
        }

        m_fPosChangeTime -= MOVE_POSITION_CHANGE_CHECK_TIME;
        m_byPosChangeCnt = 0;
    }
}

void CNtlBehaviorCharGroundMove::SetPathNode(void)
{
    if(m_MoveStuff.byPathNodeNum)
    {
        for(RwInt32 i = 0; i < m_MoveStuff.byPathNodeNum; i++)
            AddPathNode(m_MoveStuff.arrPathNode[i]);

        RwV3dAssign(&m_MoveStuff.vDest, &m_MoveStuff.arrPathNode[0]);
    }
}

void CNtlBehaviorCharGroundMove::SetTransform(void)
{
    RwV3d vPos = m_pActor->GetPosition(); 
    RwV3dAssign(&m_vChangeOldPos, &vPos);

    if(m_MoveStuff.byType == NTL_MOVETARGET_LOC)
    {
        RwV3d vDir;
        RwV3dSub(&vDir, &m_MoveStuff.vDest, &vPos);
        vDir.y = 0.0f;
        RwV3dNormalize(&vDir, &vDir); 

        m_pActor->SetDirection(&vDir); 
    }

    // slow move ������ �Ǵ��Ѵ�.
    else if(m_MoveStuff.byType == NTL_MOVETARGET_ACTOR)
    {
        CNtlSobActor *pTargetActor = reinterpret_cast<CNtlSobActor*>(GetNtlSobManager()->GetSobObject(m_MoveStuff.hFollowSerialId));
        if(pTargetActor)
        {	
            RwV3d vDestPos = pTargetActor->GetPosition(); 

            // ���� ���� ���� ���� ����ٴϴ� ��ü�� ���.
            if(pTargetActor->GetFlags() & SLFLAG_CAN_GROUND_FLY)
                vDestPos.y -= Logic_GetGroundFlyHeight(pTargetActor);

            NTL_ASSERT(m_pActor != pTargetActor, "CNtlBehaviorCharGroundMove::SetTransform");

            RwV3d vDir;
            RwV3dSub(&vDir, &vDestPos, &vPos); 

            // ���� ���� �Ÿ��� ���Ѵ�.
            vDir.y = 0.0f;
            RwReal fCurrLen = RwV3dLength(&vDir);
            if(fCurrLen - m_MoveStuff.fFollowRange < SLOW_MOVE_RANGE)
            {
                m_bSlowMove = TRUE;
            }

            RwV3dNormalize(&vDir, &vDir); 
            m_pActor->SetDirection(&vDir); 
        }
    }

    else if(m_MoveStuff.byType == NTL_MOVETARGET_DASH)
    {
        m_fDashLadingDist = NTL_DASH_SPEED*DASH_LANDING_TIME;

        Logic_GetWorldHeight(&m_MoveStuff.vDest, m_sHStuff);
        m_MoveStuff.vDest.y = m_sHStuff.fFinialHeight;
        m_fDashDestPosY	= m_MoveStuff.vDest.y;
    }
}

void CNtlBehaviorCharGroundMove::SetAnim(RwUInt8 byMoveFlags)
{
    if(m_bNotAnimChange)
        return;

    CNtlSobCharProxy *pSobProxy = reinterpret_cast<CNtlSobCharProxy*>(m_pActor->GetSobProxy());
    RwUInt32 uiCurrAnimKey = pSobProxy->GetBaseAnimationKey();
    RwUInt32 uiNextAnimKey = 0;

    if(m_MoveStuff.byType == NTL_MOVETARGET_DIR)
    {
        if( byMoveFlags == NTL_MOVE_F || byMoveFlags == NTL_MOVE_F_TURN_L ||
            byMoveFlags == NTL_MOVE_F_TURN_R )
        {
            sITEM_TBLDAT *pItemTblData = Logic_GetEquipedWeaponItemTableData(m_pActor);
            if(Logic_IsTransformGreatNamek(m_pActor))  // ���Ž�
            {
                uiNextAnimKey = TRANS_RUN_FRONT;
            }
            else if(Logic_IsTransformSpinAttack(m_pActor))
            {
                uiNextAnimKey = TRANS_IDLE;
            }
            else if(pItemTblData && Logic_IsEquipedStaffWeapon(pItemTblData))
            {
                uiNextAnimKey = NML_STAFF_FRONT_RUN;
            }
            else
            {
                uiNextAnimKey = RUN_FRONT;
            }

        }
        else if( byMoveFlags == NTL_MOVE_B || byMoveFlags == NTL_MOVE_B_TURN_L ||
            byMoveFlags == NTL_MOVE_B_TURN_R )
        {
            if(Logic_IsTransformGreatNamek(m_pActor)) // ���Ž�
            {
                uiNextAnimKey = TRANS_RUN_BACK;
            }
            else if(Logic_IsTransformSpinAttack(m_pActor))
            {
                uiNextAnimKey = TRANS_IDLE;
            }
            else
            {
                uiNextAnimKey = RUN_BACK;
            }
        }
        else if(byMoveFlags == NTL_MOVE_TURN_L)
        {
            uiNextAnimKey = TURN_LEFT;
        }
        else if(byMoveFlags == NTL_MOVE_TURN_R)
        {
            uiNextAnimKey = TURN_RIGHT;
        }
    }
    else if(m_MoveStuff.byType == NTL_MOVETARGET_LOC || m_MoveStuff.byType == NTL_MOVETARGET_ACTOR)
    {
        RwBool bWalkMove = Logic_IsActorWalkMove(m_pActor, m_MoveStuff.byFormFlag);
        sITEM_TBLDAT *pItemTblData = Logic_GetEquipedWeaponItemTableData(m_pActor);

        if(bWalkMove)
        {
            uiNextAnimKey = WALK_FRONT;
        }
        else
        {
            if(Logic_IsTransformGreatNamek(m_pActor))  // ���Ž�
            {
                uiNextAnimKey = TRANS_RUN_FRONT;
            }
            else if(Logic_IsTransformSpinAttack(m_pActor))
            {
                uiNextAnimKey = TRANS_IDLE;
            }
            else if(pItemTblData && Logic_IsEquipedStaffWeapon(pItemTblData))
            {
                uiNextAnimKey = NML_STAFF_FRONT_RUN;
            }
            else
            {
                uiNextAnimKey = RUN_FRONT;
            }
        }
    }
    else if(m_MoveStuff.byType == NTL_MOVETARGET_DASH)
    {
        if(byMoveFlags == NTL_MOVE_DASH_F)
            uiNextAnimKey = NML_DASH_FRONT;
        else if(byMoveFlags == NTL_MOVE_DASH_B)
            uiNextAnimKey = NML_DASH_BACK;
        else if(byMoveFlags == NTL_MOVE_DASH_L)
            uiNextAnimKey = NML_DASH_LEFT;
        else
            uiNextAnimKey = NML_DASH_RIGHT;

        CreateDashEffect(byMoveFlags);
        UpdateDashEffect(byMoveFlags, m_MoveStuff.vDir);
    }
    else if(m_MoveStuff.byType == NTL_MOVETARGET_DASH_ACTOR)
    {
        uiNextAnimKey = NML_DASH_FRONT;

        RwV3d vDir = m_pActor->GetDirection();

        CreateDashEffect(NTL_MOVE_DASH_F);
        UpdateDashEffect(NTL_MOVE_DASH_F, vDir);
    }

    if(uiCurrAnimKey != uiNextAnimKey)
        pSobProxy->SetBaseAnimation(uiNextAnimKey);
}

void CNtlBehaviorCharGroundMove::CreateStartDashCamera(void)
{
    if(m_MoveStuff.byType != NTL_MOVETARGET_DASH)
        return;

    if(m_pActor->GetClassID() != SLCLASS_AVATAR)
        return;

    // camera screen motion blur
    GetNtlGameCameraManager()->GetCamera()->SetEnableBlur(TRUE, 0.9f);

    CNtlSLEventGenerator::CameraDash(m_pActor->GetSerialID(), NTL_DASH_SPEED, m_MoveStuff.vDest); 

    m_bDashCameraEnable = TRUE;
}

void CNtlBehaviorCharGroundMove::DestroyEndDashCamera(void)
{
    if(m_pActor->GetClassID() != SLCLASS_AVATAR)
        return;

    if(m_MoveStuff.byType != NTL_MOVETARGET_DASH)
        return;

    if(!m_bDashCameraEnable)
        return;

    // camera screen motion blur
    GetNtlGameCameraManager()->GetCamera()->SetEnableBlur(FALSE);

    CNtlSLEventGenerator::CameraControlDelete(CAMERA_CONTROL_DASH); 
    m_bDashCameraEnable = FALSE;
}

void CNtlBehaviorCharGroundMove::SetDashAnimEnd(void)
{
    if(m_MoveStuff.byType == NTL_MOVETARGET_DASH)
    {
        RwUInt32 uiNextAnimKey = 0;

        if(m_MoveStuff.byMoveFlags == NTL_MOVE_DASH_F)
            uiNextAnimKey = NML_DASH_FRONT_LANDING;
        else if(m_MoveStuff.byMoveFlags == NTL_MOVE_DASH_B)
            uiNextAnimKey = NML_DASH_BACK_LANDING;
        else if(m_MoveStuff.byMoveFlags == NTL_MOVE_DASH_L)
            uiNextAnimKey = NML_DASH_LEFT_LANDING;
        else
            uiNextAnimKey = NML_DASH_RIGHT_LANDING;

        CNtlSobCharProxy *pSobProxy = reinterpret_cast<CNtlSobCharProxy*>(m_pActor->GetSobProxy());
        pSobProxy->SetBaseAnimation(uiNextAnimKey, FALSE);
    }
}

void CNtlBehaviorCharGroundMove::SetServerSyncPosition(RwV3d vSyncPos)
{
    if( m_pActor->GetFlags() & SLFLAG_SERVER_SENDER )
        return;

    RwV3d vSub;
    RwV3d vPos = m_pActor->GetPosition();
    RwV3dSub(&vSub, &vSyncPos, &vPos);

    vSub.y = 0;

    m_bServerSyncPos		= TRUE;
    m_fCurrServerSyncDist	= 0.0f;
    m_fDeltaServerSyncDist	= 0.0f;
    m_fServerSyncDist		= RwV3dLength(&vSub);

    if(m_fServerSyncDist >= 100.0f)
    {
        //		NTL_ASSERTFAIL("CNtlBehaviorCharGroundMove::SetServerSyncPosition");
        m_fServerSyncDist = 0.0f;
    }

    RwV3dNormalize(&m_vServerSyncDir, &vSub);
}

void CNtlBehaviorCharGroundMove::UpdateSendSyncCheck(RwReal fElapsed)
{
    if(!(m_bSyncSendCheck || IsMoveSyncSend()))
        return;

    if( !(m_pActor->GetFlags() & SLFLAG_SERVER_SENDER) )
        return;

    m_fSyncSendTime += fElapsed;

    if(m_fSyncSendTime >= MOVE_SYNC_SEND_TIME)
    {
        if(m_MoveStuff.byType == NTL_MOVETARGET_DIR)
        {
            RwV3d vPos				= m_pActor->GetPosition();
            RwV3d vDir				= m_pActor->GetDirection();
            RwUInt8 byAvatarType	= m_pActor->GetServerSyncAvatarType();

            API_GetSLPacketGenerator()->SendChangePosition(vPos, vDir, byAvatarType);
        }
        else if(m_MoveStuff.byType == NTL_MOVETARGET_LOC)
        {
            RwV3d vPos				= m_pActor->GetPosition();
            RwUInt8 byAvatarType	= m_pActor->GetServerSyncAvatarType();
            API_GetSLPacketGenerator()->SendMouseMove(vPos, m_MoveStuff.vDest, byAvatarType);
        }

        m_fSyncSendTime -= MOVE_SYNC_SEND_TIME;
    }
}



void CNtlBehaviorCharGroundMove::UpdateServerSyncPosition(RwReal fElapsed)
{
    if(!m_bServerSyncPos)
        return;

    if(m_fServerSyncDist == m_fCurrServerSyncDist)
    {
        m_bServerSyncPos = FALSE;
        return;
    }

    m_fDeltaServerSyncDist = m_fServerSyncDist * fElapsed;

    if(m_fCurrServerSyncDist + m_fDeltaServerSyncDist > m_fServerSyncDist)
    {
        m_fDeltaServerSyncDist = m_fServerSyncDist - m_fCurrServerSyncDist;
        m_fCurrServerSyncDist = m_fServerSyncDist;
    }
    else
        m_fCurrServerSyncDist += m_fDeltaServerSyncDist;
}

RwBool CNtlBehaviorCharGroundMove::UpdateDirectionMove(RwReal fElapsed)
{
    RwV3d vPos = m_pActor->GetPosition();
    RwV3d vDir = m_pActor->GetDirection();
    RwReal fOldActorHeight = vPos.y;
    RwV3d vNewPos, vNewDir;

    RwReal fSpeed	= Logic_GetFrontRunSpeed(m_pActor);
    m_fAnimSpeed	= 1.0f;    
    RwBool bMoveSync = FALSE;

    RwBool bTurn = FALSE;
    if(m_MoveStuff.byMoveFlags == NTL_MOVE_TURN_L ||  m_MoveStuff.byMoveFlags == NTL_MOVE_TURN_R)
    {
        bTurn = TRUE;
    }
    else 
    {
        m_fAnimSpeed	= fSpeed / m_fDefaultRunSpeed;        

        if(m_pActor->GetClassID() == SLCLASS_PLAYER)
        {
            bMoveSync = TRUE;
            if(!UpdateMoveSync(fElapsed, &vNewPos, &vNewDir))
                return FALSE;
        }
    }

    if(!bMoveSync)
    {
        CNtlVector vHeading, vDest;        

        //keyboard �̵��� ó���Ѵ�	
        NtlGetDestination_Keyboard(vDir.x, vDir.z, fSpeed, vPos.x, vPos.y, vPos.z, m_MoveStuff.byMoveFlags, (DWORD)(fElapsed*1000.f), 1.0f, &vHeading, &vDest);

        CNtlMath::MathRwV3dAssign(&vNewPos, vDest.x, vPos.y, vDest.z); 
        CNtlMath::MathRwV3dAssign(&vNewDir, vHeading.x, 0.0f, vHeading.z); 

        if(m_bServerSyncPos && !bTurn)
        {
            vNewPos.x += m_vServerSyncDir.x * m_fDeltaServerSyncDist;
            vNewPos.z += m_vServerSyncDir.z * m_fDeltaServerSyncDist;
        }        

        Logic_GetWorldHeight(m_pActor, &vNewPos, m_sHStuff);
        vNewPos.y = m_sHStuff.fFinialHeight;
    }
    
    RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;
    if(!bTurn)
    {
        if(ObjectCollision(vNewPos, fOldActorHeight, fSpeed, fElapsed, &byColliResult))
            return TRUE;
    }

    m_pActor->SetPosition(&vNewPos);
    m_pActor->SetDirection(&vNewDir);

    // ���� �ð� ���� �̵��� �Ÿ��� limit �Ÿ� �ȿ� ������? �����.
    if( !bTurn && byColliResult != NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
    {
        LimitPositionChangeCheck(fElapsed);        
    }

    return FALSE;
}

RwBool CNtlBehaviorCharGroundMove::UpdateLocationMove(RwReal fElapsed)
{
    //-------------------------------------
    // speed �� anim speed ����.
    RwBool bWalkMove = Logic_IsActorWalkMove(m_pActor, m_MoveStuff.byFormFlag);
    RwReal fSpeed; 
    if(bWalkMove)
    {
        fSpeed			= Logic_GetFrontWalkSpeed(m_pActor);
        m_fAnimSpeed	= fSpeed / m_fDefaultWalkSpeed;
    }
    else
    {
        fSpeed			= Logic_GetFrontRunSpeed(m_pActor);
        m_fAnimSpeed	= fSpeed / m_fDefaultRunSpeed;
    }

    //-------------------------------------
    // ���� ���� �Ÿ��� ���Ѵ�.

    RwV3d vPos = m_pActor->GetPosition();
    RwReal fOldActorHeight = vPos.y;
    RwV3d vDestPos = m_MoveStuff.vDest;    
    RwV3d vDir = vDestPos - vPos;    
    vDir.y = 0.0f;

    RwReal fCurrLen = RwV3dLength(&vDir);
    RwV3dNormalize(&vDir, &vDir);    
    RwV3d vDelta = vDir * fElapsed * fSpeed;

    if(m_bServerSyncPos)
    {
        vDelta.x += m_vServerSyncDir.x * m_fDeltaServerSyncDist;
        vDelta.z += m_vServerSyncDir.z * m_fDeltaServerSyncDist;
    }

    //-------------------------------------
    // ���� ���� �ִ� �Ÿ��� ���� �̵��� �Ÿ����� ���� ���.
    if(fCurrLen <= RwV3dLength(&vDelta))
    {
        RwUInt8 bColliResult = NTL_CHARACTER_COLLI_NONE;
        if(fElapsed >= 0.5f)
        {
            if(m_pActor->GetFlags() & SLFLAG_OBJECT_COLLISION)
            {
                RwV3dAssign(&vPos, &vDestPos);
                RwBool bCollMoveImPossible;
                bColliResult = Logic_CharacterCollisionEx(m_pActor, &vPos, fSpeed, vPos, bCollMoveImPossible, fElapsed);

                if(bColliResult == NTL_CHARACTER_COLLI_OBJECT)
                {
                    if(bCollMoveImPossible)
                    {
                        ++m_byCollMoveImpossCnt;
                    }
                }
            }
        }

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;

        m_pActor->SetPosition(&vPos);

        if(bColliResult == NTL_CHARACTER_COLLI_OBJECT)
        {
            // �浹 �ߴµ� ��������ε� �̵��� �Ұ����� ��� �����ش�.
            if(m_byCollMoveImpossCnt >= COLLISION_MOVE_IMPOSSIBLE_COUNT)
            {
                CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
                pBeData->GetMoveStuff()->byMoveResult |= NTL_MOVE_RESULT_COLLISION;                

                return TRUE;
            }

            LimitPositionChangeCheck(fElapsed);

            return FALSE;
        }

        if(PopPathNode(m_MoveStuff.vDest))
            return FALSE;

        return TRUE;
    }
    else // ���� ���� �ִ� �Ÿ��� ���� �̵��� �Ÿ����� ���� ���� ���.
    {
        vPos += vDelta;

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;

        // object �浹 ó��.
        RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;
        if(ObjectCollision(vPos, fOldActorHeight, fSpeed, fElapsed, &byColliResult))
            return TRUE;

        m_pActor->SetDirection(&vDir);
        m_pActor->SetPosition(&vPos);

        if(byColliResult == NTL_CHARACTER_COLLI_NONE)
            return FALSE;

        // ���� �ð� ���� �̵��� �Ÿ��� limit �Ÿ� �ȿ� ������? �����.
        if(byColliResult != NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
        {
            LimitPositionChangeCheck(fElapsed);
        }

        return FALSE;
    }
}

RwBool CNtlBehaviorCharGroundMove::UpdateTargetMove(RwReal fElapsed)
{
    CNtlSobActor *pTargetActor = reinterpret_cast<CNtlSobActor*>(GetNtlSobManager()->GetSobObject(m_MoveStuff.hFollowSerialId));
    if(pTargetActor == NULL)
        return TRUE;

    //RwReal fFollowRange = m_MoveStuff.fFollowRange * FOLLOW_ERROR_RANGE; // �� 0.9�� ���ϴ��� �𸣰ڴ�. �̰Ͷ����� ��ų �ߵ� �Ÿ��� ������ ����� (by agebreak 2009.08.5)
    RwReal fFollowRange = m_MoveStuff.fFollowRange;

    RwV3d vPos = m_pActor->GetPosition();
    RwV3d vDestPos = pTargetActor->GetPosition(); 
    RwReal fOldActorHeight = vPos.y;

    // ���� ���� ���� ���� ����ٴϴ� ��ü�� ���.
    if(pTargetActor->GetFlags() & SLFLAG_CAN_GROUND_FLY)
        vDestPos.y -= Logic_GetGroundFlyHeight(pTargetActor);

    // Ÿ���� �����ϴ� ������ ��쿡�� y����
    SWorldHeightStuff hStuff;
    if(Logic_IsSwimmingActor(pTargetActor, &pTargetActor->GetPosition(), hStuff))
    {
        vDestPos.y = vPos.y = 0.0f;
    }

    RwV3d vDir = vDestPos - vPos;	    

    // ���� ���� �Ÿ��� ���Ѵ�.
    RwReal fCurrLen = RwV3dLength(&vDir);
    vDir.y = 0.0f;
    RwV3dNormalize(&vDir, &vDir);

    m_pActor->SetDirection(&vDir);

    if(fCurrLen < fFollowRange)
    {
        vPos.x = vDestPos.x - vDir.x*fFollowRange;
        vPos.z = vDestPos.z - vDir.z*fFollowRange;

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;

        m_pActor->SetPosition(&vPos);

        return TRUE;
    }

    RwReal fSpeed = SLOW_MOVE_SPEED;
    if(!m_bSlowMove)
    {
        RwBool bWalkMove = Logic_IsActorWalkMove(m_pActor, m_MoveStuff.byFormFlag);
        if(bWalkMove)
        {
            fSpeed			= Logic_GetFrontWalkSpeed(m_pActor);
            m_fAnimSpeed	= fSpeed / m_fDefaultWalkSpeed;
        }
        else
        {
            fSpeed			= Logic_GetFrontRunSpeed(m_pActor);
            m_fAnimSpeed	= fSpeed / m_fDefaultRunSpeed;
        }
    }

    RwV3d vDelta = vDir * fSpeed * fElapsed;	

    // ���� ���� �Ÿ��� �̵� delta �Ÿ����� ���� ���.
    RwReal fDeltaLen = RwV3dLength(&vDelta);
    if(fCurrLen < fDeltaLen + fFollowRange)
    {
        vPos.x = vDestPos.x - vDir.x*fFollowRange;
        vPos.z = vDestPos.z - vDir.z*fFollowRange;

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;

        m_pActor->SetPosition(&vPos);
        return TRUE;
    }

    // ��ǥ update
    vPos += vDelta;    

    Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
    vPos.y = m_sHStuff.fFinialHeight;

    // slow move�� ���.
    if(m_bSlowMove)
    {
        m_fSlowMoveTime += fElapsed;
        if(m_fSlowMoveTime > SLOW_MOVE_TIME)
            return TRUE;
    }

    // �浹 üũ.
    RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;

    if(m_pActor->GetFlags() & SLFLAG_OBJECT_COLLISION)
    {
        RwBool bCollMoveImPossible;
        byColliResult = Logic_CharacterCollisionEx(m_pActor, &vPos, fSpeed, vPos, bCollMoveImPossible, fElapsed);

        if(byColliResult == NTL_CHARACTER_COLLI_OBJECT)
        {
            if(bCollMoveImPossible)
                m_byCollMoveImpossCnt++;
            else
                m_byCollMoveImpossCnt = 0;

            vPos.y = m_sHStuff.fFinialHeight;
        }
        else if(byColliResult == NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
        {
            if(m_byDashState == DASH_STATE_MOVE)
            {
                SetDashAnimEnd();
                m_byDashState = DASH_STATE_END;
                return FALSE;
            }
            else
            {
                return TRUE;
            }
        }

        // �浹 �ߴµ� ��������ε� �̵��� �Ұ����� ��� �����ش�.
        if(m_byCollMoveImpossCnt >= COLLISION_MOVE_IMPOSSIBLE_COUNT)
        {
            CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
            SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
            pMoveStuff->byMoveResult |= NTL_MOVE_RESULT_COLLISION;

            return TRUE;
        }
    }

    // ���� üũ
    if(CheckFalling(fOldActorHeight, m_sHStuff.fFinialHeight, fSpeed, NTL_MOVE_F))
        return TRUE;


    m_pActor->SetPosition(&vPos);

    if(byColliResult == NTL_CHARACTER_COLLI_NONE)
        return FALSE;

    // ���� �ð� ���� �̵��� �Ÿ��� limit �Ÿ� �ȿ� ������? �����.
    if(byColliResult != NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
    {
        LimitPositionChangeCheck(fElapsed);
    }

    return FALSE;
}

RwBool CNtlBehaviorCharGroundMove::UpdateDashMove(RwReal fElapsed)
{
    if(m_byDashState == DASH_STATE_END)
    {
        m_fEffectSmokeTime += fElapsed;
        if(m_fEffectSmokeTime > 0.1f)
        {
            DestroyDashEffect();
            DestroyDashEffectSmoke();
        }

        return TRUE;
    }

    RwV3d vPos = m_pActor->GetPosition();
    CNtlVector vNewPos;

    RwV3d vDestPos = m_MoveStuff.vDest;    

    
    RwV3d vDir = vDestPos - vPos;
    RwV3d v2dSub = vDir;
    v2dSub.y = 0.0f;    

    RwReal f2dCurrLen = RwV3dLength(&v2dSub);
    RwReal fCurrLen = RwV3dLength(&vDir);

    if(m_byDashState == DASH_STATE_MOVE)
    {
        if(fCurrLen <= m_fDashLadingDist)
        {
            m_byDashState = DASH_STATE_LANDING;
            SetDashAnimEnd();
        }
    }

    
    if(f2dCurrLen <= NTL_EPSILON || fCurrLen <= NTL_DASH_SPEED * fElapsed)
    {
        // �ε������� elapsed time�� ���� ���� ����� ��� �ڵ�.
        // ���� ���ϴ� �κ��� ��� �ڵ�.. 
        // ���� ���ϴ� ������.. character�� ���� ��ǥ + ���� ���̷� �ϱ� �����̴�.

        RwBool bSuccess = FALSE;
        RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;
        if(fElapsed >= 0.5f)
        {
            if(m_pActor->GetFlags() & SLFLAG_OBJECT_COLLISION)
            {
                RwV3dAssign(&vPos, &vDestPos);
                RwBool bCollMoveImPossible;

                byColliResult = Logic_CharacterCollisionEx(m_pActor, &vPos, NTL_DASH_SPEED, vPos, bCollMoveImPossible, fElapsed);

                if(byColliResult == NTL_CHARACTER_COLLI_OBJECT)
                {
                    if(bCollMoveImPossible)
                        m_byCollMoveImpossCnt++;
                }
            }
        }

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;
        m_MoveStuff.vDest.y = m_sHStuff.fFinialHeight;
        vDir.y = 0.0f;

        m_pActor->SetPosition(&vPos);

        if(byColliResult == NTL_CHARACTER_COLLI_OBJECT)
        {
            // �浹 �ߴµ� ��������ε� �̵��� �Ұ����� ��� �����ش�.
            if(m_byCollMoveImpossCnt >= COLLISION_MOVE_IMPOSSIBLE_COUNT)
            {
                CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
                SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
                pMoveStuff->byMoveResult |= NTL_MOVE_RESULT_COLLISION;

                bSuccess = TRUE;
            }
            else
            {
                LimitPositionChangeCheck(fElapsed);
                bSuccess = FALSE;
            }

            return FALSE;
        }
        else
        {
            bSuccess = TRUE;
        }

        if(bSuccess)
        {
            if(m_byDashState == DASH_STATE_MOVE)
            {
                SetDashAnimEnd();
            }

            DestroyEndDashCamera();

            m_byDashState = DASH_STATE_END;
        }
    }

    RwV3dNormalize(&vDir, &vDir); 
    RwReal fSpeed = NTL_DASH_SPEED * fElapsed;

    // data�� �ε��Ͽ� ���ڱ� elapsed time�� ũ�� ���� ��� �̷� ��찡 �����
    if(fSpeed >= fCurrLen)
    {
        fSpeed = fCurrLen;
        vPos += vDir * fSpeed;
        vPos.y = max(m_MoveStuff.vDest.y, vPos.y);        
    }
    else
    {
        vPos += vDir * fSpeed;        
        RwReal fCurrPosY = vPos.y;

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = max(m_sHStuff.fFinialHeight, vPos.y);        

        if(fCurrPosY < vPos.y && m_MoveStuff.vDest.y < vPos.y)
        {
            m_MoveStuff.vDest.y = vPos.y + fabs(fCurrPosY - vPos.y);
        }
        else
        {
            m_MoveStuff.vDest.y = m_fDashDestPosY;
        }
    }

    RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;
    if(m_pActor->GetFlags() & SLFLAG_OBJECT_COLLISION)
    {
        RwV2d vOld2DPos;
        vOld2DPos.x = vPos.x;
        vOld2DPos.y = vPos.z;

        RwBool bCollMoveImPossible;
        RwV3d vNewPosV3d;
        byColliResult = Logic_CharacterCollisionEx(m_pActor, &vPos, NTL_DASH_SPEED, vNewPosV3d, bCollMoveImPossible, fElapsed);

        if(byColliResult == NTL_CHARACTER_COLLI_OBJECT)
        {
            if(bCollMoveImPossible)
                m_byCollMoveImpossCnt++;
            else
                m_byCollMoveImpossCnt = 0;

            vPos.x = vNewPosV3d.x;
            vPos.z = vNewPosV3d.z;

            RwV2d vNew2DPos;
            vNew2DPos.x = vPos.x;
            vNew2DPos.y = vPos.z;
            RwV2dSub(&vNew2DPos, &vNew2DPos, &vOld2DPos);

            RwReal fCollDeltaLen = RwV2dLength(&vNew2DPos);
            vNewPos.y += fCollDeltaLen*4;

            Logic_GetWorldHeight(m_pActor, &vNewPosV3d, m_sHStuff);
            if(vPos.y <= m_sHStuff.fFinialHeight )
                vPos.y = m_sHStuff.fFinialHeight;

            if(m_MoveStuff.vDest.y < vPos.y)
                m_MoveStuff.vDest.y = vPos.y + 0.01f;
        }
        else if(byColliResult == NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
        {
            if(m_byDashState == DASH_STATE_MOVE)
            {
                SetDashAnimEnd();
                m_byDashState = DASH_STATE_END;
                return FALSE;
            }
            else
            {
                return TRUE;
            }
        }

        // �浹 �ߴµ� ��������ε� �̵��� �Ұ����� ��� �����ش�.
        if(m_byCollMoveImpossCnt >= COLLISION_MOVE_IMPOSSIBLE_COUNT)
        {
            CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
            SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
            pMoveStuff->byMoveResult |= NTL_MOVE_RESULT_COLLISION;

            if(m_byDashState == DASH_STATE_MOVE)
                SetDashAnimEnd();

            m_byDashState = DASH_STATE_END;
            return TRUE;
        }
    }

    m_pActor->SetPosition(&vPos);

    // ���� �ð� ���� �̵��� �Ÿ��� limit �Ÿ� �ȿ� ������? �����.
    if(byColliResult != NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
    {
        LimitPositionChangeCheck(fElapsed);
    }

    // effect position update
    if(m_pDashEffect)
    {
        vPos = vPos + m_vDashEffOffset;
        m_pDashEffect->SetPosition(&vPos);
    }

    UpdateDashLineEffect(vPos, vDir);

    if(m_pDashEffectSmoke)
        m_pDashEffectSmoke->SetPosition(&vPos);

    return FALSE;
}


RwBool CNtlBehaviorCharGroundMove::UpdateDashTargetMove(RwReal fElapsed)
{
    CNtlSobActor *pTargetActor = reinterpret_cast<CNtlSobActor*>(GetNtlSobManager()->GetSobObject(m_MoveStuff.hFollowSerialId));
    if(pTargetActor == NULL)
        return TRUE;

    RwReal fFollowRange = m_MoveStuff.fFollowRange*FOLLOW_ERROR_RANGE;

    RwV3d vPos = m_pActor->GetPosition();
    RwV3d vDestPos = pTargetActor->GetPosition(); 

    // ���� ���� ���� ���� ����ٴϴ� ��ü�� ���.
    if(pTargetActor->GetFlags() & SLFLAG_CAN_GROUND_FLY)
        vDestPos.y -= Logic_GetGroundFlyHeight(pTargetActor);

    RwV3d vDir;
    RwV3dSub(&vDir, &vDestPos, &vPos); 

    // ���� ���� �Ÿ��� ���Ѵ�.
    RwReal fCurrLen = RwV3dLength(&vDir);
    vDir.y = 0.0f;
    RwV3dNormalize(&vDir, &vDir);

    m_pActor->SetDirection(&vDir);

    if(fCurrLen < fFollowRange)
    {
        vPos.x = vDestPos.x - vDir.x*fFollowRange;
        vPos.z = vDestPos.z - vDir.z*fFollowRange;

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;

        m_pActor->SetPosition(&vPos);

        return TRUE;
    }

    RwReal fSpeed = NTL_ACTIVE_DASH_SPEED;

    RwV3d vDelta;
    CNtlMath::MathRwV3dAssign(&vDelta, vDir.x * fElapsed * fSpeed, 0.0f, vDir.z*fElapsed*fSpeed);

    // ���� ���� �Ÿ��� �̵� delta �Ÿ����� ���� ���.
    RwReal fDeltaLen = RwV3dLength(&vDelta);
    if(fCurrLen < fDeltaLen + fFollowRange)
    {
        vPos.x = vDestPos.x - vDir.x*fFollowRange;
        vPos.z = vDestPos.z - vDir.z*fFollowRange;

        Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
        vPos.y = m_sHStuff.fFinialHeight;

        m_pActor->SetPosition(&vPos);
        return TRUE;
    }

    // position update
    RwV3dAdd(&vPos, &vPos, &vDelta);  

    Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
    vPos.y = m_sHStuff.fFinialHeight;

    RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;
    if(m_pActor->GetFlags() & SLFLAG_OBJECT_COLLISION)
    {
        RwBool bCollMoveImPossible;
        byColliResult = Logic_CharacterCollisionEx(m_pActor, &vPos, NTL_DASH_SPEED, vPos, bCollMoveImPossible, fElapsed);

        if(byColliResult == NTL_CHARACTER_COLLI_OBJECT)
        {
            if(bCollMoveImPossible)
                m_byCollMoveImpossCnt++;
            else
                m_byCollMoveImpossCnt = 0;

            Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
            vPos.y = m_sHStuff.fFinialHeight;
        }
        else if(byColliResult == NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
        {
            if(m_byDashState == DASH_STATE_MOVE)
            {
                SetDashAnimEnd();
                m_byDashState = DASH_STATE_END;
                return FALSE;
            }
            else
            {
                return TRUE;
            }
        }

        // �浹 �ߴµ� ��������ε� �̵��� �Ұ����� ��� �����ش�.
        if(m_byCollMoveImpossCnt >= COLLISION_MOVE_IMPOSSIBLE_COUNT)
        {
            CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
            SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
            pMoveStuff->byMoveResult |= NTL_MOVE_RESULT_COLLISION;

            return TRUE;
        }
    }

    // ���ο� ��ǥ setting
    m_pActor->SetPosition(&vPos);

    // ���� �ð� ���� �̵��� �Ÿ��� limit �Ÿ� �ȿ� ������? �����.
    if(byColliResult != NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
    {
        LimitPositionChangeCheck(fElapsed);
    }

    // effect update
    // effect position update
    UpdateDashEffect(NTL_MOVE_DASH_F, vDir);

    return FALSE;
}


void CNtlBehaviorCharGroundMove::CreateDashEffect(RwUInt32 uiMoveDirFlags)
{
    if(!m_pActor)
        return;

    DestroyDashEffect();
    DestroyDashEffectSmoke();

    CNtlPLAttach* pPLChar = (CNtlPLAttach*)m_pActor->GetSobProxy()->GetPLMainEntity();

    m_pDashEffect = GetSceneManager()->CreateEntity(PLENTITY_EFFECT, NTL_VID_DASH_ACTIVE_01);
    pPLChar->Attach((CNtlPLAttach*)m_pDashEffect);

    m_pDashEffectSmoke = GetSceneManager()->CreateEntity(PLENTITY_EFFECT, NTL_VID_DASH_ACTIVE_02);
    pPLChar->Attach((CNtlPLAttach*)m_pDashEffectSmoke);    

    if(m_pActor->GetClassID() == SLCLASS_AVATAR)
        m_pDashLine = GetSceneManager()->CreateEntity(PLENTITY_EFFECT, NTL_VID_DASH_LINE);
}

void CNtlBehaviorCharGroundMove::DestroyDashEffect(void)
{
    if(m_pDashEffect)
    {
        m_pDashEffect->Finish();
        m_pDashEffect = NULL;
    }

    if(m_pDashLine)
    {
        m_pDashLine->Finish();
        m_pDashLine = NULL;
    }
}

void CNtlBehaviorCharGroundMove::DestroyDashEffectSmoke(void)
{
    if(m_pDashEffectSmoke)
    {
        //		GetSceneManager()->DeleteEntity(m_pDashEffectSmoke);
        m_pDashEffectSmoke->Finish();
        m_pDashEffectSmoke = NULL;
    }
}

void CNtlBehaviorCharGroundMove::UpdateDashEffect(RwUInt32 uiMoveDirFlags, RwV3d& vDir)
{
    RwV3d vPos = m_pActor->GetPosition();

    // �ڿ� ���� �ٴ� effect
    RwMatrix mat;
    RwMatrixSetIdentity(&mat);

    RwV3dAssign(&mat.at, &vDir);
    RwV3dCrossProduct(&mat.right, &mat.at, &CNtlPLGlobal::m_vYAxisV3);  
    RwV3dNormalize(&mat.right, &mat.right);
    RwV3dCrossProduct(&mat.up, &mat.at, &mat.right);  
    RwV3dNormalize(&mat.up, &mat.up);
    RwV3dAssign(&mat.up, &CNtlPLGlobal::m_vYAxisV3);
    RwMatrixUpdate(&mat);

    // effect ���� setting.
    if(uiMoveDirFlags == NTL_MOVE_DASH_F)
        CNtlMath::MathRwV3dAssign(&m_vDashEffOffset, vDir.x*0.6f, 0.86f, vDir.z*0.6f);
    else if(uiMoveDirFlags == NTL_MOVE_DASH_B)
        CNtlMath::MathRwV3dAssign(&m_vDashEffOffset, vDir.x*0.45f, 0.86f, vDir.z*0.45f);
    else if(uiMoveDirFlags == NTL_MOVE_DASH_L)
        CNtlMath::MathRwV3dAssign(&m_vDashEffOffset, vDir.x*0.6f, 0.86f, vDir.z*0.6f);
    else
        CNtlMath::MathRwV3dAssign(&m_vDashEffOffset, vDir.x*0.6f, 0.86f, vDir.z*0.6f);

    if(m_pDashEffectSmoke)
        m_pDashEffectSmoke->SetPosition(&vPos);

    if(m_pDashLine)
        m_pDashLine->SetMatrix(mat);

    RwV3dAdd(&vPos, &vPos, &m_vDashEffOffset);
    RwMatrixTranslate(&mat, &vPos, rwCOMBINEPOSTCONCAT);

    if(m_pDashEffect)
        m_pDashEffect->SetMatrix(mat);
}

void CNtlBehaviorCharGroundMove::UpdateDashLineEffect(RwV3d& vPos, RwV3d& vDir)
{
    if(m_pDashLine)
    {
        m_pDashLine->SetPosition(&vPos);

        // ī�޶� ���� ������
        RwMatrix *pMatrix = RwFrameGetMatrix( RwCameraGetFrame( CNtlPLGlobal::m_RwCamera ) );
        RwV3d *pCamDir = RwMatrixGetAt( pMatrix );

        RwReal fValue = RwV3dDotProduct(&vDir, pCamDir);
        if(fValue < -0.9f)
            m_pDashLine->SetAlpha(80);
        else
            m_pDashLine->SetAlpha(255);
    }

}

RwBool CNtlBehaviorCharGroundMove::UpdateMoveSync(RwReal fElapsedTime, OUT RwV3d* pDestPos, OUT RwV3d* pNewDir)
{
    CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
    SMoveSyncStuff* pMoveSyncStuff = pBeData->GetMoveSyncStuff();

    if(pMoveSyncStuff->m_pMoveSyncCurr == NULL)
    {
        if(pMoveSyncStuff->Next() == NULL)         // ���� ��Ŷ�� ���޾Ҵ�        
            return FALSE;
    }
    else
    {
        if(!pMoveSyncStuff->m_MoveSyncQ.empty())        // ���� ��Ŷ�� �޾Ƽ� ó���Ѵ�.
        {
            pMoveSyncStuff->Next();
        }
    }   
    
    RwUInt8 byMoveFlags = pBeData->GetMoveStuff()->byMoveFlags;
    RwV3d vPos = m_pActor->GetPosition();      
    RwV3d vDestPos, vDestDir, vMoveDir;    
    RwV3dNormalize(&vMoveDir, &m_pActor->GetDirection());

    RwReal fSpeed = GetMoveSpeed(pMoveSyncStuff->m_pMoveSyncCurr->byMoveFlag);                

    //keyboard �̵��� ó���Ѵ�	
    CNtlVector vHeading, vDest;
    NtlGetDestination_Keyboard(vMoveDir.x, vMoveDir.z, fSpeed, vPos.x, vPos.y, vPos.z, byMoveFlags, (DWORD)(fElapsedTime * 1000.f), 1.0f, &vHeading, &vDest);
    CNtlMath::MathRwV3dAssign(&vDestPos, vDest.x, vDest.y, vDest.z);      
    CNtlMath::MathRwV3dAssign(&vDestDir, vHeading.x, 0.0f, vHeading.z);

    // ���� MoveSync�� ���� �־���� ��ġ�� ����� ��, �� ��ġ�� �������� ������ �����Ѵ�.    
    RwV3d vSyncDir = pMoveSyncStuff->m_pMoveSyncCurr->vLoc - vDestPos;
    vSyncDir.y = 0.0f;
    RwV3dNormalize(&vSyncDir, &vSyncDir);
    RwReal fSyncDistance = CNtlMath::GetLength(pMoveSyncStuff->m_pMoveSyncCurr->vLoc, vDestPos);        
    RwV3d vMoveDest = vSyncDir * (fSyncDistance / MOVE_SYNC_SPEED) * fElapsedTime;    
    vDestPos += vMoveDest;

    // ���� ����
    *pNewDir = pMoveSyncStuff->m_pMoveSyncCurr->vDir;
    //*pNewDir = vSyncDir;  // ���� �������� �����ϸ� �ڷ� ���� ������ �����, �ٸ� �κп� �浹�� �����.
    
    
    // ���� ��ġ    
    Logic_GetWorldHeight(m_pActor, &vDestPos, m_sHStuff);
    vDestPos.y = m_sHStuff.fFinialHeight;
    *pDestPos = vDestPos;    

    SetAnim(pMoveSyncStuff->m_pMoveSyncCurr->byMoveFlag);

    return TRUE;
}

RwBool CNtlBehaviorCharGroundMove::CheckFalling(RwReal fOldActorHeight, RwReal fFinalHeight, RwReal fSpeed, RwUInt8 byMoveFlag, RwV3d* pNewPos /* = NULL */)
{
    if( m_pActor->GetFlags() & SLFLAG_FALLING_ENABLE && fOldActorHeight - fFinalHeight > FALLING_CHECK_LEN)
    {
        CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 

        SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
        pMoveStuff->byMoveResult |= NTL_MOVE_RESULT_FALLING;

        SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff();

        if(pNewPos)
        {
            RwV3d vSub = *pNewPos - m_pActor->GetPosition();        
            vSub.y = 0.0f;
            RwV3dNormalize(&pCtrlStuff->uExtra.sFalling.vFallingDir, &vSub);
        }
        else
        {
            pCtrlStuff->uExtra.sFalling.vFallingDir = m_pActor->GetDirection();
        }

        pCtrlStuff->uExtra.sFalling.byMoveFlags = byMoveFlag;
        pCtrlStuff->uExtra.sFalling.fSpeed = (byMoveFlag == NTL_MOVE_B)? fSpeed * NTL_BACKWARD_MOVEMENT_SPEED_RATE: fSpeed;
        pCtrlStuff->uExtra.sFalling.fSearchHeight = m_sHStuff.fFinialHeight;

        return TRUE;
    }

    return FALSE;
}

RwBool CNtlBehaviorCharGroundMove::ObjectCollision(OUT RwV3d &vPos, RwReal fOldActorHeight, RwReal fSpeed, RwReal fElapsed, OUT RwUInt8* pColliResult)
{
    RwUInt8 byColliResult = NTL_CHARACTER_COLLI_NONE;
    if(m_pActor->GetFlags() & SLFLAG_OBJECT_COLLISION)
    {
        //RwV2d vOld2DPos;
        //vOld2DPos.x = vPos.x;
        //vOld2DPos.y = vPos.z;

        RwBool bCollMoveImPossible;
        byColliResult = Logic_CharacterCollisionEx(m_pActor, &vPos, fSpeed, vPos, bCollMoveImPossible, fElapsed);
        *pColliResult = byColliResult;

        // ������ ���⳪, �Ӽ��� ���� �浹�� ��� �� �ڸ��� �����.
        if(byColliResult == NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT)
        {
            return TRUE;
        }

        if(byColliResult == NTL_CHARACTER_COLLI_OBJECT)
        {
            m_byCollMoveImpossCnt = bCollMoveImPossible ? ++m_byCollMoveImpossCnt : 0;

            // �� �ڵ尡 �� �ִ��� �𸣰ڴ�?? (by agebreak 09.08.13)

			// - lleo52 09.08.18
			//   �Ʒ� �ڵ尡 �� ������ ������Ʈ�� ������ ��츦 ���� ���ؼ���
			//	 �ּ� ó�� �� �׽�Ʈ ��� ���� ���� ����
			//	 �켱 �Ʒ� �ڵ�� �ּ� ó���� �ϰ� ��Ȳ�� ���Ѻ��ƾ� �� �� ����

			//RwV2d vNew2DPos;
			//vNew2DPos.x = vPos.x;
			//vNew2DPos.y = vPos.z;
			//RwReal fOffset = CNtlMath::GetLength(vNew2DPos, vOld2DPos) * 2;
			//vPos.y += fOffset;

            Logic_GetWorldHeight(m_pActor, &vPos, m_sHStuff);
            vPos.y = m_sHStuff.fFinialHeight;
            //////////////////////////////////////////////////////////////////////////
        }
        else if(byColliResult == NTL_CHARACTER_COLLI_WORLD_ATTR_TERRAIN_SLANT && Logic_IsDirectMode(m_pActor))
        {
            CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData());                 
            pBeData->GetMoveStuff()->byMoveResult |= NTL_MOVE_RESULT_COLLISION;                

            return TRUE;                
        }            
    }
    
    // �浹 �ߴµ� ��������ε� �̵��� �Ұ����� ��� �����ش�.
    if(m_byCollMoveImpossCnt >= COLLISION_MOVE_IMPOSSIBLE_COUNT)
    {
        CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData());                 
        pBeData->GetMoveStuff()->byMoveResult |= NTL_MOVE_RESULT_COLLISION;      

        return TRUE;
    }

    // falling state check
    if(CheckFalling(fOldActorHeight, m_sHStuff.fFinialHeight, fSpeed, m_MoveStuff.byMoveFlags, &vPos))
        return TRUE;

    return FALSE;
}

RwBool CNtlBehaviorCharGroundMove::IsIdleAnimationPlaying()
{
    CNtlSobCharProxy *pSobProxy = reinterpret_cast<CNtlSobCharProxy*>(m_pActor->GetSobProxy());
    RwUInt32 uiCurrAnimKey = pSobProxy->GetBaseAnimationKey();

    if(uiCurrAnimKey == TRANS_IDLE || uiCurrAnimKey == NML_IDLE_01 || 
       uiCurrAnimKey == NML_IDLE_LOOP || uiCurrAnimKey == NML_IDLE_02 ||
       uiCurrAnimKey == NML_STAFF_IDLE_LOOP || uiCurrAnimKey == NML_STAFF_IDLE_01 ||
       uiCurrAnimKey == NML_STAFF_IDLE_02 || uiCurrAnimKey == NML_DGUN_IDLE_LOOP || 
       uiCurrAnimKey == NML_DGUN_IDLE_01 || uiCurrAnimKey == NML_DGUN_IDLE_02)
    {
        return TRUE;
    }

    return FALSE;
}