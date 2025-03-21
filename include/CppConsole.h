//
// Created by Melanie on 23/02/2025.
//

#ifndef LIGHTSWITCH_CONSOLE_H
#define LIGHTSWITCH_CONSOLE_H

extern "C" {
#include "console.h"
}
#include <string>
#include <vector>
#include <functional>

class Console
{
public:
    enum ConsoleType
    {
#ifdef CONFIG_CPP_CONSOLE_TELNET
        TelnetConsole,
#endif
#ifdef CONFIG_CPP_CONSOLE_UART
        UartConsole,
#endif
    };
    Console() = default;
    void init(ConsoleType type, std::function<void(std::vector<std::string>)> processor, std::function<void (void)> onConnect = {});

private:
    void connectHandler();

    static void processCommandThunk(int argc, char **argv, void *user_data);
    static void connectHandlerThunk(void *user_data);

    ConsoleType m_type;
    struct console_handlers c_handlers = {};

//    void (*m_process)(std::vector<std::string>) = nullptr;
    std::function<void(std::vector<std::string>)> m_process;
    std::function<void (void)> m_onConnect = [this] { connectHandler(); };
};


#endif //LIGHTSWITCH_CONSOLE_H
