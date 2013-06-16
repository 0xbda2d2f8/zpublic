#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <assert.h>

///> Function call with parameters that may be unsafe - this call relies
///> on the caller to check that the passed values are correct. To disable
///> this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how
///> to use Visual C++ 'Checked Iterators'
#pragma warning(disable:4996)

///> zpublic��
#include "zpublic.hpp"

///> ��׼����
#include <string>
#include <vector>
#include <map>
#include <list>
using std::string;

///> ����������
#include <iomanip>
#include <iostream>
using std::cout;
using std::endl;

///> ����ָ��
#include <memory>

///> ������ʽ
#include <regex>

///> ԭ�Ӳ���
#include <atomic>

///> ʱ��
#include <chrono>
#include <ratio>
#include <ctime>

///> λ����
#include <bitset>

///> Conversion
///> Polymorphic and lexical casts.
#include <boost/cast.hpp>
#include <boost/lexical_cast.hpp>

///> String Algo
///> String algorithms library.
#include <boost/algorithm/string.hpp>
