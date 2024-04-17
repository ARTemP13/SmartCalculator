#ifndef CHOISEX_H
#define CHOISEX_H

#include <QWidget>

namespace Ui {
class ChoiseX;
}

class ChoiseX : public QWidget {
  Q_OBJECT

 public:
  explicit ChoiseX(QWidget *parent = nullptr);
  ~ChoiseX();

 private:
  Ui::ChoiseX *ui;
};

#endif  // CHOISEX_H
