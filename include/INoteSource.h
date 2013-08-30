#ifndef INOTESOURCE_H
#define INOTESOURCE_H
class INoteSource{
public:
    virtual time_t AddNote(const char*) = 0;
    virtual const char* FindByTime(time_t) = 0;
};
#endif // INOTESOURCE_H
