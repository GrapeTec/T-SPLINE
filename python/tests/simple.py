import tspline as t

# INITIALIZE THE T-OBJECTS
##########################

group = t.Group("group")

spline = t.Spline("spline")
group.addObject(spline)
spline.setCollector(group)

image = t.Image("image")
group.addObject(image)
image.setCollector(group)

nodegrid = t.Connect("TConnect")
group.addObject(nodegrid)
nodegrid.setCollector(group)

pointset = t.Pointset("point_set")
group.addObject(pointset)
pointset.setCollector(group)

v0 = t.Vertex("v0", 0.0, 0.0)
v1 = t.Vertex("v1", 0.5, 0.0)
v2 = t.Vertex("v2", 1.0, 0.0)
v3 = t.Vertex("v3", 0.0, 0.5)
v4 = t.Vertex("v4", 0.5, 0.5)
v5 = t.Vertex("v5", 1.0, 0.5)
v6 = t.Vertex("v6", 0.0, 1.0)
v7 = t.Vertex("v7", 1.0, 1.0)

e0 = t.Edge("e0")
e1 = t.Edge("e1")
e2 = t.Edge("e2")
e3 = t.Edge("e3")
e4 = t.Edge("e4")
e5 = t.Edge("e5")
e6 = t.Edge("e6")
e7 = t.Edge("e7")
e8 = t.Edge("e8")
e9 = t.Edge("e9")

l0 = t.Link("l0")
l1 = t.Link("l1")
l2 = t.Link("l2")
l3 = t.Link("l3")
l4 = t.Link("l4")
l5 = t.Link("l5")
l6 = t.Link("l6")
l7 = t.Link("l7")
l8 = t.Link("l8")
l9 = t.Link("l9")
l10 = t.Link("l10")
l11 = t.Link("l11")
l12 = t.Link("l12")
l13 = t.Link("l13")
l14 = t.Link("l14")
l15 = t.Link("l15")
l16 = t.Link("l16")
l17 = t.Link("l17")
l18 = t.Link("l18")
l19 = t.Link("l19")

ec0 = t.EdgeCondition("ec0")
ec1 = t.EdgeCondition("ec1")
ec2 = t.EdgeCondition("ec2")
ec3 = t.EdgeCondition("ec3")
ec4 = t.EdgeCondition("ec4")
ec5 = t.EdgeCondition("ec5")
ec6 = t.EdgeCondition("ec6")

f0 = t.Face("f0")
f1 = t.Face("f1")
f2 = t.Face("f2")

n0_0 = t.NodeV4("n0-0")
n0_1 = t.NodeV4("n0-1")
n0_2 = t.NodeV4("n0-2")
n0_3 = t.NodeV4("n0-3")
n1_0 = t.NodeV4("n1-0")
n1_1 = t.NodeV4("n1-1")
n2_0 = t.NodeV4("n2-0")
n2_1 = t.NodeV4("n2-1")
n2_2 = t.NodeV4("n2-2")
n2_3 = t.NodeV4("n2-3")
n3_0 = t.NodeV4("n3-0")
n3_1 = t.NodeV4("n3-1")
n4_0 = t.NodeV4("n4-0")
n5_0 = t.NodeV4("n5-0")
n5_1 = t.NodeV4("n5-1")
n6_0 = t.NodeV4("n6-0")
n6_1 = t.NodeV4("n6-1")
n6_2 = t.NodeV4("n6-2")
n6_3 = t.NodeV4("n6-3")
n7_0 = t.NodeV4("n7-0")
n7_1 = t.NodeV4("n7-1")
n7_2 = t.NodeV4("n7-2")
n7_3 = t.NodeV4("n7-3")

p0_0 = t.Point("p0-0", 0.0, 1.0, 0.25, 1.0)
p0_1 = t.Point("p0-1", 1.0, 1.0, 0.5, 1.0)
p0_2 = t.Point("p0-2", 0.0, 0.0, 0.0, 1.0)
p0_3 = t.Point("p0-3", 1.0, 0.0, 0.25, 1.0)
p1_0 = t.Point("p1-0", 2.0, 1.0, 0.75, 1.0)
p1_1 = t.Point("p1-1", 2.0, 0.0, 0.5, 1.0)
p2_0 = t.Point("p2-0", 3.0, 1.0, 0.5, 1.0)
p2_1 = t.Point("p2-1", 4.0, 1.0, 0.25, 1.0)
p2_2 = t.Point("p2-2", 3.0, 0.0, 0.25, 1.0)
p2_3 = t.Point("p2-3", 4.0, 0.0, 0.0, 1.0)
p3_0 = t.Point("p3-0", 0.0, 2.0, 0.5, 1.0)
p3_1 = t.Point("p3-1", 1.0, 2.0, 0.75, 1.0)
p4_0 = t.Point("p4-0", 2.0, 2.0, -1.0, 1.0)
p5_0 = t.Point("p5-0", 3.0, 2.0, 0.75, 1.0)
p5_1 = t.Point("p5-1", 4.0, 2.0, 0.5, 1.0)
p6_0 = t.Point("p6-0", 0.0, 4.0, 0.0, 1.0)
p6_1 = t.Point("p6-1", 1.0, 4.0, 0.25, 1.0)
p6_2 = t.Point("p6-2", 0.0, 3.0, 0.25, 1.0)
p6_3 = t.Point("p6-3", 1.0, 3.0, 0.5, 1.0)
p7_0 = t.Point("p7-0", 3.0, 4.0, 0.25, 1.0)
p7_1 = t.Point("p7-1", 4.0, 4.0, 0.0, 1.0)
p7_2 = t.Point("p7-2", 3.0, 3.0, 0.5, 1.0)
p7_3 = t.Point("p7-3", 4.0, 3.0, 0.25, 1.0)

points = [p0_0, p0_1, p0_2, p0_3, p1_0, p1_1,
          p2_0, p2_1, p2_2, p2_3, p3_0, p3_1,
          p4_0, p5_0, p5_1, p6_0, p6_1, p6_2,
          p6_3, p7_0, p7_1, p7_2, p7_3]

# create list of the objects
vertices = [v0, v1, v2, v3, v4, v5, v6, v7]
edges = [e0, e1, e2, e3, e4, e5, e6, e7, e8, e9]
links = [l0, l1, l2, l3, l4,
         l5, l6, l7, l8, l9,
         l10, l11, l12, l13, l14,
         l15, l16, l17, l18, l19]

edgeconditions = [ec0, ec1, ec2, ec3, ec4, ec5, ec6]
faces = [f0, f1, f2]
nodes = [n0_0, n0_1, n0_2, n0_3, n1_0, n1_1,
         n2_0, n2_1, n2_2, n2_3, n3_0, n3_1,
         n4_0, n5_0, n5_1, n6_0, n6_1, n6_2,
         n6_3, n7_0, n7_1, n7_2, n7_3]


# PATCH THE T-OBJECTS
#####################

# patchTSpline
spline.setTImage(image)
spline.setTConnect(nodegrid)
spline.setTPointset(pointset)
spline.setSDegree(3)
spline.setTDegree(3)

# patchTImage
for face in faces:
    image.addFace(face)
    group.addObject(face)
    face.setCollector(group)

for link in links:
    image.addLink(link)
    group.addObject(link)
    link.setCollector(group)

for edge in edges:
    image.addEdge(edge)
    group.addObject(edge)
    edge.setCollector(group)

for vertex in vertices:
    image.addVertex(vertex)
    group.addObject(vertex)
    vertex.setCollector(group)

# patchTConnect
for node in nodes:
    group.addObject(node)
    node.setCollector(group)

# patchTPointSet
for point in points:
    group.addObject(point)
    point.setCollector(group)

# patchTEdges
e0.patch(v0, v1, f0, None)
e1.patch(v1, v2, f1, None)
e2.patch(v0, v3, None, f0)
e3.patch(v1, v4, f0, f1)
e4.patch(v2, v5, f1, None)
e5.patch(v3, v4, f2, f0)
e6.patch(v4, v5, f2, f1)
e7.patch(v3, v6, None, f2)
e8.patch(v5, v7, f2, None)
e9.patch(v6, v7, None, f2)

# patchTLinks
l0.setOrientedEdge(e0, True)
l1.setOrientedEdge(e0, False)
l2.setOrientedEdge(e1, True)
l3.setOrientedEdge(e1, False)
l4.setOrientedEdge(e2, True)
l5.setOrientedEdge(e2, False)
l6.setOrientedEdge(e3, True)
l7.setOrientedEdge(e3, False)
l8.setOrientedEdge(e4, True)
l9.setOrientedEdge(e4, False)
l10.setOrientedEdge(e5, True)
l11.setOrientedEdge(e5, False)
l12.setOrientedEdge(e6, True)
l13.setOrientedEdge(e6, False)
l14.setOrientedEdge(e7, True)
l15.setOrientedEdge(e7, False)
l16.setOrientedEdge(e8, True)
l17.setOrientedEdge(e8, False)
l18.setOrientedEdge(e9, True)
l19.setOrientedEdge(e9, False)


# patch TEdgeConditions
ec0.setEdgeCondition(e0, True)
ec1.setEdgeCondition(e1, True)
ec2.setEdgeCondition(e2, True)
ec3.setEdgeCondition(e4, True)
ec4.setEdgeCondition(e7, True)
ec5.setEdgeCondition(e8, True)
ec6.setEdgeCondition(e9, True)

# patchTFaces
for l in [l0, l6, l11, l5]:
    f0.addLink(l)
for l in [l2, l8, l13, l7]:
    f1.addLink(l)
for l in [l10, l12, l16, l19, l15]:
    f2.addLink(l)
# Why is there no need for blending nodes???

# patchTVertices
v0.setNeighboursByVertices(links, [v3, None, None, v1])
v1.setNeighboursByVertices(links, [v4, v0, None, v2])
v2.setNeighboursByVertices(links, [v5, v1, None, None])
v3.setNeighboursByVertices(links, [v6, None, v0, v4])
v4.setNeighboursByVertices(links, [None, v3, v1, v5])
v5.setNeighboursByVertices(links, [v7, v4, v2, None])
v6.setNeighboursByVertices(links, [None, None, v3, v7])
v7.setNeighboursByVertices(links, [None, v6, v5, None])

# patchTNodes
n0_0.setNeighbours(n3_0, None, n0_2, n0_1)
n0_1.setNeighbours(n3_0, n0_0, n0_3, n1_1)
n0_2.setNeighbours(n0_0, None, None, n0_3)
n0_3.setNeighbours(n0_1, n0_2, None, n1_1)
n1_0.setNeighbours(n4_0, n0_3, n1_1, n2_2)
n1_1.setNeighbours(n1_0, n0_3, None, n2_2)
n2_0.setNeighbours(n5_1, n1_1, n2_2, n2_1)
n2_1.setNeighbours(n5_1, n2_0, n2_3, None)
n2_2.setNeighbours(n2_0, n1_1, None, n2_3)
n2_3.setNeighbours(n2_1, n2_2, None, None)
n3_0.setNeighbours(n6_2, None, n0_0, n3_1)
n3_1.setNeighbours(n6_2, n3_0, n0_0, n4_0)
n4_0.setNeighbours(None, n3_1, n1_0, n5_0)
n5_0.setNeighbours(n7_3, n4_0, n2_1, n5_1)
n5_1.setNeighbours(n7_3, n5_0, n2_1, None)
n6_0.setNeighbours(None, None, n6_2, n6_1)
n6_1.setNeighbours(None, n6_0, n6_3, n7_0)
n6_2.setNeighbours(n6_0, None, n3_0, n6_3)
n6_3.setNeighbours(n6_1, n6_2, n3_0, n7_0)
n7_0.setNeighbours(None, n6_1, n7_2, n7_1)
n7_1.setNeighbours(None, n7_0, n7_3, None)
n7_2.setNeighbours(n7_0, n6_1, n5_1, n7_3)
n7_3.setNeighbours(n7_1, n7_2, n5_1, None)

n0_0.setTMappableObject(v0)
n0_1.setTMappableObject(v0)
n0_2.setTMappableObject(v0)
n0_3.setTMappableObject(v0)
n1_0.setTMappableObject(v1)
n1_1.setTMappableObject(v1)
n2_0.setTMappableObject(v2)
n2_1.setTMappableObject(v2)
n2_2.setTMappableObject(v2)
n2_3.setTMappableObject(v2)
n3_0.setTMappableObject(v3)
n3_1.setTMappableObject(v3)
n4_0.setTMappableObject(v4)
n5_0.setTMappableObject(v5)
n5_1.setTMappableObject(v5)
n6_0.setTMappableObject(v6)
n6_1.setTMappableObject(v6)
n6_2.setTMappableObject(v6)
n6_3.setTMappableObject(v6)
n7_0.setTMappableObject(v7)
n7_1.setTMappableObject(v7)
n7_2.setTMappableObject(v7)
n7_3.setTMappableObject(v7)

n0_0.setTPoint(p0_0)
n0_1.setTPoint(p0_1)
n0_2.setTPoint(p0_2)
n0_3.setTPoint(p0_3)
n1_0.setTPoint(p1_0)
n1_1.setTPoint(p1_1)
n2_0.setTPoint(p2_0)
n2_1.setTPoint(p2_1)
n2_2.setTPoint(p2_2)
n2_3.setTPoint(p2_3)
n3_0.setTPoint(p3_0)
n3_1.setTPoint(p3_1)
n4_0.setTPoint(p4_0)
n5_0.setTPoint(p5_0)
n5_1.setTPoint(p5_1)
n6_0.setTPoint(p6_0)
n6_1.setTPoint(p6_1)
n6_2.setTPoint(p6_2)
n6_3.setTPoint(p6_3)
n7_0.setTPoint(p7_0)
n7_1.setTPoint(p7_1)
n7_2.setTPoint(p7_2)
n7_3.setTPoint(p7_3)

# patchTPoints
p0_0.setTNode(n0_0)
p0_1.setTNode(n0_1)
p0_2.setTNode(n0_2)
p0_3.setTNode(n0_3)
p1_0.setTNode(n1_0)
p1_1.setTNode(n1_1)
p2_0.setTNode(n2_0)
p2_1.setTNode(n2_1)
p2_2.setTNode(n2_2)
p2_3.setTNode(n2_3)
p3_0.setTNode(n3_0)
p3_1.setTNode(n3_1)
p4_0.setTNode(n4_0)
p5_0.setTNode(n5_0)
p5_1.setTNode(n5_1)
p6_0.setTNode(n6_0)
p6_1.setTNode(n6_1)
p6_2.setTNode(n6_2)
p6_3.setTNode(n6_3)
p7_0.setTNode(n7_0)
p7_1.setTNode(n7_1)
p7_2.setTNode(n7_2)
p7_3.setTNode(n7_3)

# PREPARE THE T-OBJECTS
#######################

t.prepareTNodeHalfLinkages(vertices)
t.prepareTJunctions(vertices)
t.prepareImageConnect(nodes, spline)

# TESSELATOR
############

tesselator = t.Tessellator(spline)
tesselator.setResolution(0.000001)
mesh = tesselator.interpolateAll()


# # VISUALISATION OF THE PARAMETRIC LAYER
# #######################################

# def parametric_layer(root):
#     global edges
#     _vertices = []
#     for i, edge in enumerate(edges):
#         _vertices.append([[edge.getStartVertex().getS(), edge.getStartVertex().getT(), 0.],
#                           [edge.getEndVertex().getS(), edge.getEndVertex().getT(), 0.]])
#     for i in _vertices:
#         root += Line(i).object


# # VISUALISATION OF SURFACE
# ##########################

# def surface(root):
#     global mesh
#     root += mesh_sep(mesh.getPoints(), mesh.getFaces())


# # VISUALISATION
# ###############

# from pivy import coin, quarter
# from PySide import QtGui
# import sys

# class Line(object):
#     def __init__(self, points, width=1):
#         self.object = coin.SoSeparator()
#         self.ls = coin.SoLineSet()
#         self.data = coin.SoCoordinate3()
#         self.color = coin.SoMaterial()
#         self.drawstyle = coin.SoDrawStyle()
#         self.points = points
#         self.color.diffuseColor = (1., 1., 1.)
#         self.drawstyle.lineWidth = width
#         self.update()
#         self.object += self.color, self.drawstyle, self.data, self.ls

#     def update(self, points=None):
#         if points is not None:
#             self.points = list(map(vector3D, points))
#         self.data.point.deleteValues(0)
#         self.data.point.setValues(0, len(self.points), self.points)

# def mesh_sep(vertices, polygons, color=(1,1,0), draw_lines=False):
#     _vertices = vertices
#     _polygons = []
#     _lines = []
#     for i in polygons:
#         _polygons += i
#         _lines += i
#         _lines.append(i[0])
#         _polygons.append(-1)
#         _lines.append(-1)

#     sep = coin.SoSeparator()
#     vertex_property = coin.SoVertexProperty()
#     face_set = coin.SoIndexedFaceSet()
#     shape_hint = coin.SoShapeHints()
#     shape_hint.vertexOrdering = coin.SoShapeHints.COUNTERCLOCKWISE
#     shape_hint.creaseAngle = coin.M_PI / 3
#     face_mat = coin.SoMaterial()
#     face_mat.diffuseColor = color
#     vertex_property.vertex.setValues(0, len(_vertices), _vertices)
#     face_set.coordIndex.setValues(0, len(_polygons), list(_polygons))
#     vertex_property.materialBinding = coin.SoMaterialBinding.PER_VERTEX_INDEXED
#     sep += shape_hint, vertex_property, face_mat, face_set

#     if draw_lines:
#         line_set = coin.SoIndexedLineSet()
#         line_set.coordIndex.setValues(0, len(_lines), list(_lines))
#         line_mat = coin.SoMaterial()
#         line_mat.diffuseColor = (.0, .0, .0)
#         sep += line_mat, line_set
#     return sep

# root = coin.SoSeparator()
# parametric_layer(root)
# surface(root)
# # Initialize Inventor and Qt
# app = QtGui.QApplication([])
# viewer = quarter.QuarterWidget()



# viewer.setSceneGraph(root)
# viewer.setWindowTitle("parametric layer")
# viewer.show()
# # viewer.viewAll()

# sys.exit(app.exec_())
