#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tempo = new QTimer(this);

    connect(tempo, &QTimer::timeout, this, &MainWindow::geraTabela);

    tempo->start(1000);
}

void MainWindow::geraTabela()
{
    ui->list_process->clear();
    std::vector<std::vector<std::string>> proc = process.get_processors();

    int linhas = static_cast<int>(proc.size());
    int colunas = static_cast<int>(proc.at(0).size());

    ui->list_process->setColumnCount(colunas);
    ui->list_process->setRowCount(linhas);
    ui->list_process->verticalHeader()->setVisible(false);

    QStringList titulos;
    for (int i = 0; i < colunas; i++) {
        titulos.append(QString::fromStdString(proc.at(0).at(i)));
    }
    ui->list_process->setHorizontalHeaderLabels(titulos);

    QTableWidgetItem *item;
    for (int i = 1; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            item = new QTableWidgetItem(QString::fromStdString(proc.at(i).at(j)));
            ui->list_process->setItem(i - 1, j, item);
        }
    }

    ui->list_process->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_filter_clicked()
{
    QString text = ui->filter_text->text();
    process.setProcess_nome(text.isEmpty() ? "null" : text.toStdString());
}

void MainWindow::on_b_kill_clicked()
{
    int pid = ui->pid_text_all->text().toInt();
    process.kill_process(pid);
    ui->pid_text_all->clear();
}

void MainWindow::on_b_stop_clicked()
{
    int pid = ui->pid_text_all->text().toInt();
    process.stop_process(pid);
}

void MainWindow::on_b_cont_clicked()
{
    int pid = ui->pid_text_all->text().toInt();
    process.cont_process(pid);
}

void MainWindow::on_b_priority_clicked()
{
    int pid = ui->pid_text_priority->text().toInt();
    int prio = ui->priority_text->text().toInt();
    process.set_prio(pid, prio);
}

void MainWindow::on_b_cpuset_clicked()
{
    std::string pid = ui->pid_text_cpu->text().toStdString();
    std::string cpu = ui->cpu_text->text().toStdString();
    process.set_CPU(pid, cpu);
}