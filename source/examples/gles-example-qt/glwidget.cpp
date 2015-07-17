#include "glwidget.h"

#include <QPaintEvent>
#include <QResizeEvent>

#include "context.h"
#include "rendergles.h"

GLWidget::GLWidget()
: m_initialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
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
    ::renderGLES();
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
    ::resizeGLES(re->size().width(), re->size().height());
    ::doneCurrent();

    update();
}

void GLWidget::initialize()
{
    ::createGLESContext(winId());
    ::initializeGLES();
    ::doneCurrent();

    m_initialized = true;
}

void GLWidget::uninitialize()
{
    ::makeCurrent();
    ::uninitializeGLES();
    ::doneCurrent();
    ::releaseContext();

    m_initialized = false;
}

QPaintEngine * GLWidget::paintEngine() const
{
    return nullptr;
}
