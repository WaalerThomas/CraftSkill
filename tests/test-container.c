#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnitCI.h>
#include "../src/CraftSkill/container.h"

static void can_add_item_to_container(void)
{
    Container c = container_new("Container", 5);
    Item random = item_new("Random", ITEM_TYPE_DEFAULT, 1);
    container_add(&c, &random);

    CU_ASSERT_EQUAL(c.count, 1);
    CU_ASSERT_STRING_EQUAL(c.items[0].name, "Random");
}

static void can_not_add_more_items_to_container_than_capacity(void)
{
    Container c = container_new("Container", 3);
    Item random = item_new("Random", ITEM_TYPE_DEFAULT, 1);
    Item other = item_new("Other", ITEM_TYPE_DEFAULT, 1);
    Item more = item_new("More", ITEM_TYPE_DEFAULT, 1);
    Item last = item_new("Last", ITEM_TYPE_DEFAULT, 1);
    container_add(&c, &random);
    container_add(&c, &other);
    container_add(&c, &more);
    container_add(&c, &last);

    CU_ASSERT_EQUAL(c.count, 3);
    CU_ASSERT_STRING_EQUAL(c.items[2].name, "More");
}

static void item_can_not_have_0_as_max_amount(void)
{
    Item i = item_new("TestItem", ITEM_TYPE_DEFAULT, 0);
    CU_ASSERT_EQUAL(i.max_amount, 1);
}

static void container_can_not_have_zero_in_capacity(void)
{
    Container c = container_new("Container", 0);
    CU_ASSERT_EQUAL(c.capacity, 1);
}

static void container_can_not_have_negative_capacity(void)
{
    Container c = container_new("Container", -5);
    CU_ASSERT_EQUAL(c.capacity, 10000);
}

static void container_can_not_have_capacity_higher_than_10_000(void)
{
    Container c = container_new("Container", 50000);
    CU_ASSERT_EQUAL(c.capacity, 10000);
}

static void can_remove_item_from_container(void)
{
    Container c = container_new("Container", 10);
    Item random = item_new("Random", ITEM_TYPE_DEFAULT, 1);
    container_add(&c, &random);

    container_remove(&c, "Random", 1);

    CU_ASSERT_EQUAL(c.count, 0);
}

static void can_remove_only_one_from_item_stack_in_container(void)
{
    Container c = container_new("Container", 10);
    Item random = item_new("Random", ITEM_TYPE_DEFAULT, 99);
    random.count = 4;
    container_add(&c, &random);

    container_remove(&c, "Random", 2);

    CU_ASSERT_EQUAL(c.count, 1);
    CU_ASSERT_EQUAL(c.items[0].count, 2);
}

static void can_not_remove_more_items_than_is_available(void)
{
    Container c = container_new("Container", 10);
    Item random = item_new("Random", ITEM_TYPE_DEFAULT, 99);
    random.count = 4;
    container_add(&c, &random);

    container_remove(&c, "Random", 5);

    CU_ASSERT_EQUAL(c.count, 1);
    CU_ASSERT_EQUAL(c.items[0].count, 4);
}

static void can_find_index_of_item(void)
{
    Container c = container_new("Container", 10);
    Item randomItem = item_new("Random", ITEM_TYPE_DEFAULT, 99);
    Item stick = item_new("Stick", ITEM_TYPE_DEFAULT, 99);
    container_add(&c, &randomItem);
    container_add(&c, &stick);

    int32_t item_index = container_get_item_index(&c, "Stick");

    CU_ASSERT_EQUAL(item_index, 1);
}

static void can_not_find_index_of_wrong_item(void)
{
    Container c = container_new("Container", 10);
    Item randomItem = item_new("Random", ITEM_TYPE_DEFAULT, 99);
    Item stick = item_new("Stick", ITEM_TYPE_DEFAULT, 99);
    container_add(&c, &randomItem);
    container_add(&c, &stick);

    int32_t item_index = container_get_item_index(&c, "NotAnItem");

    CU_ASSERT_EQUAL(item_index, -1);
}

CUNIT_CI_RUN("container-tests",
    CUNIT_CI_TEST(can_add_item_to_container),
    CUNIT_CI_TEST(can_not_add_more_items_to_container_than_capacity),
    CUNIT_CI_TEST(item_can_not_have_0_as_max_amount),
    CUNIT_CI_TEST(container_can_not_have_zero_in_capacity),
    CUNIT_CI_TEST(container_can_not_have_negative_capacity),
    CUNIT_CI_TEST(container_can_not_have_capacity_higher_than_10_000),
    CUNIT_CI_TEST(can_remove_item_from_container),
    CUNIT_CI_TEST(can_remove_only_one_from_item_stack_in_container),
    CUNIT_CI_TEST(can_not_remove_more_items_than_is_available),
    CUNIT_CI_TEST(can_find_index_of_item),
    CUNIT_CI_TEST(can_not_find_index_of_wrong_item)
);
