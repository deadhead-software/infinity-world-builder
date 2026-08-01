/*******************************************************************
* Copyright         : 2026 Jason C McQueen, Deadhead Software
* File Name         : dbio.h
* Description       : main class for writing to the seed, user, or test
*                     database.
*                    
* Revision History  :
* Date		        Author 			Comments
* ------------------------------------------------------------------
* 07/31/2026	Jason C McQueen	        initial file creation
*
/******************************************************************/
#pragma once

#include <mutex>
#include "sqlite3.h"
#include "dbio_types.h"
#include "module/module.h"

/// @brief namespace for all things database interaction
namespace DBIO
{
    /// @brief main class for database interaction, implicitly singleton
    ///        from being included in iwb_main
    class dbio_main : public module_type
    {
        private:
            /// @brief protects everything for a multi-threaded environment
            std::mutex dbio_mutex;
            /// @brief currently used database, protected as private
            db_type current_db_type = db_type::UNKNOWN;


        public:
            /// @brief returns the currently used database type
            /// @return the database type 
            db_type get_db_type();
            /// @brief sets the currently used database type (which can be set automatically
            ///        in initialize())
            /// @param value the new database type
            void set_db_type(db_type value);
            bool initialize();
    };
}