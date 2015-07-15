#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

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
