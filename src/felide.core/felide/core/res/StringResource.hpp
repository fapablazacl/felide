
#ifndef __FELIDE_STRINGRESOURCE_HPP__
#define __FELIDE_STRINGRESOURCE_HPP__

#include "Predef.hpp"
#include <string>

namespace felide {
    class FELIDE_API StringResource {
    public:
        StringResource();
        virtual ~StringResource();

        virtual std::string get(const std::string &key) const = 0;

    private:
        struct Private;
        Private *m_impl;
    };
} 

#endif
