#include "forward.h"

#ifdef DEBUG
void printd(string text) { std::cout << "DEBUG-- " + text << std::endl; }
#else
void printd(string) {}
#endif
#ifdef VERBOSE
void printv(string text)
{
    std::cout << text << std::endl
              << std::flush;
}
#else
void printv(string text)
{
}
#endif