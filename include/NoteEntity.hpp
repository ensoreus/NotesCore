#ifndef NOTEENTITY_HPP
#define NOTEENTITY_HPP

#include <string>
#include <odb/core.hxx>

using namespace std;

#pragma db object
class NoteEntity
{
public:
    NoteEntity(){}
    NoteEntity(string body):_body(body),_timestamp(time(0)),_active(true){}
    virtual void setBody(string body){_body = body;}
    virtual string getBody() const {return _body;}
    virtual bool isActive() const {return _active;}
    virtual void setActive(bool isActive){_active = isActive;}
    virtual void setTimestamp(time_t timestamp){_timestamp = timestamp;}
    virtual time_t getTimestamp()const {return _timestamp;}
    virtual long getID() const {return id_;}
private:
    friend class odb::access;
#pragma db id auto type("INTEGER")
    unsigned long id_;
#pragma db type("INTEGER")
    bool _active;
#pragma db type("INTEGER")
    time_t _timestamp;
#pragma db type("TEXT")
    string _body;
};

#endif // NOTEENTITY_HPP
