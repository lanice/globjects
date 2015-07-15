#include "mainwindow.h"

#include <QPaintEvent>
#include <QResizeEvent>

#include "context.h"
#include "rendergles.h"

MainWindow::MainWindow()
: m_initialized(false)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_PaintOnScreen);
}

void MainWindow::showEvent(QShowEvent *)
{
    if (!m_initialized)
    {
        initialize();
    }
}

void MainWindow::paintEvent(QPaintEvent * /*pe*/)
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

void MainWindow::resizeEvent(QResizeEvent * re)
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

void MainWindow::initialize()
{
    ::createGLESContext(winId());
    ::initializeGLES();
    ::doneCurrent();

    m_initialized = true;
}

void MainWindow::uninitialize()
{
    ::makeCurrent();
    ::uninitializeGLES();
    ::doneCurrent();
    ::releaseContext();

    m_initialized = false;
}

QPaintEngine * MainWindow::paintEngine() const
{
    return nullptr;
}
