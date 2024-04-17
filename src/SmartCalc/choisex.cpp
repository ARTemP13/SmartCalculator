#include "choisex.h"

#include "ui_choisex.h"

ChoiseX::ChoiseX(QWidget *parent) : QWidget(parent), ui(new Ui::ChoiseX) {
  ui->setupUi(this);
}

ChoiseX::~ChoiseX() { delete ui; }
