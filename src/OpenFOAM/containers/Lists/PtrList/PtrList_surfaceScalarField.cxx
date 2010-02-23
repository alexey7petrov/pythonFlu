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
#ifndef PtrList_surfaceScalarField_cxx
#define PtrList_surfaceScalarField_cxx


//---------------------------------------------------------------------------
%include "src/finiteVolume/fields/surfaceFields/surfaceScalarField.cxx"

%include "src/OpenFOAM/fields/tmp/autoPtr_surfaceScalarField.cxx"

%include "src/OpenFOAM/fields/tmp/tmp_surfaceScalarField.cxx"

%include "src/OpenFOAM/containers/Lists/PtrList/PtrList.cxx"

%ignore Foam::PtrList< Foam::surfaceScalarField >::PtrList;
%ignore Foam::PtrList< Foam::surfaceScalarField >::set;

#if ( __FOAM_VERSION__ >= 010600 )
%ignore Foam::PtrList< Foam::surfaceScalarField >::xfer;
#endif

%template( PtrList_surfaceScalarField ) Foam::PtrList< Foam::surfaceScalarField >;


//---------------------------------------------------------------------------
%extend Foam::PtrList< Foam::surfaceScalarField >
{
  Foam::PtrList< Foam::surfaceScalarField >( const Foam::label s )
  {
    return new Foam::PtrList< Foam::surfaceScalarField >( s );
  }
}

%extend Foam::PtrList< Foam::surfaceScalarField > PTRLISTBASED_ADDONS( Foam::surfaceScalarField )


//---------------------------------------------------------------------------
#endif