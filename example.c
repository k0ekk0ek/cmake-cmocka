/*
 * example.c -- usage example for cmocka CMake module
 *
 * Copyright (c) 2020, Jeroen Koekkoek
 *
 * See LICENSE for the license.
 *
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <cmocka.h>

/* Test runners are merely main functions that accept a set of command line
 * parameters and execute a (sub)set of tests based thereon. The cmocka CMake
 * module can automatically generate a test runner for you based on so-called
 * annotations. These annotations simply generate some declarations in the
 * runner, the main function than executes the registered tests.
 */

/* GROUPS
 *
 * cmocka runs tests in groups.
 */

/* No group specified yet, default group is the basename of the source file
 * transformed by the CMake command string(MAKE_C_IDENTIFIER ...). The default
 * group name in this case would be "example" because the file is named
 * "example.c".
 */

/* Groups can be manually defined though. */
/*!cmocka group foo */

/* The latest group is the default in the scope of the file until another
 * group is defined.
 */
/*!cmocka group bar */

/* Groups can be redefined too. e.g. to switch back to "foo". */
/*!cmocka group foo */

/* Because groups can be (re)defined and do not refer to any symbols in
 * external files, a group can contain tests from multiple files.
 */

/* TESTS
 *
 * Groups are named sets of functions with a specific signature (as dictated
 * by cmocka) executed in sequence. To create a test that does nothing but
 * prints its name and succeeds.
 */

void foobar(void **state)
{
  (void)state; /* unused */
  printf("%s called\n", __func__);
}

/* Annotate the function to include the test in the runner. */

/*!cmocka */
void foobaz(void **state)
{
  (void)state; /* unused */
  printf("%s called\n", __func__);
}

/* Tests are added to the default group unless one is specified explicitly.
 * i.e. the above test is added to the group "foo" as that is the last group,
 * and therefore the default, defined in this file. To use a different group,
 * which may or may not be defined dynamically, specify it in the directive.
 */

/*!cmocka group:baz */
void barbaz(void **state)
{
  (void)state; /* unused */
  printf("%s called\n", __func__);
}

/* The specified group is created dynamically, but not made the default. */

/* Minimalistic annotations are encouraged if the type and name can be
 * determined (without preprocessing) from the function signature that
 * follows, but tests can be named explicitly too. This can be useful if the
 * signature is created through macro expansion.
 */

/*!cmocka test foobar */

/* Tests that are named explicitly are not required to be followed by a valid
 * cmocka function signature. The above directive results in the foobar test
 * defined earlier being included in the runner.
 */

/* FIXTURES
 *
 * Both tests and groups accept fixtures. Fixtures can be used to specify
 * functions that need to be executed before or after each group or test.
 * e.g. to setup or teardown the environment.
 */

/* To execute a function before a certain group of tests is executed, use
 * setup. Similarly, to execute a function after all tests in a group are
 * executed, use teardown.
 */

/*!cmocka group foo setup:setup_foo teardown:teardown_foo */

/* Ensure that each fixture is defined and annotated. Note that fixtures do
 * not necessarily have to be defined in the same file.
 */

/*!cmocka */
int setup_foo(void **state)
{
  (void)state; /* unused */
  printf("%s called\n", __func__);
  return 0;
}

/*!cmocka */
int teardown_foo(void **state)
{
  (void)state; /* unused */
  printf("%s called\n", __func__);
  return 0;
}

/* Fixtures are static. The fixtures first defined for the group are reused
 * with every group redefintion whether the redefinition specifies fixtures
 * or not.
 */

/* Annotate tests to execute functions before and after each test. Fixtures
 * can be shared across multiple tests.
 */

/*!cmocka setup setup_bar */
int setup_bar(void **state)
{
  (void)state;
  printf("%s called\n", __func__);
  return 0;
}

/*!cmocka teardown teardown_bar */
int teardown_bar(void **state)
{
  (void)state;
  printf("%s called\n", __func__);
  return 0;
}

/*!cmocka setup:setup_bar teardown:teardown_bar */
void test_bar(void **state)
{
  (void)state;
  printf("%s called\n", __func__);
}

/*!cmocka setup:setup_bar teardown:teardown_bar */
void test_baz(void **state)
{
  (void)state;
  printf("%s called\n", __func__);
}

/* Besides setup and teardown, tests accept disabled and timeout fixtures.
 * To disable a test entirely use disabled:true (false is the default), to
 * adjust the amount of time is allowed to take, specify timeout:<seconds>
 * (default is 10s).
 */
