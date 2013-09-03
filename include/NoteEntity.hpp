#ifndef NOTEENTITY_HPP
#define NOTEENTITY_HPP

#include <string>
#include <odb/core.hxx>

using namespace std;

#pragma db object
class NoteEntity
{
public:
    NoteEntity():_active(true),_timestamp(time(0)),_body(""){}
    NoteEntity(const char* body):_active(true),_timestamp(time(0)),_body(body){}
    NoteEntity(const string& body):_active(true),_timestamp(time(0)),_body(body){}
    NoteEntity(const NoteEntity& note):_active(note._active),_timestamp(note._timestamp), _body(note._body){}
    NoteEntity(NoteEntity &note): _active(note._active), _timestamp(note._timestamp),_body(note._body){}
    virtual void setBody(string body){_body = body;}
    virtual string getBody() const {return _body;}
    virtual bool isActive() const {return _active;}
    virtual void setActive(bool isActive){_active = isActive;}
    virtual void setTimestamp(time_t timestamp){_timestamp = timestamp;}
    virtual time_t getTimestamp()const {return _timestamp;}
    virtual long getID() const {return id_;}
    virtual ~NoteEntity(){}
protected:
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
