///////////////////////////////////////////////////////////////
//
//	Filename: 	KFileVersion.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//  Date:       2007-1-17  19:54
//	Comment:	��ȡexe��dll�ļ��汾��Ϣ
//
///////////////////////////////////////////////////////////////


#ifndef _KFILEVERSION_H_
#define _KFILEVERSION_H_



class KFileVersion  
{
public:
	KFileVersion();
	~KFileVersion();

	/**
	* @brief   ָ��Ҫ��ȡ�ĸ��ļ��İ汾��Ϣ
	* @param   [in]  pszFileName,    �ļ���, �����Ǵ���Դ��Ϣ���ļ�, ��exe��dll
	* @return  ����ɹ�����TRUE, ���򷵻�FALSE
	*/
	BOOL SetFile( LPCTSTR pszFileName );


	/**
	* @brief   ��ȡ����İ汾��Ϣ
	* @param   [in]   pszInfoType,   �汾��Ϣ����, ������ȡֵ
	* @param   [out]  strInfo,       �汾��Ϣ
	* @return  ����ɹ�����TRUE, ʧ�ܷ���FALSE
	*/
	BOOL  GetVersionInfo( LPCTSTR pszInfoType, CString& strInfo );


private:
	LPVOID	m_lpBuffer;
	LPVOID	m_lpData;
	UINT	m_uDataSize;

	CString m_strLangInfo;

private:
	struct TRANSLATION 
	{ 
		WORD wLangID;    // language ID 
		WORD wCodePage;  // code page 
	};

};


#endif // _KFILEVERSION_H_
