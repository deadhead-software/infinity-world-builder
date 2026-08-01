#include "dbio.h"

namespace DBIO
{
    db_type dbio_main::get_db_type()
    {
        std::lock_guard<std::mutex> lock(dbio_mutex);
        return current_db_type;
    }

    void dbio_main::set_db_type(db_type value)
    {
        std::lock_guard<std::mutex> lock(dbio_mutex);
        current_db_type = value;
    }

    bool dbio_main::initialize()
    {

        return initialize_module("dbio");
    }
}