
#include "game_controller.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Main entry point for Bowling Game application
 * @return Exit status code (0 for success, non-zero for failure)
 */
std::int32_t main()
{
    std::int32_t i32_exit_code = EXIT_SUCCESS;

    try
    {
        i32_exit_code = GameController::RunApplication();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        i32_exit_code = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        i32_exit_code = EXIT_FAILURE;
    }

    return i32_exit_code;
}