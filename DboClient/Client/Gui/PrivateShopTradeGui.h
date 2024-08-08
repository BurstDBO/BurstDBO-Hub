/*****************************************************************************
* File			: PrivateShopTradeGui.h
* Author		: Jinsung, Kim -> Haesung, Cho
* Copyright		: (��)NTL
* Date			: 2007. 7. 4 , 2007. 12. 21
* Abstract		: DBO ���λ��� ����
*****************************************************************************
* Desc         : 
*****************************************************************************/

#ifndef __PRIVATE_SHOP_TRADE_GUI_H__
#define __PRIVATE_SHOP_TRADE_GUI_H__

#pragma once

#include "SlotGui.h"

class CPrivateShopGui;

/**
* \ingroup client
* ���λ��� ���� Gui ( ���λ��� ���� ���� Event�� �۵� )
*/
class CPrivateShopTradeGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	///< ���λ��� ���� GUI�� ä�� Ÿ��
	enum ePRIVATESHOP_TRADE_TALK_TYPE
	{
		ePRIVATESHOP_TRADE_TALK_TYPE_I,			///< �ڽ��� ���ϴ� ��
		ePRIVATESHOP_TRADE_TALK_TYPE_YOU,		///< ������ ���ϴ� ��
	};

public:
	CPrivateShopTradeGui(const RwChar* pName);
	virtual ~CPrivateShopTradeGui();

	RwBool	Create();
	void	Destroy();

	void	HandleEvents(RWS::CMsg& msg);
	RwInt32	SwitchDialog(bool bOpen);

	void	OnIMEChanged(RwInt32 eIMEState);
	void	OnMoveDlgTradeItem(RwInt32 iOldX, RwInt32 iOldY);
	void	OnPaintDlgTradeItem();

	void	OnGotFocus();
	void	OnLostFocus();

	void	OnClickedBtnAction(gui::CComponent* pComponent);
	void	OnClickedBtnClose(gui::CComponent* pComponent);
	void	OnChatReturn();

protected:
	void	SetInterface(RwUInt8 uiType, RwUInt32 uiShopOwner, WCHAR* pwcTargetName, const sPRIVATESHOP_ITEM_DATA* pPrivateShopItemData);
	void	ClearUserInterface();

	void	SetTradeItem(const sPRIVATESHOP_ITEM_DATA* pItemDatapPrivateShopItemData);
	void	AddChattingString(const WCHAR* pwcString, RwUInt32 uiColor);
	void	AddChattingString(ePRIVATESHOP_TRADE_TALK_TYPE eTalkType, const WCHAR* pwcString);

protected:
	gui::CStaticBox*		m_pStbTitle;
	gui::CButton*			m_pBtnClose;
	gui::CStaticBox*		m_pStbTradeItemTitle;
	gui::CDialog*			m_pDlgTradeItem;
	gui::CStaticBox*		m_pStbTradeItemName;
	gui::CStaticBox*		m_pStbTradeItemPriceTitle;
	gui::CStaticBox*		m_pStbTradeItemPrice;
	gui::CStaticBox*		m_pStbChattingTitle;
	gui::COutputBox*		m_pOpbChatting;
	gui::CInputBox*			m_pIpbChatting;
	gui::CStaticBox*		m_pStbIME;
	gui::CButton*			m_pBtnAction;

	gui::CSlot				m_slotIMEChanged;
	gui::CSlot				m_slotMoveDlgTradeItem;
	gui::CSlot				m_slotPaintDlgTradeItem;
	gui::CSlot				m_slotGotFocus;
	gui::CSlot				m_slotLostFocus;
	gui::CSlot				m_slotClickedBtnAction;
	gui::CSlot				m_slotClickedBtnClose;
	gui::CSlot				m_slotChatReturn;

	const sPRIVATESHOP_ITEM_DATA* m_pPrivateShopItemData;

	CPrivateShopGui*		m_pShopGui;

	CRegularSlotGui				m_sgTradeItem;
	sITEM_DATA				m_sTradeItemData;

	WCHAR					m_awcTargetName[NTL_MAX_SIZE_CHAR_NAME_UNICODE+1];	///< ���� ä�� ������ �̸�
	RwUInt32				m_uiShopOwner;				///< ���� ������ �ڵ�
	RwUInt8					m_uiTradeType;				///< ���� Ÿ��(PRIVATESHOP_BUY, PRIVATESHOP_SELL)
	RwUInt32				m_uiBusinessPrice;			///< ���� ���� ����	
	
	RwUInt16				m_uiFluctuationCount;		///< ������ ������ Ƚ��
	RwBool					m_bCloseNotify;				///< �������� ����â�� ������� ������ ���
};

/**
* \brief ���� ���� Gui
*/
class CPrivateShopTradeBoxGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CPrivateShopTradeBoxGui(const RwChar* pName);
	virtual ~CPrivateShopTradeBoxGui();

	RwBool	Create();
	void	Destroy();

	void	HandleEvents(RWS::CMsg& msg);
	RwInt32	SwitchDialog(bool bOpen);

	void	OnMoveDlgTradeItem(RwInt32 iOldX, RwInt32 iOldY);
	void	OnPaintDlgTradeItem();
	void	OnClickedBtnSubmit(gui::CComponent* pComponent);
	void	OnClickedBtnCancel(gui::CComponent* pComponent);
	void	OnClickedBtnPrice(gui::CComponent* pComponent);

protected: 
	void	ClearUserInterface();
	void	SetTradeItem(const sPRIVATESHOP_ITEM_DATA* pItemDatapPrivateShopItemData, RwUInt32 uiStartPrice);

protected: 
 	gui::CStaticBox*		m_pStbTitle;
	gui::CStaticBox*		m_pStbSubTitle;
 	gui::CButton*			m_pBtnClose;
 	gui::CDialog*			m_pDlgTradeItem;
 	gui::CStaticBox*		m_pStbTradeItemPricePrevTitle;
 	gui::CStaticBox*		m_pStbTradeItemPricePrev;
	gui::CStaticBox*		m_pStbTradeItemPriceNextTitle;
	gui::CStaticBox*		m_pStbTradeItemPriceNext;
	gui::CButton*			m_pBtnSubmit;
	gui::CButton*			m_pBtnCancel;
	gui::CButton*			m_pBtnPrice;
 
 	gui::CSlot				m_slotMoveDlgTradeItem;
 	gui::CSlot				m_slotPaintDlgTradeItem;
	gui::CSlot				m_slotClickedBtnSubmit;
	gui::CSlot				m_slotClickedBtnCancel;
	gui::CSlot				m_slotClickedBtnClose;
	gui::CSlot				m_slotClickedBtnPrice;

	const sPRIVATESHOP_ITEM_DATA* m_pPrivateShopItemData;

	RwUInt32				m_uiPrice;
 
 	CRegularSlotGui				m_sgTradeItem;
	sITEM_DATA				m_sTradeItemData;
};

#endif//__PRIVATE_SHOP_TRADE_GUI_H__