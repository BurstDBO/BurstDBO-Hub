/*****************************************************************************
 *
 * File			: AvatarController.h
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 13	
 * Abstract		: NTl CAvatarController
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_AVATAR_CONTROLLER__
#define __NTL_AVATAR_CONTROLLER__

#include "NtlCamera.h"
#include "NtlGameCamera.h"
#include "InputHandler.h"
#include "ceventhandler.h"

#include "NtlSLEvent.h"
#include "NtlSobActor.h"
#include "NtlSLEventHandler.h"
#include "NtlDebug.h"
#include "NtlDeviceRestoreHandler.h"
#include "NtlPLPicking.h"
#include "DboDef.h"

enum ECameraRotateFlag
{
	CAMERA_ROTATE_FLAG_NONE,	
	CAMERA_ROTATE_FLAG_ADJUST,	
	CAMERA_ROTATE_FLAG_ACCORD,	
};

/**
* \ingroup Client
* Keyboard �� Mouse�� �Է����� Camera�� ���� �ϸ�, Camera�� �̵� �� ȸ����
* �� ���ؼ� Avatar���� Event�� ������ ����� �Ѵ�. �׸��� Keyboard�� Mouse��
* ���ÿ� ������ ���� ó�� ���� �ϸ� ActionMap�� ���� Event�� �̰����� ������
* 
*/
class CAvatarController : public RWS::CEventHandler
{
public:

	CAvatarController();
	~CAvatarController();

	RwBool	Create();
	void	Destroy();

	void Update(RwReal fElapsed);
	void HandleEvents(RWS::CMsg &pMsg);
	
	/**
	* mouse and keyboard hander �Լ�.	
	*/

	int	MouseWheelHandler(unsigned int uiMouseData);
	int	MouseMoveHandler(unsigned int uiMouseData);

	int	MouseDownHandler(unsigned int uiMouseData);
	int	MouseUpHandler(unsigned int uiMouseData);

	int	KeyboardDownHandler(unsigned int uiKeyData);
	int KeyboardUpHandler(unsigned int uiKeyData);
	
	int RestoreHandler(void);		///< Device Restore ó�� �Լ�
		
	/**
	*	input action map ó�� �Լ�.
	*/ 
	int ActionMapKeyboardMove(unsigned int uiMoveFlags);
	int ActionMapKeyboardDashMove(unsigned int uiMoveFlags);
	int ActionAvatarSelect(void);
	int ActionJump(unsigned int uiMoveFlags);
	int ActionCharging(unsigned int uiCharging);
	int	ActionBlocking(unsigned int uiBlocking);
	int ActionSitAndStand(void);
	int ActionLooting(void);
	int ActionAutoTarget(void);
	int ActionAutoAttack(void);
	int ActionAutoFollow(void);
	int ActionPartySelect(unsigned int uiIdx);
    int ActionAutoRun();
    int ActionScouterUse(void);
    int ActionPartyShareTargetMarking(unsigned int uiSlot);
    int ActionPartyShareTargetSelect(unsigned int uiSlot);
    int ActionPartyAutoSelect();

private:

	void TeleportReset(void);

	/**
	* picking pl world entity
	*/
	void PickPLWorld(SWorldPickInfo& sPickInfo);

	/**
	* picking pl character entity
	*/
	void PickPLObject(SWorldPickInfo& sPickInfo, RwBool bAttack, RwUInt32 uiSerialID = INVALID_SERIAL_ID);

	/**
	* avatar�� ī�޶� ������ �����Ͽ� �ٷ� ������ �ٲ� �ʿ䰡 �ִµ�, �⺻ move flag�� �����Ѵ�.
	*/
	RwUInt8 ConvertStraightMoveFlags(RwUInt8 uiMoveFlags);

	/**
	* avatar�� ī�޶� ������ �����Ͽ�(���� move flag�� �����Ͽ�) �ٷ� ȸ���Ѵ�.
	*/
	RwReal CalcAvatarStraightRotate(RwUInt32 uiMoveFlags);

	/**
	* ī�޶� ȸ�� ������ ���Ѵ�.
	*/
	void CalcCameraRotateSensitivity(int iPosX, int iPosY, int iMouseDeltaX, int iMouseDeltaY);

	/**
	* ���콺 ��ư�� �ƹ��͵� ������ �ʰ�,  keyboard�� ĳ���Ͱ� front and back ���� ������ ���
	* ĳ���� �������� ī�޶� ȸ����ų delta angle�� ����Ѵ�.
	*/
	void CalcCameraRotateToCharBack(void);

	/**
	* ���콺 ��ư�� �ƹ��͵� ������ �ʰ�,  keyboard�� ĳ���Ͱ� front and back ���� ������ ���
	* ĳ���� �������� ī�޶� ȸ�������ش�.
	*/
	void UpdateCameraRotateToCharBack(RwReal fElapsed);

	/**
	* auto run�� ���.
	*/
	void UpdateAutoRun(RwReal fElapsed);

	/**
	* move mark effect create �Լ�.
	*/
	void CreateMoveMark(const RwV3d *pPos);

	/**
	* move mark effect delete �Լ�.
	*/
	void DeleteMoveMark(void);

	/**
	* move mark effect update �Լ�.
	*/
	void UpdateMoveMark(RwReal fElapsed);
	
	/**
	* move mark effect update �Լ�.
	*/
	void UpdateChangeHeading(RwReal fElapsed);

	/**
	* picking focus update �Լ�.
	*/
	void UpdatePickFocus(RwReal fElapsed);

	/**
	* mouse left button up �϶� ó�� �Լ�.
	*/
	void MouseUpLBtnHandler(const SMouseData *pData);

	/**
	* mouse right button up �϶� ó�� �Լ�.
	*/
	void MouseUpRBtnHandler(const SMouseData *pData);

	/**
	* mouse move left button down �϶� ó�� �Լ�.
	*/
	void MouseMoveLBtnHandler(const SMouseData *pData);

	/**
	* mouse move right button down �϶� ó�� �Լ�.
	*/
	void MouseMoveRBtnHandler(const SMouseData *pData);

	/**
	* mouse move not button down �϶� ó�� �Լ�.
	*/
	void MouseMoveNotBtnHandler(const SMouseData *pData);

private:

	// picking
	SWorldPickInfo	m_sPickInfo;
	sWorldPickInfo_for_Cursor	m_sPickInfo_for_Cursor;

	RwReal			m_fPickTime;

	// Effect
	RwReal			m_fMoveMarkTime;
	CNtlPLEntity	*m_pMoveMark;
	RwUInt8	    	m_uiCurMoveFlags;	
	RwBool			m_bAutoRun;
	RwBool			m_bHTBRPStock;

	// Looting
	RwReal			m_fKeyLootingTime;

	ECameraRotateFlag m_eRotFlag;

	RwBool			m_bLButtonMoveFlag;
	RwInt32			m_iOldLButtonMouseX;
	RwInt32			m_iOldLButtonMouseY;

	RwInt32			m_iDeltaButtonMouseX;
	RwInt32			m_iDeltaButtonMouseY;

	RwBool			m_bRButtonMoveFlag;
	RwInt32			m_iOldRButtonMouseX;
	RwInt32			m_iOldRButtonMouseY;

	RwBool			m_bChangeHeadingFlag;
	RwBool			m_bAutoRunKeyboardChangeHeading;
	RwBool			m_bSkipMouseWheel;
	RwReal			m_fChangeHeadingUpdateTime;
	RwReal			m_fChangeHeadingDeltaTime;
	RwReal			m_fChangeHeadingDeltaAngle;

	SERIAL_HANDLE   m_hFocusSerialId;

	INPUT_HANDLE	m_handleMouseWheel;
	INPUT_HANDLE	m_handleMouseMove;
	INPUT_HANDLE	m_handleMouseDown;
	INPUT_HANDLE	m_handleMouseUp;
	INPUT_HANDLE	m_handleKeyDown;
	INPUT_HANDLE	m_handleKeyUp;

	// device restore
	DEVICE_RESTORE_HANDLE m_handleRestoreHandler;

private:

	void SetAutoRun(RwBool bAutoRun);
};

#endif
