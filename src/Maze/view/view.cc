#include "view.h"

#include "controllerfactory.h"
#include "ui_view.h"

View::View(QWidget* parent)
    : QMainWindow{parent}, ui_{std::make_unique<Ui::View>()} {
  ui_->setupUi(this);
  InitTimer();
  ViewConnects();
  ctrl_ = std::make_shared<MazeControllerFactory>()->MakeController(kFieldSize);
  InitPaintWidget();
}

View::~View() {
  if (paint_widget_) delete paint_widget_;
}

void View::MazeCreate() {
  ctrl_ = std::make_shared<MazeControllerFactory>()->MakeController(kFieldSize);
  InitPaintWidget();
  ctrl_->Generate(ui_->sBRowsMaze->value(), ui_->sBColsMaze->value());
}

void View::CaveCreate() {
  ctrl_ = std::make_shared<CaveControllerFactory>()->MakeController(kFieldSize);
  InitPaintWidget();
  ctrl_->Generate(CaveData(ui_->dSBChance->value(), ui_->sBRowsCave->value(),
                           ui_->sBColsCave->value()));
}

void View::CaveGenerate() {
  timer_->setInterval(ui_->sBFrequency->value() * 100);
  if (ctrl_) ctrl_->LastEvolution(ui_->sBBirth->value(), ui_->sBDeath->value());
}

void View::NextStepCave() {
  if (ctrl_)
    ctrl_->NextStepEvolution(ui_->sBStepgen->value(), ui_->sBBirth->value(),
                             ui_->sBDeath->value());
}

void View::InitPaintWidget() {
  if (paint_widget_) {
    ui_->layout->removeWidget(paint_widget_);
    delete paint_widget_;
  }
  paint_widget_ = new PaintWidget(ctrl_);
  paint_widget_->setStyleSheet("background-color: outset;");
  paint_widget_->resize(kFieldSize);
  ui_->layout->addWidget(paint_widget_);
}

void View::InitTimer() {
  timer_ = new QTimer(this);
  timer_->setInterval(ui_->sBFrequency->value() * 100);
}

void View::AutoGen() {
  autogen_ == true ? autogen_ = false : autogen_ = true;
  autogen_ == true ? ui_->pBtCaveGenerate->setText("Auto generation /ON")
                   : ui_->pBtCaveGenerate->setText("Auto generation /OFF");
  autogen_ == true ? timer_->start() : timer_->stop();
}

void View::OpenFileButtonClick() {
  if (ctrl_) {
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                QDir::homePath(), tr("*"));
    ctrl_->FileOpen(path.toStdString());
  }
}

void View::SaveFileButtonClick() {
  if (ctrl_) {
    ctrl_->FileSave(
        (QFileDialog::getSaveFileName(0, "Сохранить как...",
                                      QDir::currentPath(), "TXT (*.txt)"))
            .toStdString());
  }
}

void View::ViewConnects() {
  connect(ui_->pBtCaveGenerate, &QPushButton::clicked, this,
          [=]() { AutoGen(); });

  connect(timer_, &QTimer::timeout, this, [=]() { CaveGenerate(); });

  connect(ui_->pBtCaveCreate, &QPushButton::clicked, this, &View::CaveCreate);

  connect(ui_->pBtNextGenerate, &QPushButton::clicked, this,
          &View::NextStepCave);
  connect(ui_->pBtOpenFile, &QPushButton::clicked, this,
          &View::OpenFileButtonClick);
  connect(ui_->pBtSave, &QPushButton::clicked, this,
          &View::SaveFileButtonClick);
  connect(ui_->pBtMazeGenerate, &QPushButton::clicked, this, &View::MazeCreate);
}
