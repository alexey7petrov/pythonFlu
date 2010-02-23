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
#ifndef no_tmp_typemap_GeometricFields_cxx
#define no_tmp_typemap_GeometricFields_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/GeometricFields/GeometricField.cxx"

%include "src/OpenFOAM/fields/tmp/tmp.cxx"

%include "src/OpenFOAM/primitives/scalar.cxx"
%include "src/OpenFOAM/primitives/vector.cxx"
%include "src/OpenFOAM/primitives/Lists/sphericalTensorList.cxx"
%include "src/OpenFOAM/primitives/s_ymmTensor.cxx"
%include "src/OpenFOAM/primitives/tensor.cxx"


//----------------------------------------------------------------------------
%include "src/finiteVolume/surfaceMesh.hxx"

%include "src/finiteVolume/volMesh.hxx"


//----------------------------------------------------------------------------
%include "src/finiteVolume/fields/fvPatchFields/fvPatchField.cxx"

%include "src/finiteVolume/fields/fvsPatchFields/fvsPatchField.cxx"

//---------------------------------------------------------------------------
%define NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Type, TPatchField, TMesh )

%typecheck( SWIG_TYPECHECK_POINTER ) Foam::GeometricField< Type, TPatchField, TMesh >& 
{
    void *ptr;
    int res = SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Foam::GeometricField< Type, TPatchField, TMesh > * ), 0 );
    int res1 = SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > * ), 0 );
    $1 = SWIG_CheckState( res ) || SWIG_CheckState( res1 );
}

%typemap( in ) Foam::GeometricField< Type, TPatchField, TMesh >& 
{
  void  *argp = 0;
  int res = 0;
  
  res = SWIG_ConvertPtr( $input, &argp, $descriptor(  Foam::GeometricField< Type, TPatchField, TMesh > * ), %convertptr_flags );
  if ( SWIG_IsOK( res )&& argp  ){
    Foam::GeometricField< Type, TPatchField, TMesh > * res =  %reinterpret_cast( argp, Foam::GeometricField< Type, TPatchField, TMesh >* );
    $1 = res;
  } else {
    res = SWIG_ConvertPtr( $input, &argp, $descriptor( Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > >* ), %convertptr_flags );
    if ( SWIG_IsOK( res ) && argp ) {
      Foam::tmp<Foam::GeometricField< Type, TPatchField, TMesh> >* tmp_res =%reinterpret_cast( argp, Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > * );
      $1 = tmp_res->operator->();
      } else {
        %argument_fail( res, "$type", $symname, $argnum );
        }
    }
 
}    
%enddef


//---------------------------------------------------------------------------
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::scalar, Foam::fvPatchField, Foam::volMesh );
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::Vector< Foam::scalar >, Foam::fvPatchField, Foam::volMesh );
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::Tensor< Foam::scalar >, Foam::fvPatchField, Foam::volMesh );
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::SymmTensor< Foam::scalar >, Foam::fvPatchField, Foam::volMesh );
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::SphericalTensor< Foam::scalar >, Foam::fvPatchField, Foam::volMesh );
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::scalar, Foam::fvsPatchField, Foam::surfaceMesh );
NO_TMP_TYPEMAP_GEOMETRIC_FIELD( Foam::Vector< Foam::scalar >, Foam::fvsPatchField, Foam::surfaceMesh );


//-------------------------------------------------------------------------------
#endif