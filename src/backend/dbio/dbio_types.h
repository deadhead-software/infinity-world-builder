/*******************************************************************
* Copyright         : 2026 Jason C McQueen, Deadhead Software
* File Name         : dbio_types.h
* Description       : dump file for all common types pertaining to DBIO
*                    
* Revision History  :
* Date		        Author 			Comments
* ------------------------------------------------------------------
* 08/1/2026     	Jason C McQueen	        initial file creation
*
/******************************************************************/
#pragma once


namespace DBIO
{
    /// @brief used for parameters and return statements of what database
    ///        IWB is using at the moment.
    enum class db_type
    {
        UNKNOWN,
        TEST,
        USER,
        SEED,
        MAX
    };
}