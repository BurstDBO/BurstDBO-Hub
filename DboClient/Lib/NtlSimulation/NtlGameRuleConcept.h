/*****************************************************************************
*
* File			: NtlGameRuleConcept.h
* Author		: JeongHo, Rho
* Copyright	: (��)NTL
* Date			: 2008. 1. 8	
* Abstract		: Game rule concept
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_GAME_RULE_CONCEPT_H__
#define __NTL_GAME_RULE_CONCEPT_H__


enum eGAME_RULE_TYPE
{
	// Main Layer
	// ( �Ѽ����� Main layer�� �ش��ϴ� ���³����� �ߺ��� �� ���� )
	GAME_RULE_TYPE_MAIN_NORMAL,						// �Ϲ�
	GAME_RULE_TYPE_MAIN_PRIVATESHOP_READY,			// ���� ���� ����
	GAME_RULE_TYPE_MAIN_PRIVATESHOP_RUN,			// ���� ���� �Ǹ�
	GAME_RULE_TYPE_MAIN_TMQ_WAIT_LOTTERY,			// Ÿ�̸ӽ� ��û
	GAME_RULE_TYPE_MAIN_TMQ_READY,					// Ÿ�̸ӽ� ���� ���
	GAME_RULE_TYPE_MAIN_TMQ_RUN,					// Ÿ�̸ӽ� ����Ʈ ����
	GAME_RULE_TYPE_MAIN_RANKBATTLE_READY,			// ��ũ��Ʋ ���� ��û
	GAME_RULE_TYPE_MAIN_RANKBATTLE_RUN,				// ��ũ��Ʋ ����
	GAME_RULE_TYPE_MAIN_TENKAICHIBUDOKAI_READY,		// õ������ ����ȸ ���� ��û
	GAME_RULE_TYPE_MAIN_TENKAICHIBUDOKAI_RUN,		// õ������ ����ȸ ����
	GAME_RULE_TYPE_MAIN_DRAGONBALL,					// �巡�ﺼ ����

	// Sub Layer
	GAME_RULE_TYPE_SUB_FREEPVP,						// ���� PVP ����
	GAME_RULE_TYPE_SUB_PARTY_INVITE,				// ��Ƽ �ʴ�
};


class CNtlGameRuleConcept
{
public:
	typedef std::vector< eGAME_RULE_TYPE > vecdef_RuleList;
	typedef std::map< eGAME_RULE_TYPE, vecdef_RuleList > mapdef_RuleTransTable;

	typedef RwBool (CNtlGameRuleConcept::*QUERY_RULE_TYPE) ( void );
	typedef std::map< eGAME_RULE_TYPE, QUERY_RULE_TYPE > mapdef_RuleQueryTable;


protected:
	mapdef_RuleTransTable m_defRuleTransTable;
	mapdef_RuleQueryTable m_defMainRuleQueryTable;


public:
	static CNtlGameRuleConcept* m_pInstance;
	static CNtlGameRuleConcept* GetInstance(void);


public:
	CNtlGameRuleConcept( void );
	~CNtlGameRuleConcept( void );

	RwBool Create( void );
	void Destroy( void );

	RwBool CanTransition( eGAME_RULE_TYPE eNextRuleType );


protected:
	void MakeRuleTransTable( void );
	void MakeMainRuleQueryTable( void );

	eGAME_RULE_TYPE GetCurRuleType( void );

	RwBool Is_Main_PrivateShopReady( void );
	RwBool Is_Main_PrivateShopRun( void );
	RwBool Is_Main_TMQ_Wait_Lottery( void );
	RwBool Is_Main_TMQReady( void );
	RwBool Is_Main_TMQRun( void );
	RwBool Is_Main_RankBattleReady( void );
	RwBool Is_Main_RankBattleRun( void );
	RwBool Is_Main_TenkaichibudokaiReady( void );
	RwBool Is_Main_TenkaichibudokaiRun( void );
	RwBool Is_Main_DragonBall( void );
	RwBool Is_Sub_FreePvP( void );
	RwBool Is_Sub_PartyInvite( void );

	void OutputMessage( eGAME_RULE_TYPE eCurRuleType, eGAME_RULE_TYPE eNextRuleType );
};


#endif
