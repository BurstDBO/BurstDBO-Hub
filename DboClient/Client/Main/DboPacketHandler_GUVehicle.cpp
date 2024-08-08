/*****************************************************************************
* File			: DboPackethandler_GUVehicle.cpp
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2009. 1. 6
* Abstract		: Vechicle ���� ��Ŷ
*****************************************************************************
* Desc         : 
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboPacketHandler.h"



void PacketHandler_GUVehicleStartNfy(void *pPacket)
{
	// Ż �Ϳ� Ÿ�� ������ ���۵ǰų� Ÿ�� �ִ� ä�� Ż ���� �����Ѵ�
	sGU_VEHICLE_START_NFY* pResult = (sGU_VEHICLE_START_NFY*)pPacket;

	RwV3d vSpawnPos;
	vSpawnPos.x = pResult->vStartPosition.x;
	vSpawnPos.y = pResult->vStartPosition.y;
	vSpawnPos.z = pResult->vStartPosition.z;

	CNtlSLEventGenerator::SobVehicleStart(pResult->hDriverHandle,
										  vSpawnPos,
										  pResult->hVehicleItem,
										  pResult->idVehicleItemTblidx);
}

void PacketHandler_GUVehicleEngineStartRes(void *pPacket)
{
	// ������ �õ��� �ɷ����� �ڽſ��� �˸���
	API_GetSLPacketLockManager()->Unlock(GU_VEHICLE_ENGINE_START_RES);

	sGU_VEHICLE_ENGINE_START_RES* pResult = (sGU_VEHICLE_ENGINE_START_RES*) pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(pResult->wResultCode, TRUE);
		return;
	}

	CNtlSLEventGenerator::SobVehicleEngine(Logic_GetAvatarHandle(), VEHICLE_ENGINE_START);
}

void PacketHandler_GUVehicleEngineStartNfy(void *pPacket)
{
	// ������ �õ��� �ɷ����� �ֺ��� �˸���
	sGU_VEHICLE_ENGINE_START_NFY* pResult = (sGU_VEHICLE_ENGINE_START_NFY*) pPacket;

	CNtlSLEventGenerator::SobVehicleEngine(pResult->hDriverHandle, VEHICLE_ENGINE_START);
}

void PacketHandler_GUVehicleEngineStopRes(void *pPacket)
{
	// ������ ���߾����� �ڽſ��� �˸���
	API_GetSLPacketLockManager()->Unlock(GU_VEHICLE_ENGINE_STOP_RES);

	sGU_VEHICLE_ENGINE_STOP_RES* pResult = (sGU_VEHICLE_ENGINE_STOP_RES*) pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		CNtlSLEventGenerator::SobVehicleEngine(Logic_GetAvatarHandle(), VEHICLE_ENGINE_FAIL_REQUEST_STOP);
		GetAlarmManager()->AlarmMessage(pResult->wResultCode, TRUE);
		return;
	}
}

void PacketHandler_GUVehicleEngineStopNfy(void *pPacket)
{
	// ������ ���߾����� �ֺ��� �˸���
	sGU_VEHICLE_ENGINE_STOP_NFY* pResult = (sGU_VEHICLE_ENGINE_STOP_NFY*) pPacket;

	CNtlSLEventGenerator::SobVehicleEngine(pResult->hDriverHandle, VEHICLE_ENGINE_STOP);
}

void PacketHandler_GUVehicleFuelUpdateNfy(void *pPacket)
{
	// ���� ������ ������Ʈ �Ǿ���
	//sGU_VEHICLE_FUEL_UPDATE_NFY* pResult = (sGU_VEHICLE_FUEL_UPDATE_NFY*) pPacket;

	CNtlSLEventGenerator::SobVehicleEngine(Logic_GetAvatarHandle(), VEHICLE_ENGINE_UPDATE_FUEL);
}

void PacketHandler_GUVehicleEndRes(void *pPacket)
{
	// Ż �Ϳ��� ������ ��û�� ���� ������ �ڽſ��� �˸���
	API_GetSLPacketLockManager()->Unlock(GU_VEHICLE_END_RES);

	sGU_VEHICLE_END_RES* pResult = (sGU_VEHICLE_END_RES*) pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(pResult->wResultCode, TRUE);
		return;
	}
}

void PacketHandler_GUVehicleStuntNfy(void *pPacket)
{
	sGU_VEHICLE_STUNT_NFY* pResult = (sGU_VEHICLE_STUNT_NFY*) pPacket;

	CNtlSLEventGenerator::SobVehicleStunt( pResult->hDriverHandle );
}
