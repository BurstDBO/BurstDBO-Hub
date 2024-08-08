/*****************************************************************************
 * File			: ContractGui.h
 * Author		: Hong Sungbock
 * Copyright	: (��)NTL
 * Date			: 2009. 2. 26
 * Abstract		: DBO contract gui.
 *****************************************************************************
 * Desc         : ��� GUI�� �� �� �ִ� ��쿡 ���� ����
 *
 *				  1. �ڵ����� ���� �Ǵ� ���
 *					 - ���� PC���� �������� ó�� ������ ���
 *					 - ��� ������ ����
 *					 - DBO�� Ȯ������ ������ ���� PC���� �������� ó�� ������ ���
 *
 *				  2. DBO Title ȭ�鿡�� "���" ��ư�� ������ ���
 *
 *				  3. �ڵ����� ����� ���� �Ǵ� ��� "����"���� ������ ���� ����
 *****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// cleint
#include "SurfaceGui.h"

class CContractGui : public CNtlPLGui, public RWS::CEventHandler
{
public:

	CContractGui(const RwChar *pName);
	~CContractGui();

	RwBool		Create();
	VOID		Destroy();

protected:
	CContractGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			LocateComponent(RwInt32 iWidth, RwInt32 iHeight);

	VOID			OnClicked_AgreementButton(gui::CComponent* pComponent);
	VOID			OnClicked_OKButton(gui::CComponent* pComponent);
	VOID			OnClicked_CancelButton(gui::CComponent* pComponent);
		
	VOID			OnScrollChanged(RwInt32 iOffset);
	VOID			OnCaptureWheelMove(RwInt32 iFlag, RwInt16 sDelta, CPos& pos);
	VOID			OnPaint();

protected:
	gui::CSlot			m_slotAgreementButton;
	gui::CSlot			m_slotOKButton;
	gui::CSlot			m_slotCancelButton;	
	gui::CSlot			m_slotServerScrollChanged;
	gui::CSlot			m_slotServerScrollSliderMoved;
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotPaint;

	gui::CHtmlBox*		m_pContractHtml;

	gui::CStaticBox*	m_pPleaseRead;

	gui::CButton*		m_pAgreementButton;
	gui::CButton*		m_pOKButton;
	gui::CButton*		m_pCancelButton;

	CSurfaceGui			m_srfBackground;					///< ���� ���
};