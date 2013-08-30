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

NotesSource::NotesSource()
{
    _impl = auto_ptr<INoteSource>(new NotesSourceImpl("notesource.db"));
}

time_t NotesSource::AddNote(const char *body){
    return _impl->AddNote(body);
}

const char* NotesSource::FindByTime(time_t t){
    return "1";
}
