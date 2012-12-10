/***************************************************************
 * @date:   2007-12-04
 * @author: BrucePeng
 * @brief:  Define function that delete all files in a folder
 */
#ifndef DIRECTORY_DELETE_H_
#define DIRECTORY_DELETE_H_

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ɾ��ָ��Ŀ¼�е��ļ�
 *
 * @param[IN]   pszDirName  Ŀ¼����(·��)
 * @param[IN]   pszSpecific The specific name
 * @param[IN]   bDeleteSelf �Ƿ�ɾ��Ŀ¼�ļ�������
 *
 * @note
 * �˺�����֧�ֵڹ�ɾ����������ɾ����Ŀ¼�ļ����е��ļ�
 *
 * @return �Ƿ�ɹ�
 * -TRUE    �ɹ�
 *  FALSE   ʧ��
 */
BOOL BrucePengDeleteDirectory(
    IN  TCHAR*  pszDirName, 
    IN  TCHAR*  pszSpecific,
    IN  BOOL    bDeleteSelf
);

#ifdef __cplusplus
}
#endif

#endif//DIRECTORY_DELETE_H_
