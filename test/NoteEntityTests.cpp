#include "gtest/gtest.h"
#include "gmock/gmock.h"
#define DATABASE_SQLITE
#include "NoteEntity.hpp"
#include "NoteEntity-odb.hxx"
#include <memory>
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
        _note = new NoteEntity("note1");
        _db = auto_ptr<database>(new odb::sqlite::database ("notes.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
        connection_ptr c (_db->connection ());
        c->execute ("PRAGMA foreign_keys=OFF");
        transaction t (c->begin ());
        if (!schema_catalog::exists(*_db, "notes.db"))
        {
            schema_catalog::create_schema (*_db);
        }
        t.commit ();
        c->execute ("PRAGMA foreign_keys=ON");
    }
    virtual void TearDown(){
        try{
            transaction t3 (_db->begin ());
            _db->erase(*_note);
            t3.commit();
        }
        catch (const odb::exception& e)
        {
            //just suppress warnings that object not persistant
           // cerr << e.what () << endl;
            return ;
        }
        delete _note;
    }
    NoteEntity* _note;
    auto_ptr<database> _db;
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
    odb::session session;
    //create entity and persist it
    //NoteEntity note1("note2");
    try{
        transaction tr1(_db->begin());
        long noteId = _db->persist(*_note);
        tr1.commit();
    }
    catch(const odb::exception &e){
        cerr << e.what() << endl;
        return;
    }

    typedef odb::query<NoteEntity> query;
    typedef odb::result<NoteEntity> result;
    //read from starage
    try{
        transaction t2 (_db->begin ());
        result r (_db->query<NoteEntity> (query::id == _note->getID()));
        ASSERT_FALSE(r.empty());
        NoteEntity fetchedEntity = *r.begin();
        ASSERT_STREQ( fetchedEntity.getBody().c_str(), "note1");
        t2.commit();
    }
    catch (const odb::exception& e)
    {
        cerr << e.what () << endl;
        return ;
    }

    //erase from storage

}


