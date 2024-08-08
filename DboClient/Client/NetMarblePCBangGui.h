#pragma once

#include "NtlPLGui.h"
#include "ceventhandler.h"

/**
 * \ingroup Client
 * \brief �ݸ��� PC�� �ΰ� ǥ���ϴ� GUI Ŭ����
 * �κ�� ���ӿ��� ���� ���� �����ȴ�. (GUI �׷��� �ٸ���)
 * 
 * \date 2009-05-18
 * \author agebreak
 */
class CNetMarblePCBangGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
    enum ENetMarblePCBangPos
    {
        E_POSY = 4,
        E_WIDTH = 116,
        E_LOBBY = 1024 - 889,
        E_GAME = 1024 - 720,        
    };

public:
    CNetMarblePCBangGui(void);
    CNetMarblePCBangGui(const RwChar* pName);
    virtual ~CNetMarblePCBangGui(void);

    VOID		Init();
    RwBool		Create();
    VOID		Destroy();
    RwInt32		SwitchDialog(bool bOpen);
    VOID		HandleEvents(RWS::CMsg &pMsg);

protected:
    VOID			LocateComponent(RwInt32 IWidth, RwInt32 IHeight);

};
