#pragma once

#include <memory>

#include <globjects/base/HeapOnlyDeleter.h>

#include "AbstractParticleTechnique.h"

namespace globjects
{
class TransformFeedback;
class VertexArray;
class Program;
class Buffer;
}

class TransformFeedbackParticles : public AbstractParticleTechnique
{
public:
    TransformFeedbackParticles(
        const std::vector<glm::vec4> & positions
    ,   const std::vector<glm::vec4> & velocities
    ,   const globjects::Texture & forces
    ,   const Camera & camera);
    virtual ~TransformFeedbackParticles();

    virtual void initialize() override;
    virtual void reset() override;

    virtual void step(float elapsed) override;

protected:
    virtual void draw_impl() override;

protected:
    std::unique_ptr<globjects::TransformFeedback, globjects::HeapOnlyDeleter> m_transformFeedback;
    std::unique_ptr<globjects::Program, globjects::HeapOnlyDeleter> m_transformFeedbackProgram;

    std::unique_ptr<globjects::Buffer, globjects::HeapOnlyDeleter> m_sourcePositions;
    std::unique_ptr<globjects::Buffer, globjects::HeapOnlyDeleter> m_sourceVelocities;
    std::unique_ptr<globjects::Buffer, globjects::HeapOnlyDeleter> m_targetPositions;
    std::unique_ptr<globjects::Buffer, globjects::HeapOnlyDeleter> m_targetVelocities;

    std::unique_ptr<globjects::VertexArray, globjects::HeapOnlyDeleter> m_vao;
};
