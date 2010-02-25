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
#ifndef GeometricField_cxx
#define GeometricField_cxx


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/DimensionedFields/DimensionedField.cxx"

%include "GeometricField.H"

%{
    #include "GeometricField.H"
%}


//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/GeometricFields/TGeometricBoundaryField.hxx"



%include "src/OpenFOAM/fields/GeometricFields/no_tmp_typemap_GeometricFields.hxx"

//---------------------------------------------------------------------------
%include "src/OpenFOAM/fields/tmp/tmp.cxx"

%include "src/OpenFOAM/db/objectRegistry.cxx"
%include "src/OpenFOAM/primitives/label.cxx"

%define __COMMON_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )
{
    static const Foam::GeometricField< Type, TPatchField, TMesh >&
    ext_lookupObject( const Foam::objectRegistry& theRegistry, const Foam::word& theName )
    {
        return theRegistry.lookupObject< Foam::GeometricField< Type, TPatchField, TMesh > >( theName );
    }
    
    static const TPatchField< Type >&
    ext_lookupPatchField(const Foam::fvPatch& thePatch, const word& theName )
    {
        return thePatch.lookupPatchField< Foam::GeometricField< Type, TPatchField, TMesh >, Type >( theName );
    }

    static bool ext_foundObject( const Foam::objectRegistry& theRegistry, const Foam::word& theName )
    {
        return theRegistry.foundObject< Foam::GeometricField< Type, TPatchField, TMesh > >( theName );
    }

    void ext_assign( const Foam::GeometricField< Type, TPatchField, TMesh >& theArg )
    {
        get_ref( self ) = theArg;
    }

    Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > __neg__()
    {
        return -get_ref( self );
    }


    Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > __sub__( const Foam::GeometricField< Type, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) - theArg;
    }

    Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > __add__( const Foam::GeometricField< Type, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) + theArg;
    }

    Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > __add__( const Foam::dimensioned< Type >& theArg )
    {
        return get_ref( self ) + theArg;
    }
    
    Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > __rmul__( const Foam::label& theArg )
    {
        return theArg * get_ref( self );
    }

    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > mag()
    {
        return Foam::mag( get_ref( self ) );
    }

    Foam::dimensioned< Type > ext_max() const
    {
        return Foam::max( get_ref( self ) );
    }
    
    Foam::dimensioned< Type > ext_min() const
    {
        return Foam::min( get_ref( self ) );
    }
    

    Foam::dimensioned< Type > sum() const
    {
        return Foam::sum( get_ref( self ) );
    }
    
    Foam::TGeometricBoundaryField< Type, TPatchField, TMesh > ext_boundaryField()
    {
        return Foam::TGeometricBoundaryField< Type, TPatchField, TMesh >( get_ref( self ).boundaryField() );
    }    
}
%enddef


//---------------------------------------------------------------------------
%define GEOMETRIC_FIELD_TEMPLATE_FUNC( Type, TPatchField, TMesh )

%extend Foam::GeometricField< Type, TPatchField, TMesh > COMMON_EXTENDS;

%include "src/OpenFOAM/primitives/scalar.cxx"

%extend Foam::GeometricField< Type, TPatchField, TMesh > COMMON_EXTENDS;

%extend Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > COMMON_EXTENDS;

%include "src/OpenFOAM/db/IOstreams/IOstreams/Ostream.cxx"

%extend Foam::GeometricField< Type, TPatchField, TMesh > OSTREAM_EXTENDS;

%extend Foam::GeometricField< Type, TPatchField, TMesh > __COMMON_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%extend Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > __COMMON_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%enddef


//---------------------------------------------------------------------------
%include "src/OpenFOAM/primitives/tensor.cxx"
%include "src/OpenFOAM/primitives/s_phericalTensor.cxx"

%define __SCALAR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )
{
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > sqrt()
    {
        return Foam::sqrt( get_ref( self ) );
    }
    
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __div__( const Foam::GeometricField< Foam::scalar, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) / theArg;
    }

    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __rdiv__( const Foam::scalar& theArg )
    {
        return theArg / get_ref( self );
    }

    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __rmul__( const Foam::scalar& theArg )
    {
        return theArg * get_ref( self );
    }
    
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __rmul__( const Foam::dimensioned< Foam::scalar >& theArg )
    {
        return theArg * get_ref( self ) ;
    }
    
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __mul__( const Foam::dimensioned< Foam::scalar >& theArg )
    {
        return get_ref( self ) * theArg ;
    }
    
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __radd__( const Foam::scalar& theArg )
    {
        return  theArg + get_ref( self );
    }
    
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __rsub__( const Foam::scalar& theArg )
    {
        return  theArg - get_ref( self );
    }
    
    Foam::tmp< Foam::GeometricField< Foam::tensor, TPatchField, TMesh > > __rmul__( const Foam::tensor& theArg )
    {
        return  theArg * get_ref( self );
    }
    
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __mul__( const Foam::GeometricField< Foam::scalar, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) * theArg;
    }

    Foam::tmp< Foam::GeometricField< Foam::vector, TPatchField, TMesh > > __mul__( const Foam::GeometricField< Foam::vector, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) * theArg;
    }

    Foam::tmp< Foam::GeometricField< Foam::vector, TPatchField, TMesh > > __rmul__( const Foam::GeometricField< Foam::vector, TPatchField, TMesh >& theArg )
    {
        return theArg * get_ref( self );
    }

    Foam::tmp< Foam::GeometricField< Foam::tensor, TPatchField, TMesh > > __mul__( const Foam::GeometricField< Foam::tensor, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) * theArg;
    }
    
    Foam::tmp< Foam::GeometricField< Foam::sphericalTensor, TPatchField, TMesh > > __rmul__( const Foam::sphericalTensor& theArg )
    {
        return theArg * get_ref( self );
    }
    
    Foam::tmp< Foam::GeometricField< Foam::sphericalTensor, TPatchField, TMesh > > __mul__( const Foam::GeometricField< Foam::sphericalTensor, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) * theArg;
    }

    Foam::tmp< Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh > > __mul__( const Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) * theArg;
    }
    
}
%enddef


//---------------------------------------------------------------------------
%define SCALAR_GEOMETRIC_FIELD_TEMPLATE_FUNC( TPatchField, TMesh )

GEOMETRIC_FIELD_TEMPLATE_FUNC( Foam::scalar, TPatchField, TMesh )

%extend Foam::GeometricField< Foam::scalar, TPatchField, TMesh > __SCALAR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%extend Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __SCALAR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%enddef


//---------------------------------------------------------------------------
%include "src/OpenFOAM/dimensionedTypes/dimensionedVector.cxx"
%define __VECTOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )
{
    Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > __and__( const Foam::GeometricField< Foam::vector, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) & theArg;
    }
    Foam::tmp< Foam::GeometricField< Foam::vector, TPatchField, TMesh > > __div__( const Foam::GeometricField< Foam::scalar, TPatchField, TMesh >& theArg )
    {
        return get_ref( self ) / theArg;
    }
    Foam::tmp< Foam::GeometricField< Foam::vector, TPatchField, TMesh > >  __rxor__( const Foam::dimensioned< Foam::vector >& theArg )
    {
        return theArg ^ get_ref( self );
    }

    Foam::tmp<Foam::GeometricField<Foam::scalar, TPatchField, TMesh > > __rand__( const Foam::dimensioned< Foam::vector >& theArg )
    {
        return theArg & get_ref( self );
    }
   
}
%enddef


//---------------------------------------------------------------------------
%define VECTOR_GEOMETRIC_FIELD_TEMPLATE_FUNC( TPatchField, TMesh )

GEOMETRIC_FIELD_TEMPLATE_FUNC( Foam::vector, TPatchField, TMesh )

%extend Foam::GeometricField< Foam::vector, TPatchField, TMesh > __VECTOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%extend Foam::tmp< Foam::GeometricField< Foam::vector, TPatchField, TMesh > > __VECTOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%enddef


//---------------------------------------------------------------------------
%define __TENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )
{
  Foam::tmp< Foam::GeometricField< Foam::tensor, TPatchField, TMesh > > inv()
  {
    return Foam::inv( get_ref( self ) );
  }
  
  Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > tr()
  {
    return Foam::tr( get_ref( self ) );
  }
  
  Foam::tmp< Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh > > symm()
  {
    return Foam::symm( get_ref( self ) );
  }
  
  Foam::GeometricField< Foam::vector, TPatchField, TMesh > __and__( const Foam::tmp<GeometricField< Foam::vector, TPatchField, TMesh > >& theArg )
  {
    return  get_ref( self ) & theArg;
  }
  Foam::tmp< Foam::GeometricField< Foam::tensor, TPatchField, TMesh > > __add__( const Foam::GeometricField< Foam::sphericalTensor, TPatchField, TMesh >& theArg )
  {
    return  get_ref( self ) + theArg;
  }
}
%enddef


//---------------------------------------------------------------------------
%define TENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC( TPatchField, TMesh )

GEOMETRIC_FIELD_TEMPLATE_FUNC( Foam::tensor, TPatchField, TMesh )

%extend Foam::GeometricField< Foam::tensor, TPatchField, TMesh > __TENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%extend Foam::tmp< Foam::GeometricField< Foam::tensor, TPatchField, TMesh > > __TENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%enddef


//---------------------------------------------------------------------------
%define __SYMMTENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )
{
  Foam::tmp< Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh > > dev()
  {
    return Foam::dev( get_ref( self ) );
  }
  Foam::tmp< Foam::GeometricField< Foam::scalar, TPatchField, TMesh > > magSqr()
  {
    return Foam::magSqr( get_ref( self )  );
  }
  Foam::tmp< Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh > > __add__( const Foam::GeometricField< Foam::sphericalTensor, TPatchField, TMesh >& theArg )
  {
    return  get_ref( self ) + theArg;
  }
}
%enddef


//---------------------------------------------------------------------------
%define SYMMTENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC( TPatchField, TMesh )

GEOMETRIC_FIELD_TEMPLATE_FUNC( Foam::symmTensor, TPatchField, TMesh )

%extend Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh > __SYMMTENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%extend Foam::tmp< Foam::GeometricField< Foam::symmTensor, TPatchField, TMesh > >__SYMMTENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC__( Type, TPatchField, TMesh )

%enddef


//-----------------------------------------------------------------------------
%define SPHERICALTENSOR_GEOMETRIC_FIELD_TEMPLATE_FUNC( TPatchField, TMesh )

GEOMETRIC_FIELD_TEMPLATE_FUNC( Foam::sphericalTensor, TPatchField, TMesh )

%enddef


//-------------------------------------------------------------------------------
#endif
