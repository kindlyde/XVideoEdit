#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUi.h"

class XVideoUi : public QWidget
{
	Q_OBJECT

public:
	XVideoUi(QWidget *parent = Q_NULLPTR);

public slots:
	void open();

private:
	Ui::XVideoUiClass ui;
};
