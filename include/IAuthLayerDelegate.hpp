#ifndef IAUTHLAYERDELEGATE_HPP
#define IAUTHLAYERDELEGATE_HPP

class IAuthLayerDelegate
{
public:
    IAuthLayerDelegate(){}
    virtual void onAuthorizationSuccessful() = 0;
    virtual void onAuthorizationFailed() = 0;
    ~IAuthLayerDelegate(){}
};

#endif // IAUTHLAYERDELEGATE_HPP
