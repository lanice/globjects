
#include <glbinding/gl/gl.h>

#include <globjects/NamedString.h>
#include <globjects/Shader.h>

#include <globjects/logging.h>
#include <globjects/base/File.h>

#include <common/ScreenAlignedQuad.h>
#include <common/ContextFormat.h>
#include <common/Context.h>
#include <common/Window.h>
#include <common/WindowEventHandler.h>
#include <common/events.h>


using namespace gl;
using namespace globjects;

class EventHandler : public WindowEventHandler
{
public:
    EventHandler()
    {
    }

    virtual ~EventHandler()
    {
    }

    virtual void initialize(Window & window) override
    {
        WindowEventHandler::initialize(window);

        glClearColor(0.2f, 0.3f, 0.4f, 1.f);

        NamedString::create("/color.glsl", new File("data/shaderincludes/color.glsl"));

        m_quad = new ScreenAlignedQuad(Shader::fromFile(GL_FRAGMENT_SHADER, "data/shaderincludes/test.frag"));
    }
    
    virtual void paintEvent(PaintEvent & event) override
    {
        WindowEventHandler::paintEvent(event);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_quad->draw();
    }

protected:
    ref_ptr<ScreenAlignedQuad> m_quad;
};


int main(int /*argc*/, char * /*argv*/[])
{
    info() << "Usage:";
    info() << "\t" << "ESC" << "\t\t"       << "Close example";
    info() << "\t" << "ALT + Enter" << "\t" << "Toggle fullscreen";
    info() << "\t" << "F11" << "\t\t"       << "Toggle fullscreen";
    info() << "\t" << "F10" << "\t\t"       << "Toggle vertical sync";
    info() << "\t" << "F5" << "\t\t"        << "Reload shaders";

    ContextFormat format;
    format.setVersion(3, 1);
    format.setForwardCompatible(true);

    Window::init();

    Window window;
    window.setEventHandler(new EventHandler());

    if (!window.create(format, "Shading Language Include Example"))
        return 1;

    window.show();

    return MainLoop::run();
}
