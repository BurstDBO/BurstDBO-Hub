/****************************************************************************
 *
 * File			: DboDef.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 9. 28	
 * Abstract		: DBO standard definition.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __DBO_DEF_H___
#define __DBO_DEF_H___

#include "DboCompileOpt.h"
#include "NtlSLDef.h"
#include "DboTSCoreDefine.h"

#include "NtlSob.h"

//----------------------------------------------------------------------------
// client version

#define	CLIENT_LVER		0
#define CLIENT_RVER		50

//----------------------------------------------------------------------------
#define DEFAULT_SCREEN_WIDTH	1024	
#define DEFAULT_SCREEN_HEIGHT	768

#define EXTRA_SCREEN_WIDTH		1280		// cj�� ��û�� ���ؼ�.
#define EXTRA_SCREEN_HEIGHT		1024		// cj�� ��û�� ���ؼ�.

#define DEFAULT_CAMERA_NEAR		0.5f
#define DEFAULT_CAMERA_FAR		512.0f

//----------------------------------------------------------------------------
// serialize file

#define USEROPT_SERIALIZE_FOLDERNAME		".\\user"	

#define ACCOUNTOPT_SERIALIZE_FILENAME		"Account.opt"
#define SYSTEMENV_SERIALIZE_FILENAME		"SystemEnv.txt"
#define GAMEENV_SERIALIZE_FILENAME			"GameEnv.txt"

#define CHARACTERENV_SERIALIZE_FILENAME		"CharacterEnv.txt";
#define SCOUTEROPT_SERILIZE_FILENAME		"Scouter.opt";
#define QUESTOPT_SERIALIZE_FILENAME			"QuestIndicator.opt";


//----------------------------------------------------------------------------
// client control data

#define PICK_TERRAIN_LIMIT		300.0f
#define PICK_OBJECT_LIMIT		100.0f

#define MOUSE_DASH_LIMIT		0.5f

//-----------------------------------------------------------------------------
// stage name
#define SECURITY_STAGE_NAME			"Security"
#define WEB_LOGIN_STAGE_NAME		"WebLogIn"
#define LOGIN_STAGE_NAME			"LogIn"
#define CHARACTER_STAGE_NAME		"Character"
#define GAME_STAGE_NAME				"Game"
#define GAME_LOADING_STAGE_NAME		"GameLoading"

//-----------------------------------------------------------------------------
// client ��ü buffer length

#define MAX_VIRTUAL_SERVER_PACKET_SIZE		2048
#define MAX_MSG_BOX_STRING_LEN				512
#define CHAT_MSG_BUFFER_LEN					240		/** Ŭ���̾�Ʈ ��ü ��� */

//-----------------------------------------------------------------------------
// Message sender name
#define SENDERNAME_SYSTEM	L"System"
#define SENDERNAME_NOTICE	L"Notice"


//-----------------------------------------------------------------------------
// Error Report
#define ERROR_REPORT_FILE_NAME      "DboErrorInfo.xml"

//-----------------------------------------------------------------------------
// client data folder
#define HUMAN_GUI_TEXTURE_PATH		"gui\\human\\"
#define NAMEK_GUI_TEXTURE_PATH		"gui\\namek\\"
#define MAJIN_GUI_TEXTURE_PATH		"gui\\majin\\"

//-----------------------------------------------------------------------------
// Flash Notify Invalid index && file name
#define dINVALID_FLASH_NOTIFY_FILE_INDEX		0xff
#define dINVALID_FLASH_NOTIFY_FILE_TMQ			"fn000000.swf"
#define dINVALID_FLASH_NOTIFY_FILE_PLEASE_WAIT	"TMQ_PleaseWait.swf"
#define dINVALID_FLASH_NOTIFY_FILE_CLASS_CHANGE "ClassChange_Success.swf"
#define dINVALID_FLASH_NOTIFY_FILE_LEVEL_UP     "Level_Up.swf"
#define dINVALID_FLASH_NOTIFY_FILE_HOIPOIMIX_LEVEL_UP	"Mix_Level_Up.swf"

//-----------------------------------------------------------------------------
// Flash Notify Invalid index && file name
#define dDELAY_BEFORE_VISIBLE_MESSAGEBOX		7.f		// �޼��� �ڽ��� �߱������� �ִ� �����ð�
#define dREMAIN_FOR_SERVER_REPLY				60.f	// ���� ������ ��ٸ��� �ִ� �ð�

//-----------------------------------------------------------------------------
// guild contribution zenny
#define dGUILD_CONTRIBUTION_ZENNY_1000			1000
#define dGUILD_CONTRIBUTION_ZENNY_5000			5000
#define dGUILD_CONTRIBUTION_ZENNY_10000			10000
#define dGUILD_CONTRIBUTION_ZENNY_50000			50000
#define dGUILD_CONTRIBUTION_ZENNY_100000		100000

//-----------------------------------------------------------------------------
// Moive
#define dLOGO_MOVIE								"movie/logo.avi"
#define dOPENING_MOVIE							"movie/opening.avi"

//-----------------------------------------------------------------------------
// gui Message box
// msg type begin : ���⼭ ���� end ���� 

enum EMsgBoxWork
{	
	MBW_NONE,
	MBW_REGEN_MB_MAINWORLD_MOVE_TO_POPOSTONE,		/// ���� ���忡�� ������ ���� �̵�.
	MBW_REGEN_MB_TLQ_MOVE_TO_MAINWORLD,			/// TLQ���� ���ο��� ������ġ��.
	MBW_REGEN_MB_TLQ_RETRY,				/// TLQ���� ������ġ ��Ȱ.
	MBW_REGEN_MB_TMQ_MOVE_TO_MAINWORLD,			/// TMQ���� ���ο��� ������ġ��.
	MBW_REGEN_MB_PARTYDUNGEON_RETRY,			/// ��Ƽ �������� �ʱ���ġ�� ��Ȱ.
	MBW_REGEN_MB_DOJO_RETRY,				/// ������Ż������ �ʱ���ġ�� ��Ȱ.

	MBW_NET_CONNECT_FAIL,
	MBW_NET_DISCONNECT,
	MBW_GAME_EXIT,
	MBW_CAHR_SERVER_EXIT,

	MBW_LOGIN_CONNECT_FAIL,					///< Auth server connect fail...
	MBW_AUTHKEY_FAIL,						///< Auth server key ���� fail..
	MBW_CHARACTRE_CONNECT_FAIL,				///< Auth server connect fail...

	MBW_DEL_CHARACTER,						///< ĳ���͸� �����
	MBW_RECOVERY_CHARACTER,					///< ĳ���͸� �����Ѵ�

	MBW_POST_QUIT_MESSAGE,					///< Ŭ���̾�Ʈ�� �����Ѵ�

	MBW_ASK_TUTORIAL,						///< Ʃ�丮��� �������� �����
	MBW_WAIT_FOR_TUTORIAL,					///< Ʃ�丮�� �����

	MBW_ITEMDROP_CONFIRM,					///< ������ ��� Ȯ��

	MBW_PARTY_CREATE,						///< ��Ƽ �����
	MBW_PARTY_INVITE_REQ,					///< ��Ƽ �ʴ� ����
	MBW_PARTY_LEAVE,						///< ��Ƽ Ż��
	MBW_PARTY_RELEASE_CHARM,				///< ��Ƽ �� ���� ����

	MBW_BUY_WAREHOUSE,						///< â�� ������ �����ϰڽ��ϱ�
	MBW_BUY_COMMON_WAREHOUSE,				///< ���� â�� ������ �����ϰڽ��ϱ�

	MBW_FREEPVP_CHALLENGE,					///< free pvp ���� ��û

	MBW_BIND_POPOSTONE,						///< �������� ���ε�.

	MBW_QUEST_GIVEUP,

	MBW_USER_TRADE_REQ,

	MBW_GUILD_CREATE,						///< ��� ����
	MBW_GUILD_INVITE_REQ,					///< ��� �ʴ� ����
	MBW_GUILD_DISSOLVE,						///< ��� �ػ�
	MBW_GUILD_DISSOLVE_CANCLE,				///< ��� �ػ� ���
	MBW_GUILD_CHANGE_MASTER,				///< ����� �̾�
	MBW_GUILD_APPOINT_SECOND_MASTER,		///< �α���� �Ӹ�
	MBW_GUILD_DISAPPOINT_SECOND_MASTER,		///< �α���� �Ӹ� ����
	MBW_GUILD_KICK_OUT,						///< ��� �߹�
	MBW_GUILD_LEAVE,						///< ��� Ż��
	MBW_GUILD_ADD_FUNCTION,					///< ��� ��� �߰�
	MBW_GUILD_CONTRIBUTION,					///< ��� ���� ���
	MBW_GUILD_CHANGE_GUILD_NAME,			///< ��� �̸� ����

	MBW_TUTORIAL_ASK_END,					///< Ʃ�丮�� ����

	MBW_PRIVATESHOP_SALE_START,				///< ���λ��� �ǸŸ� �����ϰڽ��ϱ�?
	MBW_PRIVATESHOP_SALE_STOP,				///< ���λ��� �ǸŸ� �����ϰڽ��ϱ�?

	MBW_PRIVATESHOP_BUSINESS_WAIT,			///< ������ ���� ������ �� ������ ��ٷ� �ֽʽÿ�.
	MBW_PRIVATESHOP_BUSINESS_CONSENT,		///< �մ��� ������ ��û�ؿԽ��ϴ�. �����Ͻðڽ��ϱ�?
	MBW_PRIVATESHOP_BUSINESS_IMMEDIATE,		///< ���� �����Ͻðڽ��ϱ�?

	MBW_MAILSYSTEM_SEND_ASK,				///< ������ �����ðڽ��ϱ�?
	MBW_MAILSYSTEM_AWAY_ON,
	MBW_MAILSYSTEM_AWAY_OFF,
	MBW_MAILSYSTEM_RECEIVE_ASK,
	MBW_MAILSYSTEM_DELETE_ASK,
	MBW_MAILSYSTEM_RETURN_ASK,

	MBW_PORTAL_ADD_OK,

	MBW_FRIENDLIST_ADD_ASK,                 ///< ģ�� ����Ʈ�� ����� ����ϰڽ��ϱ�?
	MBW_BLACKLIST_ADD_ASK,                  ///< �� ����Ʈ�� ����� ����ϰڽ��ϱ�?
	MBW_FRIENDLIST_DEL_ASK,                 ///< ģ�� ����Ʈ���� �����Ͻðڽ��ϱ�?
	MBW_BLACKLIST_DEL_ASK,                  ///< �� ����Ʈ���� �����Ͻðڽ��ϱ�?

	MBW_GET_ON_BUS_ASK,		                ///< ������ ž���Ͻðڽ��ϱ�?
	MBW_GET_OFF_BUS_ASK,					///< �������� �����ðڽ��ϱ�?

	MBW_GET_CP_FROM_ITEM,					///< �������� CP�� ��ȯ�Ͻðڽ��ϱ�?
	MBW_ASK_CHANGE_CHANNEL,					///< ä���� �����Ͻðڽ��ϱ�?

	MBW_DO_NOT_ANYTHING,					///< �ƹ��͵� ���� �ʴ´�

	MBW_TELEPORT_CONFIRM_TIMEOUT,			///< DST_TELEPORT_COMMON_CONFIRM_MSG
	MBW_TELEPORT_COMMON_CONFIRM_YES,		///< DST_TELEPORT_COMMON_CONFIRM_YES_BTN
	MBW_TELEPORT_COMMON_CONFIRM_NO,			///< DST_TELEPORT_COMMON_CONFIRM_NO_BTN
	MBW_TELEPORT_FINAL_CONFIRM_TIMEOUT,		///< DST_TELEPORT_FINAL_CONFIRM_MSG
	MBW_TELEPORT_FINAL_CONFIRM_YES,		///< DST_TELEPORT_FINAL_CONFIRM_YES_BTN
	MBW_TELEPORT_FINAL_CONFIRM_NO,		///< DST_TELEPORT_FINAL_CONFIRM_NO_BTN


	MBW_PORTAL_CONFIRM,                     ///< ��Ż �̵��Ͻðڽ��ϱ�?

	MBW_TB_REQUEST_INDI_CANCEL,				///< õ������ ����ȸ ������ ��û�� ����Ͻðڽ��ϱ�?
	MBW_TB_REQUEST_TEAM_CANCEL,				///< õ������ ����ȸ ���� ��û�� ����Ͻðڽ��ϱ�?

	MBW_HOIPOIMIX_SET_FARE,					///< ȣ������ �ͽ� ���Ḧ �����ϼ���.

	MBW_VEHICLE_ASK_GET_OFF,				///< �����ðڽ��ϱ�?

	MBW_LOBBY_WAIT_GAME_SERVER_CONNECT,		///<����� %d��° ������Դϴ�

	MBW_DOJO_ASK_ESTABLISHMENT, 			//"������ �����Ͻðڽ��ϱ�? 500,000 ���ϰ� �ʿ��մϴ�(MsgBox : ������ �����Ϸ��� �� ��"
	MBW_DOJO_ASK_UPGRAGE_WITH_ZENNY,		//"������ ���׷��̵� �Ͻðڽ��ϱ�? Ȯ���� �����ø� %d ���ϰ� �Ҹ�˴ϴ�"
	MBW_DOJO_ASK_UPGRAGE_WITH_ZENNY_AND_HOIPOI,	//"������ ���׷��̵� �Ͻðڽ��ϱ�? Ȯ���� �����ø� %d ���Ͽ� ȣ�����̶� % ���� �Ҹ�˴ϴ�"
	MBW_DOJO_ADD_FUNCTION,					///< ���� ����� �߰��ϱ�ڽ��ϱ�?

	MBW_DOJO_SCRAMBLE_ACCEPT_CHALLENGE_OK,		// %s ������ ��Ż�� ��û�� �����Ͻðڽ��ϱ�[br][br]�źθ� �����Ͻø� ��������  %d ���ϰ� �Ҹ�˴ϴ� (������ ������ ��)
	MBW_DOJO_SCRAMBLE_ACCEPT_CHALLENGE_CANCEL,	// %s ������ ��Ż�� ��û�� �����Ͻðڽ��ϱ�[br][br]�źθ� �����Ͻø� ��������  %d ���ϰ� �Ҹ�˴ϴ� (�źθ� ������ ��) 
	MBW_DOJO_SCRAMBLE_ASK_CHALLENGE_OK,		// ���� ��Ż���� ��û�Ͻðڽ��ϱ�[br]���� ��Ż�� ��û�� %d ���ϰ� �ʿ��մϴ� (��û�� ������ ��)
	MBW_DOJO_SCRAMBLE_ASK_TELEPORT_OK,		// ��Ż���� �������� ���� ������ �����̵� �Ͻðڽ��ϱ� (�̵��� ������ ��)

	MBW_COMMERCIAL_MB_UPDATE_TERM_LIMETED_ITEM,	// ���Ⱓ ����� �������� �Ⱓ�� �����ϱ�.

	MBW_DOJO_ADD_TENKAI_SEED,			// õ������ ����ȸ �õ� ������ �̸��� �Է��� �ֽʽÿ�(Msgbox : ������ ���� �������� õ������ ����ȸ �õ� �����ڸ� ������ ��)

	MBW_DOGI_ASK_APPLY_CHANGE,			// ������ ���� ������ �Ϸ��Ͻðڽ��ϱ�?(Msgbox : ���� ������ �������� ��� ��)
	MBW_DOJO_DOGI_ASK_APPLY_CHANGE,			// ������ ���� ������ �Ϸ��Ͻðڽ��ϱ�?(Msgbox : ���� ������ �������� ��� ��)
	MBW_HOIPOIMIX_SKILL_SET_MSGBOX,			// [MSGBOX]�� ���� ����� ���ðڽ��ϰ�?[br]%s �������
	MBW_HOIPOIMIX_SKILL_RESET_MSGBOX,		// [MSGBOX]�� ���� ����� �����Ͻðڽ��ϱ�?[br]%s �������[br]���� ����ġ�� ����������..
	MBW_LOBBY_ASK_RENAME,				// ���ȭ ���������� ĳ���� �̸� ������ ��
	MBW_FORCED_LOBBY_ASK_RENAME,			// ���������� �̸��� ����Ǿ� ������ ĳ������ �̸��� ������ ��

	MBW_COMMERCIAL_MB_ITEM_TERM_EXTENTION,		// �Ⱓ ����/������ ���� ���� MSG �ڽ�
	MBW_COMMERCIAL_MB_CAPSULEKIT_TERM_EXTENTION,	// ĸ��ŰƮ, �Ⱓ/������ ���� ���� MSG �ڽ� - �Ⱓ ���� BTN
	MBW_COMMERCIAL_MB_CAPSULEKIT_BUY,		// ĸ��ŰƮ, �Ⱓ/������ ���� ���� MSG �ڽ� - ������ ���� BTN
	MBW_COMMERCIAL_MB_TERM_OR_BUY_SELECT_CONFIRM,	// �Ⱓ����, ������ ���� ���� MSG �ڽ� - �Ⱓ ���� BTN
	MBW_COMMERCIAL_MB_CAPSULEKIT_ITEM_TERM_EXTENTION,	// ĸ��ŰƮ �Ⱓ ����/������ ���� ���� MSG �ڽ� - �Ⱓ ���� BTN
	MBW_COMMERCIAL_MB_CAPSULEKIT_MOVE,		// ĸ��ŰƮ �Ⱓ ����/������ ���� ���� MSG �ڽ� - ������ �̵� BTN
	MBW_COMMERCIAL_MB_TERM_EXTENTION,		// �Ⱓ���� Ȯ�� MSG �ڽ� - �Ⱓ ���� BTN

	MBW_COMMERCIAL_MB_DIRECT_BUY,			// �Ⱓ�� ������ �ٷ� ���� Ȯ��,   DST_COMMERCIAL_MB_DIRECT_BUY_MSG
	MBW_COMMERCIAL_MB_ITEM_BUY_CONFIRM,		// �Ⱓ�� ������ ���� Ȯ��, DST_COMMERCIAL_MB_ITEM_BUY_CONFIRM_MSG, DST_COMMERCIAL_MB_ITEM_MOVE_CONFIRM_MSG

	MBW_COMMERCIAL_MB_DUR_ITEM_GET_FROM_YARDRAT, // �ߵ巡Ʈ�κ��� �Ⱓ�� ������ get start point DST_COMMERCIAL_MB_ITEM_TAKE_CONFIRM_MSG
};

// msgtype end

enum EMsgBoxTypeFlag
{
	MBTF_NONE			= 0x00,
	MBTF_OK				= 0x01,
	MBTF_CANCEL			= 0x02,
	MBTF_INPUT			= 0x04,
	MBTF_CUSTOM			= 0x08,
};

enum EMsgBoxResult
{
	MBR_OPENCANCELED	= -1,				/// �޽����ڽ� ������ü�� ���. �޽��� �ڽ��� �ߺ��� ���.
	MBR_CANCEL			= 0,				/// ���.
	MBR_OK				= 1,				/// Ȯ��, ����,	
};

struct sMsgBoxCustomBtn
{
	sMsgBoxCustomBtn(VOID)
	{
		Init();
	}

	VOID sMsgBoxCustomBtn::Init(VOID)
	{
		uiStringID = INVALID_DWORD;
		uiWorkID = MBW_NONE;
	}

	RwUInt32 uiStringID;
	RwUInt32 uiWorkID;
};

//-----------------------------------------------------------------------------

///< avooo : ǥ�õǴ� �켱������ ���� �����Ͽ���.
///< peessi : Display String Define�� ���ǵ� ���ڿ��� ������ ��ġ�ؾ���.
enum EIconPopupWork	
{
	PMW_USE = 0,						    ///< ����ϱ�
	PMW_OPEN,								///< (����)����
	PMW_EQUIP,								///< �����ϱ�
	PMW_CANCEL_EQUIP,						///< ��������
	PMW_VIEW,								///< ����
	PMW_PICKUP,								///< ����
	PMW_STOP_USE,							///< �������
	PMW_PULLOUT,							///< ������
	PMW_SELL,								///< �ȱ�
	PMW_DIVIDE,								///< ������
	PMW_CLEAR,								///< ����
	PMW_DELETE,								///< ������
	PMW_PARTY_CREATE,						///< ��Ƽ �����
	PMW_PARTY_INVITE,						///< ��Ƽ �ʴ�
	PMW_PARTY_LEADER_CHANGE,				///< ��Ƽ�� ����
	PMW_PARTY_KICK_OUT,						///< ��Ƽ ����
	PMW_PARTY_LEAVE,						///< ��Ƽ Ż��
	PMW_PVP_REQUEST_FIGHT,					///< ��� ��û
	PMW_USER_TRADE,							///< ���� Ʈ���̵�
	PMW_GUILD_INVITE,						///< ��� �ʴ�
	PMW_GUILD_CHANGE_MASTER,				///< ����� �̾�
	PMW_GUILD_APPOINT_SECOND_MASTER,		///< �α���� �Ӹ�
	PMW_GUILD_DISAPPOINT_SECOND_MASTER,		///< �α���� �Ӹ� ����
	PMW_GUILD_KICK_OUT,						///< ��� �߹�
	PMW_GUILD_POST,							///< ���� ������
	PMW_FRIEND_ADD,							///< ģ�� �߰�
	PMW_FOLLOW,								///< ���� ����
	PMW_CANCEL,								///< ���
	PMW_SET_SHARETARGET_1,					// 1�� ����Ÿ�� ����
	PMW_SET_SHARETARGET_2,					// 2�� ����Ÿ�� ����
	PMW_SET_SHARETARGET_3,					// 3�� ����Ÿ�� ����
	PMW_SET_SHARETARGET_4,					// 4�� ����Ÿ�� ����
	PMW_SET_SHARETARGET_5,					// 5�� ����Ÿ�� ����
	PMW_UNSET_SHARETARGET_1,				// 1�� ����Ÿ�� ����
	PMW_UNSET_SHARETARGET_2,				// 2�� ����Ÿ�� ����
	PMW_UNSET_SHARETARGET_3,				// 3�� ����Ÿ�� ����
	PMW_UNSET_SHARETARGET_4,				// 4�� ����Ÿ�� ����
	PMW_UNSET_SHARETARGET_5,				// 5�� ����Ÿ�� ����
	PMW_PARTY_MENU_SWITCH_MEMBER,			///< ��Ƽ �ɹ�â ����ġ
	PMW_PARTY_MENU_SWITCH_MEMBER_BUFF,		///< ��Ƽ �ɹ�â ���� ����ġ
	PMW_PARTY_DUNGEON_INIT,					///< ���� �ʱ�ȭ
	PMW_PARTY_DUNGEON_NORMAL,				///< ���� ���̵� ����
	PMW_PARTY_DUNGEON_HARD,					///< ���� ���̵� �����
	PMW_PARTY_DIVIDE_PICKUP_PERSON,			///< �ݴ� ��� ȹ��
	PMW_PARTY_DIVIDE_EQUAL,					///< �Ȱ��� ������
	PMW_PARTY_DIVIDE_ORDER,					///< �����Ƿ� �й�
	PMW_PARTY_GRADE_ITEM,					///< ��޺� �����Ƿ� �й�
	PMW_PARTY_USE_INVEN,					///< ��Ƽ �κ��丮 ���

	NUM_PMW
};

enum EPlace
{
	PLACE_NONE = 0,
	PLACE_EQUIP,
	PLACE_BAG,
	PLACE_SCOUTER,
	PLACE_SCOUTER_SLOT,
	PLACE_BAGSLOT,
	PLACE_POPUPMENU,
	PLACE_QUICKSLOT,
	PLACE_SKILL,
	PLACE_BUFF,
	PLACE_NPCSHOP,
	PLACE_TRADECART,	
	PLACE_QUESTBAG,
	PLACE_ITEMUPGRADE,
	PLACE_WAREHOUSE,
	PLACE_PRIVATESHOP,				///< ���λ���
	PLACE_PRIVATESHOP_TRADEBOX,		///< ���λ��� ���� (���� ����)
	PLACE_PARTYCHARM,
	PLACE_GUILD_WAREHOUSE,
	PLACE_DOJO_UPRAGE,
	PLACE_DOGI,

	PLACE_SUB_SKILLRQ,
	PLACE_SUB_SKILLNOTLEARN,
	PLACE_SUB_HTB,
	PLACE_SUB_QUICKSLOTITEM,
	PLACE_SUB_QUICKSLOTSKILL,
	PLACE_SUB_TARGETUI,
	PLACE_SUB_PARTY_MENU_MEMBER,
	PLACE_SUB_PARTY_MENU_DIVIDE_ZENNY,
	PLACE_SUB_PARTY_MENU_DIVIDE_ITEM,
	PLACE_SUB_PARTY_MENU_SWITCH,
	PLACE_SUB_PARTY_MENU_DUNGEON,
	PLACE_SUB_PARTYMEMBERUI,
	PLACE_SUB_GUILD_DIALOG,
	PLACE_SUB_MAILSYSTEM_ITEM,
	PLACE_SUB_HOIPOIMIXCREATE,
		
	// Zenny
	PLACE_ZENNY_FIRST,

	PLACE_SUB_BAG_ZENNY = PLACE_ZENNY_FIRST,
	PLACE_SUB_PARTYCHARM_ZENNY,
	PLACE_SUB_PARTYINVEN_ZENNY,
	PLACE_SUB_WAREHOUSE_ZENNY,
	PLACE_SUB_GUILD_WAREHOUSE_ZENNY,
	PLACE_SUB_TRADECART_ZENNY,
	PLACE_SUB_MAILSYSTEM_ZENNY,

	PLACE_ZENNY_LAST = PLACE_SUB_MAILSYSTEM_ZENNY,
};


enum ELogInStageState
{
	LOGIN_STATE_NONE,
	LOGIN_STATE_LOGO,
	LOGIN_STATE_SERVER_CONNECT,	
	LOGIN_STATE_SERVER_CONNECT_FAIL,	
	LOGIN_STATE_IDLE,
	LOGIN_STATE_LOGINREQ,
	LOGIN_STATE_CHAR_SERVER_CONNECT,		// character server connecting
	LOGIN_STATE_CHAR_SERVER_LOGIN,			// character server login	
	LOGIN_STATE_EXIT,						// character server login	
	LOGIN_STATE_END
};

enum ECharacterStageState
{
	CHAR_STATE_NONE,

	CHAR_STATE_BEGIN,
	
	CHAR_STATE_SERVER_INFORMAION,		// server information ���� ������ ��.
	CHAR_STATE_SERVER_ENTER,
	CHAR_STATE_SERVER_IDLE,
	CHAR_STATE_SERVER_CHANGE,
	CHAR_STATE_SERVER_EXIT,

	CHAR_STATE_MAKE_ENTER,
	CHAR_STATE_MAKE_IDLE,
	CHAR_STATE_MAKE_EXIT,
	CHAR_STATE_MAKE_REQUEST,

	CHAR_STATE_SELECT_INFOMATION,		// Channel Infomation ���� ������ ��
	CHAR_STATE_SELECT_INFOMATION_FROM_SERVER_LIST,		// ���� ����Ʈ ȭ�鿡�� ä�� ���� ��û��
	CHAR_STATE_SELECT_ENTER,
	CHAR_STATE_SELECT_IDLE,
	CHAR_STATE_SELECT_DEL_CHAR,
	CHAR_STATE_SELECT_RECOVERY_CHAR,
	CHAR_STATE_SELECT_RENAME_REQ,
	CHAR_STATE_SELECT_EXIT,

	CHAR_STATE_RETURN_LOGIN,

	CHAR_STATE_GAME_SERVER_WAIT_CHECK_REQ,
	CHAR_STATE_CHARACTER_SELECT_REQ,
	CHAR_STATE_SUCCESS_ENTER_GAME,
	CHAR_STATE_WAITING_GAME_SERVER_RESPONSE,
	CHAR_STATE_FAIL_ENTER,

	CHAR_STATE_IMMEDIATLY_RETURN_LOGIN_ENTER,
	CHAR_STATE_IMMEDIATLY_RETURN_LOGIN_IDLE,
	CHAR_STATE_IMMEDIATLY_RETURN_LOGIN_EXIT,

	CHAR_STATE_READY_ENTER_TUTORIAL,
	CHAR_STATE_WAIT_FOR_TUTORIAL,
	CHAR_STATE_WAIT_CANCEL,

	CHAR_STATE_WAIT_GAME_SERVER_CONNECT,
	CHAR_STATE_CANCEL_WAIT_GAME_SERVER_CONNECT,

	CHAR_STATE_END,
	CHAR_MAX_STATE
};

enum EGameStageState
{
	GAME_STATE_NONE,
	GAME_STATE_IDLE,
	GAME_STATE_CHAR_SERVER_CONNECT,
	GAME_STATE_CHAR_SERVER_LOGIN,			// character server login	
    GAME_STATE_CHAR_EXIT,                   // ���ӿ��� ���� ���Ḧ Ŭ���Ͽ� ĳ���� ����ȭ������ ������
	GAME_STATE_END
};

struct sDboItemDeleteInfo
{
	RwUInt32		hSerial;
	EPlace			ePlace;
	RwInt32			nPlaceIdx;
	RwInt32			nSlotIdx;	
	RwBool			bRemoteSell;
};

/**
* \brief UNION - ���� ����
*/
struct sMsgBoxData
{
	union
	{
		sDboItemDeleteInfo		sItemDeleteInfo;	
		
		RwUInt32				uiTblIdx;		

		const WCHAR*			pwcText;

		RwUInt32				uiParam;

		struct  
		{
			SERIAL_HANDLE		hHandle;
			RwUInt8				byIndex;
		};

		struct
		{
			sTS_KEY				sTSKey;	
			RwUInt32			uiQuestTitle;
		};

		VOID*					pData;

		RwUInt8					ucData[256];			// Reserved;
	};

	SERIAL_HANDLE				hExtendHandle;				///< Input Box���� TEXT�� SerialHandle�� ���ÿ� ���� ��� ����ڰ� ����/��� �Ѵ�.
};


struct sMINIMAPINFO
{
	RwInt32			iType;
	std::wstring	wcsString;
};

typedef std::list<sMINIMAPINFO>					MINIMAPINFO_LIST;
typedef std::list<sMINIMAPINFO>::iterator		MINIMAPINFO_ITER;


struct sQUEST_SEARCH_INFO
{
	std::wstring*	pwstrNPCName;
	std::list<std::wstring>* pListQuestTitle;
};

typedef std::list<sQUEST_SEARCH_INFO>				QUEST_SEARCH_LIST;
typedef std::list<sQUEST_SEARCH_INFO>::iterator		QUEST_SEARCH_ITER;


enum eMIniMapInfoType
{
	MMIT_NPC,
	MMIT_MOB,
	MMIT_QUEST,
	MMIT_PARTY,
	MMIT_LANDMARK,
	MMIT_BIND_POS,
	MMIT_NEXTQUEST_POSITION,

	NUM_MMIT
};

struct sDetailTime
{
	RwUInt32			uiYear;
	RwUInt8				byMonth;
	RwUInt8				byDay;
	RwUInt8				byHour;
	RwUInt8				byMinute;
	RwUInt8				bySecond;

	std::wstring		strDay;			///< ����

	RwUInt8				byDay_of_Year;	///< �� ���� �� ��° ���ΰ�
};

struct sITEM_PROFILE;
struct sITEM_TBLDAT;

struct sPartyInvenDisplay
{
	sITEM_TBLDAT*		pITEM_TBLDAT;
	sITEM_PROFILE*		pITEM_PROFILE;
	RwUInt8				byCompetitor;
	RwUInt8				byScore;
};

struct sWorldPickInfo_for_Cursor
{
	RwBool				bWorldPick;
	CNtlSob*			pSobObj;
};

#endif
