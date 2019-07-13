
#ifndef __FELIDE_CORE_POM_MODELS_PROPERTYIMPL_HPP__
#define __FELIDE_CORE_POM_MODELS_PROPERTYIMPL_HPP__

#include <utility>
#include <nlohmann/json.hpp>

namespace felide {
    template<typename Class, typename T>
    struct PropertyImpl {
        constexpr PropertyImpl(T Class::*pmember, const char *pname)
            : member{pmember}, name{pname} {}
        
        using Type = T;
        
        T Class::*member;
        const char *name;
    };
    
    template<typename Class, typename T>
    constexpr auto property(T Class::*member, const char *name) {
        return PropertyImpl{member, name};
    }
    
    template<typename T, T... S, typename F>
    constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
        (static_cast<void>(f(std::integral_constant<T, S>{})), ...);
    }
    
    
    template<typename Model>
    Model deserialize(const nlohmann::json &json) {
        constexpr auto propertyCount = std::tuple_size<decltype(Model::properties)>::value;
        
        Model model;
        
        for_sequence(std::make_index_sequence<propertyCount>{}, [&](auto i) {
            constexpr auto property = std::get<i>(Model::properties);
            using Type = typename decltype(property)::Type;
            
            model.*(property.member) = json[property.name].template get<Type>();
        });
        
        return model;
    }
    
    template<typename Model>
    nlohmann::json serialize(const Model &model) {
        constexpr auto propertyCount = std::tuple_size<decltype(Model::properties)>::value;
        
        nlohmann::json json;

        for_sequence(std::make_index_sequence<propertyCount>{}, [&](auto i) {
            constexpr auto property = std::get<i>(Model::properties);
            // using Type = typename decltype(property)::Type;
            
            json[property.name] = model.*(property.member);
        });
        
        return json;
    }
}

#endif
