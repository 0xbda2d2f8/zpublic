/********************************************************************
* CreatedOn: 2007-1-22   21:49
* FileName: CreateDirectoryTree.cpp
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#include <windows.h>
#include <tchar.h>
#include "CreateDirectoryTree.h"
int CreateDirectoryTree(TCHAR* pszDirPath, size_t size)
{
	size_t sizeLen = _tcslen(pszDirPath);
	if (sizeLen > size)
		return -1;

	int nRetCode		= 0;
	DWORD dwAttrs		= INVALID_FILE_ATTRIBUTES;
	TCHAR* pPos			= NULL;
	size_t sizeFillZero = 0;
	pPos = &(pszDirPath[sizeLen - 1]);//�����һ���ַ���ʼ

	//�Ȱ�·��ĩβ��'\\'��ȥ��
	while (pPos != pszDirPath && TEXT('\\') == *pPos)
	{
		*pPos = 0;
		--sizeLen;
		--pPos;
		++sizeFillZero;
	}

	if (pPos == pszDirPath && TEXT('\\') == *pPos)
	{
		nRetCode = -1;//·��ȫΪ'\\'����,��Ч·����
	}
	else
	{
		dwAttrs = ::GetFileAttributes(pszDirPath);
		if (INVALID_FILE_ATTRIBUTES == dwAttrs)//��ǰĿ¼������
		{
			//Ѱ�����һ������������\\'�ŵ�λ��
			//������:ǰһ���ַ���Ϊ'\\'��
			while (pPos != pszDirPath 
				&& (*pPos != TEXT('\\') || TEXT('\\') == *(pPos - 1)))
			{
				--pPos;
			}

			if (*pPos != TEXT('\\'))
			{
				pPos = NULL;//û���ҵ�
			}

			if (pPos != NULL)
			{
				*pPos = 0;//���ҵ���'\\'�Ÿ�Ϊ�ս����,�����͵õ��ϼ�Ŀ¼��·��
				//�ݹ鴴���ϼ�Ŀ¼��
				nRetCode = CreateDirectoryTree(pszDirPath, (pPos - pszDirPath + 1));
				*pPos = TEXT('\\');//��ԭ���һ��'\\'��			
			}

			//����ϼ�Ŀ¼�����ɹ���û���ϼ�Ŀ¼,��ô������ǰĿ¼
			if (0 == nRetCode)
			{
				if (!::CreateDirectory(pszDirPath, NULL))
				{
					if (::GetLastError() != ERROR_ALREADY_EXISTS)
						nRetCode = -1;//�����ļ���ʧ��
				}
			}
		}
		else if (!(dwAttrs & FILE_ATTRIBUTE_DIRECTORY))
		{
			nRetCode = -1;//ָ����·�����ڵ�����һ���ļ���
		}
		//else��ǰĿ¼����,ֱ�ӷ��سɹ�
		//{}
	}

	//���ԭ����ȥ��·��ĩβ��'\\'��,��ô��ԭ��ȥ
	if (sizeFillZero != 0)
	{
		pPos = &(pszDirPath[sizeLen]);
		for (; sizeFillZero != 0; --sizeFillZero, ++pPos)
		{
			*pPos = TEXT('\\');
		}
	}
	return nRetCode;
}