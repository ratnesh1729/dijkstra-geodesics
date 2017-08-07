#include "gtest/gtest.h"

class DijTest : public ::testing::Test
{
protected:
    DijTest();

    // clean ups
    virtual ~DijTest();

    // set up and clean ups - when constructor and destructors are not enough

    virtual void SetUp();

    virtual void TearDown(); //If any exceptions - then catch here rather than destructor
};
