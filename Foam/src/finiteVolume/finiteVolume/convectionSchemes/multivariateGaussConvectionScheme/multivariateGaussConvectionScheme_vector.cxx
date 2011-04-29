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
#ifndef multivariateGaussConvectionScheme_vector_cxx
#define multivariateGaussConvectionScheme_vector_cxx


//---------------------------------------------------------------------------
%module "Foam.src.finiteVolume.finiteVolume.convectionSchemes.multivariateGaussConvectionScheme.multivariateGaussConvectionScheme_vector";
%{
  #include "src/finiteVolume/finiteVolume/convectionSchemes/multivariateGaussConvectionScheme/multivariateGaussConvectionScheme_vector.hh"
%}


//---------------------------------------------------------------------------
%import "src/finiteVolume/finiteVolume/convectionSchemes/multivariateGaussConvectionScheme/multivariateGaussConvectionScheme.cxx"

%import "src/finiteVolume/finiteVolume/convectionSchemes/convectionScheme/convectionScheme_vector.cxx"

%import "src/OpenFOAM/fields/tmp/tmp_surfaceInterpolationScheme_vector.cxx"


//----------------------------------------------------------------------------
%ignore Foam::fv::multivariateGaussConvectionScheme< Foam::vector >::multivariateGaussConvectionScheme;

%template ( multivariateGaussConvectionScheme_vector ) Foam::fv::multivariateGaussConvectionScheme< Foam::vector >;

%extend Foam::fv::multivariateGaussConvectionScheme< Foam::vector > MULTIVARIATEGAUSSCONVECTIONSCHEME_TEMPLATE_FUNC( vector );


//---------------------------------------------------------------------------
#endif