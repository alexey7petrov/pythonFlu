//  VulaSHAKA (Simultaneous Neutronic, Fuel Performance, Heat And Kinetics Analysis)
//  Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  See https://vulashaka.svn.sourceforge.net/svnroot/vulashaka
//
//  Author : Alexey PETROV


//---------------------------------------------------------------------------
#include "src/common.hpp"

#if FOAM_VERSION( <, 010500 )
#define incompressibleLESModel_hpp
#endif


//-----------------------------------------------------------------------------
#ifndef incompressibleLESModel_hpp
#define incompressibleLESModel_hpp


//----------------------------------------------------------------------------
#include "src/turbulenceModels/incompressible/turbulenceModel.hpp"

// #include "LESdelta.H"
// #include "fvm.H"
// #include "fvc.H"

#include "src/finiteVolume/fvMatrices/fvMatrices.hpp"

#include "src/transportModels/incompressible/transportModel.hpp"

// #include "wallFvPatch.H"

#include "src/finiteVolume/cfdTools/general/bound.hpp"

#include "src/OpenFOAM/fields/tmp/autoPtr.hpp"

// #include "runTimeSelectionTables.H"

#include "src/OpenFOAM/db/IOdictionary.hpp"


//----------------------------------------------------------------------------
#if FOAM_VERSION( ==, 010500 )
  #include <LES/incompressible/LESModel/LESModel.H>
#endif

#if FOAM_VERSION( >=, 010600 )
  #include <incompressible/LES/LESModel/LESModel.H>
#endif


//---------------------------------------------------------------------------
#endif