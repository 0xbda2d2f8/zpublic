/********************************************************************
* @file      : log_queue.hpp
* @author    : zapline <zhuxianzhang@kingsoft.com>
* @date      : 2012/11/27 10:08
* @brief     : ��־���У��̰߳�ȫ����������д��־
* 
* 
*********************************************************************/

#ifndef _LOG_QUEQUE_HPP_
#define _LOG_QUEQUE_HPP_

#include "log_file.hpp"
#include "../../win/thread/event.hpp"
#include "../../win/thread/mutex.hpp"
#include "../../win/time/time_format.hpp"
#include "../../win/encode/string_encode.hpp"
#include <tchar.h>
#include <Strsafe.h>
#include <process.h>

namespace zl
{

    class CLogQueue
    {
    public:
        CLogQueue(const char* lpFileName, BOOL bTrunk = FALSE)
            : m_LogFile(lpFileName, bTrunk)
            , m_Semaphore(0, 0x7FFFFFFE)
            , m_ExitEvent(TRUE, FALSE)
        {
            BeginWorkerThread();
        }
        ~CLogQueue()
        {
            ExitAndWaitWorkerThread();
        }
    public:
        void AddLog(const wchar_t* lpFormat, ...)
        {
            const int nBufLen = MAX_PATH * 2;
            wchar_t szBuf[nBufLen + 1] = {0};
            va_list ap;
            va_start(ap, lpFormat);
            StringCchVPrintfW(szBuf, nBufLen, lpFormat, ap);
            va_end(ap);
            OutputDebugStringW(szBuf);

            std::wstring sLine = GetTimeHeader();
            sLine.append(szBuf);
            AddMsgToList(WideToUTF8(sLine));
        }
        void AddLog(const char* lpFormat, ...)
        {
            const int nBufLen = MAX_PATH * 2;
            char szBuf[nBufLen + 1] = {0};
            va_list ap;
            va_start(ap, lpFormat);
            StringCchVPrintfA(szBuf, nBufLen, lpFormat, ap);
            va_end(ap);
            OutputDebugStringA(szBuf);

            std::wstring sTime = GetTimeHeader();
            std::string sLine = WideToUTF8(sTime);
            sLine.append(szBuf);
            AddMsgToList(sLine);
        }

    private:
        std::wstring GetTimeHeader()
        {
            SYSTEMTIME st = {0};
            ::GetSystemTime(&st);
            wchar_t sTime[TIME_STRING_MAX_LEN] = {0};
            Time2Str(st, sTime);
            std::wstring sOut(L"[");
            sOut.append(sTime);
            sOut.append(L"]");
            return sOut;
        }
        void AddMsgToList(std::string& strMsg)
        {

            CMutexGuard guard(m_QueueMutex);
            m_ltMsg.push_back(strMsg);
            m_Semaphore.Release();
        }

        BOOL PopMsgFromList(std::string& strMsg)
        {
            CMutexGuard guard(m_QueueMutex);
            if (m_ltMsg.empty())
            {
                strMsg = "[Null]";
                return FALSE;
            }
            else
            {
                strMsg = m_ltMsg.front();
                m_ltMsg.pop_front();
                return TRUE;
            }
        }

        BOOL BeginWorkerThread()
        {
            BOOL bResult = FALSE;
            if (m_hRecordRoutine == NULL)
            {
                m_hRecordRoutine = (HANDLE)_beginthreadex(
                    NULL, 0, RecordRoutine, (void*)this, 0, NULL);
            }
            return m_hRecordRoutine != NULL;
        }

        BOOL ExitAndWaitWorkerThread()
        {
            m_ExitEvent.Set();
            if (m_hRecordRoutine)
            {
                if (WAIT_TIMEOUT == ::WaitForSingleObject(m_hRecordRoutine, 100))
                {
                    ::TerminateThread(m_hRecordRoutine, 0);
                }

                ::CloseHandle(m_hRecordRoutine);
                m_hRecordRoutine = NULL;
            }
            return TRUE;
        }

//////////////////////////////////////////////////////////////////////////

        UINT static __stdcall RecordRoutine(LPVOID lpPrarm)
        {
            DWORD dwWait = 0;
            CLogQueue* pThis = (CLogQueue*)lpPrarm;
            if (pThis == NULL) { goto clean0; }

            try
            {
                while(TRUE)
                {
                    dwWait = pThis->m_ExitEvent.Wait2(pThis->m_Semaphore);
                    switch (dwWait)
                    {
                    case WAIT_OBJECT_0:
                        pThis->DoPorcMsg();
                        break;

                    case WAIT_OBJECT_0 + 1:
                        goto clean0;

                    case WAIT_TIMEOUT:
                        continue;

                    default:
                        goto clean0;
                    }
                }
            }
            catch (...){ }

clean0:
            _endthreadex(0);
            return 0;
        }

        void DoPorcMsg()
        {
            std::string strLine;
            BOOL bRet = PopMsgFromList(strLine);

            if (bRet)
            {
                m_LogFile.WriteLine(strLine.c_str(), strLine.size() - 1);
            }
        }

    private:
        CLogFile m_LogFile;
        HANDLE m_hRecordRoutine;
        std::list<std::string> m_ltMsg;

        ///> ��־���з��ʻ�����
        CMutex          m_QueueMutex;
        ///> ֹͣ��־�̵߳��ź���
        CEvent          m_ExitEvent;
        ///> �����־���ź���
        CSemaphore      m_Semaphore;

    };

}

#endif