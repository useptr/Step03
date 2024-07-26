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
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CStep03App class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, ADSKMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void ADSKMyGroupMyCommand () {
		// Put your command code here

	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, ADSKMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void ADSKMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, ADSKMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void ADSKMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CStep03App class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CStep03App, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}

	static void AsdkStep03_CREATE_DEFAULT(void) {
		AcDbObjectId layerId;
		if (createLayer(_T("USER"), layerId) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create layer record."));
			return;
		}
		applyCurDwgLayerTableChanges(); // call the ObjectARX global function applyCurDwgLayerTableChanges(). This function will force AutoCAD to update itself to use any changes made to any layer table records in the drawing currently in the AutoCAD editor. 
		acutPrintf(_T("\nLayer USER successfully created"));
		// Create a new block definition named "EMPLOYEE"
		if (createBlockRecord(_T("EMPLOYEE")) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create block record"));
			return;
		}
		acutPrintf(_T("\nBlock record EMPLOYEE successfully created"));
	}
	static void AsdkStep03_CREATE_BLOCK_RECORD(void) {
		TCHAR recordName[128];
		if (acedGetString(NULL, _T("\nEnter record name: "), recordName) != RTNORM)
			return;

		// Create a new block definition named "EMPLOYEE"
		if (createBlockRecord(recordName) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create block record"));
			return;
		}
		acutPrintf(_T("\nBlock record %s successfully created"), recordName);
	}
	static void AsdkStep03_CREATE_LAYER(void) {
		AcDbObjectId layerId;
		TCHAR layerName[128];
		if (acedGetString(NULL, _T("\nEnter layer name: "), layerName) != RTNORM)
			return;
		if (createLayer(layerName, layerId) != Acad::eOk) {
			acutPrintf(_T("\nERROR: Couldn't create layer record"));
			return;
		}
		applyCurDwgLayerTableChanges(); // call the ObjectARX global function applyCurDwgLayerTableChanges(). This function will force AutoCAD to update itself to use any changes made to any layer table records in the drawing currently in the AutoCAD editor. 
		acutPrintf(_T("\nLayer %s successfully created"), layerName);
	}
	static void AsdkStep03_SETLAYER(void) {
		AcDbBlockTable* pBlockTable;
		if (acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't open the block table"));
			return;
		}
		AcDbBlockTableRecord* pBlockTableRecord;
		// Get the MODEL SPACE block table record
		if (pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't get Model Space"));
			pBlockTable->close();
			return;
		}
		pBlockTable->close();
		// Obtain a block table record iterator 
		AcDbBlockTableRecordIterator* pIt;
		if (pBlockTableRecord->newIterator(pIt) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't create Model Space iterator"));
			pBlockTableRecord->close();
			return;
		}
		// Iterate through the MODEL_SPACE
		for (pIt->start(); !pIt->done(); pIt->step()) {
			AcDbEntity* pEntity;
			// Obtain the entity 
			if (pIt->getEntity(pEntity) != Acad::eOk) // pEntity need close
				continue;
			// Check if the entity is a block reference 
			if (pEntity->isA() != AcDbBlockReference::desc())
				continue;
			AcDbBlockTableRecord* pCurrentEntityBlock;
			// Obtain the block table record of the reference (AcDbBlockReference::blockTableRecord() )
			AcDbObjectId blockId = (AcDbBlockReference::cast(pEntity))->blockTableRecord();
			// open object
			if (acdbOpenObject(pCurrentEntityBlock, blockId) == Acad::eOk) { // pCurrentEntityBlock need close
				TCHAR* blockName;
				pCurrentEntityBlock->getName(blockName); // blockName need free
				if (_tcscmp(blockName, _T("EMPLOYEE")) == 0) { // check if the block table record's name is "EMPLOYEE"
					if (pEntity->upgradeOpen() == Acad::eOk) {
						pEntity->setLayer(_T("USER")); // Change the layer(setLayer())
						acutPrintf(_T("Change the layer of block table record EMPLOYEE to USER"));
					}
				}
				acdbFree(blockName);
				pCurrentEntityBlock->close();
			}
			pEntity->close();
		}
		delete pIt;
		pBlockTableRecord->close();
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep03App)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _SETLAYER, SETLAYER, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _CREATE_DEFAULT, CREATE_DEFAULT, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _CREATE_BLOCK_RECORD, CREATE_BLOCK_RECORD, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, AsdkStep03, _CREATE_LAYER, CREATE_LAYER, ACRX_CMD_TRANSPARENT, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, ADSKMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, ADSKMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CStep03App, ADSKMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
//ACED_ADSSYMBOL_ENTRY_AUTO(CStep03App, MyLispFunction, false)

