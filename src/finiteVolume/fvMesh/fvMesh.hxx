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
//  See https://csrcs.pbmr.co.za/svn/nea/prototypes/reaktor/pyfoam
//
//  Author : Alexey PETROV


//---------------------------------------------------------------------------
#ifndef fvMesh_hxx
#define fvMesh_hxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/meshes/polyMesh/polyMesh.cxx"

%include "src/OpenFOAM/containers/Lists/List/List_pPolyPatch.cxx"

%include "src/OpenFOAM/db/Time/Time.cxx"

%include "src/OpenFOAM/db/objectRegistry.cxx"

%include "src/OpenFOAM/meshes/lduMesh.cxx"

%include "src/OpenFOAM/matrices/lduMatrix/lduAddressing/lduAddressing.cxx"

%include "src/finiteVolume/fvMesh/fvBoundaryMesh.cxx"

%include "src/finiteVolume/interpolation/surfaceInterpolation/surfaceInterpolation.cxx"

%include "src/finiteVolume/fields/volFields/volFieldsFwd.hxx"

%include "src/finiteVolume/fields/surfaceFields/surfaceFieldsFwd.hxx"

%{
    #include "fvMesh.H"
    #include "volMesh.H"
%}


//---------------------------------------------------------------------------
#endif