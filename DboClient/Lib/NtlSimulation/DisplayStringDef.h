#ifndef __DISPLAY_STRING_DEF_H__
#define __DISPLAY_STRING_DEF_H__

enum EDispStingType
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Client Result Text _ ������ ����� ǥ���ϱ� ���� �ؽ�Ʈ. 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Global Message
	DST_INPUT_YOUR_ID,				// ���̵� �Է��Ͻʽÿ�
	DST_INPUT_YOUR_PASSWORD,		// ��й�ȣ�� �Է��Ͻʽÿ�
	DST_SERVER_CONNECTING,			// ���� ������ ������ ���Դϴ�.
	DST_ACCOUNT_SERVER_CONNECT_FAIL,// ������������ ����
	DST_CHAR_SERVER_CONNECT_FAIL,	// ĳ���ͼ��� ���� ���� 
	DST_GAME_SERVER_CONNECT_FAIL,	// ���Ӽ��� ���� ���� 
	DST_CHAT_SERVER_CONNECT_FAIL,	// ä�ü��� ���� ����
	DST_CHAT_SERVER_TITLE,          // ä�� ���� �˸� (Ÿ��Ʋ)
	DST_CHAT_SERVER_DISCONNECT,     // ä�ü��� ������ ������ϴ�.
	DST_CHAT_SERVER_RECONNECT,      // ä�ü����� �ٽ� ������ �ƽ��ϴ�.
	DST_SERVER_DISCONNECT,			// �������� ���� 
	DST_ACCOUNT_CREATE_SUCCESS,		// �������� ����

	DST_CHECKING_GAME_SERVER,		// ���� ������ �������Դϴ�
	DST_CHECKING_COMMUNITY_SERVER,	// Ŀ�´�Ƽ ������ �������Դϴ�

	DST_REGEN_PLAYER_MAINWORLD,		//"ĳ���Ͱ� ���� �߽��ϴ�.[br][br][font size = "9" color = "ffdb47"]�̵��ϱ� : ������ ���� ���� �̵��մϴ�."
	DST_REGEN_PLAYER_TLQ,			//"ĳ���Ͱ� ���� �߽��ϴ�.[br][br][font size = "9" color = "ffdb47"]���ư��� : ������ ����� ���ư��ϴ�.[br]�絵�� : ���� ��ġ���� �ٽ� �����մϴ�.[/font][br]"
	DST_REGEN_PLAYER_TMQ,			//"ĳ���Ͱ� ���� �߽��ϴ�.[br][br][font size = "9" color = "ffdb47"]���ư��� : ������ ����� ���ư��ϴ�."
	DST_REGEN_PLAYER_PARTY_DUNGEON,	//"ĳ���Ͱ� ���� �߽��ϴ�.[br][br][font size = "9" color = "ffdb47"]�絵�� : ������ �ʱ� ��ġ�� �̵��մϴ�"
	DST_REGEN_PLAYER_DOJO,			//"ĳ���Ͱ� ���� �߽��ϴ�.[br][br][font size = "9" color = "ffdb47"]�絵�� : ������ �ʱ� ��ġ�� �̵��մϴ�."

	DST_GAME_EXIT,					// ������ �����Ͻðڽ��ϱ�
	DST_CHAR_SERVER_EXIT,			// ĳ���� ����ȭ������ �����ðڽ��ϱ�?
	DST_PLEASE_RETRY,				// �����͸� ó�����̴� ��� �ڿ� �ٽ� �õ��� �ֽʽÿ�

	// PrivateShop Message
	DST_PRIVATESHOP_MSG_SALE_ITEM,			// �ȷ��� ��ǰ�� �����ϴ�. ��ǰ�� ����ؾ� �մϴ�.
	DST_PRIVATESHOP_MSG_SALE_OPEN,			// ���� ������ ���� ������ �ǸŸ� �����մϴ�.
	DST_PRIVATESHOP_MSG_SALE_CLOSE,			// ���� ������ �ݰ� ������ �ǸŸ� �����մϴ�.
	DST_PRIVATESHOP_MSG_ITEM_NOT_REG,		// ���� ������ ����� �� ���� ������ �Դϴ�.

	DST_PRIVATESHOP_MSG_SHOPNAME_SLANGDER,	// ���� �̸��� �弳�� ���ԵǾ� �ֽ��ϴ�. �ٽ� �ۼ��Ͽ� �ֽʽÿ�.
	DST_PRIVATESHOP_MSG_NOTICE_SLANGDER,	// ���� ���뿡 �弳�� ���ԵǾ� �ֽ��ϴ�. �ٽ� �ۼ��Ͽ� �ֽʽÿ�.
	DST_PRIVATESHOP_MSG_NOTICE_BUFFEROVER,  // ���� ������ �ʰ��Ͽ����ϴ�.
	DST_PRIVATESHOP_MSG_BUY_PROCESS,		// ���콺 ������ Ŭ������ �������� īƮ�� ����� �� �ֽ��ϴ�.

	// MailSystem Message
	DST_MAILSYSTEM_MSG_SEND_SUCCEED,			// %s�Կ��� ������ ���½��ϴ�.
	DST_MAILSYSTEM_MSG_ATTACH_ZENNY,			// �۱� �� û�� ������ �ݾ��� %u ���� ���� �Դϴ�.
	DST_MAILSYSTEM_MSG_PLEASE_TARGETNAME,		// �޴� ����� �Է��� �ּ���.
	DST_MAILSYSTEM_MSG_PLEASE_MAILCONTENT,		// ������ �Է��� �ּ���.
	DST_MAILSYSTEM_MSG_MAIL_NOT_LOCK,			// û���� �ݾ��� �ִ� ������ ��� ������ �� �����ϴ�.
	DST_MAILSYSTEM_MSG_RECEIVE_ITEM,			// %s �������� �����߽��ϴ�.
	DST_MAILSYSTEM_MSG_RECEIVE_ZENNY,			// %u ���ϸ� �����߽��ϴ�.
	DST_MAILSYSTEM_MSG_RECEIVE_ZENNY_REQ,		// %u ���ϸ� %s�Կ��� �۱��߽��ϴ�.
	DST_MAILSYSTEM_MSG_RECEIVE_ACCEPT_MAIL,		// %s�Կ��� ���� Ȯ�� ������ ���½��ϴ�.
	DST_MAILSYSTEM_MSG_SEND_BASIC,				// �����̿�� %u ���ϸ� �����ϰ� ������ �����ðڽ��ϱ�
	DST_MAILSYSTEM_MSG_SEND_ITEM,				// �����̿�� %u ���ϸ� �����ϰ� ������ �����ðڽ��ϱ�?\n(%s �������� ���� �����ϴ�)
	DST_MAILSYSTEM_MSG_SEND_ZENNY,				// �����̿�� %u ���ϸ� �����ϰ� ������ �����ðڽ��ϱ�?\n(%u ���ϸ� ���� �����ϴ�)
	DST_MAILSYSTEM_MSG_SEND_ITEM_ZENNY,			// �����̿�� %u ���ϸ� �����ϰ� ������ �����ðڽ��ϱ�?\n(%s �����۰� %u ���ϸ� ���� �����ϴ�)
	DST_MAILSYSTEM_MSG_SEND_ITEM_ZENNY_REQ,		// �����̿�� %u ���ϸ� �����ϰ� ������ �����ðڽ��ϱ�?\n(%s �������� ������ %u ���ϸ� û���մϴ�)
	DST_MAILSYSTEM_MSG_SEND_ZENNY_REQ,			// �����̿�� %u ���ϸ� �����ϰ� ������ �����ðڽ��ϱ�?\n(%u ���ϸ� û���մϴ�)
	DST_MAILSYSTEM_MSG_AWAY_ON,					// ���������� �����ϰ� ������ ���� ������ �������� �ʰڽ��ϱ�?
	DST_MAILSYSTEM_MSG_AWAY_OFF,				// ������ ������ �����ϰ� ������ �����ϰڽ��ϱ�?
	DST_MAILSYSTEM_MSG_ATTACH_ITEM_NOT,			// ÷�ι�ǰ���� ��� �� �� ���� ������ �Դϴ�.

	DST_MAILSYSTEM_MSG_RECEIVE_ITEM_ACCEPT,		// %s �������� �����ðڽ��ϱ�?
	DST_MAILSYSTEM_MSG_RECEIVE_ZENNY_ACCEPT,	// %u ���ϸ� �����ðڽ��ϱ�?
	DST_MAILSYSTEM_MSG_RECEIVE_ITEM_ZENNY_ACCEPT,		// %u���Ͽ� %s �������� �����ðڽ��ϱ�?
	DST_MAILSYSTEM_MSG_RECEIVE_ITEM_ZENNY_REQ_ACCEPT,	// ���Ͽ� ÷�ε� %s �������� �ޱ� ���ؼ� ������ û���� %u ���ϸ� �����Ͻðڽ��ϱ�?
	DST_MAILSYSTEM_MSG_RECEIVE_ZENNY_REQ_ACCEPT,		// %u ���ϸ� �����Ͻðڽ��ϱ�?
	DST_MAILSYSTEM_MSG_DELETE,					// ������ �����Ͻðڽ��ϱ�?
	DST_MAILSYSTEM_MSG_RETURN,					// ������ �ݼ��Ͻðڽ��ϱ�? 

	DST_MAILSYSTEM_MSG_SELECT_REQ_OR_SEND,		// ���� �۱� �Ǵ� û���� �����ؾ� �մϴ�.

	DST_MAILSYSTEM_MSG_RETRUN_MAIL,				// %s���� ������ �ź��ϰ� �ݼ۽�Ų �����Դϴ�.
	DST_MAILSYSTEM_MSG_REPLY_MAIL_ITEM,			// %s���� %s �������� �����߽��ϴ�.
	DST_MAILSYSTEM_MSG_REPLY_MAIL_ZENNY,		// %s���� %u ���ϸ� �����߽��ϴ�.
	DST_MAILSYSTEM_MSG_REPLY_MAIL_ITEM_ZENNY,	// %s���� %s �����۰� %u ���ϸ� �����߽��ϴ�.
	DST_MAILSYSTEM_MSG_REPLY_MAIL_ITEM_ZENNY_REQ,// %s���� %s �������� �����ϰ� û���� %u ���ϸ� �۱��߽��ϴ�.
	DST_MAILSYSTEM_MSG_REPLY_MAIL_ZENNY_REQ,	// %s���� û���� %u ���ϸ� �۱��߽��ϴ�.

	DST_MAILSYSTEM_MSG_MAIL_CONTENT_SLANGDER,	// ���� ������ �弳�� ���ԵǾ� �ֽ��ϴ�. �ٽ� �ۼ��Ͽ� �ֽʽÿ�.
	DST_MAILSYSTEM_MSG_MAIL_CONTENT_BUFFEROVER,	// ���� ������ �ʰ��Ͽ����ϴ�.

	DST_MAILSYSTEM_MSG_NOTFIND_SELECTED_MAIL,	// ������ ������ �����ϴ�.
	DST_MAILSYSTEM_TOOLTIP_DELETE_BUTTON,		// ������ ���ϵ��� �����մϴ�.

	// tutorial message
	DST_TUTORIAL_ASK_BEGIN,					// Ʃ�丮���� �����Ͻðڽ��ϱ�?(MsgBox, Ʃ�丮�� ���� �����)
	DST_TUTORIAL_WAITING_NUMBER,			// Ʃ�丮�� ������� %d�� ���ҽ��ϴ�(MsgBox, Ʃ�丮�� ���� �����)
	DST_TUTORIAL_ASK_END,					// Ʃ�丮���� �����Ͻðڽ��ϱ�?(MsbBox, Ʃ�丮�� ������ Ʃ�丮���� �ߴ����� �����)
	DST_TUTORIAL_CAN_NOT_WORK,				// ������ �� �� �����ϴ�(Ʃ�丮�� �� ������ Lock ������ ������ �Ϸ��� �� ��)

	// TMQ message
	DST_TMQ_BALLOON_LOTTERY_WAITING,		// Ÿ�Ӹӽ� ����Ʈ ��÷ �����(TMQ Side View)
	DST_TMQ_BALLOON_HOLDING_A_LOTTERY,		// Ÿ�Ӹӽ� ����Ʈ ��÷���Դϴ�(TMQ Side View)
	DST_TMQ_BALLOON_PLEASE_WAIT,			// ��ø� ��ٷ� �ֽʽÿ�(TMQ Side View)
	DST_TMQ_BALLOON_ASK_RETRY_LOTTERY,		// ���� Ÿ�Ӹӽ� ����Ʈ�� �����Ͻðڽ��ϱ�?(TMQ Side View)
	DST_TMQ_BALLOON_RETRY_LOTTERY,			// Ÿ�Ӹӽ� ����Ʈ ���û(TMQ Side View)
	DST_TMQ_BALLOON_READY_FOR_TMQ,			// Ÿ�Ӹӽ� ����Ʈ �غ� ���ֽʽÿ�(TMQ Side View)
	DST_TMQ_BALLOON_CONGRATULATION,			// �����մϴ�(TMQ Side View)
	DST_TMQ_BALLOON_SUCCESS_LOTTERY,		// ��û�Ͻ� Ÿ�Ӹӽ� ����Ʈ�� ��÷�Ǿ����ϴ�(TMQ Side View)
	DST_TMQ_BALLOON_I_AM_SORRY,				// �˼��մϴ�(TMQ Side View)
	DST_TMQ_BALLOON_FAIL_LOTTERY,			// ��û�Ͻ� Ÿ�Ӹӽ� ����Ʈ�� ��÷���� �ʾҽ��ϴ�(TMQ Side View)
	DST_TMQ_BALLOON_CAN_TELEPORT,			// Ÿ�Ӹӽ� ����Ʈ ���� %d�� ������ ����� �κ�Ʈ ��ó�� �� �ѹ� �ڷ���Ʈ �� �� �ֽ��ϴ�(TMQ Side View)

	DST_TMQ_BALLOON_CANNOT_TELEPORT,		// Ÿ�Ӹӽ� ����Ʈ ���� �����Դϴ�. �ڷ���Ʈ �Ͻ� �� �����ϴ�(TMQ Side View)
	DST_TMQ_BALLOON_LEAVE_MEMVER,			// %s���� �����Ͽ����ϴ�(TMQ �����, ������ �� �� ������)(TMQ Side View)

	DST_TMQ_STATUS_MUST_SELECT_ADDITION_REWARD, // ���ú����� ���� �ʾҽ��ϴ�(TMQ ������ ���ú����� �ִµ��� ���� �ʰ� Ȯ�ι�ư�� ��������)
	DST_TMQ_STATUS_CAN_SEE_SENARIO,			 // TMQ �ó������� �� �� �ֽ��ϴ�(TMQ �ó����� ��ư ����)
	DST_TMQ_STATUS_CAN_SEE_STAGE_INFO,		 // TMQ �������� ������ �� �� �ֽ��ϴ�(TMQ �������� ��ư ����)
	DST_TMQ_STATUS_EXPLAIN_POINT,			 // Point �������� 100%���� �Ǹ� TMQ �������� �ٲ�ϴ�(TMQ ������ ����)
	DST_TMQ_STATUS_EXPLAIN_COUPON,			 // TMQ ������ �����Ҹ� �ٹٿ��� �������� ������ ���� �� �ֽ��ϴ�(TMQ ���� ����)
	DST_TMQ_STATUS_EXPLAIN_INDICATOR,		 // TMQ���� ���� �������� ������ �� �� �ֽ��ϴ�(TMQ ����Ʈ �ε�����Ʈ ��ư ����)

	DST_TMQ_RESULT_NARRATION,				// TMQ�� Ŭ�����߽��ϴ�(TMQ ����â���� �����̼�â�� ���)

	// guild message
	DST_GUILD_ENTRUST_MASTER,				// �ְ����� ��� ������ %s�Կ��� �ñ�ðڽ��ϱ�?(MsgBox, ����� �ѱ��� ����)
	DST_GUILD_APPOINT_SECOND_MASTER,		// %s���� ������ ������� �Ӹ��Ͻðڽ��ϱ�?(MsgBox, �α���� �Ӹ� ����)
	DST_GUILD_DISMISS_SECOND_MASTER_REQ,	// %s���� ��� ������ ��Ż�Ͻðڽ��ϱ�?(MsgBox, �α���� �������� ����)
	DST_GUILD_KICK_OUT,						// %s���� ���Ŀ��� �߹��Ͻðڽ��ϱ�?(MsgBox, ���� �߹� ����)
	DST_GUILD_LEAVE_ASK,					// ��带 Ż���Ͻðڽ��ϱ�?(MsgBox, �ڽ��� ��� Ż�� ����)
	DST_GUILD_DO_MAKE,						// ��带 ����ðڽ��ϱ�?(MsgBox, ��� ���� ����)
	DST_GUILD_DO_DISSOLVE,					// ��带 �ػ��Ͻðڽ��ϱ�?(MsgBox, ��� �ػ� ����)
	DST_GUILD_NOTICE_DISSOLVE,				// %d�� %d�� %d��(%s) %d�� %d�� ��� �ػ��� ����Ǿ����ϴ�(��� �ػ� ����)
	DST_GUILD_CANCEL_DISSOLVE,				// ��� �ػ��� ����Ͻðڽ��ϱ�?(MsgBox, ��� �ػ� ��� ����)
	DST_GUILD_CANCELED_DISSOLVE,			// ��� ������ ��ҵǾ����ϴ�(��� �ػ� ��� ����)

	DST_GUILD_CREATE,						// ��带 ��������ϴ�(Notify, ����忡��)
	DST_GUILD_NAME_RULE,					// ��� �̸��� 2�ڿ��� 16�ڱ����� ����� �� �ֽ��ϴ�(��带 ����ų� �̸��� ������ ��)
	DST_GUILD_CREATE_NFY,					// %s ��尡 �����Ǿ����ϴ�(Notify, ��������)
	DST_GUILD_INVITE,						// %s���� ��忡 �ʴ��Ͽ����ϴ�(Notify, ����忡��)
	DST_GUILD_INVITE_RES,					// ��忡 ���ԵǾ����ϴ�(Notify, ��������)
	DST_GUILD_INVITE_REQ,					// %s ��忡 �����Ͻðڽ��ϱ�?(Notify, �Ϲ� PC����)
	DST_GUILD_DECLINE,						// %s���� ��� ������ �����Ͽ����ϴ�(Notify, ����忡��)
	DST_GUILD_EXPIRED,						// %s�� ��� ���Կ� �������� �ʾҽ��ϴ�(Notify, ����忡��)
	DST_GUILD_NEW_MEMBER,					// %s���� ��忡 �����Ͽ����ϴ�(Notify, ��� ��������)
	DST_GUILD_LEAVE_MEMBER,					// %s���� ��带 Ż���Ͽ����ϴ�(Notify, ��� ��������)
	DST_GUILD_KICKOUT_MEMBER,				// %s���� ��忡�� �߹�Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_SECOND_MASTER_APPOINTED,		// %s���� �α������ �Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_CHANGE_MASTER,				// %s���� ������� �Ǿ����ϴ�(Notify, ��� ��������)

	DST_GUILD_ONLINE_MEMBER,				// %s���� �����߽��ϴ�(Notify, ��� ��������)
	DST_GUILD_CLASS_CHANGE_MEMBER,			// %s���� %s Ŭ������ �Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_LEVEL_CHANGE_MEMBER,			// %s���� %d ������ �Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_DISMISS_SECOND_MASTER,		// %s���� �α�� �����Ϳ��� �Ϲ� ���ɹ��� �Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_DISBAND,						// ��尡 �ػ�Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_NOT_JOIN,						// ��忡 �������� �ʾҽ��ϴ�(������ ��尡 ���µ� Ż�� ��ư�� ������)
	DST_GUILD_EMPTY,						// �̰���

	DST_GUILD_ADD_FUNCTION,					// '%s' ��� ����� �߰��Ͻðڽ��ϱ�?(MsgBox, ����忡��)
	DST_GUILD_ADD_FUNCTION_NOTIFY,			// ��忡 ����� ����Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_CHANGE_GUILD_NAME,			// �ٲٽ� ��� �̸��� �Է����ֽʽÿ�(MsgBox, ����忡��)
	DST_GUILD_CHANGED_GUILD_NAME,			// ��� �̸��� ����Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_CHANGED_GUILD_NOTICE_SUCCESS,	// ��� ������ �߼��Ͽ����ϴ�(�ڽſ���)
	DST_GUILD_CHANGED_GUILD_NOTICE,			// ���ο� ��� ������ �ֽ��ϴ�(Notify, ��� ��������)
	DST_GUILD_CREATE_GUILD_EMBLEM,			// ��� ������ �����Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_CHANGE_GUILD_EMBLEM,			// ��� ������ ����Ǿ����ϴ�(Notify, ��� ��������)
	DST_GUILD_CONTRIBUTION_ZENNY,			// ��带 ���� %d ���ϸ� ����Ͻðڽ��ϱ�?(MsgBox, ���ϸ� ����� ������ ��� ��)
	DST_GUILD_CONTRIBUTION_ZENNY_NOTIFY,	// ���ϸ� ����Ͽ����ϴ�(Notify, �ڽſ���)
	DST_GUILD_CONTRIBUTION_ZENNY_OTHERS,	// %s���� %d ���ϸ� ����Ͽ����ϴ�(Notify, ��� ��������)
	DST_GUILD_EMBLEM_INFO,					// ��� ������ ���� �����ϴ�(guild ���̾�α׿��� ���� ��ư����)
	DST_GUILD_EMBLEM_MODIFY_INFO,			// ��� ���� ����(guild ���̾�α׿��� ���� ���� ��ư����)
	DST_GUILD_EMBLEM_EXPLAIN_1,				// �� �̹������� 3������ �������ּ���(��� ���� ����� â �޼���1)
	DST_GUILD_EMBLEM_EXPLAIN_2,				// �� �̹������� 3������ �������ּ���(��� ���� ����� â �޼���2)
	DST_GUILD_NOT_SELECT_EMBLEM,			// ������ ��Ҹ� ���� �������� �ʾҽ��ϴ�(������ ������ ������ ������ Ȯ���Ϸ��� �Ҷ�)

	DST_GUILD_WAREHOUSE_CAN_NOT_DISCARD,	// ��� â���� �������� ���� �� �����ϴ�

	// guile warehouse
	DST_GUILD_WAREHOUSE_ZENNY_DRAW_OUT,		// %d ���ϸ� ����Ͽ����ϴ�(��� â�� �����Ͽ���)
	DST_GUILD_WAREHOUSE_SAVE_ZENNY,			// %d ���ϸ� �����Ͽ����ϴ�(��� â�� ����Ͽ���)

	// Dialog mode message
	DST_DIALOG_MODE_ITEM_REPAIR,			// �ջ�� �������� �����Ͻʽÿ�(������ ���� ��忡��)
	DST_DIALOG_MODE_ITEM_IDENTIFICATION,	// �������� �������Դϴ�(������ ������ �ٸ� �۾��� �Ϸ��� �� ��)
	DST_DIALOG_MODE_NARRATION,				// �̺�Ʈ�� �������Դϴ�(�����̼� ����� �ٸ� �۾��� �Ϸ��� �� ��)
	DST_DIALOG_MODE_CHAT_RESIZING,			// ä��â�� ũ�⸦ �������Դϴ�(ä�� ũ�� ������ �ٸ� �۾��� �Ϸ��� �� ��)

	// World concept messsage
	DST_WORLD_CONCEPT_TUTORIAL,				// ������ Ʃ�丮���� �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_TMQ,					// ������ Ÿ�Ӹӽ� ����Ʈ�� �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_RANK_BATTLE,			// ������ ��ũ��Ʋ�� �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_BUDOKAI,				// ������ õ������ ����ȸ�� �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_PARTY_DUNGEON,		// ������ ��Ƽ ������ �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_TLQ,					// ������ Ÿ�Ӹ� ����Ʈ�� �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_DOJO_SCRAMBLE,		// ������ ���� ��Ż���� �������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)

	DST_WORLD_CONCEPT_FREEBATTLE,			// ������ ������Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_NPC_COMMUNICATION,	// ������ NPC�� ��ȭ���Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_TRADE,				// ������ �ŷ����Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_PLAY_DRAGONBALL,		// ������ ����� �ҷ����� �ֽ��ϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_PLAY_PRIVATESHOP,		// ������ ���λ��� �Ǹ��� �Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_PLAY_PRIVATESHOP_VISITOR, // ������ ���λ��� �̿��� �Դϴ�(���������� ���� �ٸ� �۾��� �� �� ���� ��)
	DST_WORLD_CONCEPT_PLAY_DIRECT,				// ������ �������Դϴ�.(���������� ���� �ٸ� �۾��� �� �� ���� ��)

	// Notify Get message
	DST_NOTIFY_GET_ITEM,						// %s �������� ȹ���Ͽ����ϴ�(�������� �����)
	DST_NOTIFY_GET_ZENNY,						// %d ���ϸ� ȹ���Ͽ����ϴ�(���ϸ� �����
	DST_NOTIFY_GET_ZENNY_AND_BONUS,				// %d(+%d) ���ϸ� ȹ���Ͽ����ϴ�(���ϸ� �����
	DST_NOTIFY_GET_UNIDENTIFIED_ITEM,			// ��Ȯ�� �������� ȹ���Ͽ����ϴ�.
	DST_NOTIFY_LEARN_SKILL,						// %s ��ų�� ������ϴ�.
	DST_NOTIFY_UPGRADE_SKILL,					// %s ��ų�� ���׷��̵� �߽��ϴ�.
	DST_NOTIFY_GAIN_EXP,						// EXP�� %u ȹ�� �Ͽ����ϴ�. 
	DST_NOTIFY_GAIN_EXP_AND_BONUS,				// EXP�� %u(+%u) ȹ�� �Ͽ����ϴ�. 
	DST_NOTIFY_GET_QUEST_ITEM,					// ����Ʈ������( %s )�� ȹ���Ͽ����ϴ�. 
	DST_NOTIFY_GET_BUFF,						// %s ������ ������ϴ�.
	DST_NOTIFY_GET_REPUTATION,					// %u ���� ������ϴ�.
	DST_NOTIFY_CHANGE_CLASS,					// ���� ���� ( %s -> %s )
	DST_NOTIFY_LEVEL_UP,						// ������( %u -> %u )

	// Quest GiveUp Message
	DST_QUEST_GIVEUP_MESSAGE,				// %s ����Ʈ�� �����Ͻðڽ��ϱ�? (�޼����ڽ�)
	DST_QUEST_GAVEUP_MESSAGE,				// %s ����Ʈ�� �����Ͽ����ϴ�. (��Ƽ����)
	DST_QUEST_SUCCESS_DELIVERY,				// %s ����Ʈ ������ ��� �Ϸ�.
	DST_QUEST_SUCCESS_MOBHUNT,				// %s ����Ʈ ���� ��� �Ϸ�.
	DST_QUEST_SUCCESS_COLLECTION,			// %s ����Ʈ ������ ���� �Ϸ�.
	DST_QUEST_SUCCESS_CUSTOM,				// %s ����Ʈ �ӹ� �Ϸ�.
	DST_QUEST_SUCCESS_VISIT,				// %s ����Ʈ �湮�ӹ� �Ϸ�.
	DST_QUEST_FAILED,						// %s ����Ʈ�� �����Ͽ����ϴ�.
	DST_QUEST_CLEAR,						// %s ����Ʈ Ŭ����. ������ ��������.
	DST_QUEST_COMPLETE,						// %s ����Ʈ �ϼ�.

	// Quest share message
	DST_QUEST_SHARE_TRY,						// %s ����Ʈ�� ��Ƽ���鿡�� ���� �߽��ϴ�.
	DST_QUEST_SHARE_ALREADY_PROGRESS,			// [����Ʈ ����] < %s > �� ���� ���� ���Դϴ�.
	DST_QUEST_SHARE_HAS_BEEN,					// [����Ʈ ����] < %s > �� �̹� ������ ���� �־� ���� ���� �� �����ϴ�.
	DST_QUEST_SHARE_OTHER_QUEST_PROGRESS,		// [����Ʈ ����] < %s > �� ���� �������̽��� ��� ���Դϴ�. �������̽��� ���� �� �ٽ� �õ����ּ���.
	DST_QUEST_SHARE_MAX_OVERFLOW,				// [����Ʈ ����] ���� ������ �ִ� ����Ʈ ������ �ʰ��� ���� ���� �� �����ϴ�.
	DST_QUEST_SHARE_COND_COMPLETE,				// [����Ʈ ����] ���� ����Ʈ�� �������� �ʾ� < %s > �� ���� ���� �� �����ϴ�.
	DST_QUEST_SHARE_COND_NPC_REGION,			// [����Ʈ ����] < %s > �� ���� �ޱ� ���ؼ��� Ư�� NPC ��ó�� �־�� �˴ϴ�.
	DST_QUEST_SHARE_COND_ITEM,					// [����Ʈ ����] < %s > �� ���� �ޱ� ���ؼ��� �������� ������ �־�� �մϴ�.
	DST_QUEST_SHARE_COND_QITEM,					// [����Ʈ ����] < %s > �� ���� �ޱ� ���ؼ��� ����Ʈ �������� ������ �־�� �մϴ�.
	DST_QUEST_SHARE_COND_LEVEL,					// [����Ʈ ����] ������ ���� �ʾ� < %s > �� ���� ���� �� �����ϴ�.
	DST_QUEST_SHARE_COND_PC_CLASS,				// [����Ʈ ����] ������ ���� �ʾ� < %s > �� ���� ���� �� �����ϴ�.
	DST_QUEST_SHARE_COND_PC_RACE,				// [����Ʈ ����] ������ ���� �ʾ� < %s > �� ���� ���� �� �����ϴ�.
	DST_QUEST_SHARE_COND_EQUIP_ITEM,			// [����Ʈ ����] < %s > �� ���� �ޱ� ���ؼ��� Ư�� �������� �����ϰ� �־�� �մϴ�.
	DST_QUEST_SHARE_COND_IN_WORLD,				// [����Ʈ ����] < %s > �� ���� �ޱ� ���ؼ��� Ư�� ������ �־�� �մϴ�.

	// Quest Indicator Message
	DST_QUEST_INDICATOR_CANNOT_ADD_INDICATE_ITEM,	// ���̻� ����Ʈ �˸��̿� ����� �� �����ϴ�.

	// Quest 
	DST_QUEST_LINK_ACTION_ERROR,			// ����� �ٽ� �õ����ּ���

	// user trade message
	DST_TRADE_REQUEST_START,				// %s�Կ��� �ŷ��� ��û�Ͽ����ϴ�(�ŷ��� ��û�� �������)
	DST_TRADE_YOUR_BAG_NOT_ENOUGH,			// ����� ���濡 �� ������ ���ڶ��ϴ�(�ŷ��� ����� �� ���� īƮ�� ������ ����â �޼���)
	DST_TRADE_THE_OTHERS_BAG_NOT_ENOUGH,	// ����� ���濡 �� ������ ���ڶ��ϴ�(�ŷ��� ����� �� ���� īƮ�� ������ ����â �޼���)
	DST_TRADE_ACCEPT_TRADE,					// %s���� �ŷ� ��û�� ���Ͻðڽ��ϱ�?(MsgBox, �ڽ��� �ŷ� ��û�� �޾Ҵ�)
	DST_TRADE_OTHER_CANCLE_TRADE,			// ������ �ŷ��� �����Ͽ����ϴ�(�ŷ��� �ڽſ��� �� �޼���)

	// lobby message
	DST_LOBBY_MUST_CHOICE_CHANNEL,			// ä���� �����Ͻʽÿ�
	DST_LOBBY_MUST_CHOICE_CHAR,				// ĳ���͸� �����Ͻʽÿ�
	DST_LOBBY_MUST_CHOICE_SERVER,			// ������ �����Ͻʽÿ�
	DST_LOBBY_DEL_CHARACTER,				// ĳ���͸� ����ðڽ��ϱ�
	DST_LOBBY_PLEASE_CHECK_DEL_AND_RECOVERY_DATA,	// ĳ���� �̸��� ��Ȯ�� �Է��� �ֽʽÿ�(ĳ���� ����, ������ �߸� �Է����� ��,�κ�,OK��ư)
	DST_LOBBY_ASK_RENAME,					// ���ο� ĳ���� �̸��� �Է��� �ֽʽÿ�(ĳ���� �̸��� ������ ��,Inputbox,�κ�,OK��ư,Cancel��ư)
	DST_LOBBY_NO_RELPY_SERVER,				// �����κ��� ������ �����ϴ�
	DST_LOBBY_CAN_NOT_USE_THE_WORD,			// ����� �� ���� �ܾ �ֽ��ϴ�	
	DST_LOBBY_EMPTYNAME,					// �̸��� �Է��Ͽ� �ֽʽÿ�
	DST_LOBBY_RESERVATED_CHAR,				// ���� ������� ĳ�����Դϴ�(���� ������� ĳ���ͷ� ������ �����Ϸ��� �� ��)
	DST_LOBBY_CAN_NOT_USE_CHAR_UNTIL_RENAME,// �̸��� �����ϱ� �������� ����� �� ���� ĳ�����Դϴ�(���� ��å�� ���� ����� �� ���� ĳ���� �̸����� ������ ��, �κ� �޼���, OK��ư)
	DST_LOBBY_COMPLETE_RENAME,				// ĳ������ �̸��� %s���� %s���� �ٲ�����ϴ�(ĳ���� �̸��� �ٲٱ� �������� ��, �κ� �޼���, OK��ư)
	DST_LOBBY_RECOVERY_CHAR,				// ĳ���͸� �����Ͻðڽ��ϱ�(���� ������� ĳ���͸� �����Ϸ��� �� ��)
	DST_LOBBY_WAIT_GAME_SERVER_CONNECT,		// ����� %d��° ������Դϴ�(�κ񿡼� �������� ���� �� �� �������� ����)

	// warehouse message
	DST_WAREHOUSE_WANT_YOU_BUY,				// â��(%d ����)�� �����Ͻðڽ��ϱ�?(MsgBox, â�� ���� ����)
	DST_WAREHOUSE_WANT_YOU_BUY_COMMON,		// ���� â��(%d ����)�� �����Ͻðڽ��ϱ�?(MsgBox, ���� â�� ���� ����)
	DST_WAREHOUSE_FULL,						// â�� ���� á���ϴ�(â��� �������� �ű���� �� ��)
	DST_WAREHOUSE_SUCCESS_BUY,				// â�� �����Ͽ����ϴ�(â�� ���� ����)

	// scouter message
	DST_SCOUTER_NEED_SCOUTER,					// ��ī���Ͱ� �ʿ��մϴ�(��ī���� �����Ϸ� �� ��)
	DST_SCOUTER_OUT_OF_ORDER_SCOUTER,			// ��ī���Ͱ� ���峵���ϴ�(��ī���� �����Ϸ� �� ��)
	DST_SCOUTER_MUST_CLEAR_SCOUTER,				// ��ī���͸� �ű���� ���� ������մϴ�(��ī���͸� �ű���� �� ��)
	DST_SCOUTER_FULL,							// ��ī���Ϳ� ������ ���� á���ϴ�(��ī���Ϳ� ������ �����Ϸ��� �� ��)
	DST_SCOUTER_CAN_NOT_MOVE_PARTS_ON_MENU,		// ��ī���� �޴��� �۵��߿��� ������ ������ �� �����ϴ�(��ī���Ϳ� ������ ������ �ű���� �� ��)
	DST_SCOUTER_EXPLAIN_SLOT,					// %sŰ�� ��ī���� ����â�� �� �� �ֽ��ϴ�(��ī���� ���� ����)
	DST_SCOUTER_WORKING,						// ��ī���͸� ������Դϴ�(��ī���� ����� ��ī���͸� ���� ����/�������Ϸ��� �� ��)
	DST_SCOUTER_QUEST_SEARCH_NOT_QUEST,			// ��ī������ �˻� ������ ����Ʈ�� ���� NPC�� ã�� �� �����ϴ�(����Ʈ ��ġ��)
	DST_SCOUTER_SUCCESS_FIND_HIDDEN_OBJECT,		// ������ ��ü�� %d�� ã�ҽ��ϴ�(��ī���ͷ� ������ ��ü ã�� ����� ���� ��)
	DST_SCOUTER_NOT_EXIST_HIDDEN_OBJECT,		// ��ó�� ������ ��ü�� �����ϴ�(��ī���ͷ� ������ ��ü ã�� ����� ���� ��)

	// party message
	DST_PARTY_CREATE,							// ��Ƽ�� ����ðڽ��ϱ�?(MsgBox, ��Ƽ�� ���� ��)
	DST_PARTY_NAME_RULE,						// ��Ƽ �̸��� 2�ڿ��� 16�ڱ����� ����� �� �ֽ��ϴ�(��Ƽ�� ������� �� ��)
	DST_PARTY_INVITE_SUCCESS,					// s���� ��Ƽ�� �ʴ��Ͽ����ϴ�(Notify, ��Ƽ�忡��)
	DST_PARTY_PARTY_INVITE,						// %s ��Ƽ�� �����Ͻðڽ��ϱ�?(MsgBox, �Ϲ� PC����)
	DST_PARTY_PARTY_INVITE_WITHOUT_PARTY,		// %s ���� ��Ƽ�� �����Ͻðڽ��ϱ�?(MsgBox, ��Ƽ�� �������� ���� PC�� �Ϲ� PC����)
	DST_PARTY_NEW_MEMBER,						// %s���� ��Ƽ�� �����̽��ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVITE_DECLINE,					// %s���� �ʴ븦 �����Ͽ����ϴ�(Notify, ��Ƽ�忡��)
	DST_PARTY_LEAVE_ASK,						// ��Ƽ�� Ż���Ͻðڽ��ϱ�?(MsgBox, �ڽſ���)
	DST_PARTY_LEAVE,							// %s���� ��Ƽ���� Ż���Ͽ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_CHANGE_LEADER,					// %s���� ��Ƽ���� �Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_CHANGE_ITEM_DIVISION,				// ������ �й����� %s�� ����Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_CHANGE_ZENNY_DIVISION,			// ���� �й����� %s�� ����Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_NOTIFY_DIVISION_INFO,				// �й� ����� ������ �� �� ��ư�� ���� �����Ͻʽÿ�(Notify, ��ư�� ����)
	DST_PARTY_NOTIFY_WAIT_DIVISION,				// �й� ����� �����Ϸ��� ��� ��ٸ��ʽÿ�(Notify, ��Ƽ�忡��)

	DST_PARTY_GET_ITEM,							// %s���� %s ȹ��(Notify, ��� ��Ƽ������)
	DST_PARTY_GET_ZENNY,						// %d�� %d ���ϸ� �й�޾ҽ��ϴ�(Notify, �ڽſ���)
	DST_PARTY_GET_ZENNY_AND_BONUS,				// %d�� %d(+%d) ���ϸ� �й�޾ҽ��ϴ�(Notify, �ڽſ���)
	DST_PARTY_GET_ZENNY_OTHER,                  // %s���� %d ���ϸ� ȹ���Ͽ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_GET_ZENNY_OTHER_AND_BONUS,		// %s���� %d(+%d) ���ϸ� ȹ���Ͽ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_ADD_ITEM,					// ��Ƽ �κ��丮�� %s ȹ��(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_ADD_UNDEFINED_ITEM,			// ��Ƽ �κ��丮�� ��Ȯ�� �������� ȹ���Ͽ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_ADD_UNDEFINED_ITEM_OTHER,	// %s���� ��Ȯ�� �������� ȹ���Ͽ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_CHANGE_ITEM_GRADE,			// ��Ƽ �κ��丮�� �����Ǵ� �������� ����� %s�̻����� ����Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_OCTION_LOCK,				// ��Ƽ �κ��丮�� ��Ű� ���� �Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_OCTION_UNLOCK,				// ��Ƽ �κ��丮�� ��Ű� ���� �Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_OCTION_RESET,				// ��Ƽ �κ��丮�� ��� ������ �ʱ�ȭ �Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_INVEN_OCTION_SUCCESSFUL_BID,		// ��Ƽ �κ��丮�� %s �������� ��Ű� %s�Կ��� ���� �Ǿ����ϴ�(Notify, ��� ��Ƽ������ ��� ���� ��)
	DST_PARTY_INVEN_OCTION_SUCCESSFUL_BID_WITH_UNIDENTIFY,	// ��Ƽ �κ��丮�� ��Ȯ�� �������� ��Ű� %s�Կ��� ���� �Ǿ����ϴ�(Notify, ��� ��Ƽ������ ��� ������)
	DST_PARTY_INVEN_GIVE_BY_LEADER,				// ��Ƽ �κ��丮�� %s �������� ��Ƽ���� %s�Կ��� �й� �Ͽ����ϴ�(Notify, ��� ��Ƽ������ ��Ƽ���� �й��)
	DST_PARTY_INVEN_GIVE_BY_LEADER_WITH_UNIDENTIFY,	// ��Ƽ �κ��丮�� ��Ȯ�� �������� ��Ƽ���� %s�Կ��� �й� �Ͽ����ϴ�(Notify, ��� ��Ƽ������ ��Ƽ���� �й��)
	DST_PARTY_INVEN_START_DICE,					// ��Ƽ �κ��丮�� ������ �й踦 ���� �ֻ��� �����Ⱑ ���� �Ǿ����ϴ�(Notify, ��� ��Ƽ������ �ֻ��� �й� ���۽�)
	DST_PARTY_INVEN_DICE_WINNER,				// ��Ƽ �κ��丮�� %s �������� %s���� ���� �Ͽ����ϴ�(Notify, ��� ��Ƽ������ �ֻ��� �й��)
	DST_PARTY_INVEN_DICE_WINNER_WITH_UNIDENTIFY,// ��Ƽ �κ��丮�� ��Ȯ�� �������� %s���� ���� �Ͽ����ϴ�(Notify, ��� ��Ƽ������ �ֻ��� �й��)

	DST_PARTY_NEED_ZENNY,						// %d ���ϰ� �ʿ��մϴ�(��Ƽ ������ �ߵ��Ϸ��� �� ��)
	DST_PARTY_DECLARE_ZENNY,					// ���� %d ���ϸ� ����Ͽ����ϴ�(��Ƽ����â�� ���ϸ� ����ߴ�)
	DST_PARTY_DECLARE_ZENNY_PART,				// %d ������ %d ���ϸ� ����Ͽ����ϴ�(��Ƽ����â�� ���ϸ� ����ߴ�)
	DST_PARTY_TOOLTIP_ZENNY,					// %u ���ϸ� ����Ͽ����ϴ�(��Ƽ����â ����� ���ϸ� �������� �����ش�)
	DST_PARTY_REG_VICTIM_ITEM,					// %s���� %s ������ ����߽��ϴ�(Notify, �ڽ�(��Ƽ��)����)
	DST_PARTY_UNREG_VICTIM_ITEM,				// %s ������ �����Ͽ����ϴ�(Notify, �ڽ�(��Ƽ��)����)
	DST_PARTY_ACTIVATE_CHARM,					// %s ������ �ߵ��Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_STOP_CHARM,						// %s ������ �����Ǿ����ϴ�(Notify, ��� ��Ƽ������)
	DST_PARTY_RELEASE_CHARM,					// ������ ����� �����Ͻðڽ��ϱ�?(MsgBox, �ڽſ���)
	DST_PARTY_CHARMSLOT_NOT_EMPTY,				// ���� ������ ������� �ʽ��ϴ�(Notify, �ڽſ���)
	DST_PARTY_CHARM_START_DICE,					// ��Ƽ ���� �ֻ����� �����ϴ�(�ֻ��� ���̾�α׿�, ��� ��Ƽ������ ��� ��Ƽ���� �ߵ���)
	DST_PARTY_CHARM_START_DICE_RESULT_FAIL,		// ��Ƽ ���� �����⿡ �����߽��ϴ�(Notify, ��� ��Ƽ������ ��� ��Ƽ���� �ߵ���)

	DST_PARTY_DUNGEON_INITIALIZE,				// ��Ƽ ������ �ʱ�ȭ�Ǿ����ϴ�(��Ƽ���� ��Ƽ ������ �ʱ�ȭ�Ͽ���)
	DST_PARTY_DUNGEON_CHANGE_NORMAL,			// ��Ƽ ������ ���̵��� �������� ����Ǿ����ϴ�(��Ƽ���� ��Ƽ ������ ���¸� �����Ͽ���)
	DST_PARTY_DUNGEON_CHANGE_HARD,				// ��Ƽ ������ ���̵��� ��������� ����Ǿ����ϴ�(��Ƽ���� ��Ƽ ������ ���¸� �����Ͽ���)

	// trade cart message
	DST_TRADECART_CANNOT_SELL_ITEM,				// �� �� ���� �������Դϴ�
	DST_TRADECART_NO_MORE_SLOT,					// īƮ�� ������ �����մϴ�

	// Dragonball Collection Message 
	DST_DBC_NOT_ENOUGH,						// �巡�ﺼ�� ������ �����մϴ�.
	DST_DBC_NOT_KEYWORD,					// �ֹ��� �Է��ϼ���
	DST_DBC_NOT_SAME,						// ���� Ÿ���� �巡�ﺼ�� �ƴմϴ�.
	DST_DBC_ALREADY_USE_ALTAR,				// ������ �̹� ������Դϴ�.
	DST_DBC_DRAGONBALL_NOT_FOUND,			// �巡�ﺼ�� ���濡�� ã�� �� �����ϴ�.
	DST_DBC_NOT_DRAGONBALL,                 // �巡�ﺼ���� �������� ���ܿ� ������ �����ϴ�
	DST_DBC_NOT_SAME_NUMBER,		        // ���ܿ� ���� ������ �巡�ﺼ�� ���� �� �����ϴ�.

	// Skill
	DST_SKILL_USING_TRINER_DIALOG,	        // ��ųƮ���̳� â�� �̿�ÿ��� �ڽ��� ��ųâ�� �� �� �����ϴ�
	DST_SKILL_CANCEL,				        // ��ų ������ ��ҵǾ����ϴ�.
    DST_SKILL_OCCLUSION_CHECK,              // ����� ������Ʈ�� �������� ��ų�� ����� �� �����ϴ�.


	// Skill�䱸���� ( �޼����� ���������쿡���� ó����)
	DST_SKILL_RQ_LEARN_LEVEL,		// ��ų�� ������ Level�� �÷��� �Ѵ�. 
	DST_SKILL_RQ_LEARN_SKILL,		// ��ų�� ������ �ٸ� ��ų�� ���� ������Ѵ�.
	DST_SKILL_RQ_READY_LEARN_BY_SKILLMASTER,// ��ų�����Ϳ��� ��ų�� ��� �� �ִ�.
	DST_SKILL_RQ_READY_LEARN_BY_SELF,// ��ų�� ������ ��� �� �ִ�.
	DST_SKILL_RQ_UPGRADE_LEVEL,		// ��ų�� ���׷��̵��ϱ� ���� Level�� �������
	DST_SKILL_RQ_UPGRADE_SKILLEXP,	// ��ų�� ���׷��̵��ϱ� ���� ��ųEXP�� �ʿ��ϴ�
	DST_SKILL_RQ_READY_UPGRADE,		// ��ų�� ���׷��̵� �� �� �ִ�.
	DST_SKILL_RQ_MASTERED,			// ��ų�� ������ �ߴ�.
	DST_SKILL_RQ_LEARNED,			// ��ų�� �̹� �����.	
	DST_SKILL_RQ_LEARN_CLASS,		// Ŭ������ �޶� ���� ����.
	DST_SKILL_RQ_NOT_LEARN_CHANGECLASSRIGHT,	// ���������� ���� ȹ�� �� �ִ�.

	// Skill �˸���					/// woosungs_test 20090730
	DST_SKILL_NOTYFY_UPGRADE_TITLE,	// ��ų ���׷��̵� �˸���
	DST_SKILL_NOTYFY_UPGRADE_ALARM,	// ���׷��̵� ������ ��ų�� ������ ��ųâ�� Ȯ���� �ּ���
	DST_SKILL_NOTYFY_LEARN_MASTER_SKILL_TITLE,	// ��ų ���� �˸���
	DST_SKILL_NOTYFY_LEARN_MASTER_SKILL_ALARM,	// ���ο� ��ų�� ��� �� �ֽ��ϴ� ��ųâ�� Ȯ���� �ּ��� 
	DST_SKILL_NOTYFY_LEARN_SELF_SKILL_TITLE,	// ��ų ���� �˸���
	DST_SKILL_NOTYFY_LEARN_SELF_SKILL_ALARM,	// ���ο� ��ų�� ��� �� �ֽ��ϴ� ��ųâ�� Ȯ���� �ּ���

	// ����
	DST_BATTLE_CAN_NOT_ATTACK_TARGET,	// ������ �� ���� ����Դϴ�(�����Ϸ� �� ��)

	// Item
	DST_ITEM_CONFIRM_DROP,			// %s �������� �����ðڽ��ϱ�?(MsgBox, �������� �������� �� ��)
	DST_STACKITEM_CONFIRM_DROP,		// %s ������ %d���� �����ðڽ��ϱ�?
	DST_ITEM_REMOTE_SELL,			// %s �������� �Ǹ��Ͻðڽ��ϱ�?(MsgBox, �������� �����Ǹ� �� ��)
	DST_STACKITEM_REMOTE_SELL,		// %s ������ %d���� �Ǹ��Ͻðڽ��ϱ�?(MsgBox, �������� �����Ǹ� �� ��)
	DST_ITEM_BAG_FULL,				// ���濡 �������� ���� á���ϴ�(�������� �������� �ű���� �� ��)
	DST_ITEM_CAN_NOT_MOVE_THERE,	// �װ��� �ű� �� �����ϴ�(�ű� �� ���� ���� �������� �ű���� �ߴ�)
	DST_ITEM_CAN_NOT_MOVE_TO_WAREHOUSE, // â��� �ű� �� ���� �������Դϴ�(â��� �ű� �� ���� �������� �ű���� �ߴ�)
	DST_ITEM_CAN_NOT_TRADE,			// �ŷ��� �� ���� �������Դϴ�(�ŷ��� �� ���� �������� �ŷ��Ϸ��� �ߴ�)
	DST_ITEM_CAN_NOT_SELL,			// �� �� ���� �������Դϴ�(�� �� ���� �������� �ȷ��� �ߴ�)
	DST_ITEM_CAN_NOT_SAVE_COMMON_WAREHOUSE, // ����â�� ������ �� ���� �������Դϴ�(����â�� ������ �� ���� �������� �����Ϸ��� �ߴ�)
	DST_ITEM_CAN_NOT_EQUIP_ZERO_DURABILITY,	// �������� 0�� �������� ������ �� �����ϴ�.
	DST_ITEM_CAN_NOT_EQUIP_EXPIRED_DURATION,// ���Ⱓ�� ����Ǿ� ������ �� �����ϴ�.
	DST_ITEM_CAN_NOT_MOVE_BAG_EXPIRED_DURATION,	// ������ ���Ⱓ�� ����Ǿ� �ű� �� �����ϴ�.
	DST_ITEM_CAN_NOT_MOVE_SCOUTER_EXPIRED_DURATION, // ��ī������ ���Ⱓ�� ����Ǿ� ������ ������ �� �����ϴ�. 	
	DST_ITEM_CAN_NOT_MOVE_NETPYSTORE,// ��â��� �ű� �� ���� �����Դϴ�. �ݸ��� �Ǿ����� �̿��� ��¼��...
	DST_ITEM_CAN_NOT_MOVE_BASICBAG,	 // �⺻������ �ű� �� �����ϴ�.
	DST_ITEM_CAN_NOT_MOVE_NOT_EMPTY_BAG,	// ������� ���� ������ �ű� �� �����ϴ�. 
	DST_ITEM_CAN_NOT_MOVE_NOT_EQUIAL_EQUIPTYPE,	// ���Ÿ���� �޶� ������ �� �����ϴ�.	
	DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_NOT_BAG,	// ĸ��ŰƮ���Կ��� ĸ��ŰƮ�� ���� �����մϴ�. 
	DST_ITEM_CAN_NOT_MOVE_TO_EQUIP_NOT_EQUIPITEM,	// ���������� �����۸� ������ �� �ֽ��ϴ�.
	DST_ITEM_CAN_NOT_MOVE_TO_SCOUTER_NOT_SCOUTERPARTS,	// ��ī���� ���� �����۸� ���� �����մϴ�.
	DST_ITEM_CAN_NOT_MOVE_TO_BAGSLOT_FULLBAGSLOT,	// ������ ���̻� ������ �� �����ϴ�.

	DST_ZENNY_CAN_NOT_MOVE_TO_TRADECART_NOT_VALID,	// �ŷ�â�� �����ϴ�. 

	DST_ITEM_CAN_NOT_DISCARD_NOT_PICKUP,	// �������� ���� ���¿��� Ŭ���ؾ� ���� �� �ֽ��ϴ�
	DST_ITEM_CAN_NOT_DISCARD_NOT_STATE,		// ������¿����� �������� ���� �� �����ϴ�.	
	DST_ITEM_CAN_NOT_UNEQUIP_BAG_FULL,		// ������ ������ �������� ������ �� �����ϴ�
	DST_ITEM_NO_TARGET_APPOINTED,			// ��� ����� �����ؾ� �մϴ�. (������ ���� ���� Ÿ���� ���� ��)
	DST_ITEM_CAN_NOT_USE_MAX_LP,			// LP�� ������ ����� �� �����ϴ�. ( LP, EP, RPBALL�� �ϳ��� ������ ���� �ߺ� ��µ� �� ���� )
	DST_ITEM_CAN_NOT_USE_MAX_EP,			// EP�� ������ ����� �� �����ϴ�. 
	DST_ITEM_CAN_NOT_USE_MAX_RP_BALL,		// RP BALL�� ������ ����� �� �����ϴ�. 

	DST_ITEM_CAN_NOT_MOVE_ERROR_SERIAL_ID,	// �ø��� ID �����Դϴ�. ( GM���� �����ϼ���. )
	DST_ITEM_CAN_NOT_MOVE_ERROR_PACKET_SEND,// ��Ʈ��ũ �����Դϴ�. ( �ٽ� �õ��� �ּ���. )

	// Upgrade
	DST_ITEMUPGRADE_NOTIFY_CANNOT_INSERT_HOIPOISTONE,		// �̹� ȣ������ ������ �����Ǿ� ����� �� �����ϴ�.
	DST_ITEMUPGRADE_NOTIFY_CAN_INSERT_ONLY_HOIPOISTONE,		// ȣ�����̽��游 ���� �����մϴ�.
	DST_ITEMUPGRADE_NOTIFY_CANNOT_UPGRADE,					// ���̻� ���׷��̵� �� �� �����ϴ�.
	DST_ITEMUPGRADE_NOTIFY_CANNOT_DOWNGRADE,				// ���̻� �ٿ�׷��̵� �� �� �����ϴ�.
	DST_ITEMUPGRADE_NOTIFY_CAN_INSERT_ONLY_UPGRADEBLE_ITEM,	// ���׷��̵� ������ �����۸� ���� �����մϴ�.
	DST_ITEMUPGRADE_NOTIFY_CANNOT_INSERT_DUPLEX,			// ������ ������� �ʽ��ϴ�. ������Ű�� ���������մϴ�.
	DST_ITEMUPGRADE_NOTIFY_CANNOT_CONTROL_STATE,			// ���׷��̵� ������ ������ �� ���� �����Դϴ�.	
	DST_ITEMUPGRADE_NOTIFY_CANNOT_PICKUP_UPGRADE_ITEM,		// ���׷��̵� �������� ���� �� �����ϴ�. ������ Ű�� ���� �����մϴ�.
	DST_ITEMUPGRADE_NOTIFY_CAN_INSERT_ONLY_UPGRADEITEM_OR_HOIPOISTONE,	// ���׷��̵� ������ �������̳� ȣ�����̽��游 �������� �մϴ�.
	
	// Target
	DST_TARGET_NONE,							// Ÿ���� �����ϴ�
	DST_TARGET_CANNOT_TARGETING_FOR_SCOUTER,	// �ڱ� �ڽ��� ������ �� �����ϴ�(��ī���� ������ ������)

	// free pvp
	DST_FREEPVP_CHALLENGE,						// "%s"���� ������ �Ͽ����ϴ�.\n������ ���̽ðڽ��ϱ�?
	DST_FREEPVP_OUTSIDE_STAGE,					// XX�� �Ŀ� ��� �й��ϰ� �˴ϴ�. 
	DST_FREEPVP_WIN,							// "%s"���� �й� �ϼ̽��ϴ�.
	DST_FREEPVP_LOSE,							// "%s"���� �¸� �ϼ̽��ϴ�.
	DST_FREEPVP_DRAW,							// "%s"���� �¸� �ϼ̽��ϴ�.

	// Rank Battle
	DST_RANKBATTLE_CANCELED,					// ��ũ��Ʋ�� ��ҵǾ����ϴ�.
	DST_RANKBATTLE_MUST_SELECT_ROOMID,			// ������ ��ũ��Ʋ�� �����ؾ� �մϴ�.
	DST_RANKBATTLE_MEMBER_FAINT,				// %s ���� �����߽��ϴ�.
	DST_RANKBATTLE_MEMBER_OUTOFAREA,			// %s ���� ����Դϴ�.
	DST_RANKBATTLE_MEMBER_GIVEUP,				// %s ���� ���������ϴ�.
	DST_RANKBATTLE_MATCH_READY,					// ��ũ��Ʋ �غ��߿��� �Խ����� �� �� �����ϴ�.
	
	// õ�����Ϲ���ȸ
	DST_BUDOKAI_MINOR_KILL_ANNOUNCE,		// %s���� %s���� �������׽��ϴ�.
	DST_BUDOKAI_MINOR_DICE_READY_NOTIFY,	// %u�� �� �ֻ����� ���� �ºθ� �����մϴ�.
	DST_BUDOKAI_MINOR_DICE_WIN_NOTIFY,		// %s���� %d�� �¸��ϼ̽��ϴ�.
	DST_BUDOKAI_MINOR_DICE_SCORE_NOTIFY,	// %s�� �ֻ��� ��� ( %u )
	DST_BUDOKAI_MINOR_WAIT_FOR_DICE_NOTIFY,	// ��÷�� �������Դϴ�. ��ø� ��ٷ��ֽʽÿ�.
	DST_BUDOKAI_MINOR_WAIT_FOR_KO,			// ���� ���������� %d�� ���� �Ͼ �� �����ϴ�.
	DST_BUDOKAI_MINOR_WAIT_FOR_RINGOUT,		// ��ܷ� %d�� ���� ������ ������ �� �����ϴ�.

	// Bind (���ε�� Ư���� ���� �ʿ����)
	DST_BIND_TEXT,							// ���ε� �Ͻðڽ��ϱ�? \\n���ε� �ϸ� ��Ȱ�� ���� ��ġ���� ��Ȱ�մϴ�(MsgBox, ��Ȱ ��ġ�� �����Ϸ��� �� ��)
	DST_BIND_SUCCESS,						// ���ε尡 ���������� �̷�������ϴ�(��Ȱ ��ġ�� �����ߴ�)

	// Dialog manager
	DST_CAN_NOT_OPEN_MORE_REGULAR_DIALOG,	// �� �̻� â�� �� �� �����ϴ�(���ַ� ���̾�α׸� ������ �� �� ���̻� �� ������ ����)

	// Item repair
	DST_REPAIR_ITEM,						// %d ���ϸ� �����ϰ� %s �������� �����Ͽ����ϴ�(���� ������)
	DST_REPAIR_ALL_ITEM,					// %d ���ϸ� �����ϰ� ��� �������� �����Ͽ����ϴ�(���� ������)

	// Item Identify
	DST_ITEM_IS_IDENTIFIED_ALREADY,			// �̹� Ȯ�ε� �������Դϴ�. 
	DST_ITEM_IS_UNIDENTIFIED,				// Ȯ�ε��� ���� �������Դϴ�. 

	// Block Mode Cooltime
	DST_BLOCK_MODE_COOLTIME,				// ��ϸ�带 ����� �� �����ϴ�(��Ÿ�Ӷ�����)

	// World map
	DST_WORLDMAP_CAN_OPEN_AREA,				// ������� �� �� ���� �����Դϴ�(�������	 ������ �� �� �� �� ���� �����̴�)
	DST_WORLDMAP_BIND_POPOICON_TOOLTIP,		// �������� �������濡�� ��Ȱ�� �����ϸ�\n�̰����� ��Ȱ�ϰ� �˴ϴ�(�������� ����)

	// Select Reward
	DST_MUST_SELECT_REWARD,					// ���ú����� �������� �ʾҽ��ϴ�(TMQ ���ú����� �������� �ʰ� Ȯ�ι�ư�� ������ ��)

	DST_MSG_MUST_INPUT_MESSAGE,				// �ƹ��͵� �Է����� �ʾҽ��ϴ�(��ǲ �޼��� �ڽ��� �ƹ��͵� �Է����� �ʰ� Ȯ���� ������)

	// bus
	DST_BUS_ASK_GET_ON,						// ������ ž���Ͻðڽ��ϱ�?(MsgBox, ������ Ż ������ �����)
	DST_BUS_ASK_GET_OFF,					// �������� �����ðڽ��ϱ�?(MsgBox, ������ ���� ������ �����)
	DST_BUS_SUCCESS_GET_ON,					// ������ ž���Ͽ����ϴ�(��� : %d Zenny)(������ ž�� ������)

	// Ż ��
	DST_VEHICLE_ONLY_REG_FUEL,				// ���Ḹ ���� �� �ֽ��ϴ�(���ᰡ �ƴ� �������� Ż �� GUI�� ����Ϸ� �� ��)
	DST_VEHICLE_NEED_FUEL,					// ���ᰡ �ʿ��մϴ�(���� ���� ������ �õ��� �ɷ��� �� ��)
	DST_VEHICLE_CAN_NOT_DO_THAT_WORKING_ENGINE,	// ������ �õ��� �ɷ������� �� �� �����ϴ�(������ �õ��� �ɷ��� �� �Ұ��� �ൿ�� �Ϸ��� �ϸ� ex : ���ᱳü)
	DST_VEHICLE_ASK_GET_OFF,				// �����ðڽ��ϱ�?(MsgBox, Ż �Ϳ��� �������� ��� ��)

	// npc shop	
	DST_NPCSHOP_SUCCESS_REMOTE_SELL,		// %s �������� ���� �Ǹ��Ͽ����ϴ�(�����Ǹſ� �������� ��)

	// namekan sign
	DST_UNCOVER_NAMEKAN_SIGN,				// ����ĭ������ �����͸� �ٿ� �޾ҽ��ϴ�(����ĭ ������ Ŭ������ ��)

	// ����
	DST_KNOCKDOWN,							// �ǽ� �����Դϴ�

	// Petition
	DST_PETITION_CHOICE_GREATE_CATEGORY,	// ��з��� �����Ͻʽÿ�(GM ä�� ������ â���� �������� ������ �� ��)
	DST_PETITION_CHOICE_SMALL_CATEGORY,		// �Һз��� �����Ͻʽÿ�(GM ä�� ������ â���� �������� ������ �� ��)
	DST_PETITION_INPUT_CONTENT,				// ������ �Է��ϼ���(GM ä�� ������ â���� �������� ������ �� ��)
	DST_PETITION_TOO_LONG_CONTENT,			// ������ �ʹ� ��ϴ�(GM ä�� ������ â���� �������� ������ �� ��)

	DST_PETITION_SIDEVIEW_MESSAGE,			// ������ ��û�Ǿ��� �� ���̵��� �޼���

	// ����
	DST_DOJO_ASK_ESTABLISHMENT,				// ������ �����Ͻðڽ��ϱ�? 500,000 ���ϰ� �ʿ��մϴ�(MsgBox : ������ �����Ϸ��� �� ��)
	DST_DOJO_SUCCESS_ESTABLISHMENT,			// %s�� ������ �����Ͽ����ϴ�(���Ŀ����� ������ ���������� �˸���)
	DST_DOJO_ADD_FUNCTION,					// '%s' ���� ����� �߰��Ͻðڽ��ϱ�?(MsgBox, ������� ���� ����� �߰��� ��)
	DST_DOJO_ADD_FUNCTION_NOTIFY,			// ���忡 ����� ����Ǿ����ϴ�(Notify, ��� ��������)

	DST_DOJO_ONLY_REGI_BAG_ZENNY,			// ������ ���ϸ� ����� �� �ֽ��ϴ�(���� ���׷��̵带 ���� ���ϸ� ����Ϸ� �� ��)
	DST_DOJO_ASK_UPGRAGE_WITH_ZENNY,		// ������ ���׷��̵� �Ͻðڽ��ϱ�? Ȯ���� �����ø� %d ���ϰ� �Ҹ�˴ϴ�(MsgBox : ���׷��̵� ������ ��� ��)
	DST_DOJO_ASK_UPGRAGE_WITH_ZENNY_AND_HOIPOI,	// ������ ���׷��̵� �Ͻðڽ��ϱ�? Ȯ���� �����ø� %d ���Ͽ� ȣ�����̶� % ���� �Ҹ�˴ϴ�(MsgBox : ���׷��̵� ������ ��� ��)

	DST_DOJO_ADD_TENKAI_SEED,				// õ������ ����ȸ �õ� ������ �̸��� �Է��� �ֽʽÿ�(Msgbox : ������ ���� �������� õ������ ����ȸ �õ� �����ڸ� ������ ��)

	DST_DOJO_SCRAMBLE_ASK_CHALLENGE,		// ���� ��Ż���� ��û�Ͻðڽ��ϱ�? ��û�� %d ���ϰ� �ʿ��մϴ�(Msgbox : ���� ��Ż�� ��û)
	DST_DOJO_SCRAMBLE_ACCEPT_CHALLENGE,		// %s ������ ��Ż�� ��û�� �����Ͻðڽ��ϱ�? �źθ� �����Ͻø� ���� %d ���ϰ� �Ҹ�˴ϴ�(Msgbox : ���� ��Ż�� ����)
	DST_DOJO_SCRAMBLE_ASK_TELEPORT,			// ��Ż���� �������� ��������� �����̵� �Ͻðڽ��ϱ�?(Msgbox : ���� ���� �ڷ���Ʈ)

	DST_DOJO_LOST_DOJO,						// ������ ���� ��尡 ������ �������� �Ҿ���Ƚ��ϴ�(�ƹ�Ÿ�� ���� ���İ� ������ �ִ� ������ �������� �Ҿ���)
	DST_DOJO_ASK_SCRAMBLE,					// ���� ��Ż�� ��û�� �߽��ϴ�(���� ��Ż���� ��û�� �����忡��)
	DST_DOJO_ACCEPTED_SCRAMBLE,				// ��Ż�� ��û�� �����Ǿ����ϴ�(���� ��Ż���� ��û�� �����忡��)
	DST_DOJO_REJECT_SCRAMBLE,				// ��Ż�� ��û�� �źδ��߽��ϴ�(���� ��Ż���� ��û�� �����忡��)

	DST_DOJO_SCRAMBLE_STATE_NORMAL,			// ���� %d�� %d�к��� ���� ��Ż���� ����� �����Դϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_NORMAL2,		// ���� %d�ú��� ���� ��Ż���� ����� �����Դϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_RECEIVE,		// ���� ��Ż�� ��û ������ �ð��Դϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_REJECT_END,		// ���� ��Ż�� �ź� �ð��� ����Ǿ����ϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_STANDBY,		// ���� ��Ż�� �غ����Դϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_INITIAL,		// ���� ��Ż�� �غ����Դϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_READY,			// ���� ��Ż�� ������ ���� ���忡 �����Ͽ� �ֽʽÿ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_START,			// ���� ��Ż���� ���۵Ǿ����ϴ�(���� ��Ż�� ���� �޼���)
	DST_DOJO_SCRAMBLE_STATE_END,			// ���� ��Ż���� ����Ǿ����ϴ�(���� ��Ż�� ���� �޼���)

	DST_DOJO_SCRAMBLE_CHANGE_SEAL_OWNER,	// %s���� %s�� ȹ��(���� ��Ż���� ������ ȹ���� ����� ���� ������ �޾��� ��)

	DST_DOJO_CAN_NOT_UPGRADE_BECAUSE_MAX_LEVEL, // ���� ���� ������ �ְ��Դϴ�(�ְ� ������ ������ ���׷��̵带 �Ϸ��� �� ��)
	DST_DOJO_CAN_NOT_UPGRADE_BECAUSE_NEED_ITEM, // ���� ���׷��̵忡 �ʿ��� ȣ�����̶��� ����� �ֽʽÿ�(���� ���׷��̵带 �Ϸ��� �� ��)
	DST_DOJO_CAN_NOT_UPGRADE_BECAUSE_NEED_MORE_ITEM, // ��ϵ� ȣ�����̶��� �����մϴ�(���� ���׷��̵带 �Ϸ��� �� ��)
	DST_DOJO_ONLY_REGISTER_ITEM,			 // ȣ�����̵��� ����� �� �ֽ��ϴ�(���� ���׷��̵� GUI�� �������� ����Ϸ��� �� ��)
	DST_DOJO_HAVE_NOT_DOJO,					// ������ ������ �����ϴ�(���� ���׷��̵� GUI�� �������� ����Ϸ��� �� ��)

	DST_DOJO_REWARD_GUILD_REPUTATION,		// ���� ��Ż�� �¸��� %d�� ��� ��ġ�� ȹ���߽��ϴ�(���� ��Ż�� ������ �̱������� ����)
	DST_DOJO_REWARD_ITEM,					// ���� ��Ż�� �¸��� %s �������� %d�� ȹ���߽��ϴ�(���� ��Ż�� ������ �̱������� ����)
	DST_DOJO_REWARD_NPC_NARRATION,			// �����ϼ̽��ϴ�. ����� ���İ� ���� �ְ��Դϴ�!!(���� ��Ż�� ������ �̱������� ����� NPC ���)

	// ����
	DST_DOGI_MUST_REGI_DOGI_SLOT,			// ���� ���� �������� ���Կ� ����� �ֽʽÿ�(����GUI���� ������ ������ �ٲٷ��� �� ��)
	DST_DOGI_CHANGED,						// ������ ����Ǿ����ϴ�(������ ����Ǿ����� �˸���)
	DST_DOGI_ASK_APPLY_CHANGE,				// ���� ���� ������ �Ϸ��Ͻðڽ��ϱ�?(Msgbox : ���� ���� ������ �������� ��� ��)
	DST_DOJO_DOGI_ASK_APPLY_CHANGE,			// ���� ���� ������ �Ϸ��Ͻðڽ��ϱ�?(Msgbox : ���� ���� ������ �������� ��� ��)
	DST_DOGI_ONLY_REGISTER_DOGI_ITEM,		// ������ ����� �� �ֽ��ϴ�(�������� ���� ���� GUI�� ����Ϸ� �� ��)

	// Etc
	DST_POPOSTONE_RESURRECT_SAY,			// ����� �����Ѱž�. �����ؼ� �ൿ�� (���������Ȱ�� ��ǳ��)

	DST_ASK_CHANGE_CHANNEL,					// ä���� �����Ͻðڽ��ϱ�?(MsgBox : ä�� ���������� �����)
	DST_ALREADY_SAME_CHANNEL,				// �̹� ������ ä���� �����ϼ̽��ϴ�(������ ä���� �����Ϸ��� �� ��)

	DST_NOT_SELECTED_SLOT,					// ������ ������ �����ϴ�(��� �۾��� �Ϸ� �� �� ������ ������ ��� �� �� ����)

	DST_LOBBY_ENABLE_LOCAL_TEXT,			// �ϼ��� �ѱ۰� ����, ��� ����� �� �ֽ��ϴ�(ĳ����, ��Ƽ, ��� �̸��� ������ ��/�� �ٸ� ������ �ʿ���)

	DST_LOBBY_NO_HAVE_ZENNY,				// ������ ����

	DST_CHAR_GROWN_UP,						// ĳ���Ͱ� �����Ҷ��� �޽���. Notify��
	DST_CHAR_CAN_CHANGE_CLASS,				// ������ �� ���� ���� �޽���. Notify��

	// ���Ⱓ ���� MsgBox ����
	DST_COMMERCIAL_MB_UPDATE_TERM_LIMETED_ITEM_MSG,	// HTML, %s�� ��� �Ⱓ�� ����Ǿ� ����� �����Ǿ����ϴ�.
	DST_COMMERCIAL_MB_DELETE_TERM_LIMETED_ITEM_MSG, // HTML, %s�� ��� �Ⱓ�� ����� �������Դϴ�.\n�Ⱓ������ ���� �ʰ� �����ðڽ��ϱ�?
	DST_COMMERCIAL_MB_USE_TERM_LIMETED_ITEM_MSG,	// HTML, %s�� ��� �Ⱓ�� ����� �������Դϴ�.\n�Ⱓ������ ��û�Ͻðڽ��ϱ�?
	DST_COMMERCIAL_TERM_LIMITED_ITEM_WARNING_MSG,	// %s ��� �Ⱓ �� ����˴ϴ�.

	// ���ǵ�� ǥ��
	DST_DELIBERATION_RANK_MESSAGE,			// ������ ���ǵ�� ǥ�� ����

	// ������
	DST_QUICKSLOT_IS_LOCK,					// �������� �������Դϴ�. 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// UI Display Text _ UI�� ǥ���ϱ� ���� �ؽ�Ʈ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��  ��
	DST_GUILD,								// ����
	DST_RACE,								// ����
	DST_RECORD,								// ����
	DST_NOT_JOINED_GUILD,					// ���� ����


	// �巡�ﺼ �÷��� ����
	DST_DBC_ITEM_CONFIRM,					// [UIǥ�ÿ�]������ �����ðڽ��ϱ�
	DST_DBC_ITEM_OK,						// Ȯ��
	DST_DBC_ITEM_BACK,						// ���ư���
	DST_DBC_TIME_LIMIT,						// ���ѽð�	
	DST_DBC_SEASON,							// �巡�ﺼ �÷��� �̺�Ʈ ������
	DST_DBC_NO_SEASON,						// �巡�ﺼ �÷��� �̺�Ʈ �Ⱓ�� �ƴմϴ�
	DST_DBC_COLLECT_COMPLETE,				// �巡�ﺼ ���� �ޱ�
	DST_DBC_REWARD_COMMENT,					// ����� �巡�ﺼ �������� ������ �����ʽÿ�.
	DST_DBC_KEYWORD,						// �ֹ�	

	// Pet Status
	DST_PET_TOOLTIP_ATTACK,                     // Ÿ������ ������ ���� �����մϴ�.

	// Option
	DST_OPTION_TITLE,						// �ɼ� ����
	DST_OPTION_RESET,						// �⺻��
	DST_OPTION_OK,							// ����
	DST_OPTION_CANCEL,						// ���
	DST_OPTION_TAB_SYSTEM,					// �ý���
	DST_OPTION_TAB_GAME,					// ����
	DST_OPTION_TAB_SYSTEM_GRAPHIC,			// �Ϲ�(�׷���)
	DST_OPTION_TAB_SYSTEM_EFFECT,			// ȿ��
	DST_OPTION_TAB_SYSTEM_SOUND,			// �Ҹ�
	DST_OPTION_TAB_GAME_CONTROL,			// ����Ű
	DST_OPTION_TAB_GAME_INFO,				// �Ϲ�(����)
	DST_OPTION_TAB_GAME_ETC,				// ��Ÿ
	DST_OPTION_TAB_GAME_CHATTING,			// ä��
	DST_OPTION_GRAPHIC_RESOLUTION_TITLE,	// �ػ� ����
	DST_OPTION_GRAPHIC_RESOLUTION,			// �ػ�
	DST_OPTION_GRAPHIC_GAMMA,				// ���
	DST_OPTION_GRAPHIC_WINDOWMODE,			// â ���
	DST_OPTION_GRAPHIC_TITLE,				// ȿ��
	DST_OPTION_GRAPHIC_QUALITY_TOTAL,		// ��ü �׷��� ǰ��
	DST_OPTION_GRAPHIC_QUALITY_LOW,			// ����
	DST_OPTION_GRAPHIC_QUALITY_MIDDLE,		// ����
	DST_OPTION_GRAPHIC_QUALITY_HIGH,		// ����
	DST_OPTION_GRAPHIC_QUALITY_USER,		// �����
	DST_OPTION_GRAPHIC_QUALITY_TERRAIN_RANGE,	// ���� �þ߰Ÿ�
	DST_OPTION_GRAPHIC_QUALITY_OBJECT_RANGE,	// �繰 �þ߰Ÿ�
	DST_OPTION_GRAPHIC_TERRAIN_SHADOW,			// ���� �׸���
	DST_OPTION_GRAPHIC_WATER_EFFECT,		// �� ȿ��
	DST_OPTION_GRAPHIC_CHARACTER_RANGE,		// ĳ���� �þ߰Ÿ�
	DST_OPTION_GRAPHIC_CHARACTER_SHADOW,	// ĳ���� �׸���
	DST_OPTION_GRAPHIC_MAGIC_EFFECT,		// ���� ����ȿ��
	DST_OPTION_GRAPHIC_WEATHER_EFFECT,		// ���� ȿ��
	DST_OPTION_GRAPHIC_TEXTURE_QUALITY,		// �ؽ��� �ػ�
	DST_OPTION_GRAPHIC_CHARACTER_EFFECT,	// ĳ���� ȿ��
	DST_OPTION_GRAPHIC_CARTOON_EDGE,		// ī���� �ܰ���
	DST_OPTION_GRAPHIC_UPGRADE_EFFECT,		// ���׷��̵� ȿ��
	DST_OPTION_GRAPHIC_ETC_TITLE,			// ��Ÿ ȿ��
	DST_OPTION_GRAPHIC_HDR_EFFECT,			// HDR ȿ��
	DST_OPTION_SOUND_MAIN,					// ���� ����
	DST_OPTION_SOUND_BGM,					// ��� ����
	DST_OPTION_SOUND_SE,					// ȿ�� ����
	DST_OPTION_SOUND_ENV,					// ȯ�� ����
	DST_OPTION_INFO_GUILDEMBLEM,			// ��� ����
	DST_OPTION_INFO_DOJOMARK,				// ���� ��ũ
	DST_OPTION_INFO_SCOUTERMODEL,			// ��ī��Ʈ ��
	DST_OPTION_ETC_FRIENDCONNECT,			// ģ�� ����
	DST_OPTION_ETC_GUILDCONNECT,			// ��� ��� ����
	DST_OPTION_ETC_QUESTEFFECT,				// ����Ʈ �ؽ�Ʈ ȿ��
	DST_OPTION_ETC_USERTRADE,				// ���� �ŷ�
	DST_OPTION_ETC_WINDOWMOVE,				// ������ ���� �ɼ�
	DST_OPTION_ETC_WINDOWMOVE_DEFAULT,		// ������ ��ġ�� �����Ƿ�
	DST_OPTION_ETC_MOUSEDASH,				// ���콺 ��� ����
	DST_OPTION_ETC_EX_QUICKSLOT1,			// �߰� ������ 1
	DST_OPTION_ETC_EX_QUICKSLOT2,			// �߰� ������ 2
	DST_OPTION_ETC_EX_QUICKSLOT_LOCK,		// ������ ��ױ�
	DST_OPTION_RADIO_ON,					// On
	DST_OPTION_RADIO_OFF,					// Off
	DST_OPTION_RESOLUTION_FORMAT,			// %d * %d * %dbit
	DST_OPTION_RESOLUTION_FORMAT_WINMODE,	// %d * %d

	// Control Option Window
	DST_OPTION_CONTROL_TEXT_TITLE,			// ����Ű ����
	DST_OPTION_CONTROL_TEXT_GUIDE,			// ����Ű�� �ߺ��� ��� ���� ����Ű�� [%s] ���°� �˴ϴ�.
	DST_OPTION_CONTROL_TEXT_CHANGEGUIDE,	// [%s]�� �ߺ��˴ϴ�. [%s]�� [%s]���� ����˴ϴ�.
	DST_OPTION_CONTROL_TEXT_READYGUIDE,		// ����� Ű�� �Է��ϼ���.
	DST_OPTION_CONTROL_TEXT_WAITGUIDE,		// ����� Ű�� ���ų� ���� ������ �� �����ϴ�. ��ø� ��ٷ� �ֽʽÿ�.
	DST_OPTION_CONTROL_TEXT_NOTCHANGEGUIDE, // %s Ű�� ������ �Ұ����մϴ�.
	DST_OPTION_CONTROL_TEXT_FIXEDKEYGUIDE,	// �Է��Ͻ� Ű�� ������ ���Ƿ� ����� �� ���� [������ Ű] �Դϴ�.
	DST_OPTION_CONTROL_TEXT_NOTCOMBINEGUIDE,// ���� Ű�δ� ����� �� ���� �׼��Դϴ�.
	DST_OPTION_CONTROL_TEXT_SAMEKEYGUIDE,	// ������ �ִ� Ű�� ���� Ű�Դϴ�.
	DST_OPTION_CONTROL_TEXT_NEGATIVEMODEGUIDE,	// ���� ��忡���� Ű ������ �Ұ����մϴ�.
	DST_OPTION_CONTROL_TEXT_EMPTYKEY,		// �����ȵ� 


	DST_OPTION_CONTROL_CATEGORY_AVATAR,		// �ƹ�Ÿ �ൿ(ī�װ�)
	DST_OPTION_CONTROL_CATEGORY_TARGET,		// Ÿ�� �ൿ
	DST_OPTION_CONTROL_CATEGORY_QUICKSLOT,	// ������ �ൿ
	DST_OPTION_CONTROL_CATEGORY_WINDOW,		// ������ �ൿ
	DST_OPTION_CONTROL_CATEGORY_FIXED,		// ����(����Ű ���� �Ұ���)

	DST_OPTION_CONTROL_ACTION_AVATAR_FORWARD,	// ����
	DST_OPTION_CONTROL_ACTION_AVATAR_BACKWARD,	// ����
	DST_OPTION_CONTROL_ACTION_AVATAR_LEFTTURN,	// ��ȸ��
	DST_OPTION_CONTROL_ACTION_AVATAR_RIGHTTURN,	// ��ȸ��
	DST_OPTION_CONTROL_ACTION_AVATAR_SITDOWN,	// �ȱ�/�Ͼ��
	DST_OPTION_CONTROL_ACTION_AVATAR_JUMP,		// ����
	DST_OPTION_CONTROL_ACTION_AVATAR_AUTORUN,	// �ڵ��޸���
	DST_OPTION_CONTROL_ACTION_AVATAR_SCOUTER,	// ��ī���� ���
	DST_OPTION_CONTROL_ACTION_AVATAR_CHARGE,	// �� ������
	DST_OPTION_CONTROL_ACTION_AVATAR_LOOTING,	// ������ �ݱ�
	DST_OPTION_CONTROL_ACTION_AVATAR_BLOCKING,	// ���ŷ

	DST_OPTION_CONTROL_ACTION_TARGET_SELF,		// �ڽ� ����
	DST_OPTION_CONTROL_ACTION_TARGET_1STPARTY,	// ù��° ��Ƽ�� ����
	DST_OPTION_CONTROL_ACTION_TARGET_2NDPARTY,	// �ι�° ��Ƽ�� ����
	DST_OPTION_CONTROL_ACTION_TARGET_3RDPARTY,	// ����° ��Ƽ�� ����
	DST_OPTION_CONTROL_ACTION_TARGET_4THPARTY,	// �׹�° ��Ƽ�� ����
	DST_OPTION_CONTROL_ACTION_TARGET_AUTO,		// ����� �� ����
	DST_OPTION_CONTROL_ACTION_TARGET_AUTOATK,	// �ڵ� ����
	DST_OPTION_CONTROL_ACTION_TARGET_AUTOFOLLOW,// �ڵ� ���󰡱�
	DST_OPTION_CONTROL_ACTION_TARGET_MARKING1,	// ���� Ÿ��1 ����
	DST_OPTION_CONTROL_ACTION_TARGET_MARKING2,	// ���� Ÿ��2 ����
	DST_OPTION_CONTROL_ACTION_TARGET_MARKING3,	// ���� Ÿ��3 ����
	DST_OPTION_CONTROL_ACTION_TARGET_MARKING4,	// ���� Ÿ��4 ����
	DST_OPTION_CONTROL_ACTION_TARGET_MARKING5,	// ���� Ÿ��5 ����
	DST_OPTION_CONTROL_ACTION_TARGET_SELECTING1,// ���� Ÿ��1 ����
	DST_OPTION_CONTROL_ACTION_TARGET_SELECTING2,// ���� Ÿ��2 ����
	DST_OPTION_CONTROL_ACTION_TARGET_SELECTING3,// ���� Ÿ��3 ����
	DST_OPTION_CONTROL_ACTION_TARGET_SELECTING4,// ���� Ÿ��4 ����
	DST_OPTION_CONTROL_ACTION_TARGET_SELECTING5,// ���� Ÿ��5 ����
	DST_OPTION_CONTROL_ACTION_TARGET_AUTOPARTY,	// ��Ƽ�� �ڵ� ����

	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK1,	// ������ 1��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK2,	// ������ 2��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK3,	// ������ 3��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK4,	// ������ 4��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK5,	// ������ 5��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK6,	// ������ 6��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK7, // ������ 7��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK8,	// ������ 8��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK9,	// ������ 9��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK0,	// ������ 0��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICKMIN,	// ������ -
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICKPLUS,	// ������ +
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK1_EX,	// ������ 1�� (Ȯ�� 1��)
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK2_EX,	// ������ 2��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK3_EX,	// ������ 3��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK4_EX,	// ������ 4��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK5_EX,	// ������ 5��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK6_EX,	// ������ 6��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK7_EX, // ������ 7��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK8_EX,	// ������ 8��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK9_EX,	// ������ 9��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK0_EX,	// ������ 0��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICKMIN_EX,	// ������ -
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICKPLUS_EX,	// ������ +
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK1_EX2,	// ������ 1�� (Ȯ�� 2��)
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK2_EX2,	// ������ 2��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK3_EX2,	// ������ 3��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK4_EX2,	// ������ 4��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK5_EX2,	// ������ 5��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK6_EX2,	// ������ 6��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK7_EX2, // ������ 7��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK8_EX2,	// ������ 8��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK9_EX2,	// ������ 9��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICK0_EX2,	// ������ 0��
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICKMIN_EX2,	// ������ -
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_QUICKPLUS_EX2,	// ������ +
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_PREV,	// ���� ������
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_NEXT,	// ���� ������
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_2NDCAP,	// 2�� ĸ��ŰƮ
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_3RDCAP,	// 3�� ĸ��ŰƮ
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_4THCAP,	// 4�� ĸ��ŰƮ
	DST_OPTION_CONTROL_ACTION_QUICKSLOT_5THCAP,	// 5�� ĸ��ŰƮ

	DST_OPTION_CONTROL_ACTION_WINDOW_PROFILE,	// ĳ��������
	DST_OPTION_CONTROL_ACTION_WINDOW_SKILL,		// ��ų����
	DST_OPTION_CONTROL_ACTION_WINDOW_QUEST,		// ����Ʈ ����
	DST_OPTION_CONTROL_ACTION_WINDOW_MINIMAP,	// �̴ϸ�
	DST_OPTION_CONTROL_ACTION_WINDOW_WORLDMAP,	// �����
	DST_OPTION_CONTROL_ACTION_WINDOW_MAINCAP,	// ���� ĸ��ŰƮ
	DST_OPTION_CONTROL_ACTION_WINDOW_SCOUTER,	// ��ī���� ����
	DST_OPTION_CONTROL_ACTION_WINDOW_PARTY,		// ��Ƽ ����
	DST_OPTION_CONTROL_ACTION_WINDOW_GUILD,		// ��� ����
	DST_OPTION_CONTROL_ACTION_WINDOW_FRIEND,	// ģ�� ����
	DST_OPTION_CONTROL_ACTION_WINDOW_OPTION,	// �ɼ�
	DST_OPTION_CONTROL_ACTION_WINDOW_HELP,		// ����
	DST_OPTION_CONTROL_ACTION_WINDOW_MAIN,		// ���θ޴�
	DST_OPTION_CONTROL_ACTION_WINDOW_RANKBOARD,	// ��ũ����

	DST_OPTION_CONTROL_ACTION_MINIMAP_ZOOMOUT,	// �̴ϸ� ���
	DST_OPTION_CONTROL_ACTION_MINIMAP_ZOOMIN,	// �̴ϸ� Ȯ��
	DST_OPTION_CONTROL_ACTION_CHAT_PGUP,		// ä��â ���� ������
	DST_OPTION_CONTROL_ACTION_CHAT_PGDN,		// ä��â ���� ������
	DST_OPTION_CONTROL_ACTION_GLOBAL_CANCLE,	// ���
	DST_OPTION_CONTROL_ACTION_GLOBAL_SNAPSHOT,	// ��ũ����
	DST_OPTION_CONTROL_ACTION_GLOBAL_CHAT,		// ä�� �Է�

	// Chatting Option
	DST_OPTION_CHATTING_TITLE_COMMON,			// ���� �ɼ�
	DST_OPTION_CHATTING_COMMON_INPUTMODE,		// ä��â �Է¸��
	DST_OPTION_CHATTING_COMMON_LOCK,			// ä��â ���
	DST_OPTION_CHATTING_COMMON_SCROLL,			// ���콺 ��ũ��
	DST_OPTION_CHATTING_COMMON_ADDEDWINDOW,		// �߰� ������
	DST_OPTION_CHATTING_COMMON_OPACITY,			// ������ ����

	DST_OPTION_CHATTING_TITLE_BASIC,			// �⺻ ä��â
	DST_OPTION_CHATTING_BASIC_NORMAL,			// �Ϲ� ��ȭ
	DST_OPTION_CHATTING_BASIC_WISPHER,			// �ӼӸ�
	DST_OPTION_CHATTING_BASIC_PARTY,			// ��Ƽ
	DST_OPTION_CHATTING_BASIC_GUILD,			// ���
	DST_OPTION_CHATTING_BASIC_TRADE,			// �ŷ�
	DST_OPTION_CHATTING_BASIC_SHOUT,			// ��ġ��
	DST_OPTION_CHATTING_BASIC_SYSTEM,			// �ý���

	DST_OPTION_CHATTING_TITLE_ADDED,			// �⺻ ä��â
	DST_OPTION_CHATTING_ADDED_NORMAL,			// �Ϲ� ��ȭ
	DST_OPTION_CHATTING_ADDED_WISPHER,			// �ӼӸ�
	DST_OPTION_CHATTING_ADDED_PARTY,			// ��Ƽ
	DST_OPTION_CHATTING_ADDED_GUILD,			// ���
	DST_OPTION_CHATTING_ADDED_TRADE,			// �ŷ�
	DST_OPTION_CHATTING_ADDED_SHOUT,			// ��ġ��
	DST_OPTION_CHATTING_ADDED_SYSTEM,			// �ý��� 

	DST_OPTION_TOOLTIP_TAB_GRAPHIC,				// �׷��� �ɼ��� �����մϴ�. ( �ý���-�׷��� ī�װ��� ���� )
	DST_OPTION_TOOLTIP_RESOLUTION,				// ���� �ػ󵵸� �����մϴ�.
	DST_OPTION_TOOLTIP_GAMMA,					// ������ ��⸦ �����մϴ�. ��üȭ�� ��忡���� ��� �� �� �ֽ��ϴ�.
	DST_OPTION_TOOLTIP_WINDOWMODE,				// ������ ȭ�� ��带 �����մϴ�.
	DST_OPTION_TOOLTIP_GRAPHIC_QUALITY,			// ��ü���� �׷��� ǰ���� �����մϴ�.
	DST_OPTION_TOOLTIP_TERRAIN_DISTANCE,		// ���� �þ߰Ÿ��� �����մϴ�.
	DST_OPTION_TOOLTIP_OBJECT_DISTANCE,			// �繰 �þ߰Ÿ��� �����մϴ�.
	DST_OPTION_TOOLTIP_TERRAIN_SHADOW,			// ���� �׸����� ��� ��/���� �����մϴ�.
	DST_OPTION_TOOLTIP_WATER_EFFECT,			// �� ȿ���� ��� ��/���� �����մϴ�.

	DST_OPTION_TOOLTIP_CHARACTER_DISTANCE,		// ĳ���� �þ߰Ÿ��� �����մϴ�.
	DST_OPTION_TOOLTIP_SHADOW,					// ĳ������ �׸��� ��� ��/���� �����մϴ�.
	DST_OPTION_TOOLTIP_MAGIC_DETAIL,			// ���� ����ȿ���� ǰ���� �����մϴ�.
	DST_OPTION_TOOLTIP_WEATHER_EFFECT,			// ���� ȿ���� ǰ���� �����մϴ�.
	DST_OPTION_TOOLTIP_TEXTURE_LEVEL,			// �ؽ����� ǰ���� �����մϴ�. �ý����� ������ؾ����� ����˴ϴ�.
	DST_OPTION_TOOLTIP_CARTOON_EDGE,			// ī���� �ܰ����� ��� ��/���� �����մϴ�.
	DST_OPTION_TOOLTIP_UPGRADE_EFFECT,			// ĳ���� ���׷��̵� ȿ���� ��� ��/���� �����մϴ�.
	DST_OPTION_TOOLTIP_HDR,						// HDR ȿ���� ��� ��/���� �����մϴ�.

	DST_OPTION_TOOLTIP_TAB_SOUND,				// ���� �� ���� ���� �ɼ��� �����մϴ�. ( �ý���-���� )
	DST_OPTION_TOOLTIP_MAINVOLUME,				// ��ü ������ �����մϴ�.
	DST_OPTION_TOOLTIP_BGMVOLUME,				// ��� ���� ������ �����մϴ�.
	DST_OPTION_TOOLTIP_EFFECTVOLUME,			// ȿ���� ������ �����մϴ�.
	DST_OPTION_TOOLTIP_ENVVOLUME,				// ȯ���� ������ �����մϴ�.

	DST_OPTION_TOOLTIP_TAB_CONTROL,				// ���� �� ����Ű �ɼ��� �����մϴ�. ( ����-���� )

	DST_OPTION_TOOLTIP_TAB_INFO,				// ���� �� ���� ǥ�� �ɼǵ��� �����մϴ�. ( ����-���� )
	DST_OPTION_TOOLTIP_GUILD_EMBLEM,			// ���� ���� ��� ��/���� �����մϴ�.
	DST_OPTION_TOOLTIP_DOJO_MARK,				// ���� ��ũ�� ��� ��/���� �����մϴ�.
	DST_OPTION_TOOLTIP_SCOUTER,					// �ƹ�Ÿ�� ��ī���� �� ǥ�� ��/���� �����մϴ�.

	DST_OPTION_TOOLTIP_TAB_ETC,					// ���� �� ������ �ɼǵ��� �����մϴ�. ( ����-��Ÿ )

	DST_OPTION_TOOLTIP_FRIEND_CONNECT,			// ģ���� ������ �ϸ� �̺�Ʈ�� �˷��ݴϴ�.
	DST_OPTION_TOOLTIP_MEMBER_CONNECT,			// ���ϻ��� ������ �ϸ� �̺�Ʈ�� �˷��ݴϴ�.
	DST_OPTION_TOOLTIP_QUEST_TEXT,				// ����Ʈ �ؽ�Ʈ ȿ���� �����մϴ�.
	DST_OPTION_TOOLTIP_TRADE,					// �ŷ� ���� ���θ� �����մϴ�.
	DST_OPTION_TOOLTIP_WINDOW_MOVEABLE,			// UI ������ �̵� ���θ� �����մϴ�.
	DST_OPTION_TOOLTIP_WINDOW_DEFAULT,			// UI �����츦 �⺻ ��ġ�� �̵��մϴ�.
	DST_OPTION_TOOLTIP_MOUSE_DASH,				// ���콺�� ��ø� �ϴ� Ÿ���� �����մϴ�.
	DST_OPTION_TOOLTIP_EX_QUICKSLOT1,			// �߰� ������ 1�� ���� ����� ��� ���θ� �����մϴ�.
	DST_OPTION_TOOLTIP_EX_QUICKSLOT2,			// �߰� ������ 2�� ���� ����� ��� ���θ� �����մϴ�.
	DST_OPTION_TOOLTIP_QUICKSLOT_LOCK,			// �������� ��� ������ �� �߱� ������ �����մϴ�.

	DST_OPTION_TOOLTIP_TAB_CHATTING,			// ���� �� ä�� �ɼ��� �����մϴ�. ( ����-ä�� )
	DST_OPTION_TOOLTIP_CHAT_INPUTMODE,			// ä�� �Է¸�� ����
	DST_OPTION_TOOLTIP_CHAT_LOCK,				// ä��â ��� ����
	DST_OPTION_TOOLTIP_CHAT_MOUSESCROLL,		// ���콺 ��ũ�� ����
	DST_OPTION_TOOLTIP_CHAT_ADDED_WINDOW,		// �߰� ������ ����
	DST_OPTION_TOOLTIP_CHAT_WINDOW_OPACITY,		// ������ ���� ����
	DST_OPTION_TOOLTIP_CHAT_NORMAL,				// �Ϲݴ�ȭ ����
	DST_OPTION_TOOLTIP_CHAT_WHISPER,			// �ӼӸ� ����
	DST_OPTION_TOOLTIP_CHAT_PARTY,				// ��Ƽ�� ����
	DST_OPTION_TOOLTIP_CHAT_GUILD,				// ��帻 ����
	DST_OPTION_TOOLTIP_CHAT_TRADE,				// �ŷ��� ����
	DST_OPTION_TOOLTIP_CHAT_SHOUT,				// ��ġ�� ����
	DST_OPTION_TOOLTIP_CHAT_SYSTEM,				// �ý��۸� ����

	// Help Window(Guide Book)
	DST_HELPWND_TITLE,						// �巡�ﺼ �¶��� ���̵�
	DST_HELPWND_TOP_TITLE,					// �巡�ﺼ �¶��� ����
	DST_HELPWND_HELPCONTENTS,				// ���� ����
	DST_HELPWND_GOLIST,						// ������ �̵�
	DST_HELPWND_PETITION_TO_GM,				// GM���

	// SideIcon : HelpHintView
	DST_SIDEICON_HINT_HELP_MORE,			// �ٷ� ����(���� ������ �ٷΰ��� ��ư)

	// SideIcon : PoPo Icon
	DST_SIDEICON_HINT_FRIEND_TITLE,			// ģ�� ����(Ÿ��Ʋ)
	DST_SIDEICON_HINT_FRIEND_TEXT,			// %s���� �����ϼ̽��ϴ�.
	DST_SIDEICON_HINT_SKILL_UPGRADE_TITLE,	// ��ų ���׷��̵� (Ÿ��Ʋ)
	DST_SIDEICON_HINT_SKILL_UPGRADE_TEXT,	// %s�� ���׷��̵� �� �� �ֽ��ϴ�.
	DST_SIDEICON_HINT_NEWMAIL_TITLE,		// ���� ����(Ÿ��Ʋ)
	DST_SIDEICON_HINT_NEWMAIL_TEXT,			// ���ο� ������ �����Ͽ����ϴ�.
	DST_SIDEICON_HINT_CLASS_CHANGE_TITLE,	// ���� ����(Ÿ��Ʋ)
	DST_SIDEICON_HINT_CLASS_CHANGE_TEXT,	// ���� Ŭ������ ü���� �� �� �ֽ��ϴ�.

	// PrivateShop Text
	DST_PRIVATESHOP_SHOPNAME,				// �����̸�
	DST_PRIVATESHOP_NOTICE,					// �˸��� ��
	DST_PRIVATESHOP_AWAY,					// �ڸ����
	DST_PRIVATESHOP_TAB_BUY_1,				// ��ǰ
	DST_PRIVATESHOP_TAB_BUY_2,				// �ΰ�����
	DST_PRIVATESHOP_TAB_SELL_1,				// ��ǰ
	DST_PRIVATESHOP_TAB_SELL_2,				// ����
	DST_PRIVATESHOP_SHOPNAME_EMPTY,			// [Charater Name]�� ���λ���
	DST_PRIVATESHOP_SALE_START,				// �ǸŽ���
	DST_PRIVATESHOP_SALE_STOP,				// �Ǹ�����
	DST_PRIVATESHOP_ZENNY,					// ������

	DST_PRIVATESHOP_NOTICE_FOOT,			// by %s
	DST_PRIVATESHOP_ITEM_NOT_IDENTIFICATION,// ��Ȯ�� ������

	DST_PRIVATESHOP_NAMETAG_READY,			// ���λ��� �غ���
	DST_PRIVATESHOP_NAMETAG_AWAY,			// [�ڸ����]

	DST_PRIVATESHOP_EMPTY_SLOT,				// ��� ǰ���� �ȷȽ��ϴ�.

	// PrivateShop Business Text
	DST_PRIVATESHOP_BUSINESS_WAITREQUEST,	// ������ ������ ��ٸ��� ���Դϴ�.
	DST_PRIVATESHOP_BUSINESS_CONSENT,		// %s���� %s�� ������ ��û�ؿԽ��ϴ�. �����Ͻðڽ��ϱ�?

	// PrivateShop Business Trade Gui
	DST_PRIVATESHOP_BUSINESS_TRADE_TITLE,		// ������ ���� ����
	DST_PRIVATESHOP_BUSINESS_TRADE_ITEMTITLE,	// �������� ������
	DST_PRIVATESHOP_BUSINESS_TRADE_ITEMPRICE,	// ���� ����
	DST_PRIVATESHOP_BUSINESS_TRADE_CHAT,		// ä��
	DST_PRIVATESHOP_BUSINESS_TRADE_APPLYPRICE,	// ������ ������ ����Ǿ����ϴ�.
	DST_PRIVATESHOP_BUSINESS_TRADE_APPLYNOTIFY,	// ������ �����Ǿ����ϴ�.
	DST_PRIVATESHOP_BUSINESS_TRADE_REALLYBUY,	// ���� �����Ͻðڽ��ϱ�?

	// PrivateShopBusiness Trade Box
	DST_PRIVATESHOP_BUSINESS_TRADE_IMMEDIATE,	// ��� ����
	DST_PRIVATESHOP_BUSINESS_TRADE_FLUCTUATIONS,		// ���� ����

	// PrivateShopBusiness TradeBox Gui
	DST_PRIVATESHOP_BUSINESS_TRADEBOX_TITLE,				// ���� ����
	DST_PRIVATESHOP_BUSINESS_TRADEBOX_FLUCTUATIONS,			// ���� �������� �̷��� �����մϴ�.
	DST_PRIVATESHOP_BUSINESS_TRADEBOX_PREVPRICE,			// ���� �� ����
	DST_PRIVATESHOP_BUSINESS_TRADEBOX_NEXTPRICE,			// ���� �� ����
	DST_PRIVATESHOP_BUSINESS_TRADEBOX_ACCEPT,				// ����
	DST_PRIVATESHOP_BUSINESS_TRADEBOX_CANCEL,				// ���

	// PrivateShop Cart Text
	DST_PRIVATESHOP_CART_BUY,				// ���
	DST_PRIVATESHOP_CART_PRICE,				// �� ���� �ݾ�

	// MailSystem Text
	DST_MAILSYSTEM_STATUS,						// ���Ϲڽ�
	DST_MAILSYSTEM_STATUS_UNREAD,				// ���� ���� ������ %u�� �ֽ��ϴ�.
	DST_MAILSYSTEM_STATUS_FULL,					// �������� ���ſ뷮�� �ʰ��Ͽ����ϴ�.
	DST_MAILSYSTEM_MAILBOX,						// ���Ϲڽ�

	DST_MAILSYSTEM_TAB_MAILBOX,					// ���Ϲڽ�
	DST_MAILSYSTEM_TAB_SENDMAIL,				// ���Ͼ���
	DST_MAILSYSTEM_TAB_READMAIL,				// �����б�
	DST_MAILSYSTEM_MAIL_EMPTYMAIL,				// ������ �� �뵵 �����ϴ�.
	DST_MAILSYSTEM_MAIL_EXPIRED_DAY_TITLE,		// ���� �Ⱓ
	DST_MAILSYSTEM_MAIL_EXPIRED_DAY,			// %u ��
	DST_MAILSYSTEM_MAIL_EXPIRED_DAY_LOCK,		// ���
	DST_MAILSYSTEM_MAIL_TO,						// �޴»��
	DST_MAILSYSTEM_MAIL_FROM,					// ���� ���
	DST_MAILSYSTEM_MAIL_CONTENT,				// ���� ����
	DST_MAILSYSTEM_MAIL_ATTACH,					// ÷���ϱ�
	DST_MAILSYSTEM_MAIL_ATTACH_2,				// ÷�ε� ������
	DST_MAILSYSTEM_MAIL_ATTACH_SEND,			// �۱��ϱ� 
	DST_MAILSYSTEM_MAIL_ATTACH_REQ,				// û���ϱ�
	DST_MAILSYSTEM_MAIL_SEND,					// ������
	DST_MAILSYSTEM_MAIL_RESET,					// �ٽþ���
	DST_MAILSYSTEM_MAIL_AWAY,					// �ڸ����
	DST_MAILSYSTEM_MAIL_AWAY_ON,				// ���� ���������� �����Ǿ� ������, �ٸ� �÷��̾�κ��� ������ �������� �ʽ��ϴ�.
	DST_MAILSYSTEM_MAIL_AWAY_OFF,				// ���� ���� ������ ������ �����Դϴ�.
	DST_MAILSYSTEM_MAIL_REPLY,					// �����ϱ�
	DST_MAILSYSTEM_MAIL_RETURN,					// �ݼ��ϱ�
	DST_MAILSYSTEM_MAIL_DELETE,					// �����

	DST_MAILSYSTEM_MAIL_ZENNY,					// �ݾ�
	DST_MAILSYSTEM_MAIL_ZENNY_SEND,				// ��ü�ݾ�
	DST_MAILSYSTEM_MAIL_ZENNY_REQ,				// û���ݾ�

	DST_MAILSYSTEM_MAIL_SENDDATE,				// %u�� %u�� %u�� %s %u�� %u��

	DST_MAILSYSTEM_NOT_IDENTIFICATION,			// ��Ȯ��
	DST_MAILSYSTEM_NOT_IDENTIFICATION_ITEM,		// ��Ȯ�� ������

	DST_MAILSYSTEM_TOOLTIP_NOT_ATTACH,			// ÷���� �������� ���Կ� ����ϼ���
	DST_MAILSYSTEM_TOOLTIP_EXPIREDDAY,			// �ش� �Ⱓ�� ������ �� ������ �ݼ� �Ǵ� �ڵ����� �˴ϴ�.
	DST_MAILSYSTEM_TOOLTIP_ATTACHACTION,		// ÷�ε� ��ǰ�� �ްų� ���� �մϴ�.
	DST_MAILSYSTEM_TOOLTIP_RELOAD,				// ���ΰ�ħ : 1�и��� Ȱ��ȭ ��ų �� �ֽ��ϴ�.

	DST_MAILSYSTEM_ATTACH_DISABLED_MSG,			// ��������Ĩ�� �����ϰų� ��ü���� �̿��Ͽ� �ֽʽÿ�.

	DST_MAILSYSTEM_NEGATIVE_CHECK_LOCK,			// ����� ������ ������ �� �����ϴ�.
	DST_MAILSYSTEM_NEGATIVE_CHECK_ATTACH,		// ÷�ε� ��ǰ�� �ִ� ������ ������ �� �����ϴ�.

	// Skill Gui, Skill Info
	DST_SKILL_HAVE_MORE_EFFECT,		// �� %d�� ȿ��
	DST_SKILL_CONSUME_TEXT,			// �Ҹ�/
	DST_SKILL_LP_CONSUMPTION,		// LP�Ҹ�
	DST_SKILL_EP_CONSUMPTION,		// EP�Ҹ�
	DST_SKILL_RP_CONSUMPTION,		// RP�Ҹ�
	DST_SKILL_GRADE,				// ���ǥ��
	DST_SKILL_GRADE_MASTERED,		// �����͵��
	DST_SKILL_NOT_LEARN,			// ��ų�� ����� �ʾҴ�.
	DST_SKILL_READY_LEARN,			// ��ų�� ��� �� �ִ�.
	DST_SKILL_READY_UPGRADE,		// ��ų ���׷��̵尡 �����ϴ�.
	DST_SKILL_CANT_LEARN,			// ��ų�� ��� �� ����.
	DST_SKILL_ALREADY_LEARNED,		// �̹� ��ų�� �����.
	DST_SKILL_CANT_LEARN_FOREVER,	// ��� �� ���� ��ų�Դϴ�.
	DST_SKILL_MASTERED,				// ��ų�� �������ߴ�.
	DST_SKILL_TYPE_PASSIVE,			// ��ųŸ��
	DST_SKILL_TYPE_ACTIVE,			
	DST_SKILL_TYPE_HTB,	
	DST_SKILL_CASTTIME,				// �����ð�
	DST_SKILL_DURATIONTIME,			// ���ӽð�
	DST_SKILL_COOLTIME,				// ��Ÿ��	
	DST_SKILL_USERANGE,				// ���Ÿ�
	DST_SKILL_EXP,					// ���õ�
	DST_SKILL_SP,					// ��ų����Ʈ : %u

	DST_SKILL_NEED_TEXT,			// ��������
	DST_SKILL_NEED_LEVEL,			// ĳ���� ���� %3d �̻�
	DST_SKILL_NEED_SKILL,			// %s %d��� �̻� ����
	DST_SKILL_NEED_MASTERSKILL,		// %s ����
	DST_SKILL_TOTAL_DAMAGE,			// �� ����� : %d 
	DST_SKILL_APPLY_INSTANCE_ENEMY,	// ���� ������� ��� ����

	DST_SKILL_TARGET_AND_RANGE_INFO1,	// ��ų Ÿ�� ����.
	DST_SKILL_TARGET_AND_RANGE_INFO2,
	DST_SKILL_TARGET_AND_RANGE_INFO3,
	DST_SKILL_TARGET_AND_RANGE_INFO4,
	DST_SKILL_TARGET_AND_RANGE_INFO5,
	DST_SKILL_TARGET_AND_RANGE_INFO6,
	DST_SKILL_TARGET_AND_RANGE_INFO7,
	DST_SKILL_TARGET_AND_RANGE_INFO8,
	DST_SKILL_TARGET_AND_RANGE_INFO9,
	DST_SKILL_TARGET_AND_RANGE_INFO11,
	DST_SKILL_TARGET_AND_RANGE_INFO12,
	DST_SKILL_TARGET_AND_RANGE_INFO13,
	DST_SKILL_TARGET_AND_RANGE_INFO14,
	DST_SKILL_TARGET_AND_RANGE_INFO15,
	DST_SKILL_TARGET_AND_RANGE_INFO16,
	DST_SKILL_TARGET_AND_RANGE_INFO17,
	DST_SKILL_TARGET_AND_RANGE_INFO18,
	DST_SKILL_TARGET_AND_RANGE_INFO19,
	DST_SKILL_TARGET_AND_RANGE_INFO20,
	DST_SKILL_TARGET_AND_RANGE_INFO21,
	DST_SKILL_TARGET_AND_RANGE_INFO22,
	DST_SKILL_TARGET_AND_RANGE_INFO23,
	DST_SKILL_TARGET_AND_RANGE_INFO24,
	DST_SKILL_TARGET_AND_RANGE_INFO25,
	DST_SKILL_TARGET_AND_RANGE_INFO26,
	DST_SKILL_TARGET_AND_RANGE_INFO27,
	DST_SKILL_TARGET_AND_RANGE_INFO28,
	DST_SKILL_TARGET_AND_RANGE_INFO29,
	DST_SKILL_TARGET_AND_RANGE_INFO30,
	DST_SKILL_TARGET_AND_RANGE_INFO31,
	DST_SKILL_TARGET_AND_RANGE_INFO32,
	DST_SKILL_TARGET_AND_RANGE_INFO33,
	DST_SKILL_TARGET_AND_RANGE_INFO34,
	DST_SKILL_TARGET_AND_RANGE_INFO35,
	DST_SKILL_TARGET_AND_RANGE_INFO36,
	DST_SKILL_TARGET_AND_RANGE_INFO37,
	DST_SKILL_TARGET_AND_RANGE_INFO38,
	DST_SKILL_TARGET_AND_RANGE_INFO39,
	DST_SKILL_TARGET_AND_RANGE_INFO40,
	DST_SKILL_TARGET_AND_RANGE_INFO41,

	DST_SKILL_MUST_EQUIP_ITEM,		// �ʼ����������� : %s

	DST_SKILL_MASTER_LEARN,			// ��ų������ �����ư �����ؽ�Ʈ
	DST_SKILL_MASTER_UPGRADE,		// ��ų������ ���׷��̵��ư �����ؽ�Ʈ
	DST_SKILL_RPMODE,				// ��ų������ RPMODE��ư, ��ų�����Ƽ ���� 

	DST_SKILL_MASTER_WINDOW_TITLE,	// ��ų Ʈ���̳�
	DST_SKILL_WINDOW_TITLE,			// ��ų ������

	DST_SKILL_TAB_BATTLE_SKILL,		// ������ų
	DST_SKILL_TAB_SUB_SKILL,		// ������ų
	DST_SKILL_TAB_ACTION_SKILL,		// �׼ǽ�ų
	DST_SKILL_FILTER_ALL,			// ��ü
	DST_SKILL_FILTER_ACTION,		// �ʻ��
	DST_SKILL_FILTER_HTB,			// HTB
	DST_SKILL_FILTER_SUB,			// ������
	DST_SKILL_FILTER_PASSIVE,		// �����
	DST_SKILL_FILTER_SOCIAL,		// �ҼȾ׼�
	DST_SKILL_FILTER_ETC,			// ��Ÿ�׼�	

	DST_SKILL_TEXT_EMOTION,			// ���� 
	DST_SKILL_TEXT_ACTION,			// �׼�

	DST_SKILL_SP_INFO_CURRENT_GRADE,	// ���� ��ũ : %u
	DST_SKILL_SP_INFO_NEED_SP,			// ��ũ���� �ʿ��� SP : 
	DST_SKILL_SP_INFO_NEED_SP_LEARN,	// ���µ� �ʿ��� SP : 
	DST_SKILL_SP_INFO_MASTER,			// ���� ��ũ : %u ( ������ )
	DST_SKILL_SP_INFO_NEED_SKILL,		// ��ũ���� �ʿ��� ��ų : 
	DST_SKILL_SP_INFO_NEED_SKILLGRADE,  // "%s %d���"
	DST_SKILL_SP_INFO_NEED_LEARN,		// ��ų�� ��ų�����Ϳ��� ����� �մϴ�.
	DST_SKILL_SP_INFO_CANT_LEARN,		// ���� ��ų�� ��� �� �����ϴ�.
	DST_SKILL_SP_INFO_CANT_SELFTRAIN,	// ���� ��ų�� �͵��� �� �����ϴ�.
	DST_SKILL_SP_INFO_UPGRADE,			// ��ų�� ���׷��̵� �� �� �ֽ��ϴ�.	
	DST_SKILL_SP_INFO_SELFTRAIN,		// ��ų�� ������ ��� �� �ֽ��ϴ�.
	DST_SKILL_SP_INFO_AVATAR_LEVEL,		// ��ũ���� �ʿ��� ���� :
	DST_SKILL_SP_INFO_CANT_LEARN_BY_CLASS,	// Ŭ������ �޶� ��� �� �����ϴ�. 

	// RP Bonus Tool Tip
	DST_SKILL_RPBONUS_TOOLTIP_MANUAL,				// Manual�� ����
	DST_SKILL_RPBONUS_TOOLTIP_KNOCKDOWN,			// KnockDown
	DST_SKILL_RPBONUS_TOOLTIP_RESULT_ABSOLUTE,		// Result Absolute
	DST_SKILL_RPBONUS_TOOLTIP_RESULT_PERCENT,		// Result Percent
	DST_SKILL_RPBONUS_TOOLTIP_KEEPTIME_PLUS,		// KeepTime Plus
	DST_SKILL_RPBONUS_TOOLTIP_CASTING_TIME_MINUS,	// CastingTime Plus
	DST_SKILL_RPBONUS_TOOLTIP_COOLTIME_MINUS,		// Cooltime Minus
	DST_SKILL_RPBONUS_TOOLTIP_EP_MINUS,				// Ep Minus
	DST_SKILL_RPBONUS_TOOLTIP_GUARD_CRASH,			// Guard Crash�� ����
	DST_SKILL_RPBONUS_TOOLTIP_INVALID,				// Invalid == ������

	// Rp Bonus Gui text
	DST_SKILL_RPBONUS_TEXT_TITLE,					// ��ų ��� ����
	DST_SKILL_RPBONUS_TEXT_MANUAL,					// ���� ���
	DST_SKILL_RPBONUS_TEXT_DISABLE,					// ��� ����

	// Rp Bonus Gui InfoWnd Text
	DST_INFOWND_RPBONUS_USE,						// ��ų�����Ƽ ����
	DST_INFOWND_RPBONUS_KNOCKDOWN,					// �˴ٿ� �����Ƽ 
	DST_INFOWND_RPBONUS_KEEPTIME,					// �����ð� ���� �����Ƽ
	DST_INFOWND_RPBONUS_CASTTIME,					// �ߵ��ð� ���� �����Ƽ
	DST_INFOWND_RPBONUS_COOLTIME,					// ��Ÿ�� ���� �����Ƽ
	DST_INFOWND_RPBONUS_EP,							// EP ���� �����Ƽ
	DST_INFOWND_RPBONUS_POWER,						// �Ŀ� ���� �����Ƽ
	DST_INFOWND_RPBONUS_GUARDCRASH,					// ��� ����

	// Rp Bonus Gui Guide Text
	DST_SKILL_ABILITY_ACCEPT,						// ��ų �����Ƽ ������ ����Ǿ����ϴ�.

	// ITEM Gui, Item Info
	DST_ITEM_GRADE_NORMAL,			// �����۵��
	DST_ITEM_GRADE_SUPERIOR,
	DST_ITEM_GRADE_EXCELLENT,
	DST_ITEM_GRADE_RARE,
	DST_ITEM_GRADE_LEGENDARY,
	DST_ITEM_EQUIP_CLASS_TEXT,		// ��������
	DST_ITEM_EQUIP_LEVEL_TEXT,		// ���ѷ���
	DST_ITEM_EQUIP_SLOT_TEXT,		// ���� ���� : %s
	DST_ITEM_NEED_STR,				// �ʿ���
	DST_ITEM_NEED_CON,				// �ʿ�ǰ�
	DST_ITEM_NEED_FOC,				// �ʿ�����
	DST_ITEM_NEED_DEX,				// �ʿ��ø
	DST_ITEM_NEED_SOL,				// �ʿ�����
	DST_ITEM_NEED_ENG,				// �ʿ����
	DST_ITEM_PHYSICAL_OFFENCE,		// ��������
	DST_ITEM_ENERGY_OFFENCE,		// �������
	DST_ITEM_PHYSICAL_DEFENCE,		// �������
	DST_ITEM_ENERGY_DEFENCE,		// ������
	DST_ITEM_ATTACK_RANGE,			// ���ݰŸ� %d ����
	DST_ITEM_CLOSE_ATTACK_RANGE,	// ��������
	DST_ITEM_ATTACK_SPEED,			// ���ݼӵ�
	DST_ITEM_ATTR_INFO,				// �Ӽ� : %s
	DST_ITEM_ATTR_NONE,				// ��
	DST_ITEM_ATTR_HONEST,			// ����			// �Ӽ� : ���� -> ���� ��..
	DST_ITEM_ATTR_STRANGE,			// ����			// �ؿ��� ��������.
	DST_ITEM_ATTR_WILD,
	DST_ITEM_ATTR_ELEGANCE,
	DST_ITEM_ATTR_FUNNY,
	DST_ITEM_BUY_COST,				// ���Ժ� : %%u
	DST_ITEM_SELL_COST,				// �Ǹź� : %%u
	DST_ITEM_REPAIR_COST,			// ������ : %%u
	DST_ITEM_DURABILITY,			// �����۳��� "������:����/�ִ�"
	DST_ITEM_JUST_DURABILITY,		// �����۳��� "������:�ִ�"
	DST_ITEM_ADDITIONAL_EFFECT,		// �߰�ȿ��	
	DST_ITEM_SPECIAL_CLASS,			// ƯȭŬ����
	DST_ITEM_SPECIAL_RACE,			// Ưȭ����
	DST_ITEM_SPECIAL_EFFECT,		// Ưȭȿ�� : +20%
	DST_ITEM_OPTION_EFFECT,			// �ɼ�ȿ��
	DST_ITEM_UNIDENTIFIED,			// ��Ȯ�ξ�����
	DST_ITEM_CAN_EQUIP,				// %s ���밡��
	DST_ITEM_ALL_RACE,				// ��� ����
	DST_ITEM_ALL_RACE_ENABLE_EQUIP_BUT_NMY,	// ��� ���� ���밡��\n (����ũ ���� ����)
	DST_ITEM_PHYSICAL_CLASS,		// Ÿ�ݰ迭 Ŭ����
	DST_ITEM_ENERGY_CLASS,			// ����迭 Ŭ����
	DST_ITEM_DIFF_STATUS,			// + %u
	DST_ITEM_LIMITED_SELL,			// �Ǹ� �Ұ���
	DST_ITEM_LIMITED_USER_TRADE,	// �����ŷ� �Ұ���
	DST_ITEM_LIMITED_STORE_WAREHOUSE,// â������ �Ұ���
	DST_ITEM_LIMITED_STORE_COMMON_WAREHOUSE,//����â������ �Ұ���
	DST_ITEM_IDENTIFY_MUST_IDENTIFY,		// ��ī���͸� �̿��ϰų� ��������\\n �������� �����ؾ� �մϴ�(��Ȯ�� ������ ����â)
	DST_ITEM_IDENTIFY_COST,			// ������ : %u
	DST_ITEM_FUEL_EFFICIENCY,		// ���� %d�ʴ� �� �� �Һ�
	DST_ITEM_MOVE_SPEED,			// �̵��ӵ� %d
	DST_ITEM_ALREADY_EQUIPPED,		// �������� ������

	// NPCShop Gui
	DST_NPCSHOP_MYZENNY,			// ���� ������
	DST_NPCSHOP_MUDOA_POINT,		// ���� ������ ����Ʈ
	DST_NPCSHOP_SHOPINGCART,		// ���� īƮ
	DST_NPCSHOP_ITEM_REPAIR,		// ������ ����
	DST_NPCSHOP_ITEM_ALL_REPAIR,	// ������ ��ü����
	DST_NPCSHOP_ITEM_IDENTIFY,		// ������ ����

	DST_NPCSHOP_LARGE_BUY_EXPLAIN,			// Ctrl + ���콺 ������ Ŭ�� : 20�� ����
	DST_NPCSHOP_NO_MORE_REPAIR_REG_ITEM,	// ���� ������ ��� �������� ������ �ʿ䰡 �����ϴ�(��� ������ ���� ��ư ����)

	// Trade Cart Gui
	DST_TRADECART_TOTAL,			// �� �ݾ�
	DST_TRADECART_BUY,				// �� ��
	DST_TRADECART_SELL,				// �� ��	

	// Status Gui
	DST_STATUS_WINDOW_TITLE,		// �� ����
	DST_STATUS_TAB_AVATAR,			// �ƹ�Ÿ
	DST_STATUS_TAB_SUMMON,			// ��ȯ��
	DST_STATUS_TAB_FAMILY,			// �йи� 

	DST_STATUS_NAME,				// �̸�
	DST_STATUS_JOB,					// ����
	DST_STATUS_LEVEL,				// ����
	DST_STATUS_AP,					// ������

	DST_STATUS_PHYSICAL_ATTACK,		// Ÿ�ݰ��ݷ�
	DST_STATUS_PHYSICAL_DEFENCE,	// Ÿ�ݹ���
	DST_STATUS_PHYSICAL_CRITICAL,	// Ÿ��ũ��Ƽ��
	DST_STATUS_ENERGY_ATTACK,		// ������ݷ�
	DST_STATUS_ENERGY_DEFENCE,		// �������
	DST_STATUS_ENERGY_CRITICAL,		// ���ũ��Ƽ��

	DST_STATUS_ATTACK_RATE,			// ������
	DST_STATUS_DODGE,				// ȸ����

	DST_STATUS_ATTR,				// �Ӽ�
	DST_STATUS_STAT_STR,			// STR
	DST_STATUS_STAT_DEX,			// DEX
	DST_STATUS_STAT_CON,			// CON
	DST_STATUS_STAT_ENG,			// ENG
	DST_STATUS_STAT_SOL,			// SOL
	DST_STATUS_STAT_FOC,			// FOC

	DST_STATUS_ATTACK,				// ���ݷ� (Pet���� ���)

	DST_STATUS_UNIDENTIFIED_LPEP,	// ������������ LPEP ?? / ??
	DST_STATUS_UNIDENTIFIED_NAME,	// ��ī���� ���� �������� �̸�

	DST_EQUIP_SLOT_TYPE_HAND,		// �ֹ���
	DST_EQUIP_SLOT_TYPE_SUB_WEAPON, // ��������
	DST_EQUIP_SLOT_TYPE_JACKET,		// ����
	DST_EQUIP_SLOT_TYPE_PANTS,		// ����
	DST_EQUIP_SLOT_TYPE_BOOTS,		// �Ź�
	DST_EQUIP_SLOT_TYPE_SCOUTER,	// ��ī����
	DST_EQUIP_SLOT_TYPE_DOGI,		// ����
	DST_EQUIP_SLOT_TYPE_NECKLACE,	// �����
	DST_EQUIP_SLOT_TYPE_EARRING,	// �Ͱ���
	DST_EQUIP_SLOT_TYPE_RING,		// ����	

	DST_STATUS_CURRENT_EXP,			// ����
	DST_STATUS_GOAL_EXP,			// ��ǥ

	// Status Window Tooltip
	DST_STATUS_TOOLTIP_ATTR,		// �Ӽ�
	DST_STATUS_TOOLTIP_STR,			// ��
	DST_STATUS_TOOLTIP_DEX,			// ��ø
	DST_STATUS_TOOLTIP_CON,			// �ټ�
	DST_STATUS_TOOLTIP_ENG,			// ���
	DST_STATUS_TOOLTIP_SOL,			// ����
	DST_STATUS_TOOLTIP_FOC,			// ����

	DST_STATUS_TOOLTIP_PHYSICAL_ATTACK,		// Ÿ�� ���ݷ�
	DST_STATUS_TOOLTIP_PHYSICAL_DEFENCE,	// Ÿ�� ����
	DST_STATUS_TOOLTIP_PHYSICAL_CRITICAL,	// Ÿ�� ũ��Ƽ�� Ȯ��
	DST_STATUS_TOOLTIP_ENERGY_ATTACK,		// ��� ���ݷ�
	DST_STATUS_TOOLTIP_ENERGY_DEFENCE,		// ��� ����
	DST_STATUS_TOOLTIP_ENERGY_CRITICAL,		// ��� ũ��Ƽ�� Ȯ��
	DST_STATUS_TOOLTIP_ATTACK_RATING,	// ���߷�
	DST_STATUS_TOOLTIP_DODGE_RATING,	// ȸ����

	// Status Window Honor Tab
	DST_STATUS_HONOR_TITLE_HONOR,		// ��
	DST_STATUS_HONOR_TITLE_RANKBATTLE,	// ��ũ��Ʋ

	DST_STATUS_HONOR_HTMLTAG_HONOR,		// (HTML Tag) %s[br][br]%s
	DST_STATUS_HONOR_HONOR_SCORE,		// ������ : %d
	DST_STATUS_HONOR_GUIDE_HONOR,		// �������� ���̵�, õ������ ����ȸ .....

	DST_STATUS_HONOR_HTMLTAG_RANKBATTLE,	// (HTML Tag) %s[br][br]%s[br]%s
	DST_STATUS_HONOR_PRIVATE_SCORE,		// ���� : %d�� %d�� %d��
	DST_STATUS_HONOR_RANK_SCORE,		// ��ũ����Ʈ : %d ��
	DST_STATUS_HONOR_MUDOSA_SCORE,		// ����������Ʈ : %d ��

	// Status Window Technic Tab
	DST_STATUS_TECHNIC_TITLE,					// ��ũ��
	DST_STATUS_TECHNIC_HOIPOIMIX_TITLE,			// ȣ�����̹ͽ�
	DST_STATUS_TECHNIC_HOIPOIMIX_MIXLEVEL,		// �ͽ� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_MIXEXPDATA,	// �ͽ� ����ġ
	DST_STATUS_TECHNIC_HOIPOIMIX_NORMAL_SKILL,		// �Ϲ� ���� ���
	DST_STATUS_TECHNIC_HOIPOIMIX_NORMAL_SKILL_GUIDE,	// 10���� �̻� ���� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_NORMAL_SKILL_GUIDE_HTML,	// (HTML) �ͽ� �����Ϳ��Լ� ��� �� ������....
	DST_STATUS_TECHNIC_HOIPOIMIX_SPECIAL_SKILL,		// Ư�� ���� ���
	DST_STATUS_TECHNIC_HOIPOIMIX_SPECIAL_SKILL_GUIDE,	// 15���� �̻� ���� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_SPECIAL_SKILL_GUIDE_HTML,	// (HTML) �ͽ� �����Ϳ��Լ� ���� ������...

	DST_STATUS_TECHNIC_HOIPOIMIX_SKILL_FOOD_HTML,		// (HTML) ���� ���� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_SKILL_MAIN_HTML,		// (HTML) �ֹ��� ��������
	DST_STATUS_TECHNIC_HOIPOIMIX_SKILL_ARMOR_HTML,		// (HTML) �� ���� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_SKILL_ACCESSORY_HTML,	// (HTML) �Ǽ����� ���� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_SKILL_SCOUTER_HTML,	// (HTML) ��ī���� ���� ����
	DST_STATUS_TECHNIC_HOIPOIMIX_SKILL_SUB_WEAPON_HTML,	// (HTML) �ι��� ���� ����


	// Pet Status Gui
	DST_PET_STATUS_PHYSICAL_OFFENSE, // Ÿ�ݰ��ݷ�
	DST_PET_STATUS_PHYSICAL_DEFENSE, // Ÿ�ݹ���
	DST_PET_STATUS_ENERGY_OFFENSE, // ������ݷ�
	DST_PET_STATUS_ENERGY_DEFENSE, // �������

	// PC_Race
	DST_HUMAN,						// �ΰ�
	DST_NAMEK,						// ����ũ��
	DST_MAJIN,						// ����

	// PC_Class
	DST_HUMAN_FIGHTER,
	DST_HUMAN_MYSTIC,
	DST_ENGINEER,
	DST_NAMEK_FIGHTER,
	DST_NAMEK_MYSTIC,
	DST_MIGHTY_MAJIN,
	DST_WONDER_MAJIN,
	DST_STREET_FIGHTER,
	DST_SWORD_MASTER,
	DST_CRANE_ROSHI,
	DST_TURTLE_ROSHI,
	DST_GUN_MANIA,
	DST_MECH_MANIA,
	DST_DARK_WARRIOR,
	DST_SHADOW_KNIGHT,
	DST_DENDEN_HEALER,
	DST_POCO_SUMMONER,
	DST_ULTI_MA,
	DST_GRAND_MA,
	DST_PLAS_MA,
	DST_KAR_MA,

	// Action Type (Action Info Window)
	DST_ACTION_TYPE_NORMAL,			// ��־׼�
	DST_ACTION_TYPE_SOCIAL,			// �ҼȾ׼�
	DST_CHAT_COMMAND,				// "ä�ø�� : "

	// 
	DST_SHENRON,					// �ŷ�

	// Scouter Parts Explain for ScouterBody
	DST_SCOUTERPARTS_NORMAL_START_LP,// LP + %d
	DST_SCOUTERPARTS_EP,			// EP + %d
	DST_SCOUTERPARTS_STR,			// �� + %d
	DST_SCOUTERPARTS_CON,			// �ټ� + %d
	DST_SCOUTERPARTS_FOC,			// ���� + %d
	DST_SCOUTERPARTS_DEX,			// ��ø + %d
	DST_SCOUTERPARTS_SOL,			// ���� + %d
	DST_SCOUTERPARTS_ENG,			// ��� + %d
	DST_SCOUTERPARTS_ATTACK_SPEED,	// ���� �ӵ� + %d%%
	DST_SCOUTERPARTS_ATTACK_RATE,	// ���� + %d%%
	DST_SCOUTERPARTS_DODGE_RATE,	// ȸ�� + %d%%
	DST_SCOUTERPARTS_BLOCK_RATE,	// ��� + %d%%
	DST_SCOUTERPARTS_CURSESUCCESS_RATE,	// �����̻� ���� + %d%%
	DST_SCOUTERPARTS_CURSE_TOLERANCE_RATE,	// �����̻� ���� + %d%%
	DST_SCOUTERPARTS_UPGRADE_RATE_UP,		// ����ȿ�� %02.02f�� ����
	DST_SCOUTERPARTS_ITEM_BREAK_RATE_DOWN,	// ���� ���н� ������ �ı� Ȯ�� %02.02f�� ����

	DST_SCOUTERPARTS_BEST_START,

	DST_SCOUTERPARTS_SPECIAL_START,
	DST_SCOUTERPARTS_PC_INFO_JAMMING,			// ������ ����
	DST_SCOUTERPARTS_FIND_OBJECT,				// ������ ���� ã��	
	DST_SCOUTERPARTS_MAIL_CONNECTOR,			// ������ ����
	DST_SCOUTERPARTS_MAIL_TRANSMITTER,			// ���� ����
	DST_SCOUTERPARTS_FIND_MOB_TO_GET_DRAGONBALL,// �巡�ﺼ ���� ǥ��
	DST_SCOUTERPARTS_ITEM_IDENTIFICATION,		// ������ ����	
	DST_SCOUTERPARTS_PC_INFO_VIEWER,			// ������ ������
	DST_SCOUTERPARTS_QUEST_SEARCH,				// �ֺ� ����Ʈ �˻�
	// End of 'Scouter Parts Explain for ScouterBody

	// Explain effect for charm buff
	DST_CHARM_EXP,								// ����ġ %d%% �߰� ȹ��
	DST_CHARM_COOLTIME,							// ��ų ��Ÿ�� %d%% ����
	DST_CHARM_DROPRATE,							// ������ ��� Ȯ�� %d%% ����
	DST_CHARM_RP_SHARING,						// RP ���� %d ����
	// End of effect Explain charm buff

	// Community
	DST_COMMUNITY_NAME,							// Ŀ�´�Ƽ
	DST_TAB_PARTY,								// ��Ƽ
	DST_TAB_GUILD,								// ���
	DST_TAB_RAID,								// ���̵�

	// Party UI
	DST_PARTYGUI_PARTYLEADER,					// ��Ƽ��

	DST_PARTYGUI_ITEM_LOOTING,					// ������ �й� ��� ����
	DST_PARTYGUI_ITEM_LOOTING_PICKUP_PERSON,	// �ݴ� ��� ȹ��
	DST_PARTYGUI_ITEM_LOOTING_IN_ORDER,			// �����Ƿ� �й�
	DST_PARTYGUI_ITEM_LOOTING_IN_GRADE,			// ��޺� �����Ƿ� �й�
	DST_PARTYGUI_ITEM_LOOTING_BY_LEADER,		// ��Ƽ���� �й�
	DST_PARTYGUI_ITEM_LOOTING_BY_ZENNY,			// ���
	DST_PARTYGUI_ITEM_LOOTING_BY_DICE,			// �ֻ��� ������

	DST_PARTYGUI_ZENNY_LOOTING,					// ���� �й� ��� ����
	DST_PARTYGUI_ZENNY_LOOTING_PICKUP_PERSON,	// �ݴ� ��� ȹ��
	DST_PARTYGUI_ZENNY_LOOTING_EQUAL,			// �Ȱ��� ������

	DST_PARTYGUI_MEMBER,						// ��Ƽ �ɹ�

	DST_PARTYGUI_CHARM,							// ��Ƽ ����
	DST_PARTYGUI_DEST_ZENNY,					// ��ǥ�ݾ�
	DST_PARTYGUI_CHARM_EXPLAIN,					// ��Ƽ������ ����Ͽ� ��Ƽ�� ��ü�� Ư���� ����ȿ���� ���� �� �ֽ��ϴ�
	DST_PARTYGUI_INVEN,							// ��Ƽ �κ��丮	
	DST_PARTYGUI_INVEN_COMPETITOR,				// �⿩������ ������ ������
	DST_PARTYGUI_INVEN_MYSCORE,					// ���� ������ �⿩����
	DST_PARTYGUI_INVEN_EXCUTE_DIVIDE,			// �й�
	DST_PARTYGUI_INVEN_LOCK,					// ��� ����
	DST_PARTYGUI_INVEN_UNLOCK,					// ��� ����
	DST_PARTYGUI_INVEN_SUCCESSFUL_BID,			// ����
	DST_PARTYGUI_INVEN_RESET_OCTION,			// ��� ���� �ʱ�ȭ
	DST_PARTYGUI_INVEN_ITEM_GRADE,				// ����(��Ƽ �κ��� ������ ��� ������ ��)

	DST_PARTYGUI_LEAVE_BUTTON,					// ��Ƽ Ż��
	DST_PARTYGUI_INVITE_BUTTON,					// ��Ƽ �ʴ�	
	DST_PARTYGUI_SWITCH,						// ���� ����
	DST_PARTYGUI_DUNGEON,						// ��Ƽ ����
	DST_PARTYGUI_SPREAD,						// �޴� ��ġ��
	DST_PARTYGUI_FOLD,							// �޴� ����

	DST_PARTYGUI_CHARM_USE,						// �������

	DST_PARTY_DUNGEON_NORMAL,					// ����
	DST_PARTY_DUNGEON_HARD,						// �����

	// Scouter GUI
	DST_SCOUTER_SCOUTER_NAME,					// ��ī����
	DST_SCOUTER_PARTS_NAME,						// ����
	DST_SCOUTER_PARTS_OPTION,					// ���� �ɼ�
	DST_SCOUTER_SCOUTER_ABILITY,				// ��ī���� ����
	DST_SCOUTER_POWER,							// ��뷮
	DST_SCOUTER_ENDURANCE,						// ������	
	DST_SCOUTER_POWER_MAX_INFO,					// �ִ� ��ī���� �뷮 %d	( ���������¿�����  ǥ�� )
	DST_SCOUTER_POWER_CURRENT_INFO,				// ��ī���� �뷮 %d / %d ( ������ ����뷮�� ���� ǥ�� )
	DST_SCOUTER_PARTS_POWER_CUNSUMPTION,		// ���� �Ҹ� %d
	DST_SCOUTER_REMOVER_ALL_PARTS,				// ��� ���� ����


	// ItemUpgrade Gui
	DST_ITEMUPGRADE_DLGTITLE,					// ������ ���׷��̵�
	DST_ITEMUPGRADE_INFOTITLE,					// ���׷��̵� ��Ȳ
	DST_ITEMUPGRADE_PREDICT,					// Ȯ�� ����
	DST_ITEMUPGRADE_DESTROY_PREDICT,			// �Ҹ� ����
	DST_ITEMUPGRADE_BTN_COMPOUND,				// ���׷��̵�
	DST_ITEMUPGRADE_BTN_COMPOUND_DOWN,			// �ٿ�׷��̵�
	DST_ITEMUPGRADE_BTN_CANCEL,					// ���

	DST_ITEMUPGRADE_PREDICT_VERYGOOD,			// �ſ� ����
	DST_ITEMUPGRADE_PREDICT_GOOD,				// ����
	DST_ITEMUPGRADE_PREDICT_NORMAL,				// ����
	DST_ITEMUPGRADE_PREDICT_BAD,				// ����
	DST_ITEMUPGRADE_PREDICT_POOR,				// ����
	DST_ITEMUPGRADE_PREDICT_VERYPOOR,			// �־�
	DST_ITEMUPGRADE_PREDICT_HOPELESS,			// ����

	// Item Upgrade MSG( Html �������� ��� �մϴ� )
	DST_ITEMUPGRADE_MSG_SLOT_IS_EMPTY,			// ���׷��̵� �� �����۰� ȣ�����̽����� �÷��ֽʽÿ�.	
	DST_ITEMUPGRADE_MSG_ITEM_IN,				// ȣ�����̽����� �÷��ֽʽÿ�.
	DST_ITEMUPGRADE_MSG_MINLEVEL_ITEM_IN,		// 0���� �������� ��������.
	DST_ITEMUPGRADE_MSG_MAXLEVEL_ITEM_IN,		// �ƽ����� �������� ��������.
	DST_ITEMUPGRADE_MSG_HOIPOISTONE_IN,			// ���׷��̵� �� �������� �÷��ֽʽÿ�.
	DST_ITEMUPGRADE_MSG_BLACK_HOIPOISTONE_IN,	// �ٿ�׷��̵� �� �������� �÷��ֽʽÿ�.
	DST_ITEMUPGRADE_MSG_PURE_HOIPOISTONE_IN,	// ���׷��̵� �� �������� �÷��ֽʽÿ�. ǻ�� ȣ�̽�����...
	DST_ITEMUPGRADE_MSG_UPGRADEREADY,			// ���׷��̵尡 �����մϴ�. ���׷��̵� ������[br]...
	DST_ITEMUPGRADE_MSG_DOWNGRADEREADY,			// �ٿ�׷��̵尡 �����մϴ�. �ٿ�׷��̵� ������[br]...
	DST_ITEMUPGRADE_MSG_USE_HOIPOISTONECOUNT,	// %s %d�� ���
	DST_ITEMUPGRADE_MSG_PHYSICAL_UP,
	DST_ITEMUPGRADE_MSG_ENERGY_UP,
	DST_ITEMUPGRADE_MSG_PURE_PHYSICAL_UP,		//
	DST_ITEMUPGRADE_MSG_PURE_ENERGY_UP,			//
	DST_ITEMUPGRADE_MSG_PHYSICAL_DOWN,
	DST_ITEMUPGRADE_MSG_ENERGY_DOWN,
	DST_ITEMUPGRADE_MSG_NO_CHANGE_PARAMETER,			// ��ȭ����.
	DST_ITEMUPGRADE_MSG_CHANGE_ATTR,					// �Ӽ���ȭ ->
	DST_ITEMUPGRADE_MSG_NO_CHANGE_ATTR,					// �Ӽ���ȭ ����.
	DST_ITEMUPGRADE_MSG_HOIPOISTONE_IN_FAIL_CLASS,		// ���׷��̵��� ����� ȣ������ ������ ������ ���ڶ��ϴ�. Ȯ���� �ֽʽÿ�.
	DST_ITEMUPGRADE_MSG_BLACKHOIPOISTONE_IN_FAIL_CLASS,	// �ٿ�׷��̵��� ����� ��ȣ������ ������ ������ ���ڶ��ϴ�. Ȯ���� �ֽʽÿ�.
	DST_ITEMUPGRADE_MSG_HOIPOISTONE_IN_FAIL_QUANTITY,		// ���׷��̵忡 �ʿ��� ȣ������ ������ ���ڶ��ϴ�. Ȯ���� �ֽʽÿ�.[br] %s : %s ( %d / %d ) 
	DST_ITEMUPGRADE_MSG_BLACKHOIPOISTONE_IN_FAIL_QUANTITY,	// �ٿ�׷��̵忡 �ʿ��� ��ȣ������ ������ ���ڶ��ϴ�. Ȯ���� �ֽʽÿ�.[br] %s : %s ( %d / %d ) 
	DST_ITEMUPGRADE_MSG_PUREHOIPOISTONE_IN_FAIL_QUANTITY,	// ���׷��̵忡 �ʿ��� ��ȣ������ ������ ���ڶ��ϴ�. Ȯ���� �ֽʽÿ�.[br] %s : %s ( %d / %d ) 
	DST_ITEMUPGRADE_MSG_UNUPGRADABLE_ITEM,				// �������� ���̻� ���׷��̵� �� �� �����ϴ�.
	DST_ITEMUPGRADE_MSG_UNDOWNGRADABLE_ITEM,			// �������� ���̻� �ٿ�׷��̵� �� �� �����ϴ�.
	// ������� Html �������� ���ϴ�.

	DST_ITEMUPGRADE_RESULT_MSG_SUCCESS,			// �����մϴ�./w������ ���׷��̵尡 �����߽��ϴ�.
	DST_ITEMUPGRADE_RESULT_MSG_DOWNGRADE_SUCCESS,	// ������ �ٿ�׷��̵尡 �����߽��ϴ�. 
	DST_ITEMUPGRADE_RESULT_MSG_FAIL,			// ������ ���׷��̵尡 �����߽��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_UPGRADE,		// ������ ���( %d -> %d )�� �ö����ϴ�.
	DST_ITEMUPGRADE_RESTLT_REPORT_DOWNGRADE,	// ������ ���( %d -> %d )�� ���Ƚ��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_PHYSICAL_OFFENCE_UP,	// �������� �������ݷ�( %d -> %d )�� �ö����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_PHYSICAL_OFFENCE_DOWN, // �������� �������ݷ�( %d -> %d )�� ���Ƚ��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_ENERGY_OFFENCE_UP,		// �������� ������ݷ�( %d -> %d )�� �ö����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_ENERGY_OFFENCE_DOWN,	// �������� ������ݷ�( %d -> %d )�� ���Ƚ��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_PHYSICAL_DEFENCE_UP,	// �������� ��������( %d -> %d )�� �ö����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_PHYSICAL_DEFENCE_DOWN, // �������� ��������( %d -> %d )�� ���Ƚ��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_ENERGY_DEFENCE_UP,		// �������� �������( %d -> %d )�� �ö����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_STATUS_ENERGY_DEFENCE_DOWN,	// �������� �������( %d -> %d )�� ���Ƚ��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_ATTRIBUTE,	// �������� �Ӽ�( %s -> %s )�� ���߽��ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_ITEM_DESTROY,	// �������� �ı��Ǿ����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_NO_PHYSICAL_OFFENCE_CHANGE,	// ������ �������ݷ��� ��ȭ�� �����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_NO_PHYSICAL_DEFENCE_CHANGE,	// ������ ���������� ��ȭ�� �����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_NO_ENERGY_OFFENCE_CHANGE,		// ������ ������ݷ��� ��ȭ�� �����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_NO_ENERGY_DEFENCE_CHANGE,		// ������ ��������� ��ȭ�� �����ϴ�.
	DST_ITEMUPGRADE_RESULT_REPORT_NO_ATTRIBUTE_CHANGE,	// ������ �Ӽ��� ��ȭ�� �����ϴ�.

	DST_ITEMUPGRADE_INFO_ITEM_SLOT,						// ���׷��̵��� ��� �������� �ִ� ���Դϴ�. ���������� ��޿� ���� �����...
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_EMPTY_TITLE,		//  ȣ������ ���� ���� ( ù���� ����. )
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_EMPTY_LINE1,		// ���׷��̵� ������
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_EMPTY_LINE2_1,		// �Ӽ����� ����Ǹ�
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_EMPTY_LINE2_2,		// �Ӽ���
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_EMPTY_LINE3,		// ���׷��̵� ���н� �Ӽ��� ����\n�ı� Ȯ���� ���ϰų� ���Ӽ����� ���� �� �ֽ��ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_ATTR,				//  �Ӽ��� ���� ��/�� ( ù���� ���� )
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_ATTR_BETTER,		//  %.0f%% �̵� ( ù���� ����. )
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_ATTR_WORSE,		//  %.0f%% ���� ( ù���� ����. )
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_1_CHANGE,		// ���׷��̵� ������ �������� %s �Ӽ����� ���մϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_1_BLACKCHANGE,   // �������� �ٿ�׷��̵� �Ǹ� %s �Ӽ����� ���մϴ�
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_1_NO_CHANGE,	// ���׷��̵� ������ �Ӽ��� ������ �ʽ��ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_1_NO_BLACKCHANGE,//�������� �ٿ�׷��̵� �Ǹ� �Ӽ��� ������ �ʽ��ϴ�
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_COMMON,		// �Ӽ� ������ ���� ���׷��̵� ���� ��,\n
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_BEST,			// �������� �ı��� Ȯ���� ���� �������ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_GOOD,			// �������� �ı��� Ȯ���� ���� �������ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_LITTLE_GOOD,	// �������� �ı��� Ȯ���� ���� ���� �������ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_LITTLE_BAD,	// �������� �ı��� Ȯ���� ���� ���� �ö󰩴ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_NORMAL,		// �������� �ı��� Ȯ���� ������ ���� �ʽ��ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_2_BAD,			// �������� �ı��� Ȯ���� ���� �ö󰩴ϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_3,				// ���׷��̵� ���н� �������� �Ӽ��� ���Ӽ����� ���մϴ�.
	DST_ITEMUPGRADE_INFO_HOIPOI_SLOT_IN_3_NO_CHANGE,	// ���׷��̵� ���н� �Ӽ��� ������ �ʽ��ϴ�. 

	DST_ITEMUPGRADE_INFO_OFFENCE,				// ���ݷ�
	DST_ITEMUPGRADE_INFO_DEFENCE,				// ����

	// Quest 
	DST_QUESTREWARD_INFO_EXP,					// ����ġ %d ȹ��
	DST_QUESTREWARD_INFO_ZENNY,					// ���� %d ȹ��
	DST_QUESTREWARD_INFO_CLASS,					// %s Ŭ������ ����
	DST_QUESTREWARD_INFO_REPUTATION,			// �� %d ȹ��
	DST_QUESTREWARD_PROB_REWARD,				// Ȯ������
	DST_QUESTREWARD_TEXT_BASIC,					// �⺻����
	DST_QUESTREWARD_TEXT_SELECT,				// ���ú���
	DST_QUESTREWARD_CHANGE_ADULT,				// ����� ����
	DST_QUESTREWARD_CONVERT_CLASS_RIGHT,		// 2�������� ��������

	DST_QUESTLIST_TITLE,						// ����Ʈ ����Ʈ
	DST_QUESTLIST_INVENTITLE,					// ����Ʈ �κ��丮
	DST_QUESTLIST_NOQUEST,						// ���� ������ ����Ʈ�� �����ϴ�.

	DST_QUESTLIST_TIP_NEW_QUEST,				// �� ����Ʈ
	DST_QUESTLIST_TIP_CLEARD_QUEST,				// �Ϸ�� ����Ʈ
	DST_QUESTLIST_TIP_PROGRESS_QUEST,			// �������� ����Ʈ
	DST_QUESTLIST_TIP_FAILD_QUEST,				// ������ ����Ʈ
	DST_QUESTLIST_TIP_ERROR_BLOCK,				// ����Ʈ ����

	DST_QUEST_TEXT_CONVERSATION,				// ��ȭ
	DST_QUEST_TEXT_AIM,							// ��ǥ

	DST_QUEST_GIVEUP_BTN,						// ����
	DST_QUEST_CLOSE_BTN,						// �ݱ�
	DST_QUEST_ACCEPT_BTN,						// ����
	DST_QUEST_REJECT_BTN,						// ����
	DST_QUEST_REWARD_BTN,						// ����
	DST_QUEST_CANCEL_BTN,						// ���

	DST_QUEST_PROGRESS_WINDOW_TITLE,			// ����Ʈ ����
	DST_QUEST_LIMIT_TIME,						// ���ѽð�
	DST_QUEST_PROGRESS_INFO,					// �����Ȳ

	DST_QUEST_PROPOSAL_WINDOW_TITLE,			// ����Ʈ ����
	DST_QUEST_REWARD_WINDOW_TITLE,				// ����Ʈ ����

	DST_QUEST_REMAIN_TIME,						// �����ð� %02d : %02d

	DST_QUEST_SHOW_QUEST_CATALOG,				// ����Ʈ ��� ���̱�
	DST_QUEST_HIDE_QUEST_CATALOG,				// ����Ʈ ��� ���߱�
	DST_QUEST_SHARE,							// ����Ʈ ����
	DST_QUEST_NEW,								// <������Ʈ>
	DST_QUEST_INDICATOR,						// ����Ʈ �˸���
	DST_QUEST_NEXT_INVENTORY,					// ���� 
	DST_QUEST_PREV_INVENTORY,					// ����

	DST_QUEST_CAT_TASK,							// �Ϲ� ����Ʈ
	DST_QUEST_CAT_SCENARIO,						// �ó����� ����Ʈ
	DST_QUEST_CAT_TIMEMACHINE,					// Ÿ�Ӹӽ� ����Ʈ
	DST_QUEST_CAT_DRAGONBALL,					// �巡�ﺼ ����Ʈ
	DST_QUEST_CAT_JOBCHANGE,					// ���� ����Ʈ
	DST_QUEST_CAT_TLQ,							// Ÿ�Ӹ��� ����Ʈ

	DST_QUEST_SENDER,							// �Ƿ�ó
	DST_QUEST_RECIEVER,							// ����ó

	// ĳ���� ����ŷ ����
	DST_AVATAR_SEX_MALE,						// ����
	DST_AVATAR_SEX_FEMALE,						// ����
	DST_AVATAR_SEX_NOT_EXIST,					// ���� ����

	// Warehouse
	DST_WAREHOUSE_NAME_1,					// â�� 1
	DST_WAREHOUSE_NAME_2,					// â�� 2
	DST_WAREHOUSE_NAME_3,					// â�� 3
	DST_WAREHOUSE_NAME_COMMON,				// ���� â��	
	DST_WAREHOUSE_ALL,						// ��� â��

	// log in
	DST_LOGIN,								// ����
	DST_LOGIN_ID,							// ���̵�
	DST_LOGIN_PASSWARD,						// ��й�ȣ
	DST_LOGIN_PLAY_MOVIE,					// ������ ���
	DST_LOGIN_CREDIT,						// ������ ����
	DST_LOGIN_CONTRACT,						// �� ��
	DST_LOGIN_NEW_ACCOUNT,					// �� ���� �����

	// Lobby
	DST_LOBBY_CHARACTER_MAKE,				// ĳ���� �����
	DST_LOBBY_RANDOM_CHOICE,				// �� �� �� ��
	DST_LOBBY_MAKE,							// �� �� ��
	DST_LOBBY_RETURN,						// ���ư���
	DST_LOBBY_EXIT,							// �� �� ��
	DST_LOBBY_RACE,							// ��   ��
	DST_LOBBY_GENDER,						// ��   ��
	DST_LOBBY_CLASS,						// ��   ��
	DST_LOBBY_HAIR,							// �Ӹ����
	DST_LOBBY_HAIRCOLOR,					// �Ӹ���
	DST_LOBBY_FACE,							// ��   ��
	DST_LOBBY_SKIN,							// �Ǻλ�
	DST_LOBBY_HUMAN_EXPLAIN,				// ���� ����
	DST_LOBBY_NAMEK_EXPLAIN,				// ���� ����
	DST_LOBBY_MAJIN_EXPLAIN,				// ���� ����
	DST_LOBBY_HUMAN_FIGHTER,				// Ŭ���� ����
	DST_LOBBY_HUMAN_MYSTIC,					// Ŭ���� ����
	DST_LOBBY_HUMAN_ENGINEER,				// Ŭ���� ����
	DST_LOBBY_NAMEK_FIGHTER,				// Ŭ���� ����
	DST_LOBBY_NAMEK_MYSTIC,					// Ŭ���� ����
	DST_LOBBY_MIGHTY_MAJIN,					// Ŭ���� ����
	DST_LOBBY_WONDER_MAJIN,					// Ŭ���� ����

	DST_LOBBY_CHANNEL,						// ä��
	DST_LOBBY_SERVER_NAME,					// ���� �̸�
	DST_LOBBY_SERVER_STATE,					// ���� ����
	DST_LOBBY_PERIOD,						// ���� �����ϱ��� 10�� ���ҽ��ϴ�
	DST_LOBBY_UNTIL_DEL_CHAR,				// ĳ���Ͱ� �����Ǳ���� %d%s ���ҽ��ϴ�

	DST_LOBBY_SERVER_NOT_BUSY,				// �Ѱ�
	DST_LOBBY_SERVER_NORMAL,				// ����
	DST_LOBBY_SERVER_BUSY,					// �ٻ�
	DST_LOBBY_SERVER_EXCESS,				// �ʰ�
	DST_LOBBY_SERVER_LOCK,					// ���
	DST_LOBBY_SERVER_CHECK,					// ����

	DST_LOBBY_CHAR_LEVEL,					// ����
	DST_LOBBY_CHAR_CLASS,					// Ŭ����
	DST_LOBBY_ZENNY,						// ��������	
	DST_LOBBY_POSITION,						// ������ġ
	DST_LOBBY_DEL_DAT,						// ���� ������
	DST_LOBBY_CHAR,							// ĳ����
	DST_LOBBY_CHOICE_CHANNEL,				// ä�� ����
	DST_LOBBY_DEL_CHAR,						// ĳ���� ����
	DST_LOBBY_GAME_START,					// ���ӽ���
	DST_LOBBY_OK,							// Ȯ ��
	DST_LOBBY_CANCLE,						// ���
	DST_LOBBY_CANCLE2,						// �� ��	
	DST_LOBBY_CHOICE_SERVER,				// ���� ����
	DST_LOBBY_SERVER,						// ��  ��
	DST_LOBBY_STATE,						// ����	
	DST_LOBBY_RECOVERY_CHAR_INFO,			// ĳ���� ����
	DST_LOBBY_LEFT_DELETE_TIME,				// ���� ��� �ð�

	DST_LOBBY_DEFAULT_POSITION_HUMAN,		// ���� ���� �α�
	DST_LOBBY_DEFAULT_POSITION_NAMEK,		// ������ ���� �α�
	DST_LOBBY_DEFAULT_POSITION_MAJIN,		// ���������� ���� �α�

	// Guild
	DST_GUILD_LEAVE,						// ��� Ż��
	DST_GUILD_MEMBER,						// ���ɹ�
	DST_GUILD_LEVEL,						// ����
	DST_GUILD_CUR_POS,						// ������ġ
	DST_GUILD_NOTICE,						// ��� ����
	DST_GUILD_GYM,							// ��� ����
	DST_GUILD_MASTER,						// �����
	DST_GUILD_SECOND_MASTER,				// �α����

	DST_GUILD_EMBLEM_TITLE,					// ���� ���� ����
	DST_GUILD_NOTICE_TITLE,					// ���� ���� �Է�

	// Guild warehouse
	DST_GUILDWAREHOUSE_TITLE_1,				// ��� â�� 1
	DST_GUILDWAREHOUSE_TITLE_2,				// ��� â�� 2
	DST_GUILDWAREHOUSE_TITLE_3,				// ��� â�� 3

	// ChatDisplayMode
	DST_CHAT_MODE_GENERAL,					// �Ϲ�
	DST_CHAT_MODE_WHISPER,					// �ӼӸ�
	DST_CHAT_MODE_PARTY,					// ��Ƽ
	DST_CHAT_MODE_TRADE,					// �ŷ�
	DST_CHAT_MODE_GUILD,					// ���
	DST_CHAT_MODE_SHOUT,					// ��ħ
	DST_CHAT_MODE_SYSTEM,					// �ý���	

	DST_CHAT_FILTER,						// ä�� ����	
	DST_CHAT_DISP_COMMAND_FIRST,			// �� ����
	DST_CHAT_DISP_COMMAND_PREV,				// �� �� ����
	DST_CHAT_DISP_COMMAND_NEXT,				// �� �� �Ʒ���
	DST_CHAT_DISP_COMMAND_LAST,				// �� ������
	DST_CHAT_DISP_COMMAND_LOCK,				// ä��â ũ�� ���
	DST_CHAT_DISP_COMMAND_UNLOCK,			// ä��â ũ�� ��� ����

	// �ð�
	DST_TERM,								// �Ⱓ
	DST_A_DAY,								// ��¥

	DST_MONDAY,								// ��
	DST_TUESDAY,							// ȭ
	DST_WEDNESDAY,							// ��
	DST_THURSDAY,							// ��
	DST_FRIDAY,								// ��
	DST_SATURDAY,							// ��
	DST_SUNDAY,								// ��

	DST_TIME_MONTH,							// ��
	DST_TIME_DAY,							// ��
	DST_TIME_HOUR,							// ��
	DST_TIME_AN_HOUR,						// �ð�
	DST_TIME_MINUTE,						// ��
	DST_TIME_SECOND,						// ��

	// Ÿ�Ӹӽ� ����Ʈ	
	DST_TMQ_BALLOON_TITLE,					// ��   ��
	DST_TMQ_BALLOON_CURRENT_PEOPLE,			// ���� ��û�� ��Ƽ/���� : 
	DST_TMQ_BALLOON_PRIVATE_REG,			// ���� ���
	DST_TMQ_BALLOON_PARTY_REG,				// ��Ƽ ���
	DST_TMQ_BALLOON_TIME_BY_LOTTERY,		// ��÷���� ���� �ð� : 
	DST_TMQ_BALLOON_CENCLE_RESERVATION,		// �������
	DST_TMQ_BALLOON_START_TIME,				// ��߽ð�
	DST_TMQ_BALLOON_REMAIN_TIME_BY_RETRY,	// ���û���� ���� �ð� : 
	DST_TMQ_BALLOON_RETRY,					// ���û
	DST_TMQ_BALLOON_REG_STATUS,				// ��ϻ��� : 
	DST_TMQ_BALLOON_REMAIN_TIME,			// �����ð� : 
	DST_TMQ_BALLOON_NEED_ITEM,				// �ʿ������ : 
	DST_TMQ_BALLOON_NOT_THING,				// ����
	DST_TMQ_BALLOON_MOVE,					// �̵��ϱ�

	DST_TMQ_BOARD_CURRENT_TIME,				// ����ð�
	DST_TMQ_BOARD_LIMITE_TIME,				// ���ѽð�
	DST_TMQ_BOARD_LIMITE_LEVEL,				// ���ѷ���
	DST_TMQ_BOARD_NEXT_TMQ,					// ���� Ÿ�Ӹӽ� ����Ʈ
	DST_TMQ_BOARD_RESERVATION_PRIVATE,		// ���ο���
	DST_TMQ_BOARD_RESERVATION_PARTY,		// ��Ƽ����	
	DST_TMQ_BOARD_TEAM,						// ��
	DST_TMQ_BOARD_PRIVATE,					// ����
	DST_TMQ_BOARD_RESERVATING,				// ������
	DST_TMQ_DEGREE_OF_DIFFICULTY_1,			// ����
	DST_TMQ_DEGREE_OF_DIFFICULTY_2,			// ����
	DST_TMQ_DEGREE_OF_DIFFICULTY_3,			// �����

	DST_TMQ_STATUS_TITLE,					// Ÿ�Ӹӽ� ����Ʈ
	DST_TMQ_STATUS_INFO,					// ����
	DST_TMQ_STATUS_POINT,					// ����Ʈ
	DST_TMQ_STATUS_QUEST,					// ����Ʈ
	DST_TMQ_STATUS_LASTEST_RECORD,			// �ִܱ��
	DST_TMQ_STATUS_REMAIN_TIME,				// ����ð�
	DST_TMQ_STATUS_SENARIO,					// �ó�����
	DST_TMQ_STATUS_STATUS_INFO,				// ��������

	DST_TMQ_INDICATE_DROPRATE,				// ���Ȯ�� : 

	// RankBattle
	DST_RB_TITLE,							// ���� ��û
	DST_RB_FIELD,							// �����
	DST_RB_CHALLENGER_COUNT,				// ���� �ο�
	DST_RB_BTN_INDIVIDUAL,					// ��������
	DST_RB_BTN_PARTY,						// ��Ƽ����
	DST_RB_BTN_APPLY,						// ������û
	DST_RB_BTN_CANCEL,						// �������
	DST_RB_INFO_1,							// %s �Ŀ� ������ ���۵� �����Դϴ�. 
	DST_RB_INFO_2,							// ���� Ÿ�� : %s\n����� : %s\n���� ���� �ð� : %s ��

	DST_RB_APPLY_CHALLANGE,					// ������ ��û�Ͻðڽ��ϱ�?
	DST_RB_CANCEL,							// ���
	DST_RB_OK,								// Ȯ��

	DST_RB_STRAIGHT_WIN,					// ����
	DST_RB_PERFECT_WIN,						// �Ͻ�
	DST_RB_LEVEL_LIMIT,						// %uLv.~%uLv.
	DST_RB_PAGE,							// %u / %u
	DST_RB_LEVEL,							// %d ����

	DST_RB_SIDE_WAIT_FOR_ENTER,				// ��ũ��Ʋ ��������� (%u~%uLv)
	DST_RB_SIDE_CHECK_FOR_ENTER,			// ��ũ��Ʋ ����Ȯ�� (%u~%uLv)
	DST_RB_SIDE_DO_ENTER_RANKBATTLE,		// ��ũ��Ʋ�� �����Ͻðڽ��ϱ�?
	DST_RB_SIDE_RANKBATTLE_CANCELED,		// ��ũ��Ʋ�� ��ҵǾ����ϴ�.
	DST_RB_SIDE_DOING_RANKBATTLE,			// ��ũ��Ʋ ���Դϴ�.	
	DST_RB_SIDE_ON_ENTER,					// �����մϴ�
	DST_RB_SIDE_ON_ENTER_SECOND,			// %d�� �� ����

	DST_RB_SIDE_ENTER_SUCESS,				// ��������
	DST_RB_SIDE_ENTER_FAIL,					// �����Ұ�
	DST_RB_SIDE_ENTER_TOO_LOW_LEVEL,		// (��������)
	DST_RB_SIDE_ENTER_TOO_HIGHTLEVEL,		// (�����ʰ�)
	DST_RB_SIDE_ENTER_MUST_HAVE_NEED_ITEM,	// (�����۾���)
	DST_RB_SIDE_ENTER_MUST_HAVE_NEED_ZENNY, // (���Ϻ���)
	DST_RB_SIDE_ENTER_STATE_ERROR,			// (�����̻�)		// ��ȣ �� ��Ź!!

	DST_RB_VS,								// vs Ȥ�� ��

	DST_RB_RESULT_RECORD_INFO_1,			// �� %d�� %d�� %d��
	DST_RB_RESULT_RECORD_INFO_2,			// %d ���� ( �Ͻ� : %dȸ )
	DST_RB_RESULT_POINT_TEXT,				// ����
	DST_RB_RESULT_POINT_RESULT,				// ���
	DST_RB_RESULT_WAIT_TEXT,				// ��ø� ��ٷ� �ּ���.
	DST_RB_RESULT_WAIT_TIME,				// (���ѽð�:%u��)

	DST_RB_BLUE_TEAM,						// �����
	DST_RB_RED_TEAM,						// ������
	DST_RB_ENEMY_MEMBER,					// ����� ���

	DST_RB_RESULT_MESSAGE,					// �����ϼ̽��ϴ�. ����� �̵��մϴ�. (HTML����)

	DST_RANKBATTLE_SIDEVIEW_MESSAGE_JOIN,		// %s ��\n������û�� �Ͽ����ϴ�.
	DST_RANKBATTLE_SIDEVIEW_MESSAGE_MATCHFAIL,	// ���� ��븦 ã�� �� ����\n������ ����Ǿ����ϴ�.

	// Buff
	DST_BUFF_REMAIN_TIME,					// �����ð� %s
	DST_BUFF_DROP_TEXT,						// Ŭ���ϸ� ������ ��ȿȭ�� �� �ֽ��ϴ�.

	// Exp
	DST_EXP_INFO,							// EXP : %d / %d

	// Chat
	DST_CHAT_IME_ENG,						// A
	DST_CHAT_IME_KOR,						// ��

	// MainMenu
	DST_MAINMENU_HELP,						// ����
	DST_MAINMENU_STATUS,					// ���º���
	DST_MAINMENU_INVEN,						// ĸ��ŰƮ
	DST_MAINMENU_QUEST,						// ����Ʈ
	DST_MAINMENU_OPTION,					// �ɼ�
	DST_MAINMENU_COMMUNITY,					// Ŀ�´�Ƽ
	DST_MAINMENU_RANKBOARD,					// ��ũ����
	DST_MAINMENU_SKILL,						// ��ų
	DST_MAINMENU_FRIENDLIST,				// ģ������Ʈ
	DST_MAINMENU_END_SESSION,				// ��������
	DST_MAINMENU_CHANNEL_CHANGE,			// ä�κ���
	DST_MAINMENU_END_GAME,					// ��������
	DST_MAINMENU_TOOLTIP,					// ���θ޴�

	// MultiDialog
	DST_MULTIDIALOG_MENU_SHOP,				// ��������
	DST_MULTIDIALOG_MENU_SKILL,				// ��ų����
	DST_MULTIDIALOG_MENU_BANK,				// ���� ����
	DST_MULTIDIALOG_MENU_BUY_BANK,			// â�� ����
	DST_MULTIDIALOG_MENU_OPEN_GUILD_BANK,	// ��� â�� ����
	DST_MULTIDIALOG_MENU_QUEST,				// ����Ʈ �����ϱ�
	DST_MULTIDIALOG_MENU_UPGRADE,			// ������ ���׷��̵�
	DST_MULTIDIALOG_MENU_EXIT,				// ������
	DST_MULTIDIALOG_MENU_GUILD,				// ��� ����
	DST_MULTIDIALOG_MENU_TMQ,				// Ÿ�Ӹӽ� ����Ʈ

	DST_MULTIDIALOG_GUILDMENU_MAKE,				// ��� �����
	DST_MULTIDIALOG_GUILDMENU_CANCEL_DISSOLVE,	// ��� ��ü ���
	DST_MULTIDIALOG_GUILDMENU_DISSOLVE,			// ��� ��ü
	DST_MULTIDIALOG_GUILDMENU_POINT_USE,		// ��� ����Ʈ ���
	DST_MULTIDIALOG_GUILDMENU_CONTIBUTION,		// ��� ���� ���
	DST_MULTIDIALOG_GUILDMENU_CONTIBUTION_TITLE,// %d ���� ���

	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_20,		// �ִ� ����ο� 20��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_SECOND_MASTER_1,	// �θ����� 1��
	DST_MULTIDIALOG_GUILDFUNCTION_NOTICE,				// ��� ����
	DST_MULTIDIALOG_GUILDFUNCTION_POST,					// ��� ����
	DST_MULTIDIALOG_GUILDFUNCTION_WAREHOUSE,			// ��� â��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_30,		// �ִ� ����ο� 30��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_SECOND_MASTER_2,	// �θ����� 2��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_40,		// �ִ� ����ο� 40��
	DST_MULTIDIALOG_GUILDFUNCTION_CHANGE_NAME,			// ��� �̸� ����
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_50,		// �ִ� ����ο� 50��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_SECOND_MASTER_3,	// �θ����� 3��
	DST_MULTIDIALOG_GUILDFUNCTION_SET_EMBLEM,			// ��� ���� ���
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_60,		// �ִ� ����ο� 60��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_70,		// �ִ� ����ο� 70��
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_SECOND_MASTER_4,	// �θ����� 4��
	DST_MULTIDIALOG_GUILDFUNCTION_HAVE_DOJO,			// ���� ����	
	DST_MULTIDIALOG_GUILDFUNCTION_USE_DOJO_TELEPORT,	// ���� �ڷ���Ʈ
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_80,		// �ִ� ����ο� 80��
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_1,		// ���� ���׷��̵� ���� 1
	DST_MULTIDIALOG_GUILDFUNCTION_MAKE_DOGI,			// ���� ���
	DST_MULTIDIALOG_GUILDFUNCTION_MAKE_DOJO_DOGI,		// ���� ���� ���
	DST_MULTIDIALOG_GUILDFUNCTION_CHANGE_EMBLEM,		// ���� ����
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_2,		// ���� ���׷��̵� ���� 2
	DST_MULTIDIALOG_GUILDFUNCTION_TENKAICHI_SEED,		// õ������ ����ȸ �õ� ����
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_90,		// �ִ� ����ο� 90��
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_3,		// ���� ���׷��̵� ���� 3
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_QUEST_1,			// ���� ����Ʈ 1
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_MIX_RATE_UP_1,	// ���� �ͽ� Ȯ�� ���� 1
	DST_MULTIDIALOG_GUILDFUNCTION_MAX_MEMBER_100,		// �ִ� ����ο� 100��
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_4,		// ���� ���׷��̵� ���� 4
	DST_MULTIDIALOG_GUILDFUNCTION_CAN_CHANGE_DOGI,		// ���� ����
	DST_MULTIDIALOG_GUILDFUNCTION_CAN_CHANGE_DOJO_DOGI,	// ���� ���� ����
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_5,		// ���� ���׷��̵� ���� 5
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_QUEST_2,			// ���� ����Ʈ 2
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_VEHICLE,			// ���� Ż �� ���
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_6,		// ���� ���׷��̵� ���� 6
	DST_MULTIDIALOG_GUILDFUNCTION_CAN_HAVE_BOOK,		// ���� ����
	DST_MULTIDIALOG_GUILDFUNCTION_CAN_HAVE_SKILL,		// ���� ��ų
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_UPGRADE_7,		// ���� ���׷��̵� ���� 7
	DST_MULTIDIALOG_GUILDFUNCTION_DOJO_MIX_RATE_UP_2,	// ���� �ͽ� Ȯ�� ���� 2

	DST_MULTIDIALOG_DOJO_ESTABLISHMENT,					// ���� ����	
	DST_MULTIDIALOG_DOJO_INFO,							// ���� ����
	DST_MULTIDIALOG_DOJO_ACCOUNT,						// ���� â�� ��� ����

	DST_MULTIDIALOG_BUYBANKMENU_BUYBANK,				// â�� %d ���� %dZ
	DST_MULTIDIALOG_BUYBANKMENU_BUYPUBLIC_BANK,			// ����â�� ���� %dZ

	// Multidialog HoipoiMix Npc
	DST_MULTIDIALOG_HOIPOIMIX_SET_COMMAND,				// ȣ�����̹ͽ� ��ų ����
	DST_MULTIDIALOG_HOIPOIMIX_RESET_COMMAND,			// ȣ�����̹ͽ� ��ų �ʱ�ȭ�ϱ�

	DST_MULTIDIALOG_HOIPOIMIX_SET_FOOD_DRINK,			// ȣ�����̹ͽ� �⺻ ��ų ����
	DST_MULTIDIALOG_HOIPOIMIX_SET_MAIN_WEAPON,			// ȣ�����̹ͽ� ���ο��� ����� ��ų
	DST_MULTIDIALOG_HOIPOIMIX_SET_ARMOR,				// ȣ�����̹ͽ� �� ����� ��ų
	DST_MULTIDIALOG_HOIPOIMIX_SET_ACCESSORY,			// ȣ�����̹ͽ� �Ǽ����� ����� ��ų
	DST_MULTIDIALOG_HOIPOIMIX_SET_SCOUTER,				// ȣ�����̹ͽ� ��ī���� ����� ��ų
	DST_MULTIDIALOG_HOIPOIMIX_SET_SUB_WEAPON,			// ȣ�����̹ͽ� ������� ����� ��ų

	DST_MULTIDIALOG_HOIPOIMIX_RESET_NORMAL,				// ȣ�����̹ͽ� �Ϲ� ��� �ʱ�ȭ
	DST_MULTIDIALOG_HOIPOIMIX_RESET_SPECIAL,			// ȣ�����̹ͽ� Ư�� ��� �ʱ�ȭ

	// MsgBox
	DST_MSG_BOX_TITLE,						// �޼���
	DST_MSG_BTN_OK,							// Ȯ��
	DST_MSG_BTN_CANCEL,						// ���
	DST_MSG_REMAIN_TIME,					// [br][br] �����ð� : %s 

	// Bag
	DST_BAG_TITLE,							// �κ��丮
	DST_ZENNY_BTN,							// ������
	DST_DISCARD_BTN,						// ������
	DST_BAG_SLOT,							// ĸ�� ����,
	DST_BAG_REMOTE_SELL,					// �����Ǹ�,

	// DropItem
	DST_DROPITEM_ZENNY,						// %d ����

	// PopupMenu Text -> �ʿ���°� üũ�ؼ� �˷��ּ���
	DST_POPUPMENU_USE,							    // ����ϱ�
	DST_POPUPMENU_OPEN,								// ����
	DST_POPUPMENU_EQUIP,							// �����ϱ�
	DST_POPUPMENU_CANCEL_EQUIP,						// ��������
	DST_POPUPMENU_VIEW,								// ����
	DST_POPUPMENU_PICKUP,							// ����
	DST_POPUPMENU_STOP_USE,							// �������
	DST_POPUPMENU_PULLOUT,							// ������
	DST_POPUPMENU_SELL,								// �ȱ�
	DST_POPUPMENU_DIVIDE,							// ������
	DST_POPUPMENU_CLEAR,							// ����
	DST_POPUPMENU_DELETE,							// ������
	DST_POPUPMENU_PARTY_CREATE,						// ��Ƽ �����
	DST_POPUPMENU_PARTY_INVITE,						// ��Ƽ �ʴ�
	DST_POPUPMENU_PARTY_LEADER_CHANGE,				// ��Ƽ�� ����
	DST_POPUPMENU_PARTY_KICK_OUT,					// ��Ƽ ����
	DST_POPUPMENU_PARTY_LEAVE,						// ��Ƽ Ż��
	DST_POPUPMENU_PVP_REQUEST_FIGHT,				// ��� ��û
	DST_POPUPMENU_USER_TRADE,						// ���� �ŷ�
	DST_POPUPMENU_GUILD_INVITE,						// ��� �ʴ�
	DST_POPUPMENU_GUILD_CHANGE_MASTER,				// ����� �̾�
	DST_POPUPMENU_GUILD_APPOINT_SECOND_MASTER,		// �α���� �Ӹ�
	DST_POPUPMENU_GUILD_DISAPPOINT_SECOND_MASTER,	// �α���� ����
	DST_POPUPMENU_GUILD_KICK_OUT,					// ��� �߹�
	DST_POPUPMENU_GUILD_POST,						// ���� ������
	DST_POPUPMENU_FRIEND_ADD,						// ģ�� �߰�
	DST_POPUPMENU_FOLLOW,							// ���� ����
	DST_POPUPMENU_CANCEL,							// ���
	DST_POPUPMENU_SET_SHARETARGET_1,				// 1�� ����Ÿ�� ����
	DST_POPUPMENU_SET_SHARETARGET_2,				// 2�� ����Ÿ�� ����
	DST_POPUPMENU_SET_SHARETARGET_3,				// 3�� ����Ÿ�� ����
	DST_POPUPMENU_SET_SHARETARGET_4,				// 4�� ����Ÿ�� ����
	DST_POPUPMENU_SET_SHARETARGET_5,				// 5�� ����Ÿ�� ����
	DST_POPUPMENU_UNSET_SHARETARGET_1,				// 1�� ����Ÿ�� ����
	DST_POPUPMENU_UNSET_SHARETARGET_2,				// 2�� ����Ÿ�� ����
	DST_POPUPMENU_UNSET_SHARETARGET_3,				// 3�� ����Ÿ�� ����
	DST_POPUPMENU_UNSET_SHARETARGET_4,				// 4�� ����Ÿ�� ����
	DST_POPUPMENU_UNSET_SHARETARGET_5,				// 5�� ����Ÿ�� ����
	DST_POPUPMENU_PARTY_MENU_SWITCH_MEMBER,			// ��Ƽ �ɹ�â ����ġ
	DST_POPUPMENU_PARTY_MENU_SWITCH_MEMBER_BUFF,	// ��Ƽ �ɹ�â ���� ����ġ
	DST_POPUPMENU_PARTY_DUNGEON_INIT,				// ���� �ʱ�ȭ
	DST_POPUPMENU_PARTY_DUNGEON_NORMAL,				// ���� ���̵� ����
	DST_POPUPMENU_PARTY_DUNGEON_HARD,				// ���� ���̵� �����
	DST_POPUPMENU_PARTY_DIVIDE_PICKUP_PERSON,		///< �ݴ� ��� ȹ��
	DST_POPUPMENU_PARTY_DIVIDE_EQUAL,				///< �Ȱ��� ������
	DST_POPUPMENU_PARTY_DIVIDE_ORDER,				///< �����Ƿ� �й�
	DST_POPUPMENU_PARTY_GRADE_ITEM,					///< ��޺� �����Ƿ� �й�
	DST_POPUPMENU_PARTY_USE_INVEN,					///< ��Ƽ �κ��丮 ���

	// NPC job name
	DST_JOB_WEAPON_MERCHANT,						// �������
	DST_JOB_ARMOR_MERCHANT,							// �Ǻ�����
	DST_JOB_GOODS_MERCHANT,							// ��ȭ����
	DST_JOB_SCOUTER_MERCHANT,						// ��ī���ͻ���
	DST_JOB_GUARD,									// ���
	DST_JOB_SKILL_TRAINER_HFI,						// ������ ����
	DST_JOB_SKILL_TRAINER_HMY,						// ����� ����
	DST_JOB_SKILL_TRAINER_HEN,						// �����Ͼ� ����
	DST_JOB_SKILL_TRAINER_NFI,						// ���� ����
	DST_JOB_SKILL_TRAINER_NMY,						// ���� ����
	DST_JOB_SKILL_TRAINER_MMI,						// �븶�� ����
	DST_JOB_SKILL_TRAINER_MWO,						// �Ǹ��� ����
	DST_JOB_BANKER,									// â������ 
	DST_JOB_TALKER,									// �̾߱��
	DST_JOB_GUILD_MANAGER,							// ���Ŵ���
	DST_JOB_SUMMON_PET,								// ��ȯ��
	DST_JOB_DOGI_MERCHANT,							// ���� ����
	DST_JOB_SPECIAL_WEAPON_MERCHANT,				// ��� ���� ����
	DST_JOB_SPECIAL_ARMOR_MERCHANT,					// ��� �Ǻ� ����
	DST_JOB_SPECIAL_GOODS_MERCHANT,					// ��� ��ȭ ����
	DST_JOB_SPECIAL_FOODS_MERCHANT,					// ��� �ķ�ǰ ����
	DST_JOB_SPECIAL_SCOUTER_MERCHANT,				// ��� ��ī���� ����
	DST_JOB_GRAND_SKILL_TRAINER_HFI,				// ������ �׷��� ��ų������
	DST_JOB_GRAND_SKILL_TRAINER_HMY,				// ����� �׷��� ��ų������
	DST_JOB_GRAND_SKILL_TRAINER_HEN,				// �����Ͼ� �׷��� ��ų������
	DST_JOB_GRAND_SKILL_TRAINER_NFI,				// ���� �׷��� ��ų������
	DST_JOB_GRAND_SKILL_TRAINER_NMY,				// ���� �׷��� ��ų������
	DST_JOB_GRAND_SKILL_TRAINER_MMI,				// �븶�� �׷��� ��ų������
	DST_JOB_GRAND_SKILL_TRAINER_MWO,				// �Ǹ��� �׷��� ��ų������
	DST_JOB_SUB_WEAPON_MERCHANT,					// ���� ���� ����
	DST_JOB_GATE_KEEPER,							// ������
	DST_JOB_VENDING_MACHINE,						// ���Ǳ�
	DST_JOB_TIMEMACHINE_MERCHANT,					// Ÿ�Ӹӽ����� NPC
	DST_JOB_POTALMAN,								// ��Ż��
	DST_JOB_BUS,									// ����
	DST_JOB_RECEPTION,								// õ������ ����ȸ ������
	DST_JOB_BUDOHSI_MERCHANT,						// ������ ����
	DST_JOB_REFEREE,								// ����
	DST_JOB_GAMBLE_MERCHANT,						// �̱� ����
	DST_JOB_CHAMPION_MERCHANT,						// ���ǿ� ����
	DST_JOB_DOJO_MANAGER,							// ���� ������
	DST_JOB_DOJO_MERCHANT,							// ���� ����
	DST_JOB_DOJO_SEAL,								// ���� ����
	DST_JOB_DOJO_BANKER,							// ���� â��
	DST_JOB_MIX_MASTER,								// �ͽ� ������

	// Mob_Type
	DST_MOB_TYPE_ANIMAL,							// ����
	DST_MOB_TYPE_HUMAN_ANIMAL,						// ...
	DST_MOB_TYPE_DINOSAUR,
	DST_MOB_TYPE_ALIEN,
	DST_MOB_TYPE_ANDROID,
	DST_MOB_TYPE_ROBOT,
	DST_MOB_TYPE_DRAGON,
	DST_MOB_TYPE_DEVIL,
	DST_MOB_TYPE_UNDEAD,
	DST_MOB_TYPE_PLANT,
	DST_MOB_TYPE_INSECT,
	DST_MOB_TYPE_HUMAN,
	DST_MOB_TYPE_NAMEC,
	DST_MOB_TYPE_MAJIN,
	DST_MOB_TYPE_BUILDING,

	// Portal 
	DST_MULTIDIALOG_MENU_PORTAL,                    // ��Ż Ÿ��
	DST_PORTAL_START_POINT,                         // ���� ��ġ
	DST_PORTAL_ZENNY,                               // �ʿ� ����
	DST_PORTAL_DISABLE,                             // ���� ��ġ���� ���� �����ϴ�.
	DST_PORTAL_ADD,                                 // ���ο� �̵� ��θ� ����Ͽ����ϴ�.
	DST_PORTAL_ICON_START,                          // ���� ����Ʈ
	DST_PORTAL_ICON_ENABLE,                         // ����� ����Ʈ
	DST_PORTAL_ICON_DISABLE,                        // ��ϵ� ����Ʈ
	DST_PORTAL_ICON_NOT_REGIST,                     // �̵�� ����Ʈ
	DST_PORTAL_CONFIRM,                             // '%s'���� �̵��մϴ�. \n %d ���� �Һ�

	// Item Endurance warning
	DST_ITEM_DOFIX_SIDE_TEXT,						// ���� �������� 0�̵Ǿ� ����� �� ���� �������� �ֽ��ϴ�. �����...
	DST_ITEM_DOEXTEND_SIDE_TEXT,					// ���� ���Ⱓ�� ����� �������� �ֽ��ϴ�. ���Ⱓ�� �����Ͽ� �ֽʽÿ�.

	// Rank Board
	DST_RANKBOARD_BOARD_TITLE_PVP,					// PvP
	DST_RANKBOARD_BOARD_TITLE_TMQ,					// TMQ

	DST_RANKBOARD_BOARD_PREV,						// ���� ������
	DST_RANKBOARD_BOARD_NEXT,						// ���� ������

	DST_RANKBOARD_BOARD_DATALOADING,				// ������ ó�����Դϴ�.

	DST_RANKBOARD_BOARD_MSGBOX_TOPPAGE,				// ó�� �������Դϴ�.
	DST_RANKBOARD_BOARD_MSGBOX_NOTPAGE,				// �������� �����ϴ�.
	DST_RANKBOARD_BOARD_MSGBOX_NODATA,				// ������ ��ũ��Ʋ ����� �����ϴ�.
	DST_RANKBOARD_BOARD_MSGBOX_INPUTSEARCH,			// �˻��� ������ �̸��� �Է����ּ���.
	DST_RANKBOARD_BOARD_MSGBOX_NONESCENARIO,		// ���� �ó������Դϴ�.
	DST_RANKBOARD_BOARD_MSGBOX_NOTMEMBER,			// ��Ƽ�� ������ �����ϴ�.

	DST_RANKBOARD_RANKBATTLE_SUBJECT_RANK,			// ����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_NAME,			// �̸�
	DST_RANKBOARD_RANKBATTLE_SUBJECT_LEVEL,			// ����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_CLASS,			// ����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_GUILD,			// ���
	DST_RANKBOARD_RANKBATTLE_SUBJECT_POINT,			// ����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_STRAIGHTWIN,	// ����

	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE,		// ��������

	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_1,		// 1����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_2,		// 2����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_3,		// 3����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_4,		// 4����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_5,		// 5����
	DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_6,		// 6����

	DST_RANKBOARD_TMQ_SUBJECT_RANK,					// ����
	DST_RANKBOARD_TMQ_SUBJECT_PARTYNAME,			// ��Ƽ �̸�
	DST_RANKBOARD_TMQ_SUBJECT_CLEARTIME,			// Ŭ���� �ð�
	DST_RANKBOARD_TMQ_SUBJECT_PARTYMEMBERINFO,		// ��Ƽ�� ����
	DST_RANKBOARD_TMQ_SUBJECT_PARTYMEMBER,			// ��Ƽ ���
	DST_RANKBOARD_TMQ_SUBJECT_LEVEL,				// Lv.
	DST_RANKBOARD_TMQ_SUBJECT_CLASS,				// Ŭ����
	DST_RANKBOARD_TMQ_SUBJECT_SCENARIO,				// �ó����� %d

	DST_RANKBOARD_TMQ_OVER_TIME,					// �Ϸ�����

	// Friend List
	DST_FRIEND_TAB_FRIEND,                          // ģ�� ����Ʈ
	DST_FRIEND_TAB_BLACKLIST,                       // �� ����Ʈ
	DST_FRIEND_SUBJECT_NAME,                        // �̸�
	DST_FRIEND_SUBJECT_LEVEL,                       // ����
	DST_FRIEND_SUBJECT_LOC,                         // ��ġ
	DST_FRIEND_SUBJECT_CHANNEL,                     // ä��
	DST_FRIEND_OFFLINE,                             // ��������
	DST_FRIEND_ADD,                                 // �߰�
	DST_FRIEND_INVITE,                              // ��Ƽ �ʴ�
	DST_FRIEND_WHISPER,                             // �Ӽ� �� ������
	DST_FRIEND_MAIL,                                // ���� ������
	DST_FRIEND_BLOCK,                               // ����
	DST_FRIEND_DELETE,                              // ����
	DST_FRIEND_MSG_FRIEND_ADD,                      // ģ���� �߰��� ����� �̸��� �Է��ϰ� Ȯ���� �����ּ���
	DST_FRIEND_MSG_BLACK_ADD,                       // �� ����Ʈ�� �߰��� ������ �̸��� �Է��ϰ� Ȯ���� �����ּ���
	DST_FRIEND_MSG_FRIEND_DEL,                      // ���� ������ ģ�� ����Ʈ���� �����Ͻðڽ��ϱ�?
	DST_FRIEND_MSG_BLACk_DEL,                       // ���� ������ �� ����Ʈ���� �����Ͻðڽ��ϱ�?
	DST_FRIEND_MSG_LOGIN,                           // ���� ���ӿ� �����Ͽ����ϴ�
	DST_FRIEND_ERR_EXIST_BLACK,                     // �� ����Ʈ�� �ִ� ������ ģ���� �߰��� ���� �����ϴ�
	DST_FRIEND_ERR_EXIST_FRIEND,                    // ģ�� ����Ʈ�� ���ܹ�ư�� ����� ������ �ּ���
	DST_FRIEND_INVALID_USER,                        // ���õ� ����� �����ϴ�.
	DST_FRIEND_TOO_OVER_NAME,                       // �Է��� ĳ���� �̸��� �ʹ� ��ϴ�.

	// Communication Target Window
	DST_COMMU_TARGET_FRIEND,                        // ģ��
	DST_COMMU_TARGET_GUILD,                         // ���
	DST_COMMU_TARGET_PARTY,                         // ��Ƽ

	// Minimap
	DST_MINIMAP_CHECK_POINT,                        // üũ ����Ʈ
	DST_MINIMAP_SHOW_MINIMAP,                       // �̴ϸ� ����
	DST_MINIMAP_MINIMIZE,	                        // �̴ϸ� �ּ�ȭ
	DST_MINIMAP_SHOW_WORLDMAP,                      // �����
	DST_MINIMAP_ZOOM_IN,	                        // �̴ϸ� Ȯ��
	DST_MINIMAP_ZOOM_OUT,	                        // �̴ϸ� ���
	DST_MINIMAP_POPOSTONE,	                        // ��������
	DST_MINIMAP_HIDDEN,		                        // ������ ��ü
	DST_MINIMAP_UNKNOWN,		                    // �� �� ���� ��

	// WorldMap
	DST_WORLDMAP_TITLE,		                        // �����
	DST_WORLDMAP_TRANSPARENCY,                      // ����
	DST_WORLDMAP_BUS_ROUTE_PAINT,                   // ���� �뼱��
	DST_WORLDMAP_SHOW_OUR_GUILD_MEMBER,				// �츮 ���Ŀ�
	DST_WORLDMAP_SHOW_OUR_GUILD,					// �츮 ���Ŀ� ǥ��
	DST_WORLDMAP_SHOW_OUR_GUILD_IN_MINIMAP,			// �츮 ���Ŀ� �̴ϸʿ� ǥ��
	DST_WORLDMAP_SHOW_OTHER_GUILD_MEMBER,			// ��� ���Ŀ�
	DST_WORLDMAP_SHOW_OTHER_GUILD,					// ��� ���Ŀ� ǥ��
	DST_WORLDMAP_SHOW_OTHER_GUILD_IN_MINIMAP,		// ��� ���Ŀ� �̴ϸʿ� ǥ��

	// Chat Shortcut
	DST_CHAT_SHORT_CUT_GENERAL,						// '/n '
	DST_CHAT_SHORT_CUT_TRADE,						// '/t '
	DST_CHAT_SHORT_CUT_WHISPER,						// '/w '
	DST_CHAT_SHORT_CUT_PARTY,						// '/p '
	DST_CHAT_SHORT_CUT_PARTY_NOTIFY,				// '/c '
	DST_CHAT_SHORT_CUT_GUILD,						// '/g '
	DST_CHAT_SHORT_CUT_SHOUT,						// '/s '
	DST_CHAT_SHORT_CUT_LAST_WHISPER_USER,			// '/r '
	DST_CHAT_SHORT_CUT_HELP,						// '/? '
	DST_CHAT_SHORT_CUT_GENERAL_LOCAL,				// '/�� '
	DST_CHAT_SHORT_CUT_TRADE_LOCAL,					// '/�� '
	DST_CHAT_SHORT_CUT_WHISPER_LOCAL,				// '/�� '	Local�� ���� �༮�� ���� ������ �°� �����ؾ� �մϴ�.
	DST_CHAT_SHORT_CUT_PARTY_LOCAL,					// '/�� '
	DST_CHAT_SHORT_CUT_PARTY_LOCAL_NOTIFY,			// '/�� '
	DST_CHAT_SHORT_CUT_GUILD_LOCAL,					// '/�� '
	DST_CHAT_SHORT_CUT_SHOUT_LOCAL,					// '/�� '
	DST_CHAT_SHORT_CUT_LAST_WHISPER_USER_LOCAL,		// '/�� '
	DST_CHAT_SHORT_CUT_INVITE_PARTY,				// '/�ʴ� '
	DST_CHAT_SHORT_CUT_COMMAND,						// ä�� ��ɾ�
	DST_CHAT_HAVE_NO_USER_TO_REPLY,					// ����� ����� �����ϴ�.
	DST_CHAT_FAIL_TO_USE_WHISPER,					// �ӼӸ��� �ϱ����ؼ��� /w(/W,/��) ĳ�����̸� ���� �� ���Ĵ�� �Է��Ͽ��� �մϴ�.
	DST_CHAT_FAIL_TO_WHISPER_NO_TARGET,				// %s���� �α��λ��°� �ƴմϴ�.
	DST_CHAT_HELP_TEXT,								// ä�� ����Ű �����ؽ�Ʈ. ��ȹ�� ����
	DST_CHAT_OPTION_GUI_TITLE,						// ä�� �Է¸��

	// Tutorial Guide Window
	DST_TUTORIAL_GUIDE_TITLE,						// Ʃ�丮�� ���̵� ������

	// Mob Grade
	DST_MOB_GRADE_SUPER,							// ����
	DST_MOB_GRADE_ULTRA,							// ��Ʈ��
	DST_MOB_GRADE_BOSS,								// ����
	DST_MOB_GRADE_HERO,								// �����

	// TargetInfo
	DST_TARGET_MENU,								// Ÿ�� �޴�	(��ư ����)
	DST_TARGET_SHARED_TARGET,						// ���� Ÿ�� �޴� (��ư ����)

	// GuardGauge 
	DST_GUARD_GAUGE_CAN_USE,						// ���� ��ų�� ����մϴ�.
	DST_GUARD_GAUGE_CANNOT_USE,						// ���ð��� ���� ������\\n���� ��ų�� ����� �� �����ϴ�

	// Item Type
	DST_GLOVE,
	DST_STAFF,
	DST_GUN,
	DST_DUALDST_GUN,
	DST_CLAW,
	DST_AXE,
	DST_SCROLL,
	DST_GEM,
	DST_STICK,
	DST_SWORD,
	DST_FAN,
	DST_WAND,
	DST_BAZOOKA,
	DST_BACKDST_PACK,
	DST_INSTRUMENT,
	DST_CLUB,
	DST_DRUM,
	DST_MASK,

	// Side dialog title
	DST_SIDEDLG_TITLE_TMQINFO,						// TMQ ����
	DST_SIDEDLG_TITLE_TARGETITEMINFO,				// ��� ������ ����
	DST_SIDEDLG_TITLE_RANKBATTLEINFO,				// ��ũ��Ʋ ����
	DST_SIDEDLG_TITLE_QUESTINDICATOR,				// ����Ʈ �˸���

	// Scouter PC VIewer
	DST_SCOUTER_PC_VIEWER_WEAPON,					// ����
	DST_SCOUTER_PC_VIEWER_DEFENCE,					// ��
	DST_SCOUTER_PC_VIEWER_ACCESARY,					// ��ű�
	DST_SCOUTER_PC_VIEWER_SPECIAL,					// Ư��

	// Battle attribute info window text
	DST_BATTLEATTR_ATTR,							// �Ӽ� :
	DST_BATTLEATTR_WEAPON,							// ���� �Ӽ� : 
	DST_BATTLEATTR_ARMOR,							// �� �Ӽ� :
	DST_BATTLEATTR_ON_TARGET,						// ���� ��󿡰�
	DST_BATTLEATTR_ATTACK_RATE_TARGET,				// �Ӽ����� ���ݷ� %.0f%%
	DST_BATTLEATTR_DEFENCE_RATE_TARGET,				// �Ӽ����� ���� %.0f%%
	DST_BATTLEATTR_ATTACK_RATE,						// ���ݷ� %.0f%%
	DST_BATTLEATTR_DEFENCE_RATE,					// ���� %.0f%%

	// Ʃ�丮��
	DST_TUTORIAL_MESSAGE_START,				// �巡�ﺼ �¶����� ���迡 ���� ���� ȯ���մϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002000,			// �������� Ʃ�丮���� ���� �⺻ ���۹��� ��� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002100,			// ���콺 ������ ��ư�� ����ä ���콺�� ������ ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002200,			// �̷��� ī�޶� �����̸� �ֺ��� ���̳� ����, ������ ��ġ�� �� �ľ��� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002300,			// üũ����Ʈ �ֺ��� Ŀ���� �̵���Ű�� ���콺 ���� ��ư�� ���� �ڽ��� ĳ���͸� ������ ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002400,			// ĳ���ʹ� ���콺���� �ƴ϶� Ű���带 ����ؼ� ������ ���� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002500,			// W, A, S, D Ű�� ���� üũ����Ʈ���� �̵��� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002600,			// �� �ܿ��� ĳ���͸� �����̴� �پ��� ����� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002700,			// õ���浵 �� �������Ͷ�� ���� �ֽ��ϴ�. ���� ����������� �սô�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002800,			// ĳ���� ����â������ �����(LP), ���(EP), Level �� ĳ���Ϳ� ���� �������� ������ �� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_002900,			// �̴ϸʿ����� NPC�� ����, ���� �� �ڽ��� ĳ���� �ֺ��� ������ ������ �ľ��� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003000,			// ä��â������ �ٸ� ������, ģ��, ��Ƽ����� ��ȭ�� �� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003100,			// ����â������ ��ų�̳� �������� ����� ������ �����ϰ� ����� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003200,			// ���θ޴��� ���콺 ���� ��ư���� ���� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003300,			// ��ų ��ư�� ���콺 ���� ��ư���� ������ ��ųâ�� ���� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003400,			// ��ų�������� ���콺 ���� ��ư���� ���� �ֽʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003500,			// ����â�� �� ������ ���콺 ���� ��ư���� ������ ��ų�������� ����� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003600,			// �̷��� ����â�� ��ų�� ����� ������ ������ �����ϰ� ����� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003700,			// ��ųâ�� �ݱ� ��ư�� ���콺 ���� ��ư���� ������ ��ųâ�� �ݾ� �ֽʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003800,			// ����, ���θ޴��� ��� ���� ����� �� �ְ� �Ǿ����ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_003900,			// ���� ����Ű�� â�� �� �� �ְ� �Ǿ����ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004000,			// ���͸� ���콺 ���� ��ư�� ������ Ÿ������ ������ ���ʽÿ�.(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004100,			// ���͸� ���콺 ������ ��ư�� ���� ������ ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004200,			// ���͸� ������ �� ����â�� ���콺 ������ ��ư�� �����ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004300,			// �̷��� ��ų�� ����ϸ� �ξ� ������ ������ �� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004400,			// ��ų�� ����â�� Ű���� ����Ű '1'���� '='�� ������ ����� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004500,			// �ֺ��� ������ ĸ��ŰƮ�� ���콺 ���� ��ư�� ������ �ֿ� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004600,			// �⺻ ĸ��ŰƮ�� ���콺 ������ ��ư���� ���� ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004700,			// ĸ��ŰƮ�� ��ī���͸� ���콺 ������ ��ư�� ���� ������ ���ʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004800,			// ���� ��ī���͸� ���������� ��ī���͸� ����� �� �ְ� �Ǿ����ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_004900,			// Ű���� ����Ű 'T'�� ���� ��ī���͸� ���ּ���(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005000,			// ���͸� Ÿ������ ������ �ֽʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005100,			// ���͸� Ÿ������ ���������� ��ī���� �޴��� 'PowerLevel'�� ������ �ֽʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005200,			// �̸��� �� �� ���� ������ �̸��� �ٷ� "������'�̿�����(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005300,			// �̷��� ��ī���͸� ���̳� ���Ḧ �����ϸ� �� �� ���� �������� �˾Ƴ� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005400,			// ��ī������ �ݱ� ��ư�� ������ ��ī���͸� �ݾ� �ֽʽÿ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005500,			// ��ī���ͳ� �ٸ� â�� ���� ���� 'ESC'Ű�� ���� ������ ���� ���� �ֽ��ϴ�)
	DST_TUTORIAL_MESSAGE_005600,			// ���θ޴��� ���� �޴��� �����ϸ� ����â�� �� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005700,			// ����â������ Ʃ�丮�󿡼� ����� ���ߴ� ���� ���� ��� �� �ֽ��ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005800,			// Dbo�� ���踦 Ÿ���ϸ鼭 �𸣴� ���� �ִ� ���� ����� ���ߴ� ������ �����ϴ� ���� ���� ����Դϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_005900,			// ���� �巡�ﺼ �¶��� ����� ������ �������ô�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_006000,			// ���� �����뿡 �������� ���� �� �ְ� �Ǿ����ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_006100,			// ���� ������ �������� ���콺 ������ ��ư���� ���� �� �ְ� �Ǿ����ϴ�(message, Ʃ�丮�� ���� �޼���)
	DST_TUTORIAL_MESSAGE_006200,		    //	Scouter��  Window�� ���� ���� 'ESC' Ű�� ���� ������ ���� ���� �ֽ��ϴ�.
	DST_TUTORIAL_MESSAGE_006300,			//	�������� ����� �� �ְ� �Ǿ����ϴ�.
	DST_TUTORIAL_MESSAGE_006400,			//	������ �������� Mouse Right Button���� ���� �� �ְ� �Ǿ����ϴ�.
	DST_TUTORIAL_MESSAGE_006500,			//	Mainmenu�� ���� �޴��� �����ϰų� ����Ű F1�� ���� ���� Window�� ���� �ֽ��ϴ�.
	DST_TUTORIAL_MESSAGE_006600,			//	���� Window������ Tutorial���� ����� ���ߴ� ���� ���� ��� �� �ֽ��ϴ�
	DST_TUTORIAL_MESSAGE_006700,			//	DBO�� ���踦 Ž���ϸ鼭 �𸣴� ���� ���� ���� ������ �����ϴ� ���� ���� �������.
	DST_TUTORIAL_MESSAGE_006800,			//	��, DBO�� ����� ������ �������ô�. ������!
	DST_TUTORIAL_MESSAGE_006900,			//	Minimap �ּ�ȭ �ϱ�

	// Caution SideIcon
	DST_CAUTION_SIDEICON_TITLE,				// ��� �޽���

	// �ֻ���
	DST_DICE_EXPLAIN,						// �ֻ���(1~99)�� �����ϴ�
	DST_DICE_EXPLAIN2,						// �ֻ����� Ŭ���� �ּ���
	DST_DICE_BUDOKAI_MINOR_EXPLAIN,			// �ֻ����� �ڵ����� �������ϴ�.

	// õ������ ����ȸ
	DST_BUDOKAI_NEWS_TITLE,					// �� %d ȸ õ�����Ϲ���ȸ

	DST_BUDOKAI_NEWS_HEADLINE_OPENNOTICE,	// õ������ ����ȸ ����!
	DST_BUDOKAI_NEWS_HEADLINE_DOJORECOMMEND,// õ������ ����ȸ ���� ��õ�� ��û �Ⱓ
	DST_BUDOKAI_NEWS_HEADLINE_REGISTER,		// õ������ ����ȸ ���� ��û �Ⱓ
	DST_BUDOKAI_NEWS_HEADLINE_MAJOR,		// õ������ ����ȸ ���� �Ⱓ
	DST_BUDOKAI_NEWS_HEADLINE_AWARD,		// õ������ ����ȸ ��!

	DST_BUDOKAI_NEWS_NOTICE_GUIDE_MINOR_TITLE,	// ���� ��û �Ⱓ
	DST_BUDOKAI_NEWS_NOTICE_GUIDE_DOJO_TITLE,	// ���� ��õ�� ��õ �Ⱓ
	DST_BUDOKAI_NEWS_NOTICE_GUIDE_TIME,		// %d�� %d�� %s %d:%d
	DST_BUDOKAI_NEWS_NOTICE_GUIDE_TIME_FULL,// %s ~ %s 
	DST_BUDOKAI_NEWS_NOTICE_GUIDE_TIME_AM,	// ����
	DST_BUDOKAI_NEWS_NOTICE_GUIDE_TIME_PM,	// ����

	DST_BUDOKAI_NEWS_NOTICE_INDI_STATE,		// ������ ���� �ȳ�
	DST_BUDOKAI_NEWS_NOTICE_TEAM_STATE,		// ���� ���� �ȳ�

	DST_BUDOKAI_NEWS_NOTICE_INDI_REGISTER,	// ������ ���� ��û �Ⱓ �ȳ�
	DST_BUDOKAI_NEWS_NOTICE_TEAM_REGISTER,	// ���� ���� ��û �Ⱓ �ȳ�

	DST_BUDOKAI_NEWS_NOTICE_WAIT_GUIDE,		// %s �Ⱓ �ȳ� : %s
	
	DST_BUDOKAI_NEWS_NOTICE_INDI_WINNER,	// ������ ���/�� ���
	DST_BUDOKAI_NEWS_NOTICE_TEAM_WINNER,	// ���� ���/�� ���

	DST_BUDOKAI_NEWS_NOTICE_PRIZE_WINNER,	// ����� : %s
	DST_BUDOKAI_NEWS_NOTICE_PRIZE_SECOND_WINNER,	// �� ����� : %s

	DST_BUDOKAI_NEWS_NOTICE_PRIZE_TEAM_WINNER,	// ����� : %s
	DST_BUDOKAI_NEWS_NOTICE_PRIZE_TEAM_SECOND_WINNER,	// �� ����� : %s

	DST_BUDOKAI_NEWS_NOTICE_NOT_PRIZE,		// �����ڰ� �����ϴ�.
	DST_BUDOKAI_NEWS_NTOCIE_NOT_PRIZE_TEAM,	// �������� �����ϴ�.
	
	DST_BUDOKAI_REQUEST_MINOR,				// ���� 
	DST_BUDOKAI_REQUEST_MAJOR,				// ����
	DST_BUDOKAI_REQUEST_FINAL,				// �ἱ

	DST_BUDOKAI_TYPE_ADULT_TITLE,			// ���κ�
	DST_BUDOKAI_TYPE_CHILD_TITLE,			// �ҳ��

	DST_BUDOKAI_NEWS_BUTTON_INDIREQ,		// ���� ��û
	DST_BUDOKAI_NEWS_BUTTON_TEAMREQ,		// ��Ƽ ��û
	DST_BUDOKAI_NEWS_BUTTON_TICKET,			// ������
	DST_BUDOKAI_NEWS_BUTTON_TOURNAMENT,		// ����ǥ

	DST_BUDOKAI_NEWS_CAN_ONLY_LEADER,		// ��Ƽ�� �������� ��Ƽ�� ��û�� �� �� �ֽ��ϴ�.
	DST_BUDOKAI_NEWS_YOU_ARE_NOT_ENTRANT,	// ����� õ������ ����ȸ �����ڰ� �ƴմϴ�.
	
	DST_BUDOKAI_NEWS_INFO_INDI_STATE,		// ����� ������ %s �Դϴ�.
	DST_BUDOKAI_NEWS_INFO_TEAM_STATE,		// ����� ��Ƽ�� %s �Դϴ�.

	DST_BUDOKAI_NEWS_INFO_STATE_REGISTER,	// %s ���� ������ %s �Ŀ� �����˴ϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_WAIT_MINOR_MATCH,	// %s �������� %s �Ŀ� ���۵˴ϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_MINOR_MATCH,		// %s �������� ���� �� �Դϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_WAIT_MAJOR_MATCH,	// %s %s�� %s �Ŀ� ���۵˴ϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_MAJOR_MATCH,		// %s %s�� ���� ���Դϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_WAIT_SEMIFINAL_MATCH,	// %s �ذ���� %s �Ŀ� ���۵˴ϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_SEMIFINAL_MATCH,	// %s �ذ���� ���� �� �Դϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_WAIT_FINAL_MATCH,	// %s ����� %s �Ŀ� ���۵˴ϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_FINAL_MATCH,		// %s ����� ���� �� �Դϴ�.
	DST_BUDOKAI_NEWS_INFO_STATE_MATCH_END,			// %s �� �������ϴ�.

	DST_BUDOKAI_NEWS_NEXT_MUDOSA_OPEN,				// ���� ����ȸ ���� ���� : %s
	DST_BUDOKAI_NEWS_MUDOSA_ENTER_LEFT_TIME,		// ������ ���� ���� ���� : %s ���ҽ��ϴ�.
	DST_BUDOKAI_NEWS_NOPLAN,						// ����

	DST_BUDOKAI_REQUEST_TITLE,				// ��û��
	DST_BUDOKAI_TICKET_TITLE,				// ������

	DST_BUDOKAI_INDI_REQ_NAME,				// �̸�
	DST_BUDOKAI_INDI_REQ_LEVEL,				// ����
	DST_BUDOKAI_INDI_REQ_CLASS,				// Ŭ����
	DST_BUDOKAI_INDI_REQ_RECORD,			// ����
	DST_BUDOKAI_INDI_REQ_RANKING,			// ��ŷ����Ʈ
	DST_BUDOKAI_INDI_REQ_GUILD,				// �Ҽ�����

	DST_BUDOKAI_INDI_REQ_RECORD_DATA,		// %d�� %d�� %d��

	DST_BUDOKAI_TEAM_REQ_TEAMNAME,			// ���̸�:
	DST_BUDOKAI_TEAM_REQ_TEAMLEVEL,			// Lv. %d

	DST_BUDOKAI_SUCCESS_APPLICATION,		// %s ��û�� �Ϸ�Ǿ����ϴ�.
	DST_BUDOKAI_SUCCESS_GUIDE,				// %s�� ������ȣ:
	DST_BUDOKAI_SUCCESS_MEMBER,				// Member
	
	DST_BUDOKAI_INDI_DOJO_RECOMMNED,		// ���� ��õ ���� ������
	DST_BUDOKAI_TEAM_LEAVE_NOTIFY,			// ���� ������ õ������ ����ȸ ��û�� ����Ͽ����ϴ�.
	DST_BUDOKAI_TEAM_MEMBER_LEAVE_NOTIFY,	// %s�� õ������ ����ȸ ��û�� ����Ͽ����ϴ�.

	DST_BUDOKAI_REQ_BUTTON_ACCEPT,			// ��û�ϱ�
	DST_BUDOKAI_REQ_BUTTON_CANCEL,			// ��û���

	// ��û ���
	DST_BUDOKAI_INDI_REQ_CANCEL,			// ������ ��û�� ����Ͻðڽ��ϱ�?
	DST_BUDOKAI_TEAM_REQ_CANCEL,			// ���� ��û�� ����Ͻðڽ��ϱ�?

	DST_BUDOKAI_PC_STATE_NONE,				// ��û����
	DST_BUDOKAI_PC_STATE_MINOR_APPLICANT,	// ���� ��û��
	DST_BUDOKAI_PC_STATE_MINOR_ENTRY,		// ���� ������
	DST_BUDOKAI_PC_STATE_32_ENTRY,			// 32�� ������
	DST_BUDOKAI_PC_STATE_16_ENTRY,			// 16�� ������
	DST_BUDOKAI_PC_STATE_8_ENTRY,			// 8�� ������
	DST_BUDOKAI_PC_STATE_SEMIFINAL_ENTRY,	// �ذ�� ������
	DST_BUDOKAI_PC_STATE_FINAL_ENTRY,		// ��� ������

	DST_BUDOKAI_PC_STATE_MINOR_DROPOUT,		// ���� Ż��
	DST_BUDOKAI_PC_STATE_32_DROPOUT,		// 32�� Ż��
	DST_BUDOKAI_PC_STATE_16_DROPOUT,		// 16�� Ż��
	DST_BUDOKAI_PC_STATE_8_DROPOUT,			// 8�� Ż��
	DST_BUDOKAI_PC_STATE_PRIZE_WINNER,		// �Ի���
	DST_BUDOKAI_PC_STATE_SEMIFINAL_WINNER,	// �ؿ����
	DST_BUDOKAI_PC_STATE_FINAL_WINNER,		// �����

	DST_BUDOKAI_MINORMATCH_INFO_TITLE,			// ��Ʋ�ξ�
	DST_BUDOKAI_MINORMATCH_ENEMY_NAME_TITLE,	// �̸�
	DST_BUDOKAI_MINORMATCH_KOCOUNTER_TITLE,		// K.O
	DST_BUDOKAI_MINORMATCH_ALIVE_TITLE,			// ���� �ο�
	DST_BUDOKAI_MINORMATCH_TOTAL_TITLE,			// ��ü �ο�

	DST_BUDOKAI_REGISTER_INFO_TITLE,		// ��� �Ⱓ
	DST_BUDOKAI_MINORMATCH_INFO_TITLE_WAIT,	// ������ ���
	DST_BUDOKAI_MINORMATCH_INFO_TITLE_BATTLE,	// ������
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_32_WAIT,	// 32�� ���
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_32,	// 32��
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_16_WAIT,	// 16�� ���
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_16,	// 16��
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_8_WAIT,	// 8�� ���
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_8,	// 8�� 
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_SEMIFINAL_WAIT,	// �ذ�� ���
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_SEMIFINAL, // �ذ��
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_FINAL, // ���
	DST_BUDOKAI_MAJORMATCH_INFO_TITLE_END,		// �û��

	DST_BUDOKAI_TIME_DAY,					// %d ��
	DST_BUDOKAI_TIME_HOUR,					// %d �ð�
	DST_BUDOKAI_TIME_MINUTE,				// %d ��
	DST_BUDOKAI_TIME_SECOND,				// %d ��

	DST_BUDOKAI_TOURNAMENT_A_GROUP,			// A��
	DST_BUDOKAI_TOURNAMENT_B_GROUP,			// B��
	DST_BUDOKAI_TOURNAMENT_FINAL,			// �ἱ
	DST_BUDOKAI_TOURNAMENT_INFO_1,			// ��ʸ�Ʈ ǥ ������.

	DST_BUDOKAI_TELEPORT_MSG_TBSERVER,		// ������ ( ����� õ������ ����ȸ ������ �̵��ϴ� �ſ��� )
	DST_BUDOKAI_TELEPORT_MSG_MATCH,			// %s ����� ( ���� 32�� �����, ���� 16�� �����, �ἱ 16�� ����� ���.. )

	// Budokai Side icon
	DST_BUDOKAI_SIDEICON_TITLE,				// õ������ ����ȸ

	DST_BUDOKAI_NOTICE_SOLO,				// ������
	DST_BUDOKAI_NOTICE_PARTY,				// ��Ƽ��

	// �ҳ��, ���κ� �۾� ������ �и��մϴ�.
	DST_BUDOKAI_NOTICE_OPEN_NOTICE,			// õ������ ����ȸ %s ���� �����Դϴ�.
	DST_BUDOKAI_NOTICE_DOJO_RECOMMEND,		// %s ���� ��õ�� �����մϴ�.
	DST_BUDOKAI_NOTICE_REGISTER,			// %s %s ���� ��� ��û�� �޽��ϴ�.
	DST_BUDOKAI_NOTICE_WAIT_MINOR_MATCH,	// %s %s ������ ��� �Ⱓ�Դϴ�.
	DST_BUDOKAI_NOTICE_MINOR_MATCH,			// %s %s �������� ���۵Ǿ����ϴ�.
	DST_BUDOKAI_NOTICE_WAIT_MAJOR_MATCH,	// %s %s %s ��� �Ⱓ�Դϴ�.
	DST_BUDOKAI_NOTICE_MAJOR_MATCH,			// %s %s %s�� ���۵Ǿ����ϴ�.
	DST_BUDOKAI_NOTICE_WAIT_SEMIFINAL_MATCH,// %s %s �ذ�� �غ����Դϴ�.
	DST_BUDOKAI_NOTICE_SEMIFINAL_MATCH,		// %s %s �ذ���� ���۵Ǿ����ϴ�.
	DST_BUDOKAI_NOTICE_WAIT_FINAL_MATCH,	// %s %s ��� �غ� �Ⱓ�Դϴ�.
	DST_BUDOKAI_NOTICE_FINAL_MATCH,			// %s %s ������� ���۵Ǿ����ϴ�.
	DST_BUDOKAI_NOTICE_END,					// %s %s �û���� �������Դϴ�.

	DST_BUDOKAI_NOTICE_DATA_LOADING,		// õ������ ����ȸ�� ������ �ҷ����� �ֽ��ϴ�.

	// Budokai Gamble System
	DST_GAMBLE_GUIDE,						// �޴��� �������ּ���.\\n(ĸ��ŰƮ�� �������� %d pt�� �ʿ��մϴ�. 
	DST_GAMBLE_GUIDE_RESULT,				// ĸ���� ���Խ��ϴ�.\\nĸ��ŰƮ���� Ȯ�����ּ���.
	DST_GAMBLE_COMMAND,						// �̱�!!
	DST_GAMBLE_NOT_ENOUGH_MUDOSA_POINT,		// ������ ����Ʈ�� ���ڶ��ϴ�.

	// Budokai Tournament TeamInfo
	DST_BUDOKAI_TEAMINFO_TITLE,				// �������
	DST_BUDOKAI_TEAMINFO_MATCH_NAME_COMMON,	// %d���� ��%u���
	DST_BUDOKAI_TEAMINFO_MATCH_NAME_SEMIFINAL,// �ذ�� �� %u���
	DST_BUDOKAI_TEAMINFO_MATCH_NAME_FINAL,	// ���
	DST_BUDOKAI_TEAMINFO_CLASS,				// Ŭ����
	DST_BUDOKAI_TEAMINFO_LEVEL,				// ����
	DST_BUDOKAI_TEAMINFO_RECORD,			// ����
	DST_BUDOKAI_TEAMINFO_RECORD_DATA,		// %u�� %u�� %u��
	DST_BUDOKAI_TEAMINFO_RANKING_POINT,		// ��ŷ����Ʈ(PT)
	DST_BUDOKAI_TEAMINFO_GUILD_NAME,		// �Ҽ�����
	DST_BUDOKAI_TEAMINFO_LEVEL_CLASS,		// Lv.%u %s

	DST_BUDOKAI_TEAMINFO_LEVEL_VALUE,		// Lv.%u
	DST_BUDOKAI_TEAMINFO_PRIVATE_RECORD,	// ��������
	DST_BUDOKAI_TEAMINFO_NOT_IN_GUILD,		// �̰���

	DST_BUDOKAI_TEAMINFO_DOJO_RECOMMAND,	// ���� ��ǥ	

	// Budokai Result Narration
	DST_BUDOKAI_RESULT_MESSAGE,				// �����ϼ̽��ϴ�. ������ ������ �̵��մϴ�. (HTML����)
	DST_BUDOKAI_RESULT_MESSAGE_SEMIFINAL_1,	// HTML : �׾߸��� ������ �Ƿ��ĵ��� ����Դϴ�. �̹� ��ȸ�� ���� ��ȸ�� �� �� �����ϴ�. 
	DST_BUDOKAI_RESULT_MESSAGE_SEMIFINAL_2,	// HTML : �� �̾� ���� ��Ⱑ ���۵˴ϴ�. �� ��ȸ���� ����Ͽ� ���� ���� ���и� �븮�ñ� �ٶ��ϴ�.
	DST_BUDOKAI_RESULT_MESSAGE_FINAL,		// HTML : ���� ���ڰ� ���������ϴ�. ����Դϴ�. ���! ����ڿ��Դ� ������ �ο� ���� �־����ϴ�. ���ϵ帳�ϴ�.

	// ����
	DST_BUDOKAI_PROGRESS_MESSAGE_START,					// õ�����Ϲ���ȸ�� ���۵˴ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_RECEIVE_NEWS,			// �ҽ����� ��� �Ǿ����ϴ�.

	// ����
	DST_BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_ENTERING,	// ���� ���� �����մϴ�. 
	DST_BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_ENTERING2,  // ������ �����ϼŵ� �����ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_BEFORE_1MIN,// �� ���� ������ ���۵˴ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_BEFORE_1MIN2,// ������ ���ѷ� �ֽʽÿ�.

	DST_BUDOKAI_PROGRESS_MESSAGE_MATCH_END,				// %s ���� %s ������ ����Ǿ����ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MATCH_WINNER,			// �����մϴ�. %s ������ Ȯ�� �Ǽ̽��ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MATCH_LOSER,			// ��Ÿ���Ե� %s�� �������� ���ϼ̽��ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MATCH_ALL_FINISHED,	// %s�� ��� ����Ǿ����ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MATCH_DECISION_NEXT,	// %s �����ڰ� ��� �����Ǿ����ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_MATCH_BEFORE_10SEC,	// 10�� �� %s ��������� �ڵ� ���� �մϴ�.

	DST_BUDOKAI_PROGRESS_MESSAGE_MINOR,					// ����
	DST_BUDOKAI_PROGRESS_MESSAGE_32,					// 32��
	DST_BUDOKAI_PROGRESS_MESSAGE_16,					// 16��
	DST_BUDOKAI_PROGRESS_MESSAGE_8,						// 8��
	DST_BUDOKAI_PROGRESS_MESSAGE_SF,					// �� ���

	// �� ���
	DST_BUDOKAI_PROGRESS_MESSAGE_SEMI_FINAL_RUNNING,		// �� ����� �������Դϴ�. ��� �Ͽ� �ֽʽÿ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_FINAL_WAIT_LOSER,			// ����� ���� �� �� �û���� �ֽ��ϴ�.
	DST_BUDOKAI_PROGRESS_MESSAGE_FINAL_WAIT_LOSER1,			// ���� �����ø� ������ ���� �� �����ϴ�.

	DST_BUDOKAI_PROGRESS_MESSAGE_END,						// õ������ ����ȸ�� ��� ����Ǿ����ϴ�

	DST_BUDOKAI_MUDOSA_INFO,								// ������ ���� %d��
	DST_BUDOKAI_MUDOSA_TELEPOR_INFO,						// ������ ������ �̵��մϴ�.

	// loading
	DST_TODAT_TIP,							// ������ ����

	// Petition
	DST_PETITION_TITLE,						// GM ��� ��û
	DST_PETITION_GREAT_CATEGORY,			// ��з�
	DST_PETITION_SMALL_CATEGORY,			// �Һз�
	DST_PETITION_SATISFACTION_TITLE,		// GM ��� ��û
	DST_PETITION_SATISFACTION_COMMENT,		// ��� ���뿡 ���� �ǰ��� �˷��ּ���
	DST_PETITION_SATISFACTION_GREAT,		// ���� ����
	DST_PETITION_SATISFACTION_GOOD,			// ����
	DST_PETITION_SATISFACTION_NOT_BAD,		// ����
	DST_PETITION_SATISFACTION_BAD,			// �Ҹ�
	DST_PETITION_SATISFACTION_WORST,		// �ſ� �Ҹ�
	DST_PETITION_SEND,						// ����
	DST_PETITION_GM_CHAT_TITLE,				// GM ��ȭâ

	DST_PETITION_CATEGORY1_ACCUSE,			// �ҷ� �̿��� �Ű�
	DST_PETITION_CATEGORY1_BUG,				// ���� ����
	DST_PETITION_CATEGORY1_GAMEINFO,		// ���� ����
	DST_PETITION_CATEGORY1_STUCK,			// ĳ���� �̵� �Ұ�

	DST_PETITION_CATEGORY2_ACCUSE_AUTOPROGRAM,	// �ҹ� ���α׷�
	DST_PETITION_CATEGORY2_ACCUSE_FRAUD,		// ���
	DST_PETITION_CATEGORY2_ACCUSE_PAPERING,		// ����
	DST_PETITION_CATEGORY2_BUG_SYSTEM,			// �ý���
	DST_PETITION_CATEGORY2_BUG_GRAPHIC,			// �׷���
	DST_PETITION_CATEGORY2_BUG_ETC,				// ��Ÿ
	DST_PETITION_CATEGORY2_GAME_INFO,			// ���� ����
	DST_PETITION_CATEGORY2_STUCK,				// ĳ���� �̵� �Ұ�

	DST_PETITION_CANCEL_PETITION,				// GM ��� ���

	// Teleport
	DST_TELEPORT_COMMON_CONFIRM_MSG,			// �� ��ҷ� ���� �̵� �Ͻðڽ��ϱ�? ( ��ҿ� ���ѽð� )
	DST_TELEPORT_COMMON_CONFIRM_YES_BTN,		// �̵��Ѵ�.
	DST_TELEPORT_COMMON_CONFIRM_NO_BTN,			// ���� �ʴ´�.
	DST_TELEPORT_FINAL_CONFIRM_MSG,				// ���� �����̵��� ����Ͻðڽ��ϱ�? ( ��ҽ� �ش���ҷ� �̵��� �� ���ٴ� ���� ��� )
	DST_TELEPORT_FINAL_CONFIRM_YES_BTN,			// �����̵��� ���
	DST_TELEPORT_FINAL_CONFIRM_NO_BTN,			// �ٽ� �����ϱ�

	// Observer system
	DST_OBSERVER_RECORD,						// %d�� %d�� %d��(Playerinfo â����..)

	DST_OBSERVER_SHOW_AVATAR,					// �ƹ�Ÿ ���̱�
	DST_OBSERVER_HIDE_AVATAR,					// �ƹ�Ÿ �����
	DST_OBSERVER_TENKAICHI,						// õ������ ����ȸ �޴�
	DST_OBSERVER_PORTAL,						// �ƹ�Ÿ �̵�
	DST_OBSERVER_FREE_CAMERA,					// ���� ī�޶�
	DST_OBSERVER_NORMAL_CAMERA,					// 3��Ī ī�޶�

	DST_OBSERVER_CAMERA_LOC,					// ī�޶� ��ġ ����
	DST_OBSERVER_CAMERA_MOVE,					// ī�޶� �̵�
	DST_OBSERVER_MENU_ON,						// �޴� On
	DST_OBSERVER_MENU_OFF,						// �޴� Off
	DST_OBSERVER_PLAYER_INFO,					// ���� ����
	DST_OBSERVER_TOURNAMENT,					// ����ǥ 

	// Ż ��
	DST_VEHICLE_GET_OFF,						// ������
	DST_VEHICLE_ENGINE_START,					// ���� �õ��ɱ�
	DST_VEHICLE_ENGINE_STOP,					// ���� ���߱�

	// HoipoiMix System
	DST_HOIPOIMIX_CREATE,						// ȣ������ ĸ�� �����ϱ�
	DST_HOIPOIMIX_FARERATE,						// ȣ������ �ӽ� ���� ����
	DST_HOIPOIMIX_MACHINE_DEL,					// ȣ������ �ӽ� ȸ���ϱ�	

	DST_HOIPOIMIX_RECIPE_TAB,					// ������
	DST_HOIPOIMIX_RECIPE_FILTER_TOTAL,			// ��ü	( ������ ����� ���� ��ư )
	DST_HOIPOIMIX_RECIPE_FILTER_BUILT_IN,		// �ӽ� ( ������ ����� ���� ��ư )
	DST_HOIPOIMIX_RECIPE_FILTER_NORMAL,			// �Ϲ� ( ������ ����� ���� ��ư )
	DST_HOIPOIMIX_RECIPE_FILTER_SPECIAL,		// Ư�� ( ������ ����� ���� ��ư )

	DST_HOIPOIMIX_CREATE_TAB,					// ����

	DST_HOIPOIMIX_REQUIRED_LEVEL,				// �ʿ� ���� ���� : %d
	DST_HOIPOIMIX_REQUIRED_ZENNY,				// ���� ��� : %d
	DST_HOIPOIMIX_UNSET_FARERATE,				// ȣ������ �ͽ� �ӽ� ������ �����Ǿ� ���� �ʽ��ϴ�.

	DST_HOIPOIMIX_MATERIAL_CATEGORY,			// ��� �� ���� ����
	DST_HOIPOIMIX_PREVIEW_CATEGORY,				// �̸�����
	DST_HOIPOIMIX_CONCENT_CATEGORY,				// ���߷� ��Ʈ��

	DST_HOIPOIMIX_CONCENT_RATE_PERFECT,			// �Ϻ���!
	DST_HOIPOIMIX_CONCENT_RATE_GOOD,			// ��ġ��!
	DST_HOIPOIMIX_CONCENT_RATE_BAD,				// ��ġ���� ����!

	DST_HOIPOIMIX_BUTTON_CREATE,				// �����
	DST_HOIPOIMIX_BUTTON_STOP,					// �����ϱ�

	DST_HOIPOIMIX_CREATE_SUCCESS_NORMAL,		// (����â) %s ������ �����߽��ϴ�. (�Ϲ�)
	DST_HOIPOIMIX_CREATE_SUCCESS_GREAT,		// (����â) %s ������ �����߽��ϴ�. (�뼺��)
	DST_HOIPOIMIX_CREATE_FAILED,				// (����â) ������ �����Ͽ� %s �� ��������ϴ�.

	DST_HOIPOIMIX_CREATE_SUCCESS_NORMAL_NOTIFY,	// (�˸�) ȣ������ �ͽ� ����! %s �� �����Ͽ����ϴ�. (�Ϲ�)
	DST_HOIPOIMIX_CREATE_SUCCESS_GREAT_NOTIFY,	// (�˸�) ȣ������ �ͽ� �뼺��! %s �� �����Ͽ����ϴ�. (�뼺��)
	DST_HOIPOIMIX_CREATE_FAILED_NOTIFY,			// (�˸�) ȣ������ �ͽ� ����! %s �� �����Ͽ����ϴ�. (����)

	DST_HOIPOIMIX_CREATE_FIRST_GUIDE,			// (ȣ�����̹ͽ� ����â �ϴܿ� ó������ �ߴ� ���̵� �޽���) �����̽��ٸ� Ÿ�ֿ̹� ���� ���� ��¼�� ��¼��..
	DST_HOIPOIMIX_CREATE_NEED_MATERIAL,			// ��ᰡ ���ڶ� ������ ������ �� �����ϴ�.
	DST_HOIPOIMIX_CREATE_NEED_SET_NUMBER,		// ���� ������ �����ؾ� ������ ���� �� �� �ֽ��ϴ�.

	DST_HOIPOIMIX_REGISTER_RECIPE,				// %s �����Ǹ� ��ī���Ϳ� ����߽��ϴ�.
	DST_HOIPOIMIX_REGISTER_SKILL,				// �����մϴ�. %s ���� ����� ������ϴ�.
	DST_HOIPOIMIX_SKILL_SET_MSGBOX,				// [MSGBOX]�� ���� ����� ���ðڽ��ϰ�?[br]%s �������[br]�������� : %d[br]�Һ����� : %d
	DST_HOIPOIMIX_SKILL_RESET_MSGBOX,			// [MSGBOX]�� ���� ����� �����Ͻðڽ��ϱ�?[br]%s �������[br]���� ����ġ�� ����������...
	DST_HOIPOIMIX_SKILL_RESET_RESULT,			// %s ��������� �����߽��ϴ�.

	DST_HOIPOIMIX_TOOLTIP_MAX,					// ���� ���� �������� �ڵ����� �˻��ؼ� ���� �� �ִ� �ִ� ������ �����մϴ�.
	DST_HOIPOIMIX_TOOLTIP_CALC,					// ȣ������ �ͽ� ĸ�� �������� ��� ������ ������ ���մϴ�.
	DST_HOIPOIMIX_TOOLTIP_CREATE,				// ���߷� ��Ʈ�� ������ ���콺 Ŭ���� �ؼ� ������ �� EP�� ������ �� �ֽ��ϴ�. ��� �� �����ϸ� �뼺�� Ȯ���� �ö󰩴ϴ�.
	DST_HOIPOIMIX_TOOLTIP_STOP,					// �����ϴ� ���� �ߴ� �� �� �ֽ��ϴ�.

	// Item
	DST_ITEM_RECIPE_TYPE_FOOD_DRINK,			// FOOD DRINK
	DST_ITEM_RECIPE_TYPE_MAIN_WEAPON,			// MAIN WEAPON
	DST_ITEM_RECIPE_TYPE_ARMOR,					// ARMOR
	DST_ITEM_RECIPE_TYPE_ACCESSORY,				// ACCESSORY
	DST_ITEM_RECIPE_TYPE_SCOUTER,				// SCOUTER
	DST_ITEM_RECIPE_TYPE_SUB_WEAPON,			// SUB WEAPON

	// ETC
	DST_ETC_PERSONS,							// ��
	DST_FINISHED_MONSTER,						// %s ��⿡ �����Ͽ����ϴ�(���� ��� ������ ����� �� ȭ�� �߾ӿ� �Ѹ��� �޼���)
	DST_ZENNY,									// ����

	// SYSTEM EFFECT ��ȯ��
	DST_SYSTEMEFFECT_PHYSICAL,					// ����
	DST_SYSTEMEFFECT_ENERGY,					// ���
	DST_SYSTEMEFFECT_STATE,						// �����̻�

	DST_SYSTEMEFFECT_METER,						// ����

	// ���
	DST_CONTRACT_PLEASE_READ,					// ��� ������ ������ ������ ""����"" ��ư�� Ȱ��ȭ �˴ϴ�
	DST_CONTRACT_ACCEPT,						// �� ��
	DST_CONTRACT_NOT_ACCEPT,					// ���� ����

	// ��Ȱ �޽��� �ڽ� Ŀ���� ��ư
	DST_REGEN_MB_MAINWORLD_MOVE_TO_POPOSTONE_BTN,	//"�̵��ϱ�"
	DST_REGEN_MB_TLQ_MOVE_TO_MAINWORLD_BTN,		//"���ư���"
	DST_REGEN_MB_TLQ_RETRY_BTN,					//"�絵��"
	DST_REGEN_MB_TMQ_MOVE_TO_MAINWORLD_BTN,		//"���ư���"
	DST_REGEN_MB_PARTYDUNGEON_RETRY_BTN,			//"�絵��"
	DST_REGEN_MB_DOJO_RETRY_BTN,					//"�絵��"

	// ����
	DST_DOJO,									// ����
	DST_DOJO_UPGRADE,							// ���� �����ϱ�
	DST_DOJO_NAME,								// ���� �̸�
	DST_DOJO_NEED_GUILD_POINT,					// �ʿ��� ���� ����Ʈ
	DST_DOJO_NEED_ZENNY,						// �ʿ��� ����
	DST_DOJO_NEED_ITEM,							// �ʿ��� ������
	DST_DOJO_RUN_UPGRADE,						// �����ϱ�

	DST_DOJO_ACCOUNT_WAREHOUSE,					// ���� â�� ��볻��
	DST_DOJO_ACCOUNT_EXPENDITURE,				// ��볻��
	DST_DOJO_ACCOUNT_ITEM,						// ����
	DST_DOJO_ACCOUNT_AMOUNT,					// �ݾ�
	DST_DOJO_ACCOUNT_BALANCE,					// �ܾ�
	DST_DOJO_ACCOUNT_TYPE_LEADER_INCOME,		// ��� �Ա�
	DST_DOJO_ACCOUNT_TYPE_LEADER_OUTCOME,		// ��� ���
	DST_DOJO_ACCOUNT_TYPE_VILLAGE_INCOME,		// ��� ���
	DST_DOJO_ACCOUNT_TYPE_BATTLE_OUTCOME,		// ��� ���
	DST_DOJO_ACCOUNT_TYPE_BATTLE_INCOME,		// ��û ȯ�ޱ�

	DST_DOGI_SETUP,								// ���� ����
	DST_DOGI_PREVIEW,							// ���� �̸�����
	DST_DOGI_COLOR,								// ���� ����

	DST_DOJO_PEACE_STATE_PANIC,					// ��Ȳ
	DST_DOJO_PEACE_STATE_FEAR,					// �Ҿ�
	DST_DOJO_PEACE_STATE_COMMON,				// ����
	DST_DOJO_PEACE_STATE_QUIET,					// ���
	DST_DOJO_PEACE_STATE_FESTIVAL,				// ����

	DST_DOJO_INFO,								// ���� ����
	DST_DOJO_INFO_INFO,							// ����
	DST_DOJO_INFO_BATTLE,						// ����

	DST_DOJO_INFO_SET_TENKAI_SEED_PLAYER,		// õ������ ����ȸ �õ� ������ ����
	DST_DOJO_INFO_GUILD_NOTICE,					// ��� ����
	DST_DOJO_INFO_DOJO_INFO,					// ���� ����
	DST_DOJO_INFO_DOJO_NAME,					// ���� �̸�
	DST_DOJO_INFO_DOJO_LEVEL,					// ���� ����
	DST_DOJO_INFO_CITY_NAME,					// ���� �̸�
	DST_DOJO_INFO_GUILD_NAME,					// ���� �̸�
	DST_DOJO_INFO_GUILD_POINT,					// ���� ����Ʈ
	DST_DOJO_INFO_PUBLIC_SECURITY,				// ���� ġ��
	DST_DOJO_INFO_TENKAI_SEED_PLAYER,			// ����ȸ ������
	DST_DOJO_INFO_NOTICE_INPUT,					// ���� ���� �Է�

	DST_DOJO_BATTLE_APPLICATION_FOR_BATTLE,		// ��û�ϱ�
	DST_DOJO_BATTLE_DUEL_DEFFENCE_PLAYER,		// �� ������ - �����
	DST_DOJO_BATTLE_DULE_OFFENCE_PLAYER,		// ���� ���� ����
	DST_DOJO_BATTLE_SCRAMBLE_OFFENCE_PLAYER,	// ��Ż�� ���� ����

	DST_DOJO_SCRAMBLE_ACCEPT_CHALLENGE_OK_BTN,		// ����
	DST_DOJO_SCRAMBLE_ACCEPT_CHALLENGE_CANCEL_BTN,	// �ź�
	DST_DOJO_SCRAMBLE_ASK_CHALLENGE_OK_BTN,			// ��û
	DST_DOJO_SCRAMBLE_ASK_TELEPORT_OK_BTN,			// �̵�

	DST_DOJO_SCRAMBLE_RULE_TITLE,					// ��Ż���� �¸��ϱ� ���� �� ���� ���
	DST_DOJO_SCRAMBLE_RULE,							// 1. �����, ������, ���޽�, ���߽�, �񹫴뿡 �ִ� �� 5���� ������ �����Ͽ� ��Ż������ 100�� ȹ���϶�") 2.�� �ð��� ��Ż�� ���� ������ĺ��� ���� ��Ż������ ȹ���϶�
	
	DST_DOJO_SCRAMBLE_REWARD_REPUTATION,			// ȹ�� ���� ����Ʈ
	DST_DOJO_SCRAMBLE_REWARD_ITEM,					// ȹ�� ������

	DST_DOJO_SCRAMBLE_TITLE,						// ���� ��Ż��
	DST_DOJO_SCRAMBLE_GUILD_MEMBER_COUNT,			// ���� �ο�
	DST_DOJO_SCRAMBLE_OWNER_SEAL_COUNT,				// ȹ�� ���� ����
	DST_DOJO_SCRAMBLE_ENTER,						// �����ϱ�

	DST_DOJO_SCRAMBLE_OUR_GUILD_SEAL,				// �츮 ���� ����
	DST_DOJO_SCRAMBLE_OTHER_GUILD_SEAL,				// ��� ���� ����
	DST_DOJO_SCRAMBLE_NO_OWNER_SEAL,				// ���� ���� ����

	DST_DOJO_UPGRADE_CONSUMPTION_GUILD_POINT,		// �Ҹ� ���� ����Ʈ
	DST_DOJO_UPGRADE_CONSUMPTION_ZENNY,				// �Ҹ� ����
	DST_DOJO_UPGRADE_NEED_ITEM,						// ȣ�����̶�

	// ���� ���� ������ Ư¡�� ���� ������ Ư¡�� ����
	DST_DOJO_UPGRADE_CURENT_LEVEL_1,				// ���� ���� 1
	DST_DOJO_UPGRADE_CURENT_LEVEL_2,				// ���� ���� 2
	DST_DOJO_UPGRADE_CURENT_LEVEL_3,				// ���� ���� 3
	DST_DOJO_UPGRADE_CURENT_LEVEL_4,				// ���� ���� 4
	DST_DOJO_UPGRADE_CURENT_LEVEL_5,				// ���� ���� 5
	DST_DOJO_UPGRADE_CURENT_LEVEL_6,				// ���� ���� 6
	DST_DOJO_UPGRADE_CURENT_LEVEL_7,				// ���� ���� 7

	DST_DOJO_UPGRADE_NEXT_LEVEL_2,					// ���� ���� 2
	DST_DOJO_UPGRADE_NEXT_LEVEL_3,					// ���� ���� 3
	DST_DOJO_UPGRADE_NEXT_LEVEL_4,					// ���� ���� 4
	DST_DOJO_UPGRADE_NEXT_LEVEL_5,					// ���� ���� 5
	DST_DOJO_UPGRADE_NEXT_LEVEL_6,					// ���� ���� 6
	DST_DOJO_UPGRADE_NEXT_LEVEL_7,					// ���� ���� 7

	//
	DST_RPBALL_TOOLTIP,							// RPBall ����

	// ���Ⱓ ���� ����
	DST_COMMERCIAL_MB_UPDATE_TERM_LIMETED_ITEM_BTN,	// �Ⱓ ����
	DST_COMMERCIAL_MB_DELETE_TERM_LIMETED_ITEM_BTN,	// ������
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_INFO,		// ���� ���Ⱓ\n%s
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_INFO_BELOW_HOUR,	// 1�ð� ����
	DST_COMMERCIAL_USE_TERM_LIMITED_ITEM_EXPIRED_INFO,	// ���Ⱓ ����
	DST_COMMERCIAL_USE_TERM_LIMITED_ITEM_TITLE,		// ���Ⱓ ����
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_REMIAN_TIME,	// ���� ���Ⱓ
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_ADD_TIME,		// �߰� ���Ⱓ
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CONSUME_JENNY,	// �Ҹ� ����
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_OWNED_JENNY,	// ���� ����
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CONSUME_NETPHY,	// �Ҹ� ����
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_OWNED_NETPHY,	// ���� ����
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CONSUME_CASH,	// ���� CC Cash
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_OWNED_CASH,	// ���� CC Cash
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_EXTEND_Q,		// �������� ���ð��� �����Ͻðڽ��ϱ�?
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CASH_EXTEND_Q,	// �������� ���ð��� �����Ͽ� �����Ͻðڽ��ϱ�?
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CASH_BUY_WARN_DESC1, // ��ǰ���Ž� ���ȱ�, ��ȯ, ȯ���� �Ұ����մϴ�.
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CASH_BUY_WARN_DESC2, // û�� öȸ(�������, ȯ��)�� �Ұ����մϴ�.
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_CASH_BUY_WARN_DESC3, // ���� ������ ListȮ�� Page ����
	DST_COMMERCIAL_USE_TERM_BUY_DURATION,			// �Ⱓ ����
	DST_COMMERCIAL_REFILL_CASH,						// ĳ�� ����
	DST_COMMERCIAL_USE_TERM_LIMITED_ITEM_BUY_TITLE,		// ���� Ȯ��
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_BUY_Q1,		// ��û�Ͻ� ���ų����� ���� �����ϴ�.
	DST_COMMERCIAL_USE_TERM_LIMETED_ITEM_BUY_Q2,		// Ȯ���� �����ø� ���Ű� �Ϸ�˴ϴ�.

	DST_COMMERCIAL_MB_DIRECT_BUY_MSG,					// �ȳ� �޽���, ������ �̸� %S, �Ҹ����� : %d
	DST_COMMERCIAL_MB_DIRECT_BUY_NETPY_MSG ,			// �ȳ� �޽���, ������ �̸� %S, �Ҹ���� : %d
	DST_COMMERCIAL_MB_ITEM_BUY_MSG,						// �Ⱓ����
	DST_COMMERCIAL_MB_ITEM_TERM_EXTENTION_BTN,			// �Ⱓ����
	DST_COMMERCIAL_MB_CAPSULEKIT_ITEM_TERM_EXTENTION,	// ĳ��ŰƮ�Ⱓ����
	DST_COMMERCIAL_MB_CAPSULEKIT_TERM_EXTENTION_BTN,	//�Ⱓ����
	DST_COMMERCIAL_MB_CAPSULEKIT_BUY_BTN,				//������ ����
	DST_COMMERCIAL_MB_ITEM_BUY_CONFIRM_MSG,				//"�ȳ� �޽���"
	DST_COMMERCIAL_MB_ITEM_TAKE_CONFIRM_MSG,			// "�ȳ� �޽���"
	DST_COMMERCIAL_MB_TERM_OR_BUY_SELECT_CONFIRM_MSG,	// "�ȳ� �޽���"
	DST_COMMERCIAL_MB_TERM_OR_BUY_SELECT_CONFIRM_BTN,	////////// �߰�
	DST_COMMERCIAL_MB_CAPSULEKIT_ITEM_SELECT,			// "�ȳ� �޽���"
	DST_COMMERCIAL_MB_CAPSULEKIT_ITEM_TERM_EXTENTION_BTN,// �Ⱓ����
	DST_COMMERCIAL_MB_CAPSULEKIT_MOVE_BTN,				// ������ ����
	DST_COMMERCIAL_MB_ITEM_MOVE_CONFIRM_MSG,			// "�ȳ� �޽���"
	// DST_COMMERCIAL_MB_ITEM_MOVE_CONFIRM_MSG��
	DST_COMMERCIAL_MB_TERM_EXTENTION,					////////// �߰�
	DST_COMMERCIAL_MB_TERM_EXTENTION_BTN,				// "�Ⱓ����" 

	DST_LACK_OF_ZENNY,									// ������ ���ϰ� �����մϴ�.
	DST_LACK_OF_NETPY,									// ������ ���ǰ� �����մϴ�.
	DST_LACK_OF_CASH,									// ������ ĳ���� �����մϴ�.

	DST_CASH,						// ĳ��
	DST_DAY,						// ��
	DST_TIME,						// �ð�
	DST_MINUTE,						// ��

	// N-Protect
	DST_NPGAMEMON_COMM_ERROR,							// ���Ӱ������ ����� ���������ϴ�.
	DST_NPGAMEMON_COMM_CLOSE,							// ���Ӱ��尡 ����Ǿ����ϴ�.
	DST_NPGAMEMON_INIT_ERROR,							// ���Ӱ��� ���� ���� : %lu
	DST_NPGAMEMON_SPEEDHACK,							// ���ǵ����� �����Ǿ����ϴ�.
	DST_NPGAMEMON_GAMEHACK_KILLED,						// �������� �߰ߵǾ����ϴ�.
	DST_NPGAMEMON_GAMEHACK_DETECT,						// �������� �߰ߵǾ����ϴ�.
	DST_NPGAMEMON_GAMEHACK_DOUBT,						// �����̳� ���Ӱ��尡 �����Ǿ����ϴ�.
	DST_NPGAMEMON_ERROR_EXIST,							// ���Ӱ��尡 ���� �� �Դϴ�. ��� �ĳ� ����� �Ŀ� �ٽ� �����غ��ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_GAME_EXIST,						// ������ �ߺ� ����Ǿ��ų� ���Ӱ��尡 �̹� ���� �� �Դϴ�. ���� ���� �� �ٽ� �����غ��ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_INIT,							// ���Ӱ��� �ʱ�ȭ �����Դϴ�. ����� �� �ٽ� �����غ��ų� �浹�� �� �ִ� �ٸ� ���α׷����� ������ �� ������ ���ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_NO_CONFIG_FILE,					// ���Ӱ��� ���� ������ ���ų� �����Ǿ����ϴ�.
	DST_NPGAMEMON_ERROR_CRYPTOAPI,						// �������� �Ϻ� �ý��� ������ �ջ�Ǿ����ϴ�. ���ͳ� �ͽ��÷η�(IE)�� �ٽ� ��ġ�غ��ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_EXECUTE,						// ���Ӱ��� ���࿡ �����߽��ϴ�. ���Ӱ��� �¾� ������ �ٽ� ��ġ�غ��ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_ILLEGAL_PRG,					// �ҹ� ���α׷��� �߰ߵǾ����ϴ�. ���ʿ��� ���α׷��� ������ �Ŀ� ������ �ٽ� �����غ��ñ� �ٶ��ϴ�.
	DST_NPGMUP_ERROR_ABORT,								// ���Ӱ��� ������Ʈ�� ����ϼ̽��ϴ�. ������ ��� ���� ���� ��� ���ͳ� �� ���� ��ȭ�� ������ ������ ���ñ� �ٶ��ϴ�.
	DST_NPGMUP_ERROR_CONNECT,							// ���Ӱ��� ������Ʈ ���� ���ӿ� �����ϼ̽��ϴ�. ��� �� �ٽ� �����ϰų� ��Ʈ�� ���¸� ������ ���ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_GAMEGUARD,						// ���Ӱ��� �ʱ�ȭ ���� �Ǵ� �������� ���Ӱ��� �����Դϴ�. ���Ӱ��� �¾� ������ �ٽ� ��ġ�ϰ� ������ ������ ���ñ� �ٶ��ϴ�.
	DST_NPGMUP_ERROR_PARAM,								// ini ������ ���ų� �����Ǿ����ϴ�. ���Ӱ��� �¾� ������ ��ġ�Ͻø� �ذ��� �� �ֽ��ϴ�.
	DST_NPGMUP_ERROR_INIT,								// npgmup.des �ʱ�ȭ �����Դϴ�. ���Ӱ��� ������ ������ �ٽ� ���ӽ����� �غ��ñ� �ٶ��ϴ�.
	DST_NPGMUP_ERROR_DOWNCFG,							// ���Ӱ��� ������Ʈ ���� ���ӿ� �����Ͽ����ϴ�. ��� �� �ٽ� �õ��� ���ų� ���� ��ȭ���� �ִٸ� ������ ������ ���ñ� �ٶ��ϴ�.
	DST_NPGMUP_ERROR_AUTH,								// ���Ӱ��� ������Ʈ�� �Ϸ����� �� �߽��ϴ�. ���̷��� ����� �Ͻ� ������Ų �� ��õ� �غ��ðų�, pc ���� ���α׷��� ����ϽŴٸ� ������ ������ ���ñ� �ٶ��ϴ�.
	DST_NPGAMEMON_ERROR_NPSCAN,							// ���̷��� �� ��ŷ�� �˻� ��� �ε��� ���� �߽��ϴ�. �޸� �����̰ų� ���̷����� ���� ������ �� �ֽ��ϴ�.
	DST_NPGAMEGUARD_ERROR_ETC,							// ���Ӱ��� ���� �� ������ �߻��Ͽ����ϴ�. ���� ���� ���� GameGuard ������ �ִ� *.erl ���ϵ��� Game1@inca.co.kr �� ÷���Ͽ� ���� �����ֽñ� �ٶ��ϴ�.

	// PC�� ����
	DST_NETPY_REMAIN_TIME,                              // ���� ���� ȹ����� ���� �ð�
	DST_NETPY_GET_NETPY,                                // ���� �� ȹ���� ����
	DST_NETPY_CURRENT_NETPY,                            // ���� ���� ����
	DST_NETPY_GET_NOTIFY,                               // ���� %d ����Ʈ�� ȹ���߽��ϴ�.
	DST_NETPY_POINT,                                    // ����Ʈ

	DST_NETPY,											// ����
	DST_NETPYSHOP,										// ���ǘ�
	DST_NETSTORE,										// �ݽ����

	DST_INFOWINDOW_USE_STATE,							// ��� ����
	DST_INFOWINDOW_ZENNY,								// %d Zenny 
	DST_INFOWINDOW_RECIPE_MAT,							// ������ ���
	DST_INFOWINDOW_CREATE_ITEM,							// �ͽ� ������(������� ������)
	DST_INFOWINDOW_MAKE_ZENNY,							// ���� ���
	DST_INFOWINDOW_SELL_PRICE,							// �Ǹ� ����
	DST_INFOWINDOW_MAKE_LEVEL,							// ���� ���� : %d ����

	// Teleport Type
	DST_TELEPORT_TYPE_GAME_IN,							// ���ӿ� ó�� �������� ���� �ڷ���Ʈ	
	DST_TELEPORT_TYPE_GAME_OUT,							// ���ӿ� ���� ���� �ڷ���Ʈ
	DST_TELEPORT_TYPE_SKILL,							// ��ų
	DST_TELEPORT_TYPE_NPC_PORTAL,						// NPC Portal
	DST_TELEPORT_TYPE_POPOSTONE,						// ��������
	DST_TELEPORT_TYPE_WORLD_MOVE,						// ���� �̵�
	DST_TELEPORT_TYPE_TMQ_WORLD_MOVE,					// TMQ
	DST_TELEPORT_TYPE_TMQ_PORTAL,						// TMQ
	DST_TELEPORT_TYPE_RANKBATTLE,						// ��ũ��Ʋ
	DST_TELEPORT_TYPE_TIMEQUEST,						// TIME QUEST
	DST_TELEPORT_TYPE_TUTORIAL,							// Ʃ�丮��
	DST_TELEPORT_TYPE_BUDOKAI,							// õ�����Ϲ���ȸ ����
	DST_TELEPORT_TYPE_MATCH,							// õ�����Ϲ���ȸ ���
	DST_TELEPORT_TYPE_MINORMATCH,						// õ�����Ϲ���ȸ ����
	DST_TELEPORT_TYPE_MAJORMATCH,						// õ�����Ϲ���ȸ ����
	DST_TELEPORT_TYPE_FINALMATCH,						// õ�����Ϲ���ȸ �ἱ
	DST_TELEPORT_TYPE_COMMAND,							// COMMAND
	DST_TELEPORT_TYPE_GM,								// GM
	DST_TELEPORT_TYPE_DUNGEON,							// DUNGEON
	DST_TELEPORT_TYPE_DOJO,								// ����

	// GMT
	DST_OPTION_GMT_TAB,									// �ŴϾ� Ÿ�� ( �ǿ� ���� �ؽ�Ʈ )
	DST_GMT_TITLE,										// ���� �ŴϾ� Ÿ��
	DST_GMT_PROFILE,									// ���� �÷��̿� ������ �Ǵ� �߰� ȹ�� �ð��븦���մϴ�. �缳�� Ƚ����...
	DST_GMT_EXT_GET,									// �߰� ȹ��
	DST_GMT_RESET,										// �缳��
	DST_GMT_APPLY_TIME,									// ���� �ð�
	DST_GMT_CHANGE_TIME,								// ����� �ð�

	DST_GMT_LIST_EXP,									// ����ġ �߰� ȹ�� %u%%
	DST_GMT_LIST_ZENNY,									// ���� �߰� ȹ�� %u%%

	DST_GMT_REMAIN_COUNT,								// ���� �缳�� Ƚ�� : %d
	DST_GMT_TIME_INFO,									// %2d:00
	DST_GMT_NO_TIME,									// ����
	
	DST_GMT_RESET_TITLE,								// �ŴϾ� Ÿ�� ����

	DST_GMT_RESET_ALREADY_OPEN,							// GMT ���� â�� �̹� ���� �ֽ��ϴ�. ( �޽����ڽ� )
	DST_GMT_RESET_COUNT_OVER,							// ���� �� �ִ� �ð� ������ �ʰ��Ͽ����ϴ�.
	
	DST_GMT_ENABLE_CHECK_COUNT,							// ���� ������ �ð��� ���� : %d
	
	DST_GMT_DONOT_CHECK_ALL,							// GMT�� �缳�� �ϱ� ���ؼ��� ��� GMT �׸��� �ð��븦 �� üũ�Ͽ��� �մϴ�.

};

#endif