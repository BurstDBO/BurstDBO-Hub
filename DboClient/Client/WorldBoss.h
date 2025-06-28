#ifndef __WORLDBOSS_SIDE_ICON_GUI_H__
#define __WORLDBOSS_SIDE_ICON_GUI_H__

#include "SideIconGui.h"
#include "NtlPLGui.h"
#include "ceventhandler.h"

class CWorldBossSideIconGui :public CSideIconBase, public RWS::CEventHandler
{
public:
	CWorldBossSideIconGui(const RwChar* pName);
	~CWorldBossSideIconGui(VOID);

	RwBool	Create(VOID);
	VOID	Destroy(VOID);
	VOID	Update(RwReal fElapsedTime);

	VOID	OnSideViewClosed(VOID);

};

#endif