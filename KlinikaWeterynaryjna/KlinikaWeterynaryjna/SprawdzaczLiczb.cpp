#include "SprawdzaczLiczb.h"


bool SprawdzaczLiczb::jestLiczba(const string& tekst)
{
    for (char const& znak : tekst) {
        if (std::isdigit(znak) == 0)
            return false;
    }
    return true;
}