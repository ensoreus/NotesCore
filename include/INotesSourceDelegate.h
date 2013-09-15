#ifndef INOTESSOURCEDELEGATE_H
#define INOTESSOURCEDELEGATE_H
#include <memory>
#include <list>
#include "NoteEntity.hpp"

using namespace std;

class INoteSourceDelegate{
  public:
    virtual void sourceDidFoundNotes( auto_ptr< list< NoteEntity > >) = 0;
    virtual void sourceNotFoundNotes() = 0;
};
#endif // INOTESSOURCEDELEGATE_H
