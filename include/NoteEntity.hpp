#ifndef NOTEENTITY_HPP
#define NOTEENTITY_HPP
#include <string>

using namespace std;

class NoteEntity
{
public:
    NoteEntity();
    virtual void setBody(string body){_body = body;}
    virtual string getBody() const {return _body;}
private:
    string _body;
};

#endif // NOTEENTITY_HPP
