#include "unity.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../examples/autotest-validate/autotest-validate.h"
#include "../../assignment-autotest/test/assignment1/username-from-conf-file.h"

/**
* This function should:
*   1) Call the my_username() function in Test_assignment_validate.c to get your hard coded username.
*   2) Obtain the value returned from function malloc_username_from_conf_file() in username-from-conf-file.h within
*       the assignment autotest submodule at assignment-autotest/test/assignment1/
*   3) Use unity assertion TEST_ASSERT_EQUAL_STRING_MESSAGE the two strings are equal.  See
*       the [unity assertion reference](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md)
*/
void test_validate_my_username()
{
    /**
     * TODO: Replace the line below with your code here as described above to verify your /conf/username.txt 
     * config file and my_username() functions are setup properly
     */
    const char* username = my_username(); 
    const char* user_from_malloc = malloc_username_from_conf_file();
    printf("Username from conf file: %s\n", user_from_malloc);
    printf("Username from my_username(): %s\n", username);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(username, user_from_malloc,"Username from conf file and my_username() do not match");
}
