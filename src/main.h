#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/async_logger.h"
#include "backend/dbio/dbio.h"

class iwb_main
{
    public:
        static iwb_main& get_instance()
        {
            static iwb_main instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        iwb_main() {}                    // Constructor? (the {} brackets) are needed here.
        iwb_main(iwb_main const&);              // Don't Implement
        void operator=(iwb_main const&); // Don't implement


        std::mutex main_mutex;
        /// @brief main logger for our cases
        std::shared_ptr<spdlog::async_logger> logger = nullptr;
        /// @brief spdlog sinks for async logging
        std::vector<spdlog::sink_ptr> sinks;

        /// @brief main database interaction module instantiation
        DBIO::dbio_main dbio;



        /// @brief attempts to initialize all modules used by IWB with try-catch statements
        /// @return false if any module fails to initialize
        bool initialize_modules();
    public:

        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status

                /// @brief 
        /// returns pointer to the main logger (through spdlog)
        /// @return 
        std::shared_ptr<spdlog::logger> get_logger();

        /// @brief returns the main loggers sinks so you can create a logger that goes to the same log
        /// @return 
        std::vector<spdlog::sink_ptr>& get_logger_sinks();

        /// @brief 
        /// initializes infinity-world-builder
        bool initialize();
};