/******************************************************************************
* File			: PartyInvenGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Abstract		: 2006. 10. 30
*****************************************************************************
* Desc			: ��Ƽ �÷��̽� �й� ��Ŀ� ���� ���� ��� �̻��� �������� 
*				  ��Ƽ �κ��� �����ȴ�
*
*				  2009. 4. 28 : ��ȹ��(��ȫ��) ��û���� ��Ƽ�κ� ����� ����
*				  �ʱ�� �ߴ�. CGameGuiGroup���� CPartyInvenGui��ü��
*				  ���� ��ü�� ���� �ʴ´�
*****************************************************************************/

// core
#include "ceventhandler.h"

// share
#include "NtlParty.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// cleint
#include "SlotGui.h"

class CPartyInvenGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
#define dITEM_GRADE_IN_PARTY_INVEN_USED		ITEM_RANK_COUNT - 1

	enum eInvenDivideType
	{
		INVEN_DIVIDE_TYPE_BY_LEADER,
		INVEN_DIVIDE_TYPE_BY_OCTION,
		INVEN_DIVIDE_TYPE_BY_DICE,

		NUM_INVEN_DIVIDE_TYPE,

		INVALID_DIVIDE_TYPE
	};

	struct sPartyInvenSlot
	{
		CRegularSlotGui			slot;			///< ������ ����
		sITEM_PROFILE		ItemProfile;	///< InfoWindow ���� �����ֱ� ���� ����
	};

	struct sDivide_by_leader
	{
		gui::CStaticBox*	pMemberName[NTL_MAX_MEMBER_IN_PARTY];		///< ��Ƽ�� �̸�
		gui::CButton*		pSendItemButton[NTL_MAX_MEMBER_IN_PARTY];	///< ��Ƽ������ ������ �ֱ� ��ư
		gui::CSlot			slotButton[NTL_MAX_MEMBER_IN_PARTY];

		SERIAL_HANDLE		hSerial[NTL_MAX_MEMBER_IN_PARTY];			///< ��Ƽ�� �ø��� �ڵ�
	};	

	struct sDivide_by_Oction
	{
		struct sSlotInvest
		{
			SERIAL_HANDLE		hSerial;			///< ��Ƽ�� �ø��� �ڵ�
			RwUInt32			uiZenny;			///< ���ڵ� ����
			RwBool				bBestisAvatar;		///< �ڽ��� ���� ���� �����ߴ��� ����
			CSurfaceGui			srfOthersInvestedIcon;	///< ���� ���� ���� ������������ ������
			CSurfaceGui			srfMyInvestedIcon;		///< �ڽ��� ���� ���� ������������ ������
		};

		gui::CStaticBox*	pBidedMember;				///< ���� ���� ���� ���� ������ ��Ƽ��
		gui::CStaticBox*	pBidedZenny;				///< ���� ���� ���� ���ڵ� ��

		gui::CButton*		pBidedZennyButton;			///< ���� ���ڵ� ���� ���� �� �� ���� ��ư
		gui::CButton*		pOctionUnLockButton;		///< ��� ��� ��ư
		gui::CButton*		pOctionLockButton;			///< ��� �� ��ư
		gui::CButton*		pBidButton;					///< ���� ��ư
		gui::CButton*		pResetButton;				///< �ʱ�ȭ ��ư

		CSurfaceGui			srfZennySlotDestination;	///< ���� ���� Destination �̹���

		gui::CSlot			slotBidedZennyButton;
		gui::CSlot			slotOctionUnLockButton;
		gui::CSlot			slotOctionLockButton;
		gui::CSlot			slotBidButton;
		gui::CSlot			slotResetButton;

		CSurfaceGui			srfOctionBack;				///< ���â ���

		RwBool				bOctionLock;				///< ������ΰ� ����
		RwBool				bZennySlotDestination;
		sSlotInvest			slotInvest[NTL_PARTY_INVENTORY_SLOT_COUNT];	///< ���� ��� ���� ����
	};

	struct sDivide_by_Dice
	{
		gui::CButton*		pDiceButton;	///< �ֻ��� ������ ��ư
		gui::CSlot			slotButton;

		RwBool				bRollingDice;	///< �ֻ��� �����⸦ �����ߴ��� ����
	};
	
	CPartyInvenGui(const RwChar* pName);
	virtual ~CPartyInvenGui();

	static VOID		CreateInstance();
	static VOID		DestroyInstance();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CPartyInvenGui() {}
	virtual VOID HandleEvents( RWS::CMsg &msg );	

	VOID		Clear();
	VOID		CheckInfoWindow();

	VOID		ActivateDivideMethod(eInvenDivideType eType);
	VOID		ActivateDivideMethod_by_leader(bool bActive);
	VOID		ActivateDivideMethod_by_Oction(bool bActive);
	VOID		ActivateDivideMethod_by_Dice(bool bActive);

	VOID		EnableConrollers(bool bEnable);
	VOID		CalcInvestedAvatarZenny();

	VOID		OnClicked_MinimizeButton(gui::CComponent* pComponent);
	VOID		OnClicked_ItemGradeToggleButton(gui::CComponent* pComponent, bool bToggled);
	VOID		OnClicked_ChangeMethodDivideButton(gui::CComponent* pComponent);
	VOID		OnClicked_SendItemButton(gui::CComponent* pComponent);
	VOID		OnClicked_DiceButton(gui::CComponent* pComponent);
	VOID		OnClicked_Oction_ZennyButton(gui::CComponent* pComponent);
	VOID		OnClicked_Oction_LockUnLockButton(gui::CComponent* pComponent);
	VOID		OnClicked_Oction_BidButton(gui::CComponent* pComponent);
	VOID		OnClicked_Oction_ResetButton(gui::CComponent* pComponent);

	RwInt8		PtinSlot(RwInt32 iX, RwInt32 iY);
	VOID		FocusEffect(RwBool bPush, RwInt32 iSlotIdx = -1);
	VOID		SelectEffect(RwInt32 iSlot);

	VOID		OnMouseDown(const CKey& key);
	VOID		OnMouseUp(const CKey& key);
	VOID		OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID		OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID		OnMouseLeave(gui::CComponent* pComponent);
	VOID		OnCaptureMouseDown(const CKey& key);
	VOID		OnPaint();
	VOID		OnPostPaint();

protected:
	static CPartyInvenGui*	m_pInstance;

	gui::CSlot			m_slotMinimizeButton;
	gui::CSlot			m_slotItemGradeButton[dITEM_GRADE_IN_PARTY_INVEN_USED];
	gui::CSlot			m_slotLeftButton;
	gui::CSlot			m_slotRightButton;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;
	
	RwInt8				m_byInfoWindowIndex;///< Info Window�� �����ְ� �ִ� ������ �ε���
	RwInt32				m_iMouseDownSlot;	///< ���콺�� ���� ������ �ε���
	RwInt32				m_iSelectedSlot;	///< ���õ� ������ �ε���
	RwBool				m_bFocus;			///< ��Ŀ���� �����.	

	gui::CStaticBox*	m_pDialogName;		///< ���̾�α��� �̸� ����ƽ
	gui::CStaticBox*	m_pDivideMethod;	///< ���� �й� ��� ����

	gui::CButton*		m_pMinimizeButton;	///< �ּ�ȭ ��ư
	gui::CButton*		m_pItemGradeButton[dITEM_GRADE_IN_PARTY_INVEN_USED];	///< ������ ��� ��ư
	gui::CButton*		m_pLeftButton;		///< ��Ƽ �κ� �й� ��� ����(����)
	gui::CButton*		m_pRightButton;		///< ��Ƽ �κ� �й� ��� ����(����)

	CSurfaceGui			m_srfSlots;			///< ��Ƽ �κ��丮�� ��� �����۵��� ��� ����
	CSurfaceGui			m_srfDivideMethodBack;	///< �й� ��� ������ ���
	CSurfaceGui			m_FocusEffect;		///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;		///< ���� ����Ʈ ����Ʈ	

	sPartyInvenSlot		m_SlotInfo[NTL_PARTY_INVENTORY_SLOT_COUNT];	///< ���� ����

	eInvenDivideType	m_eInvenType;

	sDivide_by_leader	m_Divide_by_Leader;	///< ��Ƽ�忡 ���� �й��� ���� ����
	sDivide_by_Oction	m_Divide_by_Oction;	///< ��ſ� ���� �й��� ���� ����
	sDivide_by_Dice		m_Divide_by_Dice;	///< �ֻ��� �����⿡ ���� �й��� ���� ����
};