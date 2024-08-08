/******************************************************************************
* File			: HoipoiMixRecipe.h
* Author		: Haesung Cho
* Copyright		: (��)NTL
* Date			: 2009. 1. 8
* Abstract		: 
*****************************************************************************
* Desc			: ȣ������ �ͽ� ĸ�� ������ ������ ����Ʈ TAB
*****************************************************************************/

#ifndef _HOIPOIMIX_RECIPE_H_
#define _HOIPOIMIX_RECIPE_H_

#pragma once

#include "ceventhandler.h"
#include "NtlPLGui.h"
#include "SurfaceGui.h"
#include "NtlSharedType.h"
#include "SlotGui.h"

struct sITEM_RECIPE_TBLDAT;
class CHoipoiMixCapsuleGui;

class CRecipeDlgItem
{
public:
	CRecipeDlgItem();
	virtual ~CRecipeDlgItem();

	RwBool		Create( RwInt32 nIndex, CHoipoiMixCapsuleGui* pParentGui, TBLIDX idxRecipeTbl, RwUInt8 byDiscountRate );
	VOID		Destroy();

	RwUInt8		GetRecipeType();
	TBLIDX		GetRecipeTableIndex();

	VOID		SetDiscountRate( RwUInt8 byDiscountRate );
	VOID		RecipeItemDisposition( RwUInt32 uiIndex );
	VOID		Show( RwBool bShow );
	VOID		SelectItem( RwBool bSelect );

	VOID		OnEnterItem( gui::CComponent* pComponent );
	VOID		OnLeaveItem( gui::CComponent* pComponent );

	VOID		OnMouseDown( const CKey& key );
	VOID		OnMouseUp( const CKey& key );
	VOID		OnMouseMove( RwInt32 nKeys,RwInt32 nX, RwInt32 nY );

protected:
	VOID		OnPaint();

public:
	VOID		OnMove( int nOldX, int nOldY );

protected:
	gui::CDialog*		m_pThis;
	CRegularSlotGui			m_Slot;
	CSurfaceGui			m_surIcon;

	RwInt32				m_nIndex;
	TBLIDX				m_idxTbl;
	RwBool				m_bSelect;
	RwBool				m_bMouseDown;

	gui::CStaticBox*	m_pStbRecipeName;
	gui::CStaticBox*	m_pStbRequiredLevel;
	gui::CPanel*		m_pPnlSlot;
	gui::CStaticBox*	m_pStbZenny;

	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotMove;

	gui::CSlot			m_slotEnterItem;
	gui::CSlot			m_slotLeaveItem;

	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMouseMove;

	sITEM_RECIPE_TBLDAT*	m_pItemRecipeTblDat;
	CHoipoiMixCapsuleGui*	m_pHoipoiMix;
};

class CHoipoiMixRecipe
{
public:
	CHoipoiMixRecipe();
	virtual ~CHoipoiMixRecipe();

	// ������ ����Ʈ�� ������ �� ����ϴ� ����
	enum eFILTER	{ FILTER_NONE = -1, FILTER_TOTAL = 0, FILTER_BUILTIN, FILTER_NORMAL, FILTER_SPECIAL, NUM_FILTER };

	RwBool			Create( CHoipoiMixCapsuleGui* pParentGui );
	VOID			Destroy();

	VOID			Show( bool bShow );
	RwBool			IsShow();

	VOID			HandleEvents( RWS::CMsg& msg );

	VOID			OnAbsoluteMouseWheel( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );
	VOID			OnScrollChanged( RwInt32 nNewOffset );

	VOID			SelectFirstItem();

	RwBool			CreateAvatarRecipeList();
	VOID			DestroyAvatarRecipeList();

	RwBool			CreateBuiltInRecipeList(TBLIDX idxTblHoipoiMix);
	VOID			DestroyBuiltInRecipeList();

	VOID			OnToggledFilter( gui::CComponent* pComponent, bool bToggled );
	VOID			CreateRecipeFilterList();
	VOID			RecipeDispoisition();

	VOID			SelectRecipeItem( CRecipeDlgItem* pSelectItem );
	VOID			DeSelectRecipeItem();

protected:
	gui::CDialog*		m_pThis;
	gui::CButton*		m_pBtnFilter[NUM_FILTER];
	gui::CDialog*		m_pClipDialog;
	gui::CDialog*		m_pListDialog;
	gui::CScrollBar*	m_pScbBar;
	
	gui::CSlot			m_slotScrollChanged;
	gui::CSlot			m_slotScrollSliderMoved;
	gui::CSlot			m_slotToggledFilterTotal;
	gui::CSlot			m_slotToggledFilterBuiltIn;
	gui::CSlot			m_slotToggledFilterNormal;
	gui::CSlot			m_slotToggledFilterSpecial;

	typedef std::vector< CRecipeDlgItem* > RECIPE_VEC;
	RECIPE_VEC			m_vecAvatarRecipe;					///< �ƹ�Ÿ�� ������ �ִ� ������ ����Ʈ
	RECIPE_VEC			m_vecBuiltInRecipe;					///< ȣ������ �ͽ� �ӽſ� ���Ե� ������ ����Ʈ ( Dynamic Object�� Ŭ���� ������ �������� �� )

	RECIPE_VEC			m_vecShowListRecipe;

	gui::CSlot			m_slotAbsoluteMouseWheel;

	RwUInt8				m_byDiscountRate;					///< ȣ������ �ͽ� �ӽ��� ���� ���η� ( 0 ~ 100% )

	CRecipeDlgItem*		m_pSelectDlgItem;
	CHoipoiMixCapsuleGui*	m_pHoipoiMix;
};

#endif