#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <array>
#include <tuple>
#include <memory>

#include "tspline.h"
#include "factory.h"
#include "tessellator.h"
#include "trimesh.h"
#include "visitor.h"
#include "utils.h"
#include "extractor.h"
#include "rhbuilder.h"

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);



std::vector<std::array<double, 3>> getTriMeshPoints(TSPLINE::TriMesh & mesh)
{
    std::vector<std::array<double, 3>> points;
    TSPLINE::P3dVIterator iter;
    for (iter=mesh.pointIteratorBegin(); iter!=mesh.pointIteratorEnd(); iter++)
    {
        TSPLINE::Point3DPtr _point = *iter;
        std::array<double, 3> point {_point->x(), _point->y(), _point->z()};
        points.push_back(point);
    }

    return points;
}
std::vector<std::array<double, 3>> getTriMeshNormals(TSPLINE::TriMesh & mesh)
{
    std::vector<std::array<double, 3>> normals;
    TSPLINE::N3dVIterator iter;
    for (iter=mesh.normalIteratorBegin(); iter!=mesh.normalIteratorEnd(); iter++)
    {
        TSPLINE::Vector3DPtr _normal = *iter;
        std::array<double, 3> normal {_normal->i(), _normal->j(), _normal->k()};
        normals.push_back(normal);
    }

    return normals;
}
std::vector<std::array<unsigned int, 3>> getTriMeshFaces(TSPLINE::TriMesh & mesh)
{
    std::vector<std::array<unsigned int, 3>> triangles;
    TSPLINE::TriVIterator iter;
    for (iter=mesh.triangleIteratorBegin(); iter!=mesh.triangleIteratorEnd(); iter++)
    {
        TSPLINE::TrianglePtr _triangle = *iter;
        std::array<unsigned int, 3> triangle {_triangle->point_indices[0],
                                              _triangle->point_indices[1], 
                                              _triangle->point_indices[2]};
        triangles.push_back(triangle);
    }

    return triangles;
}



TSPLINE::TLinkPtr findTLinkByStartEndVertices(TSPLINE::TLnkVector links, 
                                     const TSPLINE::TVertexPtr &start, 
                                     const TSPLINE::TVertexPtr &end )
{
    TSPLINE::TLnkVIterator link_iter = std::find_if(links.begin(), links.end(), 
        TSPLINE::TLinkVisitorCheckStartEndVertices(start, end));

    if (link_iter != links.end())
    {
        return *link_iter;
    }
    else
    {
        return 0;
    }
}

void patchEdge(TSPLINE::TEdge & edge, TSPLINE::TVertexPtr & startVertex, TSPLINE::TVertexPtr & endVertex, 
                                      TSPLINE::TFacePtr & leftFace, TSPLINE::TFacePtr & rightFace)
{
    edge.setStartVertex(startVertex);
    edge.setEndVertex(endVertex);
    edge.setLeftFace(leftFace);
    edge.setRightFace(rightFace);
}

void setNeighboursByVertices(TSPLINE::TVertexPtr & vertex, TSPLINE::TLnkVector & links,  
                                std::vector<TSPLINE::TVertexPtr> & oriented_vertices)
{
    std::vector<TSPLINE::TLinkPtr> oriented_links;
    for (TSPLINE::TVertexPtr neighbour: oriented_vertices)
        oriented_links.push_back(findTLinkByStartEndVertices(links, vertex, neighbour));
    vertex->setNeighbours(oriented_links[0], oriented_links[1], oriented_links[2], oriented_links[3]);
}

void prepareTJunctions(TSPLINE::TVtxVector vertices)
{
    std::for_each(vertices.begin(), vertices.end(), TSPLINE::TVertexVisitorCheckTJunctions());
}

void prepareTNodeHalfLinkages(TSPLINE::TVtxVector vertices)
{
    std::for_each(vertices.begin(), vertices.end(), TSPLINE::TVertexVisitorCheckTNodes());
}

void prepareImageConnect(TSPLINE::TNodV4Vector nodes, TSPLINE::TSplinePtr spline)
{
    TSPLINE::TNodV4VIterator iter;
    for (iter=nodes.begin();iter!=nodes.end();iter++)
    {
        TSPLINE::TNodeV4Ptr node = *iter;
        TSPLINE::TFacVector faces;
        TSPLINE::TExtractor::extractTFacesFromTNodeV4(node, faces, spline->getSDegree(), spline->getTDegree());

        TSPLINE::TFacVIterator fiter;
        for (fiter=faces.begin();fiter!=faces.end();fiter++)
        {
            TSPLINE::TFacePtr face = *fiter;
            if (face)
                face->addBlendingNode(node);
        }
    }
}

void setTMappableObject(TSPLINE::TNodePtr & node, TSPLINE::TVertexPtr & vertex)
{
    node->setTMappableObject(TSPLINE::castPtr<TSPLINE::TMappableObject>(vertex));
}

void init_tspline(py::module &m)
{

    // TObject:
    py::class_<TSPLINE::TObject, TSPLINE::TObjectPtr>(m, "_Object", "docs")
        .def("setCollector", &TSPLINE::TObject::setCollector);

    // TMapableObject:
    py::class_<TSPLINE::TMappableObject, TSPLINE::TMappableObjectPtr>(m, "MappableObject",
        py::base<TSPLINE::TObject>(), "docs")
        .def("getCollector", &TSPLINE::TMappableObject::getCollector);

    // TGroup:
    py::class_<TSPLINE::TGroup, TSPLINE::TGroupPtr>(m, "Group",
            py::base<TSPLINE::TObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("addObject", &TSPLINE::TGroup::addObject)
        .def("insertObject", &TSPLINE::TGroup::insertObject)
        .def("removeObject", (bool (TSPLINE::TGroup::*)(const TSPLINE::TObjectPtr &)) 
            &TSPLINE::TGroup::removeObject)
        .def("removeObject", (bool (TSPLINE::TGroup::*)(unsigned int, unsigned int)) 
            &TSPLINE::TGroup::removeObject)
        .def("replaceObject", &TSPLINE::TGroup::replaceObject);

    // TVertex:
    py::class_<TSPLINE::TVertex, TSPLINE::TVertexPtr>(m,
        "Vertex", py::base<TSPLINE::TMappableObject>(), "Coordinates (s, t) in the parametric space")
        .def(py::init<const std::string &, TSPLINE::Real, TSPLINE::Real>(),
             py::arg("name")="", py::arg("s")=0., py::arg("t")=0.)
        .def("setNeighbour", &TSPLINE::TVertex::setNeighbours)
        .def("setNeighboursByVertices", &setNeighboursByVertices)
        .def("getS", &TSPLINE::TVertex::getS)
        .def("getT", &TSPLINE::TVertex::getT)
        .def("numberOfNeighbors", &TSPLINE::TVertex::numberOfNeighbors);
        // .def_read_only("pos", [](){return std::array<double, 2>{&TSPLINE::TVertex::getS());

    // TEdge:
    py::class_<TSPLINE::TEdge, TSPLINE::TEdgePtr>(m, "Edge", 
        py::base<TSPLINE::TMappableObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("patch", &patchEdge)
        .def("setStartVertex", &TSPLINE::TEdge::setStartVertex)
        .def("getStartVertex", &TSPLINE::TEdge::getStartVertex)
        .def("setEndVertex", &TSPLINE::TEdge::setEndVertex)
        .def("getEndVertex", &TSPLINE::TEdge::getEndVertex)
        .def("setLeftFace", &TSPLINE::TEdge::setLeftFace)
        .def("getLeftFace", &TSPLINE::TEdge::getLeftFace)
        .def("setRightFace", &TSPLINE::TEdge::setRightFace);

    // TFace:
    py::class_<TSPLINE::TFace, TSPLINE::TFacePtr>(m, "Face",
        py::base<TSPLINE::TMappableObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("addLink", &TSPLINE::TFace::addLink)
        .def("addBlendingNode", &TSPLINE::TFace::addBlendingNode);

    // TLink:
    py::class_<TSPLINE::TLink, TSPLINE::TLinkPtr>(m, "Link",
        py::base<TSPLINE::TObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("setOrientedEdge", &TSPLINE::TLink::setOrientedEdge);

    // TEdgeCondition:
    py::class_<TSPLINE::TEdgeCondition, TSPLINE::TEdgeConditionPtr>(m, "EdgeCondition",
        py::base<TSPLINE::TObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("setEdgeCondition", &TSPLINE::TEdgeCondition::setEdgeCondition);

    // TPoint:
    py::class_<TSPLINE::TPoint, TSPLINE::TPointPtr>(m, "Point",
            py::base<TSPLINE::TObject>(), "location of a Vertex in the cartesian space") 
        .def(py::init<const std::string &, TSPLINE::Real, TSPLINE::Real, 
            TSPLINE::Real, TSPLINE::Real>(), "docs here", 
            py::arg("name")="", py::arg("x")=0., py::arg("y")=0.,
            py::arg("z")=0., py::arg("w")=1.)
        .def("setTNode", &TSPLINE::TPoint::setTNode);

    // TPointset:
    py::class_<TSPLINE::TPointset, TSPLINE::TPointsetPtr>(m, "Pointset", 
        py::base<TSPLINE::TGroup>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="");

    // TNode:
    py::class_<TSPLINE::TNode, TSPLINE::TNodePtr>(m, "Node",
        py::base<TSPLINE::TObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("setTMappableObject", &TSPLINE::TNode::setTMappableObject)
        .def("setTPoint", &TSPLINE::TNode::setTPoint)
        .def("getTMapper", &TSPLINE::TNode::getTMapper);


    // TNodeV4
    py::class_<TSPLINE::TNodeV4, TSPLINE::TNodeV4Ptr>(m, "NodeV4",
        py::base<TSPLINE::TNode>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("setNeighbours", &TSPLINE::TNodeV4::setNeighbours);

    // TConnect:
    py::class_<TSPLINE::TConnect, TSPLINE::TConnectPtr>(m, "Connect", 
        py::base<TSPLINE::TGroup>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="");

    // TSpline:
    py::class_<TSPLINE::TSpline, TSPLINE::TSplinePtr>(m, "Spline",
        py::base<TSPLINE::TObject>(), "docs")
        .def(py::init<const std::string &, int, bool>(), py::arg("name")="",
             py::arg("degree")=3, py::arg("force_bezier_end_condition")=false)
        .def("setTImage", &TSPLINE::TSpline::setTImage)
        .def("setTConnect", &TSPLINE::TSpline::setTConnect)
        .def("setTPointset", &TSPLINE::TSpline::setTPointset)
        .def("setSDegree", &TSPLINE::TSpline::setSDegree)
        .def("setTDegree", &TSPLINE::TSpline::setTDegree);    

    // TImage:
    py::class_<TSPLINE::TImage, TSPLINE::TImagePtr>(m, "Image",
        py::base<TSPLINE::TObject>(), "docs")
        .def(py::init<const std::string &>(), py::arg("name")="")
        .def("addFace", &TSPLINE::TImage::addFace)
        .def("addLink", &TSPLINE::TImage::addLink)
        .def("addEdge", &TSPLINE::TImage::addEdge)
        .def("addVertex", &TSPLINE::TImage::addVertex);

    // TTesselator
    py::class_<TSPLINE::TTessellator, TSPLINE::TTessellatorPtr>(m, "Tessellator", "docs")
        .def(py::init<const TSPLINE::TSplinePtr &>())
        .def(py::init<const TSPLINE::TGroupPtr &>())
        .def("setResolution", &TSPLINE::TTessellator::setResolution)
        .def("interpolateAll", &TSPLINE::TTessellator::interpolateAll);

    // // TFactory:
    // py::class_<TSPLINE::TFactory, TSPLINE::TFactoryPtr>(m, "Factory", "docs")
    //     .def(py::init())
    //     .def("createTSpline", &TSPLINE::TFactory::createTSpline)
    //     .def("createTImage", &TSPLINE::TFactory::createTImage)
    //     .def("createTConnect", &TSPLINE::TFactory::createTConnect)
    //     .def("createTPointset", &TSPLINE::TFactory::createTPointset)
    //     .def("createTVertex", &TSPLINE::TFactory::createTVertex)
    //     .def("createTEdge", &TSPLINE::TFactory::createTEdge)
    //     .def("createTLink", &TSPLINE::TFactory::createTLink)
    //     .def("createTEdgeCondition", &TSPLINE::TFactory::createTEdgeCondition)
    //     .def("createTFace", &TSPLINE::TFactory::createTFace)
    //     .def("createTNode", &TSPLINE::TFactory::createTNode)
    //     .def("createTNodeV4", &TSPLINE::TFactory::createTNodeV4)
    //     .def("createTPoint", &TSPLINE::TFactory::createTPoint)
    //     .def("patchTSpline", 
    //         (void (TSPLINE::TFactory::*)(const TSPLINE::TSplinePtr &, const std::string &, const std::string &, const std::string &, int))
    //             &TSPLINE::TFactory::patchTSpline,
    //             py::arg("spline"), py::arg("tmesh"), py::arg("nodes"), py::arg("points"), py::arg("degree")=3)
    //     .def("patchTPoint", 
    //         (void (TSPLINE::TFactory::*)(const TSPLINE::TPointPtr &, const std::string &))
    //             &TSPLINE::TFactory::patchTPoint)

    //     .def("prepareTNodeHalfLinkages", &TSPLINE::TFactory::prepareTNodeHalfLinkages)
    //     .def("prepareTJunctions", &TSPLINE::TFactory::prepareTJunctions)
    //     .def("prepareImageConnect", &TSPLINE::TFactory::prepareImageConnect);

    // TriMesh
    py::class_<TSPLINE::TriMesh, TSPLINE::TriMeshPtr>(m, "TriMesh", "docs")
        .def("getPoints", &getTriMeshPoints)
        .def("getNormals", &getTriMeshNormals)
        .def("getFaces", &getTriMeshFaces);

    py::class_<RhBuilder, RhBuilderPtr>(m, "RhBuilder", "docs")
        .def(py::init<const string &>())
        .def("findTSpline", &RhBuilder::findTSpline)
        .def("findTGroup", &RhBuilder::findTGroup);

    m.def("findLinks", &findTLinkByStartEndVertices);
    m.def("prepareTJunctions", &prepareTJunctions);
    m.def("prepareTNodeHalfLinkages", &prepareTNodeHalfLinkages);
    m.def("prepareImageConnect", &prepareImageConnect);
}


PYBIND11_PLUGIN(_tspline)
{
    py::module m("_tspline", "tspline bindings");
    init_tspline(m);
    return m.ptr();
}