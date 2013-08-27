#ifndef AUTHLAYER_HPP
#define AUTHLAYER_HPP

#include <string>
#include "IAuthLayerDelegate.hpp"

using namespace std;
class AuthLayer
{
public:
    AuthLayer(const string& url);
    string getServerURL() const {return _baseURL;}
    virtual void setLogin(const string& login){_login = login;}
    virtual void setPassword(const string& password){_password = password;}
    virtual void authorize();
    virtual bool isAuthorized(){return _isAuthorized;}
    virtual void setDelegate(IAuthLayerDelegate* delegate){_delegate = delegate;}
    virtual ~AuthLayer(){_delegate = NULL;}
protected:
    AuthLayer(){}
private:
    string _baseURL;
    string _login;
    string _password;
    bool _isAuthorized;
    IAuthLayerDelegate *_delegate;
};

#endif // AUTHLAYER_HPP
