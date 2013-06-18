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

///> ���ļ����������ڵ�ǰ����ҳ(936)�б�ʾ���ַ���
///> �뽫���ļ�����Ϊ Unicode ��ʽ�Է�ֹ���ݶ�ʧ
#pragma warning(disable:4819)

///> zpublic��
#include "zpublic.hpp"

///> ��׼����
#include <array>
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

///> Format
///> The format library provides a class for formatting arguments 
///> according to a format-string, as does printf, but with two major 
///> differences: format sends the arguments to an internal stream, and so
///> is entirely type-safe and naturally supports all user-defined types; 
///> the ellipsis (...) can not be used correctly in the strongly typed 
///> context of format, and thus the function call with arbitrary arguments
///> is replaced by successive calls to an argument feeding operator%.
#include <boost/format.hpp>

///> Tokenizer
///> Break of a string or other character sequence into a series of tokens.
#include <boost/tokenizer.hpp>

///> Bimap
///> Bidirectional maps library for C++. With Boost.Bimap you can create
///> associative containers in which both types can be used as key.
#include <boost/bimap.hpp>
