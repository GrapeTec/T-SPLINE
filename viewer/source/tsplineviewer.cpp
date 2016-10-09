#include "tsplineviewer.h"

#include "glwidget.h"

TSplineViewer::TSplineViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(closeFile()));

	_gl_widget = new GLWidget(this);
	setCentralWidget(_gl_widget);

	connect(ui.actionBottom_View, SIGNAL(triggered()), _gl_widget, SLOT(setBottomView()));
	connect(ui.actionTop_View, SIGNAL(triggered()), _gl_widget, SLOT(setTopView()));
	connect(ui.actionLeft_VIew, SIGNAL(triggered()), _gl_widget, SLOT(setLeftView()));
	connect(ui.actionRight_View, SIGNAL(triggered()), _gl_widget, SLOT(setRightView()));
	connect(ui.actionFront_View, SIGNAL(triggered()), _gl_widget, SLOT(setFrontView()));
	connect(ui.actionISO_View, SIGNAL(triggered()), _gl_widget, SLOT(setISOView()));

	connect(ui.actionPoint, SIGNAL(triggered()), _gl_widget, SLOT(setPointRenderMode()));
	connect(ui.actionLine, SIGNAL(triggered()), _gl_widget, SLOT(setLineRenderMode()));
	connect(ui.actionFill, SIGNAL(triggered()), _gl_widget, SLOT(setFillRenderMode()));
}

TSplineViewer::~TSplineViewer()
{

}

void TSplineViewer::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("TSpline file(*.tsm);;obj file(*.obj);;stl file(*.stl);;off file(*.off)"));
	if(!fileName.isNull())
	{
		_gl_widget->createScene(fileName);
	}
}

void TSplineViewer::closeFile()
{
	if (QMessageBox::Yes == QMessageBox::question(this,
		tr("TSplineViewer"),
		tr("Exit TSplineViewer?"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::Yes)) 
	{
			this->close();
	} else 
	{
	}
}