#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Tree scene;

private slots:
    void on_Add_clicked();

    void on_Delete_clicked();

    void on_Search_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
