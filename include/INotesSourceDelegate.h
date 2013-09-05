#ifndef INOTESSOURCEDELEGATE_H
#define INOTESSOURCEDELEGATE_H
#include <memory>
#include <list>
#include "NoteEntity.hpp"

using namespace std;

class INoteSourceDelegate{
  public:
    virtual void sourceDidFoundNotes( list< NoteEntity* > *) = 0;
};
#endif // INOTESSOURCEDELEGATE_H
