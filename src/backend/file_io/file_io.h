/*******************************************************************
* Copyright         : 2026 Jason C McQueen, Deadhead Software
* File Name         : file_io.h
* Description       : main class for reading and writing to files
*                     - mainly a wrapper for FileSystem (mostly, again, 
*                       for logging)
*                    
* Revision History  :
* Date		        Author 			Comments
* ------------------------------------------------------------------
* 08/2/2026	       Jason C McQueen	        initial file creation
*
/******************************************************************/
#pragma once

#include <iostream>
#include "module/module.h"

namespace FILE_IO
{
    class file_io_main : public module_type
    {
        private:
            /// @brief Look for the seed database in assets shipped alongside
            ///        the binary.
            /// @return true if the seed database was found in the assets folder along
            ///         with the binary.
            bool check_for_seed_db();
            /// @brief Either copies the seed db to the app data directory or returns true
            ///        if a user database already exists. If not, it'll try to create the DH SW
            ///         directory plus copy over the seed db. Will return false if either of these fail
            /// @return True if we found a user db or copied the seed database over. False if any of this
            ///         failed which would mean the app should fail.
            bool handle_user_db();
        public:
            bool initialize();

           
    };
}