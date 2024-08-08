/*****************************************************************************
 *
 * File			: NtlSobAvatarAtt.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 30	
 * Abstract		: Simulation object avatar attribute base class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_SOBAVATAR_ATTR_H__
#define __NTL_SOBAVATAR_ATTR_H__

#include "NtlSobPlayerAttr.h"

class CNtlSobAvatarAttr : public CNtlSobPlayerAttr
{
	DECLEAR_MEMORY_POOL(CNtlSobAvatarAttr, NTL_DEFAULT_MEMORY_POOL)
	
public:

	RwUInt32 m_uiExp;		// ���� level������ current exp	
	RwUInt32 m_uiMaxExp;	// ���� level������ max exp

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

	RwUInt16 m_wLastRpRegen;			// RP ���� �ӵ�.(/second)
	RwUInt16 m_wLastRpDimimutionRate;	// RP ���� �ӵ�.(/second)

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
	
	RwUInt16 m_wBaseCurseSuccessRate;
	RwUInt16 m_wLastCurseSuccessRate;
	RwUInt16 m_wBaseCurseToleranceRate;
	RwUInt16 m_wLastCurseToleranceRate;

	RwUInt16 m_wBasePhysicalCriticalRate;
	RwUInt16 m_wLastPhysicalCriticalRate;
	RwUInt16 m_wBaseEnergyCriticalRate;
	RwUInt16 m_wLastEnergyCriticalRate;

	RwUInt16 m_wBaseAttackSpeedRate;
	RwUInt16 m_wLastAttackSpeedRate;

	RwUInt32 m_uiZenny;	

	RwUInt32 m_uiSp;

	RwUInt32 m_uiHonorPoint;			///< �� ����Ʈ
	RwUInt32 m_uiMudosaPoint;			///< ������ ����Ʈ

	RwBool	 m_bCanChangeClass;			///< ���� ���� ����

    //////////////////////////////////////////////////////////////////////////
    // PC�� ����
    DWORD    m_dwNetPy;                 ///< ���� NetPy

	// Battle Attributes bonus rate
	RwReal m_fHonestOffence;
	RwReal m_fHonestDefence;
	RwReal m_fStrangeOffence;
	RwReal m_fStrangeDefence;
	RwReal m_fWildOffence;
	RwReal m_fWildDefence;
	RwReal m_fEleganceOffence;
	RwReal m_fEleganceDefence;
	RwReal m_fFunnyOffence;
	RwReal m_fFunnyDefence;

public:

	CNtlSobAvatarAttr(); 

	virtual ~CNtlSobAvatarAttr() {}

	virtual RwBool Create(void) { SetClassID(SLCLASS_AVATAR); return TRUE; }

	virtual void Destroy(void) {}

	virtual void HandleEvents(RWS::CMsg &pMsg);

	RwUInt32 GetAP(void);	
};

#endif
