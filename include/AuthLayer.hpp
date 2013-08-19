#ifndef AUTHLAYER_HPP
#define AUTHLAYER_HPP

#include <string>

using namespace std;
class AuthLayer
{
public:
    AuthLayer(const string& url);
    string getServerURL() const {return _baseURL;}
protected:
    AuthLayer(){}
private:
    string _baseURL;
};

#endif // AUTHLAYER_HPP
