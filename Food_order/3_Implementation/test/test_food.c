#include "unity.h"
#include "unity_internals.h"
#include "food.h"
/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}


void test_add(void)
{
  TEST_ASSERT_EQUAL(30, add(10,20));
  TEST_ASSERT_EQUAL(320, add(300,20));
}

void test_add_zero(void)
{
  TEST_ASSERT_EQUAL(20, add(0,20));
  TEST_ASSERT_EQUAL(30, add(0,30));
}


void test_add_neg(void)
{
	TEST_ASSERT_EQUAL(30, add(70,-40));
  TEST_ASSERT_EQUAL(320, add(-100,420));
}

int test_main(void)
{
/* Initiate the Unity Test Framework */
  UNITY_BEGIN();

  RUN_TEST(test_add);
  RUN_TEST(test_add_zero);
  RUN_TEST(test_add_neg);

  /* Close the Unity Test Framework */
  return UNITY_END();
}
