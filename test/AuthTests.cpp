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
 };
