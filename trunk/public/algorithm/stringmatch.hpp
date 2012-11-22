/*
 * stringmatch.hpp
 *
 *  Created on: 2012-11-13
 *      Author: kevin
 */

#ifndef STRINGMATCH_HPP__
#define STRINGMATCH_HPP__

#ifndef INVALID_PTR
#define INVALID_PTR 0
#endif

namespace zl
{

size_t SundayMatchString(const char* lpSource, size_t nSourceLen, const char* lpPattern, size_t nPatLen)
{
	size_t			nStep[256];
	size_t			nPos = 0;
	size_t			j;

	if(lpSource == INVALID_PTR || lpPattern == INVALID_PTR)
	{
		return -1;
	}


	if(nPatLen > nSourceLen)
	{
		return -1;
	}
	for(size_t i=0; i<256; i++)
	{
		nStep[i] = nPatLen + 1;
	}

	//����pattern����;
	for(size_t i=0; i<nPatLen; i++)
	{
		nStep[(unsigned char)lpPattern[i]] = nPatLen - i; 	
	}

	while(nPos < nSourceLen-nPatLen+1)
	{
		if(lpSource[nPos] != lpPattern[0])
		{
			//��һ��λ�ò���� �ȽϽ����ִ������һ���ַ�;
			if(nPos+nPatLen > nSourceLen)
				break;
			nPos +=  nStep[(unsigned char)lpSource[nPos+nPatLen]];

		}
		else
		{	
			for(j=1; j < nPatLen; j++)
			{
				if(*(lpSource+nPos+j) != *(lpPattern+j))
				{
					break;
				}
			}
			if(j == nPatLen)
			{
				return nPos;
			}

			nPos++;
		}
	}

	return -1;
}


}
#endif // STRINGMATCH_HPP__
