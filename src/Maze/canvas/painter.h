#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include <QWidget>
#include <memory>

class IPainter {
 public:
  virtual ~IPainter() = default;
  virtual void drawLine(float x1, float y1, float x2, float y2) const = 0;
  virtual void drawPoint(float x, float y) const = 0;
  virtual void drawRect(float x, float y, float width, float height) const = 0;
  virtual void setPen(const QPen& pen) const = 0;
  virtual void setBrush(const QColor& brush) const = 0;
};

class FigurePainter : public IPainter {
 public:
  FigurePainter(QWidget* parent) : q_painter_(parent) {}

  void drawLine(float x1, float y1, float x2, float y2) const override {
    const_cast<QPainter&>(q_painter_).drawLine(x1, y1, x2, y2);
  }

  void drawPoint(float x, float y) const override {
    const_cast<QPainter&>(q_painter_).drawPoint(x, y);
  }

  void drawRect(float x, float y, float width, float height) const override {
    const_cast<QPainter&>(q_painter_).drawRect(x, y, width, height);
  }

  void setPen(const QPen& pen) const override {
    const_cast<QPainter&>(q_painter_).setPen(pen);
  }

  void setBrush(const QColor& brush) const override {
    const_cast<QPainter&>(q_painter_).setBrush(brush);
  }

 private:
  QPainter q_painter_;
};

#endif  // PAINTER_H
