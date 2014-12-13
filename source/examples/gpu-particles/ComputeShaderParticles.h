#pragma once

#include <memory>

#include <globjects/base/HeapOnlyDeleter.h>

#include "AbstractParticleTechnique.h"

namespace globjects
{
class Buffer;
class Program;
class VertexArray;
}

class ComputeShaderParticles : public AbstractParticleTechnique
{
public:
    ComputeShaderParticles(
        const std::vector<glm::vec4> & positions
    ,   const std::vector<glm::vec4> & velocities
    ,   const globjects::Texture & forces
    ,   const Camera & camera);

    virtual ~ComputeShaderParticles();

    virtual void initialize() override;
    virtual void reset() override;

    virtual void step(float elapsed) override;
    
protected:
    virtual void draw_impl() override;

protected:
    std::unique_ptr<globjects::Buffer, globjects::HeapOnlyDeleter> m_positionsSSBO;
    std::unique_ptr<globjects::Buffer, globjects::HeapOnlyDeleter> m_velocitiesSSBO;

    std::unique_ptr<globjects::Program, globjects::HeapOnlyDeleter> m_computeProgram;

    std::unique_ptr<globjects::VertexArray, globjects::HeapOnlyDeleter> m_vao;

    glm::uvec3 m_workGroupSize;
};
