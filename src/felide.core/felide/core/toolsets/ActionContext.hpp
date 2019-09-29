
#ifndef __FELIDE_CORE_TOOLSETS_ACTIONCONTEXT_HPP__
#define __FELIDE_CORE_TOOLSETS_ACTIONCONTEXT_HPP__

#include <string>
#include <map>

namespace felide {
    typedef std::string CommandTemplate;
    typedef std::map<std::string, std::string> ActionContext;

    /**
     * @brief Instanciates a CommandTemplate into a String, based on the variables passed
     */
    std::string instanceTemplate(const CommandTemplate &command, const ActionContext &context);
}

#endif 
