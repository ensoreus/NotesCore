#include "gtest/gtest.h"
#include "gmock/gmock.h"
#define DATABASE_SQLITE
#include "NoteEntity.hpp"
#include "NoteEntity-odb.hxx"
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/connection-factory.hxx>
#include "database.hxx"

using namespace std;
using namespace odb;
using namespace odb::core;

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

TEST_F(NoteEntityTestSuite, TestConstructorWithParams){
    delete _note;
    _note = new NoteEntity("note1");
    ASSERT_STREQ(_note->getBody().c_str(), "note1");
    ASSERT_NE(_note->getTimestamp(), 0);
    ASSERT_TRUE(_note->isActive());
}

TEST_F(NoteEntityTestSuite, TestNoteHaveBody){
    string body("body1");
    _note->setBody(body);
    ASSERT_EQ(_note->getBody(), body);
}

TEST_F(NoteEntityTestSuite, TestNoteHaveDate){
    std::time_t t = time(NULL);
    _note->setTimestamp(t);
    ASSERT_EQ(_note->getTimestamp(), t);
}

TEST_F(NoteEntityTestSuite, TestNoteIsActive){
    _note->setActive(true);
    ASSERT_TRUE(_note->isActive());
}

TEST_F(NoteEntityTestSuite, TestNoteIsInactive){
    _note->setActive(false);
    ASSERT_TRUE(!_note->isActive());
}

TEST_F(NoteEntityTestSuite, TestNotePersistant){

}


