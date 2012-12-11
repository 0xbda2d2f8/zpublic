/** 
* @file LoserTree.h
* @brief ��������·�鲢�㷨�ඨ��
* @author BAO<baoderong@kingsoft.com>
* @date May-25-2010
*
* @reference ����ο����������Ͽ�����еİ������㷨
*/

#ifndef LOSERTREE_H
#define LOSERTREE_H

#include <vector>

#include "LTIOInterface.h"

#define SWAP2INT( a, b )	\
	do						\
{							\
	a = a + b;				\
	b = a - b;				\
	a = a - b;				\
} while(0);

/** 
* @class CTreeOfLoser
* @brief ��������·�鲢�㷨��
*/
template <class LTItem>
class CTreeOfLoser
{
	typedef enum tagKeyStatus
	{
		enumKey_Status_Max = 1,
		enumKey_Status_Nor = 0,
		enumKey_Status_Min = -1
	}KEY_STATUS; 

public:
	/** 
	* @brief ���캯��
	*
	* @param ��
	* @return ��
	*/
	CTreeOfLoser(void)
	{
		m_dwNum = 0;
		m_piOut = NULL;
		m_pnTree = NULL;
	}

	/** 
	* @brief ��������
	*
	* @param ��
	* @return ��
	*/
	~CTreeOfLoser(void)
	{
		clear();
	}


	/** 
	* @brief ��һ·Ҫ�鲢�ļ�¼����������
	*
	* @param[in] ILTInput<LTItem> *pIter Ҫ�鲢�ļ�¼
	* @return �ɹ�����0��ʧ�ܷ���-1��û�м�¼����1
	*
	* @remarks ���ýӿ���ָ����ļ������κμ�¼ʱ�����ļ�������������������
	*/
	int AddInput(
		ILTInput<LTItem> *pIter)
	{
		int nResult = -1;
		int nRetCode = -1;

		if (NULL == pIter)
		{
			goto Exit0;
		}

		m_dwNum ++;
		nRetCode = pIter->First();

		if (1 == nRetCode)
		{
			nResult = 1;
			goto Exit0;
		}
		else if (-1 == nRetCode)
		{
			goto Exit0;
		}
		else
		{

		}

		m_vecipInput.push_back(pIter);

		nResult = 0;

Exit0:
		return nResult;
	}

	/** 
	* @brief ���鲢����ӿڵļ�¼����������
	*
	* @param[in] ILTInput<LTItem> *pIter Ҫ�鲢�ļ�¼
	* @return ����0
	*
	* @remarks ����ָ��ΪNULLʱ�������������
	*/
	int SetOutput(
		ILTOutput<LTItem>* piOut = NULL)
	{
		m_piOut = piOut;
		m_vecStat.resize(m_dwNum + 1);

		for (int i = 0; i < (int)m_dwNum; i ++)
		{
			m_vecStat[i] = enumKey_Status_Nor;
		}

		m_vecStat[m_dwNum] = enumKey_Status_Min;
		return 0;
	}

	/** 
	* @brief ��ȡ��ǰҪ�鲢��·��
	*
	* @param ��
	* @return �鲢��·��
	*/
	virtual DWORD GetNumber()
	{
		return (DWORD)m_vecipInput.size();
	}

	/** 
	* @brief ��dwIndex·��¼�Ƿ�Ϊ���ֵ
	* @details ����·��¼ȫ���鲢�꣬û�м�¼ʱ���õ�ֵΪ���ֵ
	*
	* @param[in] const DWORD dwIndex ��¼·��
	* @return �鲢��·��
	*/
	virtual bool IsMax(
		const DWORD dwIndex)
	{
		if (dwIndex >= m_vecStat.size() 
			|| m_vecStat[dwIndex] != enumKey_Status_Max)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	/** 
	* @brief ��ȡdwIndex����һ����¼
	* @details ����ö����Ѿ������ϣ���ô�����м�¼Ϊ���ֵ
	*
	* @param[in] const DWORD dwIndex ��¼·��
	* @return �鲢��·��
	*/
	virtual int InputOneItem(
		const DWORD dwIndex)
	{
		int	nResult = -1;
		int nRetCode = -1;

		ILTInput<LTItem> *IterData = m_vecipInput[dwIndex];

		if (!IterData)
		{
			goto Exit0;
		}

		if (enumKey_Status_Max == m_vecStat[dwIndex])
		{
			goto Exit1;
		}

		nRetCode = IterData->Next();

		if (1 == nRetCode)
		{
			m_vecStat[dwIndex] = enumKey_Status_Max;
		}
		else if (-1 == nRetCode)
		{
			goto Exit0;
		}
		else
		{
			m_vecStat[dwIndex] = enumKey_Status_Nor;
		}

Exit1:
		nResult = 0;
Exit0:
		return nResult;
	}

	/** 
	* @brief ��dwIndex�ĵ�ǰ��¼���
	*
	* @param[in] const DWORD dwIndex ��¼·��
	* @return �鲢��·��
	*/
	virtual int OutputOneItem(
		const DWORD dwIndex)
	{
		int nResult = -1;

		//m_vecSortedArray.push_back(dwIndex);

		if (m_piOut)
		{
			m_piOut->Output(m_vecipInput[dwIndex], dwIndex);
		}

		nResult = 0;
		return nResult;
	}

	/** 
	* @brief ��dwIndex�ĵ�ǰ��¼���
	* @details ���dwIndex >= m_dwNumber ��ô���϶�����С��
	*
	* @param[in] const DWORD dwIndexA Ҫ�Ƚϵ�·��A
	* @param[in] const DWORD dwIndexB Ҫ�Ƚϵ�·��B
	* @param[out] int *nResult �ȽϽ������ȷ���0��A>B����1,A<B����-1
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	virtual int	Compare(
		const DWORD dwIndexA,
		const DWORD dwIndexB,
		int *nResult)
	{
		int nFuResult = -1;
		int nRetCod = -1;

		if (NULL == nResult)
		{
			goto Exit0;
		}

		*nResult = 0;

		if (enumKey_Status_Nor == m_vecStat[dwIndexA] 
		&& enumKey_Status_Nor == m_vecStat[dwIndexB])
		{
			nRetCod = (m_vecipInput[dwIndexA])->Comp(m_vecipInput[dwIndexB]);
		}
		else
		{
			nRetCod = m_vecStat[dwIndexA] - m_vecStat[dwIndexB];
		}

		*nResult = nRetCod;

		nFuResult = 0;
Exit0:
		return nFuResult;	
	}
	
	/** 
	* @brief ������л�������
	*
	* @param ��
	* @return ��
	*/
	void clear()
	{
		m_dwNum = 0;
		m_piOut = NULL;
		m_vecSortedArray.clear();
		m_vecStat.clear();
		m_vecipInput.clear();

		if (m_pnTree)
		{
			delete [] m_pnTree;
			m_pnTree = NULL;
		}
	}

	/** 
	* @brief ������һ����¼�����¹���ð�����
	*
	* @param[in] DWORD dwIndex Ҫ���¼�¼��·��
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	int Adjust(
		DWORD dwIndex)
	{
		int nResult = -1;
		int nRetCode = 0;

		int nParentIndex = (m_dwNum + dwIndex) / 2;

		while (nParentIndex > 0)
		{
			nResult = Compare(dwIndex, m_pnTree[nParentIndex], &nRetCode);

			if (nResult)
			{
				goto Exit0;
			}

			if (nRetCode > 0)
			{
				SWAP2INT(dwIndex, m_pnTree[nParentIndex]);
			}

			nParentIndex = nParentIndex / 2;
		}

		m_pnTree[0] = dwIndex;

		nResult = 0;
Exit0:
		return nResult;
	}

	/** 
	* @brief �ð�������·�鲢�㷨����������
	*
	* @param ��
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	int Make()
	{
		int nResult = -1;
		int nRetcode = -1;

		DWORD dwIndex = 0;

		if (m_pnTree)
		{
			delete []m_pnTree;
			m_pnTree = NULL;
		}

		m_pnTree = new int[m_dwNum];

		if (NULL == m_pnTree)
		{
			goto Exit0;
		}

		/// ����������
		for (int i = 0; i < (int)m_dwNum; ++i)
		{
			m_pnTree[i] = m_dwNum;
		}

		for(int i = m_dwNum - 1; i >= 0; --i)
		{
			nRetcode = Adjust(i);

			if (nRetcode)
			{
				goto Exit0;
			}
		}

		/// �ð���������
		while ( !IsMax(m_pnTree[0]) )
		{
			dwIndex = m_pnTree[0];
			nRetcode = OutputOneItem(dwIndex);

			if (nRetcode)
			{
				goto Exit0;
			}

			nRetcode = InputOneItem(dwIndex);

			if (nRetcode)
			{
				goto Exit0;
			}

			nRetcode = Adjust(dwIndex);

			if (nRetcode)
			{
				goto Exit0;
			}
		}

		if (nRetcode)
		{
			goto Exit0;
		}

		nResult = 0;

Exit0:
		return nResult;
	}

private:
	DWORD m_dwNum;
	int *m_pnTree;
	ILTOutput<LTItem> *m_piOut;

	std::vector<int> m_vecSortedArray;

	std::vector<KEY_STATUS>	m_vecStat;
	std::vector<ILTInput<LTItem> *> m_vecipInput;	
};

#endif

