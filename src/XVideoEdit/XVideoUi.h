#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUi.h"

class XVideoUi : public QWidget
{
	Q_OBJECT

public:
	XVideoUi(QWidget *parent = Q_NULLPTR);
	void timerEvent(QTimerEvent *e);

public slots:
	void open();
	void sliderMove();
	void sliderPress();
	void sliderRelease();
	void set();
	void exportVideo();
	void exportEnd();

private:
	Ui::XVideoUiClass ui;
};
