/******************************************************************************
* File			: PortalGui.h
* Author		: agebreak
* Copyright		: (��)NTL
* Date			: 2007. 10. 22
* Abstract		: 
*****************************************************************************
* Desc			: CPortalGui
*                 ��Ż NPC�� Ŭ���ϸ� ������ Portal GUI
*                 ��Ż�ʿ��� ���� ���� ��Ҹ� Ŭ���ϸ� �����̵� �ȴ�.
*				  
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"
#include "surfaceGui.h"

// presetation
#include "NtlPLGui.h"

class SNtlEventPortalInfoRes;


// ��Ż UI�� ���� �������� Ÿ��
enum EPortalIconType
{
    E_PORTAL_ICON_START_POINT,                      ///< ���� ����Ʈ�� ǥ���� ������
    E_PORTAL_ICON_START_POINT_FOCUS,
    E_PORTAL_ICON_ENABLE,                           ///< ���� �̵� ������ ������    
    E_PORTAL_ICON_ENABLE_FOCUS,

    MAX_ICON_TYPE_CNT,

    E_PORTAL_ICON_NOT,
};

/// ��Ż ������ ǥ���Ҷ� �Ѱ��ֱ� ���� ����ü
struct SPortalTooltip
{
    RwUInt32 nPortalID;
    RwInt32  ePortalIconType;
    DWORD    nZenny;
};

// ��Ż�� ���� (��Ż�� ID�� ���� Key���� �ȴ�.)
struct SPortalInfo
{
    RwInt32             m_nIndex;           ///< ��Ż�� ID
    CSurfaceGui         m_surIcon;          ///< ICon�� ǥ���� �����̽�
    EPortalIconType     m_eIconType;        ///< ���� ��Ż�� �������� ������ Ÿ��
    DWORD               m_nZenny;           ///< �Һ� ���� (���� ���� ��Ż�̸� 0)    
    RwBool              m_bRegist;          ///< ��� ����
};

class CPortalGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
    CPortalGui(const RwChar* pName);
    ~CPortalGui();

    RwBool      Create();
    VOID        Destroy();
    RwInt32     SwitchDialog(bool bOpen);                   ///< DialogManager������ Open/Close

protected:
    VOID        HandleEvents(RWS::CMsg &pMsg);
    VOID        Init();    
    
    VOID        SetupPortalInfo();                          ///< ��Ż���� �������� �����Ѵ� (���ʿ� �ѹ��� ȣ��)
    VOID        UpdatePortalInfo();                         ///< ��Ż���� �������� ������Ʈ�Ѵ�.
    RwBool      CheckRegist(RwUInt32 hNPCSerialID);         ///< ���� ��Ż ����Ʈ�� ��ϵǾ� �ִ� �������� üũ�ϰ�, ��ϵǾ� ���������� ����Ѵ�.    
    RwBool      IsConnect(RwUInt32 nPortalID, DWORD& nZenny);    ///< ���� ����Ʈ�� ����Ǿ� �ִ� ����Ʈ���� Ȯ���Ѵ�. (��ϵǾ� ������ True�� �ʿ� Zenny�� ��ȯ�Ѵ�)
    VOID        SetPortalInfo(SNtlEventPortalInfoRes* pInfo);    ///< ��ϵ� ��Ż���� ������ �����Ѵ�.
    RwInt32     FindPointIndex(RwUInt32 nCurrPortalID, RwUInt32 nTargetPortalID); ///< Ÿ�� ��Ż�� ��������Ʈ������ �ε����� ã�Ƽ� ��ȯ�Ѵ�. 

    inline RwBool      IsRegist(RwUInt32 nPortalID);               ///< ���� ��ϵǾ� �ִ��� Ȯ���Ѵ�.

    // CallBack
    VOID        OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
    VOID        OnMouseUp(const CKey& key);    
    VOID	    OnPaint();
    VOID	    OnMove(RwInt32 iOldX, RwInt32 iOldY);
    VOID	    OnClickExitBtn(gui::CComponent* pComponent);    

protected:
    typedef     std::map<RwUInt32, SPortalInfo*>  MAPPortalInfo;    
    typedef     std::pair<RwUInt32, SPortalInfo*> PAIRPortalInfo;

    MAPPortalInfo m_mapPortalInfo;                          ///< ��Ż���� ������ ������ �ִ� ��

    RwInt32     m_nCurrIdx;                                 ///< ���� ��ġ�ϰ� �ִ� ��Ż�� �ε���
    RwInt32     m_nSelectIdx;                               ///< ���� ������(Ŀ���� �����ִ�)�� ��Ż�� �ε���    
    RwUInt32    m_hNPCSerialID;                             ///< NPC�� Serail ID    
    RwBool      m_bTeleportSuccess;                         ///< �ڷ���Ʈ ���� ����
    
    gui::CSurface m_aSurIcon[MAX_ICON_TYPE_CNT];        ///< �����ܿ� ���� �����̽���

    // Control
    gui::CButton* m_pBtnExit; 

    // ������ ���� �ؽ�Ʈ��
    gui::CStaticBox* m_pSttStartPoint;                      
    gui::CStaticBox* m_pSttEnablePoint;    

    // slot
    gui::CSlot  m_slotMouseMove;
    gui::CSlot  m_slotMouseUp;
    gui::CSlot  m_slotPaint;
    gui::CSlot  m_slotBtnExit;
    gui::CSlot  m_slotMove;
};
