#include "precomp_ntlsimulation.h"
#include "NtlSobVehicle.h"

// core
#include "NtlDebug.h"

// presentation
#include "NtlPLCharacter.h"

// simulation
#include "NtlSobManager.h"
#include "NtlSobVehicleAttr.h"
#include "NtlSobVehicleProxy.h"
#include "NtlSobCharProxy.h"
#include "NtlSobCharProxyDecoration.h"
#include "NtlSLEvent.h"
#include "NtlFSMVehicleActLayer.h"
#include "NtlSLLogic.h"


DEFINITION_MEMORY_POOL( CNtlSobVehicle )


CNtlSobVehicle::CNtlSobVehicle( void )
{
	SetFlags( SLFLAG_ADD_UPDATE | SLFLAG_OBJECT_COLLISION | SLFLAG_CAN_SWIMMING | SLFLAG_FALLING_ENABLE );

	m_pBeData = NULL;

	m_bAttachDriver = FALSE;

	// Centimeter ������ �����
	m_fRideOnOffAccel		= 200.f;
	m_fRideOnOffMaxSpeed	= 200.f;
	m_fRideOnOffCurSpeed	= 0.f;
	m_fTargetRideOnHeight	= 0.f;
	m_fCurRideOnHeight		= 0.f;
}

CNtlSobVehicle::~CNtlSobVehicle( void )
{
}

RwBool CNtlSobVehicle::Create( void )
{
	SetClassName( SLCLASS_NAME_VEHICLE );

	m_pSobProxy = NTL_NEW CNtlSobVehicleProxy;
	m_pSobProxy->Create( 0 );
	m_pSobProxy->SetSobObj( this );

	m_pBeData = NTL_NEW CNtlBeCharData; 

	if ( !CNtlSobActor::Create() )
	{
		return FALSE;
	}

	return TRUE;
}

void CNtlSobVehicle::Destroy(void)
{
	NTL_DELETE( m_pBeData );

	CNtlSobActor::Destroy();
}

void CNtlSobVehicle::Update( RwReal fElapsed )
{
	CNtlSobActor::Update( fElapsed );

	UpdateRideOnHeight( fElapsed );

	UpdateAttachDriverAndVehicle( fElapsed );
}

void CNtlSobVehicle::HandleEvents( RWS::CMsg& pMsg )
{
	if ( pMsg.Id == g_EventSobCreate )
	{
		SNtlEventSobVehicleCreate* pSobCreate = reinterpret_cast<SNtlEventSobVehicleCreate*>(pMsg.pData);

		SetPosition( &pSobCreate->vLoc );
		SetDirection( &pSobCreate->vDir );

		GetSobAttr()->HandleEvents( pMsg );

		GetSobProxy()->HandleEvents( pMsg );

		if ( pSobCreate->bOwnerAvatar )
		{
			m_pFSMLayer = NTL_NEW CNtlFSMVehicleActLayer;
			m_pFSMLayer->SetActor( this ); 

			m_pFSMLayer->Create( SLCONTROLLER_VEHICLE ); 

			SetFlags( GetFlags() | SLFLAG_SERVER_SENDER );
		}
		else
		{
			m_pFSMLayer = NTL_NEW CNtlFSMVehicleActLayer;
			m_pFSMLayer->SetActor( this ); 

			m_pFSMLayer->Create( SLCONTROLLER_VEHICLE_SYNC ); 
		}

		RwV3d vResultPos, vResultDir;
		Logic_GetWorldSlop( this, pSobCreate->vLoc, pSobCreate->vDir, GetSobProxy()->GetPLEntityDepth() / 2.f, vResultPos, vResultDir );

		SetPosition( &vResultPos );
		SetDirection( &vResultDir );
	}

	CNtlSobActor::HandleEvents( pMsg );
}

void CNtlSobVehicle::AttachDriver( RwBool bAttachDriver )
{
	m_bAttachDriver = bAttachDriver;
}

RwReal CNtlSobVehicle::GetMaxRideOnHeight( void )
{
	return ((CNtlSobVehicleAttr*)GetSobAttr())->GetVehicleTable()->wRunHeight;
}

void CNtlSobVehicle::SetRideOnHeight( RwReal fRideOnHeight )
{
	m_fCurRideOnHeight = fRideOnHeight;
}

void CNtlSobVehicle::UpdateRideOnHeight( RwReal fElapsed )
{
	sCHARSTATE* pState = GetServerFullState();

	if ( ASPECTSTATE_VEHICLE == pState->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId )
	{
		if ( pState->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn )
		{
			m_fTargetRideOnHeight = ((CNtlSobVehicleAttr*)GetSobAttr())->GetVehicleTable()->wRunHeight;
		}
		else
		{
			m_fTargetRideOnHeight = 0.f;
		}

		// ���
		if ( m_fTargetRideOnHeight > m_fCurRideOnHeight )
		{
			m_fRideOnOffCurSpeed += m_fRideOnOffAccel * fElapsed;
			m_fRideOnOffCurSpeed = (m_fRideOnOffCurSpeed >= m_fRideOnOffMaxSpeed ? m_fRideOnOffMaxSpeed : m_fRideOnOffCurSpeed);

			m_fCurRideOnHeight += m_fRideOnOffCurSpeed * fElapsed;
			m_fCurRideOnHeight = (m_fCurRideOnHeight >= m_fTargetRideOnHeight ? m_fTargetRideOnHeight : m_fCurRideOnHeight);
		}
		// �ϰ�
		else if ( m_fTargetRideOnHeight < m_fCurRideOnHeight )
		{
			m_fRideOnOffCurSpeed += m_fRideOnOffAccel * fElapsed;
			m_fRideOnOffCurSpeed = (m_fRideOnOffCurSpeed >= m_fRideOnOffMaxSpeed ? m_fRideOnOffMaxSpeed : m_fRideOnOffCurSpeed);

			m_fCurRideOnHeight -= m_fRideOnOffCurSpeed * fElapsed;
			m_fCurRideOnHeight = (m_fCurRideOnHeight <= m_fTargetRideOnHeight ? m_fTargetRideOnHeight : m_fCurRideOnHeight);
		}
		else
		{
			m_fRideOnOffCurSpeed	= 0.f;
			m_fCurRideOnHeight		= m_fTargetRideOnHeight;
		}
	}
	else
	{
		m_fRideOnOffCurSpeed	= 0.f;
		m_fTargetRideOnHeight	= 0.f;
		m_fCurRideOnHeight		= 0.f;
	}
}

void CNtlSobVehicle::UpdateAttachDriverAndVehicle( RwReal fElapsed )
{
	if ( !m_bAttachDriver )
	{
		return;
	}

	CNtlSob* pDriver = GetNtlSobManager()->GetSobObject( GetOwnerID() );

	if ( NULL == pDriver )
	{
		return;
	}

	CNtlPLCharacter* pPLBike = (CNtlPLCharacter*)GetSobProxy()->GetPLMainEntity();
	if ( pPLBike )
	{
		pPLBike->Update( fElapsed );

		RwFrame* pFrame = pPLBike->GetBoneByName( "Bike_Dummy" );

		if ( pFrame )
		{
			RwMatrix* pMat = RwFrameGetLTM( pFrame );

			pDriver->SetDirection( &pMat->at );
			pDriver->SetPosition( &pMat->pos );

			((CNtlSobCharProxy*)pDriver->GetSobProxy())->GetDecorationProxy()->UpdatePlayerNamePosition( pMat->pos );

			pDriver->GetSobProxy()->GetPLMainEntity()->SetMatrix( *pMat );
		}
	}
}
