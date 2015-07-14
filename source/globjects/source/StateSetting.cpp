
#include <globjects/StateSetting.h>

#include <globjects/binding/enum.h>

namespace globjects
{

using namespace binding;

StateSettingType::StateSettingType()
: m_functionIdentifier(nullptr)
{
}

StateSettingType::StateSettingType(void * functionIdentifier)
: m_functionIdentifier(functionIdentifier)
{
}

bool StateSettingType::operator==(const StateSettingType & other) const
{
    return m_functionIdentifier == other.m_functionIdentifier && m_subtypes == other.m_subtypes;
}

std::size_t StateSettingType::hash() const
{
    return std::hash<void*>()(m_functionIdentifier);
}

void StateSettingType::specializeType(const GLenum subtype)
{
    m_subtypes.insert(subtype);
}

StateSetting::StateSetting(AbstractFunctionCall * functionCall)
: m_functionCall(functionCall)
, m_type(m_functionCall->identifier())
{
}

StateSetting::~StateSetting()
{
}

void StateSetting::apply()
{
    (*m_functionCall)();

}

const StateSettingType & StateSetting::type() const
{
    return m_type;
}

StateSettingType & StateSetting::type()
{
    return m_type;
}

} // namespace globjects

namespace std {

size_t hash<globjects::StateSettingType>::operator()(const globjects::StateSettingType & type) const
{
    return type.hash();
}

} // namespace std
