#include "AuthLayer.hpp"
#include "configuration.hpp"

AuthLayer::AuthLayer(const string& url)
{
    _baseURL = url;
    _delegate = nullptr;
}

void AuthLayer::authorize(){
    _isAuthorized =  (_login == VALID_LOGIN && _password == VALID_PASSWORD);
    if ( _isAuthorized && _delegate != nullptr )
    {
         _delegate->onAuthorizationSuccessful();
    }else{
        _delegate->onAuthorizationFailed();
    }
}


