#pragma once

enum emDbgSessionStatus
{
    emStatusSuccess                     = 0,    ///> �������ʵĳɹ�

    ///> �������1000��Ϊ����
    emStatusErrUnknow                   = 1001, ///> δ֪����
    emStatusErrSessionExist             = 1002, ///> �Ѿ��ڵ�����
    emStatusErrSessionNotExist          = 1003, ///> ���ԻỰ������
    emStatusErrCreateDbgProcessFailed   = 1004,
    emStatusErrKillDbgProcessFailed     = 1005,
    emStatusErrGetThreadContext         = 1006,
    emStatusErrSetThreadContext         = 1007,
    emStatusErrInvalidArg               = 1008,
    emStatusErrFileNotExist             = 1009,
};

enum emDbgSessionRunStatus
{
    emDbgSessionRunStatusNone           = 0,
    emDbgSessionRunStatusSuspended      = 1,
    emDbgSessionRunStatusInterrupted    = 2,
    emDbgSessionRunStatusRunning        = 3,
};

#define DBG_SUCCEEDED(status)   (((int)(hr)) >= 0 && ((int)(hr)) <= 1000)
#define DBG_FAILED(status)      (((int)(hr)) > 1000)

class CDbgSession
{
public:
    CDbgSession();
    ~CDbgSession();

    emDbgSessionStatus StartDebugSession(LPCTSTR path);
    emDbgSessionStatus ContinueDebugSession();
    emDbgSessionStatus StopDebugSeesion();
    void HandledException(BOOL handled);
    emDbgSessionStatus GetThreadContext(CONTEXT* pContext);
    emDbgSessionStatus SetThreadContext(const CONTEXT* pContext);
    emDbgSessionRunStatus GetRunStatus();
    BOOL ReadMemory(
        unsigned int address,
        unsigned int length,
        void* pData,
        SIZE_T& bytesRead);
    BOOL WriteMemory(
        unsigned int address,
        unsigned int length,
        const void* pData,
        SIZE_T& byteWriten);

private:
    BOOL OnProcessCreated(const CREATE_PROCESS_DEBUG_INFO* pInfo);
    BOOL OnThreadCreated(const CREATE_THREAD_DEBUG_INFO* pInfo);
    BOOL OnException(const EXCEPTION_DEBUG_INFO* pInfo);
    BOOL OnProcessExited(const EXIT_PROCESS_DEBUG_INFO* pInfo);
    BOOL OnThreadExited(const EXIT_THREAD_DEBUG_INFO* pInfo);
    BOOL OnOutputDebugString(const OUTPUT_DEBUG_STRING_INFO* pInfo);
    BOOL OnRipEvent(const RIP_INFO* pInfo);
    BOOL OnDllLoaded(const LOAD_DLL_DEBUG_INFO* pInfo);
    BOOL OnDllUnloaded(const UNLOAD_DLL_DEBUG_INFO* pInfo);

private:
    BOOL _DispatchDebugEvent(const DEBUG_EVENT* pDebugEvent);

private:
    emDbgSessionRunStatus       m_emRunStatus;
    HANDLE                      m_hProcess;
    HANDLE                      m_hThread;
    DWORD                       m_dwProccessId;
    DWORD                       m_dwThreadId;
    DWORD                       m_continueStatus;
};
