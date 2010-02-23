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
#if ( __FOAM_VERSION__ < 010600 )
%include "src/common.hxx"
#define UniformDimensionedVectorField_cxx
#endif


//---------------------------------------------------------------------------
#ifndef UniformDimensionedVectorField_cxx
#define UniformDimensionedVectorField_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/UniformDimensionedFields/UniformDimensionedField.cxx"

%include "src/OpenFOAM/dimensionedTypes/dimensionedVector.cxx"

%include "src/OpenFOAM/fields/GeometricFields/GeometricField_vector_fvsPatchField_surfaceMesh.cxx"

%ignore Foam::UniformDimensionedField< Foam::vector >::typeName;
%ignore Foam::UniformDimensionedField< Foam::vector >::debug;

%template( UniformDimensionedVectorField ) Foam::UniformDimensionedField< Foam::vector >;

%inline 
{
    namespace Foam
    {
     typedef UniformDimensionedField< vector > UniformDimensionedVectorField;
    }
}



%extend Foam::UniformDimensionedField< Foam::vector >
{
  Foam::UniformDimensionedField< Foam::vector >( const IOobject& io )
  {
    return new Foam::UniformDimensionedField< Foam::vector >( io );
  }

  Foam::tmp< Foam::GeometricField< Foam::scalar, Foam::fvsPatchField, Foam::surfaceMesh > >__and__
           ( const Foam::GeometricField< Foam::vector, Foam::fvsPatchField, Foam::surfaceMesh >& theArg )
  {
    return *self & theArg;
  }
  
}

//---------------------------------------------------------------------------
#endif