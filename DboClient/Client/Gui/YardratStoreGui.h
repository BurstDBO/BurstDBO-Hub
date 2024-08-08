#pragma once

#include "NtlPLGui.h"
#include "ceventhandler.h"
#include "surfaceGui.h"
#include "Windowby3.h"
#include "NtlItem.h"
#include "NtlSobItem.h"
/**
* \ingroup Client
* \brief ���ȭ����  YardratStore  HLS Shopd�ļ� ������ ĳ������ �⺻������ Yardrat â�� ��ġ�� �Ǿ��ִ�.
*
*
*
* 
* \date 2009-08-24
* \author woosung_test
*/

class sITEM_TBLDAT;

class CYardratStoreGui : public CNtlPLGui, public RWS::CEventHandler
{
protected:


public:

	CYardratStoreGui( const RwChar* pName );
	~CYardratStoreGui(VOID);

	//! Operation
	VOID						Init(VOID);
	virtual RwBool				Create(VOID);
	virtual VOID				Destroy(VOID);

	VOID						UpdateSurfacePos();

	RwInt32						SwitchDialog(bool bOpen);
/*
	VOID						OpenDialog(GUI_EXTEND_MODE eMode, sITEM_TBLDAT* pITEM_TBLDAT, RwUInt32 uiItemIdx);
	VOID						OpenDialog();

	VOID						StartBuyDurItemProcessNPC( RwUInt32 uiItemIdx, RwUInt32 uiNPCSerial, sSHOP_BUY_CART& ShopBuyCart ); /// NPC, 
	VOID						StartBuyDurItemProcessNetpy( RwUInt32 uiItemIdx, RwUInt32 uiMerchantTblidx, BYTE byMerchanSlotPos ); /// Netpy Shop
	sITEM_TBLDAT*				StartBuyDurItemProcessCommonForItem( RwUInt32 uiItemIdx );
	VOID						StartMoveDurItemProcessCash( RwUInt32 uiItemIdx, RwUInt32 uiProductId );						/// Yardrat
	// Net
	VOID						NetSendBuyDurItemNPC();				/// NPC Shop
	VOID						NetSendBuyDurItemNetpy();			/// Netpy Shop
	VOID						NetSendMoveDurItemFromYardrat();	/// Yardrat
*/
	//! Event
	virtual VOID				HandleEvents( RWS::CMsg& msg );
/*
	//! Access
	VOID						SetDurationItem(RwUInt32 uiItemIdx);
	VOID						SetExtendTargetItem(CNtlSobItem* pNtlSobItem);
	VOID						SetCurrItemTbl(RwUInt32 uiItemIdx);
	VOID						SetCurrItemTbl(sITEM_TBLDAT* pITEM_TBLDAT);	/// ��� item ���� ���� setting
	/// setting���� GUI_EXTEND_MODE�� �����Ǿ� �־�� ��
	protected:
	//! Implementation
	VOID						ChangeExtendMode(GUI_EXTEND_MODE eMode);
	RwBool						SetIcon(const RwChar* pcIconName);

	VOID						OnMouseEnter_pnlItemButt(gui::CComponent* pComponent);			
	VOID						OnMouseLeave_pnlItemButt(gui::CComponent* pComponent);
	VOID						OnClicked_btnConfirm(gui::CComponent* pComponent);
	VOID						OnClicked_btnCancel(gui::CComponent* pComponent);
	VOID						OnClicked_btnBuyDuration(gui::CComponent* pComponent);
	VOID						OnClicked_btnRefillCash(gui::CComponent* pComponent);
	VOID						OnClicked_btnClose(gui::CComponent* pComponent);
	*/
	VOID						OnPaint(VOID);
	VOID						OnMove(int nX,int nY);

	// Gui Components
	gui::CStaticBox*			m_pStatic_stbTitle;					// title���� ����
	gui::CButton*				m_pButt_btnClose;
	gui::CDialog*				m_pDlg_dlgContentsScrolled;
/*
	gui::CPanel*				m_pPanel_pnlItemButt;
	//gui::CPanel*				m_pPanel_pnlPanel1;
	gui::CStaticBox*			m_pStatic_stbRemainTimeTitle;
	gui::CStaticBox*			m_pStatic_stbAddableTimeTitle;
	gui::CStaticBox*			m_pStatic_stbConsumeGoldTitle;
	gui::CStaticBox*			m_pStatic_stbMyGoldTitle;
	gui::CStaticBox*			m_pStatic_stbRemainTime;
	gui::CStaticBox*			m_pStatic_stbAddableTime;
	gui::CStaticBox*			m_pStatic_stbConsumeGold;
	gui::CPanel*				m_pPanel_pnlPanelConsumeGoldIcon;	
	gui::CStaticBox*			m_pStatic_stbMyGold;
	gui::CPanel*				m_pPanel_pnlPanelMyGoldIcon;		

	gui::CPanel*				m_pPanel_pnlPanel2;					// �������� ����
	gui::COutputBox*			m_pInput_opbDescriptDetail;

	gui::CPanel*				m_pPanel_pnlPanelName;
	gui::CStaticBox*			m_pStatic_stbItemName;
	gui::CStaticBox*			m_pStatic_stbDescript1;				// ��ȭ ��
	gui::CStaticBox*			m_pStatic_stbDescript2;				// ��ȭ ��
	gui::CButton*				m_pButt_btnConfirm;					// �������� ����
	gui::CButton*				m_pButt_btnCancel;					// ��ġ����
	gui::CButton*				m_pButt_btnBuyDuration;				// ������
	gui::CButton*				m_pButt_btnRefillCash;				// ������

	// Variable
	CSurfaceGui					m_surItemIconSlot;
	CSurfaceGui					m_surEnterSlot;
	CSurfaceGui					m_surConsumeGoldIcon;				// �ؽ�ó �ٲ� �� ����
	CSurfaceGui					m_surMyGoldIcon;					// �ؽ�ó �ٲ� �� ����
*/
	CWindowby3					m_DialogSurface;					///< ũ�� ���� ������ dialog�̹���
/*
	// Gui Signals
	gui::CSlot					m_slotGotFocus_pnlItemButt;
	gui::CSlot					m_slotLostFocus_pnlItemButt;
	gui::CSlot					m_slotClicked_btnConfirm;
	gui::CSlot					m_slotClicked_btnCancel;
	gui::CSlot					m_slotClicked_btnBuyDuration;
	gui::CSlot					m_slotClicked_btnRefillCash;
	gui::CSlot					m_slotClicked_btnClose;
*/
	gui::CSlot					m_slotPaint_dlgMain;
	gui::CSlot					m_slotMove_dlgMain;
	
};