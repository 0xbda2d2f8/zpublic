#pragma once
#include "i_support.h"

///> ��������֧�֣��������ߡ�������
class CBaseSupport : public ISupport
{
public:
    CBaseSupport();
    ~CBaseSupport();

    virtual int Register( IClientOperate* iOper );
    virtual int Unregister( IClientOperate* iOper );

};
