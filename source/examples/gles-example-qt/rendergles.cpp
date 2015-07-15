#include "rendergles.h"

#include <glm/vec2.hpp>

#include <globjects/binding/Binding.h>
#include <globjects/binding/functions.h>
#include <globjects/binding/bitfield.h>
#include <globjects/binding/enum.h>

#include <globjects/globjects.h>

#include <globjects/Buffer.h>
#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/VertexArray.h>
#include <globjects/VertexAttributeBinding.h>
#include <globjects/base/StaticStringSource.h>

namespace
{
    const char * vertexShaderCode = R"(
#version 300 es

precision mediump float;

in vec2 corner;

out vec4 color;

void main()
{
    gl_Position = vec4(corner * 2.0 - 1.0, 0.0, 1.0);
    color = vec4(corner, 0.0, 1.0);
}

)";
    const char * fragmentShaderCode = R"(
#version 300 es

precision mediump float;

out vec4 fragColor;

in vec4 color;

void main()
{
    fragColor = color;
}

)";

    globjects::ref_ptr<globjects::VertexArray> m_vao;
    globjects::ref_ptr<globjects::Buffer> m_cornerBuffer;
    globjects::ref_ptr<globjects::Program> m_program;

}

using namespace globjects;
using namespace globjects::binding;

void initializeGLES()
{
    globjects::init();

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);

    m_cornerBuffer = new Buffer();
    m_program = new Program();
    m_vao = new VertexArray();

    m_program->attach(
        Shader::fromString(GL_VERTEX_SHADER,  vertexShaderCode),
        Shader::fromString(GL_FRAGMENT_SHADER, fragmentShaderCode));

    m_cornerBuffer->setData(std::array<glm::vec2, 4>{ {
        glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(1, 1) } }, GL_STATIC_DRAW);

    m_vao->binding(0)->setAttribute(0);
    m_vao->binding(0)->setBuffer(m_cornerBuffer, 0, sizeof(glm::vec2));
    m_vao->binding(0)->setFormat(2, GL_FLOAT);
    m_vao->enable(0);
}

void uninitializeGLES()
{
}

void resizeGLES(int width, int height)
{
    glViewport(0, 0, width, height);
}

void renderGLES()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->use();
    m_vao->drawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glFlush();
}
