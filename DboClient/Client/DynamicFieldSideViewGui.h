#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "Windowby3.h"
#include "SideIconGui.h"
#include "NtlSLEvent.h"

class CDynamicFieldSideViewGui :public CSideViewBase, public RWS::CEventHandler
{

public:
	CDynamicFieldSideViewGui(const RwChar* pName);
	virtual ~CDynamicFieldSideViewGui(void);

	RwBool		Create();
	VOID		Destroy();

	virtual VOID	OnPressESC();
	virtual VOID	OnSideViewOpen(const void* pData);
	virtual VOID	OnSideViewClose();
	virtual VOID	OnSideViewLocate(const CRectangle& rectSideIcon);

public:

	

protected:
	virtual VOID	HandleEvents(RWS::CMsg& msg);
	VOID			LocateComponent();
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnResize(RwInt32 iOldW, RwInt32 iOldH);
	VOID			OnPaint();

	void			DynamicProgress(float CurCount, float MaxCount);

	void			SetBossInfoText(DWORD CurCount,DWORD MaxCount);

protected:
	CWindowby3			m_BackPanel;	// ±≥æ∞‰÷»æÕº
	FLOAT				m_progress = 0.0f;

	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotResize;

	gui::CStaticBox*	m_pstbBossTitle;
	gui::CStaticBox*	m_pstbProgress;
	gui::CStaticBox*	m_pstbMapInfo;
	gui::CStaticBox*	m_pstbViewInfo;
	gui::CStaticBox*	m_pstbViewInfo1;
	gui::CStaticBox*	m_pstbQuest;
	gui::CStaticBox*	m_pstbTotal;

};