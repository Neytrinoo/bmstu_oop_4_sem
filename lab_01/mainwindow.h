#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>

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
    void on_load_file_btn_clicked();

    void on_do_transfer_btn_clicked();

    void on_do_turn_btn_clicked();

    void on_do_scale_btn_clicked();

    void on_save_as_btn_clicked();

private:
    Ui::MainWindow *ui;
//    void setInputSettings();
    QDoubleValidator *double_validator_;
};
#endif // MAINWINDOW_H
