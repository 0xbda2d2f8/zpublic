// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


///> Function call with parameters that may be unsafe - this call relies
///> on the caller to check that the passed values are correct. To disable
///> this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how
///> to use Visual C++ 'Checked Iterators'
#pragma warning(disable:4996)

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <memory>
#include <map>
#include <queue>
#include <thread>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

///> Protocol Buffers
#include <google/protobuf/message.h>
#ifdef _DEBUG
#pragma comment(lib, "libprotobuf_d.lib")
#else
#pragma comment(lib, "libprotobuf.lib")
#endif
