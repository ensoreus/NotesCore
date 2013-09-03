#ifndef NOTESSOURCE_H
#define NOTESSOURCE_H
#include <time.h>
#include "INoteSource.h"
#include <memory>

using namespace std;

class NotesSource
{
public:
    static NotesSource* book();
    NotesSource();
    NotesSource(INoteSource* implementation);
    NoteEntity* AddNote(const char* body);
    NoteEntity* FindByTime(time_t t);
    virtual ~NotesSource(){ }

private:
    auto_ptr<INoteSource> _impl;
};

#endif // NOTESSOURCE_H
