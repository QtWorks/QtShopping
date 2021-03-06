#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonOrder_clicked();

    void on_pushButtonCash_clicked();

    void on_pushButtonBuy_clicked();

    void on_pushButtonHistory_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
