/******************************************************************************
* File			: PartyCharmGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Abstract		: 2006. 10. 23
*****************************************************************************
* Desc			: ��Ƽ ������ ����Ͽ� �ߵ���Ű�� ���� GUI
*****************************************************************************/

// core
#include "ceventhandler.h"

// shared
#include "NtlParty.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLParty.h"
#include "NtlSLDef.h"

// dbo
#include "SlotGui.h"

struct sPartyMember;

class CPartyCharm : public CNtlPLGui, public RWS::CEventHandler
{
public:
	struct sMemberVictim
	{
		gui::CStaticBox*	pName;				///< �̸�
		gui::CProgressBar*	pZennyGauge;		///< Zenny �ۼ�Ʈ
		CSurfaceGui			srfGaugeBack;

		SERIAL_HANDLE		hMember;
		RwUInt32			uiZenny;

		sMemberVictim()
			:hMember(INVALID_SERIAL_ID), uiZenny(0)
		{}
	};

	struct sBagLockInfo
	{
		SERIAL_HANDLE		hHandle;
		RwUInt8				byPlace;
		RwUInt8				byPos;
	};

	CPartyCharm(const RwChar* pName);
	virtual ~CPartyCharm();

	static VOID		CreateInstance();
	static VOID		DestroyInstance();

	// GageStage ���ᰡ �ƴ� ������ Ŭ������ ����� ���� ȣ��, �׷��� ������ ����� Sob��ü��
	// �����Ͽ� ����� ������ �ִ�
	static VOID		ClearBagLock();

	RwBool		Create();
	VOID		Destroy();	

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CPartyCharm() {}
	virtual VOID HandleEvents( RWS::CMsg &msg );

	VOID		Clear();
	VOID		CheckInfoWindow();
	VOID		CheckIconMove();

	VOID		AddMember(sPartyMember* pMember);
	VOID		DelMember(SERIAL_HANDLE hHandle);

	sMemberVictim* GetMemberVictim(SERIAL_HANDLE hHandle);

	RwUInt32	GetTotalCharmZenny();

	VOID		RefreshTotalZenny();

	RwBool		PtinSlot(RwInt32 iX, RwInt32 iY);
	VOID		FocusEffect(RwBool bPush);
	VOID		SelectEffect(RwBool bPush);

	VOID		OnClicked_CloseButton(gui::CComponent* pComponent);
	VOID		OnClicked_ZennyButton(gui::CComponent* pComponent);
	VOID		OnClicked_ActivateButton(gui::CComponent* pComponent);

	VOID		OnMouseDown(const CKey& key);
	VOID		OnMouseUp(const CKey& key);
	VOID		OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID		OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID		OnMouseLeave(gui::CComponent* pComponent);
	VOID		OnPaint();
	VOID		OnPostPaint();

protected:
	static CPartyCharm*	m_pInstance;

	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;	
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotBtnZenny;
	gui::CSlot			m_slotActivateButton;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;

	gui::CTexture*		m_pMoneyIconTexture;

	gui::CStaticBox*	m_pDialogName;				///< ���̾�α��� �̸� ����ƽ
	gui::CStaticBox*	m_pDestZenny;				///< "��ǥ�ݾ�"
	gui::CStaticBox*	m_pDestZennyPoint;			///< ��ǥ Zenny
	gui::CStaticBox*	m_pAvatarName;				///< �ƹ�Ÿ �̸�
	gui::CStaticBox*	m_pCurZenny;				///< ���� �ڽ��� ������ Zenny

	gui::CProgressBar*	m_pZennyGauge;				///< ��ü Zenny ������

	gui::CButton*		m_pExitButton;
	gui::CButton*		m_pZennyButton;				///< Zenny ���� ��ư
	gui::CButton*		m_pActivateButton;			///< ���� �ߵ� ��ư

	CRegularSlotGui			m_CharmSlot;

	CSurfaceGui			m_FocusEffect;				///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;				///< ���� ����Ʈ ����Ʈ
	CSurfaceGui			m_srfCharmPanel;			///< ���������� �ִ� ������ ���
	CSurfaceGui			m_srfZennySlotDestination;	///< ���� ���� Destination �̹���
	CSurfaceGui			m_srfZennyIcon;				///< ���� ������
	CSurfaceGui			m_srfCharmSlot;				///< ���� ���� ���
	CSurfaceGui			m_srfZennyGaugeBack;		///< ��ü ���� ������ ���

	sMemberVictim		m_MemberVictim[NTL_MAX_MEMBER_IN_PARTY];

	RwBool				m_bSelect;
	RwBool				m_bFocus;
	RwBool				m_bZennySlotDestination;
	RwBool				m_bLeftMouseDown;
	RwBool				m_bRightMouseDown;

	sBagLockInfo		m_BagLockInfo;
	sCHARM_TBLDAT*		m_pCHARM_TBLDAT;			///< ��ϵ� ������ �� ���̺�
};