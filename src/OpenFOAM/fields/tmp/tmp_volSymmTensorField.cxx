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
#ifndef tmp_volSymmTensorrField_cxx
#define tmp_volSymmTensorField_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/tmp/tmp_symmTensorField.cxx"

%include "src/OpenFOAM/fields/GeometricFields/GeometricField_SymmTensor_fvPatchField_volMesh.cxx"

%template( tmp_volSymmTensorField ) Foam::tmp< Foam::GeometricField< Foam::symmTensor, Foam::fvPatchField, Foam::volMesh > >;

%extend Foam::tmp< Foam::GeometricField< Foam::symmTensor, Foam::fvPatchField, Foam::volMesh > >
{
    bool operator==( const Foam::UList< Foam::symmTensor >& theArg )
    {
        Foam::UList< Foam::symmTensor >* aSelf = static_cast< Foam::UList< Foam::symmTensor >* >( self->ptr() );
        return *aSelf == theArg;
    }
}

%inline
{
    namespace Foam
    {
        typedef tmp< GeometricField< symmTensor, fvPatchField, volMesh > > tmp_volSymmTensorField;
    }
}


//---------------------------------------------------------------------------
#endif