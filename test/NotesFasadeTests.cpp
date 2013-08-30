#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "NotesSource.h"

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


TEST_F(NotesFasadeTests, LazyCreationOfNotesSource){
    ASSERT_TRUE(_notesSource != NULL);
}

TEST_F(NotesFasadeTests, AccessBySingleton){
    NotesSource* noteBook = NotesSource::book();
    ASSERT_TRUE(noteBook != NULL);
    EXPECT_STREQ(typeid(noteBook).name(), "P11NotesSource" );
}

TEST_F(NotesFasadeTests, AddNewNoteWithBodyOnlyAndGetItByTimestamp){
    time_t stamp = _notesSource->AddNote("Body1");
    ASSERT_TRUE(stamp == time(0));

    const char* bodyOfNote = _notesSource->FindByTime(stamp);
    ASSERT_STREQ(bodyOfNote, "Body1");
}
