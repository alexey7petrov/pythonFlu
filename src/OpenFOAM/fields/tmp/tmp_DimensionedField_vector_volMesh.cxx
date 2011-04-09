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
#ifndef tmp_DimensionedField_vector_volMesh_cxx
#define tmp_DimensionedField_vector_volMesh_cxx


//---------------------------------------------------------------------------
// Keep on corresponding "director" includes at the top of SWIG defintion file

%include "src/OpenFOAM/directors.hxx"

%include "src/finiteVolume/directors.hxx"


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/tmp/tmp.cxx"

%include "src/OpenFOAM/fields/DimensionedFields/DimensionedField_vector_volMesh.cxx"


//---------------------------------------------------------------------------
%template( tmp_DimensionedField_vector_volMesh ) Foam::tmp< Foam::DimensionedField< Foam::vector, Foam::volMesh > >;

%inline
{
    namespace Foam
    {
        typedef tmp< DimensionedField< vector, volMesh > > tmp_DimensionedField_vector_volMesh;
    }
}


//---------------------------------------------------------------------------
#endif