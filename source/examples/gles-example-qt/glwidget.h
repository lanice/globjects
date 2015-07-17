#pragma once

#include <QWidget>

class GLWidget : public QWidget
{
    Q_OBJECT
public:
    GLWidget();

    virtual QPaintEngine * paintEngine() const override;
protected:
    virtual void paintEvent(QPaintEvent *pe) override;
    virtual void resizeEvent(QResizeEvent * re) override;
    virtual void showEvent(QShowEvent * se) override;

    bool m_initialized;
public slots:
    void initialize();
    void uninitialize();
};
