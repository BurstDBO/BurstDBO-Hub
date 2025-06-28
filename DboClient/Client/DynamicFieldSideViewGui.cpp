#include "precomp_dboclient.h"
#include "DynamicFieldSideViewGui.h"

// core
#include "NtlDebug.h"

// presentation
#include "NtlPLGuiManager.h"

// dbo
#include "DisplayStringManager.h"
#include "DialogDefine.h"
#include "DialogManager.h"
#include "NtlStorageManager.h"
#include "NtlStorageGroupQuest.h"
#include "NtlStorageUnit.h"

#include "NtlSLGlobal.h"

CDynamicFieldSideViewGui::CDynamicFieldSideViewGui(const RwChar* pName)
:CSideViewBase(pName)
{

}

CDynamicFieldSideViewGui::~CDynamicFieldSideViewGui(void)
{
}

RwBool CDynamicFieldSideViewGui::Create()
{
	if (!CNtlPLGui::Create("", "gui\\DynamicFieldSideView.srf", "gui\\DynamicFieldSideView.frm"))
		return FALSE;

	CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

	m_pThis = (gui::CDialog*)GetComponent("dlgMain");

	// ����
	m_BackPanel.SetType(CWindowby3::WT_HORIZONTAL);
	m_BackPanel.SetSurface(0, GetNtlGuiManager()->GetSurfaceManager()->GetSurface("DynamicFieldSideView.srf", "srfDialogBackUp"));
	m_BackPanel.SetSurface(1, GetNtlGuiManager()->GetSurfaceManager()->GetSurface("DynamicFieldSideView.srf", "srfDialogBackCenter"));
	m_BackPanel.SetSurface(2, GetNtlGuiManager()->GetSurfaceManager()->GetSurface("DynamicFieldSideView.srf", "srfDialogBackDown"));
	
	// ���Ӳۺ���
	m_slotPaint = m_pThis->SigPaint().Connect(this, &CDynamicFieldSideViewGui::OnPaint);
	m_slotMove = m_pThis->SigMove().Connect(this, &CDynamicFieldSideViewGui::OnMove);
	m_slotResize = m_pThis->SigMove().Connect(this, &CDynamicFieldSideViewGui::OnResize);


	// ������Ⱦ����
	CRectangle rect;
	rect.SetRectWH(0, 15, 250, 14);
	m_pstbBossTitle = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_CENTER);
	m_pstbBossTitle->CreateFontStd(DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR);
	m_pstbBossTitle->SetTextColor(INFOCOLOR_7);
	m_pstbBossTitle->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_TITLE_01"));

	rect.SetRectWH(0,40,250,14);
	m_pstbProgress = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_CENTER);
	m_pstbProgress->CreateFontStd(DEFAULT_FONT, 115, DEFAULT_FONT_ATTR);
	m_pstbProgress->SetTextColor(INFOCOLOR_5);
	
	rect.SetRectWH(0, 60, 250, 14);
	m_pstbMapInfo = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_CENTER);
	m_pstbMapInfo->CreateFontStd(DEFAULT_FONT, 80, DEFAULT_FONT_ATTR);
	m_pstbMapInfo->SetTextColor(INFOCOLOR_5);
	m_pstbMapInfo->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_TITLE_04"));

	rect.SetRectWH(0, 80, 250, 14);
	m_pstbTotal = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_CENTER);
	m_pstbTotal->CreateFontStd(DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR);
	m_pstbTotal->SetTextColor(INFOCOLOR_5);

	// ���ν���
	rect.SetRectWH(20,105,250,14);
	m_pstbViewInfo = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_LEFT);
	m_pstbViewInfo->CreateFontStd(DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR);
	m_pstbViewInfo->SetTextColor(INFOCOLOR_0);
	m_pstbViewInfo->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_CONTENT_01"));
	rect.SetRectWH(20, 125, 250, 14);
	m_pstbViewInfo1 = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_LEFT);
	m_pstbViewInfo1->CreateFontStd(DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR);
	m_pstbViewInfo1->SetTextColor(INFOCOLOR_0);
	m_pstbViewInfo1->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_CONTENT_06"));

	// ��������
	rect.SetRectWH(0, 150, 250, 14);
	m_pstbQuest = NTL_NEW gui::CStaticBox(rect, m_pThis, GetNtlGuiManager()->GetSurfaceManager(), COMP_TEXT_CENTER);
	m_pstbQuest->CreateFontStd(DEFAULT_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR);
	//m_pstbQuest->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_CONTENT_04"));

	// ����smg����
	LinkMsg(g_EventDynamic_Count);

	Show(false);

	return true;
}


// ��������
VOID CDynamicFieldSideViewGui::HandleEvents(RWS::CMsg& msg)
{
	if (msg.Id == g_EventDynamic_Count) 
	{
		SNtlEventDynamicField_Count* pData = (SNtlEventDynamicField_Count*)msg.pData;
		// ����ٷֱ�
		DynamicProgress((float)pData->dwCurCount, (float)pData->dwMaxCount);

		//���½���
		SetBossInfoText(pData->dwCurCount, pData->dwMaxCount);
	}
}

// ���ý����ı�
void CDynamicFieldSideViewGui::SetBossInfoText(DWORD dwCurCount, DWORD dwMaxCount)
{
	m_pstbProgress->Format(L"%.1f%%", m_progress);
	m_pstbTotal->Format(L"%d / %d", dwCurCount, dwMaxCount);
}

// �������
void CDynamicFieldSideViewGui::DynamicProgress(float CurCount, float MaxCount)
{
	m_progress = (CurCount / MaxCount) * 100;
}

// �ݻ�
VOID CDynamicFieldSideViewGui::Destroy()
{
	GetNtlGuiManager()->RemoveUpdateFunc(this);

	UnLinkMsg(g_EventDynamic_Count);
	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();
}

// ��ϢUI��ʾ��
VOID CDynamicFieldSideViewGui::OnSideViewOpen(const void* pData)
{
	Show(true);
	if (IsShow())
	{
		RwBool NoQuest = FALSE;
		for (auto it : GetNtlSLGlobal()->GetAvatarInfo()->wQuestListTid)
		{	
			if (it == 6861 || it == 6860)
			{
				m_pstbQuest->SetTextColor(INFOCOLOR_9);
				m_pstbQuest->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_CONTENT_05"));
				NoQuest = TRUE;
				break;
			}
		}

		if (!NoQuest)
		{
			m_pstbQuest->SetTextColor(INFOCOLOR_14);
			m_pstbQuest->SetText(GetDisplayStringManager()->GetString("DST_DYNAMIC_FIELD_SIDEVIEW_CONTENT_04"));
		}
		
	}
}

// ��ϢUI��ʾλ��
VOID CDynamicFieldSideViewGui::OnSideViewLocate(const CRectangle& rectSideIcon)
{
	RwInt32 iHeight = 190;
	m_pThis->SetHeight(iHeight);
	LocateComponent();
	m_pThis->SetPosition(rectSideIcon.left - m_pThis->GetWidth() + rectSideIcon.GetWidth(), rectSideIcon.top - iHeight);
}

// ��ϢUI��ʾ�ر�
VOID CDynamicFieldSideViewGui::OnSideViewClose()
{
	Show(false);
}


// ��סESC
VOID CDynamicFieldSideViewGui::OnPressESC()
{

}

VOID CDynamicFieldSideViewGui::LocateComponent()
{
	m_BackPanel.SetRect(m_pThis->GetScreenRect());
}

// �ƶ�
VOID CDynamicFieldSideViewGui::OnMove(RwInt32 iOldX, RwInt32 iOldY)
{
	LocateComponent();
}
// ������С
VOID CDynamicFieldSideViewGui::OnResize(RwInt32 iOldW, RwInt32 iOldH)
{
	LocateComponent();
}
// ��Ⱦ
VOID CDynamicFieldSideViewGui::OnPaint()
{
	m_BackPanel.Render();
}