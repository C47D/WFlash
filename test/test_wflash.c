#include "unity.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "wflash.h"

#include "fff.h"
DEFINE_FFF_GLOBALS;

/* Fake of a function with arguments and return value
 * A variable is created for every argument in the form
 * "function_name"_fake.argNval.
 * 
 * Argument history
 * "function_name"_fake.argN_history[0]
 *
 * Return values.
 * "function_name"_fake.return_val */
FAKE_VALUE_FUNC(uint32_t, wflash_ll_program, uint32_t, void *, size_t);

/* Se ejecuta antes de cada test */
void setUp(void)
{
    /* Reset the fake */
    RESET_FAKE(wflash_ll_program);

    /* Reset common fff internal structures */
    FFF_RESET_HISTORY();
}

/* Se ejecuta despues de cada test */
void tearDown(void)
{
}

void test_write_one_page(void)
{    
    uint8_t data_in[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
    };

    wflash_write(0, data_in, sizeof data_in);
    TEST_ASSERT_TRUE_MESSAGE(1, "invalid returned op ok");
    TEST_ASSERT_EQUAL(1, wflash_ll_program_fake.call_count);
}

void test_write_one_page_capture_arguments(void)
{    
    uint8_t data_in[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
    };

    wflash_write(0, data_in, sizeof data_in);
    TEST_ASSERT_TRUE_MESSAGE(1, "invalid returned op ok");
    
    TEST_ASSERT_EQUAL(1, wflash_ll_program_fake.call_count);
    TEST_ASSERT_EQUAL(0, wflash_ll_program_fake.arg0_val);
}

void test_write_multiple_pages(void)
{
    
    uint8_t data_in[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 16
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 32
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 48
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 64
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
    };

    wflash_write(31, data_in, sizeof data_in);
    TEST_ASSERT_TRUE_MESSAGE(1, "invalid returned op ok");
    TEST_ASSERT_EQUAL(4, wflash_ll_program_fake.call_count);
}

