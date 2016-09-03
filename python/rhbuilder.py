import tspline as t

builder = t.RhBuilder("../rhino/Bike.tsm")

tesselator = t.Tessellator(builder.findTSpline())
mesh = tesselator.interpolateAll()


# VISUALISATION OF SURFACE
##########################

def surface(root):
    global mesh
    root += mesh_sep(mesh.getPoints(), mesh.getFaces())


# VISUALISATION
###############

from pivy import coin, quarter
from PySide import QtGui
import sys

class Line(object):
    def __init__(self, points, width=1):
        self.object = coin.SoSeparator()
        self.ls = coin.SoLineSet()
        self.data = coin.SoCoordinate3()
        self.color = coin.SoMaterial()
        self.drawstyle = coin.SoDrawStyle()
        self.points = points
        self.color.diffuseColor = (1., 1., 1.)
        self.drawstyle.lineWidth = width
        self.update()
        self.object += self.color, self.drawstyle, self.data, self.ls

    def update(self, points=None):
        if points is not None:
            self.points = list(map(vector3D, points))
        self.data.point.deleteValues(0)
        self.data.point.setValues(0, len(self.points), self.points)

def mesh_sep(vertices, polygons, color=(1,1,0), draw_lines=True):
    _vertices = vertices
    _polygons = []
    _lines = []
    for i in polygons:
        _polygons += i
        _lines += i
        _lines.append(i[0])
        _polygons.append(-1)
        _lines.append(-1)

    sep = coin.SoSeparator()
    vertex_property = coin.SoVertexProperty()
    face_set = coin.SoIndexedFaceSet()
    shape_hint = coin.SoShapeHints()
    shape_hint.vertexOrdering = coin.SoShapeHints.COUNTERCLOCKWISE
    shape_hint.creaseAngle = coin.M_PI / 3
    face_mat = coin.SoMaterial()
    face_mat.diffuseColor = color
    vertex_property.vertex.setValues(0, len(_vertices), _vertices)
    face_set.coordIndex.setValues(0, len(_polygons), list(_polygons))
    vertex_property.materialBinding = coin.SoMaterialBinding.PER_VERTEX_INDEXED
    sep += shape_hint, vertex_property, face_mat, face_set

    if draw_lines:
        line_set = coin.SoIndexedLineSet()
        line_set.coordIndex.setValues(0, len(_lines), list(_lines))
        line_mat = coin.SoMaterial()
        line_mat.diffuseColor = (.0, .0, .0)
        sep += line_mat, line_set
    return sep

root = coin.SoSeparator()
surface(root)
# Initialize Inventor and Qt
app = QtGui.QApplication([])
viewer = quarter.QuarterWidget()



viewer.setSceneGraph(root)
viewer.setWindowTitle("parametric layer")
viewer.show()
# viewer.viewAll()

sys.exit(app.exec_())
