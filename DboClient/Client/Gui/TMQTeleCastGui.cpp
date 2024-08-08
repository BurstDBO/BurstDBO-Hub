#include "precomp_dboclient.h"
#include "TMQTeleCastGui.h"

// core
#include "NtlDebug.h"

// PL
#include "NtlPLSceneManager.h"

// SL
#include "NtlSLApi.h"
#include "TableContainer.h"
#include "NtlWorldconceptTMQ.h"

// DBO
#include "NtlPLGuiManager.h"
#include "DboGlobal.h"
#include "DialogManager.h"
#include "MinimapGui.h"

// Share
#include "NtlDirection.h"
#include "NPCTable.h"
#include "NpcSpeechTable.h"
#include "TextAllTable.h"
#include "DboEventGenerator.h"

#define BALLOON_FLASH_WIDTH 300
#define BALLOON_FLASH_HEIGHT 150
#define BALLOON_TEXT_WIDTH 211
#define BALLOON_TEXT_HEIGHT 70
#define BALLOON_TEXT_X 44
#define BALLOON_TEXT_Y 43

CTMQTeleCastGui::CTMQTeleCastGui(const RwChar* pName)
: CNtlPLGui(pName)
{
    Init();
}

CTMQTeleCastGui::~CTMQTeleCastGui( void ) 
{    
}

VOID CTMQTeleCastGui::Init() 
{
    m_eTeleCastState = TELECAST_CLOSED;
    m_pFlashOpening = NULL;
    m_pFlashClosing = NULL;
    m_pFlashNoraml = NULL;
    m_pFlashWarn = NULL;    
    m_pFlashFade = NULL;
    m_pFlashBalloon = NULL;
    m_pNPCModel = NULL;
    m_uiPrevNPCIdx = NULL;
    m_fFreqTime = NULL;
    m_bShakeLeft = TRUE;
    m_dwDisplayTime  = 0;
    m_nPrevBalloonType = NULL;
    m_pUIConfigTeleCast = NULL;    
    ZeroMemory(&m_eventInfo, sizeof(m_eventInfo));                
}

RwBool CTMQTeleCastGui::Create() 
{
    if(!CNtlPLGui::Create("", "gui\\TMQTeleCast.srf", "gui\\TMQTeleCast.frm"))
        return FALSE;

    CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

    m_pThis         = (gui::CDialog*)GetComponent("dlgMain");    
    m_pPnlBack      = (gui::CPanel*)GetComponent("pnlBack");
    m_pFlashFade  = (gui::CFlash*)GetComponent("swfFade");
    m_pFlashOpening = (gui::CFlash*)GetComponent("swfOpening");
    m_pFlashClosing = (gui::CFlash*)GetComponent("swfClosing");
    m_pFlashNoraml  = (gui::CFlash*)GetComponent("swfNormal");
    m_pFlashWarn    = (gui::CFlash*)GetComponent("swfWarn");    
    m_pSttBalloon   = (gui::CStaticBox*)GetComponent("sttBalloon");
    
    m_slotPaint = m_pPnlBack->SigPaint().Connect(this, &CTMQTeleCastGui::OnPaint);    
    m_slotMove  = m_pThis->SigMove().Connect(this, &CTMQTeleCastGui::OnMove);
    m_slotOpeningMovieEnd = m_pFlashOpening->SigMovieEnd().Connect(this, &CTMQTeleCastGui::OnOpeningMovieEnd);
    m_slotClosingMovieEnd = m_pFlashClosing->SigMovieEnd().Connect(this, &CTMQTeleCastGui::OnClosingMovieEnd);
    m_slotFadeMovieEnd    = m_pFlashFade->SigMovieEnd().Connect(this, &CTMQTeleCastGui::OnFadeMovieEnd);

    GetNtlGuiManager()->AddUpdateBeforeFunc( this );
    GetNtlGuiManager()->AddUpdateFunc(this);

    m_pUIConfigTeleCast = GetDboGlobal()->GetDBOUIConfig()->GetTeleCastConfig();

    // ��ġ, ũ�� ����
    m_pThis->SetSize((RwInt32)m_pUIConfigTeleCast->v2dSize.x, (RwInt32)m_pUIConfigTeleCast->v2dSize.y);        
    m_pThis->SetPosition(GetDboGlobal()->GetScreenWidth(), m_pUIConfigTeleCast->nYPos);    

    // �÷��� ��ü���� �����Ѵ�.    
    LoadFlash(m_pThis->GetWidth(), m_pThis->GetHeight());

    // NPC ���� ī�޶� �����Ѵ�.    
    m_NPCCamera.Create(256, 256, m_pThis->GetWidth(), m_pThis->GetHeight());    

    LinkMsg(g_EventUIConfigReload);
    LinkMsg(g_EventTMQCleintState);
    LinkMsg(g_EventWorldChange);
    LinkMsg(g_EventCreateWorld);
    LinkMsg(g_EventTMQCleintState);
    LinkMsg(g_EventNotify);

    Show(false);
    
    return TRUE;
}

VOID CTMQTeleCastGui::Destroy() 
{
 
    UnLinkMsg(g_EventUIConfigReload);
	UnLinkMsg(g_EventTMQCleintState);
    UnLinkMsg(g_EventWorldChange);
    UnLinkMsg(g_EventCreateWorld);
    UnLinkMsg(g_EventTMQCleintState);
    UnLinkMsg(g_EventNotify);

    if(m_pNPCModel)
    {
        GetSceneManager()->DeleteEntity(m_pNPCModel);
        m_pNPCModel = NULL;
    }

    m_NPCCamera.Destroy();
    
    if(m_pFlashFade)
        m_pFlashFade->Unload();
    if(m_pFlashOpening)
        m_pFlashOpening->Unload();
    if(m_pFlashClosing)
        m_pFlashClosing->Unload();
    if(m_pFlashNoraml)
        m_pFlashNoraml->Unload();
    if(m_pFlashWarn)
        m_pFlashWarn->Unload();    

    std::map<RwInt32, gui::CFlash*>::iterator it;
    for(it = m_mapFlashBalloon.begin(); it != m_mapFlashBalloon.end(); ++it)
    {
        gui::CFlash* pFlash = (*it).second;
        if(pFlash)
            pFlash->Unload();
    }

    GetNtlGuiManager()->RemoveUpdateBeforeFunc(this);
    GetNtlGuiManager()->RemoveUpdateFunc(this);

    CNtlPLGui::DestroyComponents();
    CNtlPLGui::Destroy();
}

// UIConfig.XML�� �����Ǿ� �ִ� �÷��� ���ϵ��� �ε��Ѵ�.
VOID CTMQTeleCastGui::LoadFlash(RwInt32 nWidth, RwInt32 nHeight)
{
    m_pFlashFade->Load(m_pUIConfigTeleCast->strFadeFlashFile.c_str());
    m_pFlashOpening->Load(m_pUIConfigTeleCast->strOpeningFlashFile.c_str());
    m_pFlashClosing->Load(m_pUIConfigTeleCast->strClosingFlashFile.c_str());
    m_pFlashNoraml->Load(m_pUIConfigTeleCast->strBackNormalFlashFile.c_str());
    m_pFlashWarn->Load(m_pUIConfigTeleCast->strBackWarnFlashFile.c_str());
    
    m_pFlashFade->PlayMovie(FALSE);
    m_pFlashOpening->PlayMovie(FALSE);
    m_pFlashClosing->PlayMovie(FALSE);
    m_pFlashNoraml->PlayMovie(FALSE);
    m_pFlashWarn->PlayMovie(FALSE);
    
    m_pFlashFade->AutoRewind(FALSE);
    m_pFlashOpening->AutoRewind(FALSE);
    m_pFlashClosing->AutoRewind(FALSE);
    
    m_pFlashFade->SetResizeType(gui::CFlash::EXACTFIT);
    m_pFlashOpening->SetResizeType(gui::CFlash::EXACTFIT);
    m_pFlashClosing->SetResizeType(gui::CFlash::EXACTFIT);
    m_pFlashNoraml->SetResizeType(gui::CFlash::EXACTFIT);
    m_pFlashWarn->SetResizeType(gui::CFlash::EXACTFIT);

    // ��ǳ�� �÷��õ��� �����Ѵ�.
    CreateDialogBalloon();
}

VOID CTMQTeleCastGui::Update( RwReal fElapsed ) 
{
    if(!IsShow())
        return;

    // Fade Flash Update
    if(m_pFlashFade && m_pFlashFade->IsPlayMovie() && m_pFlashFade->IsVisible())
    {
        RwReal fOrgPlayTime = m_pFlashFade->GetFrameCount() / m_pFlashFade->GetFrameRate();
        RwReal fRatio = fOrgPlayTime / m_pUIConfigTeleCast->fFadeTime;
        m_pFlashFade->Update(fElapsed * fRatio);
    }

    switch(m_eTeleCastState)
    {
    case TELECAST_SLIDING_IN:
        UpdateSliding(fElapsed);        
        break;
    case TELECAST_OPENING:
        if(m_pFlashOpening) m_pFlashOpening->Update(fElapsed);                
        break;
    case TELECAST_OPEN:              
        if(m_pFlashBalloon && m_pFlashBalloon->IsVisible()) // ��ǳ�� ������Ʈ        
        {
            m_pSttBalloon->Show(true);
            m_pFlashBalloon->Update(fElapsed);            
        }
        break;
    case TELECAST_CLOSING:
        if(m_pFlashClosing) m_pFlashClosing->Update(fElapsed);
        break;    
    case TELECAST_SLIDING_OUT:
        UpdateSliding(fElapsed);
        break;
    case TELECAST_CLOSED:        
        break;
    }

    // ��Ȳ�� �´� ���� �÷��ø� ����Ѵ�.
    if(m_eTeleCastState != TELECAST_CLOSED)
    {
        switch(m_eventInfo.byTelecastType)
        {
        case TELECAST_MESSAGE_TYPE_NORMAL:
        case TELECAST_MESSAGE_TYPE_NOTIFY:
            if(m_pFlashNoraml)
                m_pFlashNoraml->Update(fElapsed);
            break;
        case TELECAST_MESSAGE_TYPE_DANGER:     
            if(m_eTeleCastState == TELECAST_OPEN)
            {
                UpdateShake(fElapsed);              // ���� �÷��ô� ������ ���� ����.
            }            
        case TELECAST_MESSAGE_TYPE_WARNING:
            if(m_pFlashWarn)
                m_pFlashWarn->Update(fElapsed);
            break;        
        }
    }

    // NPC �ִϸ��̼� ������Ʈ �� �ؽ��Ŀ� ������    
    if(m_surNPC.IsShow() && m_pNPCModel)
    {
        m_pNPCModel->Update(fElapsed);        
    }    

    if(m_eTeleCastState == TELECAST_OPEN)
    {
        // Ÿ�� ���̽���� ���� �ð� üũ
        if(m_eventInfo.dwDisplayTime != INVALID_DWORD && m_eventInfo.dwDisplayTime > 0)
        {
            m_dwDisplayTime += (DWORD)(fElapsed * 1000.0f);
            if(m_dwDisplayTime >= m_eventInfo.dwDisplayTime)            
            {
                Closing();
                m_dwDisplayTime = 0L;
            }
        }
    }    
}

VOID CTMQTeleCastGui::OnPaint() 
{
    if(!IsShow())
        return;

    // NPC�� �������� �ؽ��ĸ� ���� ȭ�鿡 ������
    if(m_eTeleCastState != TELECAST_CLOSED && m_pNPCModel && m_surNPC.IsShow())
    {        
        m_surNPC.Render();
    }    
}

RwInt32 CTMQTeleCastGui::SwitchDialog( bool bOpen ) 
{
    if(bOpen)
    {
		CNtlWorldConceptController* pWorldConcept = GetNtlWorldConcept()->FindGradeExtController(WORLD_CONCEPT_FIRST_GRADE);
		if( pWorldConcept )
		{
			if( pWorldConcept->GetConceptType() == WORLD_PLAY_TUTORIAL )
			{
				if( pWorldConcept->GetState() == WORLD_STATE_ENTER )
				{
					CMinimapGui* pMinimapGui = reinterpret_cast<CMinimapGui*>( GetDialogManager()->GetDialog(DIALOG_MINIMAP) );
					pMinimapGui->ChangeMapStyle(CMinimapGui::MS_MINIMAM);
				}
			}
		}
		
		//if( pWorldConcept->GetConceptType() == WORLD_PLAY_TIME_MACHINE )
		//{
		//	CNtlWorldConceptTMQ* pTMQWorldConcept = reinterpret_cast<CNtlWorldConceptTMQ*>(pWorldConcept);

		//	if( pTMQWorldConcept->GetTMQState() < WORLD_STATE_TMQ_WAIT ||
		//		pTMQWorldConcept->GetTMQState() >= WORLD_STATE_TMQ_END )
		//		return -1;
		//}
		//else if( pWorldConcept->GetConceptType() != WORLD_PLAY_TUTORIAL )
		//	return -1;

		RaiseTop();

        Show(TRUE);
    }
    else
    {
		CNtlWorldConceptController* pWorldConcept = GetNtlWorldConcept()->FindGradeExtController(WORLD_CONCEPT_FIRST_GRADE);
		if( pWorldConcept )
		{
			if( pWorldConcept->GetConceptType() == WORLD_PLAY_TUTORIAL )
			{
				CMinimapGui* pMinimapGui = reinterpret_cast<CMinimapGui*>( GetDialogManager()->GetDialog(DIALOG_MINIMAP) );
				pMinimapGui->ChangeMapStyle(CMinimapGui::MS_NORMAL);
			}
		}

        // Side Dialog�� �Ŵ������� �˾Ƽ� �����ֱ� ������ ȭ�鿡�� ����� �ȵȴ�.        
         Show(FALSE);
         m_surNPC.Show(FALSE);
    }
 
    return TRUE;
}

VOID CTMQTeleCastGui::HandleEvents( RWS::CMsg &pMsg ) 
{
    //if(pMsg.Id == g_EventTeleCastBegNfy)
    //{
    //    // ���� �˸����϶��� ���â�� �߱��.
    //    if(IsShow() && m_eventInfo.byTelecastType == TELECAST_MESSAGE_TYPE_NOTIFY)
    //        return;

    //    SNtlEventTeleCastBegNfy* pData = (SNtlEventTeleCastBegNfy*)pMsg.pData;
    //    m_eventInfo = *pData;
    //    m_dwDisplayTime = 0;

    //    RaiseLinked();
    //    OnSlidingIn();
    //}
    //else if(pMsg.Id == g_EventTeleCastEndNfy)
    //{
    //    Closing();
    //}
    if(pMsg.Id == g_EventNotify)       // �����κ��� �˸��� ����������
    {
        SDboEventNotify* data = (SDboEventNotify*)pMsg.pData;
        if(data->eType == SDboEventNotify::NPC)
        {
            // �����Ͱ� �ٸ��� ���ε�
            if(m_pUIConfigTeleCast->m_eTelecastType != TELECAST_TYPE_SERVER_NOTIFY)
            {
                GetDboGlobal()->GetDBOUIConfig()->LoadTeleCast(TELECAST_TYPE_SERVER_NOTIFY);

                // ��ġ, ũ�� ����
                m_pThis->SetSize((RwInt32)m_pUIConfigTeleCast->v2dSize.x, (RwInt32)m_pUIConfigTeleCast->v2dSize.y);        
                m_pThis->SetPosition(GetDboGlobal()->GetScreenWidth(), m_pUIConfigTeleCast->nYPos);   
                AdjustDialogBalloon();
            }

            // ������ ����
            m_eventInfo.npcTblidx = m_pUIConfigTeleCast->uiNPCID;
            m_eventInfo.byTelecastType = TELECAST_MESSAGE_TYPE_NOTIFY;
            m_eventInfo.speechTblidx = INVALID_INDEX;      // ������� �ʴ´�.            
            m_eventInfo.wstrNotifyMsg = data->wchMessage;
            m_eventInfo.dwDisplayTime = (DWORD)(m_pUIConfigTeleCast->fShowTime * 1000.0f);

            m_dwDisplayTime = 0;

            RaiseLinked();
            OnSlidingIn();
        }
    }
    else if(pMsg.Id == g_EventUIConfigReload)       // UIConfig.XML�� ���븦 ���ε� ������ (������)
    {
        // ��ġ, ũ�� ����
        m_pThis->SetSize((RwInt32)m_pUIConfigTeleCast->v2dSize.x, (RwInt32)m_pUIConfigTeleCast->v2dSize.y);        
        m_pThis->SetPosition(GetDboGlobal()->GetScreenWidth() - m_pThis->GetWidth(), m_pUIConfigTeleCast->nYPos);    

        // ���� �÷��� �����ʹ� �ǽð����� ���������� �ʴ´�.
        // ���� ��û�� �����ÿ��� �÷��� �����͵� ���ε��ϴ� ������ �߰��Ѵ�.

        // ��ǳ�� 
        AdjustDialogBalloon();        
    }
    else if(pMsg.Id == g_EventTMQCleintState)      // ���� ������ ����Ǿ�����.
    {
        // ���� �����͸� ���� �ε��Ѵ�.
        SNtlEventTMQServerState* pData = (SNtlEventTMQServerState*)pMsg.pData;
        if(pData->uiState == WORLD_STATE_TMQ_BEGIN)
        {
            if(pData->eWorldConcept == WORLD_PLAY_TUTORIAL)
            {
                GetDboGlobal()->GetDBOUIConfig()->LoadTeleCast(TELECAST_TYPE_TUTORIAL);            
            }
            else if(pData->eWorldConcept == WORLD_PLAY_TIME_MACHINE)
            {
                GetDboGlobal()->GetDBOUIConfig()->LoadTeleCast(TELECAST_TYPE_TMQ);     
            }

            // ��ġ, ũ�� ����
            m_pThis->SetSize((RwInt32)m_pUIConfigTeleCast->v2dSize.x, (RwInt32)m_pUIConfigTeleCast->v2dSize.y);        
            m_pThis->SetPosition(GetDboGlobal()->GetScreenWidth(), m_pUIConfigTeleCast->nYPos);   
            AdjustDialogBalloon();
        }
    }
	else if( pMsg.Id == g_EventTMQCleintState ) // TMQ ���Կ� �����ϴ� ��쿡�� ȭ�鿡�� �����ش�.
	{
		SNtlEventTMQServerState* pEvent = reinterpret_cast<SNtlEventTMQServerState*>( pMsg.pData );

		if( pEvent->uiState == WORLD_STATE_TMQ_FAIL )
		{
			GetDialogManager()->CloseDialog(DIALOG_TELECAST);
		}
	}
    else if(pMsg.Id == g_EventWorldChange)      // ���尡 ����Ǵ� ��쿡�� ȭ�鿡�� �����ش�.
    {
        SNtlEventWorldChange* pWorldChange = reinterpret_cast<SNtlEventWorldChange*>(pMsg.pData);
        
        if(pWorldChange->bWorldChange)      
        {            
            if(m_pNPCModel)
            {
                GetSceneManager()->DeleteEntity(m_pNPCModel);
                m_pNPCModel		= NULL;
				m_uiPrevNPCIdx	= NULL;
            }
            SwitchDialog(false);
        }
    }
    else if(pMsg.Id == g_EventCreateWorld)      // ���� ����/���� �ɶ��� ���� �����־�߸��Ѵ�.
    {
        if(m_pNPCModel)
        {
            GetSceneManager()->DeleteEntity(m_pNPCModel);
            m_pNPCModel		= NULL;
			m_uiPrevNPCIdx	= NULL;
        }
    }
}

VOID CTMQTeleCastGui::OnSlidingIn() 
{
    SwitchDialog(true);
    m_eTeleCastState = TELECAST_SLIDING_IN;

    // ���� ��ġ ����
    m_pThis->SetPosition(GetDboGlobal()->GetScreenWidth() + 1, m_pUIConfigTeleCast->nYPos);

    // �����̵� ������ ���� ���ӵ� ��Ʈ�ѷ� ����
    RwReal fStartPos = (RwReal)m_pThis->GetPosition().left;
    RwReal fEndPos =(RwReal)GetDboGlobal()->GetScreenWidth() - m_pThis->GetScreenRect().GetWidth();
    m_AccelController.SetAccel(fStartPos, fEndPos, m_pUIConfigTeleCast->fSlideStartVel, m_pUIConfigTeleCast->fSlideAccel);

    // ��ü ȭ�� �÷��� ���
    m_pFlashFade->PlayMovie(TRUE);
    m_pFlashFade->Show(TRUE);
    m_pFlashFade->RestartMovie();

    m_surNPC.Show(FALSE);
}

// ������ �÷��� ����
VOID CTMQTeleCastGui::Opening() 
{
    m_eTeleCastState = TELECAST_OPENING;

    if(m_eventInfo.byTelecastType == TELECAST_MESSAGE_TYPE_NORMAL ||
       m_eventInfo.byTelecastType == TELECAST_MESSAGE_TYPE_NOTIFY)
    {
        m_pFlashNoraml->PlayMovie(TRUE);
        m_pFlashNoraml->Show(TRUE); 
        m_pFlashNoraml->RestartMovie();

        m_pFlashWarn->PlayMovie(FALSE);
        m_pFlashWarn->Show(FALSE);
    }
    else
    {
        m_pFlashWarn->PlayMovie(TRUE);
        m_pFlashWarn->Show(TRUE);
        m_pFlashWarn->RestartMovie();

        m_pFlashNoraml->PlayMovie(FALSE);
        m_pFlashNoraml->Show(FALSE);
    }

    m_pFlashOpening->PlayMovie(TRUE);
    m_pFlashOpening->Show(TRUE);
    m_pFlashOpening->RestartMovie();

    // NPC �� ����
    CreateNPCModel();
}

// Ŭ��¡ �÷��� ����
VOID CTMQTeleCastGui::Closing() 
{
    m_eTeleCastState = TELECAST_CLOSING;        
    
    // Shake�� ��� ���� ��ġ�� �����ش�.
    if(m_eventInfo.byTelecastType == TELECAST_MESSAGE_TYPE_DANGER)
    {
        if(!m_bShakeLeft)   // �������� ������ ���
        {
            CRectangle rect = m_pThis->GetScreenRect();            
            SetPosition(rect.left + m_pUIConfigTeleCast->nShakeAmp, rect.top);
        }           
    }

    if(m_pFlashFade->IsPlayMovie())
    {
        m_pFlashFade->PlayMovie(FALSE);
        m_pFlashFade->Show(FALSE);
    }

    m_pFlashClosing->PlayMovie(TRUE);
    m_pFlashClosing->Show(TRUE);
    m_pFlashClosing->RestartMovie();

    // ��ǳ���� ����.
    CloseDialogBalloon();
}

VOID CTMQTeleCastGui::OnOpeningMovieEnd( gui::CComponent* pComponent ) 
{
    m_eTeleCastState = TELECAST_OPEN;
    
    m_pFlashOpening->PlayMovie(FALSE);
    m_pFlashOpening->Show(FALSE);

    m_surNPC.Show(TRUE);

    // ��ǳ���� �����Ѵ�.
    SetDialogBalloon();    
}
VOID CTMQTeleCastGui::OnClosingMovieEnd( gui::CComponent* pComponent ) 
{
    m_eTeleCastState = TELECAST_SLIDING_OUT;

    m_pFlashNoraml->PlayMovie(FALSE);
    m_pFlashNoraml->Show(false);
    m_pFlashWarn->PlayMovie(FALSE);
    m_pFlashWarn->Show(false);
    m_pFlashClosing->PlayMovie(FALSE);
    m_pFlashClosing->Show(FALSE);

    // NPC�� ĳ���ϰ� �ֱ� ������ �������� �ʴ´�.   
    m_surNPC.Show(FALSE);

    // �����̵� �ƿ��� ����
    RwReal fStartPos = (RwReal)m_pThis->GetPosition().left;
    RwReal fEndPos = GetDboGlobal()->GetScreenWidth() + 1.0f;
    m_AccelController.SetAccel(fStartPos, fEndPos, m_pUIConfigTeleCast->fSlideStartVel, m_pUIConfigTeleCast->fSlideAccel);
}

VOID CTMQTeleCastGui::OnFadeMovieEnd( gui::CComponent* pComponent ) 
{
    m_pFlashFade->PlayMovie(FALSE);
    m_pFlashFade->Show(false);
}

VOID CTMQTeleCastGui::UpdateShake( RwReal fElapsed ) 
{
    m_fFreqTime += fElapsed;
    if(m_fFreqTime >= m_pUIConfigTeleCast->fShakeFreq)
    {
        m_pThis->RemoveChild(m_pSttBalloon);
        m_pThis->RemoveChild(m_pFlashBalloon);      // ��ǳ���� Shake�Ǹ� �ȵȴ�.
        

        m_fFreqTime = 0.0;
        RwInt32 nAmp = m_pUIConfigTeleCast->nShakeAmp;
        if(m_bShakeLeft) // ����->������ġ->����->������ġ..������ �����Ѵ�.
        {
            nAmp = -nAmp;
        }
        m_bShakeLeft = !m_bShakeLeft;
        CRectangle rect = m_pThis->GetScreenRect();        
        SetPosition(rect.left + nAmp, rect.top);

        m_pThis->AddChild(m_pFlashBalloon);
        m_pThis->AddChild(m_pSttBalloon);        
    }
}

VOID CTMQTeleCastGui::OnMove( RwInt32 iOldX, RwInt32 iOldY ) 
{
    // ���
    m_pPnlBack->SetSize(m_pThis->GetWidth(), m_pThis->GetHeight());
    
    // NPC Render Ÿ���� ��ġ (��� �׸����� ���� �۰��Ѵ�)
    CRectangle rect = m_pThis->GetScreenRect();
    rect.left += 18;
    rect.top += 10;
    rect.right -= 12;
    rect.bottom -= 10;
    m_surNPC.SetRect(rect);      

    // �÷��õ��� ũ�� ���� (��ġ�� ���� Ŭ�������� ��������)
    RwInt32 nWidth = m_pThis->GetWidth();
    RwInt32 nHeight = m_pThis->GetHeight();
    m_pFlashOpening->SetSize(nWidth, nHeight);
    m_pFlashClosing->SetSize(nWidth, nHeight);
    m_pFlashNoraml->SetSize(nWidth, nHeight);
    m_pFlashWarn->SetSize(nWidth, nHeight);    

    // ��üȭ�� �÷���
    rect = m_pThis->GetScreenRect();
    m_pFlashFade->SetSize(GetDboGlobal()->GetScreenWidth(), GetDboGlobal()->GetScreenHeight());    
    m_pFlashFade->SetPosition(-rect.left, -rect.top);    
}

void CTMQTeleCastGui::Show( bool bShow ) 
{
    CNtlPLGui::Show(bShow);    

    // �÷��ô� ��Ȳ�� �°� Show �Ǳ� ������ �� �Լ��� ������ ������ �ȵȴ�.    
    m_pFlashFade->Show(false);
    m_pFlashOpening->Show(false);
    m_pFlashClosing->Show(false);
    m_pFlashNoraml->Show(false);
    m_pFlashWarn->Show(false);
    m_pSttBalloon->Show(FALSE);
}

VOID CTMQTeleCastGui::CreateNPCModel() 
{
    // ������ �ε��� NPC�� ���� NPC��� ���� �ε����� �ʴ´�.    
    if(m_uiPrevNPCIdx == m_eventInfo.npcTblidx)
    {
        return;
    }
    else if(m_pNPCModel)
    {
        GetSceneManager()->DeleteEntity(m_pNPCModel);
        m_pNPCModel = NULL;
    }

    sBOT_TBLDAT* pTableData = (sBOT_TBLDAT*)API_GetTableContainer()->GetNpcTable()->FindData(m_eventInfo.npcTblidx);
    if(!pTableData)
    {
        m_uiPrevNPCIdx = NULL;
        return;
    }

    SPLCharacterCreateParam param;
    ZeroMemory(&param, sizeof(SPLCharacterCreateParam)); 
    param.bPcFlag = FALSE;    
    m_pNPCModel = (CNtlPLCharacter*)GetSceneManager()->CreateEntity(PLENTITY_CHARACTER, pTableData->szModel, &param);
    if(!m_pNPCModel)
        return;

	m_uiPrevNPCIdx = m_eventInfo.npcTblidx;

    // ī�޶� ��ġ ����
    RwV3d vFaceCamPos = m_pNPCModel->GetFaceCameraPos();
    RwV3d vFaceCamLookAt = m_pNPCModel->GetFaceCameraLookAt();
    m_NPCCamera.SetCameraPosition(&vFaceCamPos, &vFaceCamLookAt);

    m_pNPCModel->SetVisible(FALSE);
    m_pNPCModel->SetPosition(&ZeroAxis);
    m_pNPCModel->SetBaseAnimation(NML_IDLE_LOOP, 0.0f, TRUE);
    m_NPCTexture.Load(m_NPCCamera.GetTexture());
    m_surNPC.SetTexture(&m_NPCTexture);
}

VOID CTMQTeleCastGui::UpdateBeforeCamera( RwReal fElapsed ) 
{
    if(!IsShow())
        return;

    if(m_pNPCModel)
    {
        m_NPCCamera.RenderTexture(m_pNPCModel);                
    }    
}

VOID CTMQTeleCastGui::CreateDialogBalloon() 
{
    // ��ǳ������ ���� �̸� �����صд�.
    std::map<RwInt32, STeleCastBalloon>::iterator it;
    for(it = m_pUIConfigTeleCast->mapBalloonRes.begin(); it != m_pUIConfigTeleCast->mapBalloonRes.end(); ++it)
    {
        STeleCastBalloon* data = &((*it).second);
        RwInt32 nPosX = (RwInt32)(-data->v2dOffset.x - data->v2dSize.x);
        RwInt32 nPosY = (RwInt32)(-data->v2dOffset.y);
        
        gui::CFlash* pFlash = NTL_NEW gui::CFlash(m_pThis, GetNtlGuiManager()->GetSurfaceManager());
        pFlash->Load(data->strFileName.c_str());
        pFlash->SetSize((RwInt32)data->v2dSize.x, (RwInt32)data->v2dSize.y);
        pFlash->SetPosition(nPosX, nPosY);
        pFlash->SetResizeType(gui::CFlash::EXACTFIT);
        pFlash->SetFrameCallback(FALSE);
        pFlash->PlayMovie(FALSE);
        pFlash->Show(FALSE);        

        m_mapFlashBalloon[(*it).first] = pFlash;
    }

    m_pSttBalloon->Raise();
}

VOID CTMQTeleCastGui::SetDialogBalloon() 
{
    if(m_eventInfo.byTelecastType == TELECAST_MESSAGE_TYPE_NOTIFY)          // ���� �˸�â�϶��� �ؽ�Ʈ�� ����´�.
    {
        m_pSttBalloon->SetText(m_eventInfo.wstrNotifyMsg.c_str());
        
        m_pFlashBalloon = m_mapFlashBalloon[1];
        m_nPrevBalloonType = 1;
        AdjustDialogBalloon();
    }
    else
    {
        sNPC_SPEECH_TBLDAT* ptblData = (sNPC_SPEECH_TBLDAT*)API_GetTableContainer()->GetNpcSpeechTable()->FindData(m_eventInfo.speechTblidx);
        if(!ptblData)
            return;

        // �ؽ�Ʈ ���̺�
        std::wstring strDialog = API_GetTableContainer()->GetTextAllTable()->GetNpcDialogTbl()->GetText(ptblData->textIndex);
        m_pSttBalloon->SetText(strDialog.c_str());

        // ������ ��ǳ�� Ÿ���� �ٸ����� ���� �����Ѵ�.
        if(m_nPrevBalloonType != ptblData->byBallonType)
        {
            if(m_pFlashBalloon)
            {
                m_pFlashBalloon->Show(FALSE);
                m_pFlashBalloon->PlayMovie(FALSE);
            }

            STeleCastBalloon sTeleCastBalloon = m_pUIConfigTeleCast->mapBalloonRes[ptblData->byBallonType];        
            m_pFlashBalloon = m_mapFlashBalloon[ptblData->byBallonType];
            m_nPrevBalloonType = ptblData->byBallonType;

            AdjustDialogBalloon();        
        }
    }

    m_pFlashBalloon->Show(TRUE);
    m_pFlashBalloon->PlayMovie(TRUE);    

    m_pSttBalloon->Show(TRUE);
}

VOID CTMQTeleCastGui::AdjustDialogBalloon() 
{
    if(!m_pFlashBalloon)
        return;
    
    STeleCastBalloon sTeleCastBalloon = m_pUIConfigTeleCast->mapBalloonRes[m_nPrevBalloonType];        

    // �÷��� ��ġ�� ũ�� ����
    RwInt32 nPosX = (RwInt32)(-sTeleCastBalloon.v2dOffset.x - sTeleCastBalloon.v2dSize.x);
    RwInt32 nPosY = (RwInt32)(-sTeleCastBalloon.v2dOffset.y);
    m_pFlashBalloon->SetSize((RwInt32)sTeleCastBalloon.v2dSize.x, (RwInt32)sTeleCastBalloon.v2dSize.y);
    m_pFlashBalloon->SetPosition(nPosX, nPosY);

    // ��ǳ���� �ؽ�Ʈ ��ġ�� ũ�� ����
    RwV2d   v2dRatio;
    v2dRatio.x = BALLOON_TEXT_WIDTH * sTeleCastBalloon.v2dSize.x / BALLOON_FLASH_WIDTH;
    v2dRatio.y = BALLOON_TEXT_HEIGHT * sTeleCastBalloon.v2dSize.y / BALLOON_FLASH_HEIGHT;
    m_pSttBalloon->SetSize((RwInt32)v2dRatio.x, (RwInt32)v2dRatio.y);
    m_pSttBalloon->SetPosition(m_pFlashBalloon->GetPosition().left + BALLOON_TEXT_X, 
                               m_pFlashBalloon->GetPosition().top + BALLOON_TEXT_Y); 
}

VOID CTMQTeleCastGui::CloseDialogBalloon() 
{
    if(m_pFlashBalloon)
    {
        m_pFlashBalloon->Show(FALSE);
        m_pFlashBalloon->PlayMovie(FALSE);
    }
    
    m_pSttBalloon->Show(FALSE);    
}

VOID CTMQTeleCastGui::UpdateSliding( RwReal fElapsed ) 
{
    RwBool bUpdate = m_AccelController.Update(fElapsed);

    m_pThis->SetPosition((RwInt32)m_AccelController.GetCurrentValue(), m_pThis->GetScreenRect().top);

    if(!bUpdate)
    {
        if(m_eTeleCastState == TELECAST_SLIDING_IN)    // �����̵��� �Ϸ�
        {
            Opening();
        }
        else if(m_eTeleCastState == TELECAST_SLIDING_OUT)   // �����̵� �ƿ� �Ϸ�
        {
            m_eTeleCastState = TELECAST_CLOSED;
            SwitchDialog(false);
        }
    }
}

