#pragma once

#include <memory>

#include <globjects/base/HeapOnlyDeleter.h>

#include "AbstractParticleTechnique.h"

namespace globjects
{
class Texture;
class Framebuffer;
class VertexArray;
}

class FragmentShaderParticles : public AbstractParticleTechnique
{
public:
    FragmentShaderParticles(
        const std::vector<glm::vec4> & positions
    ,   const std::vector<glm::vec4> & velocities
    ,   const globjects::Texture & forces
    ,   const Camera & camera);

    virtual ~FragmentShaderParticles();

    virtual void initialize() override;
    virtual void reset() override;

    virtual void step(float elapsed) override;

protected:
    virtual void draw_impl() override;

protected:
    std::vector<glm::vec4> m_positionsFilled;
    std::vector<glm::vec4> m_velocitiesFilled;

    std::unique_ptr<globjects::Texture, globjects::HeapOnlyDeleter> m_positionsTex;
    std::unique_ptr<globjects::Texture, globjects::HeapOnlyDeleter> m_velocitiesTex;

    std::unique_ptr<globjects::Framebuffer, globjects::HeapOnlyDeleter> m_updateFbo;
    std::unique_ptr<ScreenAlignedQuad, globjects::HeapOnlyDeleter> m_updateQuad;

    std::unique_ptr<globjects::VertexArray, globjects::HeapOnlyDeleter> m_vao;

    glm::ivec2 m_workGroupSize;
};
