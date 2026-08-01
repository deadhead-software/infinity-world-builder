/*******************************************************************
* Copyright         : 2026 Jason C McQueen, Deadhead Software
* File Name         : module.h
* Description       : class for module derivation, creates loggers,
*                     holds health, etc.
*                    
* Revision History  :
* Date		        Author 			Comments
* ------------------------------------------------------------------
* 08/1/2026     	Jason C McQueen	        initial file creation
*
/******************************************************************/
#pragma once

#include <mutex>
#include <memory>
#include <string>
#include "spdlog/logger.h"

class module_type
{
    private:
        std::mutex my_mutex;

    protected:
        /// @brief (put this in your initialize class) initializes the logger for the 
        ///        module with the module's name. 
        /// @param name takes in the name of the module (preference for short names)
        /// @return returns false if it failed to initialize the logger for any reason
        bool initialize_module(std::string name);

        std::string module_name = "NO_NAME";
        std::shared_ptr<spdlog::logger> logger = nullptr;
    public:
        std::shared_ptr<spdlog::logger> get_logger();
        std::string get_name();
        void set_name(std::string new_name);
};