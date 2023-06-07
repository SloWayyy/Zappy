/*
** EPITECH PROJECT, 2023
** communication
** File description:
** TestSdk.cpp
*/

#include <criterion/criterion.h>

#include "ICommunicationModule.hpp"

Test(sdk, basic_connection) {
    auto module = std::unique_ptr<zappy::sdk::ICommunicationModule>(communicationEntrypoint());

    try {
        module->connect("127.0.0.1", 4000);
    } catch (zappy::sdk::CommunicationException &e) {
        std::string message = "Connection failed: " + std::string(e.what());
        cr_assert_fail("%s", message.c_str());
    }
    cr_assert_eq(module->isConnected(), true, "Not connected");
    module->connectAsGraphical();
}
