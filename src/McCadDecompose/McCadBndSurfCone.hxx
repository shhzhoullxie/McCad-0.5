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

public:

    McCadBndSurfCone();
    McCadBndSurfCone(const TopoDS_Face &theFace);
    virtual ~McCadBndSurfCone();

    /**< Detect the collision between cone and triangle */
    virtual Standard_Boolean TriangleCollision(McCadTriangle *& triangle, POSITION & eSide);
    /**< Generate the cone solid for Boolean operation */
    void GenExtCone(Standard_Real length);

    /**< The cone has assisted splitting surface or not */
    Standard_Boolean HasAstSplitSurfaces();

    /**< Has assisted splitting surface for separating cone and plane */
    Standard_Boolean HasConePlnSplitSurf();
    /**< Has assisted splitting surface for separating cylinder and cone */
    Standard_Boolean HasConeCylnSplitSurf();
    /**< Has assisted splitting surface for separating cone and cone */
    Standard_Boolean HasConeConeSplitSurf();

    gp_Pnt GetPeak() const;      /**< Get the peak point of cone */
    gp_Pnt GetBottomCenter() const;     /**< Get the center of cone bottom */
    gp_Vec GetAxis() const;             /**< Get the axis of cone */

    virtual Standard_Boolean IsPntOnSurf(gp_Pnt &thePnt, Standard_Real disTol); /**< The point is on surface or not */

private:

    /**< Detect the collision between cone and triangle with Boolean operation*/
    Standard_Boolean BooleanCollisionDetect(McCadTriangle *& triangle, POSITION &eSide);

    gp_Pnt m_peak;         /**< The peak point of cone */
    TopoDS_Face m_cylSurf; /**< Generated a close and extended cone surface */

    Standard_Boolean m_bHasAstSplitSurfaces;/**< If the cylinder has assisted splitting surface */
    Bnd_Box m_ConeBndBox;                   /**< The boundary box of whole cylinder */

    gp_Pnt m_Radian;        /**< The radian of cylinder */
    gp_Vec m_Center;        /**< The center of cylinder, namely one point on the axis */


};




#endif // MCCADBNDSURFCONE_HXX
