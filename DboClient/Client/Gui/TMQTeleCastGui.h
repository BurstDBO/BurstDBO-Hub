/******************************************************************************
* File			: TMQTeleCastGui.h
* Author		: agebreak
* Copyright		: (��)NTL
* Date			: 2007. 11. 15
* Abstract		: 
*****************************************************************************
* Desc			: TMQ�� ��� �ý����� ���� GUI
*				  
*****************************************************************************/

#pragma once

#include "NtlPLGui.h"
#include "ceventhandler.h"
#include "NtlSLEvent.h"
#include "NtlPLCameraRenderTexture.h"
#include "NtlPLCharacter.h"
#include "SurfaceGui.h"
#include "DBOUIConfig.h"
#include "NtlPLAccelController.h"
    
class CTMQTeleCastGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
    /// ���� ���� �÷���
    enum ETeleCastState
    {
        TELECAST_SLIDING_IN,        ///< �����̵� �� ���� ����
        TELECAST_OPENING,           ///< ������ ���� ����
        TELECAST_OPEN,              ///< �Ϲ� ���� ����        
        TELECAST_CLOSING,           ///< ������ ���� ����
        TELECAST_SLIDING_OUT,       ///< �����̵� �ƿ� ���� ����
        TELECAST_CLOSED,            ///< ���� ����
    };

public:
    CTMQTeleCastGui(const RwChar* pName);
    ~CTMQTeleCastGui(void);

    // ���� ���̵�
    RwBool      Create();
    VOID        Destroy();
    VOID		Update(RwReal fElapsed);
    RwInt32     SwitchDialog(bool bOpen);                   ///< DialogManager������ Open/Close
    void	    Show(bool bShow);				
    VOID	    UpdateBeforeCamera(RwReal fElapsed);
    
protected:
    // ���� ���̵�
    VOID        HandleEvents(RWS::CMsg &pMsg);
    VOID        Init();    

    // CallBack
    VOID	    OnPaint();
    VOID		OnOpeningMovieEnd(gui::CComponent* pComponent);
    VOID		OnClosingMovieEnd(gui::CComponent* pComponent);
    VOID        OnFadeMovieEnd(gui::CComponent* pComponent);
    VOID	    OnMove(RwInt32 iOldX, RwInt32 iOldY);

    // ��ü �޼ҵ�
    VOID        LoadFlash(RwInt32 nWidth, RwInt32 nHeight);///< �÷��� ���ҽ����� �ε��Ѵ�.
    VOID        OnSlidingIn();                             ///< �����̵��� ������ �����Ѵ�.
    VOID        Opening();                                 ///< Opening ������ �Ѵ�
    VOID        Closing();                                 ///< Closing ������ �Ѵ�.
    VOID        UpdateShake(RwReal fElapsed);              ///< Shake ������ ������Ʈ �Ѵ�.
    VOID        UpdateSliding(RwReal fElapsed);            ///< �����̵� ������ ������Ʈ �Ѵ�.
    VOID        CreateNPCModel();                          ///< NPC ���� �����Ѵ�.
    VOID        CreateDialogBalloon();                     ///< ��ǳ���� �����Ѵ�.
    VOID        SetDialogBalloon();                        ///< ��ǳ���� �����Ѵ�.
    VOID        AdjustDialogBalloon();                     ///< ��ǳ���� ��ġ�� �����Ѵ�.
    VOID        CloseDialogBalloon();                      ///< ��ǳ���� ����.

protected:
    // ��Ʈ��    
    gui::CPanel*            m_pPnlBack;
    gui::CFlash*            m_pFlashFade;                   ///< Fade ���� �÷���
    gui::CFlash*            m_pFlashOpening;                ///< ������ ���� �÷���
    gui::CFlash*            m_pFlashClosing;                ///< ������ ���� �÷���
    gui::CFlash*            m_pFlashNoraml;                 ///< ���� ���� �÷���
    gui::CFlash*            m_pFlashWarn;                   ///< ���� ���� �÷���
    gui::CFlash*            m_pFlashBalloon;                ///< ���� ��ǳ�� �÷���
    std::map<RwInt32, gui::CFlash*> m_mapFlashBalloon;      ///< ��ǳ�� �÷��� ��
    gui::CStaticBox*        m_pSttBalloon;                  ///< ��ǳ�� �ؽ�Ʈ

    // ����
    gui::CSlot  m_slotPaint;
    gui::CSlot  m_slotOpeningMovieEnd;
    gui::CSlot  m_slotClosingMovieEnd;
    gui::CSlot  m_slotFadeMovieEnd;
    gui::CSlot  m_slotMove;

    // ��ü ��� ����
    ETeleCastState          m_eTeleCastState;               ///< ���� ���� ���� �÷���
    SNtlEventTeleCastBegNfy m_eventInfo;                    ///< �̺�Ʈ ������ ��� �ִ� ����ü
    DWORD                   m_dwDisplayTime;                ///< ǥ�� �ð�
    RwInt32                 m_nPrevBalloonType;             ///< ���� ��ǳ�� Ÿ��
    SUIConfigTeleCast*      m_pUIConfigTeleCast;            ///< Config ���� ����ü�� ������        

    // NPC ���� ����
    CNtlPLCameraRenderTexture m_NPCCamera;                  ///< NPC�� �������� ī�޶�    
    CNtlPLCharacter*          m_pNPCModel;                  ///< NPC �� ��ü
    CSurfaceGui               m_surNPC;                     ///< NPC�� �������� �����̽�
    gui::CTexture             m_NPCTexture;                 ///< NPC�� �������� �ؽ��� ��ü
    RwUInt32                  m_uiPrevNPCIdx;               ///< NPC ĳ���� ���ؼ� �����ϰ� �ִ� NPC �ε���

    // Shake �� �����̵� ����
    RwReal                    m_fFreqTime;                  ///< �������� ����ϱ� ���� Ÿ�� ����
    RwBool                    m_bShakeLeft;                 ///< ���� ������ ���� �ϱ� ���� ����        
    CNtlPLAccelController     m_AccelController;            ///< �����̵� ������ ���� ���ӵ� ��Ʈ�ѷ�
};
