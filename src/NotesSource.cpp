#include "NotesSource.h"
#include <memory>
#include <INoteSource.h>
#include "NotesSourceImpl.h"

NotesSource* NotesSource::book()
{
   static NotesSource* source = NULL;
   if (source == NULL){
       source = new NotesSource();
   }
   return source;
}

NotesSource::NotesSource(INoteSource* implementation)
{
    _impl.reset( implementation);
}

NotesSource::NotesSource()
{
    _impl = auto_ptr<INoteSource>(new NotesSourceImpl("notesource.db"));
}

NoteEntity* NotesSource::AddNote(const char *body)
{
    return _impl->AddNote(body);
}

NoteEntity* NotesSource::FindByTime(time_t t)
{
    return _impl->FindByTime(t);
}


