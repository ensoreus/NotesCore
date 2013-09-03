#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NotesSource.h"
#include "NotesSourceImpl.h"
#include "INotesSourceDelegate.h"

#include <memory>
#include <list>

#define testEntityBody "Body1"
#define testDBfile "notes.db"

using namespace std;

class NotesFasadeTests : public ::testing::Test
{
protected:
    virtual void SetUp(){
        _notesSource = new NotesSource();
    }

    virtual void TearDown(){
        delete _notesSource;
    }
    NotesSource* _notesSource;
};

class NotesImplTests : public ::testing::Test
{
protected:
    virtual void SetUp(){
        _notesSourceImpl = new NotesSourceImpl(testDBfile);
    }
    virtual void TearDown(){
        delete _notesSourceImpl;
    }
    NotesSourceImpl* _notesSourceImpl;
};

class MockNotesSourceImpl : public NotesSourceImpl{
public:
    MockNotesSourceImpl(const char* dbfilename):NotesSourceImpl(dbfilename){}
    MOCK_METHOD1( AddNote, NoteEntity*(const string& body) );
    MOCK_METHOD1( FindByTime, NoteEntity*(time_t t) );

    virtual void cleanup(NoteEntity *entity)
    {
        transaction tr(_db->begin());
        _db->erase(entity);
        tr.commit();
    }
    virtual ~MockNotesSourceImpl(){ }
};

class MockDelegate : public INoteSourceDelegate
{
public:
    MockDelegate(){}
    virtual ~MockDelegate(){}
    MOCK_METHOD1( sourceDidFoundNotes, void( list<auto_ptr<NoteEntity> >) );
};

TEST_F(NotesFasadeTests, LazyCreationOfNotesSource){
    ASSERT_TRUE(_notesSource != NULL);
}

TEST_F(NotesFasadeTests, AccessBySingleton){
    NotesSource* noteBook = NotesSource::book();
    ASSERT_TRUE(noteBook != NULL);
    EXPECT_STREQ(typeid(noteBook).name(), "P11NotesSource" );
}

TEST_F(NotesFasadeTests, AddNewNoteWithBodyOnly){
    const char* body = "Body1";
    MockNotesSourceImpl *mockImpl = new MockNotesSourceImpl(testDBfile);
    NotesSource* source = new NotesSource(mockImpl);
    EXPECT_CALL(*mockImpl, AddNote(body));
    auto_ptr<NoteEntity> note( _notesSource->AddNote(body) );
    //mockImpl->cleanup(note.get());
    delete source;
}

TEST_F(NotesFasadeTests, SynchronousSearchByTimestamp){
    MockNotesSourceImpl *mockImpl = new MockNotesSourceImpl(testDBfile);
    NotesSource* source = new NotesSource(mockImpl);
    EXPECT_CALL(*mockImpl, FindByTime(time(0)));
    auto_ptr<NoteEntity> note( _notesSource->FindByTime(time(0)) );
    //mockImpl->cleanup( note.get());
    delete source;
}

TEST_F(NotesImplTests, LazyCreationOfNotesSourceImplementation)
{
    ASSERT_TRUE(_notesSourceImpl != NULL);
}

TEST_F(NotesImplTests, NoteAdding){
    time_t t = time(0);
    NoteEntity* entity = _notesSourceImpl->AddNote(testEntityBody);
    EXPECT_EQ(entity->getTimestamp(), t);
    EXPECT_STREQ(entity->getBody().c_str(), testEntityBody);
    delete entity;
}

TEST_F(NotesImplTests, AsynchronousSearchByBody){
    auto_ptr<NoteEntity> addedNote(_notesSourceImpl->AddNote(testEntityBody) );
    MockDelegate* mock = new MockDelegate();
    _notesSourceImpl->setDelegate( dynamic_cast<INoteSourceDelegate>(mock) );
    list<auto_ptr<NoteEntity> > foundNotes;
    foundNotes.push_back( addedNote );
    EXPECT_CALL(mock, sourceDidFoundNotes(foundNotes));
    _notesSourceImpl->FindByText(testEntityBody);

}

