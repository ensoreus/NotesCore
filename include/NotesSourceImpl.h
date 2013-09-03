#ifndef NOTESSOURCEIMPL_H
#define NOTESSOURCEIMPL_H

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/connection-factory.hxx>

#include "NoteEntity.hpp"
#include "NoteEntity-odb.hxx"
#include "INoteSource.h"

using namespace std;
using namespace odb;

class NotesSourceImpl : public INoteSource
{
public:
    NotesSourceImpl(){}
    NotesSourceImpl(const char* dbfilename);
    NoteEntity* AddNote(const char*);
    NoteEntity* FindByTime(time_t);
protected:
    auto_ptr<database> _db;
};

#endif // NOTESSOURCEIMPL_H
