#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <creditcalc.h>
#include <graphics.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graphics *window_graph;
  CreditCalc *window_credit;
 signals:
  void signal(Stack *pol);
 private slots:
  void digits_number();
  void on_pushButton_dot_clicked();
  void operations();
  void on_pushButton_delete_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_pi_clicked();
  void function();
  void on_pushButton_equal_clicked();
  void on_button_option_clicked();
  void on_button_credit_clicked();
  void on_paint_graph_clicked();
  void on_calculate_clicked();
  void on_pushButton_clicked();
};

#endif  // MAINWINDOW_H
