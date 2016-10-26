#ifndef MCCADBNDSURFCONE_HXX
#define MCCADBNDSURFCONE_HXX
#include "McCadBndSurface.hxx"

class McCadBndSurfCone : public McCadBndSurface
{
public:  

    void* operator new(size_t,void* anAddress)
    {
        return anAddress;
    }
    void* operator new(size_t size)
    {
        return Standard::Allocate(size);
    }
    void  operator delete(void *anAddress)
    {
        if (anAddress) Standard::Free((Standard_Address&)anAddress);
    }

    McCadBndSurfCone();
    McCadBndSurfCone(const TopoDS_Face & theFace);
    ~McCadBndSurfCone();

public:

    /**<  */
    virtual Standard_Boolean TriangleCollision(McCadTriangle *& triangle, POSITION & eSide);
    /**<  */
    void GenExtCone(Standard_Real length);

    virtual Standard_Boolean CanFuseSurf(McCadBndSurface *& pSurf);
    virtual TopoDS_Face FuseSurfaces(McCadBndSurface *& pSurf);
    virtual Standard_Boolean IsPntOnSurf(gp_Pnt &thePnt, Standard_Real disTol);


};





#endif // MCCADBNDSURFCONE_HXX
