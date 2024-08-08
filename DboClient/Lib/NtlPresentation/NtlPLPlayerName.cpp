#include "precomp_ntlpresentation.h"
#include "NtlPLPlayerName.h"
#include "NtlDebug.h"
#include "NtlPLEntityFreeList.h"
#include "NtlMath.h"
#include "gui_precomp.h"
#include "guicore_precomp.h"
#include "gui_font.h"
#include "gui_fontmanager.h"
#include "gui_texture.h"
#include "gui_texturemanager.h"
#include "ntlworldcommon.h"
#include "NtlPLEvent.h"
#include "NtlPLEventGenerator.h"

using namespace gui;

#define dPLAYER_NAME_CREATE_TEXTURE_OFFSET 5

/**
* \brief Constructions
*/
CNtlPLPlayerName::CNtlPLPlayerName()
{
	m_bCameraCullIn		= FALSE;
	m_fCullDist			= PLAYERNAME_DIST;
	m_pFont				= NULL;
	m_pGuildFont		= NULL;
	m_pTexture			= NULL;
	m_pEmblemTexture	= NULL;
	m_pNickTexture		= NULL;
    m_byAlpha			= 255;
	m_byFlag			= dNTL_PL_FLAG_NAME;
	m_bNameVisible		= TRUE;

	m_posNameSize.SetPos( 0, 0 );
	m_posGuildNameSize.SetPos( 0, 0 );
	m_posNickNameSize.SetPos( 0, 0 );

	// World Position �ʱ�ȭ
	CNtlMath::MathRwV3dAssign(&m_v3WorldPosition, 0.0f, 0.0f, 0.0f);

	SetLayer(PLENTITY_LAYER_PLAYERNAME);
	SetClassType(PLENTITY_PLAYER_NAME);
	SetFlags(NTL_PLEFLAG_FRUSTUMOUT_NOTUPDATE | NTL_PLEFLAG_NOT_ADD_WORLD | NTL_PLEFLAG_NOT_PROPERTY_USED | NTL_PLEFLAG_ATTACH);

	AllVertexInit();
	VertexAssign();
}

/**
* \brief Destructions
*/
CNtlPLPlayerName::~CNtlPLPlayerName()
{
}

/**
* \brief Create
* \param pParam		(SPLEntityCreateParam*) Entity�� Create �Ķ���� ����ü
* \return ��������
*/
RwBool CNtlPLPlayerName::Create( const SPLEntityCreateParam * pParam )
{
	NTL_FUNCTION("CNtlPLPlayerName::Create");
	
	NTL_ASSERT( pParam != NULL, RWSTRING( "NULL Param" ) );

	const SPLPlayerNameCreateParam *pPlayerNameParam = reinterpret_cast<const SPLPlayerNameCreateParam*>(pParam);
	if(pPlayerNameParam->pName == NULL)
	{
		NTL_RETURN(FALSE);
	}

	// ī�޶� �ø� �Ÿ�
	m_fCullDist = pPlayerNameParam->fCullDist;

	// �̸� �ؽ��ĸ� ����
	if( !CreateNameTexture( pPlayerNameParam->pName ) )
		NTL_RETURN(FALSE);

	if(pPlayerNameParam->pGuildName == NULL )
	{
		NTL_RETURN(FALSE);
	}
	// ��� �̸��� ���̰� 0���� ũ�ٸ� ��� �̸��� �����Ѵٰ� �Ǵ�
	else if( (RwInt32)wcslen( pPlayerNameParam->pGuildName ) > 0 )
	{
		if( CreateGuildNameTexture( pPlayerNameParam->pGuildName ) )
			m_byFlag = dNTL_PL_FLAG_NAME | dNTL_PL_FLAG_GUILD;

		if( CreateGuildEmblemTexture( pPlayerNameParam->pEmblemFactor) )
			m_byFlag |= dNTL_PL_FLAG_EMBLEM;
		
	}
	
	NTL_RETURN(TRUE);
}

/**
* \brief Destroy
*/
void CNtlPLPlayerName::Destroy(void) 
{
	NTL_FUNCTION("CNtlPLPlayerName::Destroy");
	
	if( m_pFont )
	{
		g_FontMgr.DeleteGuiFont(m_pFont);
		m_pFont = NULL;
	}

	if( m_pGuildFont )
	{
		g_FontMgr.DeleteGuiFont( m_pGuildFont );
		m_pGuildFont = NULL;
	}

	if( m_pTexture )
	{
		g_TextureMgr.DeleteTexture(m_pTexture);
		m_pTexture = NULL;
	}

	if( m_pEmblemTexture )
	{
		GetEmblemMaker()->DestoyEmblem( m_pEmblemTexture );
		m_pEmblemTexture = NULL;
	}

	if( m_pNickTexture )
	{
		g_TextureMgr.DeleteTexture( m_pNickTexture );
		m_pNickTexture = NULL;
	}
		
	NTL_RETURNVOID();
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
RwBool CNtlPLPlayerName::Update(RwReal fElapsed)
{
	// Entity�� ���� ���̴� ���°� �ƴ϶�� Update���� �ʴ´�.
	if(!IsVisible())
		return TRUE;

	// ī�޶� �ø� üũ
	RwSphere sphere;
	sphere.center = m_v3WorldPosition;
	sphere.radius = PLAYERNAME_CAMERA__BOUNDING_RADIUS;

	RwReal fCameraDist;
	RwFrustumTestResult ret = RwCameraFrustumTestSphere(CNtlPLGlobal::m_RwCamera, &sphere);
	if(ret == rwSPHEREOUTSIDE || ret == rwSPHEREBOUNDARY)
	{
		SetCameraCullin( FALSE );

		return TRUE;
	}
	else
	{
		RwV3d v3Dist;
		RwV3dSub(&v3Dist, &sphere.center, &RwCameraGetFrame(CNtlPLGlobal::m_RwCamera)->modelling.pos);

		fCameraDist = RwV3dLength(&v3Dist);
		if(fCameraDist > m_fCullDist)
		{
			SetCameraCullin( FALSE );

			return TRUE;
		}
		else
		{
			SetCameraCullin( TRUE );
		}
	}

	// Flag�� ���� �ٸ� �Լ��� �����Ѵ�.
	if( m_byFlag & dNTL_PL_FLAG_EMBLEM )
		EmblemVertexAssign();
	else
		NameVertexAssign();

	if( m_byFlag & dNTL_PL_FLAG_NICK )
		NickNameVertexAssign();

	RwMatrix matInvert, matScale;
	RwMatrix *pMatrix = RwCameraGetViewMatrix(CNtlPLGlobal::m_RwCamera);
	RwMatrixInvert(&matInvert, pMatrix);

	RwReal fScale = fCameraDist/20.0f;
	if(fScale < 0)
		fScale = 0.0f;

	RwV3d vScale;
	CNtlMath::MathRwV3dAssign(&vScale, 1.0f+fScale, 1.0f+fScale, 1.0f+fScale);
	RwMatrixScale(&matScale, &vScale, rwCOMBINEREPLACE);

	RwMatrixMultiply(&m_matWorld, &matScale, &matInvert);
	CNtlMath::MathRwV3dAssign(&m_matWorld.pos, m_v3WorldPosition.x, m_v3WorldPosition.y, m_v3WorldPosition.z);
	CNtlMath::MathRwV3dAssign(&m_matWorld.right, -m_matWorld.right.x, -m_matWorld.right.y, -m_matWorld.right.z);

	for (RwInt32 i = 0; i < 4; ++ i)
	{
		RwV3dTransformPoint(&m_3dVertices[i].objVertex, &m_v3Pos[i], &m_matWorld);
	}

	if( m_byFlag & dNTL_PL_FLAG_EMBLEM )
	{
		for (RwInt32 i = 0; i < 4; ++ i)
		{
			RwV3dTransformPoint(&m_3dEmblemVertices[i].objVertex, &m_v3EmblemPos[i], &m_matWorld);
		}
	}

	if( m_byFlag & dNTL_PL_FLAG_NICK )
	{
		for (RwInt32 i = 0; i < 4; ++ i)
		{
			RwV3dTransformPoint(&m_3dNickVertices[i].objVertex, &m_v3NickPos[i], &m_matWorld);
		}
	}

	// Alpha �� ����ġ�� 1.0f �ƴ϶�� Entity�� ���� ����ġ ���� ���� ��ƼƼ�� ���İ��� �����Ѵ�.
    if(GetWeightAlpha() != 1.0f)
    {
        RwUInt8 byAlpha = (RwUInt8)(m_byAlpha * GetWeightAlpha());
        for(int i = 0; i < 4; ++i)
        {
           RwIm3DVertexSetRGBA(&m_3dVertices[i], 255, 255, 255, byAlpha);        
        }
    }

	return TRUE;
}

/**
* \brief Render
* �̸��� Emblem�� �������Ѵ�.
*/
RwBool CNtlPLPlayerName::Render(void)
{
	if(!IsVisible() || !m_bCameraCullIn)
		return TRUE;

	RenderName();
	RenderEmblem();
	RenderNick();
		
	return TRUE;
}

/**
* \brief PlayerName Entity�� ���ĸ� �����Ѵ�.
* \param byValue	(RwUInt8) ���İ�
*/
void CNtlPLPlayerName::SetAlpha(RwUInt8 byValue)
{
	RwIm3DVertexSetRGBA(&m_3dVertices[0], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dVertices[1], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dVertices[2], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dVertices[3], 255, 255, 255, byValue);

	RwIm3DVertexSetRGBA(&m_3dEmblemVertices[0], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dEmblemVertices[1], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dEmblemVertices[2], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dEmblemVertices[3], 255, 255, 255, byValue);

	RwIm3DVertexSetRGBA(&m_3dNickVertices[0], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dNickVertices[1], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dNickVertices[2], 255, 255, 255, byValue);
	RwIm3DVertexSetRGBA(&m_3dNickVertices[3], 255, 255, 255, byValue);

    m_byAlpha = byValue;
}

/**
* \brief new ������ �����ε�
* \param size	(size_t) �޸� ������
* \return (void*) CNtlPLEntityFreeList�� Alloc�� ���ϰ�
*/
void* CNtlPLPlayerName::operator new(size_t size)
{
	NTL_FUNCTION("CNtlPLPlayerName::operator new");

	NTL_RETURN(CNtlPLEntityFreeList::Alloc(PLENTITY_PLAYER_NAME));
}

/**
* \brief delte ������ �����ε�
* \param pObj	(void*) CNtlPLEntityFreeList�� Free�� ��������� �ϴ� ��ü�� void pointer
*/
void CNtlPLPlayerName::operator delete(void *pObj)
{
	CNtlPLEntityFreeList::Free(PLENTITY_PLAYER_NAME, pObj);
}

/**
* \brief ��� ���ؽ� ������ 0���� �ʱ�ȭ�Ѵ�.
*/
void CNtlPLPlayerName::AllVertexInit( void ) 
{
	memset( &m_v3Pos, 0, sizeof(RwV3d) * PLAYERNAME_VERTEX_COUNT );
	memset( &m_v3EmblemPos, 0, sizeof(RwV3d) * PLAYERNAME_VERTEX_COUNT );
	memset( &m_v3NickPos, 0, sizeof(RwV3d) * PLAYERNAME_VERTEX_COUNT );
	memset( &m_3dVertices, 0, sizeof(RwIm3DVertex) * PLAYERNAME_VERTEX_COUNT );
	memset( &m_3dEmblemVertices, 0, sizeof(RwIm3DVertex) * PLAYERNAME_VERTEX_COUNT );
	memset( &m_3dNickVertices, 0, sizeof(RwIm3DVertex) * PLAYERNAME_VERTEX_COUNT );
}

/**
* \brief PlayerName���� ���̴� ��� ���ؽ����� UV�� RGB���� ����
*/
void CNtlPLPlayerName::VertexAssign( void ) 
{
	// UV Setting
	RwIm3DVertexSetU (&m_3dVertices[0], 0.0f);
	RwIm3DVertexSetV (&m_3dVertices[0], 0.0f);

	RwIm3DVertexSetU (&m_3dVertices[1], 0.0f);
	RwIm3DVertexSetV (&m_3dVertices[1], 1.0f);

	RwIm3DVertexSetU (&m_3dVertices[2], 1.0f);
	RwIm3DVertexSetV (&m_3dVertices[2], 0.0f);

	RwIm3DVertexSetU (&m_3dVertices[3], 1.0f);
	RwIm3DVertexSetV (&m_3dVertices[3], 1.0f);

	// RGBA Setting
	for(RwInt32 i = 0; i < 4; i++)
	{
		RwIm3DVertexSetRGBA(&m_3dVertices[i], 255, 255, 255, 255);
	}

	// UV Setting
	RwIm3DVertexSetU (&m_3dEmblemVertices[0], 0.0f);
	RwIm3DVertexSetV (&m_3dEmblemVertices[0], 0.0f);

	RwIm3DVertexSetU (&m_3dEmblemVertices[1], 0.0f);
	RwIm3DVertexSetV (&m_3dEmblemVertices[1], 1.0f);

	RwIm3DVertexSetU (&m_3dEmblemVertices[2], 1.0f);
	RwIm3DVertexSetV (&m_3dEmblemVertices[2], 0.0f);

	RwIm3DVertexSetU (&m_3dEmblemVertices[3], 1.0f);
	RwIm3DVertexSetV (&m_3dEmblemVertices[3], 1.0f);

	// RGBA Setting
	for(RwInt32 i = 0; i < 4; i++)
	{
		RwIm3DVertexSetRGBA(&m_3dEmblemVertices[i], 255, 255, 255, 255);
	}

	// UV Setting
	RwIm3DVertexSetU (&m_3dNickVertices[0], 0.0f);
	RwIm3DVertexSetV (&m_3dNickVertices[0], 0.0f);

	RwIm3DVertexSetU (&m_3dNickVertices[1], 0.0f);
	RwIm3DVertexSetV (&m_3dNickVertices[1], 1.0f);

	RwIm3DVertexSetU (&m_3dNickVertices[2], 1.0f);
	RwIm3DVertexSetV (&m_3dNickVertices[2], 0.0f);

	RwIm3DVertexSetU (&m_3dNickVertices[3], 1.0f);
	RwIm3DVertexSetV (&m_3dNickVertices[3], 1.0f);

	// RGBA Setting
	for(RwInt32 i = 0; i < 4; i++)
	{
		RwIm3DVertexSetRGBA(&m_3dNickVertices[i], 255, 255, 255, 255);
	}

	RwMatrixSetIdentity(&m_matWorld);
}

/**
* \brief PlayerName �̳� Guild Name ������ ����Ҷ� ���Ǵ� ���ؽ� ����
*/
void CNtlPLPlayerName::NameVertexAssign(void) 
{
	if( m_pTexture == NULL )
		return;

	RwReal fWidth = GetAdjustPolygonWidth( m_pTexture->GetWidth() );
	RwReal fHeight = GetAdjustPolygonHeight( m_pTexture->GetHeight() );

	// Name Texture Local Position
	m_v3Pos[0].x = (fWidth/2.f);
	m_v3Pos[0].y = (-fHeight/2.f);
	m_v3Pos[0].z = 0.f;

	m_v3Pos[1].x = (fWidth/2.f);
	m_v3Pos[1].y = (fHeight/2.f);
	m_v3Pos[1].z = 0.f;

	m_v3Pos[2].x = (-fWidth/2.f);
	m_v3Pos[2].y = (-fHeight/2.f);	
	m_v3Pos[2].z = 0.f;

	m_v3Pos[3].x = (-fWidth/2.f);
	m_v3Pos[3].y = (fHeight/2.f);	
	m_v3Pos[3].z = 0.f;
	
}

/**
* \brief Emblem �̹��� ���� ��µɶ� ���Ǵ� ���ؽ� ����
*/
void CNtlPLPlayerName::EmblemVertexAssign(void) 
{
	if( m_pEmblemTexture == NULL )
		return;

	// �̸��� �����ϴ� ������ ������
	RwReal fNameWidth = GetAdjustPolygonWidth( m_pTexture->GetWidth() );
	RwReal fNameHeight = GetAdjustPolygonHeight( m_pTexture->GetHeight() );
	
	// ������ �����ϴ� ������ ������
	/*RwReal fEmblemWidth = GetAdjustPolygonWidth( m_pEmblemTexture->raster->width );
	RwReal fEmblemHeight = GetAdjustPolygonHeight( m_pEmblemTexture->raster->height );*/

	RwReal fEmblemWidth = (RwReal)m_pEmblemTexture->raster->width * PLAYERNAME_EMBLEM_BASIS_CX;
	RwReal fEmblemHeight =(RwReal)m_pEmblemTexture->raster->height * PLAYERNAME_EMBLEM_BASIS_CY;
	
	// �̸��� ���� �ؽ��� ũ��
	RwInt32 nNameHeight = m_posNameSize.y + m_posGuildNameSize.y + PLAYERNAME_LINE_INTERVAL_Y;
	RwInt32 nNameWidth = m_posNameSize.x > m_posGuildNameSize.x ? m_posNameSize.x : m_posGuildNameSize.x;

	// �̸��� ���� ������ ������
	RwReal fNameAdjustWidth = fNameWidth * ( (RwReal)nNameWidth/(RwReal)m_pTexture->GetWidth() );
	RwReal fNameAdjustHeight = fNameHeight * ( (RwReal)nNameHeight/(RwReal)m_pTexture->GetHeight() );

	RwReal fTotalWidth = fEmblemWidth + fNameWidth;
	RwReal fTotalHeight = fEmblemHeight + fNameHeight;

	RwReal fTotalAdjustWidth = fEmblemWidth +  fNameAdjustWidth;
	RwReal fTotalAdjustHeight = fEmblemWidth + fNameAdjustHeight;

	// Name�� Offset
	RwReal fOffsetNameWidth = (fEmblemWidth)/2.f;
	RwReal fOffsetNameHeight = (fNameHeight-fNameAdjustHeight)/2.f;
	
	RwReal fOffsetExtraWidth = (fNameWidth - fNameAdjustWidth)/2.f;

	// Emblem �� Offset

	RwReal fOffsetEmblemExtraWidth = (fNameWidth - fNameAdjustWidth)/2.f;
	RwReal fOffsetEmblemWidth = (fTotalWidth/2.f) - (fEmblemWidth/2.f);
	
	// Name Texture Local Position
	m_v3Pos[0].x = (fNameWidth/2.f) - fOffsetNameWidth - fOffsetExtraWidth - PLAYERNAME_BOX_OFFSET;
	m_v3Pos[0].y = (-fNameHeight/2.f) + fOffsetNameHeight;
	m_v3Pos[0].z = 0.f;

	m_v3Pos[1].x = (fNameWidth/2.f) - fOffsetNameWidth - fOffsetExtraWidth - PLAYERNAME_BOX_OFFSET;
	m_v3Pos[1].y = (fNameHeight/2.f) + fOffsetNameHeight;
	m_v3Pos[1].z = 0.f;

	m_v3Pos[2].x = (-fNameWidth/2.f) - fOffsetNameWidth - fOffsetExtraWidth - PLAYERNAME_BOX_OFFSET;
	m_v3Pos[2].y = (-fNameHeight/2.f) + fOffsetNameHeight;	
	m_v3Pos[2].z = 0.f;

	m_v3Pos[3].x = (-fNameWidth/2.f) - fOffsetNameWidth - fOffsetExtraWidth - PLAYERNAME_BOX_OFFSET;
	m_v3Pos[3].y = (fNameHeight/2.f) + fOffsetNameHeight;	
	m_v3Pos[3].z = 0.f;

	// Emblem Texture Local Position
	m_v3EmblemPos[0].x = (fEmblemWidth/2.f) + (fOffsetEmblemWidth) - (fOffsetExtraWidth) + PLAYERNAME_BOX_OFFSET;
	m_v3EmblemPos[0].y = (-fEmblemHeight/2.f);
	m_v3EmblemPos[0].z = 0.f;	

	m_v3EmblemPos[1].x = (fEmblemWidth/2.f) + (fOffsetEmblemWidth) - (fOffsetExtraWidth) + PLAYERNAME_BOX_OFFSET;
	m_v3EmblemPos[1].y = (fEmblemHeight/2.f);
	m_v3EmblemPos[1].z = 0.f;

	m_v3EmblemPos[2].x = (-fEmblemWidth/2.f) + (fOffsetEmblemWidth) - (fOffsetExtraWidth) + PLAYERNAME_BOX_OFFSET;
	m_v3EmblemPos[2].y = (-fEmblemHeight/2.f);
	m_v3EmblemPos[2].z = 0.f;

	m_v3EmblemPos[3].x = (-fEmblemWidth/2.f) + (fOffsetEmblemWidth) - (fOffsetExtraWidth) + PLAYERNAME_BOX_OFFSET;
	m_v3EmblemPos[3].y = (fEmblemHeight/2.f);
	m_v3EmblemPos[3].z = 0.f;
}

/**
* \brief �� ������ ��µ� ���ؽ��� ��ġ�� ũ�⸦ ����
*/
void CNtlPLPlayerName::NickNameVertexAssign( void )
{
	if( m_pNickTexture == NULL )
		return;

	RwReal fWidth = GetAdjustPolygonWidth( m_pNickTexture->GetWidth() );
	RwReal fHeight = GetAdjustPolygonHeight( m_pNickTexture->GetHeight() );

	m_v3NickPos[0].x = (fWidth/2.f);
	m_v3NickPos[0].y = (-fHeight/2.f) - m_v3Pos[1].y - PLAYERNAME_NICK_OFFSET;
	m_v3NickPos[0].z = 0.f;

	m_v3NickPos[1].x = (fWidth/2.f);
	m_v3NickPos[1].y = (fHeight/2.f) - m_v3Pos[1].y - PLAYERNAME_NICK_OFFSET;
	m_v3NickPos[1].z = 0.f;

	m_v3NickPos[2].x = (-fWidth/2.f);
	m_v3NickPos[2].y = (-fHeight/2.f) - m_v3Pos[1].y - PLAYERNAME_NICK_OFFSET;	
	m_v3NickPos[2].z = 0.f;

	m_v3NickPos[3].x = (-fWidth/2.f);
	m_v3NickPos[3].y = (fHeight/2.f) - m_v3Pos[1].y - PLAYERNAME_NICK_OFFSET;	
	m_v3NickPos[3].z = 0.f;
}

/**
* \brief Texture ����� ���� �� ���ϸ��� �������� ����� �����Ѵ�.
* \param nSize	(RwInt32) �ؽ����� ���� ������
* \return (RwReal) �������� ������
*/
RwReal CNtlPLPlayerName::GetAdjustPolygonWidth( RwInt32 nSize ) 
{
	// Texture Size 1 �� �������� ���ϴ� ������ ������
	return nSize * PLAYERNAME_BOX_BASIS_CX;
}

/**
* \brief Texture ����� ���� �� ���ϸ��� �������� ����� �����Ѵ�.
* \param nSize	(RwInt32) �ؽ����� ���� ������
* \return (RwReal) �������� ������
*/
RwReal CNtlPLPlayerName::GetAdjustPolygonHeight( RwInt32 nSize ) 
{
	return nSize * PLAYERNAME_BOX_BASIS_CY;
}

/**
* \brief �̸��� �ؽ��ĸ� �����Ѵ�. (�̸��� ũ�⸸ ���)
* \param pName	(const WCHAR*) �̸��� ���ڿ� ������
* \return (RwBool) ���� ����
*/
RwBool CNtlPLPlayerName::CreateNameTexture( const WCHAR* pName ) 
{
	// Texture�� �̹� �����ϰ� �ִٸ� ����� �ٽ� �����ؾ� �Ѵ�. ���� : Resize
	if( m_pTexture )
	{
		g_TextureMgr.DeleteTexture( m_pTexture );
		m_pTexture = NULL;
	}

	// Font ����
	m_pFont = g_FontMgr.CreateGuiFont( DEFAULT_FONT, dNTL_PLAYERNAME_FONTSIZE_NAME, DEFAULT_FONT_ATTR ); 
	if(m_pFont == NULL)
	{
		NTL_RETURN(FALSE);
	}

	// Name�� ���ۿ� ��� �ִ� ���ڿ��� �Ѱ��� ���ٸ� ���ڰ� ���� ������ �����ϰ� FALSE�� ����
	if( (RwInt32)wcslen( pName ) <= 0 )
	{
		NTL_RETURN(FALSE);
	}
 
	// Text�� �ȼ� ����� ���ؼ� �����ϰ� �ؽ��ĸ� �����Ѵ�.
	CPos size = m_pFont->GetTextWSize( pName, (int)wcslen( pName )); 	
	m_posNameSize.SetPos( size.x, size.y );
	m_pTexture = g_TextureMgr.CreateTexture( m_posNameSize.x + dPLAYER_NAME_CREATE_TEXTURE_OFFSET, m_posNameSize.y );
	if(m_pTexture == NULL)
	{
		NTL_RETURN(FALSE);
	}

	RwTextureSetFilterMode(m_pTexture->GetTexture(), rwFILTERLINEAR); 
	RwTextureSetAddressingU(m_pTexture->GetTexture(), rwTEXTUREADDRESSWRAP);
	RwTextureSetAddressingV(m_pTexture->GetTexture(), rwTEXTUREADDRESSWRAP);

	// World Tool Mode������ ���� SetNameColor() �Լ��� ȣ����� �ʰ� RefreshName���� �Լ��� ���� ����Ѵ�.
#ifdef dNTL_WORLD_TOOL_MODE
	COLORREF color = RGB(255, 255, 255);

	m_pFont->TextOutW(L"               ", 0, 0);
	m_pFont->TextOutW(pName, 0, 0);

	CRectangle rect;
	rect.left = (m_pTexture->GetWidth()-size.x)/2;
	rect.top = (m_pTexture->GetHeight()-size.y)/2;
	rect.right = rect.left + size.x;
	rect.bottom = rect.top + size.y;

	// texture�� string copy
	g_FontMgr.BitmapToTexture(m_pTexture, rect, color,TE_SHADOW, 0, 2);
#endif

	NTL_RETURN(TRUE);
}

/**
* \brief ��� �̸����� ����ϴ� �ؽ��ĸ� �����.
* \param pGuildName	(const WCHAR*) ����̸��� ���ڿ�
* \return ��������
*/
RwBool CNtlPLPlayerName::CreateGuildNameTexture(const WCHAR* pGuildName) 
{
	// ��� �̸��� ��Ʈ�� �����.
	m_pGuildFont = g_FontMgr.CreateGuiFont( DEFAULT_FONT, dNTL_PLAYERNAME_FONTSIZE_GUILD, DEFAULT_FONT_ATTR ); 
	if(m_pGuildFont == NULL)
	{
		NTL_RETURN(FALSE);
	}

	// Texture Resize ( Delete & Create )
	if( m_pTexture )
	{
		g_TextureMgr.DeleteTexture(m_pTexture);
		m_pTexture = NULL;
	}

	// ������ ����� �����ϰ� ����� �˸��� �ؽ��ĸ� �����.
	CPos size = m_pGuildFont->GetTextWSize(pGuildName, (int)wcslen(pGuildName)); 
	m_posGuildNameSize.SetPos( size.x, size.y );

	RwInt32 nMaxWidth = m_posNameSize.x > m_posGuildNameSize.x ? m_posNameSize.x : m_posGuildNameSize.x;

	m_pTexture = g_TextureMgr.CreateTexture( nMaxWidth+dPLAYER_NAME_CREATE_TEXTURE_OFFSET , m_posNameSize.y+m_posGuildNameSize.y+PLAYERNAME_LINE_INTERVAL_Y );
	if( m_pTexture == NULL )
		NTL_RETURN(FALSE);

	RwTextureSetFilterMode(m_pTexture->GetTexture(), rwFILTERLINEAR); 
	RwTextureSetAddressingU(m_pTexture->GetTexture(), rwTEXTUREADDRESSWRAP);
	RwTextureSetAddressingV(m_pTexture->GetTexture(), rwTEXTUREADDRESSWRAP);

	NTL_RETURN(TRUE);
}

/**
* \brief ��� ������ �ؽ��ĸ� �����. ( EmblemMaker���� ������� �ؽ����� �����͸� ������ �´�.)
* \param pEmblemFactor	(sEmblemFactor*) ���� ���� ����ü
* \return ��������
*/
RwBool CNtlPLPlayerName::CreateGuildEmblemTexture(sEmblemFactor *pEmblemFactor) 
{
	// ���࿡ ������ EmblemTexture�� �ִٸ� ���� ����Ŀ�� ��û�Ͽ� ���۷��� ī��Ʈ�� 1 �ٿ��ش�.
	if( m_pEmblemTexture )
	{
		GetEmblemMaker()->DestoyEmblem( m_pEmblemTexture );
		m_pEmblemTexture = NULL;
	}

	// Emblem Texture�� NULL�� ��ȯ�ϸ� ������ ����� �ȵǾ� �ִ� ��.
	m_pEmblemTexture = GetEmblemMaker()->CreateEmblem( pEmblemFactor );
	if( m_pEmblemTexture == NULL )
		return FALSE;

	return TRUE;
}

RwBool CNtlPLPlayerName::CreateNickNameTexture( const WCHAR* pNickName )
{
	// ��� �̸��� ��Ʈ�� �����.
	m_pNickFont = g_FontMgr.CreateGuiFont( DEFAULT_FONT, dNTL_PLAYERNAME_FONTSIZE_NICK, DEFAULT_FONT_ATTR ); 
	if(m_pNickFont == NULL)
	{
		NTL_RETURN(FALSE);
	}

	// Texture Resize ( Delete & Create )
	if( m_pNickTexture )
	{
		g_TextureMgr.DeleteTexture(m_pNickTexture);
		m_pNickTexture = NULL;
	}

	// ������ ����� �����ϰ� ����� �˸��� �ؽ��ĸ� �����.
	CPos size = m_pNickFont->GetTextWSize( pNickName, (int)wcslen(pNickName)); 
	m_posNickNameSize.SetPos( size.x, size.y );

	m_pNickTexture = g_TextureMgr.CreateTexture( m_posNickNameSize.x+dPLAYER_NAME_CREATE_TEXTURE_OFFSET , m_posNickNameSize.y );
	if( m_pNickTexture == NULL )
		NTL_RETURN(FALSE);

	RwTextureSetFilterMode(m_pNickTexture->GetTexture(), rwFILTERLINEAR); 
	RwTextureSetAddressingU(m_pNickTexture->GetTexture(), rwTEXTUREADDRESSWRAP);
	RwTextureSetAddressingV(m_pNickTexture->GetTexture(), rwTEXTUREADDRESSWRAP);

	NTL_RETURN(TRUE);
}

/**
* \brief �̸� �Ǵ� ��� �̸����� �������Ѵ�.
* \return ��������
*/
RwBool CNtlPLPlayerName::RenderName( void ) 
{
	if(m_pTexture)
		RwD3D9SetTexture(m_pTexture->GetTexture(), 0);
	else
	{
		RwD3D9SetTexture(NULL, 0);
		return FALSE; // m_pTexture�� NULL�̸� ���������� �ʴ´�.
	}

	RwUInt32 nTransformFlags = rwIM3D_VERTEXUV | rwIM3D_ALLOPAQUE;

	if( RwIm3DTransform(m_3dVertices, 4, &CNtlPLGlobal::m_matIden, nTransformFlags) )
	{                         
		RwIm3DRenderPrimitive(rwPRIMTYPETRISTRIP);  

		RwIm3DEnd();
	}

	return TRUE;
}

/**
* \brief ������ �������Ѵ�.
* \param ���� ����
*/
RwBool CNtlPLPlayerName::RenderEmblem( void ) 
{
	if( !(m_byFlag & dNTL_PL_FLAG_EMBLEM) )
		return FALSE;

	if(m_pEmblemTexture)
		RwD3D9SetTexture(m_pEmblemTexture, 0);
	else
	{
		RwD3D9SetTexture(NULL, 0);
		return FALSE; // m_pTexture�� NULL�̸� ���������� �ʴ´�.
	}

	RwUInt32 nTransformFlags = rwIM3D_VERTEXUV | rwIM3D_ALLOPAQUE;

	if( RwIm3DTransform(m_3dEmblemVertices, 4, &CNtlPLGlobal::m_matIden, nTransformFlags) )
	{                         
		RwIm3DRenderPrimitive(rwPRIMTYPETRISTRIP);  

		RwIm3DEnd();
	}

	return TRUE;
}

RwBool CNtlPLPlayerName::RenderNick( void )
{
	if(m_pNickTexture)
		RwD3D9SetTexture(m_pNickTexture->GetTexture(), 0);
	else
	{
		RwD3D9SetTexture(NULL, 0);
		return FALSE; // m_pNickTexture�� NULL�̸� ���������� �ʴ´�.
	}

	RwUInt32 nTransformFlags = rwIM3D_VERTEXUV | rwIM3D_ALLOPAQUE;

	if( RwIm3DTransform(m_3dNickVertices, 4, &CNtlPLGlobal::m_matIden, nTransformFlags) )
	{                         
		RwIm3DRenderPrimitive(rwPRIMTYPETRISTRIP);  

		RwIm3DEnd();
	}

	return TRUE;
}

/**
* \brief �̸��� ���� �������� ������Ʈ �Ѵ�.
* \param pPos	(const RwV3d) ������ ������ �� ������
*/
void CNtlPLPlayerName::SetPosition(const RwV3d *pPos)
{
	// position�� update ���� ���.
	if(!IsVisible())
		return;

	// World Position�� ����
	m_v3WorldPosition = *pPos;
}

/**
* \brief ���� ���� ����� ��ǥ�� ����
* \return ���� ����� ��ǥ ( ī�޶��� ����� )
*/
RwV3d CNtlPLPlayerName::GetPosition(void)
{
	return m_matWorld.pos;
}
	
void CNtlPLPlayerName::SetNameColor(const WCHAR* pwcName, COLORREF color)
{
	if( m_pTexture )
		m_pTexture->FillClear();

	m_pFont->TextOutW(L"                ");
	m_pFont->TextOutW(pwcName);

	if( m_pTexture )
	{
		CRectangle rect;
		CPos size = m_pFont->GetTextWSize(pwcName, (int)wcslen(pwcName));

		rect.left	= (m_pTexture->GetWidth()-size.x)/2;
		rect.top	= (m_pTexture->GetHeight()-size.y)/2;
		rect.right	= rect.left + size.x;
		rect.bottom = rect.top + size.y;

		// texture�� string copy
		g_FontMgr.BitmapToTexture(m_pTexture, rect, color, TE_SHADOW, 0, 2);
	}
}

/**
* \brief �̸��� �÷��� �������ش�.
* \param pwcName		(const WCHAR*) �̸�
* \param color			(COLORREF) �̸��� ����
* \param pwcGuildName	(const WCHAR*) ��� �̸�
* \param guildcolor		(COLORREF) ��� �̸��� ����
* \param pEmblemFactor	(sEmblemFactor*) ���� ������ ����ü
*/
void CNtlPLPlayerName::SetNameColor( const WCHAR* pwcName, COLORREF color, const WCHAR* pwcGuildName, COLORREF guildcolor
									,sEmblemFactor* pEmblemFactor )
{
	if( m_pTexture )
		m_pTexture->FillClear();

	// �̸� ��ȿ�� �Ǵ�
	if( pwcName == NULL )
		return;
	else if( (RwInt32)wcslen( pwcName ) <= 0 )
		return;

	// �Ǵ�
	if( pwcGuildName == NULL )
	{
		if( CreateNameTexture( pwcName ) )
			m_byFlag = dNTL_PL_FLAG_NAME;
	}
	else if( (RwInt32)wcslen( pwcGuildName ) > 0 )
	{
		// ��� �̸��� ���� �����Ͽ��ٸ� ���� �Ǵܱ��� �Ѵ�.
		if( CreateGuildNameTexture( pwcGuildName ) )
		{
			m_byFlag = dNTL_PL_FLAG_NAME | dNTL_PL_FLAG_GUILD;

			if( CreateGuildEmblemTexture( pEmblemFactor ) )
				m_byFlag = dNTL_PL_FLAG_NAME | dNTL_PL_FLAG_GUILD | dNTL_PL_FLAG_EMBLEM;
		}
	}
	// ��� �̸� �����Ͱ� NULL�� �ƴϰ� ���۰� 0 �� ���� �̸��� ��µȴ�.
	else
	{
		if( CreateNameTexture( pwcName ) )
			m_byFlag = dNTL_PL_FLAG_NAME;
	}

	if( m_pNickTexture )
		m_byFlag |= dNTL_PL_FLAG_NICK;


	m_pFont->TextOutW(L"                ");
	m_pFont->TextOutW(pwcName);

	if( m_pTexture )
	{
		if( m_byFlag & dNTL_PL_FLAG_EMBLEM )
		{
			CRectangle rect;
			CPos size = m_pFont->GetTextWSize(pwcName, (int)wcslen(pwcName));

			rect.left	= 0;
			rect.top	= 0;
			rect.right	= rect.left + size.x;
			rect.bottom = rect.top + size.y;

			// texture�� string copy
			g_FontMgr.BitmapToTexture(m_pTexture, rect, color, TE_SHADOW, 0, 2);

			CPos size2 = m_pGuildFont->GetTextWSize(pwcGuildName, (int)wcslen(pwcGuildName)); 

			m_pGuildFont->TextOutW(L"                                ");
			m_pGuildFont->TextOutW(pwcGuildName);

			rect.left = 0;
			rect.top = size.y + PLAYERNAME_LINE_INTERVAL_Y;
			rect.right = rect.left + size2.x;
			rect.bottom = rect.top + size2.y;

			// texture�� string copy
			g_FontMgr.BitmapToTexture(m_pTexture, rect, guildcolor, TE_SHADOW, 0, 2);
		}
		else if( m_byFlag & dNTL_PL_FLAG_GUILD )
		{
			CRectangle rect;
			CPos size = m_pFont->GetTextWSize(pwcName, (int)wcslen(pwcName));

			rect.left	= (m_pTexture->GetWidth()-size.x)/2;
			rect.top	= 0;
			rect.right	= rect.left + size.x;
			rect.bottom = rect.top + size.y;

			// texture�� string copy
			g_FontMgr.BitmapToTexture(m_pTexture, rect, color, TE_SHADOW, 0, 2);

			CPos size2 = m_pGuildFont->GetTextWSize(pwcGuildName, (int)wcslen(pwcGuildName)); 

			m_pGuildFont->TextOutW(L"                                ");
			m_pGuildFont->TextOutW(pwcGuildName);

			rect.left = (m_pTexture->GetWidth()-size2.x)/2;
			rect.top = size.y + PLAYERNAME_LINE_INTERVAL_Y;
			rect.right = rect.left + size2.x;
			rect.bottom = rect.top + size2.y;

			// texture�� string copy
			g_FontMgr.BitmapToTexture(m_pTexture, rect, guildcolor, TE_SHADOW, 0, 2);
		}
		else
		{
			CRectangle rect;
			CPos size = m_pFont->GetTextWSize(pwcName, (int)wcslen(pwcName));

			rect.left	= (m_pTexture->GetWidth()-size.x)/2;
			rect.top	= (m_pTexture->GetHeight()-size.y)/2;
			rect.right	= rect.left + size.x;
			rect.bottom = rect.top + size.y;

			// texture�� string copy
			g_FontMgr.BitmapToTexture(m_pTexture, rect, color, TE_SHADOW, 0, 2);
		}
	}
}

RwBool CNtlPLPlayerName::IsExistEmblemTexture()
{
	if( m_pEmblemTexture )
		return true;

	return false;
}

void CNtlPLPlayerName::SetVisible( RwBool bVisible )
{
	if( bVisible )
	{
		// SetVisible(TRUE) �� ���� �� NameVisible �� TRUE ��� �̸��� �����ش�.
		if( m_bNameVisible )
		{
			CNtlPLEntity::SetVisible( bVisible );
		}
	}
	else
	{
		// SetVisible(FALSE) �� ���� ���� ������ ���ش�.
		CNtlPLEntity::SetVisible( bVisible );
	}
}

void CNtlPLPlayerName::EnablePlayerNameVisible( RwBool bVisible )
{
	SetVisible( bVisible );

	m_bNameVisible = bVisible;
}

RwBool CNtlPLPlayerName::IsEnablePlayerNameVisible()
{
	return m_bNameVisible;
}

void CNtlPLPlayerName::SetCameraCullin( RwBool bCullin )
{
	m_bCameraCullIn = bCullin;
}

void CNtlPLPlayerName::SetTitleColor( const WCHAR* pwcTitle, COLORREF color )
{
	if( m_pNickTexture )
		m_pNickTexture->FillClear();

	// �̸� ��ȿ�� �Ǵ�
	if( pwcTitle == NULL || (RwInt32)wcslen( pwcTitle ) <= 0 )
	{
		if( m_pNickTexture )
		{
			g_TextureMgr.DeleteTexture(m_pNickTexture);
			m_pNickTexture = NULL;
		}

		return;
	}	

	// �Ǵ�
	if( CreateNickNameTexture( pwcTitle ) )
	{
			m_byFlag |= dNTL_PL_FLAG_NICK;
	}
	

	m_pNickFont->TextOutW(L"                ");
	m_pNickFont->TextOutW(pwcTitle);

	if( m_pNickTexture )
	{
		CRectangle rect;
		CPos size = m_pNickFont->GetTextWSize(pwcTitle, (int)wcslen(pwcTitle));

		rect.left	= (m_pNickTexture->GetWidth()-size.x)/2;
		rect.top	= (m_pNickTexture->GetHeight()-size.y)/2;
		rect.right	= rect.left + size.x;
		rect.bottom = rect.top + size.y;

		// texture�� string copy
		g_FontMgr.BitmapToTexture(m_pNickTexture, rect, color, TE_SHADOW, 0, 2);
	}
}