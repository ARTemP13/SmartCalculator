#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QDialog>
#include <QVector>
extern "C" {
#include "smartcalc.h"
};

namespace Ui {
class Graphics;
}

class Graphics : public QDialog {
  Q_OBJECT

 public:
  explicit Graphics(QWidget *parent = nullptr);
  ~Graphics();
 public slots:
  void slot(Stack *pol);

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Graphics *ui;
};

#endif  // GRAPHICS_H
