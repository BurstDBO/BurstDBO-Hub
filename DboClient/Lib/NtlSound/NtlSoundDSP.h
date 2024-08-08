/*****************************************************************************
*
* File			: NtlSoundDSP.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 4. 3
* Abstract		: FMOD�� DSP(Disital Signal Processor)�� �����Ѵ�
*****************************************************************************
* Desc			: FMOD�� �ý���, ä�α׷�, ä�ο� ȿ���� �����ϱ� ���� Ŭ����
*				  ȿ���� ������ ��󿡰� �ߺ��ؼ� ���� ȿ���� ������ �� ������
*				  �Ҹ��� ���� ���ϰ� �� ȿ���� ���ڸ� �־� ������ �� �־�
*				  �ߺ��ؼ� ���� ȿ���� �������� ���ϵ��� �Ͽ���.
*				  �׷���, �ý���(������ �׷�), ä�α׷�, ä�ο� ���� ȿ����
*				  �־� �ߺ��ؼ� ȿ���� �� ���� ������ �������� �ʴ´�.
*
*				  ����) ���� ȿ���� �Ķ��Ÿ�� ������ ��� �ٸ���. �����
*				  ������ �Ķ��Ÿ ���� ����Ѵ�.
*****************************************************************************/

#pragma once

#include <map>

class CNtlSoundDSP
{
public:
	typedef std::map<RwUInt8, FMOD::DSP*>				MAP_DSP;
	typedef std::map<RwUInt8, FMOD::DSP*>::iterator		MAP_DSP_ITER;

	CNtlSoundDSP() {}
	~CNtlSoundDSP();

	VOID		Destroy();

	FMOD::DSP*	CreateDSP(FMOD_DSP_TYPE eType);
	VOID		ReleaseDSP(FMOD_DSP_TYPE eType);

	VOID		SetParameta(FMOD_DSP_TYPE eType, RwUInt8 byParametaType, RwReal fValue);
	RwReal		GetParameta(FMOD_DSP_TYPE eType, RwUInt8 byParametaType);

	RwBool		IsExistDSP(FMOD_DSP_TYPE eType);

protected:
	VOID		SetDetailParameta(FMOD_DSP_TYPE eType, FMOD::DSP* pDSP);

protected:
	MAP_DSP		m_mapDSP;
};