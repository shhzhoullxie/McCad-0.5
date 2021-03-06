// File generated by CPPExt (Transient)
//
//                     Copyright (C) 1991 - 2000 by  
//                      Matra Datavision SA.  All rights reserved.
//  
//                     Copyright (C) 2001 - 2004 by
//                     Open CASCADE SA.  All rights reserved.
// 
// This file is part of the Open CASCADE Technology software.
//
// This software may be distributed and/or modified under the terms and
// conditions of the Open CASCADE Public License as defined by Open CASCADE SA
// and appearing in the file LICENSE included in the packaging of this file.
//  
// This software is distributed on an "AS IS" basis, without warranty of any
// kind, and Open CASCADE SA hereby disclaims all such warranties,
// including without limitation, any warranties of merchantability, fitness
// for a particular purpose or non-infringement. Please see the License for
// the specific terms and conditions governing rights and limitations under the
// License.

#ifndef _Handle_McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger_HeaderFile
#define _Handle_McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_TCollection_MapNode_HeaderFile
#include <Handle_TCollection_MapNode.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(TCollection_MapNode);
class McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger);

class Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger) : public Handle(TCollection_MapNode) {
  public:
    Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)():Handle(TCollection_MapNode)() {} 
    Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)(const Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)& aHandle) : Handle(TCollection_MapNode)(aHandle) 
     {
     }

    Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)(const McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger* anItem) : Handle(TCollection_MapNode)((TCollection_MapNode *)anItem) 
     {
     }

    Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)& operator=(const Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)& operator=(const McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger* operator->() const
     {
      return (McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger *)ControlAccess();
     }

//   Standard_EXPORT ~Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger)();
 
   Standard_EXPORT static const Handle(McCadModelManager_DataMapNodeOfDataMapOfShapePtrInteger) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif
