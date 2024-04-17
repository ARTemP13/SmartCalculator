#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
  // button back
  QPixmap pixmap(":/back.png");
  ui->button_back->setIcon(pixmap);
  ui->button_back->setIconSize(QSize(30, 30));

  windows_diff_table = new Diff_calc_table;
  connect(this, &CreditCalc::signal, windows_diff_table,
          &Diff_calc_table::slot);
  ui->sum_credit->setText("");
  ui->period->setText("");
  ui->rate->setText("");
  ui->screen->setText("0");
  ui->sum_credit->setWordWrapMode(QTextOption::NoWrap);
  ui->period->setWordWrapMode(QTextOption::NoWrap);
  ui->rate->setWordWrapMode(QTextOption::NoWrap);

  setWindowTitle("Кредитный калькулятор");
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_button_back_clicked() {
  ui->sum_credit->setText("");
  ui->period->setText("");
  ui->rate->setText("");
  ui->screen->setText("0");
  this->close();
  emit credit();
}
int CheckingString(QString str) {  // 1 - Fail 0 - Success
  int flag = 0;
  for (int i = 0; i < str.size(); i++) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
    } else {
      flag = 1;
      break;
    }
  }
  return flag;
}

void CreditCalc::on_pushButton_clicked() {
  ui->screen->setText("");
  QString sum_credit1 = ui->sum_credit->toPlainText();
  QString period1 = ui->period->toPlainText();
  QString rate1 = ui->rate->toPlainText();
  int flag1 = CheckingString(sum_credit1);
  int flag2 = CheckingString(period1);
  int flag3 = CheckingString(rate1);
  if (flag1 == 0 && flag2 == 0 && flag3 == 0) {
    double sum_credit2 = sum_credit1.toDouble();
    double period2 = period1.toDouble();
    double rate2 = rate1.toDouble();
    QString cbox = ui->comboBox->currentText();
    if (cbox == "лет") {
      period2 *= 12;
    }
    if (period2 > 0 && period2 <= 600 && rate2 > 0 && rate2 <= 999 &&
        sum_credit2 < 1e18) {
      if (ui->ann->isChecked()) {
        rate2 = rate2 / (100.0 * rate2);
        double res =
            (sum_credit2 * rate2) / (1.0 - pow((1.0 + rate2), -period2));
        QString res1 = QString::number(res);
        ui->screen->setText(res1);
      } else {
        QVector<double> sum_months;
        rate2 = rate2 / 12.0;
        double ost = sum_credit2;
        for (int i = 0; i < period2; i++) {
          double res = ((ost)*rate2) / 100.0 + (sum_credit2 / period2);
          sum_months.push_back(res);
          ost -= (sum_credit2 / period2);
        }

        windows_diff_table->show();
        emit signal(sum_months, (sum_credit2 / period2));
      }
    } else {
      ui->screen->setText("error");
    }

  } else {
    ui->screen->setText("error");
  }
}
