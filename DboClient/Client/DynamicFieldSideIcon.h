#ifndef _DYNAMICFIELD_SIDE_ICON_GUI_H_
#define _DYNAMICFIELD_SIDE_ICON_GUI_H_

// core
#include "ceventhandler.h"
#include "NtlSLEvent.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "SideIconGui.h"

class CDynamicFieldSideIcon :public CSideIconBase, public RWS::CEventHandler
{
public:
	CDynamicFieldSideIcon(const RwChar* pName);
	virtual ~CDynamicFieldSideIcon(void);

	RwBool	Create();
	VOID	Destroy();
	
	virtual VOID	OnIconButtonClicked(gui::CComponent* pComponent);
	virtual VOID	OnSideViewClosed();
	virtual void	Show(bool bShow);
	

protected:

	virtual VOID	HandleEvents(RWS::CMsg& msg);
	void            OnMouseEnter(gui::CComponent* pComponent);
	void            OnMouseLeave(gui::CComponent* pComponent);
	void			IconColor();
	void			DynamicProgress(float CurCount, float MaxCount);

protected:
	RwBool		m_DynamicFieldCount;
	bool		m_EventTime;
	FLOAT		m_progress;

	gui::CButton*	m_pbtnStepOneSideIcon;
	gui::CButton*	m_pbtnStepTwoSideIcon;
	gui::CButton*	m_pbtnStepThreeSideIcon;
	gui::CButton*	m_pbtnStepDisableSideIcon;

	gui::CSlot      m_slotBossInfoBtn;
	gui::CSlot      m_slotBossInfoMouseEnter;
	gui::CSlot      m_slotBossInfoMouseLeave;
	
};
#endif