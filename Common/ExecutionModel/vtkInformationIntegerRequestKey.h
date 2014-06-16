/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkInformationIntegerRequestKey.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkInformationIntegerRequestKey - key that can used to request integer values from the pipeline
// vtkInformationIntegerRequestKey is a vtkInformationIntegerKey that can
// used to request integer values from upstream. A good example of this is
// UPDATE_NUMBER_OF_PIECES where downstream can request that upstream provides
// data partitioned into a certain number of pieces. There are several components
// that make this work. First, the key will copy itself upstream during
// REQUEST_UPDATE_EXTENT. Second, after a successfull execution, it will stor
// its value into a data object's information using a specific key defined by
// its data member DataKey. Third, before execution, it will check if the requested
// value matched the value in the data object's information. If not, it will ask
// the pipeline to execute.
//
// The best way to use this class is to subclass it to set the DataKey data member.
// This is usually done in the subclass' constructor.

#ifndef __vtkInformationIntegerRequestKey_h
#define __vtkInformationIntegerRequestKey_h

#include "vtkCommonExecutionModelModule.h" // For export macro
#include "vtkInformationIntegerKey.h"

#include "vtkCommonInformationKeyManager.h" // Manage instances of this type.

class VTKCOMMONEXECUTIONMODEL_EXPORT vtkInformationIntegerRequestKey : public vtkInformationIntegerKey
{
public:
  vtkTypeMacro(vtkInformationIntegerRequestKey,vtkInformationIntegerKey);
  void PrintSelf(ostream& os, vtkIndent indent);

  vtkInformationIntegerRequestKey(const char* name, const char* location);
  ~vtkInformationIntegerRequestKey();

  // Description:
  // Returns true if a value of type DataKey does not exist in dobjInfo
  // or if it is different that the value stored in pipelineInfo using
  // this key.
  virtual bool NeedToExecute(vtkInformation* pipelineInfo,
                             vtkInformation* dobjInfo);

  // Description:
  // Copies the value stored in pipelineInfo using this key into
  // dobjInfo.
  virtual void StoreMetaData(vtkInformation* request,
                             vtkInformation* pipelineInfo,
                             vtkInformation* dobjInfo);

  // Description:
  // Copies the value stored in fromInfo using this key into toInfo
  // if request has the REQUEST_UPDATE_EXTENT key.
  virtual void CopyDefaultInformation(vtkInformation* request,
                                      vtkInformation* fromInfo,
                                      vtkInformation* toInfo);

protected:
  vtkInformationIntegerKey* DataKey;

private:
  vtkInformationIntegerRequestKey(const vtkInformationIntegerRequestKey&);  // Not implemented.
  void operator=(const vtkInformationIntegerRequestKey&);  // Not implemented.

};

#endif
