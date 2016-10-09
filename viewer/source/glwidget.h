#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QSet>

//GLC headers
#include <viewport/glc_viewport.h>
#include <viewport/glc_movercontroller.h>
#include <shading/glc_light.h>
#include <sceneGraph/glc_3dviewcollection.h>
#include <sceneGraph/glc_world.h>
#include <glc_factory.h>

//tspline headers
#include <tspline.h>
#include <rhbuilder.h>
#include <tessellator.h>

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GLWidget(QWidget *parent);
	~GLWidget();

	void createScene(const QString &filename);//create or load scene/model

	public slots:
	//view
	void setBottomView();
	void setTopView();
	void setLeftView();
	void setRightView();
	void setFrontView();
	void setISOView();
	//render mode
	void setPointRenderMode();
	void setLineRenderMode();
	void setFillRenderMode();
	
private:
	//virtual functions
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	//events
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);

	//
	void createScene();//create or load scene/model
	GLC_World loadModel(const QString &filename);//load model(GLC support extensions)
	GLC_World loadTSMFile(const QString &filename);//load TSM model using tspline library


	// Selection function
	void select(const int x, const int y);

private:

private:
	GLC_Viewport _glc_view;//GLC view with default camera
	GLC_MoverController _glc_mover_controller;//GLC mouse controller

	GLC_Light _glc_light;//GLC light
	//GLC_3DViewCollection _glc_collection;//GLC all shape
	GLC_World _glc_world;//GLC all shape

	bool isSet;//adapt scene
};

#endif // GLWIDGET_H
