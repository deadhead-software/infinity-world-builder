// Source - https://stackoverflow.com/a/1008289
// Posted by Loki Astari, modified by community. See post 'Timeline' for change history
// Retrieved 2026-07-31, License - CC BY-SA 4.0

/// @brief FOR REFERENCE, DO NOT USE NOR DERIVE THIS CLASS, USE THE IDEA TO MAKE SINGLETONS OF OTHER CLASS TYPES
class singleton
{
    public:
        static singleton& get_instance()
        {
            static singleton instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        singleton() {}                    // Constructor? (the {} brackets) are needed here.

        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are inaccessible(especially from outside), otherwise, you may accidentally get copies of
        // your singleton appearing.
        singleton(singleton const&);              // Don't Implement
        void operator=(singleton const&); // Don't implement

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        singleton(singleton const&)               = delete;
        void operator=(singleton const&)  = delete;

        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};
