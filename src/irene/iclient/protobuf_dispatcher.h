#pragma once
#include "i_client_operate.h"

///> �ο���˶�����£�һ���Զ�������Ϣ���͵� Google Protobuf ���紫�䷽��
///> http://www.cnblogs.com/Solstice/archive/2011/04/03/2004458.html


/*
class Callback : boost::noncopyable
{
public:
    virtual ~Callback() {};
    virtual void onMessage(google::protobuf::Message* message) const = 0;
};


template <typename T>
class CallbackT : public Callback
{
public:
    CallbackT(const MessageCallback& callback)
        : callback_(callback)
    {
    }

    virtual void onMessage(google::protobuf::Message* message) const
    {
        T* t = dynamic_cast<T*>(message);
        assert(t != NULL);
        callback_(t);
    }

private:
    MessageCallback callback_;
};
*/

class ProtobufDispatcher : private boost::noncopyable
{
public:
    ProtobufDispatcher();

    void onMessage(google::protobuf::Message* message) const;

    /* Ϊ�˿�ģ�飬�����Զ��Ƶ��ķ�ʽ�����뱣��
    typedef std::map<const google::protobuf::Descriptor*, std::shared_ptr<Callback> > CallbackMap;
    template<typename T>
    void registerMessageCallback(
        const typename CallbackT<T>::ProtobufMessageCallback& callback)
    {
        std::shared_ptr<CallbackT<T> > pd(new CallbackT<T>(callback));
        callbacks_[T::descriptor()] = pd;
    }
    */

    typedef std::map<const google::protobuf::Descriptor*, MessageCallback> CallbackMap;
    void registerMessageCallback(
        const google::protobuf::Descriptor* desc,
        const MessageCallback& callback)
    {
        callbacks_[desc] = callback;
    }
    void unregisterMessageCallback(
        const google::protobuf::Descriptor* desc)
    {
        callbacks_.erase(desc);
    }

    CallbackMap callbacks_;
    boost::function<void (google::protobuf::Message* message)> defaultCallback_;
};
