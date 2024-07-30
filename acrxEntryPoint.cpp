// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "utilties.h"
#include <memory>
#include "Tchar.h" // _T
//-----------------------------------------------------------------------------
#define szRDS _RXST("ADSK")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep03App : public AcRxArxApp {

public:
	CStep03App () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	static void AsdkStep03_CREATE_DEFAULT(void) {
		AcDbObjectId LayerId;
		if (CreateLayer(_T("USER"), LayerId) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create layer record."));
			return;
		}
		applyCurDwgLayerTableChanges(); // call the ObjectARX global function applyCurDwgLayerTableChanges(). This function will force AutoCAD to update itself to use any changes made to any layer table records in the drawing currently in the AutoCAD editor. 
		acutPrintf(_T("\nLayer USER successfully created"));
		// Create a new block definition named "EMPLOYEE"
		if (CreateBlockRecord(_T("EMPLOYEE")) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create block record"));
			return;
		}
		acutPrintf(_T("\nBlock record EMPLOYEE successfully created"));
	}
	static void AsdkStep03_CREATE_BLOCK_RECORD(void) {
		TCHAR szBlocTableRecordName[128];
		if (acedGetString(NULL, _T("\nEnter record name: "), szBlocTableRecordName) != RTNORM)
			return;

		// Create a new block definition named "EMPLOYEE"
		if (CreateBlockRecord(szBlocTableRecordName) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create block record"));
			return;
		}
		acutPrintf(_T("\nBlock record %s successfully created"), szBlocTableRecordName);
	}
	static void AsdkStep03_CREATE_LAYER(void) {
		AcDbObjectId LayerId;
		TCHAR szLayerName[128];
		if (acedGetString(NULL, _T("\nEnter layer name: "), szLayerName) != RTNORM)
			return;
		if (CreateLayer(szLayerName, LayerId) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create layer record"));
			return;
		}
		applyCurDwgLayerTableChanges(); // call the ObjectARX global function applyCurDwgLayerTableChanges(). This function will force AutoCAD to update itself to use any changes made to any layer table records in the drawing currently in the AutoCAD editor. 
		acutPrintf(_T("\nLayer %s successfully created"), szLayerName);
	}
	static void AsdkStep03_SETLAYER(void) {
		AcDbBlockTableRecordPointer pBlockTableRecord(acdbHostApplicationServices()->workingDatabase()->currentSpaceId(), AcDb::kForWrite);
		if (pBlockTableRecord.openStatus() != Acad::eOk) {
			acutPrintf(_T("\nERROR: Cannot open BlockTableRecord"));
			return;
		}
		// Obtain a block table record iterator 
		AcDbBlockTableRecordIterator* pIt{nullptr};
		if (pBlockTableRecord->newIterator(pIt) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Cannot create Model Space BlockTableRecordIterator"));
			return;
		}
		std::unique_ptr<AcDbBlockTableRecordIterator> iteratorPtr(pIt);
		// Iterate through the MODEL_SPACE
		for (pIt->start(); !pIt->done(); pIt->step()) {
			AcDbObjectId entityId;
			pIt->getEntityId(entityId);
			AcDbEntityPointer pEntity(entityId);
			if (pEntity.openStatus() != Acad::eOk)
				continue;
			// Check if the entity is a block reference 
			if (pEntity->isA() != AcDbBlockReference::desc())
				continue;
			// open object
			AcDbObjectId blockId = (AcDbBlockReference::cast(pEntity.object()))->blockTableRecord();
			AcDbBlockTableRecordPointer pCurrentEntityBlock(blockId);
			if (pCurrentEntityBlock.openStatus() != Acad::eOk)
				continue;			
			TCHAR* szBlockName{nullptr};
			pCurrentEntityBlock->getName(szBlockName); // string that is a dynamically allocated copy and needs to be freed 
			std::unique_ptr<TCHAR, decltype(&acdbFree)> pBlockName(szBlockName, &acdbFree);
			if (_tcscmp(szBlockName, _T("EMPLOYEE")) == 0) { // check if the block table record's name is "EMPLOYEE"
				if (pEntity->upgradeOpen() == Acad::eOk) {
					pEntity->setLayer(_T("USER")); // Change the layer
					acutPrintf(_T("Change the layer of block table record EMPLOYEE to USER"));
				}
			}
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep03App)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _SETLAYER, SETLAYER, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _CREATE_DEFAULT, CREATE_DEFAULT, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _CREATE_BLOCK_RECORD, CREATE_BLOCK_RECORD, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _CREATE_LAYER, CREATE_LAYER, ACRX_CMD_TRANSPARENT, NULL)

