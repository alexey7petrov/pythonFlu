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

Class
    Foam::polyPatch

Description
    A patch is a list of labels, which address the faces in the global face
    list. Based on the global faces, the patch can calculate its own edge.
    Patch also contains all addressing between the faces.

SourceFiles
    polyPatch.C
    calcPolyPatchAddressing.C
    calcPolyPatchFaceCells.C
    calcPolyPatchIntBdryEdges.C
    calcPolyPatchMeshEdges.C
    calcPolyPatchMeshData.C
    calcPolyPatchPointAddressing.C
    clearPolyPatch.C
    newPolyPatch.C
    polyPatchTools.C

\*---------------------------------------------------------------------------*/

#ifndef polyPatch_H
#define polyPatch_H

#include "patchIdentifier.H"
#include "primitivePatch.H"
#include "typeInfo.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

class polyBoundaryMesh;

// Forward declaration of friend functions and operators

class polyPatch;

Ostream& operator<<(Ostream&, const polyPatch&);


/*---------------------------------------------------------------------------*\
                           Class polyPatch Declaration
\*---------------------------------------------------------------------------*/

class polyPatch
:
    public patchIdentifier,
#ifndef SWIG
    public primitivePatch
#else
    public PrimitivePatch< face, SubList, const pointField& >
#endif
{
    // Private data

        //- Start label of this patch in the polyMesh face list
        label start_;

        //- Reference to boundary mesh
        const polyBoundaryMesh& boundaryMesh_;


        // Demand-driven private data

            //- face-cell addressing
            mutable labelList::subList* faceCellsPtr_;

            //- Global edge addressing
            mutable labelList* mePtr_;


    // Private Member Functions

        //- Calculate labels of mesh edges
        void calcMeshEdges() const;


protected:

    // Protected Member Functions

        // The polyPatch geometry initialisation is called by polyBoundaryMesh
        friend class polyBoundaryMesh;

        //- Initialise the calculation of the patch geometry
        virtual void initGeometry()
        {}

        //- Calculate the patch geometry
        virtual void calcGeometry()
        {}

        //- Initialise the patches for moving points
        virtual void initMovePoints(const pointField&)
        {}

        //- Correct patches after moving points
        virtual void movePoints(const pointField& p);

        //- Initialise the update of the patch topology
        virtual void initUpdateMesh()
        {}

        //- Update of the patch topology
        virtual void updateMesh();


public:

    //- Runtime type information
    TypeName("patch");

    //- Debug switch to disallow the use of genericPolyPatch
    static int disallowGenericPolyPatch;


    // Declare run-time constructor selection tables

#ifndef SWIG
        declareRunTimeSelectionTable
        (
            autoPtr,
            polyPatch,
            word,
            (
                const word& name,
                const label size,
                const label start,
                const label index,
                const polyBoundaryMesh& bm
            ),
            (name, size, start, index, bm)
        );

        declareRunTimeSelectionTable
        (
            autoPtr,
            polyPatch,
            dictionary,
            (
                const word& name,
                const dictionary& dict,
                const label index,
                const polyBoundaryMesh& bm
            ),
            (name, dict, index, bm)
        );
#endif


    // Constructors

        //- Construct from components
        polyPatch
        (
            const word& name,
            const label size,
            const label start,
            const label index,
            const polyBoundaryMesh& bm
        );

        //- Construct from dictionary
        polyPatch
        (
            const word& name,
            const dictionary& dict,
            const label index,
            const polyBoundaryMesh& bm
        );

        //- Construct as copy, resetting the boundary mesh
        polyPatch(const polyPatch&, const polyBoundaryMesh&);

        //- Construct given the original patch and resetting the
        //  face list and boundary mesh information
        polyPatch
        (
            const polyPatch& pp,
            const polyBoundaryMesh& bm,
            const label index,
            const label newSize,
            const label newStart
        );

        //- Construct as copy
        polyPatch(const polyPatch&);

        //- Construct and return a clone, resetting the boundary mesh
        virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
        {
            return autoPtr<polyPatch>(new polyPatch(*this, bm));
        }

        //- Construct and return a clone, resetting the face list
        //  and boundary mesh
        virtual autoPtr<polyPatch> clone
        (
            const polyBoundaryMesh& bm,
            const label index,
            const label newSize,
            const label newStart
        ) const
        {
            return autoPtr<polyPatch>
            (
                new polyPatch(*this, bm, index, newSize, newStart)
            );
        }


    // Selectors

        //- Return a pointer to a new patch created on freestore from
        //  components
        static autoPtr<polyPatch> New
        (
            const word& patchType,
            const word& name,
            const label size,
            const label start,
            const label index,
            const polyBoundaryMesh& bm
        );

        //- Return a pointer to a new patch created on freestore from
        //  dictionary
        static autoPtr<polyPatch> New
        (
            const word& name,
            const dictionary& dict,
            const label index,
            const polyBoundaryMesh& bm
        );


    // Destructor

        virtual ~polyPatch();


    // Member Functions

        //- Return start label of this patch in the polyMesh face list
        label start() const
        {
            return start_;
        }

        //- Return boundaryMesh reference
        const polyBoundaryMesh& boundaryMesh() const;

        //- Return true if this patch field is coupled
        virtual bool coupled() const
        {
            return false;
        }

        //- Return true if the given type is a constraint type
        static bool constraintType(const word& pt);

        //- Return a list of all the constraint patch types
        static wordList constraintTypes();

        //- Slice list to patch
        template<class T>
        const typename List<T>::subList patchSlice(const List<T>& l) const
        {
            return typename List<T>::subList(l, this->size(), start_);
        }

        //- Slice Field to patch
        template<class T>
        const typename Field<T>::subField patchSlice(const Field<T>& l) const
        {
            return typename Field<T>::subField(l, this->size(), start_);
        }


        //- Write the polyPatch data as a dictionary
        virtual void write(Ostream&) const;


        // Geometric data; point list required

            //- Return face centres
            const vectorField::subField faceCentres() const;

            //- Return face normals
            const vectorField::subField faceAreas() const;

            //- Return face neighbour cell centres
            tmp<vectorField> faceCellCentres() const;


        // Addressing into mesh

            //- Return face-cell addressing
            const unallocLabelList& faceCells() const;

            //- Return global edge index for local edges
            const labelList& meshEdges() const;

            //- Clear addressing
            void clearAddressing();


        // Other patch operations

            //- Return label of face in patch from global face label
            inline label whichFace(const label l) const
            {
                return l - start_;
            }


        //- Initialize ordering for primitivePatch. Does not
        //  refer to *this (except for name() and type() etc.)
        virtual void initOrder(const primitivePatch&) const;

        //- Return new ordering for primitivePatch.
        //  Ordering is -faceMap: for every face
        //  index of the new face -rotation:for every new face the clockwise
        //  shift of the original face. Return false if nothing changes
        //  (faceMap is identity, rotation is 0), true otherwise.
        virtual bool order
        (
            const primitivePatch&,
            labelList& faceMap,
            labelList& rotation
        ) const;


    // Member operators

        //- Assignment
        void operator=(const polyPatch&);


    // Ostream Operator

        friend Ostream& operator<<(Ostream&, const polyPatch&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
