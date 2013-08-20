#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AuthLayer.hpp"
#include "configuration.hpp"
#include "IAuthLayerDelegate.hpp"

using namespace ::testing;
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

class MockAuthLayerDelegate : public IAuthLayerDelegate{
public:
    MOCK_METHOD0(onAuthorizationFailed,void());
    MOCK_METHOD0(onAuthorizationSuccessful, void());
};

 TEST_F(AuthTestSuite, TestServerURLSetupCorrectly){
     ASSERT_TRUE(_authLayer != nullptr);
     EXPECT_EQ(_authLayer->getServerURL(), SERVER_URL);
 }

 TEST_F(AuthTestSuite, TestServerDenyWithAllInvalidCredentionals){
     using ::testing::Mock;
     MockAuthLayerDelegate *mockAuthLayerDelegate = new MockAuthLayerDelegate();

     _authLayer->setLogin(INVALID_LOGIN);
     _authLayer->setPassword(INVALID_PASSWORD);
     _authLayer->setDelegate(mockAuthLayerDelegate);
      EXPECT_CALL(*mockAuthLayerDelegate, onAuthorizationFailed()).Times(1);
     _authLayer->authorize();


     Mock::VerifyAndClearExpectations(mockAuthLayerDelegate);
 }

 TEST_F(AuthTestSuite, TestServerDenyWithInvalidPassword){
     using ::testing::Mock;
     MockAuthLayerDelegate *mockAuthLayerDelegate = new MockAuthLayerDelegate();

     _authLayer->setLogin(VALID_LOGIN);
     _authLayer->setPassword(INVALID_PASSWORD);
     _authLayer->setDelegate(mockAuthLayerDelegate);
     EXPECT_CALL(*mockAuthLayerDelegate, onAuthorizationFailed()).Times(1);
     _authLayer->authorize();
     Mock::VerifyAndClearExpectations(mockAuthLayerDelegate);
 }

 TEST_F(AuthTestSuite, TestServerAcceptWithValidCredentions){
     using ::testing::Mock;
     MockAuthLayerDelegate *mockAuthLayerDelegate = new MockAuthLayerDelegate();

     _authLayer->setLogin(VALID_LOGIN);
     _authLayer->setPassword(VALID_PASSWORD);
     _authLayer->setDelegate(mockAuthLayerDelegate);
     EXPECT_CALL(*mockAuthLayerDelegate, onAuthorizationSuccessful()).Times(1);

     _authLayer->authorize();
     Mock::VerifyAndClearExpectations(mockAuthLayerDelegate);
 }
