/*****************************************************************************
*
* File			: DboLogic.h
* Author		: HyungSuk, Jang
* Copyright	: (��)NTL
* Date			: 2005. 11. 08	
* Abstract		: DBO logic.h
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __DBO_LOGIC_H__
#define __DBO_LOGIC_H__

// shared
#include "NtlItem.h"
#include "NtlClientService.h"

// gui
#include "gui_precomp.h"
#include "gui_surface.h"
#include "gui_texturemanager.h"

// simulation
#include "NtlSobItem.h"
#include "NtlWorldConcept.h"

// dbo
#include "DboDef.h"
#include "DialogDefine.h"

struct sSKILL_TBLDAT;
struct sHTB_SET_TBLDAT;
struct sITEM_TBLDAT;
struct sITEM_OPTION_TBLDAT;
struct sGuildWarehouseSlot;

class CNtlPLGui;


extern RwReal	g_fElapsedWeightValue;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	IconMoveManager ���� procedure ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//RwBool Logic_ItemMoveProc(EDragDropType eSrcType, RwInt32 iSrcSlotIdx, RwUInt32 uiSrcSerialId, 
//						  EDragDropType eDestType, RwInt32 iDestSlotIdx, RwUInt32 uiDestSerialId, RwUInt32 uiDestParentSerialId);

RwBool Logic_ItemMoveProc( SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);

// peessi	: Logic_ItemMoveSubProc Return value ����
// desc		: �����ο� �޽��� ����� �پ�ȭ�� ���� RwBool->RwUInt32(EDispStingType)�� ����. 
//			: ����, ������ �˻� ��ƾ�� �Ͽ�ȭ�� ���� �ߺ��� ��Ҵ� ���� �����ϰ� �̰����� ������.
//			: INVALID_DWORD ( �޽��� ��¾���, �����۵� Ȥ�� PacketLock )
//			: ��ī���� ���� ���� �����Լ����� ����, Equip�� ScouterSlot���� �����Ѵ�.

RwUInt32 Logic_ItemMoveSubProcEquipToEquip( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcEquipToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcEquipToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcEquipToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx );
RwUInt32 Logic_ItemMoveSubProcEquipToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx );
//RwUInt32 Logic_ItemMoveSubProcBagSlotToEquip	( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcBagSlotToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcBagSlotToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcBagSlotToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcBagSlotToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcBagChildToEquip( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcBagChildToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcBagChildToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
//RwUInt32 Logic_ItemMoveSubProcBagChildToScouterSlot(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcBagChildToPartyCharmSlot(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcBagChildToScouter( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcBagChildToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount);
RwUInt32 Logic_ItemMoveSubProcBagChildToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount);
RwUInt32 Logic_ItemMoveSubProcScouterToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcScouterToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcScouterToGuildWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcScouterToScouter( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx);
//RwUInt32 Logic_ItemMoveSubProcScouterSlotToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
//RwUInt32 Logic_ItemMoveSubProcScouterSlotToWarehouse( SERIAL_HANDLE hSrcSerial, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
//RwUInt32 Logic_ItemMoveSubProcScouterSlotToGuildWarehouse( SERIAL_HANDLE hSrcSerial, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcQuestToQuest( RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx );
RwUInt32 Logic_ItemMoveSubProcWarehouseToEquip( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcWarehouseToBagSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount );
RwUInt32 Logic_ItemMoveSubProcWarehouseToBagChild( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount);
RwUInt32 Logic_ItemMoveSubProcWarehouseToScouter( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, RwUInt8 ucDestSlotIdx);
RwUInt32 Logic_ItemMoveSubProcWarehouseToWarehouse( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount);
//RwUInt32 Logic_ItemMoveSubProcWarehouseToScouterSlot( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx);
RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToEquip(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);
RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToBagSlot(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);
RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToBagChild(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);
RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToScouter(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);
//RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToScouterSlot(SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx, EPlace eDestPlace, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);
RwUInt32 Logic_ItemMoveSubProcGuildWarehouseToGuildWarehouse(SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx, SERIAL_HANDLE hDestParentSerial, RwUInt8 ucDestSlotIdx, RwUInt32 uiStackCount = 1);

// ���� ����.
RwUInt32 Logic_ItemMoveSubProcSubBagZennyToPartyCharmZenny(RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcSubBagZennyToWarehouseZenny(SERIAL_HANDLE hDestParentSerial, RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcSubBagZennyToGuildWarehouseZenny(SERIAL_HANDLE hDestParentSerial, RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcSubBagZennyToTradeCartZenny(SERIAL_HANDLE hTargetHandle, RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcSubBagZennyToMailSystemZenny(RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcSubBagZennyPartyInvenZenny(RwUInt8 bySlot, RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcPartyCharmZennyToSubBagZenny(RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcWareHouseZennyToSubBagZenny(RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcGuildWareHouseZennyToSubBagZenny(RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcTradeCartZennyToSubBagZenny(RwUInt32 uiZenny);
RwUInt32 Logic_ItemMoveSubProcMailSystemZennyToSubBagZenny(RwUInt32 uiZenny);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	��Ÿ procedure ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RwBool Logic_ItemRepairProc( RwUInt8 ucPlace, RwUInt8 ucSrcSlotIdx );
RwBool Logic_ItemIdentificationProc( RwUInt8 byBagIndex, RwUInt8 ucSrcSlotIdx );
RwBool Logic_ItemIdentification_in_NPCShop_Proc( RwUInt8 byBagIndex, RwUInt8 ucSrcSlotIdx );

RwBool Logic_ItemDeleteProc( sDboItemDeleteInfo* pInfo, RwBool* pPacketLock );
RwBool Logic_ItemDirectEquipProc( SERIAL_HANDLE hSrcSerial, EPlace eSrcPlace, RwUInt8 ucSrcSlotIdx );
RwBool Logic_UseProc( SERIAL_HANDLE hSrcSerial, RwUInt32 param1 = 0xFF );
RwBool Logic_UseProcRpBonusSkill( SERIAL_HANDLE hSrcSerial );
RwBool Logic_ItemBagClearProc( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx );

VOID   Logic_ItemDropConfirmProc(RwBool bRemoteSell = FALSE);

RwInt32 Logic_ItemGetGUI_EXTEND_MODEByCommonPointType( RwUInt8 byCommonPointType);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Event ���� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �ش� iType�� ������Ʈ�ΰ��� �˻�
// iType : NtlSLEvent.h���Ͼ��� EEventAvatarInfoUpdateType ���� Ÿ��
// pData : CMsg�� pData
RwBool Logic_IsUpdateType(RwInt32 iType, void* pData);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Texture Loading
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum eTEXTURETYPE { TEXTYPE_NONE, TEXTYPE_ICON, TEXTYPE_ILLUST, TEXTYPE_MAP, TEXTYPE_LANDMARK, TEXTTYPE_WARFOG, TEXTTYPE_EMBLEM };

gui::CTexture* Logic_CreateTexture( RwChar* pFilename, eTEXTURETYPE eTexType = TEXTYPE_ICON, RwChar* pcPathName = NULL);
VOID		   Logic_DeleteTexture( gui::CTexture* pTexture );

std::string Logic_GetSmallIconName(const char* pcIconName);

gui::CSurface& Logic_GetPCClassIconSurface(RwUInt8 byClass, RwBool bOutLine = TRUE );
gui::CSurface& Logic_GetNPCClassIconSurface(RwUInt8 byClass, RwBool bOutLine = TRUE );
gui::CSurface& Logic_GetSmallRPTypeMark( RwInt32 eRpType );
gui::CSurface& Logic_GetBattleAttributeIconSurface(RwUInt8 byAttribute, RwBool bOutLine = TRUE );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Passive skill ��� ���� ���� �˻�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RwBool Logic_IsPassiveDashUsePossible(void);

RwBool Logic_IsPassiveChargingUsePossible(void);

RwBool Logic_IsPassiveBlockingUsePossible(void);
RwBool Logic_IsPassiveBlockingUsePossibleCoolTime(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	��Ÿ ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RwInt32				Logic_GetPCClassFlagFromPCClass( RwUInt8 ucClass );					// 1��, 2������ ������ Flag
RwInt32				Logic_GetExplicitPCClassFlagFromPCClass( RwUInt8 ucClass );			// ���� Ŭ�������� ǥ���ϴ� Flag

eCONTAINER_TYPE		Logic_ConvertBagIdxToContainerType	( RwUInt8 ucBagIndex );
RwInt8				Logic_ConvertContainerTypeToBagIdx ( RwUInt8 ucContainerType );
eEQUIP_SLOT_TYPE	Logic_ConvertEquipSlotIdxToType	( RwUInt8 ucEquipSlotIdx );
RwUInt8				Logic_ConvertEquipTypeToSlotIdx	( eEQUIP_SLOT_TYPE eEquipType );
RwBool				Logic_EquipSlotTypeFlagCheck		( RwUInt16 usTypeFlag1, RwUInt16 usTypeFlag2 );
RwInt16				Logic_ConvertEquipSlotIdxToFlag	( RwUInt8 ucEquipSlotIdx );

// ������ Container ��ȣ�� Pos �� ������ HANDLE�� �˾Ƴ��� ����
SERIAL_HANDLE		Logic_GetItemHandleFromContainerPos( RwUInt8 ucContainerType, RwUInt8 byPos );

RwUInt32			Logic_ConvertClassToClassFlag( RwUInt8 ucClass );

eCONTAINER_TYPE		Logic_ConverWarehouseIdxToContainderType(RwUInt8 byWarehouseIndex);
RwUInt8				Logic_ConverContainerTypeToWarehouseIdx	(eCONTAINER_TYPE eContainerType);

eCONTAINER_TYPE		Logic_ConverGuildWarehouseIdxToContainderType(RwUInt8 byGuildwarehouseIndex);
RwUInt8				Logic_ConverContainerTypeToGuildWarehouseIdx(eCONTAINER_TYPE eContainerType);

RwBool Logic_CanAcceptOthersAsk();

RwBool Logic_IsStackMovable( SERIAL_HANDLE hSrcSerial, SERIAL_HANDLE hDestSerial, RwUInt32 nSplitCount );
RwBool Logic_IsStackMovable_to_GuildWarehouse( sGuildWarehouseSlot* pGuildWarehouseItem, SERIAL_HANDLE hSrcSerial, RwUInt32 nSplitCount );
RwBool Logic_IsStackMovable_from_GuildWarehouse( sGuildWarehouseSlot* pGuildWarehouseItem, SERIAL_HANDLE hDestSerial, RwUInt32 nSplitCount );
RwBool Logic_IsStackMovable_from_GuildWarehouse( sGuildWarehouseSlot* pGuildWarehouseSrcItem, sGuildWarehouseSlot* pGuildWarehouseDestItem, RwUInt32 nSplitCount );
RwBool Logic_IsBagClearable( SERIAL_HANDLE hSrcSerial, RwUInt8 ucSrcSlotIdx );
RwBool Logic_IsMovableEquipedScouter();
RwBool Logic_IsMovableEquipedScouterParts();
RwBool Logic_IsUsingScouter(VOID);
RwBool Logic_IsScouterHasParts(VOID);
RwBool Logic_FindEmptyItemSlot( RwInt32* pBagIndex, RwInt32* pSlotIndex );
RwBool Logic_FindEmptyItemSlot();

RwBool Logic_WorldItemLooting( CNtlSob* pWorldItem );

RwInt32 Logic_WhichBagHasItem( SERIAL_HANDLE hItemSerial );	// ������ �ø���� ����鿡 ����ִ��� ����. ���� = -1
CNtlSobItem* Logic_FindInventoryItemByTableId( RwUInt32 tblidx );
RwUInt32	 Logic_FindInventoryItemCountByTableId( RwUInt32 tblidx );
CNtlSobItem* Logic_FindEquipItemByTableId( RwUInt32 tblidx );
CNtlSobItem* Logic_FindInventoryItemMinDurByDurationGroup(RwUInt32 uiDurationGroup);

class CRetCaculDayHourMinSecond
{
public:
	RwUInt32 uiDay;		RwUInt32 uiHour;	RwUInt32 uiMin;		RwUInt32 uiSec;
};
VOID	Logic_CaculDayHourMinSecond( RwUInt32 uiInSecond, CRetCaculDayHourMinSecond* pOut);

VOID	Logic_EnableIcon( RwBool bEnable, RwUInt8 byPlace, RwUInt8 byPos ); // ��Ŷ�ڵ鷯���� �ַ� ����� �����ܶ�.

RwBool IsV2LessLength(const RwV2d* vPos, const RwV2d* vPos2, RwReal fLength);
RwBool IsV2LessorEqualLength(const RwV2d* vPos, const RwV2d* vPos2, RwReal fLength);
RwBool IsV2MoreLength(const RwV2d* vPos, const RwV2d* vPos2, RwReal fLength);
RwBool IsV2MoreorEqualLength(const RwV2d* vPos, const RwV2d* vPos2, RwReal fLength);
RwBool IsV2EqualLength(const RwV2d* vPos, const RwV2d* vPos2, RwReal fLength);

void Logic_NameNotify(const WCHAR* pwcText);

RwBool Logic_CanUseLocalName(const WCHAR* pwcText);

RwBool Logic_IsUsableCharacterName_with_WarningMessage(const WCHAR* pwcText);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	user option load/save
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const WCHAR* Logic_GetActiveServerName(void);

RwBool Logic_MakeLoadGameOptFileName(std::string& strFileName, const WCHAR *pCharName);
RwBool Logic_MakeSaveGameOptFileName(std::string& strFileName, const WCHAR *pCharName);

void Logic_LoadAccountOption(void);
void Logic_SaveAccountOption(void);

void Logic_LoadSystemOption(void);
void Logic_SaveSystemOption(void);

void Logic_LoadGameOption(void);
void Logic_SaveGameOption(void);

void Logic_LoadCharacterOption(void);
void Logic_SaveCharacterOption(void);

void Logic_LoadScouterOption(void);
void Logic_SaveScouterOption(void);

void Logic_LoadQuestOption(void);
void Logic_SaveQuestOption(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	game�� ���� callback �Լ�.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic_CallbackHtmlUserTag(const WCHAR *pTag, RwUInt32 uiId, std::wstring& strOut);
void Logic_CallbackHtmlLinkTag(gui::CComponent* pComponent, RwUInt8 byType, RwUInt32 uiIndex, std::wstring& strFilename);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	��Ʈ�� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const WCHAR* Logic_GetClassName(RwUInt8 byClass);	// Ŭ���� �̸� ��ȯ
const WCHAR* Logic_GetNPCJobName(RwUInt8 byJob);	// NPC ���� �̸� ��ȯ
const WCHAR* Logic_GetPlayerRaceName(RwUInt8 byRace);	// Player ���� �̸� ��ȯ
const WCHAR* Logic_GetNPCRaceName(RwUInt8 byRace);	// NPC ���� �̸� ��ȯ
const WCHAR* Logic_GetMobRaceName(RwUInt8 byRace);	// �� ���� �̸� ��ȯ
const WCHAR* Logic_GetBattleAttributeName(RwUInt8 byAttr);
const WCHAR* Logic_GetSkillName(RwUInt32 tblidx);
const WCHAR* Logic_GetHTBName(RwUInt32 tblidx);
const WCHAR* Logic_GetItemName(RwUInt32 tblidx);
const WCHAR* Logic_GetHoipoiMixSkillName(RwUInt8 byType);	// ȣ�����̹ͽ� ��ų �̸� ��ȯ
const WCHAR* Logic_GetHoipoiMixRecipeName(RwUInt32 tblIdx);
const WCHAR* Logic_GetTeleportTypeName(RwUInt32 uiTeleportType);

RwBool	Logic_GetSystemEffectText( RwUInt32 uiSystemEffectIdx, RwReal fValue, std::wstring& wstrText, RwUInt8 byPercentType, sSKILL_TBLDAT* pSkillData = NULL, RwUInt32* pColor = NULL, RwBool* pBuffShow = NULL );

void Logic_DialogModeMessage(eDialogMode eMode);
RwUInt32 Logic_GetWarnningWorldConceptActionMessageIndex(RwUInt32 uiGrade);
void Logic_WarnningWorldConceptActionMessage(RwUInt32 uiGrade);

void Logic_timeToDetailTime(time_t tTime, sDetailTime& sTime);

///< �ð��� �ѷ��� ǥ��
WCHAR* Logic_GetTimeString(RwReal fSecond);

// �ð��� �ѷ��� �ƴ� ü�� �ð��� ������ ���߾� ǥ���Ѵ�.
WCHAR* Logic_GetCoolTimeString(RwReal fSecond);

///< ���̺� �ε����� �ش� ������ �̸��� �����´�.
RwBool Logic_GetAreaNameFromTblIDX(TBLIDX tblIdx, std::wstring* pstrString);

///< ��ȯ�Ǵ� ��Ʈ���� �ݵ�� �ٸ� �޸� ������ �����ϵ��� �Ѵ�
RwChar* Logic_GetFormatString(const RwChar* pcFormat, ...);
WCHAR* Logic_GetFormatWideString(const WCHAR* pwcFormat, ...);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	���� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RwUInt32 Logic_CalcPrice_for_Sell(sITEM_TBLDAT* pITEM_TBLDAT, sITEM_OPTION_TBLDAT* pITEM_OPTION_TBLDAT, RwUInt32 uiCount);
RwUInt32 Logic_AllRepairCost();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	World Item ����.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic_WorldItemPick(SERIAL_HANDLE hPickSerial);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Target
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic_SobTarget( RwUInt32 hTargetSerial );
void Logic_SobTargetRelease(void);
void Logic_AvatarTarget(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ��ų ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RwReal Logic_GetHTBTotalPower( sHTB_SET_TBLDAT* pHTBData );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	��Ʋ �Ӽ� ������ �� ���� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic_SetBattleAttributeMark( gui::CPanel* pComponent, RwUInt8 byBattleAttribute, RwBool bOutLine = TRUE );
RwUInt32 Logic_GetBattleAttributeColor( RwUInt8 byBattleAttribute );

// �� ��ü���� ��� ����
enum eCounterpartGradeType { CGT_STRONG_1, CGT_SIMILAR, CGT_WEAK_1 };
RwUInt8 Logic_GetCounterpartGradeType(CNtlSobAttr* pOriginalSobAttr, CNtlSobAttr* pCounterpartSobAttr);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	���̾�α� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ŭ���̾�Ʈ�� ����� �پ��� �� Ŭ���̾�Ʈ �����츦 �����
// ���̾�α� �Ŵ���, ���̵� ���̾�α� �Ŵ���, ���̵� ������ �Ŵ�����
// ������ ���� �ʴ� ���̾�α׵��� ��ġ�� �������Ѵ�.
void Logic_LocateDialog_in_CleintRect(CNtlPLGui* pGui, RwBool bForce = FALSE);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// õ������ ����ȸ ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const WCHAR* Logic_GetTBTypeString( RwUInt8 byMainState );
const WCHAR* Logic_GetStringTBMatchType( RwUInt8 byTBMatchType );
const WCHAR* Logic_GetStringTBMatchState( RwUInt8 byTBMatchState );
const WCHAR* Logic_GetAvatarTBJoinState();								// ���� �ƹ�Ÿ�� ���� ����
const WCHAR* Logic_GetTBRemainTimeString( BUDOKAITIME tmTime );
const WCHAR* Logic_GetTBDateToDateString( tm tmAtTime, tm tmToTime );
const WCHAR* Logic_GetTBDateString( tm tmTime );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DBOTIME
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const WCHAR* Logic_GetMailRemainTimeString( DBOTIME tmTime );
RwInt32		 Logic_IsMailRemainTimeOverDay( DBOTIME tmTime );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȣ������ �ͽ� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RwBool		Logic_IsEnableCreateRecipe( TBLIDX idxRecipeTable );
RwInt32		Logic_AmountEnableCreateRecipe( TBLIDX idxRecipeTable );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ȱ�޽��� �ڽ� 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logic_ShowRegenBox(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logic_SetOptionMoviePlay();
void Logic_SetOptionMovieStop();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RwUInt32 Logic_GetItemRankColor( RwUInt8 byRank );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logic_ProcessSecurityResultCode( RwUInt32 uiNPRetCode, sSEC_RET_DATA* pRetData );

#endif
