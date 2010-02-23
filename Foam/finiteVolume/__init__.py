## Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
## 
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
## 
## See https://csrcs.pbmr.co.za/svn/nea/prototypes/reaktor/pyfoam
##
## Author : Alexey PETROV
##


#---------------------------------------------------------------------------
from Foam import get_module_initializtion_command
exec get_module_initializtion_command( "finiteVolume_" ) 


#---------------------------------------------------------------------------
volScalarField = GeometricField_scalar_fvPatchField_volMesh

volVectorField = GeometricField_vector_fvPatchField_volMesh

volTensorField = GeometricField_tensor_fvPatchField_volMesh

volSymmTensorField = GeometricField_symmTensor_fvPatchField_volMesh

surfaceScalarField = GeometricField_scalar_fvsPatchField_surfaceMesh

surfaceVectorField = GeometricField_vector_fvsPatchField_surfaceMesh


#---------------------------------------------------------------------------
fvPatchScalarField = fvPatchField_scalar

fvPatchVectorField = fvPatchField_vector

fvPatchTensorField = fvPatchField_tensor


#---------------------------------------------------------------------------
zeroGradientFvPatchScalarField = zeroGradientFvPatchField_scalar


#----------------------------------------------------------------------------
def continuityErrs( mesh, phi, runTime, cumulativeContErr ):
    from Foam import fvm, fvc

    tmp_contErr = fvc.div( phi )
    contErr = tmp_contErr()
    
    sumLocalContErr = runTime.deltaT().value() * contErr.mag().weightedAverage( mesh.V() ).value()

    globalContErr = runTime.deltaT().value() * contErr.weightedAverage( mesh.V() ).value()

    cumulativeContErr += globalContErr
    
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info << "time step continuity errors : sum local =" << sumLocalContErr \
             << ", global =" << globalContErr \
             << ", cumulative =" << cumulativeContErr
    
    return cumulativeContErr


#---------------------------------------------------------------------------