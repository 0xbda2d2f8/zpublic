/********************************************************************
* CreatedOn: 2007-12-3   14:36
* FileName: CreateDirectoryTree.h
* CreatedBy: qiuruifeng <qiuruifeng@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/
#ifndef CREATEDIRECTORYTREE_H
#define CREATEDIRECTORYTREE_H

/**
 * @brief �ݹ鴴��Ŀ¼��,Ϊ���Ż�Ч��,ʹ�ô���Ĳ�����������,
 * @remark ���Դ����ڲ����ظ�б����·����"C:\\a\\\\b\\\\"
 * @param pszDirPath Ŀ¼·��������
 * @param size ��������С
 * @return �ɹ�����0,ʧ�ܷ��ظ���
 */
int CreateDirectoryTree(TCHAR* pszDirPath, size_t size);


#endif //CREATEDIRECTORYTREE_H