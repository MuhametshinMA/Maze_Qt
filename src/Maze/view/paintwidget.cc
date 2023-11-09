#include "paintwidget.h"

PaintWidget::PaintWidget(std::shared_ptr<IController> ctrl_)
    : controller_(ctrl_) {}

void PaintWidget::paintEvent(QPaintEvent* event) {
  FigurePainter painter(this);
  for (const auto& it : controller_->GetFigures()) {
    it->draw(&painter);
  }
  update();
}

void PaintWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    controller_->SetPoint(event->pos().y(), event->pos().x());
    update();
  } else if (event->button() == Qt::RightButton) {
    controller_->ClearPath();
  }
}
