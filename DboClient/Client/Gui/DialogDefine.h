/******************************************************************************
* File			: DialogDefine.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 11
* Abstract		: 
*****************************************************************************
* Desc			: Dialog ���� ����
*****************************************************************************/

#pragma once

enum eDialogVisible
{
	DIALOGVISIBLE_FALSE,					///< ���̾�α׸� �ݴ´�.
	DIALOGVISIBLE_TRUE						///< ���̾�α׸� ����.
};

// SideDilaog�� �ε����� ��ġ�� �ʵ��� �����Ѵ�
enum eDialogType
{
	DIALOG_FIRST,

	// GM Dialog(ESC Ű�� ������ ���� �ʴ´�)

	DIALOG_GM_FIRST = DIALOG_FIRST,
	
	DIALOG_GM_QUICKSLOT = DIALOG_GM_FIRST,

	DIALOG_GM_LAST = DIALOG_GM_QUICKSLOT,


	// �⺻ ���̾�α�(������ �⺻������ ǥ�õ� ���̾�α�, ESC Ű�� ������ ���� �ʴ´�)

	DIALOG_DEFAULT_FIRST,

	DIALOG_HP = DIALOG_DEFAULT_FIRST,		///< HP ������
	DIALOG_EXP,								///< EXP â(����ġ)
	DIALOG_CHAT,							///< ä��â
	DIALOG_QUICKSLOT,						///< ������ â	
	DIALOG_BAGSLOT,							///< ĸ�� ����	
	DIALOG_MINIMAP,							///< �̴ϸ�	
	DIALOG_MAINMENUBUTTON,					///< ���� �޴� ��ư
	DIALOG_SCOUTER_SLOT,					///< ��ī���� ����(���� ���� �ִ�)
	DIALOG_SIDEICON,						///< ���̵� ������
	DIALOG_SIDEDIALOG_MANAGER,				///< ���̵� ���̾�α� �Ŵ���	
	DIALOG_SIDEDIALOG_CONTROLLER,			///< ���̵� ���̾�α� ��Ʈ�ѷ�
	DIALOG_PARTYMENU,						///< ��Ƽ �޴�(��Ƽ �ɹ�â�� �ڽ����� ���´�)
	DIALOG_GM_CHATTING,						///< GM ä��
	DIALOG_GROUP_CHAT_MANAGER,				///< Group ä�� �Ŵ���
	DIALOG_DICE_MANAGER,					///< �ֻ��� �Ŵ���
	DIALOG_VEHICLE,							///< Ż �� ����â
    DIALOG_NETMARBLEPCBANG,                 ///< �ݸ��� PC�� �ΰ�

	DIALOG_DEFAULT_LAST = DIALOG_NETMARBLEPCBANG,
	

	// Event Dialog(�⺻������ ESC Ű�� ������ ���� �ʴ´�)

	DIALOG_EVENT_FIRST,

	DIALOG_TARGER_UI = DIALOG_EVENT_FIRST,	///< Ÿ�� UI
	DIALOG_SCOUTER_BACKGROUND,				///< ��ī���� ��� ȭ��	
	DIALOG_SCOUTER_MEASURE,					///< ��ī���� ������ ����
	DIALOG_SHOPING_CART,					///< ������ īƮ
	DIALOG_TRADECART,						///< Ʈ���̵� īƮ
	DIALOG_PRIVATESHOP_CART,				///< ���λ��� īƮ
	DIALOG_PRIVATESHOP_TRADEBOX,			///< ���λ��� ���� �ڽ�
	DIALOG_NETPYSHOP_TRADE,					///< NetPy Shop Trade Cart
	DIALOG_SCOUTER_INFO,					///< ��ī���� ����â
	DIALOG_WAREHOUSE_1,						///< 1�� â��
	DIALOG_WAREHOUSE_2,						///< 2�� â��
	DIALOG_WAREHOUSE_3,						///< 3�� â��
	DIALOG_WAREHOUSE_COMMON,				///< ���� â��
	DIALOG_DBC_REWARD,						///< �巡�ﺼ ���� GUI
	DIALOG_DBC_DRAGON_DIALOG,				///< ����� ��ȭ ��ǳ�� GUI
	DIALOG_DROPITEM_INFO,					///< ��Ӿ����� ����â
	DIALOG_TMQ_REWARD,						///< Ÿ�Ӹӽ� ����Ʈ ����â
	DIALOG_BACKBOARD,						///< ȭ����ü�� ������ �麸��â	
	DIALOG_FLASH_NOTIFY,					///< Flash�� �̿��� Notify �˸�â
	DIALOG_INTERFACE_SHAKE,					///< �˴ٿ� �� �������̽��� �����Ͽ� ȸ���� ������ �ϴ� â
    DIALOG_NET_CONNECT_BOX,                 ///< ���� ���� ���н� ���¸� ǥ���ϴ� ���̾�α� �ڽ�
    DIALOG_TELECAST,                        ///< ���â
	DIALOG_TIME_NOTIFY,						///< �ð� �˸� ǥ��â
	DIALOG_GUILD_WAREHOUSE_1,				///< ��� 1�� â��
	DIALOG_GUILD_WAREHOUSE_2,				///< ��� 2�� â��
	DIALOG_GUILD_WAREHOUSE_3,				///< ��� 3�� â��
	DIALOG_TUTORIAL_DIALOG_FOCUS,			///< Ʃ�丮�� ���̾�α� ��Ŀ��â
	DIALOG_TUTORIAL_EXAMPLE,				///< Ʃ�丮�� ����â
	DIALOG_TUTORIAL_MESSAGE,				///< Ʃ�丮�� �޼���
	DIALOG_TUTORIAL_CONFIRM,				///< Ʃ�丮�� Ȯ�� �޼���
	DIALOG_PETITION_SATISFACTION,			///< GM ��� ������ ����â
	DIALOG_BROADCAST,
	DIALOG_PET_STATUSBAR,					///< �� ���� â    
	DIALOG_PET_SKILL_SLOT,                ///< ���� ��ȯ������ ��Ÿ���� ��ų ����â
	DIALOG_SCRAMBLE_NOTIFY,					///< ���� ��Ż�� ���� �˸�â

	DIALOG_EVENT_LAST = DIALOG_SCRAMBLE_NOTIFY,

	
	// ������ ���ۿ� ���� ȭ�鿡 �׷����� ���̾�α�

	DIALOG_NORMAL_FIRST, 

	DIALOG_MAINMENU = DIALOG_NORMAL_FIRST,	///< ���� �޴�	
	DIALOG_ESCMENU,							///< ESC Menu
	DIALOG_STATUS,							///< �������ͽ� ������			
	DIALOG_SKILL,							///< ��ųâ
	DIALOG_SCOUTER_BODY,					///< ��ī���� �ٵ�â		
	DIALOG_CHAT_LOG,						///< ä�÷α�â
    DIALOG_COMMUNITY,						///< Ŀ�´�Ƽ ���̾�α�
    DIALOG_FRIEND_LIST,                     ///< ģ�� ����Ʈ/�� ����Ʈ
	DIALOG_WORLDMAP,						///< �����
	DIALOG_OPTIONWND,						///< �ɼ� ������
	DIALOG_HELPWND,							///< ���� ������	
	DIALOG_PRIVATESHOP,						///< ���λ���
	DIALOG_PRIVATESHOP_TRADE,				///< ���λ��� ����
	DIALOG_MAILSYSTEM,						///< ���� �ý���
	DIALOG_MAILSYSTEM_READ,					///< ���� �ý��� : ���� �б�
	DIALOG_DBC_ALTAR,						///< �巡�ﺼ �÷��� ���� ������
    DIALOG_COMMU_TARGET,                    ///< Ŀ�´�Ƽ Ÿ��â
	DIALOG_SCOUTER_MENU,					///< ��ī���� �޴�
	DIALOG_HOIPOIMIX_CAPSULE,				///< ȣ������ �ͽ� ĸ�� �ý���	

	DIALOG_CAPSULE_1,						///< ����
	DIALOG_CAPSULE_2,
	DIALOG_CAPSULE_3,
	DIALOG_CAPSULE_4,
	DIALOG_CAPSULE_5,
	DIALOG_CAPSULE_NETPY,					///< 

	//DIALOG_MSGBOX,							///< �޼����ڽ� (�߾�����)
	
	DIALOG_QUESTLIST,						///< ����Ʈ����Ʈ 
	DIALOG_QUESTPROGRESS,					///< ����Ʈ����	
	
	DIALOG_SKILL_RPBONUS,					///< RP BONUS ��ų ��� GUI
	DIALOG_SKILL_RPBONUS_AUTO,

	DIALOG_RANKBOARD,						///< Ranking Board
	DIALOG_BUDOKAI_NEWS,					///< õ������ ����ȸ �ҽ���
	DIALOG_BUDOKAI_REQUEST,					///< õ������ ����ȸ ��û��
	DIALOG_BUDOKAI_TOURNAMENT,
	DIALOG_BUDOKAI_TOURNAMENT_MATCHINFO,	///< ��ʸ�Ʈ MatchInfo

	DIALOG_TBGAMBLERESULT,					///< �׺� ĸ�� Ȯ�� â
	DIALOG_CHANNGEL_CHANGE,					///< ������ ä�� ���� â
	DIALOG_PETITION,						///< GM ��� ��ûâ

	DIALOG_SKILLABILITYSET,					///< Skill Ability ���� GUI
	DIALOG_SKILLABILITYUSE,

	DIALOG_SKILL_HTB_RPUSE,					///< HTB Skill Rp Use Gui

	DIALOG_GMT_RESET,

	DIALOG_NORMAL_LAST = DIALOG_GMT_RESET,


	// NPC ���� ���̾�α�(�⺻������ ESC Ű�� ������ ���� �ʴ´�)

	DIALOG_NPCDIALOG_FIRST,

	DIALOG_MULTIDIALOG = DIALOG_NPCDIALOG_FIRST,///< NPC ��Ƽ���̾�α�
	
	DIALOG_SKILL_TRAINER,					///< ��ų Ʈ���̳� â
	DIALOG_QUESTMESSAGE,					///< ����Ʈ�޼���	
	DIALOG_QUESTPROPOSAL,					///< ����Ʈ����	
	DIALOG_QUESTREWARD,						///< ����Ʈ����
	DIALOG_ITEMUPGRADE,						///< ������ ���׷��̵�	
	DIALOG_RBBOARD,							///< ��ũ��Ʋ �Խ���
	DIALOG_RBCHALLENGE,						///< ��ũ��Ʋ ��������
	DIALOG_NPCSHOP,							///< NPC ����	
	DIALOG_TMQBOARD,						///< Ÿ�Ӹӽ� ����Ʈ �Խ���	
	DIALOG_WAREHOUSEBAR,					///< â�� ��Ʈ�� ��	
    DIALOG_PORTAL,                          ///< ��Ż NPC 
	DIALOG_OBJECT_CLICK,					///< ������Ʈ Ŭ��
	DIALOG_GUILD_WAREHOUSEBAR,				///< ��� â�� ��Ʈ�� ��
	DIALOG_DOJO_INFO,						///< ���� ����â
	DIALOG_DOJO_ACCOUNT,					///< ���� â�� ��볻��
	DIALOG_DOGI,							///< ���� ���̾�α�
	DIALOG_DOJO_UPGRADE,					///< ���� ���׷��̵� ���̾�α�
	DIALOG_NETPYSHOP,
	DIALOG_DURATION_EXTEND_CONFIRM,			///< �Ⱓ���� ���̾�α�
	DIALOG_YARDRAT,							///< �ߵ巡Ʈ â��
	DIALOG_NPCDIALOG_LAST = DIALOG_NETPYSHOP,

	DIALOG_NUM,

	DIALOG_LAST = DIALOG_NPCDIALOG_LAST,

	DIALOG_UNKNOWN = 0xFF,					///< �߸��� ���̾�α� �ε���
};

enum eDialogMode
{	
	DIALOGMODE_ITEM_REPAIR,					///< ������ ���� ���
	DIALOGMODE_ITEM_IDENTIFICATION,			///< ��Ȯ�� ������ ����
	DIALOGMODE_NPCSHOP_ITEM_IDENTIFICATION,	///< �������� ��Ȯ�� ������ ����
	DIALOGMODE_NARRATION,					///< �����̼� ���

	DIALOGMODE_CHATTING_RESIZE_HORI,		///< ä�� ���÷���â ���� ��������
	DIALOGMODE_CHATTING_RESIZE_RIGHTUP,		///< ä�� ���÷���â ���� ��������
	DIALOGMODE_CHATTING_RESIZE_RIGHTDOWN,	///< ä�� ���÷���â ���ϴ� ��������
	DIALOGMODE_CHATTING_RESIZE_VERT,		///< ä�� ���÷���â ���� ��������

	DIALOGMODE_UNKNOWN,

	DIALOGMODE_FIRST = DIALOGMODE_ITEM_REPAIR,
	DIALOGMODE_LAST  = DIALOGMODE_NARRATION
};


// Regular dialog attribute
#define dRDA_NORMAL							0x00000000
#define dRDA_EXCLUSIVE						0x00000001	///< �ٸ� ���ַ� ���̾�αװ� ���� �� �ڸ��� �纸���� �ʴ´�
#define dRDA_HALFSIZE						0x00000002	///< �ٸ� ���ַ� ���̾�α׺��� ���� ������ ũ��� �Ʒ��� ���ĵȴ�
#define dRDA_NOT_ESC						0x00000004	///< ESCŰ�� ������ ���� �ʴ´�

// Entire focusing dialog attribute
#define dEFDA_NORMAL						0x00000000
#define dEFDA_BACKBOARD						0x00000001


// GUI Common Define
#define dDIALOG_CLEINT_EDGE_GAP				0

#define DBOGUI_DIALOG_TITLE_X				30
#define DBOGUI_DIALOG_TITLE_Y				2

#define DBOGUI_STACKNUM_WIDTH				32
#define DBOGUI_STACKNUM_HEIGHT				32
#define DBOGUI_STACKNUM_FONT				"detail"
#define DBOGUI_STACKNUM_FONTHEIGHT			75
#define DBOGUI_STACKNUM_FONTEFFECTMODE		TE_OUTLINE
#define DBOGUI_STACKNUM_FONTATTR			0
#define DBOGUI_STACKNUM_ALIGN				COMP_TEXT_LEFT | COMP_TEXT_DOWN

#define DBOGUI_SLOT_KEYNAME_FONT			"detail"
#define DBOGUI_SLOT_KEYNAME_FONTHEIGHT		75
#define DBOGUI_SLOT_KEYNAME_FONTEFFECTMODE	TE_OUTLINE
#define DBOGUI_SLOT_KEYNAME_FONTATTR		0
#define DBOGUI_SLOT_KEYNAME_ALIGN			COMP_TEXT_LEFT | COMP_TEXT_UP

#define DBOGUI_QUESTBALLOON_FONTHEIGHT		105

#define DBOGUI_ICON_SIZE					32
#define DBOGUI_ICON_SIZEDIFF				2

#define NTL_LINKED_DIALOG_GAP				5

#define dINPUTBOX_CARET_WIDTH				2
#define dINPUTBOX_CARET_HEIGHT				12


// Text Color
#define INFOCOLOR_0		RGB( 254, 254, 254 )
#define INFOCOLOR_1		RGB( 148, 191, 234 )
#define INFOCOLOR_2		RGB(  38, 158, 255 )
#define INFOCOLOR_3		RGB( 172, 250,  80 )
#define INFOCOLOR_4		RGB( 176, 254,  90 )
#define INFOCOLOR_5		RGB( 243, 106, 124 )
#define INFOCOLOR_6		RGB( 255, 168,  68 )
#define INFOCOLOR_7		RGB( 255, 218,  75 )
#define INFOCOLOR_8		RGB( 231, 121, 210 )
#define INFOCOLOR_9		RGB( 180, 180, 180 )
#define INFOCOLOR_12	RGB( 255, 219, 71 )

#define INFOCOLOR_LOBBY_FOC		RGB( 255, 255, 255 )
#define INFOCOLOR_LOBBY_DOWN	RGB( 193, 193, 193 )

#define RANKBATTLE_COLOR_YELLOW	RGB( 255, 254, 0 )
#define RANKBATTLE_COLOR_RED	RGB( 255, 0, 0 )
#define RANKBATTLE_COLOR_WHITE	RGB( 254, 254, 254 )
#define RANKBATTLE_COLOR_GRAY	RGB( 127, 127, 127 )
#define RANKBATTLE_COLOR_GREEN	RGB( 131, 255, 143 )

// button defalut color
#define NTL_BUTTON_UP_COLOR				RGB(255, 255, 255)
#define NTL_BUTTON_DOWN_COLOR			RGB(255, 210, 29)
#define NTL_BUTTON_FOCUS_COLOR			RGB(255, 255, 255)
#define NTL_BUTTON_DISABLE_COLOR		RGB(180, 180, 180)

// Party button color
#define NTL_PARTY_BUTTON_UP_COLOR			RGB(255, 210, 29)
#define NTL_PARTY_BUTTON_DOWN_COLOR			RGB(255, 210, 29)
#define NTL_PARTY_BUTTON_FOCUS_COLOR		RGB(255, 255, 255)
#define NTL_PARTY_BUTTON_DISABLE_COLOR		RGB(180, 180, 180)

// Team Color
#define NTL_RED_TEAM_COLOR		RGB( 255, 0, 0 )
#define NTL_BLUE_TEAM_COLOR		RGB( 0, 135, 255 )

#define NTL_BUTTON_CLICK_DIFFX			2 
#define NTL_BUTTON_CLICK_DIFFY			3 

// RPGauge 
#define RPGAUGE_TIME_SERVER		1.0f
#define RPGAUGE_TIME_EPSILON	0.0f

// LP Warning ramp rate
#define dLPWARNING_RATE			0.3f

// RP Bonus Apply KeyTime
#define SKILL_RPBONUS_KEYTIME	0.5f

// Item Duration warning
#define ITEM_DURATION_WARNING	0.3f

// Dialog�� Ŭ������ �� �ش翡 Link�� Dialog�� �ڽ��� �ֻ�ܿ� �׸��� ���� ��ũ��
#define CAPTURE_MOUSEDOWN_RAISE(eDialog, PosX, PosY)	\
	if( m_pThis->GetParent()->GetChildComponentReverseAt((RwInt32)PosX, (RwInt32)PosY) != m_pThis ) \
	return; \
	\
	CRectangle rect = m_pThis->GetScreenRect(); \
	\
	if( rect.PtInRect((RwInt32)PosX, (RwInt32)PosY)) \
	{ \
		RaiseLinked(); \
		GetDialogManager()->RaiseDialogbyUser(eDialog); \
	}


// Dialog�� Ŭ������ �� �ش� Dialog�� Link�ϰ� �ִ� Dialog�� �� Dialog�� Link�� Dialog����
// �ֻ�ܿ� �׸��� ���� ��ũ��
#define CAPTURE_MOUSEDOWN_RAISE_TOP_LINKED(TopLinkedDialog, PosX, PosY)	\
	if( m_pThis->GetParent()->GetChildComponentReverseAt((RwInt32)PosX, (RwInt32)PosY) != m_pThis ) \
		return; \
	\
	CRectangle rect = m_pThis->GetScreenRect(); \
	\
	if( rect.PtInRect((RwInt32)PosX, (RwInt32)PosY)) \
		GetDialogManager()->GetDialog(TopLinkedDialog)->RaiseLinked();


// MouseWheelMove Macro
#define CAPTURE_MOUSEWHEELMOVE_SCROLLBAR( bShow, pDialog, pComponent, pScrollBar, sDelta, pos )\
	if( !bShow ) return;\
	if( pDialog->GetParent()->GetChildComponentReverseAt( pos.x - pDialog->GetParent()->GetScreenRect().left, pos.y - pDialog->GetParent()->GetScreenRect().top ) != pDialog ) return;\
	if( pComponent->PosInRect( pos.x, pos.y ) != gui::CComponent::INRECT ) return;\
	\
	RwInt32 nValue = pScrollBar->GetValue();\
	RwInt32 nMaxValue = pScrollBar->GetMaxValue();\
	RwInt32 nDelta = nValue - sDelta / GUI_MOUSE_WHEEL_DELTA;\
	\
	if( nDelta < 0 ) nDelta = 0;\
	else if( nDelta > nMaxValue ) nDelta = nMaxValue;\
	pScrollBar->SetValue( nDelta );