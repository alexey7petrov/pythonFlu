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
#ifndef FieldField_fvPatchField_symmTensor_cxx
#define FieldField_fvPatchField_symmTensor_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/FieldFields/FieldField.cxx"

%include "src/OpenFOAM/containers/Lists/PtrList/PtrList_symmTensorField.cxx"

%include "src/finiteVolume/fields/fvPatchFields/fvPatchField_symmTensor.cxx"

%ignore Foam::FieldField< Foam::fvPatchField, Foam::symmTensor >::FieldField;

%inline
%{
    typedef Foam::FieldField< Foam::fvPatchField, Foam::symmTensor > FieldField_fvPatchField_symmTensor;
%}

%template( FieldField_fvPatchField_symmTensor ) Foam::FieldField< Foam::fvPatchField, Foam::symmTensor >;


//---------------------------------------------------------------------------
%extend Foam::FieldField< Foam::fvPatchField, Foam::symmTensor >
{
    int __len__()
    {
        return self->size();
    }
    
    symmTensorField& __getitem__( const Foam::label theIndex )
    {
            return self->operator[]( theIndex );
    }

}


//---------------------------------------------------------------------------
#endif
    