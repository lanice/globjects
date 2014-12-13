#pragma once

#include <memory>

namespace globjects
{

class VertexArray;
class Program;
class Buffer;
class Texture;
class Shader;

}


class ScreenAlignedQuad
{
public:
    ScreenAlignedQuad(globjects::Shader * fragmentShader, globjects::Texture * texture);

    ScreenAlignedQuad(globjects::Texture * texture);
    ScreenAlignedQuad(globjects::Shader  * fragmentShader);
    ScreenAlignedQuad(globjects::Program * program);

    ~ScreenAlignedQuad();

    void draw();

    void setTexture(globjects::Texture * texture);

    void setSamplerUniform(int index);

    /**
     * @brief Returns the program pointer if ScreenAlignedQuad was not create dusing an existing program
     * @return the private program instance.
     */
    globjects::Program * program();

protected:
    void initialize();

protected:
    std::unique_ptr<globjects::VertexArray> m_vao;

    std::unique_ptr<globjects::Buffer> m_buffer;

    std::unique_ptr<globjects::Shader> m_vertexShader;
    globjects::Shader * m_fragmentShader;
    std::unique_ptr<globjects::Shader> m_ownFragmentShader;

    globjects::Program * m_program;
    std::unique_ptr<globjects::Program> m_ownProgram;
    globjects::Texture * m_texture;

    int m_samplerIndex;
};
