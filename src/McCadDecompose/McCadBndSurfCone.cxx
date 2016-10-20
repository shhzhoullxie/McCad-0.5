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


/** ***************************************************************************
* @brief
* @param
* @return
*
* @date
* @author
******************************************************************************/
Standard_Boolean McCadBndSurfCone::TriangleCollision(McCadTriangle *& triangle, POSITION & eSide)
{

}


Standard_Boolean McCadBndSurfCone::IsPntOnSurf(gp_Pnt &thePnt, Standard_Real disTol)
{
       return Standard_False;
}
