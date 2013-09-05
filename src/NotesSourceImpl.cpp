#include "NotesSourceImpl.h"
#include "NoteEntity.hpp"
#include "NoteEntity-odb.hxx"
#include <odb/schema-catalog.hxx>

NotesSourceImpl::NotesSourceImpl(const char* dbfilename)
{
    _db = auto_ptr<database>(new odb::sqlite::database (dbfilename, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
    connection_ptr c (_db->connection ());
    c->execute ("PRAGMA foreign_keys=OFF");
    transaction t (c->begin ());
    if (!schema_catalog::exists(*_db, dbfilename))
    {
        schema_catalog::create_schema (*_db);
    }
    t.commit ();
    c->execute ("PRAGMA foreign_keys=ON");
}

NoteEntity* NotesSourceImpl::AddNote(const char* noteBody)
{
    session s();
    transaction t(_db->begin());
    NoteEntity* note = new NoteEntity(noteBody);
    _db->persist(*note);
    return note;
}

void NotesSourceImpl::FindByText(const char* text) const
{
    session s;
    typedef odb::query<NoteEntity> query;
    query qBody( query::body == text);
    transaction tr(_db->begin());
    odb::result<NoteEntity> searchResult(_db->query<NoteEntity>(qBody));

    if (searchResult.empty())
    {
      _delegate->sourceDidFoundNotes(auto_ptr<list<NoteEntity *> >(new list<NoteEntity*>()));
    }else{
      //       _delegate->sourceDidFoundNotes();
    }
    tr.commit();
}

NoteEntity* NotesSourceImpl::FindByTime(time_t t)
{
    session s;
    transaction tr(_db->begin());
    odb::result<NoteEntity> searchResults(_db->query<NoteEntity> ( odb::query<NoteEntity>::timestamp == t));
    if (searchResults.empty())
        return NULL;
    NoteEntity* entity = new NoteEntity(*searchResults.begin());
    tr.commit();
    return entity;
}
