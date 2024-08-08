////////////////////////////////////////////////////////////////////////////////
// File: BuffDispObject
// Desc: Buff Gui Object. 
//		 - �ߺ� ������ �����ϵ��� ����.
//
//		 - 1. Show(), Update(), Move()���� �����ϴ� ��ü���� ������ �־�� ��. 
//
// 2007.05.07 Peessi@hitel.net   
////////////////////////////////////////////////////////////////////////////////

#ifndef __BUFF_DISP_OBJECT_H__
#define __BUFF_DISP_OBJECT_H__

#include "gui_precomp.h"
#include "guicore_precomp.h"
#include "SurfaceGui.h"
#include "DialogDefine.h"

class CNtlBuffContainer;
class CNtlFakeBuffContainer;
class CNtlSobBuff;
class CNtlSobBuffAttr;
struct sNtlFakeBuff;

class CBuff
{
public:
	//! Enumeration
	enum TYPE { TYPE_NONE, TYPE_SKILL, TYPE_ITEM };

	//! Constructor & Destructor
	CBuff(VOID) { m_eType = TYPE_NONE; }
	virtual ~CBuff(VOID) {}

	virtual VOID SetBuff( void* pBuff, TYPE eType ) {}
	virtual VOID ShowInfoWnd( RwInt32 nParentX, RwInt32 nParentY, RwInt32 nDlgType ) {}
	virtual VOID DropBuff(VOID) {}

	VOID SetMove( RwInt32 nScreenX, RwInt32 nScreenY );
	VOID SetRect( RwInt32 nX, RwInt32 nSize, gui::CSurface& KeepTimeSurface );

	virtual VOID Update( RwReal fElapsedTime ) {}
	VOID Render(VOID);

	//! Variable
	CRectangle			m_Rect;
	CSurfaceGui			m_Surface;
	TYPE				m_eType;

	gui::CRadarEffect	m_KeepTimeEffect;
};

class CSobBuff : public CBuff
{
public:
	CSobBuff(VOID) { m_pBuff = NULL; }
	virtual ~CSobBuff(VOID) {}

	VOID	SetBuff( void* pBuff, TYPE eType );
	VOID	ShowInfoWnd( RwInt32 nParentX, RwInt32 nParentY, RwInt32 nDlgType );
	VOID	DropBuff(VOID);

	VOID	Update( RwReal fElapsedTime );

	CNtlSobBuff*	m_pBuff;
};

class CFakeBuff : public CBuff
{
public:
	CFakeBuff(VOID) { m_pBuff = NULL; }
	virtual ~CFakeBuff(VOID) {}

	VOID	SetBuff( void* pBuff, TYPE eType );
	VOID	ShowInfoWnd( RwInt32 nParentX, RwInt32 nParentY, RwInt32 nDlgType );

	VOID	Update( RwReal fElapsedTime );

	sNtlFakeBuff*	m_pBuff;
};

class CBuffDispBar
{
public:
	//! Constructur & Destructor
	CBuffDispBar(VOID);
	~CBuffDispBar(VOID);

	//! Operation
	VOID	Create( RwInt32 nBuffCount, eDialogType eDlgType, RwInt32 nIconSize, RwInt32 eBuffOrigin );
	VOID	Destroy(VOID);

	VOID	Update( RwReal fElapsedTime );	

	VOID	SetBuff( VOID* pBuff, CBuff::TYPE eType, RwInt32 nSlot );
	VOID	SetMove( RwInt32 nScreenX, RwInt32 nScreenY );
	VOID	SetSize( RwInt32 nWidth, RwInt32 nHeight );
	VOID	Show( bool bShow );

	VOID	RefreshInfoWnd(VOID);

protected:
	//! Implementation
	VOID	SetBuffRect( RwInt32 nIconSize );

	//! CallBack
	VOID	OnMouseDown( const CKey& key );
	VOID	OnMouseMove( RwInt32 nKey, RwInt32 nXPos, RwInt32 nYPos );
	VOID	OnMouseLeave( gui::CComponent* pComponent );
	VOID	OnMove( RwInt32 nX, RwInt32 nY );
	VOID	OnPaint(VOID);

	gui::CSlot		m_slotMouseDown;
	gui::CSlot		m_slotMouseMove;
	gui::CSlot		m_slotMouseLeave;
	gui::CSlot		m_slotMove;
	gui::CSlot		m_slotPaint;

	//! Variable
	gui::CDialog*	m_pDialog;
	eDialogType		m_eDlgType;

	CBuff**			m_ppArrBuff;
	RwInt32			m_nBuffCnt;

	RwInt32			m_nMouseOnIndex;
};

class CBuffDispGui
{
public: 
	//! Enumuration
	enum TYPE		{ TYPE_2X8, TYPE_4X4 };
	enum ICONSIZE	{ SMALL_ICONSIZE = 16, NORMAL_ICONSIZE = 20 };
	enum BUFFATTR	{ BLESS_BUFF, CURSE_BUFF };
	enum ORIGIN		{ SOBBUFF, FAKEBUFF };
		
	//! Contructor & Destructor
	CBuffDispGui(VOID);
	~CBuffDispGui(VOID);

	//! Operation
	VOID	Create( TYPE eType, ICONSIZE eIconSize, RwInt32 nOffsetX, RwInt32 nOffsetY, eDialogType eDlgType, ORIGIN eOrigin = SOBBUFF );	
	VOID	Destroy(VOID);

	VOID	Update( RwReal fElapsedTime );

	VOID	SetBuffAll( RwUInt32 hSerial );
	VOID	SetBuffAll( CNtlFakeBuffContainer* pFakeBuffContainer );
	VOID	ClearBuff(VOID);
	
	VOID	SetMove( CRectangle& rtScreen );	// ���� �ִ� GUI�� ��ũ�� ��ǥ�� �Ѱ��ִ� ������ OK.
	VOID	Show( bool bShow );					// ���� �ִ� GUI�� Show�� ���� ������ �� �ֵ���.
	
protected:
	//! Implementation
	VOID	BuffRegisterProc( CNtlBuffContainer* pBuffContainer );
	VOID	BuffRegisterProc( CNtlFakeBuffContainer* pFakeBuffContainer	);
	VOID	BuffUnregisterProc(VOID);
	VOID	RegisterBuffToSlot( VOID* pBuff, BUFFATTR eBuffAttrType, CBuff::TYPE eBuffOriginType, RwInt32 nIndex );
	VOID	FitBuffBarRect( RwInt32 nBlessBuffCnt, RwInt32 nCurseBuffCnt );

	//! Variable
	TYPE			m_eType;	
	RwInt32			m_nRowCnt;
	RwInt32			m_nColCnt;
	ICONSIZE		m_eIconSize;

	CBuffDispBar*	m_pArrBuffBar;	

	RwInt32			m_nOffsetX;					// �� ��ü�� �����ϴ� Gui���� ��ǥ ����.
	RwInt32			m_nOffsetY;	

	RwReal			m_fUpdateInfoTime;	

	RwBool			m_bShow;
	RwBool			m_bEnable;			
};

#endif//__BUFF_DISP_OBJECT_H__