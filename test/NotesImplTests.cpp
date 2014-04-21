#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NotesSourceImpl.h"
#include "INotesSourceDelegate.h"

#define testEntityBody "body1"
#define testDBfile "notes.db"

class NotesImplTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        _notesSourceImpl = new NotesSourceImpl(testDBfile);
    }
    virtual void TearDown(){
      delete _notesSourceImpl;
    }
    NotesSourceImpl* _notesSourceImpl;
};

class MockDelegate : public INoteSourceDelegate
{
public:
    MockDelegate(){}
    virtual ~MockDelegate(){}
    virtual void sourceDidFoundNotes( auto_ptr<list<NoteEntity> > notesFound)
    {
        testSourceDidFoundNotes(!notesFound->empty());
    }
  MOCK_METHOD1 (testSourceDidFoundNotes, void(bool));
  MOCK_METHOD0 (sourceNotFoundNotes, void(void));
};

TEST_F(NotesImplTests, LazyCreationOfNotesSourceImplementation)
{
    ASSERT_TRUE(_notesSourceImpl != NULL);
}

TEST_F(NotesImplTests, NoteCreating){
    time_t t = time(0);
    NoteEntity* entity = _notesSourceImpl->AddNote(testEntityBody);
    EXPECT_EQ(entity->getTimestamp(), t);
    EXPECT_STREQ(entity->getBody().c_str(), testEntityBody);
    delete entity;
}

TEST_F(NotesImplTests, CanHoldDelegate)
{
   MockDelegate  *mockDelegate = new MockDelegate() ;
   _notesSourceImpl->setDelegate( mockDelegate);
   ASSERT_TRUE(_notesSourceImpl->getDelegate() != NULL);
}

TEST_F(NotesImplTests, AsynchronousSearchByBody){
  typedef auto_ptr< list<NoteEntity> > ReturnValuesList;
  NoteEntity* addedNote = _notesSourceImpl->AddNote(testEntityBody) ;
  MockDelegate* mock = new MockDelegate();
  _notesSourceImpl->setDelegate( static_cast< INoteSourceDelegate* >(mock) );
  EXPECT_CALL( *mock, testSourceDidFoundNotes(true) );
  _notesSourceImpl->FindByText(testEntityBody);
  delete addedNote;
}

TEST_F(NotesImplTests, FindNotesByTimeRange)
{
   typedef auto_ptr< list<NoteEntity> > ReturnValuesList;
   NoteEntity* addedNote1 = _notesSourceImpl->AddNote(testEntityBody) ;
   time_t t = time(0);

   addedNote1->setTimestamp(t);
   NoteEntity* addedNote2 = _notesSourceImpl->AddNote(testEntityBody) ; 
   addedNote2->setTimestamp(t + 1200);
   NoteEntity* addedNote3 = _notesSourceImpl->AddNote(testEntityBody) ;
   addedNote3->setTimestamp(t + 1200 * 2);
   NoteEntity* addedNote4 = _notesSourceImpl->AddNote(testEntityBody) ;
   addedNote3->setTimestamp(t + 1200 * 3);
   time_t beginTime = t;
   time_t endTime = t + 1200 * 3;
   _notesSourceImpl->FindByTimeRange(beginTime, endTime);
   
   MockDelegate* mock = new MockDelegate();
   _notesSourceImpl->setDelegate( static_cast< INoteSourceDelegate* >(mock) );
    EXPECT_CALL( *mock, testSourceDidFoundNotes(true) );
    
}
