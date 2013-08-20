#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "NoteEntity.hpp"

class NoteEntityTestSuite : public ::testing::Test{
  protected:
    virtual void SetUp(){
        _note = new NoteEntity();
    }
    virtual void TearDown(){
        delete _note;
    }

    NoteEntity* _note;
};


TEST_F(NoteEntityTestSuite, TestNoteHaveBody){
    string body("body1");
    _note->setBody(body);
    ASSERT_EQ(_note->getBody(), body);
}
