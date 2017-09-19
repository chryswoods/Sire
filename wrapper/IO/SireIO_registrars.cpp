//WARNING - AUTOGENERATED FILE - CONTENTS WILL BE OVERWRITTEN!
#include <Python.h>

#include "SireIO_registrars.h"

#include "tinker.h"
#include "amberrst.h"
#include "iobase.h"
#include "pdb2.h"
#include "flexibilitylibrary.h"
#include "amber.h"
#include "protoms.h"
#include "perturbationslibrary.h"
#include "pdb.h"
#include "zmatrixmaker.h"
#include "moleculeparser.h"
#include "mol2.h"
#include "trajectorymonitor.h"
#include "amberrst7.h"
#include "amberprm.h"

#include "Helpers/objectregistry.hpp"

void register_SireIO_objects()
{

    ObjectRegistry::registerConverterFor< SireIO::Tinker >();
    ObjectRegistry::registerConverterFor< SireIO::AmberRst >();
    ObjectRegistry::registerConverterFor< SireIO::NullIO >();
    ObjectRegistry::registerConverterFor< SireIO::PDBAtom >();
    ObjectRegistry::registerConverterFor< SireIO::PDBCrystal >();
    ObjectRegistry::registerConverterFor< SireIO::PDBHelix >();
    ObjectRegistry::registerConverterFor< SireIO::PDBMaster >();
    ObjectRegistry::registerConverterFor< SireIO::PDBSheet >();
    ObjectRegistry::registerConverterFor< SireIO::PDBTitle >();
    ObjectRegistry::registerConverterFor< SireIO::PDBTransform >();
    ObjectRegistry::registerConverterFor< SireIO::PDB2 >();
    ObjectRegistry::registerConverterFor< SireIO::FlexibilityLibrary >();
    ObjectRegistry::registerConverterFor< SireIO::FlexibilityTemplate >();
    ObjectRegistry::registerConverterFor< SireIO::Amber >();
    ObjectRegistry::registerConverterFor< SireIO::ProtoMS >();
    ObjectRegistry::registerConverterFor< SireIO::PerturbationsLibrary >();
    ObjectRegistry::registerConverterFor< SireIO::PerturbationsTemplate >();
    ObjectRegistry::registerConverterFor< SireIO::PDB >();
    ObjectRegistry::registerConverterFor< SireIO::ZmatrixMaker >();
    ObjectRegistry::registerConverterFor< SireIO::NullParser >();
    ObjectRegistry::registerConverterFor< SireIO::Mol2 >();
    ObjectRegistry::registerConverterFor< SireIO::TrajectoryMonitor >();
    ObjectRegistry::registerConverterFor< SireIO::AmberRst7 >();
    ObjectRegistry::registerConverterFor< SireIO::AmberPrm >();

}

