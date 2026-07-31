#pragma once

#include <memory>
#include "spdlog/sinks/stdout_color_sinks.h"


class iwb_main
{
    private:
        std::shared_ptr<spdlog::logger> logger = nullptr;
    public:
        /// @brief 
        /// returns pointer to the main logger (through spdlog)
        /// @return 
        std::shared_ptr<spdlog::logger> get_logger();

        /// @brief 
        /// initializes infinity-world-builder
        void initialize();

};