#pragma once


///> �������
class DecoratorComponent
{
public:
    virtual ~DecoratorComponent()
    {

    }

    virtual void Operation(void* lpData = 0) = 0;
};

///> �������
class ConcreteComponent : public DecoratorComponent
{
public:
    virtual ~ConcreteComponent()
    {

    }
};

///> װ�����
class Decorator : public DecoratorComponent
{
public:
    Decorator(DecoratorComponent* pComponent = 0) : m_pComponent(pComponent)
    {

    }
    virtual ~Decorator()
    {

    }

    void Decorate(DecoratorComponent* pComponent)
    {
        m_pComponent = pComponent;
    }

protected:
    DecoratorComponent* m_pComponent;
};
