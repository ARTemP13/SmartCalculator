#include "diff_calc_table.h"

#include <QDate>
#include <QStandardItem>

#include "ui_diff_calc_table.h"

Diff_calc_table::Diff_calc_table(QWidget *parent)
    : QWidget(parent), ui(new Ui::Diff_calc_table) {
  ui->setupUi(this);
  ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  setWindowTitle("Дифференцированный кредит");
}

Diff_calc_table::~Diff_calc_table() { delete ui; }

void Diff_calc_table::slot(QVector<double> sum_month, double main_sum) {
  model = new QStandardItemModel(ui->tableView);
  model->setHorizontalHeaderLabels(
      {"Месяц", "Сумма платежа", "Основной долг", "Платеж по процентам"});
  QDate currentDate = QDate::currentDate();
  int year = currentDate.year();
  int month = currentDate.month();
  if (month == 12) {
    month = 0;
    year++;
  }
  double sum_dept = 0;
  double sum_main_dept = 0;
  double sum_precent_dept = 0;
  for (int i = 0; i < (int)sum_month.size() + 1; ++i) {
    QList<QStandardItem *> items;
    if (i == (int)sum_month.size()) {
      items.append(new QStandardItem("Итог"));
      items.append(
          new QStandardItem(QString::number(sum_dept, 'f', 0) + "₽"));
      items.append(
          new QStandardItem(QString::number(sum_main_dept, 'f', 0) + "₽"));
      items.append(
          new QStandardItem(QString::number(sum_precent_dept, 'f', 0) + "₽"));
    } else {
      if (month == 0)
        items.append(
            new QStandardItem(QString("Январь " + QString::number(year))));
      else if (month == 1)
        items.append(
            new QStandardItem(QString("Февраль " + QString::number(year))));
      else if (month == 2)
        items.append(
            new QStandardItem(QString("Март " + QString::number(year))));
      else if (month == 3)
        items.append(
            new QStandardItem(QString("Апрель " + QString::number(year))));
      else if (month == 4)
        items.append(
            new QStandardItem(QString("Май " + QString::number(year))));
      else if (month == 5)
        items.append(
            new QStandardItem(QString("Июнь " + QString::number(year))));
      else if (month == 6)
        items.append(
            new QStandardItem(QString("Июль " + QString::number(year))));
      else if (month == 7)
        items.append(
            new QStandardItem(QString("Август " + QString::number(year))));
      else if (month == 8)
        items.append(
            new QStandardItem(QString("Сентябрь " + QString::number(year))));
      else if (month == 9)
        items.append(
            new QStandardItem(QString("Октябрь " + QString::number(year))));
      else if (month == 10)
        items.append(
            new QStandardItem(QString("Ноябрь " + QString::number(year))));
      else if (month == 11)
        items.append(
            new QStandardItem(QString("Декабрь " + QString::number(year))));
      month++;
      if (month == 12) {
        month = 0;
        year++;
      }
      items.append(new QStandardItem(QString::number(sum_month[i], 'f', 0)));
      sum_dept += sum_month[i];
      items.append(new QStandardItem(QString::number(main_sum)));
      sum_main_dept += main_sum;
      items.append(
          new QStandardItem(QString::number(sum_month[i] - main_sum, 'f', 0)));
      sum_precent_dept += sum_month[i] - main_sum;
    }
    model->appendRow(items);
  }
  ui->tableView->setModel(model);
  ui->tableView->show();
}
