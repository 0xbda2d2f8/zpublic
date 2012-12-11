/** 
* @file LTIOInterface.h
* @brief ����������������ӿ�
* @author BAO<baoderong@kingsoft.com>
* @date May-25-2010
*/

#ifndef LT_IO_INTERFACE_H
#define LT_IO_INTERFACE_H

/** 
* @class ILTInput
* @brief ��������·�鲢�㷨��ÿ·����ӿ�
*/
template <class LTItem>
class ILTInput
{
public:
	/** 
	* @brief ��ȡ��·���ݵĵ�һ����¼
	*
	* @param ��
	* @return �ɹ�����0��ʧ�ܷ���-1���յķ���1
	*/
	virtual int First() = 0;

	/** 
	* @brief ��ȡ��·���ݵ���һ����¼
	*
	* @param ��
	* @return �ɹ�����0��ʧ�ܷ���-1��û����һ����¼����1
	*/
	virtual int Next() = 0;

	/** 
	* @brief ��ȡ��·���ݵĵ�ǰ��¼
	*
	* @param ��
	* @return �ɹ�����0��ʧ�ܷ���-1
	*/
	virtual int CurrentItem(LTItem &stItem) const = 0;

	/** 
	* @brief �Ƚϱ�·���ݵĵ�ǰ��¼��piInput·�ĵ�ǰ��¼
	*
	* @param[in] ILTInput *piInput Ҫ�Ƚϵļ�¼�ľ��
	* @return ��ȷ���0������¼���ڷ���1������¼С�ڷ���-1
	*/
	virtual int Comp(ILTInput *piInput) const = 0;
};

/** 
* @class ILTInput
* @brief ��������·�鲢�㷨��ÿ·����ӿ�
*/
template <class LTItem>
class ILTOutput
{
public:
	/** 
	* @brief ����¼���
	*
	* @param[in] ILTInput *piInput Ҫ����ļ�¼�ľ��
	* @param[in] int nPos ��ǰ�����·����
	* @return ��ȷ���0������¼���ڷ���1������¼С�ڷ���-1
	*/
	virtual int Output(ILTInput<LTItem> *piInput, int nPos) = 0;
};

#endif
