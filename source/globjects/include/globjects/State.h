#pragma once

#include <unordered_map>
#include <vector>

#include <globjects/binding/types.h>
#include <globjects/binding/typeintegrations.h>

#include <globjects/base/Referenced.h>

#include <globjects/globjects_api.h>
#include <globjects/AbstractState.h>

namespace globjects
{

class StateSetting;
class Capability;


class GLOBJECTS_API State : public AbstractState, public Referenced
{
public:
    enum Mode
    {
        DeferredMode,
        ImmediateMode
    };

public:
    State(Mode = ImmediateMode);

    static State * currentState();

    void setMode(Mode mode);
    Mode mode() const;

    void apply();

    virtual void enable(binding::GLenum capability) override;
    virtual void disable(binding::GLenum capability) override;
    virtual bool isEnabled(binding::GLenum capability) const override;
    virtual void enable(binding::GLenum capability, int index) override;
    virtual void disable(binding::GLenum capability, int index) override;
    virtual bool isEnabled(binding::GLenum capability, int index) const override;

    virtual void add(StateSetting * setting) override;

    Capability * capability(binding::GLenum capability);
    const Capability * capability(binding::GLenum capability) const;
    std::vector<Capability *> capabilities() const;

    StateSetting * setting(const StateSettingType & type);
    const StateSetting * setting(const StateSettingType & type) const;
    std::vector<StateSetting *> settings();
    std::vector<const StateSetting *> settings() const;

protected:
    void addCapability(Capability * capability);
    Capability * getCapability(binding::GLenum capability);
    const Capability * getCapability(binding::GLenum capability) const;

protected:
    virtual ~State();

    Mode m_mode;
    std::unordered_map<binding::GLenum, Capability *> m_capabilities;
    std::unordered_map<StateSettingType, StateSetting *> m_settings;
};

} // namespace globjects
