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
%module "Foam.src.turbulenceModels.incompressible.RAS.RASModel";
%{
  #include "src/turbulenceModels/incompressible/RAS/RASModel.hpp"
%}


//---------------------------------------------------------------------------
%include "src/common.hxx"

#if FOAM_VERSION( <, 010500 )
#define incompressibleRASModel_cxx
#endif


//-----------------------------------------------------------------------------
#ifndef incompressibleRASModel_cxx
#define incompressibleRASModel_cxx


//----------------------------------------------------------------------------
%import "src/turbulenceModels/incompressible/turbulenceModel.cxx"

%import "src/finiteVolume/fvMesh/fvMeshes.cxx"

%import "src/finiteVolume/fvMatrices/fvMatrices.cxx"

%import "src/transportModels/incompressible/transportModel.cxx"

%import "src/OpenFOAM/db/IOdictionary.cxx"

%import "src/OpenFOAM/db/Switch.cxx"

%import "src/finiteVolume/cfdTools/general/bound.cxx"


//----------------------------------------------------------------------------
%ignore Foam::incompressible::RASModel::k;

%ignore Foam::incompressible::RASModel::epsilon;

%ignore Foam::incompressible::RASModel::nut;

%rename( incompressible_RASModel ) Foam::incompressible::RASModel;

%include <incompressible/RASModel.H>


//---------------------------------------------------------------------------
%extend Foam::incompressible::RASModel
{
  Foam::volScalarField& ext_k()
  {
    return self->k()();
  }
  Foam::volScalarField& ext_epsilon()
  {
    return self->epsilon()();
  }
  Foam::volScalarField& ext_nut()
  {
    return self->nut()();
  }
}


//---------------------------------------------------------------------------
#endif
