#include "McCadBndSurfCone.hxx"

McCadBndSurfCone::McCadBndSurfCone()
{
}

McCadBndSurfCone::McCadBndSurfCone(const TopoDS_Face &theFace):McCadBndSurface(theFace)
{

}

McCadBndSurfCone::~McCadBndSurfCone()
{
}


Standard_Boolean McCadBndSurfCone::TriangleCollision(McCadTriangle *& triangle, POSITION & eSide)
{

}

void McCadBndSurfCone::GenExtCone(Standard_Real length)
{

}

Standard_Boolean McCadBndSurfCone::CanFuseSurf(McCadBndSurface *& pSurf)
{

}

TopoDS_Face McCadBndSurfCone::FuseSurfaces(McCadBndSurface *& pSurf)
{

}

Standard_Boolean McCadBndSurfCone::IsPntOnSurf(gp_Pnt &thePnt, Standard_Real disTol)
{

}
