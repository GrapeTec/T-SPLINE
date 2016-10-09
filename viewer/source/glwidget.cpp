#include "glwidget.h"

//GLC headers
#include <glc_context.h>
#include <glc_exception.h>

// For VSYNC problem under Mac OS X
#if defined(Q_OS_MAC)
#include <OpenGL.h>
#endif

GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(new GLC_Context(QGLFormat(QGL::SampleBuffers)), parent)
	, _glc_view()
	, _glc_mover_controller()
	, _glc_light()
	,_glc_world()
{
	connect(&_glc_view, SIGNAL(updateOpenGL()), this, SLOT(updateGL()));

	_glc_light.setPosition(4000.0, 40000.0, 80000.0);
	_glc_light.setAmbientColor(QColor(0.1,0.1,0.8));

	_glc_view.cameraHandle()->setDefaultUpVector(glc::Z_AXIS);
	_glc_view.cameraHandle()->setIsoView();//set camera view

	_glc_mover_controller = GLC_Factory::instance()->createDefaultMoverController(Qt::green, &_glc_view);//create move controller

	isSet = false;
	//create or load scene
	//createScene();
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
	// For VSYNC problem under Mac OS X
#if defined(Q_OS_MAC)
	const GLint swapInterval = 1;
	CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif

	_glc_view.initGl();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLC_Context::current()->glcLoadIdentity();

	if(!isSet && !_glc_world.isEmpty())
	{
		isSet = true;
		_glc_view.reframe(_glc_world.boundingBox());
	}

	try
	{
		if(!_glc_world.isEmpty())
		{
			_glc_view.setDistMinAndMax(_glc_world.boundingBox());
			_glc_light.setPosition(_glc_world.boundingBox().xLength()*1000, _glc_world.boundingBox().yLength()*1000, _glc_world.boundingBox().zLength()*10000);
		}

		_glc_view.glExecuteCam();

		_glc_light.glExecute();


		if(!_glc_world.isEmpty())
		{
			_glc_world.render(0, glc::ShadingFlag);
		}

		_glc_mover_controller.drawActiveMoverRep();
	}
	catch(GLC_Exception &e)
	{
		qDebug() << e.what();
	}
}

void GLWidget::resizeGL( int width, int height )
{
	_glc_view.setWinGLSize(width, height);
}

// Mouse events

void GLWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (_glc_mover_controller.hasActiveMover()) return;
	//deep style
	switch (e->button())
	{
	case (Qt::LeftButton):
		//Select/unselect Faces by Mouse DoubleClick event
		select(e->x(), e->y());
		break;
	default:
		break;
	}
}

void GLWidget::mousePressEvent( QMouseEvent *e )
{
	if (_glc_mover_controller.hasActiveMover()) return;
	//deep style
	switch (e->button())
	{
	case (Qt::RightButton):
		// zoom
		_glc_mover_controller.setActiveMover(GLC_MoverController::Zoom, GLC_UserInput(e->x(), e->y()));
		updateGL();
		break;
	case (Qt::LeftButton):
		//Set translate
		_glc_mover_controller.setActiveMover(GLC_MoverController::TrackBall, GLC_UserInput(e->x(), e->y()));
		updateGL();

		break;
	case (Qt::MidButton):
		// Set pan
		_glc_mover_controller.setActiveMover(GLC_MoverController::Pan, GLC_UserInput(e->x(), e->y()));
		updateGL();
		break;
	default:
		break;
	}
}

void GLWidget::mouseMoveEvent( QMouseEvent *e )
{
	if (_glc_mover_controller.hasActiveMover())
	{
		// Move with the active mover
		_glc_mover_controller.move(GLC_UserInput(e->x(), e->y()));
		updateGL();
	}
}

void GLWidget::mouseReleaseEvent( QMouseEvent *e )
{
	if (_glc_mover_controller.hasActiveMover())
	{
		// Set No mover
		_glc_mover_controller.setNoMover();
		updateGL();
	}
}

void GLWidget::createScene()
{
	//_glc_world = loadModel("mouse.obj");
	_glc_world = loadTSMFile("F:\\T-SPLINE\\rhino\\simple.tsm"); 
}

// Create scene. Load model from a file
void GLWidget::createScene(const QString &filename)
{
	QFileInfo fi(filename);
	QString ext = fi.suffix();
	if(ext == "tsm")
	{
		_glc_world = loadTSMFile(filename);
		isSet = false;
	}
	else if(ext == "obj" || ext == "stl" || ext == "off")
	{
		_glc_world = loadModel(filename);
		isSet = false;
	}
}

// Load the model
GLC_World GLWidget::loadModel( const QString &filename )
{
	return GLC_Factory::instance()->createWorldFromFile(QFile(filename));
}

//Load TSM file
GLC_World GLWidget::loadTSMFile( const QString &filename )
{
	RhBuilderPtr reader = makePtr<RhBuilder>(filename.toStdString());
	TSplinePtr spline = reader->findTSpline();

	GLC_World w;

	IndexList face;
	QList<float> vertex;
	QList<float> normal;

	TTessellator tessellator(spline);

	TImagePtr image = spline->getTImage();

	// Go through all the faces in TImage and create abjects 
	TFacVIterator fiter = image->faceIteratorBegin();
	for (;fiter!=image->faceIteratorEnd();fiter++)
	{
		TFacePtr tface = *fiter;

		TriMeshPtr trimesh = tessellator.interpolateFace(tface);

		P3dVIterator piter = trimesh->pointIteratorBegin();
		for (piter;piter!=trimesh->pointIteratorEnd();piter++)
		{
			vertex.push_back((*piter)->x());
			vertex.push_back((*piter)->y());
			vertex.push_back((*piter)->z());
		}

		N3dVIterator niter = trimesh->normalIteratorBegin();
		for (;niter!=trimesh->normalIteratorEnd();niter++)
		{
			normal.push_back((*niter)->i());
			normal.push_back((*niter)->j());
			normal.push_back((*niter)->k());
		}

		TriVIterator titer = trimesh->triangleIteratorBegin();
		for (;titer!=trimesh->triangleIteratorEnd();titer++)
		{
			face.push_back((*titer)->point_indices[0]);
			face.push_back((*titer)->point_indices[1]);
			face.push_back((*titer)->point_indices[2]);
		}

		GLC_Mesh* glc_mesh = new GLC_Mesh();
		glc_mesh->addTriangles(0,face);
		face.clear();
		glc_mesh->addVertice(vertex.toVector());
		vertex.clear();
		glc_mesh->addNormals(normal.toVector());
		normal.clear();
		glc_mesh->finish();

		GLC_3DRep *rep = new GLC_3DRep(glc_mesh);
		glc_mesh = NULL;
		
		// Set the material 
		GLC_Material* pCurrentMat= NULL;
		pCurrentMat= rep->geomAt(0)->firstMaterial();
		pCurrentMat->setAmbientColor(Qt::gray);
		pCurrentMat->setDiffuseColor(Qt::gray);

		// Add objects (faces) to the world collection 
		w.collection()->add(*rep);
	}
	return w;
}

// Set the view

void GLWidget::setBottomView()
{
	_glc_view.cameraHandle()->setBottomView();
	updateGL();
}

void GLWidget::setTopView()
{
	_glc_view.cameraHandle()->setTopView();
	updateGL();
}

void GLWidget::setLeftView()
{
	_glc_view.cameraHandle()->setLeftView();
	updateGL();
}

void GLWidget::setRightView()
{
	_glc_view.cameraHandle()->setRightView();
	updateGL();
}

void GLWidget::setFrontView()
{
	_glc_view.cameraHandle()->setFrontView();
	updateGL();
}

void GLWidget::setISOView()
{
	_glc_view.cameraHandle()->setIsoView();
	updateGL();
}

// Set the polygon mode type

void GLWidget::setPointRenderMode()
{
	_glc_world.collection()->setPolygonModeForAll(GL_FRONT_AND_BACK, GL_POINT);
	updateGL();
}

void GLWidget::setLineRenderMode()
{
	_glc_world.collection()->setPolygonModeForAll(GL_FRONT_AND_BACK, GL_LINE);
	updateGL();
}

void GLWidget::setFillRenderMode()
{
	_glc_world.collection()->setPolygonModeForAll(GL_FRONT_AND_BACK, GL_FILL);
	updateGL();
}

// Select a face 
void GLWidget::select(const int x, const int y)
{
	// Fill all the faces
	setFillRenderMode();

	setAutoBufferSwap(false);
	GLC_uint SelectionID= _glc_view.renderAndSelect(x, y);
	setAutoBufferSwap(true);

	if (SelectionID != 0)
	{
		GLC_3DViewInstance instance(*_glc_world.collection()->instanceHandle(SelectionID));
		if (!instance.isEmpty())
		{	
			if (instance.geomAt(0)->firstMaterial()->ambientColor() == Qt::gray)
			{
				instance.geomAt(0)->firstMaterial()->setAmbientColor(Qt::red);
				instance.geomAt(0)->firstMaterial()->setDiffuseColor(QColor::fromRgbF(0.8, 0.2, 0.2, 1.0));
			}
			else
			{
				instance.geomAt(0)->firstMaterial()->setAmbientColor(Qt::gray);
				instance.geomAt(0)->firstMaterial()->setDiffuseColor(Qt::gray);
			}
		}
	}
	else // unselect all the faces
	{
		QList<GLC_3DViewInstance*> instansesList = _glc_world.collection()->instancesHandle();
		QList<GLC_3DViewInstance*>::iterator facesIter;
		for (facesIter = instansesList.begin(); facesIter != instansesList.end(); ++facesIter)
		{
			(*facesIter)->geomAt(0)->firstMaterial()->setAmbientColor(Qt::gray);
			(*facesIter)->geomAt(0)->firstMaterial()->setDiffuseColor(Qt::gray);
		}
	}	
	updateGL();
}
