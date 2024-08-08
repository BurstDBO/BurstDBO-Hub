/******************************************************************************
* File			: ScouterGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 9. 13
* Last Update	: 2007. 8. 28
* Abstract		: 
*****************************************************************************
* Desc			: 
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

#include "NtlSLDef.h"
#include "NtlSob.h"

// dbo
#include "SurfaceGui.h"
#include "NumberGui.h"

class CNtlSobItem;
class CNtlSobActor;

class CScouterMeasureGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	enum eMeasureType
	{
		MEASURE_POWER,								///< ������ ���� ���
		MEASURE_FIND_HIDDEN_OBEJCT,					///< ������ ������Ʈ ã�� ���

		NUM_MEASURE
	};

	enum eNumberColor
	{
		NUMBERCOLOR_RED,
		NUMBERCOLOR_YELLOW,
		NUMBERCOLOR_WHITE,

		NUM_COLOR
	};

	struct sAvatarPower
	{
		RwBool				bShow;
		RwUInt32			uiPower;
		RwInt32				iMeasurePowerCount;

		gui::CSlot			slotOnMoiveEnd;

		gui::CFlash*		pflaAvatarDirect;			///< HP ���̾�α׸� ����Ű�� �÷���
		CNumberGui			NumberAvatarPower;			///< ������ ������ �ƹ�Ÿ�� ������ ǥ��		
	};

	struct sTarget;

	typedef VOID	(CScouterMeasureGui::*callback_Update)(RwReal, sTarget*);
	typedef VOID	(CScouterMeasureGui::*callback_Destroy)(sTarget*);
	typedef VOID	(CScouterMeasureGui::*callback_Paint)(sTarget*);


	struct sTarget
	{
		eMeasureType		eType;
		SERIAL_HANDLE		hTarget;			///< ������ Ÿ���� �ڵ�
		CNtlSob*			pSobTarget;			///< ������ ������ �ϰ� �ִ� Ÿ���� Sob ������
		DWORD				dwDisplayFlag;		///< ȭ�鿡 ǥ�õǴ� GUI �÷���
		RwReal				fTimer;		

		callback_Update		pCallback_Update;
		callback_Destroy	pCallback_Destory;
		callback_Paint		pCallback_Paint;

		sTarget()
		:hTarget(INVALID_SERIAL_ID)		
		,pSobTarget(NULL)
		,dwDisplayFlag(0)
		,fTimer(0.f)		
		,pCallback_Update(NULL)
		,pCallback_Destory(NULL)
		,pCallback_Paint(NULL)
		{}
	};

	struct sPowerData : public sTarget
	{		
		RwBool				bShowScouterBack;
		gui::CFlash*		pFlashCircle;
		gui::CFlash*		pFlashArrow;
		gui::CFlash*		pFlashDirect;

		RwUInt32			uiOffencePower;		///< ��ǥ ������
		RwUInt32			uiPostPower;		///< ���� ������
		RwUInt32			uiAdjustPower;		///< ������ ������
		RwUInt32			uiDisplayPower;		///< ���� ȭ�鿡 ǥ���� ������

		RwUInt32			uiMoreMeasureCount;	///< �������� ������ Ƚ��
		
		RwReal				fTimeRecievePower;	///< �������� �����κ��� ���� �ð�
		RwReal				fTimeAdjustPower;	///< ������ ���� �ð�
		RwReal				fTimeDisplayPower;	///< ������ ��ġ�� �����ִ� �ð�

		RwInt32				iAdjustCount;		///< ������ ���� Ƚ��

		RwBool				bAskPower;			///< ������ ��ġ�� ��û�ߴ�		

		sPowerData()
		:bShowScouterBack(true)		
		,pFlashCircle(NULL)
		,pFlashArrow(NULL)
		,pFlashDirect(NULL)
		,uiOffencePower(0)
		,uiPostPower(0)
		,uiAdjustPower(0)
		,uiDisplayPower(0)
		,uiMoreMeasureCount(0)
		,fTimeRecievePower(0.f)
		,fTimeAdjustPower(0.f)
		,fTimeDisplayPower(0.f)
		,bAskPower(false)
		,iAdjustCount(0)		
		{}
	};

	struct sHiddenObjectData : public sTarget
	{
		RwBool				bShowScouterBack;	

		gui::CFlash*		pFlashCircle;
		gui::CFlash*		pFlashArrow;

		sHiddenObjectData()
		:bShowScouterBack(true)
		,pFlashCircle(NULL)
		,pFlashArrow(NULL)
		{}
	};

	typedef std::map<SERIAL_HANDLE, sTarget*>						MEASURE_MAP;
	typedef std::map<SERIAL_HANDLE, sTarget*>::iterator				MEASURE_ITER;

	typedef std::map<SERIAL_HANDLE, RwV3d>							MAP_OBJECTPOS;
	typedef std::map<SERIAL_HANDLE, RwV3d>::iterator				MAP_OBJECTPOS_ITER;

	struct sHiddenObjectVisiable
	{
		// ts���� �Ѱ��ִ� ���� ������Ʈ �����͸� �����ϰ� �ִ´�.
		MAP_OBJECTPOS		mapObjectPos;
		RwBool				bRemainVisible;		///< ��ī���Ͱ� ������ �����ð� �ڿ� ������Ʈ�� �������
		RwReal				fElapsed;
	};
	

	CScouterMeasureGui(const RwChar* pName);
	virtual ~CScouterMeasureGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();
	VOID		Clear();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

protected:
	CScouterMeasureGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

	VOID		StartMeasure(eMeasureType eMode);		///< ��ī���� ������ �����Ѵ�

	// ������ ���� ����
	RwBool		MeasurePower_Init();
	VOID		MeasurePower_Destroy(sTarget* pTarget);
	VOID		MeasurePower_Update(RwReal fElapsed, sTarget* pTarget);
	VOID		MeasurePower_Paint(sTarget* pTarget);
	VOID		MeasurePower_Display(sPowerData* pPowerData, RwUInt32 uiPower);			///< ������ ���� ����Ʈ�� �����ش�.
	VOID		MeasurePower_AskPowertoServer(sPowerData* pPowerData);					///< �������� �����Ѵ�.
	
	// ���� ������Ʈ ã�� ����
	RwBool		MeasureFindObject_Init();
	VOID		MeasureFindObject_Destroy(sTarget* pTarget);
	VOID		MeasureFindObject_Update(RwReal fElapsed, sTarget* pTarget);
	VOID		MeasureFindObject_Paint(sTarget* pTarget);

	VOID		OutOfOrder();							///< ��ī���Ͱ� ���峵��

	VOID		OnMovieEnd_AvatarDirect(gui::CComponent* pComponent);

	VOID		EndDisplayImmediately(SERIAL_HANDLE hHandle);
	VOID		EndDisplay(sTarget* pTarget);

	RwBool		IsWorking(eMeasureType eType);			///< ���� ��尡 �����ϴ��� ����

	VOID		TargetEdgeEffect(RwBool bActive, sTarget* pTarget);

	VOID		OnPaint();

protected:	
	gui::CSlot			m_slotPaint;	

	CNumberGui			m_Number[NUM_COLOR];
	CNumberGui			m_NumberDistance;

	CSurfaceGui			m_srfDistanceMark;
	CSurfaceGui			m_srfDistanceUnit;

	RwBool				m_bOutofOrder;

	sAvatarPower		m_AvatarPower;

	MEASURE_MAP			m_mapMeasure;
	std::list<sTarget*>	m_listRemove;

	sHiddenObjectVisiable	m_HiddenObject;
};