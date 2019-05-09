#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Button_is_clicked();
    void Resect_is_clicked();
    void cat_move(int x,int y);
    void init_graph();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
