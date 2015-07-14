#include <globjects/State.h>

#include <globjects/binding/enum.h>
#include <globjects/binding/extension.h>
#include <globjects/binding/Version.h>

#include <globjects/globjects.h>
#include <globjects/Capability.h>
#include <globjects/StateSetting.h>

namespace globjects 
{

using namespace binding;

State::State(const Mode mode)
: m_mode(mode)
{
}

State::~State()
{
    for (const auto & capability : m_capabilities)
    {
        delete capability.second;
    }
    for (const auto & setting : m_settings)
    {
        delete setting.second;
    }
}

State * State::currentState()
{
    State * state = new State(DeferredMode);

    std::vector<GLenum> capabilities = {
        GL_BLEND,
#ifdef GLOBJECTS_GL_BINDING
        GL_COLOR_LOGIC_OP,
#endif
        GL_CULL_FACE,
#ifdef GLOBJECTS_GL_BINDING
        GL_DEPTH_CLAMP,
#endif
        GL_DEPTH_TEST,
        GL_DITHER,
#ifdef GLOBJECTS_GL_BINDING
        GL_FRAMEBUFFER_SRGB,
        GL_LINE_SMOOTH,
        GL_MULTISAMPLE,
#else
        GL_FRAMEBUFFER_SRGB_EXT,
#endif
        GL_POLYGON_OFFSET_FILL,
#ifdef GLOBJECTS_GL_BINDING
        GL_POLYGON_OFFSET_LINE,
        GL_POLYGON_OFFSET_POINT,
        GL_POLYGON_SMOOTH,
        GL_PROGRAM_POINT_SIZE,
#else
        GL_POLYGON_OFFSET_LINE_NV,
        GL_POLYGON_OFFSET_POINT_NV,
#endif
        GL_RASTERIZER_DISCARD,
        GL_SAMPLE_ALPHA_TO_COVERAGE,
#ifdef GLOBJECTS_GL_BINDING
        GL_SAMPLE_ALPHA_TO_ONE,
#endif
        GL_SAMPLE_COVERAGE,
        GL_SAMPLE_MASK,
        GL_SCISSOR_TEST,
        GL_STENCIL_TEST
    };

#ifdef GLOBJECTS_GL_BINDING
    if (globjects::version() >= binding::Version(3, 1))
    {
        capabilities.push_back(GL_PRIMITIVE_RESTART);
        if (hasExtension(GLextension::GL_ARB_ES3_compatibility))
        {
            capabilities.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
        }
        state->primitiveRestartIndex(getInteger(GL_PRIMITIVE_RESTART_INDEX));

        if (hasExtension(GLextension::GL_ARB_sample_shading))
        {
            capabilities.push_back(GL_SAMPLE_SHADING);
        }
        if (hasExtension(GLextension::GL_ARB_seamless_cube_map))
        {
            capabilities.push_back(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        }
        if (hasExtension(GLextension::GL_ARB_provoking_vertex))
        {
            state->provokingVertex(getEnum(GL_PROVOKING_VERTEX));
        }
        // is this necessary here? should be controlled by debugmessageoutput
        if (hasExtension(GLextension::GL_KHR_debug))
        {
            capabilities.push_back(GL_DEBUG_OUTPUT);
            capabilities.push_back(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        }
    }
#endif

    for (GLenum capability : capabilities)
    {
        state->setEnabled(capability, globjects::isEnabled(capability));
    }

    state->blendColor(getFloats<4>(GL_BLEND_COLOR));
    state->blendFuncSeparate(getEnum(GL_BLEND_SRC_RGB), getEnum(GL_BLEND_DST_RGB), getEnum(GL_BLEND_SRC_ALPHA), getEnum(GL_BLEND_DST_ALPHA));
    state->clearColor(getFloats<4>(GL_COLOR_CLEAR_VALUE));
    state->clearDepth(getFloat(GL_DEPTH_CLEAR_VALUE));
    state->clearStencil(getInteger(GL_STENCIL_CLEAR_VALUE));
    state->colorMask(getBooleans<4>(GL_COLOR_WRITEMASK));
    state->cullFace(getEnum(GL_CULL_FACE_MODE));
    state->depthFunc(getEnum(GL_DEPTH_FUNC));
    state->depthMask(getBoolean(GL_DEPTH_WRITEMASK));
    state->depthRange(getFloats<2>(GL_DEPTH_RANGE));
    state->frontFace(getEnum(GL_FRONT_FACE));
#ifdef GLOBJECTS_GL_BINDING
    state->logicOp(getEnum(GL_LOGIC_OP_MODE));
    state->pointParameter(GL_POINT_FADE_THRESHOLD_SIZE, getInteger(GL_POINT_FADE_THRESHOLD_SIZE));
    state->pointParameter(GL_POINT_SPRITE_COORD_ORIGIN, getInteger(GL_POINT_SPRITE_COORD_ORIGIN));
    state->pointSize(getFloat(GL_POINT_SIZE));
    state->polygonMode(GL_FRONT, getEnums<2>(GL_POLYGON_MODE)[0]);
    state->polygonMode(GL_BACK, getEnums<2>(GL_POLYGON_MODE)[1]);
#else
    state->polygonMode(GL_FRONT, getEnums<2>(GL_POLYGON_MODE_NV)[0]);
    state->polygonMode(GL_BACK, getEnums<2>(GL_POLYGON_MODE_NV)[1]);
#endif
    state->polygonOffset(getFloat(GL_POLYGON_OFFSET_FACTOR), getFloat(GL_POLYGON_OFFSET_UNITS));
    state->sampleCoverage(getFloat(GL_SAMPLE_COVERAGE_VALUE), getBoolean(GL_SAMPLE_COVERAGE_INVERT));
    state->scissor(getIntegers<4>(GL_SCISSOR_BOX));
    state->stencilFuncSeparate(GL_FRONT, getEnum(GL_STENCIL_FUNC), getInteger(GL_STENCIL_REF), getInteger(GL_STENCIL_VALUE_MASK));
    state->stencilOpSeparate(GL_FRONT, getEnum(GL_STENCIL_FAIL), getEnum(GL_STENCIL_PASS_DEPTH_FAIL), getEnum(GL_STENCIL_PASS_DEPTH_PASS));
    state->stencilMaskSeparate(GL_FRONT, getInteger(GL_STENCIL_WRITEMASK));
    state->stencilFuncSeparate(GL_BACK, getEnum(GL_STENCIL_BACK_FUNC), getInteger(GL_STENCIL_BACK_REF), getInteger(GL_STENCIL_BACK_VALUE_MASK));
    state->stencilOpSeparate(GL_BACK, getEnum(GL_STENCIL_BACK_FAIL), getEnum(GL_STENCIL_BACK_PASS_DEPTH_FAIL), getEnum(GL_STENCIL_BACK_PASS_DEPTH_PASS));
    state->stencilMaskSeparate(GL_BACK, getInteger(GL_STENCIL_BACK_WRITEMASK));

    // pixel store
    std::vector<GLenum> pixelstoreParameters = {
#ifdef GLOBJECTS_GL_BINDING
        GL_PACK_SWAP_BYTES,
        GL_PACK_LSB_FIRST,
        GL_PACK_IMAGE_HEIGHT,
        GL_PACK_SKIP_IMAGES,
        GL_UNPACK_SWAP_BYTES,
        GL_UNPACK_LSB_FIRST,
#endif
        GL_PACK_ROW_LENGTH,
        GL_PACK_SKIP_PIXELS,
        GL_PACK_SKIP_ROWS,
        GL_PACK_ALIGNMENT,
        GL_UNPACK_ROW_LENGTH,
        GL_UNPACK_IMAGE_HEIGHT,
        GL_UNPACK_SKIP_PIXELS,
        GL_UNPACK_SKIP_ROWS,
        GL_UNPACK_SKIP_IMAGES,
        GL_UNPACK_ALIGNMENT
    };
    for (GLenum param : pixelstoreParameters)
    {
        state->pixelStore(param, getInteger(param));
    }

    return state;
}

void State::enable(const GLenum capability)
{
    Capability* cap = getCapability(capability);
    cap->enable();
    if (m_mode == ImmediateMode)
        cap->apply();
}

void State::disable(const GLenum capability)
{
    Capability* cap = getCapability(capability);
    cap->disable();
    if (m_mode == ImmediateMode)
        cap->apply();
}

bool State::isEnabled(const GLenum capability) const
{
    if (m_capabilities.find(capability) == m_capabilities.end())
        return false;

    return m_capabilities.at(capability)->isEnabled();
}

void State::enable(const GLenum capability, const int index)
{   
    Capability* cap = getCapability(capability);
    cap->enable(index);
    if (m_mode == ImmediateMode)
        cap->apply();
}

void State::disable(const GLenum capability, const int index)
{
    Capability* cap = getCapability(capability);
    cap->disable(index);
    if (m_mode == ImmediateMode)
        cap->apply();
}

bool State::isEnabled(const GLenum capability, const int index) const
{
    if (m_capabilities.find(capability) == m_capabilities.end())
        return false;

    return m_capabilities.at(capability)->isEnabled(index);
}

void State::setMode(const Mode mode)
{
    m_mode = mode;
}

State::Mode State::mode() const
{
    return m_mode;
}

void State::apply()
{
    for (const auto & capability : m_capabilities)
    {
        capability.second->apply();
    }
    for (const auto & setting : m_settings)
    {
        setting.second->apply();
    }
}

void State::addCapability(Capability * capability)
{
    if (m_capabilities.find(capability->capability()) != m_capabilities.end())
    {
        delete m_capabilities[capability->capability()];
    }

    m_capabilities[capability->capability()] = capability;
}

Capability* State::getCapability(GLenum capability)
{
    if (m_capabilities.find(capability) == m_capabilities.end())
    {
        m_capabilities[capability] = new Capability(capability);
    }

    return m_capabilities[capability];
}

std::vector<Capability*> State::capabilities() const
{
    std::vector<Capability*> caps;

    for (const auto& capability : m_capabilities)
    {
        caps.push_back(capability.second);
    }

    return caps;
}

Capability* State::capability(const GLenum capability)
{
    auto it = m_capabilities.find(capability);
    if (it == m_capabilities.end())
        return nullptr;

    return it->second;
}

const Capability* State::capability(const GLenum capability) const
{
    auto it = m_capabilities.find(capability);
    if (it == m_capabilities.end())
        return nullptr;

    return it->second;
}

std::vector<StateSetting*> State::settings()
{
    std::vector<StateSetting*> settings;

    for (const auto& setting : m_settings)
    {
        settings.push_back(setting.second);
    }

    return settings;
}

std::vector<const StateSetting*> State::settings() const
{
    std::vector<const StateSetting*> settings;

    for (const auto& setting : m_settings)
    {
        settings.push_back(setting.second);
    }

    return settings;
}

StateSetting * State::setting(const StateSettingType & type)
{
    auto it = m_settings.find(type);
    if (it == m_settings.end())
        return nullptr;

    return it->second;
}

const StateSetting * State::setting(const StateSettingType & type) const
{
    auto it = m_settings.find(type);
    if (it == m_settings.end())
        return nullptr;

    return it->second;
}

void State::add(StateSetting * setting)
{
    auto type = setting->type();
    if (m_settings.find(type) != m_settings.end())
    {
        delete m_settings[type];
        m_settings.erase(type);
    }
    m_settings[type] = setting;

    if (m_mode == ImmediateMode)
        setting->apply();
}

} // namespace globjects
