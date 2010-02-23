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
#ifndef tmp_fvPatchField_scalar_cxx
#define tmp_fvPatchField_scalar_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/tmp/tmp.cxx"

%include "src/finiteVolume/fields/fvPatchFields/fvPatchField_scalar.cxx"

TMP_TYPEMAP( Foam::fvPatchField< Foam::scalar > )

%ignore Foam::tmp< Foam::fvPatchField< Foam::scalar > >::tmp;

%template( tmp_fvPatchField_scalar ) Foam::tmp< Foam::fvPatchField< Foam::scalar > >;

%extend Foam::tmp< Foam::fvPatchField< Foam::scalar > >
{
  Foam::tmp< Foam::fvPatchField< Foam::scalar > >( const  Foam::tmp< Foam::fvPatchField< Foam::scalar > >&  theArg ) 
  {
    return new Foam::tmp< Foam::fvPatchField< Foam::scalar > >( theArg );
  }
  
  bool operator==( const Foam::UList< Foam::scalar >& theArg )
  {
    Foam::UList< Foam::scalar >* aSelf = static_cast< Foam::UList< Foam::scalar >* >( self->ptr() );
    return *aSelf == theArg;
  }
}
//---------------------------------------------------------------------------
#endif