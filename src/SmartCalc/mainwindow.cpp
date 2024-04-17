#include "mainwindow.h"

#include <QMessageBox>

#include "graphics.h"
#include "ui_mainwindow.h"

extern "C" {
#include "smartcalc.h"
};

extern "C" Stack *Parsing(char *str);
extern "C" Stack *RPN(Stack *input);
extern "C" Stack *pop_back(Stack *stack);
extern "C" Stack *reverse_stack(Stack *stack);
extern "C" Stack *push_back(double value, int priority, int type, Stack *stack);
extern "C" int check_braces(char *str);
extern "C" double calculating_graph(Stack input, double x);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->frame->setVisible(false);
  // Инициализация окна для графиков
  window_graph = new Graphics;
  connect(this, &MainWindow::signal, window_graph, &Graphics::slot);
  setWindowTitle("Калькулятор");

  connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_minusone, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_delete_all, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_braces_left, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_braces_right, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(function()));

  // Icon for button
  QPixmap pixmap1(":/credit1.png");
  ui->button_credit->setIcon(pixmap1);
  ui->button_credit->setIconSize(QSize(30, 30));
  QPixmap pixmap2(":/deposit1.png");
  ui->button_deposit->setIcon(pixmap2);
  ui->button_deposit->setIconSize(QSize(30, 30));
  // panel1
  ui->panel->setVisible(false);
  // Init window creditcalc
  window_credit = new CreditCalc;
  connect(window_credit, &CreditCalc::credit, this, &MainWindow::show);
}
int flag = 0;
int sigh_braces = 0;
int flag_delete = 0;
QString str = "";
QString current_str = "";
int visible_panel = 0;

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_number() {
  QPushButton *button = (QPushButton *)sender();
  if (flag_delete == -1 || flag_delete == 0 || flag_delete == 1 ||
      flag_delete == 2 || flag_delete == 3 || flag_delete == 7 ||
      flag_delete == 6) {
    sigh_braces = 0;
    flag_delete = 1;
    current_str += button->text();
    ui->screen->setText(str + current_str);
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  if (flag_delete == 1) {
    if (!(current_str.contains('.'))) {
      current_str += ".";
      ui->screen->setText(str + current_str);
      flag_delete = -1;
    }
  }
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "+/-" && str.size() == 0) {
    if (current_str[0] == '-') {
      for (int i = 0; i < current_str.size() - 1; i++) {
        current_str[i] = current_str[i + 1];
      }
      current_str.chop(1);
    } else {
      current_str += '1';
      for (int i = 0; i < current_str.size() - 1; i++) {
        current_str[current_str.size() - 1 - i] =
            current_str[current_str.size() - 2 - i];
      }
      current_str[0] = '-';
    }
    ui->screen->setText(current_str);

  } else if (button->text() == "+" &&
             (flag_delete == 1 || flag_delete == 4 || flag_delete == 5)) {
    ui->screen->setText(ui->screen->text() + " + ");
    str += current_str + " + ";
    flag = 1;
    flag_delete = 2;
    current_str = "";
  } else if (button->text() == "-" &&
             (flag_delete == 0 || flag_delete == 1 || flag_delete == 3 ||
              flag_delete == 4 || flag_delete == 5 || flag_delete == 7)) {
    if (sigh_braces == 1 || flag_delete == 0) {
      ui->screen->setText(str + "-");
      str += current_str + "-";
      flag = 1;
      sigh_braces = 0;
      flag_delete = 6;
    } else {
      ui->screen->setText(ui->screen->text() + " - ");
      str += current_str + " - ";
      flag = 1;
      flag_delete = 2;
    }
    current_str = "";
  } else if (button->text() == "÷" &&
             (flag_delete == 1 || flag_delete == 4 || flag_delete == 5)) {
    ui->screen->setText(ui->screen->text() + " / ");
    str += current_str + " / ";
    flag = 1;
    current_str = "";
    flag_delete = 2;
  } else if (button->text() == "×" &&
             (flag_delete == 1 || flag_delete == 4 || flag_delete == 5)) {
    ui->screen->setText(ui->screen->text() + " * ");
    str += current_str + " * ";
    flag = 1;
    current_str = "";
    flag_delete = 2;
  } else if (button->text() == "^" &&
             (flag_delete == 1 || flag_delete == 4 || flag_delete == 5)) {
    ui->screen->setText(ui->screen->text() + "^");
    str += current_str + "^";
    flag = 1;
    current_str = "";
    flag_delete = 6;
  } else if (button->text() == "%" &&
             (flag_delete == 1 || flag_delete == 4 || flag_delete == 5)) {
    ui->screen->setText(ui->screen->text() + " % ");
    str += current_str + " % ";
    flag = 1;
    current_str = "";
    flag_delete = 2;
  } else if (button->text() == "AC") {
    str = "";
    current_str = "";
    flag_delete = 0;
    ui->screen->setText("0");
  } else if (button->text() == "(" &&
             (flag_delete == 0 || flag_delete == 2 || flag_delete == 3 ||
              flag_delete == 7 || flag_delete == 6)) {
    ui->screen->setText(str + "(");
    str += "(";
    sigh_braces = 1;
    current_str = "";
    flag_delete = 3;
  } else if (button->text() == ")" &&
             (flag_delete == 1 || flag_delete == 4 || flag_delete == 5)) {
    ui->screen->setText(ui->screen->text() + ")");
    str += current_str + ")";
    current_str = "";
    sigh_braces = 0;
    flag = 0;
    flag_delete = 4;
  }
}

void MainWindow::on_pushButton_delete_clicked() {
  int transition = 0;
  if (flag_delete == 1) {
    current_str.chop(1);
    ui->screen->setText(str + current_str);
    if (current_str.size() == 0) {
      transition = 1;
    }
  } else if (flag_delete == 2) {
    str.chop(3);
    if (str.size() != 0) {
      ui->screen->setText(str);
    }
    transition = 1;
  } else if (flag_delete == 3) {
    str.chop(1);
    ui->screen->setText(str);
    transition = 1;
  } else if (flag_delete == 4) {
    str.chop(1);
    ui->screen->setText(str);
    transition = 1;
  } else if (flag_delete == 5) {
    str.chop(1);
    ui->screen->setText(str);
    transition = 1;
  } else if (flag_delete == 6) {
    str.chop(1);
    if (str.size() != 0) {
      ui->screen->setText(str);
    }
    transition = 1;
  } else if (flag_delete == 7) {
    int j = str.size() - 2;
    int k = 1;
    while (str[j] != '(' && str[j] != ' ' && j > 0) {
      j--;
      k++;
    }
    if (j == 0) k++;
    str.chop(k);
    if (str.size() != 0) {
      ui->screen->setText(str);
    }
    transition = 1;
  }
  if (str.size() + current_str.size() == 0) {
    ui->screen->setText("0");
    flag_delete = 0;
  }
  if (transition == 1 && str.size() > 0) {
    int j = str.size() - 1;
    if (str[j] == 'X') {
      flag_delete = 5;
    } else if (str[j] == ' ') {
      flag_delete = 2;
    } else if (str[j] >= '0' && str[j] <= '9') {
      flag_delete = 1;
      int count = 0;
      int r = j;
      while ((str[j] >= 'a' && str[j] <= 'z') || str[j] == '.') {
        j--;
        if (j == 0) break;
      }
      int l = j;
      if (j != 0) j++;
      count = r - l + 1;
      current_str = "";
      while (j <= r) {
        current_str += str[j];
        j++;
      }
      str.chop(count);
    } else if (j != 0 && str[j - 1] >= 'a' && str[j - 1] <= 'z' &&
               str[j] == '(') {
      flag_delete = 7;
    } else if (str[j] == '(') {
      flag_delete = 3;
      sigh_braces = 1;
    } else if (str[j] == ')') {
      flag_delete = 4;
      sigh_braces = 0;
      flag = 0;
    } else if (str[j] == '-' || str[j] == '+' || str[j] == '^') {
      flag_delete = 6;
    }
  }
}

void MainWindow::on_pushButton_x_clicked() {
  if ((flag_delete == 0 || flag_delete == 2 || flag_delete == 3 ||
       flag_delete == 7 || flag_delete == 6)) {
    ui->screen->setText(str + "X");
    str += current_str + "X";
    current_str = "";
    flag = 0;
    sigh_braces = 0;
    flag_delete = 5;
  }
}

void MainWindow::on_pushButton_pi_clicked() {
  if (flag_delete == 0 || flag_delete == 2 || flag_delete == 3 ||
      flag_delete == 7) {
    ui->screen->setText(str + "3.14159265359");
    current_str = "3.14159265359";
    flag = 0;
    sigh_braces = 0;
    flag_delete = 1;
  }
}

void MainWindow::function() {
  if (flag_delete == 0 || flag_delete == 2 || flag_delete == 3 ||
      flag_delete == 7 || flag_delete == 6) {
    QPushButton *button = (QPushButton *)sender();

    if (button->text() == "cos") {
      ui->screen->setText(str + current_str + "cos(");
      str += current_str + "cos(";
    } else if (button->text() == "sin") {
      ui->screen->setText(str + current_str + "sin(");
      str += current_str + "sin(";
    } else if (button->text() == "tan") {
      ui->screen->setText(str + current_str + "tan(");
      str += current_str + "tan(";
    } else if (button->text() == "asin") {
      ui->screen->setText(str + current_str + "asin(");
      str += current_str + "asin(";
    } else if (button->text() == "atan") {
      ui->screen->setText(str + current_str + "atan(");
      str += current_str + "atan(";
    } else if (button->text() == "acos") {
      ui->screen->setText(str + current_str + "acos(");
      str += current_str + "acos(";
    } else if (button->text() == "√x") {
      ui->screen->setText(str + current_str + "sqrt(");
      str += current_str + "sqrt(";
    } else if (button->text() == "ln") {
      ui->screen->setText(str + current_str + "ln(");
      str += current_str + "ln(";
    } else if (button->text() == "log") {
      ui->screen->setText(str + current_str + "log(");
      str += current_str + "log(";
    }
    current_str = "";
    flag = 0;
    sigh_braces = 1;
    flag_delete = 7;
  }
}

Stack *pol1 = (Stack *)malloc(sizeof(Stack));
void MainWindow::on_pushButton_equal_clicked() {
  str += current_str;
  QByteArray byteArray = str.toUtf8();
  char *str1 = byteArray.data();
  Stack *stack1 = (Stack *)malloc(sizeof(Stack));
  stack1 = Parsing(str1);
  Stack *pol = (Stack *)malloc(sizeof(Stack));
  pol = RPN(stack1);
  pol1 = pol;
  double result = 0;
  if (str.contains('X') == 0) result = calculating_graph(*pol, 0);
  if ((result == S21_NAN || check_braces(str1) == 1) &&
      str.contains('X') == 0) {
    current_str = "";
    str = "";
    ui->screen->setText("error");
    flag_delete = 8;
  } else {
    if (str.contains('X') == 1) {
      ui->frame->setVisible(true);
      ui->value_x->setText("0");
    } else {
      QString result1 = QString::number(result, 'g', 15);
      current_str = result1;
      str = "";
      ui->screen->setText(result1);
    }
  }
}

void MainWindow::on_button_option_clicked() {
  if (visible_panel == 0) {
    ui->panel->setVisible(true);
    visible_panel = 1;
  } else {
    ui->panel->setVisible(false);
    visible_panel = 0;
  }
}

void MainWindow::on_button_credit_clicked() {
  window_credit->show();
  this->close();
}

void MainWindow::on_paint_graph_clicked() {
  ui->frame->setVisible(false);
  window_graph->show();
  emit signal(pol1);
}

void MainWindow::on_calculate_clicked() {
  QString x = ui->value_x->toPlainText();
  int flag = 0;
  int dot = 0;
  for (int i = 0; i < x.size(); i++) {
    if ((x[i] >= '0' && x[i] <= '9')) {
    } else if (x[i] == '.')
      dot++;
    else
      flag = 1;
  }
  double x1 = 0;
  if (flag == 0 && dot <= 1) {
    x1 = x.toDouble();
    double result_final = calculating_graph(*pol1, x1);
    QString result1 = QString::number(result_final, 'g', 15);
    current_str = result1;
    str = "";
    ui->screen->setText(result1);
    ui->frame->setVisible(false);
  } else {
    ui->value_x->setText("error");
  }
}

void MainWindow::on_pushButton_clicked() { ui->frame->setVisible(false); }
