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
#if ( __FOAM_VERSION__ == 010500 )   
%include "src/common.hxx"
#define PtrList_ccompressible_turbulenceModel_cxx
#endif


//---------------------------------------------------------------------------
#ifndef PtrList_ccompressible_turbulenceModel_cxx
#define PtrList_compressible_turbulenceModel_cxx


//---------------------------------------------------------------------------
//It is necessary to include "director's" classes above first's DIRECTOR_INCLUDE
%include "src/finiteVolume/directors.hxx"


//---------------------------------------------------------------------------
%include "src/turbulenceModels/compressible/turbulenceModel.cxx"

%include "src/OpenFOAM/fields/tmp/autoPtr_compressible_turbulenceModel.cxx"

%include "src/OpenFOAM/containers/Lists/PtrList/PtrList.cxx"

%ignore Foam::PtrList< Foam::compressible::turbulenceModel >::PtrList;
%ignore Foam::PtrList< Foam::compressible::turbulenceModel >::begin;
%ignore Foam::PtrList< Foam::compressible::turbulenceModel >::end;
%ignore Foam::PtrList< Foam::compressible::turbulenceModel >::set;

#if ( __FOAM_VERSION__ >= 010600 )
%ignore Foam::PtrList< Foam::compressible::turbulenceModel >::xfer;
#endif

%template( PtrList_compressible_turbulenceModel ) Foam::PtrList< Foam::compressible::turbulenceModel >;


//---------------------------------------------------------------------------
%extend Foam::PtrList< Foam::compressible::turbulenceModel >
{
  Foam::PtrList< Foam::compressible::turbulenceModel >( const Foam::label s )
  {
    return new Foam::PtrList< Foam::compressible::turbulenceModel >( s );
  }
}

%extend Foam::PtrList< Foam::compressible::turbulenceModel > PTRLISTBASED_ADDONS( Foam::compressible::turbulenceModel )


//---------------------------------------------------------------------------
#endif
