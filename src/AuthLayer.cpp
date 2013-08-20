#include "AuthLayer.hpp"

AuthLayer::AuthLayer(const string& url)
{
    _baseURL = url;
    _delegate = nullptr;
}

void AuthLayer::authorize(){
    //if (_login == VALID_LOGIN && _password == )
}


