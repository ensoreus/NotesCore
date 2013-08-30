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

time_t NotesSourceImpl::AddNote(const char* noteBody)
{
    session s();
    transaction t(_db->begin());
    NoteEntity* note = new NoteEntity(noteBody);
    _db->persist(note);

    time_t theTime = note->getTimestamp();
    t.commit();
    delete note;
    return theTime;
}

const char* NotesSourceImpl::FindByTime(time_t)
{

}
//auto_ptr<NoteEntity> note(new NoteEntity(body));
