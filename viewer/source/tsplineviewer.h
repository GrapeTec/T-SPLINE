#ifndef TSPLINEVIEWER_H
#define TSPLINEVIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_tsplineviewer.h"

class GLWidget;

class TSplineViewer : public QMainWindow
{
	Q_OBJECT

public:
	TSplineViewer(QWidget *parent = 0);
	~TSplineViewer();

private slots:
	void openFile();
	void closeFile();
private:
	Ui::TSplineViewerClass ui;
	GLWidget *_gl_widget;
};

#endif // TSPLINEVIEWER_H
