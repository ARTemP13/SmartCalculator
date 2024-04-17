#ifndef DIFF_CALC_TABLE_H
#define DIFF_CALC_TABLE_H

#include <QStandardItem>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class Diff_calc_table;
}

class Diff_calc_table : public QWidget {
  Q_OBJECT

 public:
  explicit Diff_calc_table(QWidget *parent = nullptr);
  ~Diff_calc_table();

 private:
  Ui::Diff_calc_table *ui;
  QStandardItemModel *model;
 public slots:
  void slot(QVector<double> sum_month, double main_dept);
};

#endif  // DIFF_CALC_TABLE_H
