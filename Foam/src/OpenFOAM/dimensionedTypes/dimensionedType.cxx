//  VulaSHAKA (Simultaneous Neutronic, Fuel Performance, Heat And Kinetics Analysis)
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
//  See https://vulashaka.svn.sourceforge.net/svnroot/vulashaka
//
//  Author : Alexey PETROV


//---------------------------------------------------------------------------
#ifndef dimensionedType_cxx
#define dimensionedType_cxx


//---------------------------------------------------------------------------
%module "Foam.src.OpenFOAM.dimensionedTypes.dimensionedType";
%{
  #include "src/OpenFOAM/dimensionedTypes/dimensionedType.hh"
%}


//---------------------------------------------------------------------------
%import "src/OpenFOAM/dimensionSet.cxx"

%import "src/OpenFOAM/primitives/direction.cxx"

%import "src/OpenFOAM/primitives/strings/word.cxx"

%import "src/OpenFOAM/db/IOstreams/ITstream.cxx"

%include <dimensionedType.H>


//---------------------------------------------------------------------------
%define DIMENSIONEDTYPE_ADDONS( Type )

%extend Foam::dimensioned< Type > COMMON_EXTENDS;

%extend Foam::dimensioned< Type >
{
  void setValue( const Type& theValue )
  {
    self->value() = theValue;
  }
  
  Type ext_value()
  {
    return self->value();
  }
  
  void setDimensions( const Foam::dimensionSet& theValue )
  {
    self->dimensions() = theValue;
  }
  
  
  Foam::dimensioned< Type > __neg__()
  {
    return -*self;
  }
  
  Foam::dimensioned< Type > __div__( const Foam::dimensioned< Foam::scalar >& ds )
  {
    return *self / ds;
  }
  
  Foam::dimensioned< Type > __add__( const Foam::dimensioned< Type >& ds )
  {
    return *self + ds;
  }
  
  Foam::dimensioned< Type > __rmul__( const Foam::dimensioned< Foam::scalar >& ds )
  {
    return ds * *self;
  }
  
  Foam::dimensioned< Type > __mul__( const Foam::dimensioned< Foam::scalar >& ds )
  {
    return *self * ds;
  }
  
  Foam::dimensioned< Type > __rmul__( const Foam::scalar& ds )
  {
    return ds * *self;
  }
  
  Foam::dimensioned< Type > __sub__( const Foam::dimensioned< Type >& ds )
  {
    return *self - ds;
  }
  Foam::dimensioned< Foam::scalar > mag()
  {
    return Foam::mag( *self );
  }
}

%import "src/OpenFOAM/db/IOstreams/IOstreams/Ostream.cxx"

%extend Foam::dimensioned< Type > OSTREAM_EXTENDS;

%enddef


//---------------------------------------------------------------------------
#endif
