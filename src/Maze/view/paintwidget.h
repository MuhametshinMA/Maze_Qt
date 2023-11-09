#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QMouseEvent>
#include <QWidget>
#include <vector>

#include "icontroller.h"

class PaintWidget : public QWidget {
 public:
  PaintWidget(std::shared_ptr<IController> ctrl_);

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

 private:
  std::shared_ptr<IController> controller_;
};

#endif  // PAINTWIDGET_H
