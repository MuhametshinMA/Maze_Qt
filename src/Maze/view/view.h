#ifndef VIEW_H
#define VIEW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>

#include "icontroller.h"
#include "paintwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget* parent = nullptr);
  ~View();

 private slots:
  void CaveCreate();
  void CaveGenerate();
  void NextStepCave();
  void MazeCreate();
  void OpenFileButtonClick();
  void SaveFileButtonClick();
  //  void SaveMazeButtonClick();

 private:
  const QSize kFieldSize = QSize(502, 502);

  void AutoGen();
  void ViewConnects();
  void InitPaintWidget();
  void InitTimer();

  std::unique_ptr<Ui::View> ui_;
  std::shared_ptr<IController> ctrl_;
  PaintWidget* paint_widget_ = nullptr;
  QTimer* timer_;
  bool autogen_;
  bool ormaze_, orcave_;
};

#endif  // VIEW_H
