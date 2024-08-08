#include "precomp_ntlpresentation.h"
#include "NtlInstanceTrailSystem.h"
#include "NtlEffectSystemFreeList.h"
#include "NtlPLGlobal.h"
#include "NtlMath.h"
#include "NtlPLRenderState.h"

void* CNtlInstanceTrailSystem::operator new(size_t size)
{
    NTL_FUNCTION(__FUNCTION__);

    NTL_RETURN(CNtlEffectSystemFreeList::Alloc(CNtlResourceComponentSystem::RESOURCE_SYSTEMTYPE_TRAIL));
}

void CNtlInstanceTrailSystem::operator delete(void *pObj)
{
    CNtlEffectSystemFreeList::Free(CNtlResourceComponentSystem::RESOURCE_SYSTEMTYPE_TRAIL, pObj);
}

CNtlInstanceTrailSystem::CNtlInstanceTrailSystem(void)
{
    Init();
}

CNtlInstanceTrailSystem::~CNtlInstanceTrailSystem(void)
{
    Delete();

}

void CNtlInstanceTrailSystem::Reset() 
{
    Delete();
}

void CNtlInstanceTrailSystem::Init() 
{
    CNtlInstanceTraceSystem::Init();

    m_pEmitterTrail = NULL;
    m_pAttachComponent = NULL;
    ZeroMemory(&m_vPrevTrailPoint, sizeof(RwV3d));

    m_uiMemoryUseSize = sizeof(CNtlInstanceTrailSystem);
}

void CNtlInstanceTrailSystem::Delete() 
{
    CNtlInstanceTraceSystem::Delete();
}

/**
 * Trail ����Ʈ�� �����Ѵ�.
 * \param pComponentSystem Trail�� ���� �θ� InstanceComponentSystem ��ü
 * \param pEmitterTrail Trail ���� ������ ������ �ִ� ������Ƽ ��ü
 * return ���� ����
 */
RwBool CNtlInstanceTrailSystem::Create(CNtlInstanceComponentSystem* pComponentSystem, SNtlPrtStdEmitterTrail* pEmitterTrail)
{
    if(!pEmitterTrail || !pComponentSystem)
        return FALSE;

    m_pEmitterTrail = pEmitterTrail;
    m_pAttachComponent = pComponentSystem;

    // �̺�Ʈ ��ü�� �����Ͽ�, ���� �ִ´�. (���� Ŭ������ �޼ҵ���� �״�� Ȱ���Ҽ� �ֱ� �����̴�)
    m_pEventTrace = NTL_NEW SEventTrace();    
    m_pEventTrace->fLifeTime     = 999999;                      ///< Trail���� LifeTime�� ����.
    m_pEventTrace->fEdgeLifeTime = pEmitterTrail->fEdgeLifeTime;
    m_pEventTrace->fMaxLength    = pEmitterTrail->fMaxLength;
    m_pEventTrace->fEdgeGap      = pEmitterTrail->fEdgeGap;
    m_pEventTrace->nSplinePointCount = pEmitterTrail->nSplinePointCount;
    m_pEventTrace->eSrcBlend     = pEmitterTrail->eSrcBlend;
    m_pEventTrace->eDestBlend    = pEmitterTrail->eDestBlend;
    m_pEventTrace->colStartColor = pEmitterTrail->colStartColor;
    m_pEventTrace->nMaxEdgeCount = pEmitterTrail->nMaxEdgeCount;
    m_pEventTrace->colEndColor   = pEmitterTrail->colEndColor;  
    m_uiMemoryUseSize += sizeof(SEventTrace);

    if(CNtlInstanceEffect::GetLowSpecEnable())
    {
        m_pEventTrace->fEdgeGap *= 1.0f / CNtlInstanceEffect::GetLowSpecRatio();
    }

    // Vertex Buffer ����    
    m_pVertices = NTL_NEW RwIm3DVertex[pEmitterTrail->nMaxEdgeCount * pEmitterTrail->nSplinePointCount * 2];
    if(!m_pVertices)
        return FALSE;
    ZeroMemory(m_pVertices, sizeof(RwIm3DVertex) * pEmitterTrail->nMaxEdgeCount * pEmitterTrail->nSplinePointCount * 2);
    m_uiMemoryUseSize += sizeof(RwIm3DVertex) * pEmitterTrail->nMaxEdgeCount * pEmitterTrail->nSplinePointCount * 2;

    // Pool�� �����Ѵ�.
    m_poolTraceEdge = NTL_NEW STraceEdge[pEmitterTrail->nMaxEdgeCount * pEmitterTrail->nSplinePointCount];
    if(!m_poolTraceEdge)
        return FALSE;
    ZeroMemory(m_poolTraceEdge, sizeof(STraceEdge) * pEmitterTrail->nMaxEdgeCount * pEmitterTrail->nSplinePointCount);
    m_uiMemoryUseSize += sizeof(STraceEdge) * pEmitterTrail->nMaxEdgeCount * pEmitterTrail->nSplinePointCount;

    m_poolControlPoint = NTL_NEW STraceEdge[pEmitterTrail->nMaxEdgeCount];
    if(!m_poolControlPoint)
        return FALSE;
    ZeroMemory(m_poolControlPoint, sizeof(STraceEdge) * pEmitterTrail->nMaxEdgeCount);
    m_uiMemoryUseSize += sizeof(STraceEdge) * pEmitterTrail->nMaxEdgeCount;
    
    // �ؽ��� ����
    std::string strTexture = pEmitterTrail->strTexture;
    m_pCurrentTexture = m_pStandardTexture = CreateTexture(strTexture);

    m_vPrevTrailPoint = *RwMatrixGetPos(&m_pAttachComponent->m_matRender);

    return TRUE;
}

/**
 * ���ο� Edge�� ����Ʈ�� �ǳ��� �߰��Ѵ�. 
 */
void CNtlInstanceTrailSystem::CreateEdge() 
{
    // �ִ� Edge ������ �ʰ��ߴ��� ����Ѵ�.
    if(m_nControlPointIndex >= m_pEventTrace->nMaxEdgeCount)
    {
        // Index�� Pool�� ���� ���ϸ� ó������ �ǵ�����.
        m_nControlPointIndex = 0;        

        m_listControlPoint.erase(m_listControlPoint.begin());
    }
    // �ִ� ���̸� �ʰ� �ߴ��� ����Ѵ�.
    if(m_listTraceEdge.size() > 2)
    {
        RwReal fLength = 0.0f;               

        ListTraceEdge::iterator it = m_listTraceEdge.begin();
        RwV3d  v3dPrevPos = (*it)->vVertices[0].objVertex;
        ++it;

        while(it != m_listTraceEdge.end())
        {            
            RwV3d vLength = (*it)->vVertices[0].objVertex - v3dPrevPos;
            fLength += RwV3dLength(&vLength);

            v3dPrevPos = (*it)->vVertices[0].objVertex;
            ++it;
        }

        if(fLength >= m_pEventTrace->fMaxLength)
        {
            m_listTraceEdge.erase(m_listTraceEdge.begin());            
        }
    }

    // �ΰ��� Vertex�� ��ġ�� �����Ѵ�.
    SetEdgePoint();
    
    // List�� ���ο� ��Ʈ�� ����Ʈ�� �߰��Ѵ�.
    m_poolControlPoint[m_nControlPointIndex].vVertices[0].objVertex = m_vStartPoint;
    m_poolControlPoint[m_nControlPointIndex].vVertices[1].objVertex = m_vEndPoint;

    m_listControlPoint.push_back(&m_poolControlPoint[m_nControlPointIndex]);
    ++m_nControlPointIndex;

    // Spline Curve Point�� �����Ͽ� ����Ʈ�� �߰��Ѵ�.
    CreateSplinePath();  

}

void CNtlInstanceTrailSystem::SetEdgePoint() 
{
    //RwV3d vTrailPoint = *RwMatrixGetPos(&m_pAttachComponent->m_matRender);
    //RwV3d vDir = vTrailPoint - m_vPrevTrailPoint;
    //RwV3dNormalize(&vDir, &vDir);

    //RwV3d vCameraPos = *RwMatrixGetPos(RwFrameGetMatrix(RwCameraGetFrame(CNtlPLGlobal::m_RwCamera)));
    //
    //RwV3d vAtCamera = vCameraPos - m_vPrevTrailPoint;
    //RwV3dNormalize(&vAtCamera, &vAtCamera);

    //RwV3d vRight;
    //RwV3dCrossProduct(&vRight, &vAtCamera, &vDir);
    //RwV3dNormalize(&vRight, &vRight);

    //m_vStartPoint = m_vPrevTrailPoint + vRight * m_pEmitterTrail->fWidth * 0.5f;
    //m_vEndPoint   = m_vPrevTrailPoint - vRight * m_pEmitterTrail->fWidth * 0.5f;

    //m_vPrevTrailPoint = vTrailPoint;

    RwV3d vTrailPoint = *RwMatrixGetPos(&m_pAttachComponent->m_matRender);
    RwV3d vDir = vTrailPoint - m_vPrevTrailPoint;
    RwV3dNormalize(&vDir, &vDir);

    RwV3d vCameraPos = *RwMatrixGetPos(RwFrameGetMatrix(RwCameraGetFrame(CNtlPLGlobal::m_RwCamera)));
    RwV3d vAtCamera = vCameraPos - vTrailPoint;
    RwV3dNormalize(&vAtCamera, &vAtCamera);

    RwV3d vRight;
    RwV3dCrossProduct(&vRight, &vAtCamera, &vDir);
    RwV3dNormalize(&vRight, &vRight);

    m_vStartPoint = vTrailPoint + vRight * m_pEmitterTrail->fWidth * 0.5f;
    m_vEndPoint   = vTrailPoint - vRight * m_pEmitterTrail->fWidth * 0.5f;

    // Offset�� �����Ǿ� ������ �����Ѵ�.
    if(RwV3dLength(&m_pEmitterTrail->vOffset) > 0.0f)
    {
        // Matrix���� ȸ������ �����ͼ� Offset�� ������ �� Point�� ���Ѵ�.
        RwMatrix matComponent = m_pAttachComponent->m_matRender;
        *RwMatrixGetPos(&matComponent) = ZeroAxis;

        RwV3d vOffset;
        RwV3dTransformPoint(&vOffset, &m_pEmitterTrail->vOffset, &matComponent);

        m_vStartPoint += vOffset;
        m_vEndPoint += vOffset;
    }

    m_vPrevTrailPoint = vTrailPoint;
}