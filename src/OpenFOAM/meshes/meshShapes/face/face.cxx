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
#ifndef face_cxx
#define face_cxx


//---------------------------------------------------------------------------
%module "Foam.src.OpenFOAM.meshes.meshShapes.face.face";
%{
   #include "src/OpenFOAM/meshes/meshShapes/face/face.hpp"
%}


//---------------------------------------------------------------------------
%import "src/OpenFOAM/primitives/Lists/labelList.cxx"

%import "src/OpenFOAM/meshes/primitiveShapes/point/pointField.cxx"

%import "src/OpenFOAM/fields/Fields/vectorField.cxx"

%ignore Foam::face::ray;
%ignore Foam::face::intersection;
%ignore Foam::face::nearestPoint;

#if FOAM_BRANCH_VERSION( dev, ==, 010500 )
  %ignore Foam::face::fastIntersection;
#endif

%include <face.H>


//---------------------------------------------------------------------------
#endif
