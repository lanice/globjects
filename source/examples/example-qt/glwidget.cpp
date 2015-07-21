#include "glwidget.h"

#include <QPaintEvent>

#include "context.h"
#include "render.h"

GLWidget::GLWidget()
: m_displayInitialized(false)
, m_initialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget()
{
    if (m_displayInitialized)
    {
        ::uninitializeDisplay();
    }
}

void GLWidget::showEvent(QShowEvent *)
{
    if (!m_initialized)
    {
        initialize();
    }
}

void GLWidget::paintEvent(QPaintEvent * /*pe*/)
{
    if (!m_initialized)
    {
        initialize();
    }

    ::makeCurrent();
    ::render();
    ::waitClient();
    ::swapBuffers();
    ::doneCurrent();
}

void GLWidget::resizeEvent(QResizeEvent * re)
{
    if (!m_initialized)
    {
        initialize();
    }

    ::makeCurrent();
    ::resize(re->size().width(), re->size().height());
    ::doneCurrent();

    update();
}

void GLWidget::initialize()
{
    if (!m_displayInitialized)
    {
        ::initializeDisplay(winId());
        m_displayInitialized = true;
    }

#ifdef GLOBJECTS_GL_BINDING
    ::createGLContext();
#else
    ::createGLESContext();
#endif
    ::makeCurrent();
    ::initialize();
    ::doneCurrent();

    m_initialized = true;
}

void GLWidget::uninitialize()
{
    ::makeCurrent();
    ::uninitialize();
    ::doneCurrent();
    ::releaseContext();

    m_initialized = false;
}

QPaintEngine * GLWidget::paintEngine() const
{
    return nullptr;
}
