/*****************************************************************************
 *
 * File			: NtlSobPetAtt.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 30	
 * Abstract		: Simulation object player attribute base class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_SOBPET_ATTR_H__
#define __NTL_SOBPET_ATTR_H__

#include "NtlSharedDef.h"
#include "NtlSobAttr.h"


class CNtlSobPetAttr : public CNtlSobBattleAttr
{
	DECLEAR_MEMORY_POOL(CNtlSobPetAttr, NTL_DEFAULT_MEMORY_POOL)
	
public:

	RwUInt8		m_bySummonSourceType;	/** skill or item */	
	RwUInt32	m_uiSourceTblId;		/** skill or item table id */
	sNPC_TBLDAT *m_pNpcTbl;				/** mob table data pointer */

	RwUInt8 m_byBaseStr;		// �ٷ�
	RwUInt8 m_byLastStr;		// �ٷ�
	RwUInt8 m_byBaseCon;		// �ǰ�
	RwUInt8 m_byLastCon;		// �ǰ�
	RwUInt8 m_byBaseFoc;		// ������ Ŭ������ ���� �������� ������ ����
	RwUInt8 m_byLastFoc;		// ������ Ŭ������ ���� �������� ������ ����
	RwUInt8 m_byBaseDex;		// ��ø
	RwUInt8 m_byLastDex;		// ��ø
	RwUInt8 m_byBaseSol;		// ������ Ŭ������ ���� �������� ������ ����
	RwUInt8 m_byLastSol;		// ������ Ŭ������ ���� �������� ������ ����
	RwUInt8 m_byBaseEng;		// ������ Ŭ������ ���� �������� ���⸦ ����
	RwUInt8 m_byLastEng;		// ������ Ŭ������ ���� �������� ���⸦ ����

	RwUInt16 m_wBasePhyshicalOffence;
	RwUInt16 m_wLastPhyshicalOffence;
	RwUInt16 m_wBasePhyshicalDefence;
	RwUInt16 m_wLastPhyshicalDefence;
	
	RwUInt16 m_wBaseEnergyOffence;
	RwUInt16 m_wLastEnergyOffence;
	RwUInt16 m_wBaseEnergyDefence;
	RwUInt16 m_wLastEnergyDefence;
	
	RwUInt16 m_wBaseAttackRate;
	RwUInt16 m_wLastAttackRate;
	RwUInt16 m_wBaseDodgeRate;
	RwUInt16 m_wLastDodgeRate;
	RwUInt16 m_wBaseBlockRate;
	RwUInt16 m_wLastBlockRate;
	RwUInt16 m_wBaseAttackSpeedRate;
	RwUInt16 m_wLastAttackSpeedRate;

	RwUInt16 m_wBaseCurseSuccessRate;
	RwUInt16 m_wLastCurseSuccessRate;
	RwUInt16 m_wBaseCurseToleranceRate;
	RwUInt16 m_wLastCurseToleranceRate;

	RwUInt16 m_wBasePhysicalCriticalRate;
	RwUInt16 m_wLastPhysicalCriticalRate;
	RwUInt16 m_wBaseEnergyCriticalRate;
	RwUInt16 m_wLastEnergyCriticalRate;
	
public:

	CNtlSobPetAttr(); 

	virtual ~CNtlSobPetAttr() {}

	virtual RwBool Create(void) { SetClassID(SLCLASS_PET); return TRUE; }

	virtual void Destroy(void) {}

	virtual void HandleEvents(RWS::CMsg &pMsg);

public:

	sNPC_TBLDAT* GetNpcTbl(void) const;
};

#endif
