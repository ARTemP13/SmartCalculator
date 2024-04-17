#include "graphics.h"

#include "ui_graphics.h"

extern "C" {
#include "smartcalc.h"
};

extern "C" double calculating_graph(Stack input, double x);

Graphics::Graphics(QWidget *parent) : QDialog(parent), ui(new Ui::Graphics) {
  ui->setupUi(this);
  setWindowTitle("График");
}

Graphics::~Graphics() { delete ui; }
Stack *stack_rpn;

void Graphics::slot(Stack *pol) {
  ui->textEdit_x0->setPlainText("-10");
  ui->textEdit_x1->setPlainText("10");
  ui->textEdit_y0->setPlainText("-10");
  ui->textEdit_y1->setPlainText("10");
  stack_rpn = pol;
  double result = 0;
  QVector<double> x;
  QVector<double> y;
  for (double i = -10; i < 10;) {
    result = calculating_graph(*pol, i);
    if (result != S21_NAN) {
      x.push_back(i);
      y.push_back(result);
    }
    i += 0.0005;
  }
  ui->widget->clearGraphs();
  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void Graphics::on_pushButton_clicked() {
  ui->widget->clearGraphs();
  QString x0_str = (ui->textEdit_x0)->toPlainText();
  double x0_num = x0_str.toDouble();
  QString x1_str = (ui->textEdit_x1)->toPlainText();
  double x1_num = x1_str.toDouble();
  QString y0_str = (ui->textEdit_y0)->toPlainText();
  double y0_num = y0_str.toDouble();
  QString y1_str = (ui->textEdit_y1)->toPlainText();
  double y1_num = y1_str.toDouble();
  for (int i = 0; i < x0_str.size(); i++) {
    if ((x0_str[i] >= '0' && x0_str[i] <= '9') || x0_str[i] == '-') {
    } else {
    }
  }
  double result = 0;
  QVector<double> x;
  QVector<double> y;
  for (double i = x0_num; i < x1_num;) {
    result = calculating_graph(*stack_rpn, i);
    if (result != S21_NAN) {
      x.push_back(i);
      y.push_back(result);
    }
    if (abs(x0_num * x1_num) <= 10000) i += 0.0005;
    if (abs(x0_num * x1_num) >= 10000 && abs(x0_num * x1_num) <= 1000000)
      i += 0.01;
    if (abs(x0_num * x1_num) >= 1000000 && abs(x0_num * x1_num) <= 10000000)
      i += 0.1;
    if (abs(x0_num * x1_num) >= 10000000) i += 1;
  }
  ui->widget->xAxis->setRange(x0_num, x1_num);
  ui->widget->yAxis->setRange(y0_num, y1_num);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}
