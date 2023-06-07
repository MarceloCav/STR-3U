#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <processors.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void geraTabela();

    void on_b_filter_clicked();

    void on_b_kill_clicked();

    void on_b_stop_clicked();

    void on_b_cont_clicked();

    void on_b_priority_clicked();

    void on_b_cpuset_clicked();

private:
    Ui::MainWindow *ui;
    processors process;
    QTimer *tempo;
};
#endif // MAINWINDOW_H
