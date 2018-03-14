
#ifndef __FELIDE_GTK3_HELPER_HPP__
#define __FELIDE_GTK3_HELPER_HPP__

#include <gtkmm.h>

namespace Felide::GTK3 {
    /**
     * @brief Get a reference to the underlying GTKmm smart pointer
     */
    template<typename T>
    inline T& ref(Glib::RefPtr<T> &obj) {
        return *obj.operator->();
    }
}

#endif
