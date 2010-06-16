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
#ifndef HashTable_regIOobject_word_string_hash_cxx
#define HashTable_regIOobject_word_string_hash_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/containers/HashTables/HashTable/HashTable.cxx"

%include "src/OpenFOAM/primitives/Lists/wordList.cxx"

%include "src/OpenFOAM/db/regIOobject.cxx"

%ignore Foam::HashTable< Foam::regIOobject*, Foam::word, Foam::string_hash >::HashTable;
%ignore Foam::HashTable< Foam::regIOobject*, Foam::word, Foam::string_hash >::find;
%ignore Foam::HashTable< Foam::regIOobject*, Foam::word, Foam::string_hash >::begin;
%ignore Foam::HashTable< Foam::regIOobject*, Foam::word, Foam::string_hash >::operator();

#if ( __FOAM_VERSION__ >= 010600 )
%ignore Foam::HashTable< Foam::regIOobject*, Foam::word, Foam::string_hash >::cbegin;
#endif

%template( HashTable_regIOobject_word_string_hash ) Foam::HashTable< Foam::regIOobject*, Foam::word, Foam::string_hash >; 

HASHTABLE_ADDONS( Foam::regIOobject*, Foam::word, Foam::string_hash )


//---------------------------------------------------------------------------
#endif
