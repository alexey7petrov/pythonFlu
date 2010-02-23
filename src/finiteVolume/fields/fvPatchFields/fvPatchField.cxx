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
#ifndef fvPatchField_cxx
#define fvPatchField_cxx

//---------------------------------------------------------------------------
%include "src/finiteVolume/fvMesh/fvPatches/fvPatch.cxx"
%include "src/OpenFOAM/fields/DimensionedFields/DimensionedField.cxx"

%include "fvPatchField.H"

%{
    #include "fvPatchField.H"

    #include "volMesh.H"
%}

%feature( "director" ) fvPatchField;


//---------------------------------------------------------------------------
%define FVPATCHFIELD_VIRTUAL_EXTENDS( Type )
{
  void ext_assign( const Foam::fvPatchField< Foam::Type >& theSource )
  {
    *dynamic_cast< Foam::fvPatchField< Foam::Type >* >( self ) = theSource;
  }
}
%enddef


//---------------------------------------------------------------------------
%define FVPATCHFIELD_EXTENDS( Type )

%feature( "director" ) fvPatchField_##Type;

NO_TMP_TYPEMAP_FIELD( fvPatchField< Foam::scalar > );
NO_TMP_TYPEMAP_FIELD( fvPatchField< Foam::vector > );
NO_TMP_TYPEMAP_FIELD( fvPatchField< Foam::tensor > );

%extend Foam::fvPatchField< Foam::Type > FIELD_VIRTUAL_EXTENDS( Type );

%extend Foam::fvPatchField< Foam::Type > FVPATCHFIELD_VIRTUAL_EXTENDS( Type );

%include "src/OpenFOAM/db/IOstreams/IOstreams/Ostream.cxx"

%extend Foam::fvPatchField< Foam::Type > OSTREAM_EXTENDS;

%enddef


//---------------------------------------------------------------------------
%define __FVPATCHFIELD_TEMPLATE_OPERATOR__( Type )
{
  Foam::tmp< Foam::Field< Foam::Type > > __mul__( const Foam::Field< Foam::Type >& theArg)
  {
    return *self * theArg;
  }
}

%enddef


//---------------------------------------------------------------------------
%{
    #include "src/finiteVolume/fields/fvPatchFields/fvPatchField_ConstructorToTable.hxx"
%}

%include "src/finiteVolume/fields/fvPatchFields/fvPatchField_ConstructorToTable.hxx"

%feature("director") fvPatchFieldConstructorToTableBase;


//---------------------------------------------------------------------------
%define __FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC__( Type, counter )
  %feature("director") fvPatchFieldConstructorToTableBase_##Type##_##counter;
  %template( fvPatchFieldConstructorToTableBase_##Type##_##counter ) Foam::fvPatchFieldConstructorToTableBase< Foam::Type, counter >;
%enddef


//---------------------------------------------------------------------------
%define FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC( Type )
  %template( TConstructorToTableCounter_fvPatchField_##Type ) Foam::TConstructorToTableCounter< Foam::fvPatchField< Foam::Type > >;
  __FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC__( Type, 0 );
  __FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC__( Type, 1 );
  __FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC__( Type, 2 );
%enddef


//---------------------------------------------------------------------------
%define FVPATCHFIELD_ADDONS( Type )
  FVPATCHFIELD_EXTENDS( Type )
  FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC( Type )
%enddef


//---------------------------------------------------------------------------
%define FVPATCH_SCALAR_FIELD_ADOONS (Type)
  __FVPATCHFIELD_TEMPLATE_OPERATOR__( Type )
  FVPATCHFIELD_EXTENDS( Type )
  FVPATCHFIELD_CONSTRUCTORTOTABLE_TEMPLATE_FUNC( Type )

%enddef


//---------------------------------------------------------------------------
#endif