#pragma once

#include <unordered_map>
#include <memory>

#include <globjects/binding/ContextHandle.h>

namespace globjects
{

class ObjectRegistry;
class ExtensionRegistry;
class ImplementationRegistry;
class NamedStringRegistry;


class Registry
{
public:
    static void registerContext(binding::ContextHandle contextId);
    static void registerContext(binding::ContextHandle contextId, binding::ContextHandle sharedContextId);
    static void deregisterContext(binding::ContextHandle contextId);

    static void setCurrentContext(binding::ContextHandle contextId);

    static Registry & current();

    ObjectRegistry & objects();
    ExtensionRegistry & extensions();
    ImplementationRegistry & implementations();
    NamedStringRegistry & namedStrings();

    bool isInitialized() const;

private:
    Registry();
    Registry(Registry * sharedRegistry);
    ~Registry();

    void initialize();

    static bool isContextRegistered(binding::ContextHandle contextId);
    static void setCurrentRegistry(binding::ContextHandle contextId);

    static std::unordered_map<binding::ContextHandle, Registry *> s_registries;

private:
    bool m_initialized;
    std::shared_ptr<ObjectRegistry> m_objects;
    std::shared_ptr<ExtensionRegistry> m_extensions;
    std::shared_ptr<ImplementationRegistry> m_implementations;
    std::shared_ptr<NamedStringRegistry> m_namedStrings;
};

} // namespace globjects
