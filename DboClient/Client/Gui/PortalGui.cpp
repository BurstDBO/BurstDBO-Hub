#include "precomp_dboclient.h"
#include "PortalGui.h"
#include "NtlDebug.h"

// PL
#include "NtlPLGuiManager.h"

// sound
#include "GUISoundDefine.h"


// Simul
#include "NtlSLApi.h"
#include "TableContainer.h"
#include "PortalTable.h"
#include "NtlSobNpc.h"
#include "NtlSobNpcAttr.h"
#include "NtlSobManager.h"
#include "NtlSLEventFunc.h"
#include "NtlCameraController.h"
#include "NtlSlGlobal.h"
#include "NtlSobAvatar.h"
#include "NtlResultCode.h"
#include "NPCTable.h"

// DBO
#include "DboGlobal.h"
#include "DboEvent.h"
#include "DboEventHandler.h"
#include "DialogManager.h"
#include "gui_texturemanager.h"
#include "InfoWndManager.h"
#include "DboEventGenerator.h"
#include "DisplayStringManager.h"
#include "MsgBoxManager.h"

CPortalGui::CPortalGui( const RwChar* pName ) 
:CNtlPLGui(pName)
{

}
CPortalGui::~CPortalGui() 
{

}

VOID CPortalGui::Init() 
{
    m_nCurrIdx = 0;
    m_nSelectIdx = 0;
    m_hNPCSerialID = INVALID_SERIAL_ID;
    m_bTeleportSuccess = FALSE;
}

RwBool CPortalGui::Create() 
{
    if(!CNtlPLGui::Create("","gui\\Portal.srf", "gui\\Portal.frm"))
        NTL_RETURN(FALSE);

    Init();    

    CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

    m_pThis = (gui::CDialog*)GetComponent("dlgMain");
    m_pBtnExit = (gui::CButton*)GetComponent("btnExit");
    m_pSttStartPoint = (gui::CStaticBox*)GetComponent("sttStartPoint");
    m_pSttEnablePoint = (gui::CStaticBox*)GetComponent("sttEnablePoint");    

    m_pSttStartPoint->SetText(GetDisplayStringManager()->GetString(DST_PORTAL_ICON_START));
    m_pSttEnablePoint->SetText(GetDisplayStringManager()->GetString(DST_PORTAL_ICON_ENABLE));    

    m_slotMouseMove = m_pThis->SigMouseMove().Connect(this, &CPortalGui::OnMouseMove);
    m_slotMouseUp = m_pThis->SigMouseUp().Connect(this, &CPortalGui::OnMouseUp);    
    m_slotPaint   = m_pThis->SigPaint().Connect(this, &CPortalGui::OnPaint);
    m_slotMove    = m_pThis->SigMove().Connect(this, &CPortalGui::OnMove);

    m_slotBtnExit = m_pBtnExit->SigClicked().Connect(this, &CPortalGui::OnClickExitBtn);

    LinkMsg(g_EventNPCDialogOpen);
    LinkMsg(g_EventPortalStartRes);
    LinkMsg(g_EventPortalInfoRes);
    LinkMsg(g_EventPortalAddRes);
    LinkMsg(g_EventPortalRes);
    LinkMsg(g_EventMsgBoxResult);
    LinkMsg(g_EventDialog);

    // ��Ż���� ��ġ �������� �����Ѵ�.
    SetupPortalInfo();

    Show(false);

    return TRUE;
}

VOID CPortalGui::Destroy() 
{
    UnLinkMsg(g_EventNPCDialogOpen);
    UnLinkMsg(g_EventPortalStartRes);
    UnLinkMsg(g_EventPortalInfoRes);
    UnLinkMsg(g_EventPortalAddRes);
    UnLinkMsg(g_EventPortalRes);
    UnLinkMsg(g_EventMsgBoxResult);
    UnLinkMsg(g_EventDialog);

    for each(PAIRPortalInfo pair in m_mapPortalInfo)
    {
        NTL_DELETE(pair.second);
    }
    m_mapPortalInfo.clear();

    CNtlPLGui::DestroyComponents();
    CNtlPLGui::Destroy();
}


RwInt32 CPortalGui::SwitchDialog( bool bOpen ) 
{
    Show(bOpen);

    if(bOpen)
    {
        UpdatePortalInfo();
        m_bTeleportSuccess = FALSE;                     // ���߿� ������ Ŭ�����ư���� ��������, ��Ż ���η� �������� �Ǵ��ϴ� �÷���
    }
    else
    {
        if(GetInfoWndManager()->GetRequestGui() == DIALOG_PORTAL)
        {
            GetInfoWndManager()->ShowInfoWindow(FALSE);
        }    

        if(!m_bTeleportSuccess)     // ��Ż�� �������� ī�޶� ���� �ʴ´�.
        {
            CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
            GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
        }        

		GetMsgBoxManager()->DeleteMsgBox( DST_PORTAL_CONFIRM );
    }

    return TRUE;
}

VOID CPortalGui::HandleEvents(RWS::CMsg &pMsg)
{
    if(pMsg.Id == g_EventNPCDialogOpen)     // Dialog Open
    {
        SDboNpcDialogOpen* pData = reinterpret_cast<SDboNpcDialogOpen*>(pMsg.pData);

        if(pData->eDialog != DIALOG_PORTAL)
            return;

        if(GetDialogManager()->IsOpenDialog(DIALOG_PORTAL))
            return;

		RwBool	bPacketLock		= FALSE;
		bool	bSendSuccess	= GetDboGlobal()->GetGamePacketGenerator()->SendPortalStartReq(pData->hSerialId, &bPacketLock);

		if( bPacketLock && !bSendSuccess )
		{
			GetNtlWorldConcept()->RemoveWorldPlayConcept( WORLD_PLAY_NPC_COMMU );
			CNtlSLEventGenerator::CameraControlDelete( CAMERA_CONTROL_NPC );
			return;
		}

		m_hNPCSerialID = pData->hSerialId;
    }    
    else if(pMsg.Id == g_EventPortalStartRes)   // Portal Start
    {
        SNtlEventPortalStartRes* pData = reinterpret_cast<SNtlEventPortalStartRes*>(pMsg.pData);
        if(pData->wResultCode == GAME_SUCCESS)
        {
            // ���� ��Ż��ġ�� ��ϵǾ� �ִ��� Ȯ���Ѵ�. ��ϵǾ� ���� ������ ����� �� UI�� ����Ѵ�.
            if(CheckRegist(m_hNPCSerialID))
            {
                GetDialogManager()->OpenDialog(DIALOG_PORTAL, m_hNPCSerialID);    
            }            
        }
        else
        {
            CDboEventGenerator::DialogEvent(DIALOGEVENT_OPEN_FAIL_NPC_DIALOG, PLACE_NONE, DIALOG_PORTAL);            
            CNtlSLEventGenerator::SysMsg(GetNtlSLGlobal()->GetSobAvatar()->GetSerialID(), pData->wResultCode);
            GetDialogManager()->CloseDialog(DIALOG_PORTAL);
        }
    }
    else if(pMsg.Id == g_EventDialog)       // ���̾�α� Fail�� ���� ó��
    {
        SDboEventDialog* pData = reinterpret_cast<SDboEventDialog*>(pMsg.pData);
        if(pData->iDestDialog == DIALOG_PORTAL)
        {
            if(pData->iType == DIALOGEVENT_OPEN_FAIL_NPC_DIALOG)
            {
                GetNtlWorldConcept()->RemoveWorldPlayConcept(WORLD_PLAY_NPC_COMMU);
                CNtlSLEventGenerator::CameraControlDelete(CAMERA_CONTROL_NPC);
                GetDialogManager()->CloseDialog(DIALOG_PORTAL);
            }
			else if( pData->iType == DIALOGEVENT_NPC_BYEBYE && pData->iDestDialog == DIALOG_PORTAL )
			{
				GetDialogManager()->CloseDialog(DIALOG_PORTAL);
			}
        }
    }
    else if(pMsg.Id == g_EventPortalInfoRes)    // Portal ������ ������ ���� ������
    {
        SNtlEventPortalInfoRes* pData = reinterpret_cast<SNtlEventPortalInfoRes*>(pMsg.pData);                    
        SetPortalInfo(pData);
    }
    else if(pMsg.Id == g_EventPortalAddRes)     // �ű� ��Ż ��Ͽ� ���� ����
    {
        SNtlEventPortalAddRes* pData = reinterpret_cast<SNtlEventPortalAddRes*>(pMsg.pData);
        if(pData->wResultCode == GAME_SUCCESS)
        {
            if(m_mapPortalInfo.find(pData->portalID) != m_mapPortalInfo.end())
            {
                m_mapPortalInfo[pData->portalID]->m_bRegist = TRUE;    
            }
            
            if(m_hNPCSerialID != INVALID_SERIAL_ID)
            {
                GetDialogManager()->OpenDialog(DIALOG_PORTAL, m_hNPCSerialID);    
            }            
        }
        else
        {
            CNtlSLEventGenerator::SysMsg(GetNtlSLGlobal()->GetSobAvatar()->GetSerialID(), pData->wResultCode);
        }
    }
    else if(pMsg.Id == g_EventPortalRes)        // ���� ��Ż ��û�� ���� ����
    {
        SNtlEventPortalRes* pData = reinterpret_cast<SNtlEventPortalRes*>(pMsg.pData);
        if(pData->wResultCode == GAME_SUCCESS)
        {
            m_bTeleportSuccess = TRUE;
            GetDialogManager()->CloseDialog(DIALOG_PORTAL);
        }
        else
        {
            CNtlSLEventGenerator::SysMsg(GetNtlSLGlobal()->GetSobAvatar()->GetSerialID(), pData->wResultCode);
        }
    }
    else if(pMsg.Id == g_EventMsgBoxResult)     // �ű� ��Ż ��� �޽��� �ڽ����� Ȯ�� ��ư Ŭ����
    {
        SDboEventMsgBoxResult *pMsgBoxResult = reinterpret_cast<SDboEventMsgBoxResult*>( pMsg.pData );
        if( pMsgBoxResult->eResult == MBR_OK && pMsgBoxResult->uiWorkId == MBW_PORTAL_ADD_OK)
        {
            GetDboGlobal()->GetGamePacketGenerator()->SendPortalAddReq(m_hNPCSerialID);
        }        
    }
}

VOID CPortalGui::SetupPortalInfo() 
{
    // ��Ż �����ܵ��� ������ ��ġ�� ��ġ ��Ų��.
    m_mapPortalInfo.clear();    

    CPortalTable* pPortalTable = (CPortalTable*)API_GetTableContainer()->GetPortalTable();    
    if(!pPortalTable)
        return;

    sPORTAL_TBLDAT* pPortalData = NULL;
    for(CTable::TABLEIT it = pPortalTable->Begin(); it != pPortalTable->End(); ++it)
    {
        pPortalData = (sPORTAL_TBLDAT*)(*it).second;
        if(pPortalData)
        {
            SPortalInfo* pPortalInfo = NTL_NEW SPortalInfo();
            pPortalInfo->m_nIndex = (*it).first;            
            pPortalInfo->m_eIconType = E_PORTAL_ICON_NOT;  
            pPortalInfo->m_bRegist = FALSE;            
            m_mapPortalInfo[pPortalInfo->m_nIndex] = pPortalInfo;
        }
    }

    // ICON�� ���� �����̽����� �����Ѵ�. (�ε��� + 1�� Ȱ��ȭ �������� �����̽�)    
    m_aSurIcon[E_PORTAL_ICON_START_POINT]     = CNtlPLGuiManager::GetInstance()->GetSurfaceManager()->GetSurface("Portal.srf", "srfIconStartPoint");
    m_aSurIcon[E_PORTAL_ICON_START_POINT_FOCUS] = CNtlPLGuiManager::GetInstance()->GetSurfaceManager()->GetSurface("Portal.srf", "srfIconStartPointFoc");
    m_aSurIcon[E_PORTAL_ICON_ENABLE]          = CNtlPLGuiManager::GetInstance()->GetSurfaceManager()->GetSurface("Portal.srf", "srfIconEnablePoint");
    m_aSurIcon[E_PORTAL_ICON_ENABLE_FOCUS]    = CNtlPLGuiManager::GetInstance()->GetSurfaceManager()->GetSurface("Portal.srf", "srfIconEnablePointFoc");       
}

VOID CPortalGui::OnMove( RwInt32 iOldX, RwInt32 iOldY ) 
{
    sPORTAL_TBLDAT* pPortalData = NULL;
    for each(PAIRPortalInfo pair in m_mapPortalInfo)    
    {
        pPortalData = (sPORTAL_TBLDAT*)API_GetTableContainer()->GetPortalTable()->FindData(pair.first);
        if(!pPortalData)
            continue;

        // ���̺��� ��ǥ�� �������� ���� ��ǥ�̱⶧���� �������ش�.        
        pair.second->m_surIcon.SetRectWH(m_pThis->GetPosition().left + (RwInt32)pPortalData->vMap.x - (RwInt32)(pair.second->m_surIcon.GetWidth() * 0.5f),
                                         m_pThis->GetPosition().top + (RwInt32)pPortalData->vMap.z - (RwInt32)(pair.second->m_surIcon.GetHeight() * 0.5f),
                                         pair.second->m_surIcon.GetWidth(),
                                         pair.second->m_surIcon.GetHeight());
    }
}

VOID CPortalGui::UpdatePortalInfo() 
{
    sPORTAL_TBLDAT* pPortalData = (sPORTAL_TBLDAT*)API_GetTableContainer()->GetPortalTable()->FindData(m_nCurrIdx);
    if(!pPortalData)
        return;

    // ��Ż �����ܵ��� ������ ������Ʈ�Ѵ�. (������ ��ġ�� �°�)

    // 0. ���� �������� ��Ż���� Ȯ���Ѵ�.
    // 1. ��ϵ� ��Ż���� Ȯ�� �Ѵ�.
    // 2. ���� ����Ʈ���� ����� ��Ż���� �ƴ��� Ȯ���Ѵ�.

    for each(PAIRPortalInfo pair in m_mapPortalInfo)    
    {
        SPortalInfo* pPortalInfo = pair.second;
        if(!pPortalInfo)
            continue;

        pPortalInfo->m_nZenny = 0;

        if(pPortalInfo->m_nIndex == m_nCurrIdx)     // ���� ����Ʈ
        {
            pPortalInfo->m_eIconType = E_PORTAL_ICON_START_POINT;

            // �������� �����Ѵ�.        
            pPortalInfo->m_surIcon.SetSurface(m_aSurIcon[E_PORTAL_ICON_START_POINT]);
        }
        else if(IsRegist(pPortalInfo->m_nIndex) && IsConnect(pPortalInfo->m_nIndex, pPortalInfo->m_nZenny))              
        {
            pPortalInfo->m_eIconType = E_PORTAL_ICON_ENABLE;

            // �������� �����Ѵ�.        
            pPortalInfo->m_surIcon.SetSurface(m_aSurIcon[E_PORTAL_ICON_ENABLE]);            
        }
        else
        {
            pPortalInfo->m_eIconType = E_PORTAL_ICON_NOT;
        }
    }

    OnMove(0, 0);
}

// ���콺�� ������ ���� �ö������ ������ ǥ���Ѵ�.
VOID CPortalGui::OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY)
{
    nX += m_pThis->GetPosition().left;
    nY += m_pThis->GetPosition().top;

    CRectangle rect;
    SPortalInfo* pSelectPortal = NULL;

    for each(PAIRPortalInfo pair in m_mapPortalInfo)    
    {
        if(pair.second->m_eIconType == E_PORTAL_ICON_NOT)
            continue;

        pair.second->m_surIcon.GetRect(rect);

        if(!pSelectPortal && rect.PtInRect(nX, nY))
        {
            sPORTAL_TBLDAT* pPortalData = (sPORTAL_TBLDAT*)API_GetTableContainer()->GetPortalTable()->FindData(pair.first);
            if(!pPortalData)
                return;           

            pSelectPortal = pair.second;

            if(m_nSelectIdx != pair.second->m_nIndex)
            {
                m_nSelectIdx = pair.second->m_nIndex;
                
                // �����̽��� �����Ѵ�.                            
                if(pair.second->m_eIconType == E_PORTAL_ICON_START_POINT ||
                   pair.second->m_eIconType == E_PORTAL_ICON_ENABLE)
                {
                    pair.second->m_eIconType = (EPortalIconType)(pair.second->m_eIconType + 1);
                    pair.second->m_surIcon.SetSurface(m_aSurIcon[pair.second->m_eIconType]);
                    pair.second->m_surIcon.SetRect(rect);

					Logic_PlayGUISound( GSD_SYSTEM_POTAL_ICON_MOUSE_OVER );			
                }                                    
            }    

            // ���� ��ü�� ����ü�� �Ѱ��ش�. (�޴� ���ڰ� �ϳ� ���̴�.)
            SPortalTooltip sPortalToolTip;
            sPortalToolTip.nPortalID = pair.second->m_nIndex;
            sPortalToolTip.ePortalIconType = (RwInt32)pair.second->m_eIconType;
            sPortalToolTip.nZenny = pair.second->m_nZenny;
            GetInfoWndManager()->ShowInfoWindow(TRUE, CInfoWndManager::INFOWND_PORTAL, rect.left, rect.top, (VOID*)&sPortalToolTip, DIALOG_PORTAL);            	
			
        }        
        else
        {
            // ������ �����̽��� ����� �������� ������ ������� �����ش�            
            if(pair.second->m_eIconType == E_PORTAL_ICON_START_POINT_FOCUS ||
               pair.second->m_eIconType == E_PORTAL_ICON_ENABLE_FOCUS)
            {
                pair.second->m_eIconType = (EPortalIconType)(pair.second->m_eIconType - 1);;
                pair.second->m_surIcon.SetSurface(m_aSurIcon[pair.second->m_eIconType]);                    
                pair.second->m_surIcon.SetRect(rect);
            }                            
        }
    }

    if(!pSelectPortal && GetInfoWndManager()->GetRequestGui() == DIALOG_PORTAL)
    {
        m_nSelectIdx = NULL;
        GetInfoWndManager()->ShowInfoWindow(FALSE);
    }    
}

// �ʿ��� �̵� ������ Ŭ�������� ȣ��ȴ�.
VOID CPortalGui::OnMouseUp( const CKey& key ) 
{
    if(m_nSelectIdx <= 0 || m_nSelectIdx == m_nCurrIdx || 
       m_mapPortalInfo[m_nSelectIdx]->m_eIconType != E_PORTAL_ICON_ENABLE_FOCUS)
        return;

    RwInt32 nPoint = FindPointIndex(m_nCurrIdx, m_nSelectIdx);
    if(nPoint < 0)
        return;

    SPortalInfo* pInfo = m_mapPortalInfo[m_nSelectIdx];
    
    sMsgBoxData data;
    data.hHandle = m_hNPCSerialID;
    data.byIndex = (RwUInt8)nPoint;

    // �̸��� �����´�.
    sPORTAL_TBLDAT* pPortalData = (sPORTAL_TBLDAT*)API_GetTableContainer()->GetPortalTable()->FindData(pInfo->m_nIndex);
    if(!pPortalData)
        return;

    std::wstring wstrMapName = API_GetTableContainer()->GetTextAllTable()->GetMapNameTbl()->GetText(pPortalData->dwPointName);                    
    
    GetInfoWndManager()->ShowInfoWindow(FALSE);
    GetAlarmManager()->FormattedAlarmMessage(DST_PORTAL_CONFIRM, FALSE, &data,  pInfo->m_nZenny, wstrMapName.c_str());
    
}

VOID CPortalGui::OnPaint() 
{
    for each(PAIRPortalInfo pair in m_mapPortalInfo)    
    {
        if(pair.second->m_eIconType != E_PORTAL_ICON_NOT)
            pair.second->m_surIcon.Render();
    }
}

/// ���� ��Ż ��ġ�� ��ϵǾ� �ִ��� Ȯ���غ���, ��ϵǾ� ���� ������ ����Ѵ�.
/// �̹� ��ϵǾ� ������ True�� ��ȯ, ��ϵǾ� �����ʾƼ� ���� ����Ѵٸ� False�� ��ȯ
RwBool CPortalGui::CheckRegist( RwUInt32 hNPCSerialID ) 
{
    // 1. NPC ���̺�κ��� ������ Portal Index�� �����´�.
     CNtlSobNpc* pNPC = (CNtlSobNpc*)GetNtlSobManager()->GetSobObject(hNPCSerialID);
     if(!pNPC)
         return FALSE;

     CNtlSobNpcAttr* pNPCAttr = (CNtlSobNpcAttr*)pNPC->GetSobAttr();

     // NPC���̺��� NPC�� ��ŻID�� �����´�.
     m_nCurrIdx = pNPCAttr->GetNpcTbl()->contentsTblidx;

     // 2. ������ ��ϵǾ� �ִ��� Ȯ���Ѵ�.
     if(IsRegist(m_nCurrIdx))
     {
         return TRUE;         
     }
     else
     {
         // 3. ������ ��ϵǾ� ���� ������ Ȯ�� �޽����� ����Ѵ�.                  
         //CDboEventGenerator::MsgBoxShow(GetDisplayStringManager()->GetString(DST_PORTAL_ADD), MBW_PORTAL_ADD_OK, MBTF_OK);
		 GetAlarmManager()->AlarmMessage( DST_PORTAL_ADD );

         // 4. Ȯ�� ��ư�� Ŭ���ϸ� ������ ��ϵȴ�.
         // �� ���� HandleEvent���� ó���Ѵ�.

         return FALSE;
     }
}

VOID CPortalGui::OnClickExitBtn( gui::CComponent* pComponent ) 
{
    GetDialogManager()->CloseDialog(DIALOG_PORTAL);
}

RwBool CPortalGui::IsRegist( RwUInt32 nPortalID ) 
{
    if(m_mapPortalInfo.find(nPortalID) == m_mapPortalInfo.end())
        return FALSE;

    return m_mapPortalInfo[nPortalID]->m_bRegist;
}

RwBool CPortalGui::IsConnect(RwUInt32 nPortalID, DWORD& nZenny)
{
    sPORTAL_TBLDAT* pPortalData = (sPORTAL_TBLDAT*)API_GetTableContainer()->GetPortalTable()->FindData(m_nCurrIdx);

    for(int i = 0; i < DBO_MAX_POINT_PORTAL; ++i)
    {
        if(nPortalID == pPortalData->aPoint[i])
        {
            nZenny = pPortalData->adwPointZenny[i];
            return TRUE;        
        }
    }

    return FALSE;
}

VOID CPortalGui::SetPortalInfo( SNtlEventPortalInfoRes* pInfo ) 
{
    for(int i = 0; i < pInfo->byCount; ++i)
    {
        RwInt32 nIdx = pInfo->paPortalID[i];  

        NTL_ASSERT(m_mapPortalInfo.find(nIdx) != m_mapPortalInfo.end(), "Portal Info Invalid!");
        if(m_mapPortalInfo.find(nIdx) == m_mapPortalInfo.end())
            continue;

        m_mapPortalInfo[nIdx]->m_bRegist = TRUE;
    }
}

// ���� ��Ż ���̺��� Ÿ�� ��Ż ����Ʈ�� �ε����� ã�Ƽ� ��ȯ�Ѵ�.
// Return : 0 ~ 7 ������ �ε��� ��ȣ, ã�� ���� ��쿡�� -1�� ����
RwInt32 CPortalGui::FindPointIndex( RwUInt32 nCurrPortalID, RwUInt32 nTargetPortalID ) 
{
    sPORTAL_TBLDAT* pPortalData = (sPORTAL_TBLDAT*)API_GetTableContainer()->GetPortalTable()->FindData(nCurrPortalID);
    if(!pPortalData)
        return -1;

    for(int i = 0; i < DBO_MAX_POINT_PORTAL; ++i)
    {
        if(nTargetPortalID == pPortalData->aPoint[i])
            return i;
    }

    return -1;
}