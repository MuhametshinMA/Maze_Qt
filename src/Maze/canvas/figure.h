#ifndef FIGURE_H
#define FIGURE_H

#include "painter.h"

class IFigure {
 public:
  virtual void draw(IPainter* painter) const = 0;
  virtual ~IFigure() = default;

  void setPenColor(const QColor& color) { color_ = color; }
  void setPenSize(int size) { size_ = size; }

 protected:
  QColor color_;
  int size_;
};

class Point : public IFigure {
 public:
  Point(int x, int y, const QColor& color, int size) : x_(x), y_(y) {
    this->setPenColor(color);
    this->setPenSize(size);
  }
  void draw(IPainter* painter) const override {
    painter->setPen(QPen(this->color_, this->size_));
    painter->drawPoint(x_, y_);
  }

  int GetX() { return x_; }
  int GetY() { return y_; }

 private:
  int x_;
  int y_;
};

class Line : public IFigure {
 public:
  Line(int x1, int y1, int x2, int y2, const QColor& color, int size)
      : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {
    setPenColor(color);
    setPenSize(size);
  }

  void draw(IPainter* painter) const override {
    painter->setPen(QPen(color_, size_));
    painter->drawLine(x1_, y1_, x2_, y2_);
  }

 private:
  int x1_;
  int y1_;
  int x2_;
  int y2_;
};

class Rectangle : public IFigure {
 public:
  Rectangle(int x, int y, int width, int height, const QColor& color, int size)
      : x_(x), y_(y), width_(width), height_(height) {
    setPenColor(color);
    setPenSize(size);
  }

  void draw(IPainter* painter) const override {
    painter->setPen(QPen(color_, size_));
    painter->setBrush(color_);
    painter->drawRect(x_, y_, width_, height_);
  }

 private:
  int x_;
  int y_;
  int width_;
  int height_;
};

#endif  // FIGURE_H
