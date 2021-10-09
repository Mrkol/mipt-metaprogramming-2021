#pragma once

#include <string.hpp>
#include <optional>

template <class Base, class Derived>
concept IsDerived = std::is_base_of<Base, Derived>::value;

template <class From, auto target>
struct Mapping;

template <class Base, class Target, class... Mappings>
struct ClassMapper {
    static std::optional<Target> map(const Base& object);
};

template <class Base, class Target, Target target, class From, class... Mappings> requires IsDerived<Base, From>
struct ClassMapper<Base, Target, Mapping<From, target>, Mappings...> {
    static std::optional<Target> map(const Base& object) {
        return dynamic_cast<const From*>(&object) ? target : ClassMapper<Base, Target, Mappings...>::map(object);
    }
};

template <class Base, class Target>
struct ClassMapper<Base, Target> {
    static std::optional<Target> map(const Base&) {
        return std::nullopt;
    }
};
