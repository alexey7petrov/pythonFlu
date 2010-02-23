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
#if ( __FOAM_VERSION__ < 010600 )
%include "src/common.hxx"
#define Xfer_hxx
#endif


//---------------------------------------------------------------------------
#ifndef Xfer_hxx
#define Xfer_hxx

//---------------------------------------------------------------------------
%include "src/common.hxx"

%{
    #include "Xfer.H"
%}

%include "Xfer.H"


//---------------------------------------------------------------------------
%define XFER_ADDONS( Type )

%typecheck( SWIG_TYPECHECK_POINTER ) const Foam::Xfer< Type > &
{
    void *ptr;
    if ( SWIG_ConvertPtr( $input, (void **) &ptr, $1_descriptor, 0 ) == -1 ) {
        if ( SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Type* ), 0 ) == -1 ) {
            $1 = false;
        } else {
            $1 = true;
        }
    } else {
        $1 = true;
    }
}


%typemap( in ) const Foam::Xfer< Type > &
{
    void *ptr;
    if ( SWIG_ConvertPtr( $input, (void **) &ptr, $1_descriptor, 0 ) == -1 ) {
        SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Type* ), 0 );
        Type* aValue = reinterpret_cast< Type* >( ptr );
        $1 = new Foam::Xfer< Type >( aValue );
    } else {
        $1 = reinterpret_cast< $1_ltype >( ptr );
    }
}

%enddef


//---------------------------------------------------------------------------
#endif