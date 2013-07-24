#pragma once
#include "i_support.h"
#include "..\common\protocol\s2c_auth.pb.h"

///> ��������֧�֣��������ߡ�������
class CBaseSupport : public ISupport
{
public:
    CBaseSupport();
    ~CBaseSupport();

    virtual int Register( IClientOperate* iOper );
    virtual int Unregister( IClientOperate* iOper );

    void onAuth(google::protobuf::Message* message);
};
