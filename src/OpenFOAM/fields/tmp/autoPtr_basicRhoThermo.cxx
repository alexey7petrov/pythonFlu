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
//  See https://vulashaka.svn.sourceforge.net/svnroot/vulashaka/pyfoam
//
//  Author : Alexey PETROV


//---------------------------------------------------------------------------
#if ( __FOAM_VERSION__ < 010600 )
#define autoPtr_basicRhoThermo_cxx
%include "src/common.hxx"
#endif


//---------------------------------------------------------------------------
#ifndef autoPtr_basicRhoThermo_cxx
#define autoPtr_basicRhoThermo_cxx


//---------------------------------------------------------------------------
// Keep on corresponding "director" includes at the top of SWIG defintion file

%include "src/OpenFOAM/directors.hxx"

%include "src/finiteVolume/directors.hxx"


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/tmp/autoPtr.cxx"

%include "src/thermophysicalModels/basic/rhoThermo/basicRhoThermo.cxx"


//---------------------------------------------------------------------------
AUTOPTR_TYPEMAP( Foam::basicRhoThermo )

%ignore Foam::autoPtr< Foam::basicRhoThermo >::operator->;

%template( autoPtr_basicRhoThermo ) Foam::autoPtr< Foam::basicRhoThermo >;

%inline
{
  namespace Foam
  {
    typedef autoPtr< basicRhoThermo > autoPtr_basicRhoThermo;
  }
}


//------------------------------------------------------------------------------
%feature( "pythonappend" ) Foam::autoPtr< Foam::basicRhoThermo >::SMARTPTR_PYAPPEND_GETATTR( autoPtr_basicRhoThermo );

%extend Foam::autoPtr< Foam::basicRhoThermo >
{
  SMARTPTR_EXTEND_ATTR( autoPtr_basicRhoThermo )
}

//---------------------------------------------------------------------------
#endif