#pragma once
#include "StdAfx.h" 
//Declaration of CreateLayer():
Acad::ErrorStatus CreateLayer(const TCHAR* aszLayerName, AcDbObjectId& arCLayerId);

//Declaration of CreateBlockRecord():
Acad::ErrorStatus CreateBlockRecord(const TCHAR* aszBlockTableRecordName);

