#include "stdafx.h"
#include "z_thread_pool.h"


z_thread_pool::z_thread_pool()
{

}

z_thread_pool::~z_thread_pool()
{

}

z_thread_pool::z_thread_pool(int thread_num)
{
    m_bIsExit = false;
    for(int i = 0; i < thread_num; i++)
    {
        z_thread* t = new z_thread(this);
        m_IdleThreadStack.push(t);
        t->start_thread();
    }
}

bool z_thread_pool::switch_active_thread( z_thread* t )
{
    if (!t)
    {
        return false;
    }
    z_task *pTask = m_TaskQueue.pop();
    if(pTask)
    {
        ///> ������в�Ϊ�գ�����ȡ����ִ�С�
        t->assign_task(pTask);
        t->start_task();
    }
    else
    {
        //�������Ϊ�գ����̹߳���
        t->suspend_thread();
        m_ActiveThreadList.remove_thread(t);
        m_IdleThreadStack.push(t);
    }
    return true;
}

bool z_thread_pool::addTask( z_task* t, z_thread_priority priority )
{
    if(!t || m_bIsExit)
        return false;

    //���ڿ����̡߳�ֱ�ӵ��ÿ����̴߳�������
    z_thread *pThread = m_IdleThreadStack.pop();
    if(pThread)
    {
        m_ActiveThreadList.add_thread(pThread);
        pThread->assign_task(t);
        pThread->start_task();	
    }
    else
    {
        if(priority == z_thread_priority_normal)
        {
            m_TaskQueue.push(t);
        }
        else if(priority == z_thread_priority_high)
        {
            m_TaskQueue.push_front(t);
        }
    }
    return true;
}

bool z_thread_pool::destroy()
{
    m_bIsExit = true;
    m_TaskQueue.clear();
    m_IdleThreadStack.clear();
    m_ActiveThreadList.clear();
    return true;
}

