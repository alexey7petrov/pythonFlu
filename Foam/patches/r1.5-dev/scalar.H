/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2008 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Typedef
    Foam::scalar

Description
    Single floating point number identical to float or double depending on
    whether SP or DP is defined.

SourceFiles
    scalar.C

\*---------------------------------------------------------------------------*/

#ifndef scalar_H
#define scalar_H

#include "floatScalar.H"
#include "doubleScalar.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#if defined(SP)

// Define scalar as a float

namespace Foam
{
  #ifndef SWIG
    typedef floatScalar scalar;
    static const scalar GREAT = floatScalarGREAT;
    static const scalar VGREAT = floatScalarVGREAT;
    static const scalar ROOTVGREAT = floatScalarROOTVGREAT;
    static const scalar SMALL = floatScalarSMALL;
    static const scalar VSMALL = floatScalarVSMALL;
    static const scalar ROOTVSMALL = floatScalarROOTVSMALL;
  #else
    static const float GREAT = floatScalarGREAT;
    static const float VGREAT = floatScalarVGREAT;
    static const float ROOTVGREAT = floatScalarROOTVGREAT;
    static const float SMALL = floatScalarSMALL;
    static const float VSMALL = floatScalarVSMALL;
    static const float ROOTVSMALL = floatScalarROOTVSMALL;
  #endif
    scalar readScalar(Istream& is);
}

#elif defined(DP)

// Define scalar as a double

namespace Foam
{
  #ifndef SWIG    
    typedef doubleScalar scalar;
    static const scalar GREAT = doubleScalarGREAT;
    static const scalar VGREAT = doubleScalarVGREAT;
    static const scalar ROOTVGREAT = doubleScalarROOTVGREAT;
    static const scalar SMALL = doubleScalarSMALL;
    static const scalar VSMALL = doubleScalarVSMALL;
    static const scalar ROOTVSMALL = doubleScalarROOTVSMALL;
  #else
    static const double GREAT = doubleScalarGREAT;
    static const double VGREAT = doubleScalarVGREAT;
    static const double ROOTVGREAT = doubleScalarROOTVGREAT;
    static const double SMALL = doubleScalarSMALL;
    static const double VSMALL = doubleScalarVSMALL;
    static const double ROOTVSMALL = doubleScalarROOTVSMALL;
  #endif
    scalar readScalar(Istream& is);
}

#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
