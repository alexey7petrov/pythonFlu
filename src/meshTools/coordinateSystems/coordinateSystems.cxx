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
#if ( __FOAM_VERSION__ < 010500 )
%include "src/common.hxx"
#define coordinateSystems_cxx
#endif


//---------------------------------------------------------------------------
#ifndef coordinateSystems_cxx
#define coordinateSystems_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/containers/Lists/PtrList/IOPtrList/IOPtrList_coordinateSystem.cxx"

%{
    #include "coordinateSystems.H"
%}

#if ( __FOAM_VERSION__ < 010600 )

%ignore Foam::coordinateSystems::dataType;

%ignore Foam::coordinateSystems::coordinateSystems;

%ignore Foam::coordinateSystems::writeData;

%ignore Foam::coordinateSystems::rewriteDict;

%ignore Foam::coordinateSystems::toc;

%ignore Foam::coordinateSystems::found;

%ignore Foam::coordinateSystems::find;

#endif

%include "coordinateSystems.H"


//---------------------------------------------------------------------------
#endif