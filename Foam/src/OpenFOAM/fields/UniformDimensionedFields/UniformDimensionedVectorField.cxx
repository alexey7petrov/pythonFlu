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
%module "Foam.src.OpenFOAM.fields.UniformDimensionedFields.UniformDimensionedVectorField";
%{
  #include "src/OpenFOAM/fields/UniformDimensionedFields/UniformDimensionedVectorField.hh"
%}


//---------------------------------------------------------------------------
%import "src/common.hxx"

#if FOAM_VERSION( <, 010600 )
#define UniformDimensionedVectorField_cxx
#endif


//---------------------------------------------------------------------------
#ifndef UniformDimensionedVectorField_cxx
#define UniformDimensionedVectorField_cxx


//---------------------------------------------------------------------------
%import "src/OpenFOAM/fields/UniformDimensionedFields/UniformDimensionedField.cxx"

%import "src/OpenFOAM/dimensionedTypes/dimensionedVector.cxx"

%ignore Foam::UniformDimensionedField< Foam::vector >::typeName;
%ignore Foam::UniformDimensionedField< Foam::vector >::debug;

%template( uniformDimensionedVectorField ) Foam::UniformDimensionedField< Foam::vector >;

%include "src/OpenFOAM/fields/UniformDimensionedFields/UniformDimensionedVectorField.hh"


//--------------------------------------------------------------------------
%import "src/try_reverse_operator.hxx"

%feature ("pythonprepend") Foam::UniformDimensionedField< Foam::vector >::TRY_REVERSE_PYPREPEND( and );

%extend Foam::UniformDimensionedField< Foam::vector >
{
  Foam::UniformDimensionedField< Foam::vector >( const IOobject& io )
  {
    return new Foam::UniformDimensionedField< Foam::vector >( io );
  }
  
  TRY_REVERSE_EXTEND( and );
}


//---------------------------------------------------------------------------
#endif