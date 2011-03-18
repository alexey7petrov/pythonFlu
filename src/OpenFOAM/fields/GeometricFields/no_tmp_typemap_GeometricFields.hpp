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
#ifndef no_tmp_typemap_GeometricFields_hpp
#define no_tmp_typemap_GeometricFields_hpp


//---------------------------------------------------------------------------
#include "src/OpenFOAM/fields/GeometricFields/GeometricField.hpp"

#include "src/OpenFOAM/fields/tmp/tmp.hpp"

#include "ext/common/ext_tmp.hpp"


//---------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/scalar.hpp"
#include "src/finiteVolume/volMesh.hpp"
#include "src/finiteVolume/fields/fvPatchFields/fvPatchField.hpp"


//----------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/vector.hpp"
#include "src/finiteVolume/volMesh.hpp"
#include "src/finiteVolume/fields/fvPatchFields/fvPatchField.hpp"


//----------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/tensor.hpp"
#include "src/finiteVolume/volMesh.hpp"
#include "src/finiteVolume/fields/fvPatchFields/fvPatchField.hpp"


//-----------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/s_ymmTensor.hpp"
#include "src/finiteVolume/volMesh.hpp"
#include "src/finiteVolume/fields/fvPatchFields/fvPatchField.hpp"


//------------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/s_phericalTensor.hpp"
#include "src/finiteVolume/volMesh.hpp"
#include "src/finiteVolume/fields/fvPatchFields/fvPatchField.hpp"


//------------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/scalar.hpp"
#include "src/finiteVolume/surfaceMesh.hpp"
#include "src/finiteVolume/fields/fvsPatchFields/fvsPatchField.hpp"


//-------------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/vector.hpp"
#include "src/finiteVolume/surfaceMesh.hpp"
#include "src/finiteVolume/fields/fvsPatchFields/fvsPatchField.hpp"


//-------------------------------------------------------------------------------
#include "src/OpenFOAM/primitives/tensor.hpp"
#include "src/finiteVolume/surfaceMesh.hpp"
#include "src/finiteVolume/fields/fvsPatchFields/fvsPatchField.hpp"


//-------------------------------------------------------------------------------
#endif