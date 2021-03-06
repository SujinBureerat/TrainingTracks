/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::weaklyCoupled3DofFsi

Group
    grpweaklyCoupled3DofFsiFunctionObjects

Description
    

SeeAlso
    

SourceFiles


\*---------------------------------------------------------------------------*/

#ifndef weaklyCoupled3DofFsi_H
#define weaklyCoupled3DofFsi_H


#include "forces.H"
#include "volFieldsFwd.H"
#include "Tuple2.H"
#include "OFstream.H"
#include "coordinateSystem.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class objectRegistry;
class dictionary;
class polyMesh;
class mapPolyMesh;

namespace functionObjects
{

/*---------------------------------------------------------------------------*\
                           Class weaklyCoupled3DofFsi Declaration
\*---------------------------------------------------------------------------*/

class weaklyCoupled3DofFsi
:
    public forces
{

protected:

        //- cylinder mass
        vector M_;
        
        //- damping coefficient
        vector C_;
        
        //- rigidity coefficient
        vector K_;
        
        //- ratio of real cylinder length to depth of domain
        scalar R_;

        //- maximum amplitude of displacement
        vector Ymax_;

        //- true if after restart data should be appended to previous log 
        //  false if log should be overwritten
        bool append_;

        //- current state of system (y,Vy)
        Pair<vector> Y_; 
        
        //- old state of system (y, Vy)
        Pair<vector> Yold_;
        
        //-
        autoPtr<coordinateSystem> coordSys_;

protected:

        //- Disallow default bitwise copy construct
        weaklyCoupled3DofFsi(const weaklyCoupled3DofFsi&);

        //- Disallow default bitwise assignment
        void operator=(const weaklyCoupled3DofFsi&);
        
        //-
        void createFsiOutFile(const dictionary& dict);


public:

    //- Runtime type information
    TypeName("weaklyCoupled3DofFsi");


    // Constructors

        //- Construct from given Time and dictionary.
        weaklyCoupled3DofFsi
        (
            const word& name,
            const Time&,
            const dictionary&
        );
        
        //- Construct from given objectRegistry and dictionary.
        weaklyCoupled3DofFsi
        (
            const word& name,
            const objectRegistry&,
            const dictionary&
        );

    //- Destructor
    virtual ~weaklyCoupled3DofFsi();


    // Member Functions

        //- Read the weaklyCoupled3DofFsi data
        virtual bool read(const dictionary&);
        
        //-
        virtual bool execute();
        
        //- Write the weaklyCoupled3DofFsi
        virtual bool write();
        
        //- Distributes displacements between slave processes
        // and sets cellDisplacement field Y component on patch
        void setDisplacements(volVectorField& yDispl);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace functionObjects

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
