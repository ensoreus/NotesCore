#ifndef INOTESOURCE_H
#define INOTESOURCE_H

class NoteEntity;

class INoteSource{
public:
    virtual NoteEntity* AddNote(const char*) = 0;
    virtual NoteEntity* FindByTime(time_t) = 0;
};
#endif // INOTESOURCE_H
