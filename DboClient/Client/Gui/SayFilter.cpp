#include "precomp_dboclient.h"
#include "SayFilter.h"

// core
#include "NtlDebug.h"
#include "NtlClientService.h"

// shared
#include "TableContainer.h"
#include "ChattingFilterTable.h"
#include "TextAllTable.h"

// simulation
#include "NtlSLApi.h"
#include "NtlService.h"


CFilterManager::CFilterManager() 
: m_bIsEmpty( TRUE )
{
	InitOnce();
}

CFilterManager::~CFilterManager()
{
	Destroy();
}

void CFilterManager::InitOnce() 
{
	m_defaultReplace = L"--";

	m_pFilterWord = NTL_NEW CWFILTERWORD;
}

void CFilterManager::Destroy() 
{
	if( m_pFilterWord )
		NTL_DELETE(m_pFilterWord);
}

void CFilterManager::Create(void) 
{
	// TODO : ���̺��� �����͸� �о�鿩�� �߰��� ����.
	// ���͸� �ܾ� ���̺� �߰�
	CChattingFilterTable* pFilterTable = API_GetTableContainer()->GetChattingFilterTable();
	
	// ���̺��� ��� ������ ������ �ǰ� �ؾ� �Ѵ�.
	DBO_ASSERT( pFilterTable, "CFilterManager: filter table pointer is NULL");
	if( NULL == pFilterTable )
		return;

	sCHAT_FILTER_TBLDAT* pFilter = NULL;

	for(CChattingFilterTable::TABLEIT it = pFilterTable->Begin(); it != pFilterTable->End(); it++)
	{
		pFilter = (sCHAT_FILTER_TBLDAT*)it->second;
		AddFilter( pFilter->tblidx, pFilter->wszSlangText, pFilter->filteringTextIndex );
	}

	// �ܾ 1�� �̻� ��ϵǾ� ������ ���̺��� ��� �ִ°��� �ƴϴٶ�� �Ǵ��Ѵ�.
	if( m_pFilterWord->GetNumFilter() > 0 )
		m_bIsEmpty = FALSE;
}

void CFilterManager::AddFilter(int nIndex, wchar_t* pText, int nLink)
{
	m_pFilterWord->AddText( nIndex, pText, lstrlenW( pText ), nLink );
}

/**
* \brief UNICODE ���ڿ� ���͸� �Լ�
*
* UNICODE ���ڿ��� �弳�� ġȯ�Ͽ� �����Ѵ�.
*
* \param pText (std::wstring&)���͸��� wstring
* \return (std::wstring)���͸��� wstring
*/
std::wstring CFilterManager::Filtering(std::wstring& pText)
{
	// ���̺��� �ε� �ȵǾ� �ִٸ� �׳� �����ع�����.
	if( m_bIsEmpty )
	{
		DBO_FAIL( "CFilterManager:: Filter word is empty.");
		return pText;
	}

	// ���� ���ڿ��� �����ؼ� ���͸��� ���� ���͸��� ���ڿ��� �����Ѵ�.
	std::wstring		strText = pText;

	// vecResult ����ü�� ���͸��� �ܾ���� ��ġ�� �������� ä���ִ´�.
	std::vector<CWFILTERWORD::SResult> vecResult;
	m_pFilterWord->FindText(strText.c_str(), (int)strText.length(), vecResult);

	// ���̺��� �̸� ������ �ִ´�.
	CTextTable* pReplaceTable = API_GetTableContainer()->GetTextAllTable()->GetFilteringTable();
	
	// ���̺��� �ε����� ���ߴٸ� �ܾ �ٲ��� �ʰ� �����Ѵ�.
	DBO_ASSERT( pReplaceTable , "CFilterManager: Replace table pointer is NULL");
	if( NULL == pReplaceTable )
		return strText;
		
	// vecResult�� ���� ����� �������� ġȯ�� �����Ѵ�.
	// �̰��� ���ڿ��� �տ��� ġȯ���� ��� ���ڿ��� ���� ���̰� �ٲ�� ��츦 ����Ѵ�.
	for (int i = (int)vecResult.size() - 1; i >= 0; --i)
	{
		CWFILTERWORD::SResult& resultRef = vecResult.at(i);

		// ���͸��� �ܾ ġȯ�Ѵ�. strText.erase( StartPos, Offset );
		strText.erase(resultRef.uPosStart, resultRef.uPosEnd-resultRef.uPosStart+1);
		

		// ���� ġȯ�� �ܾ��� �ε����� ���ٸ� �⺻���� �����Ǿ� �ִ� �ܾ�� �������ش�.
		sTEXT_TBLDAT* pReplace = (sTEXT_TBLDAT*)pReplaceTable->FindData(resultRef.nLink);

		if( NULL == pReplace )
			strText.insert(resultRef.uPosStart, m_defaultReplace.c_str() );
		else
			strText.insert(resultRef.uPosStart, pReplace->wstrText.c_str() );
		
	}

	return strText;
}

/**
* \brief MULTIBYTE ���ڿ� ���͸� �Լ�
*
* MULTIBYTE ���ڿ��� UNICODE�� ��ȯ�� �� std::wstring CWSayFilterManager::Filtering( std::wstring& pText );
* �� ȣ���Ͽ� ���͸� �ϰ� �ٽ� MULTIBYTE�� ��ȯ�� �� �����Ѵ�. (ATL ��ũ�� ���)
*
* \param pText (std::string&)���͸��� string
* \return (std::string)���͸��� string
*/
std::string CFilterManager::Filtering(std::string& pText)
{
	// MULTIBYTE�� UNICODE�� ��ȯ�ؼ� Filtering�� ������ ��
	// �ٽ� MULTIBYTE�� ��ȯ�ؼ� �����Ѵ�.
	// WinAPI�� �ٲ����.
	
	WCHAR awcBuffer[64] = L" ";
	::MultiByteToWideChar( GetACP(), 0, pText.c_str(), -1, awcBuffer, 64 );
	
	std::wstring wstrResult = Filtering( awcBuffer );
	
	CHAR acBuffer[64]= " ";
	::WideCharToMultiByte( GetACP(), 0, wstrResult.c_str(), -1, acBuffer, 64, NULL, NULL );
	std::string strResult = acBuffer;

	return strResult;
}

/**
* \brief UNICODE ���ڿ� ���͸� �Լ�
*
* \param pText (wchar_t*)���͸��� UNICODE ���ڿ� ������
* \return (std::wstring)���͸��� wstring
*/
std::wstring CFilterManager::Filtering(const wchar_t* pText)
{
	std::wstring strText = pText;

	return Filtering( strText );
}

/**
* \brief UNICODE ���ڿ� �弳 üũ �Լ�
*
* \param pText (std::wstring)üũ�� ���ڿ�
* \return (BOOL)�弳�̶�� TRUE, �ƴ϶�� FALSE�� ����
*/
RwBool CFilterManager::IsSlang(std::wstring& pText )
{
	// ���̺��� �ε� �ȵǾ� �ִٸ� �׳� �����ع�����.
	if( m_bIsEmpty )
	{
		DBO_FAIL("CFilterManager: Filterword is empty.");
		return FALSE;
	}

	std::wstring strText = pText;

	std::vector<CWFILTERWORD::SResult> vecResult;
	m_pFilterWord->FindText(strText.c_str(), (int)strText.length(), vecResult);

	// ���� �ܾ �ϳ��� �˻��Ǹ� �� ���ڿ��� �弳�� �ȴ�.
	if( vecResult.size() > 0 )
		return TRUE;

	return FALSE;
}

RwBool CFilterManager::IsSlang(std::string& pText)
{
	WCHAR awcBuffer[64] = L" ";
	::MultiByteToWideChar( GetACP(), 0, pText.c_str(), -1, awcBuffer, 64 );


	std::wstring buf = awcBuffer;

	return IsSlang( buf );
}

RwBool CFilterManager::IsSlang( const wchar_t* pText )
{
	std::wstring buf = pText;

	return IsSlang( buf );
}

RwBool CFilterManager::IsAnyInvalidText( const WCHAR* pText )
{
	std::wstring buf = pText;

	if( IsSlang( buf ) )
		return TRUE;

	eDBO_SERVICE_PUBLISHER eService = GetServiceInterface()->GetPublisherID();
	if( Dbo_AnyInvalidCharacterInName( (BYTE)eService, const_cast<WCHAR*>(pText), wcslen( pText ) ) )
		return TRUE;

	return FALSE;
}