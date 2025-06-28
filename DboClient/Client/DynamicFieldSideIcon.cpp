#include "precomp_dboclient.h"
#include "DynamicFieldSideIcon.h"

// core
#include "NtlDebug.h"

// presentation
#include "NtlPLGuiManager.h"

// dbo
#include "DboEvent.h"
#include "DboEventGenerator.h"
#include "DboPacketGenerator.h"
#include "DialogManager.h"
#include "DboGlobal.h"

#include "DboTSCQAgency.h"
#include "DboTSCTAgency.h"
#include "DboTSCQCtrl.h"

//icon
CDynamicFieldSideIcon::CDynamicFieldSideIcon(const RwChar* pName)
:CSideIconBase(pName)
{
	m_DynamicFieldCount = FALSE;
}

CDynamicFieldSideIcon::~CDynamicFieldSideIcon(void)
{
}

// 创建
RwBool CDynamicFieldSideIcon::Create()
{
	NTL_FUNCTION("__FUNCTION__");

	if (!CNtlPLGui::Create("gui\\Game.rsr", "gui\\DynamicFieldSideIcon.srf", "gui\\DynamicFieldSideIcon.frm"))
		NTL_RETURN(FALSE);

	// 创建GUI ICON部件
	CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

	m_pThis = (gui::CDialog*)GetComponent("dlgMain");
	m_pbtnStepOneSideIcon = (gui::CButton*)GetComponent("btnStepOneSideIcon");
	m_pbtnStepTwoSideIcon = (gui::CButton*)GetComponent("btnStepTwoSideIcon");
	m_pbtnStepThreeSideIcon = (gui::CButton*)GetComponent("btnStepThreeSideIcon");
	m_pbtnStepDisableSideIcon = (gui::CButton*)GetComponent("btnStepDisableSideIcon");

	m_slotBossInfoBtn = m_pbtnStepDisableSideIcon->SigClicked().Connect(this, &CDynamicFieldSideIcon::OnIconButtonClicked);
	m_slotBossInfoMouseEnter = m_pbtnStepDisableSideIcon->SigMouseEnter().Connect(this, &CDynamicFieldSideIcon::OnMouseEnter);
	m_slotBossInfoMouseLeave = m_pbtnStepDisableSideIcon->SigMouseLeave().Connect(this, &CDynamicFieldSideIcon::OnMouseLeave);


	// 连接一个开启UI
	LinkMsg(g_EventDynamic_Count);
	LinkMsg(g_EventSobInfoUpdate);

	Show(false);

	NTL_RETURN(TRUE);
}

// 摧毁
VOID CDynamicFieldSideIcon::Destroy()
{
	UnLinkMsg(g_EventDynamic_Count);
	UnLinkMsg(g_EventSobInfoUpdate);

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();
	Show(false);
}


VOID CDynamicFieldSideIcon::HandleEvents(RWS::CMsg& msg)
{
	NTL_FUNCTION("CDynamicFieldSideIcon::HandleEvents");

	if (msg.Id == g_EventDynamic_Count) 
	{
		
		SNtlEventDynamicField_Count* pData = (SNtlEventDynamicField_Count*)msg.pData;

		m_EventTime = pData->nEventTime;

		// 计算百分比
		DynamicProgress((float)pData->dwCurCount, (float)pData->dwMaxCount);
		IconColor();

		CNtlTSTrigger* pTrig = ((CDboTSCMain*)API_GetQuestAgency()->GetParent())->FindQuestFromTS(6860);
		CDboTSContStart* pStartCont = (CDboTSContStart*)pTrig->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(START_CONTAINER_ID);
		CDboTSCheckLvl* pLvl = (CDboTSCheckLvl*)pStartCont->GetChildEntity(1);
		
		// 开启
		if (Logic_GetLevel(GetNtlSLGlobal()->GetSobAvatar()) >= pLvl->GetMinLvl()) // 当玩家大于40及才允许开启ui
		{
			m_DynamicFieldCount = TRUE;
			Show(true);
		}
	}
	else if (msg.Id == g_EventSobInfoUpdate) // 判断任务等级来开启与关闭UI
	{
		SNtlEventSobInfoUpdate* pUpdate = reinterpret_cast<SNtlEventSobInfoUpdate*>(msg.pData);
		if (pUpdate->uiUpdateType & EVENT_AIUT_ATTR_LEVELUP)
		{
			CNtlTSTrigger* pTrig = ((CDboTSCMain*)API_GetQuestAgency()->GetParent())->FindQuestFromTS(6860);
			CDboTSContStart* pStartCont = (CDboTSContStart*)pTrig->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(START_CONTAINER_ID);
			CDboTSCheckLvl* pLvl = (CDboTSCheckLvl*)pStartCont->GetChildEntity(1);

			if (Logic_GetLevel(GetNtlSLGlobal()->GetSobAvatar()) >= pLvl->GetMinLvl()) // 当玩家大于40及才允许开启ui
			{
				m_DynamicFieldCount = TRUE;
				Show(true);
			}
			else
			{
				m_DynamicFieldCount = FALSE;
				Show(false);
			}
		}
	}

	NTL_RETURNVOID();
}

// 计算进度
void CDynamicFieldSideIcon::DynamicProgress(float CurCount,float MaxCount)
{
	m_progress = (CurCount / MaxCount) * 100;
}

// 计算图标颜色
void CDynamicFieldSideIcon::IconColor()
{
	if (m_EventTime)
	{
		m_pbtnStepDisableSideIcon->Enable(true);
		m_pbtnStepOneSideIcon->Enable(false);
		m_pbtnStepTwoSideIcon->Enable(false);
		m_pbtnStepThreeSideIcon->Enable(false);
		// 连接槽函数

		m_slotBossInfoBtn = m_pbtnStepDisableSideIcon->SigClicked().Connect(this, &CDynamicFieldSideIcon::OnIconButtonClicked);
		m_slotBossInfoMouseEnter = m_pbtnStepDisableSideIcon->SigMouseEnter().Connect(this, &CDynamicFieldSideIcon::OnMouseEnter);
		m_slotBossInfoMouseLeave = m_pbtnStepDisableSideIcon->SigMouseLeave().Connect(this, &CDynamicFieldSideIcon::OnMouseLeave);

		return;
	}
	
	if (m_progress <= 33.0f) {

		m_pbtnStepDisableSideIcon->Enable(false);
		m_pbtnStepOneSideIcon->Enable(true);
		m_pbtnStepTwoSideIcon->Enable(false);
		m_pbtnStepThreeSideIcon->Enable(false);

		m_slotBossInfoBtn = m_pbtnStepOneSideIcon->SigClicked().Connect(this, &CDynamicFieldSideIcon::OnIconButtonClicked);
		m_slotBossInfoMouseEnter = m_pbtnStepOneSideIcon->SigMouseEnter().Connect(this, &CDynamicFieldSideIcon::OnMouseEnter);
		m_slotBossInfoMouseLeave = m_pbtnStepOneSideIcon->SigMouseLeave().Connect(this, &CDynamicFieldSideIcon::OnMouseLeave);
	}
	else if (m_progress <= 66.0f && m_progress > 33.0f)
	{
		m_pbtnStepDisableSideIcon->Enable(false);
		m_pbtnStepOneSideIcon->Enable(false);
		m_pbtnStepTwoSideIcon->Enable(true);
		m_pbtnStepThreeSideIcon->Enable(false);

		m_slotBossInfoBtn = m_pbtnStepTwoSideIcon->SigClicked().Connect(this, &CDynamicFieldSideIcon::OnIconButtonClicked);
		m_slotBossInfoMouseEnter = m_pbtnStepTwoSideIcon->SigMouseEnter().Connect(this, &CDynamicFieldSideIcon::OnMouseEnter);
		m_slotBossInfoMouseLeave = m_pbtnStepTwoSideIcon->SigMouseLeave().Connect(this, &CDynamicFieldSideIcon::OnMouseLeave);
		
	}
	else
	{
		m_pbtnStepDisableSideIcon->Enable(false);
		m_pbtnStepOneSideIcon->Enable(false);
		m_pbtnStepTwoSideIcon->Enable(false);
		m_pbtnStepThreeSideIcon->Enable(true);

		m_slotBossInfoBtn = m_pbtnStepThreeSideIcon->SigClicked().Connect(this, &CDynamicFieldSideIcon::OnIconButtonClicked);
		m_slotBossInfoMouseEnter = m_pbtnStepThreeSideIcon->SigMouseEnter().Connect(this, &CDynamicFieldSideIcon::OnMouseEnter);
		m_slotBossInfoMouseLeave = m_pbtnStepThreeSideIcon->SigMouseLeave().Connect(this, &CDynamicFieldSideIcon::OnMouseLeave);
	}
}


// 点击按钮时
VOID CDynamicFieldSideIcon::OnIconButtonClicked(gui::CComponent* pComponent)
{
	// 弹出对应任务。写法应该是发送一个MSG给QuestGUI
	sQUEST_INFO		m_sData;

	m_sData.bVisitOP = false;
	m_sData.eProgType = eQUEST_PROGRESS_TYPE_NEW;
	m_sData.fXPos = 0;
	m_sData.fZPos = 0;
	m_sData.sKey.byTSType = 0;
	m_sData.sKey.taID = 255;
	m_sData.sKey.tcID = 255;
	m_sData.sKey.tgID = 255;
	m_sData.uiNPCTblIdx = INVALID_TBLIDX;

	CNtlTSTrigger* pTrig = ((CDboTSCMain*)API_GetQuestAgency()->GetParent())->FindQuestFromTS(6860);
	CDboTSContStart* pStartCont = (CDboTSContStart*)pTrig->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(START_CONTAINER_ID);
	CDboTSCheckLvl* pLvl = (CDboTSCheckLvl*)pStartCont->GetChildEntity(1);

	CNtlTSTrigger* pTrig2 = ((CDboTSCMain*)API_GetQuestAgency()->GetParent())->FindQuestFromTS(6861);
	CDboTSContStart* pStartCont2 = (CDboTSContStart*)pTrig2->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(START_CONTAINER_ID);
	CDboTSCheckLvl* pLvl2 = (CDboTSCheckLvl*)pStartCont2->GetChildEntity(1);

	RwUInt8 Level = Logic_GetLevel(GetNtlSLGlobal()->GetSobAvatar());
	if (Level >= pLvl->GetMinLvl() && pLvl->GetMaxLvl() > Level)
	{
		m_sData.dwQuestStartDialog = 686007;
		m_sData.dwQuestTitle = 686002;
		m_sData.sKey.tID = 6860;
		CNtlSLEventGenerator::DoQuest(m_sData, eEVENT_GEN_TYPE_CLICK_SIDEICON, INVALID_TBLIDX, FALSE);
	}
	if (Level >= pLvl2->GetMinLvl() && pLvl2->GetMaxLvl() >= Level)
	{
		m_sData.dwQuestStartDialog = 686107;
		m_sData.dwQuestTitle = 686102;
		m_sData.sKey.tID = 6861;
		CNtlSLEventGenerator::DoQuest(m_sData, eEVENT_GEN_TYPE_CLICK_SIDEICON, INVALID_TBLIDX, FALSE);
	}
}

// 当鼠标对准icon
void CDynamicFieldSideIcon::OnMouseEnter(gui::CComponent* pComponent)
{
	CSideIconGui::GetInstance()->OpenSideView(this, SIDEVIEW_DYNAMIC, NULL);
}

// 当鼠标移出icon
void CDynamicFieldSideIcon::OnMouseLeave(gui::CComponent* pComponent)
{
	CSideIconGui::GetInstance()->CloseSideView(SIDEVIEW_DYNAMIC);
}

VOID CDynamicFieldSideIcon::OnSideViewClosed()
{

}

// icon show
void CDynamicFieldSideIcon::Show(bool bShow)
{
	if (!m_DynamicFieldCount){
		__super::Show(FALSE);
		return;
	}
	__super::Show(bShow);
}