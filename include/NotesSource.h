#ifndef NOTESSOURCE_H
#define NOTESSOURCE_H
#include <time.h>
#include <memory>
#include "INoteSource.h"

using namespace std;

class NotesSource
{
public:
    static NotesSource* book();
    NotesSource();
    time_t AddNote(const char* body);
    const char *FindByTime(time_t t);
private:
    auto_ptr<INoteSource> _impl;
};

#endif // NOTESSOURCE_H
