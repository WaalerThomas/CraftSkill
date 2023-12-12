#include <CUnit/CUnitCI.h>
#include "../src/CraftSkill/player.h"

static void item_moves_from_container_when_equipped()
{
    // Arrange
    Player player = player_new(10);
    Item axe = item_new("Axe", ITEM_TYPE_WEAPON, 1);
    container_add(&player.inventory, &axe);

    // Act
    player_equip(&player, &player.inventory, "Axe");

    // Assert
    CU_ASSERT_NOT_EQUAL(player.equipped.mainhand.name, NULL);
    CU_ASSERT_NOT_EQUAL(player.equipped.mainhand.count, 0);
    CU_ASSERT_STRING_EQUAL(player.equipped.mainhand.name, "Axe");
    CU_ASSERT_EQUAL(player.inventory.count, 0);
}

static void can_not_equip_item_that_does_not_exist()
{
    Player player = player_new(10);
    Item stick = item_new("Stick", ITEM_TYPE_DEFAULT, 99);
    container_add(&player.inventory, &stick);

    player_equip(&player, &player.inventory, "NotAnItem");

    CU_ASSERT_EQUAL(player.inventory.count, 1);
}

static void can_not_equip_non_equipable_item()
{
    Player player = player_new(10);
    Item stick = item_new("Stick", ITEM_TYPE_DEFAULT, 99);
    container_add(&player.inventory, &stick);

    player_equip(&player, &player.inventory, "Stick");

    CU_ASSERT_EQUAL(player.inventory.count, 1);
}

CUNIT_CI_RUN("player-tests",
    CUNIT_CI_TEST(item_moves_from_container_when_equipped),
    CUNIT_CI_TEST(can_not_equip_item_that_does_not_exist),
    CUNIT_CI_TEST(can_not_equip_non_equipable_item)
);
