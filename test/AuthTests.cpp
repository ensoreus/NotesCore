#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AuthLayer.hpp"
#include "configuration.hpp"

using ::testing::Test;

class AuthTestSuite : public ::testing::Test{
protected:
    virtual void SetUp(){
        _authLayer = new AuthLayer(SERVER_URL);
    }
    virtual void TearDown(){
        delete _authLayer;
    }
    AuthLayer* _authLayer;
};

 TEST_F(AuthTestSuite, TestServerURLSetupCorrectly){
     ASSERT_TRUE(_authLayer != nullptr);
     EXPECT_EQ(_authLayer->getServerURL(), SERVER_URL);
 }

 TEST_F(AuthTestSuite, TestServerDenieWithAllInvalidCredentionals){
     _authLayer->setLogin(INVALID_LOGIN);
     _authLayer->setPassword(INVALID_PASSWORD);
     EXPECT_CALL(_authLayer, onAuthorizationFailed());
 }

 TEST_F(AuthTestSuite, TestServerDenieWithInvalidPassword){
     _authLayer->setLogin(VALID_LOGIN);
     _authLayer->setPassword(INVALID_PASSWORD);
     EXPECT_CALL(_authLayer, onAuthorizationFailed());
 }

 TEST_F(AuthTestSuite, TestServerAcceptWithValidCredentions){
     _authLayer->setLogin(VALID_LOGIN);
     _authLayer->setPassword(VALID_PASSWORD);
     EXPECT_CALL(_authLayer, onAuthorizationSuccessful());
     EXPECT_TRUE(_authLayer, isAuthorized());
 }
