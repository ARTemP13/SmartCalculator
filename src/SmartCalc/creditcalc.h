#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QMainWindow>

#include "diff_calc_table.h"

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QMainWindow {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private:
  Ui::CreditCalc *ui;
  Diff_calc_table *windows_diff_table;
 signals:
  void credit();
  void signal(QVector<double> sum_months, double main_dept);

 private slots:
  void on_button_back_clicked();
  void on_pushButton_clicked();
};

#endif  // CREDITCALC_H
