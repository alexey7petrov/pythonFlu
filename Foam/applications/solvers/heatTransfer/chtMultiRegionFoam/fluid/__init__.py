#!/usr/bin/env python

#--------------------------------------------------------------------------------------
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


#-----------------------------------------------------------------
def createFluidMeshes( rp, runTime ) :
    
    from Foam.finiteVolume import fvMesh, PtrList_fvMesh
    fluidRegions = PtrList_fvMesh( rp.fluidRegionNames.size() )
    
    from Foam.OpenFOAM import word, fileName, IOobject
    for index in range( rp.fluidRegionNames.size() ) :
        from Foam.OpenFOAM import ext_Info, nl
        ext_Info()<< "Create fluid mesh for region " << rp.fluidRegionNames[ index ] \
                  << " for time = " << runTime.timeName() << nl << nl
        mesh = fvMesh( IOobject( rp.fluidRegionNames[ index ],
                                 fileName( runTime.timeName() ),
                                 runTime,
                                 IOobject.MUST_READ ) )
        fluidRegions.ext_set( index, mesh )
        pass
    
    return fluidRegions
    
    
#-------------------------------------------------------------------
def createFluidFields( fluidRegions, runTime ) :
    
    # Initialise fluid field pointer lists
    from Foam.finiteVolume import PtrList_volScalarField
    rhoFluid = PtrList_volScalarField( fluidRegions.size() )
    KFluid =  PtrList_volScalarField( fluidRegions.size() )

    from Foam.finiteVolume import PtrList_volVectorField
    UFluid = PtrList_volVectorField( fluidRegions.size() )

    from Foam.finiteVolume import PtrList_surfaceScalarField
    phiFluid = PtrList_surfaceScalarField( fluidRegions.size() )    

    DpDtFluid = PtrList_volScalarField( fluidRegions.size() )
     
    from Foam.OpenFOAM import PtrList_UniformDimensionedVectorField
    gFluid = PtrList_UniformDimensionedVectorField( fluidRegions.size() )
 
    from Foam.compressible import PtrList_compressible_turbulenceModel
    turbulence = PtrList_compressible_turbulenceModel( fluidRegions.size() ) 
    
    from Foam.thermophysicalModels import PtrList_basicPsiThermo
    thermoFluid = PtrList_basicPsiThermo( fluidRegions.size() ) 
    
    from Foam.OpenFOAM import List_scalar
    initialMassFluid = List_scalar( fluidRegions.size() )
    
    #Populate fluid field pointer lists

    for index in range( fluidRegions.size() ) :
        from Foam.OpenFOAM import ext_Info, nl
        ext_Info() << "*** Reading fluid mesh thermophysical properties for region " \
            << fluidRegions[ index ].name() << nl << nl

        ext_Info()<< "    Adding to thermoFluid\n" << nl
        
        from Foam.thermophysicalModels import autoPtr_basicPsiThermo, basicPsiThermo
 
        pthermo= basicPsiThermo.New( fluidRegions[ index ] )
        thermoFluid.ext_set( index, pthermo )
        
        ext_Info()<< "    Adding to rhoFluid\n" << nl
        from Foam.OpenFOAM import word, fileName, IOobject
        from Foam.finiteVolume import volScalarField
        tmp =  thermoFluid[ index ].rho()
        tmp = volScalarField( IOobject( word( "rho" ), 
                                        fileName( runTime.timeName() ), 
                                        fluidRegions[ index ], 
                                        IOobject.NO_READ, 
                                        IOobject.AUTO_WRITE ),
                              tmp() )
        rhoFluid.ext_set( index, tmp )
        
        ext_Info()<< "    Adding to KFluid\n" << nl
        tmp=thermoFluid[ index ].Cp().ptr() * thermoFluid[ index ].alpha()
        tmp = volScalarField( IOobject( word( "K" ),
                                        fileName( runTime.timeName() ),
                                        fluidRegions[ index ],
                                        IOobject.NO_READ,
                                        IOobject.NO_WRITE ),
                              tmp() )
        KFluid.ext_set( index, tmp )
        
        ext_Info()<< "    Adding to UFluid\n" << nl
        from Foam.finiteVolume import volVectorField
        tmp=volVectorField( IOobject( word( "U" ),
                                      fileName( runTime.timeName() ),
                                      fluidRegions[ index ],
                                      IOobject.MUST_READ,
                                      IOobject.AUTO_WRITE ),
                            fluidRegions[ index ] )
        UFluid.ext_set( index, tmp )
        
        ext_Info()<< "    Adding to phiFluid\n" << nl
        from Foam.finiteVolume import surfaceScalarField
        from Foam.finiteVolume import linearInterpolate
                
        tmp = rhoFluid[ index ] * UFluid[ index ]
        tmp = linearInterpolate( tmp )
        tmp = tmp() & fluidRegions[ index ].Sf()
        tmp = surfaceScalarField( IOobject( word( "phi" ),
                                            fileName( runTime.timeName() ),
                                            fluidRegions[ index ],
                                            IOobject.READ_IF_PRESENT,
                                            IOobject.AUTO_WRITE),
                                  tmp() )
 
        phiFluid.ext_set( index, tmp )
        
        ext_Info()<< "    Adding to gFluid\n" << nl
        from Foam.OpenFOAM import UniformDimensionedVectorField
        tmp = UniformDimensionedVectorField( IOobject( word( "g" ),
                                                       fileName( runTime.constant() ),
                                                       fluidRegions[ index ],
                                                       IOobject.MUST_READ,
                                                       IOobject.NO_WRITE ) )
        gFluid.ext_set( index, tmp )        
        
        ext_Info()<< "    Adding to turbulence\n" << nl
        from Foam import compressible
        tmp = compressible.turbulenceModel.New( rhoFluid[ index ],
                                                UFluid[ index ],
                                                phiFluid[ index ],
                                                thermoFluid[ index ] )
        turbulence.ext_set( index, tmp )
        
        ext_Info()<< "    Adding to DpDtFluid\n" << nl
        from Foam import fvc
        tmp = phiFluid[ index ] / fvc.interpolate( rhoFluid[ index ] )
        tmp = surfaceScalarField( word( "phiU" ), tmp() )
        tmp = fvc.DDt( tmp, thermoFluid[ index ].p() )
        tmp = volScalarField( word( "DpDt" ), tmp() )           
        DpDtFluid.ext_set( index, tmp )

        initialMassFluid[ index ] = fvc.domainIntegrate( rhoFluid[ index ] ).value()              
        pass
    
    return thermoFluid, rhoFluid, KFluid, UFluid, phiFluid, gFluid, turbulence, DpDtFluid, initialMassFluid
        

#-----------------------------------------------------------------------------------------------------------------------
def compressibleCourantNo( mesh, runTime, rho, phi) :
    
    from Foam.OpenFOAM import Time
    from Foam.finiteVolume import fvMesh
    from Foam.finiteVolume import surfaceScalarField

    CoNum = 0.0;
    meanCoNum = 0.0;

    from Foam import fvc
    tmp_SfUfbyDelta = mesh.deltaCoeffs() * phi.mag() / fvc.interpolate( rho )
    SfUfbyDelta = tmp_SfUfbyDelta()
    CoNum = ( SfUfbyDelta / mesh.magSf() ).ext_max().value() * runTime.deltaT().value()
    meanCoNum = ( SfUfbyDelta.sum() / mesh.magSf().sum() ).value() * runTime.deltaT().value()

    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Region: " << mesh.name() << " Courant Number mean: " << meanCoNum \
        << " max: " << CoNum << nl
    
    return  CoNum   
            

#-------------------------------------------------------------------------------------------------------------------------
def compressubibleMultiRegionCourantNo(fluidRegions, runTime, rhoFluid, phiFluid ) :
    
    from Foam.OpenFOAM import GREAT
    CoNum = -GREAT
    for index in range( fluidRegions.size() ):
        CoNum = max( CoNum, compressibleCourantNo( fluidRegions[ index ], runTime, rhoFluid[ index ], phiFluid[ index ] ) )
        pass
    
    return CoNum
    
    
#-------------------------------------------------------------------------------------------------------------------------
def readFluidMultiRegionPIMPLEControls( mesh ) :
    
    from Foam.OpenFOAM import word, readInt, Switch
    pimple = mesh.solutionDict().subDict( word( "PIMPLE" ) )
    nCorr = readInt( pimple.lookup( word( "nCorrectors" ) ) )
    nNonOrthCorr = pimple.lookupOrDefault( word( "nNonOrthogonalCorrectors" ), 0 )
    momentumPredictor =pimple.lookupOrDefault( word( "momentumPredictor" ), Switch( True ) )
    
    return pimple, nCorr, nNonOrthCorr, momentumPredictor


#--------------------------------------------------------------------------------------------------------------------------
def setRegionFluidFields( i, fluidRegions, thermoFluid, rhoFluid, KFluid, UFluid, \
                          phiFluid, gFluid, turbulence, DpDtFluid, initialMassFluid ):
    mesh = fluidRegions[ i ]

    thermo = thermoFluid[ i ]
    rho = rhoFluid[ i ]
    K = KFluid[ i ]
    U = UFluid[ i ]
    phi = phiFluid[ i ]
    g = gFluid[ i ]

    turb = turbulence[ i ]
    DpDt = DpDtFluid[ i ]

    p = thermo.p()
    psi = thermo.psi()
    h = thermo.h()

    from Foam.OpenFOAM import dimensionedScalar, word, dimMass
    massIni = dimensionedScalar( word( "massIni" ), dimMass, initialMassFluid[ i ] )

    return mesh, thermo, rho, K, U, phi, g, turb, DpDt, p, psi, h, massIni


#--------------------------------------------------------------------------------------------------------------------------
def storeOldFluidFields( p, rho ):
    p.storePrevIter()
    rho.storePrevIter()
    pass


#--------------------------------------------------------------------------------------------------------------------------
def initContinuityErrs( size ):
    from Foam.finiteVolume import List_scalar
    cumulativeContErr = List_scalar( size, 0.0 )
    
    return cumulativeContErr


#--------------------------------------------------------------------------------------------------------------------------
def compressibleContinuityErrors( i, mesh, rho, thermo, cumulativeContErr ) :
    from Foam import fvc
    totalMass = fvc.domainIntegrate(rho)
       
    sumLocalContErr =  (fvc.domainIntegrate( ( rho - thermo.rho()  ).mag() )  / totalMass ).value()
    
    globalContErr =  ( fvc.domainIntegrate( rho - thermo.rho() ) / totalMass ).value()

    cumulativeContErr[i] = cumulativeContErr[i] + globalContErr
    
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info()<< "time step continuity errors (" << mesh.name() << ")" \
        << ": sum local = " << sumLocalContErr \
        << ", global = " << globalContErr \
        << ", cumulative = " << cumulativeContErr[i] \
        << nl
        
    return cumulativeContErr


#--------------------------------------------------------------------------------------------------------------------------
def fun_UEqn( rho, U, phi, g, p, turb, mesh, momentumPredictor ) :
    # Solve the Momentum equation
    from Foam import fvm
    UEqn = fvm.ddt( rho, U ) + fvm.div( phi, U ) + turb.divDevRhoReff( U )

    UEqn.relax()
    
    if momentumPredictor :
        from Foam import fvc
        from Foam.finiteVolume import solve
        tmp = fvc.reconstruct( fvc.interpolate( rho ) * ( g & mesh.Sf() )  - fvc.snGrad( p ) * mesh.magSf() )
        solve( UEqn() == tmp )
        pass
    
    return UEqn


#--------------------------------------------------------------------------------------------------------------------------
def fun_hEqn( rho, h, phi, turb, DpDt, thermo, mesh, oCorr, nOuterCorr ) :
    
    from Foam import fvm
    tmp = fvm.ddt( rho, h ) + fvm.div( phi, h ) - fvm.laplacian( turb.alphaEff(), h )
    
    hEqn = ( tmp() == DpDt )
    
    if oCorr == nOuterCorr - 1 :
       hEqn.relax()
       from Foam.OpenFOAM import word
       hEqn.solve( mesh.solver( word( "hFinal" ) ) )
    else:
       hEqn.relax()
       hEqn.solve()
       pass
   
    thermo.correct()
    
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info()<< "Min/max T:" << thermo.T().ext_min().value() << ' ' \
        << thermo.T().ext_max().value() << nl
        
    return hEqn


#---------------------------------------------------------------------------------------------------------    
def fun_pEqn( i, mesh, p, g, rho, turb, thermo, thermoFluid, K, UEqn_tmp, U, phi, psi, DpDt, massIni, \
              nNonOrthCorr, oCorr, nOuterCorr, corr, nCorr, cumulativeContErr ) :
    
    closedVolume = p.needReference()

    rho.ext_assign( thermo.rho() )
    UEqn = UEqn_tmp()

    rUA_tmp = 1.0 / UEqn.A()
    rUA = rUA_tmp()
    
    from Foam import fvc
    tmp = fvc.interpolate( rho * rUA )

    from Foam.OpenFOAM import word 
    from Foam.finiteVolume import surfaceScalarField
    rhorUAf = surfaceScalarField( word( "(rho*(1|A(U)))" ) , tmp() )

    U.ext_assign( rUA * UEqn.H() ) 
    
    from Foam import fvc
    phiU_tmp = ( fvc.interpolate( rho ) *
                 (  ( fvc.interpolate( U ) & mesh.Sf() ) +
                    fvc.ddtPhiCorr( rUA, rho, U, phi ) ) )
    phiU = phiU_tmp()
    phi.ext_assign( phiU + fvc.interpolate( rho ) * ( g & mesh.Sf() ) * rhorUAf )
    
    from Foam import fvm
    for nonOrth in range ( nNonOrthCorr + 1 ):
        pEqn_tmp = ( fvm.ddt( psi, p) + fvc.div( phi ) - fvm.laplacian( rhorUAf, p ) )
        pEqn = pEqn_tmp()
        if oCorr == ( nOuterCorr - 1 ) and corr == ( nCorr - 1 ) and nonOrth == nNonOrthCorr :
            pEqn.solve( mesh.solver( word( str( p.name() ) +  "Final" ) ) )
        else:
            pEqn.solve( mesh.solver( p.name() ) )
            pass
        
        if nonOrth == nNonOrthCorr :
            phi.ext_assign( phi + pEqn.flux() )
            pass
        pass
    
    # Correct velocity field
    U.ext_assign( U + rUA * fvc.reconstruct( ( phi - phiU ) / rhorUAf ) )
    U.correctBoundaryConditions()

    #Update pressure substantive derivative
    tmp =  phi / fvc.interpolate( rho )
    DpDt.ext_assign( fvc.DDt( surfaceScalarField( word( "phiU" ), tmp() ), p ) )
    
    # Solve continuity
    from Foam.finiteVolume.cfdTools.compressible import rhoEqn
    rhoEqn( rho, phi )   
    
    # Update continuity errors
    cumulativeContErr = compressibleContinuityErrors( i, mesh, rho, thermo, cumulativeContErr )
    
    # For closed-volume cases adjust the pressure and density levels
    # to obey overall mass continuity
    if closedVolume :
       p.ext_assign( p + ( massIni - fvc.domainIntegrate( psi * p ) ) / fvc.domainIntegrate( psi ) )
       rho.ext_assign( thermo.rho() )
       pass
    #Update thermal conductivity
    K.ext_assign( thermoFluid[ i ].Cp() * turb.alphaEff() )
        
    return cumulativeContErr


#--------------------------------------------------------------------------------------------------------------------------
def solveFluid( i, mesh, thermo, thermoFluid, rho, K, U, phi, g, h, turb, DpDt, p, psi, massIni,\
                oCorr, nCorr, nOuterCorr, nNonOrthCorr, momentumPredictor,cumulativeContErr ) :
    
    if oCorr == 0 :
        from Foam.finiteVolume.cfdTools.compressible import rhoEqn
        rhoEqn( rho, phi )
        pass
    
    UEqn_tmp = fun_UEqn( rho, U, phi, g, p, turb, mesh, momentumPredictor )
    hEqn_tmp = fun_hEqn( rho, h, phi, turb, DpDt, thermo, mesh, oCorr, nOuterCorr )
    
    # --- PISO loop
    for corr in range( nCorr ):
        cumulativeContErr =  fun_pEqn( i, mesh, p, g, rho, turb, thermo, thermoFluid, K, UEqn_tmp, U, phi, psi, DpDt, massIni,
                                       nNonOrthCorr, oCorr, nOuterCorr, corr, nCorr, cumulativeContErr )
        pass
    
    turb.correct()
    rho = thermo.rho()
    
    return cumulativeContErr


#-----------------------------------------------------------------------------------------------------------------