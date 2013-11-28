#pragma once
#include <string>

class CPropertyTree
{
public:
    CPropertyTree();
    ~CPropertyTree();

public:
    ///> �����Ƿ��ȡ�ɹ�
    bool get(const std::wstring& key, std::wstring& value);
    ///> �����Ƿ��Ѵ���
    bool set(const std::wstring& key, const std::wstring& value, bool cover = true);
};