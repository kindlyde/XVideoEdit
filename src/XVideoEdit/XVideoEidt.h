#pragma once
#include <QOpenGLWidget>
class XVideoEidt :public QOpenGLWidget
{
public:
	XVideoEidt(QWidget *p);
	void paintEvent(QPaintEvent *e);
	virtual ~XVideoEidt();
};

