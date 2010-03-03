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
#ifndef FieldField_fvPatchField_scalar_cxx
#define FieldField_fvPatchField_scalar_cxx


//---------------------------------------------------------------------------
//It is necessary to include "director's" classes above first's DIRECTOR_INCLUDE
%include "src/finiteVolume/directors.hxx"


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/FieldFields/FieldField.cxx"

%include "src/finiteVolume/fields/fvPatchFields/fvPatchField_scalar.cxx"

%ignore Foam::FieldField< Foam::fvPatchField, Foam::scalar >::FieldField;
%ignore Foam::FieldField< Foam::fvPatchField, Foam::scalar >::T;

%inline
%{
    typedef Foam::FieldField< Foam::fvPatchField, Foam::scalar > FieldField_fvPatchField_scalar;
%}

%template( FieldField_fvPatchField_scalar ) Foam::FieldField< Foam::fvPatchField, Foam::scalar >;


//---------------------------------------------------------------------------
%extend Foam::FieldField< Foam::fvPatchField, Foam::scalar >
{
    int __len__()
    {
        return self->size();
    }
    
    scalarField& __getitem__( const Foam::label theIndex )
    {
            return self->operator[]( theIndex );
    }

    void __setitem__( const Foam::label theIndex, const scalarField& theValue )
    {
        self->operator[]( theIndex ) = theValue;
    }
}


//---------------------------------------------------------------------------
#endif
    
