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
#ifndef mixedFvPatchField_cxx
#define mixedFvPatchField_cxx


//---------------------------------------------------------------------------
%include "src/finiteVolume/fields/fvPatchFields/fvPatchField.cxx"

%{
    #include "mixedFvPatchField.H"

%}

%feature( "director" ) mixedFvPatchField;

%include "mixedFvPatchField.H"


//--------------------------------------------------------------------------------
%define _MIXEDFVPATCHFIELD_TEMPLATE_OPERATORS( Type )

 Foam::tmp< Foam::Field< Foam::Type > > __sub__( const Foam::Field< Foam::Type >& theArg)
  {
    return *self - theArg;
  }

%enddef

//---------------------------------------------------------------------------
%define MIXEDFVPATCHFIELD_TEMPLATE_Func( Type )

_MIXEDFVPATCHFIELD_TEMPLATE_OPERATORS( Type );

%enddef

#endif