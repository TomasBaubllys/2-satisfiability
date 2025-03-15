#ifndef NOT_IMPLEMENTED_H_INCLUDED
#define NOT_IMPLEMENTED_H_INCLUDED

#include <stdexcept>

#define NOT_IMPL_DEFAULT_MSG "Function not implemented yet"

class Not_implemented: public std::logic_error {
    public:
        Not_implemented(const char *msg);
};

#endif // NOT_IMPLEMENTED_H_INCLUDED