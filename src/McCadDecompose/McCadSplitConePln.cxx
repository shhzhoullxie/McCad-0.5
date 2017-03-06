#include "McCadSplitConePln.hxx"

#include "McCadBndSurface.hxx"
#include "McCadAstSurface.hxx"

#include <BRepBuilderAPI_MakeFace.hxx>

#include <BRepTools.hxx>
#include <gp_Pln.hxx>

#include "../McCadTool/McCadGeomTool.hxx"

McCadSplitConePln::McCadSplitConePln()
{
}

McCadSplitConePln::~McCadSplitConePln()
{
}


/** ***************************************************************************
* @brief  Generate the assisted surfaces and add them to the assisted splitting
*         surface list
* @param  McCadBndSurface input cone face, assisted splitting face list
* @return void
*
* @date 01/03/2017
* @modify 06/03/2015
* @author  Lei Lu
******************************************************************************/
void McCadSplitConePln::GenSplitSurfaces( McCadDcompSolid *& pSolid)
{
    vector<McCadBndSurface *>  &cone_list     = pSolid->m_CylinderList;
    vector<McCadBndSurface *>  &plane_list    = pSolid->m_PlaneList;
    vector<McCadAstSurface*>   &AstFaceList   = pSolid->m_AstFaceList;

    m_fLength = pSolid->m_fBoxSqLength; // Set the length of created splitting surface

    for(int i = 0; i < cone_list.size(); i++ )
    {
        // The cone has common straight edge with planes or not
        Standard_Boolean bHasStraightEdge = Standard_False;

        McCadBndSurfCone *pBndCone = (McCadBndSurfCone*)cone_list.at(i);


        ///< if the cone is not splitting surface, or it is a entire cylinder.
        ///< it does not need to be added assisted splitting surface
        if(pBndCone->GetSplitSurfNum() == 0 || pBndCone->GetRadian() >= M_PI*2)
        {
            continue;
        }
        ///< if the cone is concave, use different streagy to add splitting surface
        if(pBndCone->Orientation() == TopAbs_REVERSED )
        {

            // Wait for the new code


            continue;
        }
        else if(pBndCone->Orientation() == TopAbs_FORWARD)
        {
            ///< if the cone has a common straight edge with a plane, add a plane through
            ///< the edge and axis of cylinder as assisted splitting surface.
            for(int j = 0; j < plane_list.size(); j++ )
            {
                McCadBndSurface *pBndPln = plane_list.at(j);

                if(FindComLineEdge(pBndCone,pBndPln))
                {
                    bHasStraightEdge = Standard_True;
                }
            }
        }

        /** If the cylinder does not connect with other cylinders or planes with a straight edge
            but it is still a splitting surface, then add assisted splitting all the same.*/
        //TopoDS_Face theCyln = (TopoDS_Face)(*pBndCyln);
        //if (!HasStraightEdge(theCyln))// Lei Lu modification
        if (!bHasStraightEdge)
        {
            // GenAssistSurfaces(pBndCyln,AstFace_list);
            // pBndCyln->AddAstSurfaces(Standard_True);
        }
    }

    for(int i = 0; i < cone_list.size(); i++ )
    {
        McCadBndSurfCone *pBndCone = (McCadBndSurfCone*)cone_list.at(i);
        //if(pBndCone->HasConePlnSplitSurf())
        {
            CrtSplitSurfaces(pBndCone,AstFaceList);
        }
    }

    // Merge the generated assisted splitting surfaces
    if(AstFaceList.size() >= 2)
    {
      //  MergeSurfaces(AstFaceList);
    }
}


/** ***************************************************************************
* @brief  Judge the input two surfaces have common connected edges or not
* @param  McCadBndSurface * pSurfA,
          McCadBndSurface * pSurfB,
          McCadEdge *& pEdge
* @return Standard_Boolean
*
* @date 13/07/2015
* @modify 13/07/2015
* @author  Lei Lu
******************************************************************************/
Standard_Boolean McCadSplitConePln::FindComLineEdge(McCadBndSurfCone *& pSurfCone,
                                        McCadBndSurface *& pSurfPln)
{
    /// Judge the surfaces have the common straight edge
    for(unsigned i = 0; i < pSurfCone->GetEdgeList().size(); i++)
    {
        McCadEdge *pEdgeA = pSurfCone->GetEdgeList().at(i);
        if(pEdgeA->GetType() != Line || !pEdgeA->CanAddAstSplitSurf())
        {
            continue;
        }

        for(unsigned j = 0; j < pSurfPln->GetEdgeList().size(); j++)
        {
            McCadEdge *pEdgeB = pSurfPln->GetEdgeList().at(j);
            if(pEdgeB->GetType() != Line )
            {
                continue;
            }

            if (pEdgeA->IsSame(pEdgeB,1.0e-5))
            {
                /// Get the first vertex of edge
                gp_Pnt pntStart = pEdgeA->StartPoint();

                /// Get the normals of each surface
                gp_Dir normalA = McCadGeomTool::NormalOnFace(*pSurfCone,pntStart);
                gp_Dir normalB = McCadGeomTool::NormalOnFace(*pSurfPln,pntStart);

                Standard_Real angle = normalA.Angle(normalB);

                if(angle < 1.0e-4)
                {
                    pEdgeA->SetConvexity(flat);
                    pEdgeB->SetConvexity(flat);
                }

                if(angle >= 0.5*M_PI && angle <= M_PI)
                {
                    continue;
                }
                else
                {
                    pSurfCone->AddConePlnSplitEdge(pEdgeA);
                }
                return Standard_True;
            }
        }
    }

    return Standard_False;
}




/** ***************************************************************************
* @brief
*
* @param McCadBndSurfCylinder *& pCylnFace,
         vector<McCadAstSurface*> & astFace_list  >> The generated splitting
         surface is added into this face list.
* @return void
*
* @date
* @modify
* @author  Lei Lu
******************************************************************************/
void McCadSplitConePln::CrtSplitSurfaces(McCadBndSurfCone *& pConeFace,
                                         vector<McCadAstSurface*> & astFace_list)
{
    int iEdgeNum = pConeFace->GetConePlnSplitEdgeList().size();
    if (iEdgeNum  == 1)
    {
         McCadEdge *pEdge = pConeFace->GetConePlnSplitEdgeList().at(0);
         McCadAstSurfPlane *pAstSplitSurf = CrtSplitSurfThroughEdge(pConeFace,pEdge);
         astFace_list.push_back(pAstSplitSurf);
    }
    else if (iEdgeNum == 2)
    {
        Standard_Real radian = pConeFace->GetRadian();

        /// if the radian of cylinder is smaller than 180 degree, use two splitting surfaces
        /// to split them
        if (radian < M_PI)
        {
            for(unsigned int i = 0 ; i < pConeFace->GetConePlnSplitEdgeList().size(); i++)
            {
                McCadEdge *pEdge = pConeFace->GetConePlnSplitEdgeList().at(i);
                McCadAstSurfPlane *pAstSplitSurf = CrtSplitSurfThroughEdge(pConeFace,pEdge);
                astFace_list.push_back(pAstSplitSurf);
            }
        }
        else /// if the radian of cylinder is lager than 120 degree, use one splitting
             /// surfaces which connect two edges
        {
            McCadEdge *pEdgeA = pConeFace->GetConePlnSplitEdgeList().at(0);
            McCadEdge *pEdgeB = pConeFace->GetConePlnSplitEdgeList().at(1);

            McCadAstSurfPlane* pAstSplitSurf = CrtSplitSurfThroughTwoEdges(pEdgeA,pEdgeB);
            astFace_list.push_back(pAstSplitSurf);
        }
    }
}



/** ***************************************************************************
* @brief
*
* @param McCadBndSurfCylinder *& pCylnFace,
         McCadEdge *& pEdge
* @return McCadAstSurfPlane *     >> Generated assisted splittin surface
*
* @date 13/06/2016
* @modify 13/06/2016
* @author  Lei Lu
******************************************************************************/
McCadAstSurfPlane* McCadSplitConePln::CrtSplitSurfThroughEdge(McCadBndSurfCone *& pConeFace,
                                                              McCadEdge *& pEdge)
{
    BRepTools::Update(*pConeFace);
    gp_Pnt center = pConeFace->GetPeak();

    gp_Pnt posStart = pEdge->StartPoint();
    gp_Pnt posEnd = pEdge->EndPoint();

    gp_Vec vec1(center, posStart), vec2(center, posEnd);
    gp_Vec vec = vec1 ^ vec2;
    vec.Normalize();
    gp_Dir dir(vec);

    Standard_Real size = m_fLength;
    gp_Pln pln(posStart, dir);
    TopoDS_Face surf = BRepBuilderAPI_MakeFace(pln,-size,size,-size,size).Face();

    McCadAstSurfPlane *pAstSurfA = new McCadAstSurfPlane(surf);
    pAstSurfA->SetEdge(*pEdge); // Set the edge throught by assisted splitting surface

    return pAstSurfA;
}




/** ***************************************************************************
* @brief Generate assisted splitting surface through two edges
*
* @param McCadEdge *& pEdgeA, McCadEdge *& pEdgeB
* @return McCadAstSurfPlane *     >> Generated assisted splittin surface
*
* @date 13/06/2016
* @modify 13/06/2016
* @author  Lei Lu
******************************************************************************/
McCadAstSurfPlane* McCadSplitConePln::CrtSplitSurfThroughTwoEdges(McCadEdge *& pEdgeA, McCadEdge *& pEdgeB)
{
    /// Get the start and end points of the curves, and calculate middle points
    gp_Pnt pntStartB = pEdgeB->StartPoint();
    gp_Pnt pntEndB = pEdgeB->EndPoint();

    gp_Pnt pntMidA = pEdgeA->MidPoint();

    /// Calculate the normal vector or plane through the two edges (three points)
    gp_Vec vec1(pntStartB, pntMidA), vec2(pntEndB, pntMidA);
    gp_Vec vec = vec1 ^ vec2;
    vec.Normalize();
    gp_Dir dir(vec);

    gp_Pln pln(pntMidA, dir);

    Standard_Real size = m_fLength;
    /// Generate the surface according to the normal vector
    TopoDS_Face face = BRepBuilderAPI_MakeFace(pln,-size,size,-size,size).Face();
    McCadAstSurfPlane *pSurf = new McCadAstSurfPlane(face);
    pSurf->SetCombined(Standard_True);

    return pSurf;
}
