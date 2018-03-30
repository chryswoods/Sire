/********************************************\
  *
  *  Sire - Molecular Simulation Framework
  *
  *  Copyright (C) 2014  Christopher Woods
  *
  *  This program is free software; you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation; either version 2 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  *
  *  For full details of the license please see the COPYING file
  *  that should have come with this distribution.
  *
  *  You can contact the authors via the developer's mailing list
  *  at http://siremol.org
  *
\*********************************************/

#include "atommatcher.h"
#include "atommatchers.h"
#include "atomidx.h"
#include "atomname.h"
#include "atomselection.h"
#include "atomidentifier.h"
#include "evaluator.h"
#include "moleculeinfodata.h"
#include "moleculeview.h"

#include "tostring.h"

#include "SireUnits/units.h"

#include "SireError/errors.h"

#include "SireStream/datastream.h"

using namespace SireMol;
using namespace SireUnits;
using namespace SireBase;
using namespace SireStream;

/////////
///////// Implmentation of AtomIdxMatcher
/////////

static const RegisterMetaType<AtomIdxMatcher> r_idxmatcher;

/** Serialise to a binary datastream */
QDataStream SIREMOL_EXPORT &operator<<(QDataStream &ds, const AtomIdxMatcher &idxmatcher)
{
    writeHeader(ds, r_idxmatcher, 1);
    ds << static_cast<const AtomMatcher&>(idxmatcher);
    
    return ds;
}

/** Extract from a binary datastream */
QDataStream SIREMOL_EXPORT &operator>>(QDataStream &ds, AtomIdxMatcher &idxmatcher)
{
    VersionID v = readHeader(ds, r_idxmatcher);
    
    if (v == 1)
    {
        ds >> static_cast<AtomMatcher&>(idxmatcher);
    }
    else
        throw version_error(v, "1", r_idxmatcher, CODELOC);

    return ds;
}

/** Constructor */
AtomIdxMatcher::AtomIdxMatcher() : ConcreteProperty<AtomIdxMatcher,AtomMatcher>()
{}

/** Copy constructor */
AtomIdxMatcher::AtomIdxMatcher(const AtomIdxMatcher &other)
               : ConcreteProperty<AtomIdxMatcher,AtomMatcher>(other)
{}

/** Destructor */
AtomIdxMatcher::~AtomIdxMatcher()
{}

/** Copy assignment operator */
AtomIdxMatcher& AtomIdxMatcher::operator=(const AtomIdxMatcher &other)
{
    return *this;
}

/** Comparison operator */
bool AtomIdxMatcher::operator==(const AtomIdxMatcher &other) const
{
    return true;
}

/** Comparison operator */
bool AtomIdxMatcher::operator!=(const AtomIdxMatcher &other) const
{
    return false;
}

QString AtomIdxMatcher::toString() const
{
    return QObject::tr("AtomIdxMatcher()");
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomIdxMatcher::pvt_match(const MoleculeView &mol0,
                                                 const PropertyMap &map0,
                                                 const MoleculeView &mol1,
                                                 const PropertyMap &map1) const
{
    const AtomSelection sel0 = mol0.selection();
    const AtomSelection sel1 = mol1.selection();
    
    QHash<AtomIdx,AtomIdx> map;
    
    if (sel0.selectedAll() and sel1.selectedAll())
    {
        const int nats = qMin(sel0.nSelectedAtoms(), sel1.nSelectedAtoms());
    
        map.reserve(nats);
    
        for (int i=0; i<nats; ++i)
        {
            map.insert( AtomIdx(i), AtomIdx(i) );
        }
    }
    else
    {
        const int nats1 = mol1.data().info().nAtoms();
    
        foreach (const AtomIdx atom, sel0.selectedAtoms())
        {
            if (atom.value() < nats1)
            {
                if (sel1.selected(atom))
                    map.insert(atom, atom);
            }
        }
    }
    
    return map;
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomIdxMatcher::pvt_match(const MoleculeInfoData &mol0,
                                                 const MoleculeInfoData &mol1) const
{
    QHash<AtomIdx,AtomIdx> map;
    
    const int nats = qMin(mol0.nAtoms(), mol1.nAtoms());
    
    map.reserve(nats);

    for (int i=0; i<nats; ++i)
    {
        map.insert( AtomIdx(i), AtomIdx(i) );
    }
    
    return map;
}

/** The AtomIdx matcher does not change the order of the atoms */
bool AtomIdxMatcher::pvt_changesOrder(const MoleculeInfoData &molinfo0,
                                      const MoleculeInfoData &molinfo1) const
{
    return false;
}

const char* AtomIdxMatcher::typeName()
{
    return QMetaType::typeName( qMetaTypeId<AtomIdxMatcher>() );
}

/////////
///////// Implementation of AtomNameMatcher
/////////

static const RegisterMetaType<AtomNameMatcher> r_namematcher;

/** Serialise to a binary datastream */
QDataStream SIREMOL_EXPORT &operator<<(QDataStream &ds, 
                                       const AtomNameMatcher &namematcher)
{
    writeHeader(ds, r_namematcher, 1);
    ds << static_cast<const AtomMatcher&>(namematcher);
    
    return ds;
}

/** Extract from a binary datastream */
QDataStream SIREMOL_EXPORT &operator>>(QDataStream &ds, AtomNameMatcher &namematcher)
{
    VersionID v = readHeader(ds, r_namematcher);
    
    if (v == 1)
    {
        ds >> static_cast<AtomMatcher&>(namematcher);
    }
    else
        throw version_error(v, "1", r_namematcher, CODELOC);

    return ds;
}

/** Constructor */
AtomNameMatcher::AtomNameMatcher() : ConcreteProperty<AtomNameMatcher,AtomMatcher>()
{}

/** Copy constructor */
AtomNameMatcher::AtomNameMatcher(const AtomNameMatcher &other)
               : ConcreteProperty<AtomNameMatcher,AtomMatcher>(other)
{}

/** Destructor */
AtomNameMatcher::~AtomNameMatcher()
{}

/** Copy assignment operator */
AtomNameMatcher& AtomNameMatcher::operator=(const AtomNameMatcher &other)
{
    return *this;
}

/** Comparison operator */
bool AtomNameMatcher::operator==(const AtomNameMatcher &other) const
{
    return true;
}

/** Comparison operator */
bool AtomNameMatcher::operator!=(const AtomNameMatcher &other) const
{
    return false;
}

QString AtomNameMatcher::toString() const
{
    return QObject::tr("AtomNameMatcher()");
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomNameMatcher::pvt_match(const MoleculeView &mol0,
                                                  const PropertyMap &map0,
                                                  const MoleculeView &mol1,
                                                  const PropertyMap &map1) const
{
    QHash<AtomIdx,AtomIdx> map;

    const AtomSelection sel0 = mol0.selection();
    const AtomSelection sel1 = mol1.selection();
    
    if (sel0.selectedAll() and sel1.selectedAll())
    {
        for (int i=0; i<mol0.data().info().nAtoms(); ++i)
        {
            const AtomIdx idx0(i);
        
            const AtomName name = mol0.data().info().name(idx0);
            
            try
            {
                AtomIdx idx1 = mol1.data().info().atomIdx(name);
                map.insert( idx0, idx1 );
            }
            catch(...)
            {}
        }
    }
    else
    {
        foreach (const AtomIdx idx0, sel0.selectedAtoms())
        {
            const AtomName name = mol0.data().info().name(idx0);
            
            try
            {
                AtomIdx idx1 = mol1.data().info().atomIdx(name);
                
                if (sel1.selected(idx1))
                    map.insert(idx0, idx1);
            }
            catch(...)
            {}
        }
    }

    return map;
}
/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomNameMatcher::pvt_match(const MoleculeInfoData &mol0,
                                                  const MoleculeInfoData &mol1) const
{
    QHash<AtomIdx,AtomIdx> map;

    for (int i=0; i<mol0.nAtoms(); ++i)
    {
        const AtomIdx idx0(i);
    
        const AtomName name = mol0.name(idx0);
        
        try
        {
            AtomIdx idx1 = mol1.atomIdx(name);
            map.insert( idx0, idx1 );
        }
        catch(...)
        {}
    }

    return map;
}

const char* AtomNameMatcher::typeName()
{
    return QMetaType::typeName( qMetaTypeId<AtomNameMatcher>() );
}

/////////
///////// Implementation of AtomMCSMatcher
/////////

static const RegisterMetaType<AtomMCSMatcher> r_mcsmatcher;

/** Serialise to a binary datastream */
QDataStream SIREMOL_EXPORT &operator<<(QDataStream &ds, 
                                       const AtomMCSMatcher &mcsmatcher)
{
    writeHeader(ds, r_mcsmatcher, 2);
    
    SharedDataStream sds(ds);
    
    sds << mcsmatcher.prematcher << double(mcsmatcher.t.to(second))
        << mcsmatcher.match_light
        << static_cast<const AtomMatcher&>(mcsmatcher);
    
    return ds;
}

/** Extract from a binary datastream */
QDataStream SIREMOL_EXPORT &operator>>(QDataStream &ds, AtomMCSMatcher &mcsmatcher)
{
    VersionID v = readHeader(ds, r_mcsmatcher);
    
    if (v == 2)
    {
        double timeout;
        
        SharedDataStream sds(ds);
        
        sds >> mcsmatcher.prematcher >> timeout
            >> mcsmatcher.match_light
            >> static_cast<AtomMatcher&>(mcsmatcher);
        
        mcsmatcher.t = timeout*second;
    }
    else if (v == 1)
    {
        double timeout;
        
        SharedDataStream sds(ds);
        
        sds >> mcsmatcher.prematcher >> timeout >> static_cast<AtomMatcher&>(mcsmatcher);
        
        mcsmatcher.t = timeout*second;
        mcsmatcher.match_light = false;
    }
    else
        throw version_error(v, "1,2", r_namematcher, CODELOC);

    return ds;
}

/** Constructor */
AtomMCSMatcher::AtomMCSMatcher()
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(), t(1*second),
                 match_light(false)
{}

/** Construct specifying the timeout for the MCS match */
AtomMCSMatcher::AtomMCSMatcher(const SireUnits::Dimension::Time &timeout)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(), t(timeout),
                 match_light(false)
{}

/** Construct specifying the prematcher for the MCS match */
AtomMCSMatcher::AtomMCSMatcher(const AtomMatcher &matcher)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(),
                 prematcher(matcher), t(1*second), match_light(false)
{}

/** Construct specifying the timeout and prematcher for the MCS match */
AtomMCSMatcher::AtomMCSMatcher(const AtomMatcher &matcher,
                               const SireUnits::Dimension::Time &timeout)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(),
                 prematcher(matcher), t(timeout), match_light(false)
{}

/** Constructor, specifying whether or not to match light atoms */
AtomMCSMatcher::AtomMCSMatcher(bool match_light_atoms)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(), t(1*second),
                 match_light(match_light_atoms)
{}

/** Construct specifying the timeout for the MCS match, and specifying whether or not 
    to match light atoms */
AtomMCSMatcher::AtomMCSMatcher(const SireUnits::Dimension::Time &timeout,
                               bool match_light_atoms)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(), t(timeout),
                 match_light(match_light_atoms)
{}

/** Construct specifying the prematcher for the MCS match,
    and specifying whether or not to match light atoms
*/
AtomMCSMatcher::AtomMCSMatcher(const AtomMatcher &matcher,
                               bool match_light_atoms)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(),
                 prematcher(matcher), t(1*second), match_light(match_light_atoms)
{}

/** Construct specifying the timeout and prematcher for the MCS match,
    and specifying whether or not to match light atoms
*/
AtomMCSMatcher::AtomMCSMatcher(const AtomMatcher &matcher,
                               const SireUnits::Dimension::Time &timeout,
                               bool match_light_atoms)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(),
                 prematcher(matcher), t(timeout), match_light(match_light_atoms)
{}

/** Copy constructor */
AtomMCSMatcher::AtomMCSMatcher(const AtomMCSMatcher &other)
               : ConcreteProperty<AtomMCSMatcher,AtomMatcher>(other),
                 prematcher(other.prematcher), t(other.t),
                 match_light(other.match_light)
{}

/** Destructor */
AtomMCSMatcher::~AtomMCSMatcher()
{}

/** Copy assignment operator */
AtomMCSMatcher& AtomMCSMatcher::operator=(const AtomMCSMatcher &other)
{
    if (this != &other)
    {
        t = other.t;
        prematcher = other.prematcher;
        match_light = other.match_light;
    }
    
    return *this;
}

/** Comparison operator */
bool AtomMCSMatcher::operator==(const AtomMCSMatcher &other) const
{
    return prematcher == other.prematcher and t == other.t and match_light == other.match_light;
}

/** Comparison operator */
bool AtomMCSMatcher::operator!=(const AtomMCSMatcher &other) const
{
    return not operator==(other);
}

QString AtomMCSMatcher::toString() const
{
    if (prematcher.isNull() or prematcher.read().isNull())
    {
        return QObject::tr("AtomMCSMatcher( timeout() = %1 s, matchingLightAtoms() = %2 )")
                .arg(t.to(second)).arg(match_light);
    }
    else
    {
        return QObject::tr("AtomMCSMatcher( preMatcher() = %1, timeout() = %2 s, "
                           "matchingLightAtoms() = %3 )")
                    .arg(prematcher.read().toString())
                    .arg(t.to(second))
                    .arg(match_light);
    }
}

const char* AtomMCSMatcher::typeName()
{
    return QMetaType::typeName( qMetaTypeId<AtomMCSMatcher>() );
}

/** Return the prematcher (if any) that is used to pre-match atoms
    before the MCS match */
const AtomMatcher& AtomMCSMatcher::preMatcher() const
{
    return prematcher.read();
}

/** Return the timeout before the MCS match is abandoned */
SireUnits::Dimension::Time AtomMCSMatcher::timeout() const
{
    return t;
}

/** Return whether or not this will include light atoms (e.g. hydrogen)
    when searching for the maximum common substructure */
bool AtomMCSMatcher::matchingLightAtoms() const
{
    return match_light;
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomMCSMatcher::pvt_match(const MoleculeView &mol0,
                                                 const PropertyMap &map0,
                                                 const MoleculeView &mol1,
                                                 const PropertyMap &map1) const
{
    if (prematcher.isNull() or prematcher.read().isNull())
        return Evaluator(mol0).findMCS(mol1, t, match_light, map0, map1);
    else
        return Evaluator(mol0).findMCS(mol1, prematcher.read(), t, match_light, map0, map1);
}

/////////
///////// Implementation of AtomIDMatcher
/////////

static const RegisterMetaType<AtomIDMatcher> r_idmatcher;

/** Serialise to a binary datastream */
QDataStream SIREMOL_EXPORT &operator<<(QDataStream &ds, 
                                       const AtomIDMatcher &idmatcher)
{
    writeHeader(ds, r_idmatcher, 1);
    
    SharedDataStream sds(ds);
    sds << idmatcher.m << static_cast<const AtomMatcher&>(idmatcher);
    
    return ds;
}

/** Extract from a binary datastream */
QDataStream SIREMOL_EXPORT &operator>>(QDataStream &ds, AtomIDMatcher &idmatcher)
{
    VersionID v = readHeader(ds, r_idmatcher);
    
    if (v == 1)
    {
        SharedDataStream sds(ds);
        sds >> idmatcher.m >> static_cast<AtomMatcher&>(idmatcher);
    }
    else
        throw version_error(v, "1", r_idmatcher, CODELOC);

    return ds;
}

/** Constructor */
AtomIDMatcher::AtomIDMatcher() : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{}

/** Construct to match atom names */
AtomIDMatcher::AtomIDMatcher(const QList< QPair<QString,QString> > &names)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    for (int i=0; i<names.count(); ++i)
    {
        const QPair<QString,QString> &name = names[i];

        if (not (name.first.isEmpty() or name.second.isEmpty()))
        {
            m.append( QPair<AtomIdentifier,AtomIdentifier>( AtomName(name.first),
                                                            AtomName(name.second) ) );
        }
    }
}

/** Construct to match atom names */
AtomIDMatcher::AtomIDMatcher(const QHash<QString,QString> &names)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    QSet<QString> matched_names;

    for (QHash<QString,QString>::const_iterator it = names.constBegin();
         it != names.constEnd();
         ++it)
    {
        if (not it.key().isEmpty() or it.value().isEmpty())
        {
            if (matched_names.contains(it.value()))
                throw SireError::invalid_arg( QObject::tr(
                        "You are trying to match multiple atoms (%1) to the same name (%2). "
                        "Please ensure that you have a unique name <=> name mapping.")
                            .arg(Sire::toString(names.keys(it.value())))
                            .arg(it.value()), CODELOC );
        
            matched_names.insert(it.value());
            m.append( QPair<AtomIdentifier,AtomIdentifier>( AtomName(it.key()),
                                                            AtomName(it.value()) ) );
        }
    }
}

/** Construct to match atom indexes */
AtomIDMatcher::AtomIDMatcher(const QList< QPair<int,int> > &idxs)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    for (int i=0; i<idxs.count(); ++i)
    {
        const QPair<int,int> &idx = idxs[i];
        
        m.append( QPair<AtomIdentifier,AtomIdentifier>( AtomIdx(idx.first),
                                                        AtomIdx(idx.second) ) );
    }
}

/** Construct to match atom indexes */
AtomIDMatcher::AtomIDMatcher(const QHash<int,int> &idxs)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    QSet<int> matched_idxs;
    
    for (QHash<int,int>::const_iterator it = idxs.constBegin();
         it != idxs.constEnd();
         ++it)
    {
        if (matched_idxs.contains(it.value()))
            throw SireError::invalid_arg( QObject::tr(
                    "You are trying to match multiple atoms (%1) to the same index (%2). "
                    "Please ensure that you have a unique index <=> index mapping.")
                        .arg(Sire::toString(idxs.keys(it.value())))
                        .arg(it.value()), CODELOC );
    
        matched_idxs.insert(it.value());
        
        m.append( QPair<AtomIdentifier,AtomIdentifier>( AtomIdx(it.key()),
                                                        AtomIdx(it.value()) ) );
    }
}

/** Construct to match specified AtomIdentifiers */
AtomIDMatcher::AtomIDMatcher(const QList< QPair<AtomIdentifier,AtomIdentifier> > &ids)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    for (int i=0; i<ids.count(); ++i)
    {
        const QPair<AtomIdentifier,AtomIdentifier> id = ids[i];
        
        if (not (id.first.isNull() or id.second.isNull()))
            m.append(id);
    }
}

/** Construct to match specified AtomIdentifiers */
AtomIDMatcher::AtomIDMatcher(const QHash<AtomIdentifier,AtomIdentifier> &ids)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    QSet<AtomIdentifier> matched_ids;
    
    for (QHash<AtomIdentifier,AtomIdentifier>::const_iterator it = ids.constBegin();
         it != ids.constEnd();
         ++it)
    {
        if (not it.key().isNull() or it.value().isNull())
        {
            if (matched_ids.contains(it.value()))
                throw SireError::invalid_arg( QObject::tr(
                        "You are trying to match multiple atoms (%1) to the same ID (%2). "
                        "Please ensure that you have a unique ID <=> ID mapping.")
                            .arg(Sire::toString(ids.keys(it.value())))
                            .arg(it.value().toString()), CODELOC );
        
            matched_ids.insert(it.value());
            
            m.append( QPair<AtomIdentifier,AtomIdentifier>(it.key(), it.value()) );
        }
    }
}

/** Construct to match atom names */
AtomIDMatcher::AtomIDMatcher(const QList< boost::tuple<QString,QString> > &names)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    for (int i=0; i<names.count(); ++i)
    {
        const boost::tuple<QString,QString> &name = names[i];

        if (not (name.get<0>().isEmpty() or name.get<1>().isEmpty()))
        {
            m.append( QPair<AtomIdentifier,AtomIdentifier>( AtomName(name.get<0>()),
                                                            AtomName(name.get<1>()) ) );
        }
    }
}

/** Shorthand to construct to match atom names from the passed single string, 
    with format 'atom0:atom1,atom2:atom3' etc. (i.e. comma separated pairs,
    each pair is colon separated to match atom to atom, e.g. this string
    matches atom0 to atom1, and atom2 to atom3) */
AtomIDMatcher::AtomIDMatcher(const QString &atom_names)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    auto words = atom_names.split(",");
    
    if (not words.isEmpty())
    {
        QHash<QString,QString> match_names;
        match_names.reserve(words.count());
        
        for (auto word : words)
        {
            auto atoms = word.split(":");
            
            if (atoms.count() == 2)
            {
                match_names.insert( atoms[0].simplified(), atoms[1].simplified() );
            }
        }
        
        this->operator=( AtomIDMatcher(match_names) );
    }
}

/** Construct to match atom indexes */
AtomIDMatcher::AtomIDMatcher(const QList< boost::tuple<int,int> > &idxs)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    for (int i=0; i<idxs.count(); ++i)
    {
        const boost::tuple<int,int> &idx = idxs[i];
        
        m.append( QPair<AtomIdentifier,AtomIdentifier>( AtomIdx(idx.get<0>()),
                                                        AtomIdx(idx.get<1>()) ) );
    }
}

/** Construct to match specified AtomIdentifiers */
AtomIDMatcher::AtomIDMatcher(const QList< boost::tuple<AtomIdentifier,AtomIdentifier> > &ids)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>()
{
    for (int i=0; i<ids.count(); ++i)
    {
        const boost::tuple<AtomIdentifier,AtomIdentifier> id = ids[i];
        
        if (not (id.get<0>().isNull() or id.get<1>().isNull()))
            m.append( QPair<AtomIdentifier,AtomIdentifier>(id.get<0>(),id.get<1>()) );
    }
}

/** Copy constructor */
AtomIDMatcher::AtomIDMatcher(const AtomIDMatcher &other)
              : ConcreteProperty<AtomIDMatcher,AtomMatcher>(other),
                m(other.m)
{}

/** Destructor */
AtomIDMatcher::~AtomIDMatcher()
{}

/** Copy assignment operator */
AtomIDMatcher& AtomIDMatcher::operator=(const AtomIDMatcher &other)
{
    m = other.m;
    return *this;
}

/** Comparison operator */
bool AtomIDMatcher::operator==(const AtomIDMatcher &other) const
{
    return m == other.m;
}

/** Comparison operator */
bool AtomIDMatcher::operator!=(const AtomIDMatcher &other) const
{
    return not operator==(*this);
}

/** Return whether or not this matcher is null (cannot be used for matching) */
bool AtomIDMatcher::isNull() const
{
    return m.isEmpty();
}

QString AtomIDMatcher::toString() const
{
    if (isNull())
        return QObject::tr("AtomIDMatcher::null");

    QStringList matches;
    
    for (QList< QPair<AtomIdentifier,AtomIdentifier> >::const_iterator it = m.constBegin();
         it != m.constEnd();
         ++it)
    {
        matches.append( QObject::tr(" %1 <=> %2").arg(it->first.toString(),
                                                      it->second.toString()) );
    }

    return QObject::tr("AtomIDMatcher( %1 )").arg( matches.join("\n") );
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomIDMatcher::pvt_match(const MoleculeView &mol0,
                                                const PropertyMap &map0,
                                                const MoleculeView &mol1,
                                                const PropertyMap &map1) const
{
    QHash<AtomIdx,AtomIdx> map;

    const AtomSelection sel0 = mol0.selection();
    const AtomSelection sel1 = mol1.selection();

    QSet<AtomIdx> found_1;
    
    const int nats0 = sel0.nSelectedAtoms();
    const int nats1 = sel1.nSelectedAtoms();
    
    for (QList< QPair<AtomIdentifier,AtomIdentifier> >::const_iterator it = m.constBegin();
         it != m.constEnd();
         ++it)
    {
        //find the atom in mol0
        try
        {
            AtomIdx idx0 = mol0.data().info().atomIdx(it->first);
            
            if (sel0.selected(idx0) and not map.contains(idx0))
            {
                try
                {
                    AtomIdx idx1 = mol1.data().info().atomIdx(it->second);
                    
                    if (sel1.selected(idx1) and not found_1.contains(idx1))
                    {
                        map.insert(idx0, idx1);
                        found_1.insert(idx1);
                    }
                }
                catch(...)
                {}
            }
        }
        catch(...)
        {}
        
        if (map.count() >= nats0 or found_1.count() >= nats1)
            break;
    }
        
    return map;
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomIDMatcher::pvt_match(const MoleculeInfoData &mol0,
                                                const MoleculeInfoData &mol1) const
{
    QHash<AtomIdx,AtomIdx> map;


    QSet<AtomIdx> found_1;
    
    const int nats0 = mol0.nAtoms();
    const int nats1 = mol1.nAtoms();
    
    for (QList< QPair<AtomIdentifier,AtomIdentifier> >::const_iterator it = m.constBegin();
         it != m.constEnd();
         ++it)
    {
        //find the atom in mol0
        try
        {
            AtomIdx idx0 = mol0.atomIdx(it->first);
            
            if (not map.contains(idx0))
            {
                try
                {
                    AtomIdx idx1 = mol1.atomIdx(it->second);
                    
                    if (not found_1.contains(idx1))
                    {
                        map.insert(idx0, idx1);
                        found_1.insert(idx1);
                    }
                }
                catch(...)
                {}
            }
        }
        catch(...)
        {}
        
        if (map.count() >= nats0 or found_1.count() >= nats1)
            break;
    }
        
    return map;
}

const char* AtomIDMatcher::typeName()
{
    return QMetaType::typeName( qMetaTypeId<AtomIDMatcher>() );
}

/////////
///////// Implementation of AtomMultiMatcher
/////////

static const RegisterMetaType<AtomMultiMatcher> r_multimatcher;

/** Serialise to a binary datastream */
QDataStream SIREMOL_EXPORT &operator<<(QDataStream &ds, 
                                       const AtomMultiMatcher &multimatcher)
{
    writeHeader(ds, r_multimatcher, 1);
    
    SharedDataStream sds(ds);
    sds << multimatcher.m << static_cast<const AtomMatcher&>(multimatcher);
    
    return ds;
}

/** Extract from a binary datastream */
QDataStream SIREMOL_EXPORT &operator>>(QDataStream &ds, AtomMultiMatcher &multimatcher)
{
    VersionID v = readHeader(ds, r_multimatcher);
    
    if (v == 1)
    {
        SharedDataStream sds(ds);
        sds >> multimatcher.m >> static_cast<AtomMatcher&>(multimatcher);
    }
    else
        throw version_error(v, "1", r_multimatcher, CODELOC);

    return ds;
}

/** Constructor */
AtomMultiMatcher::AtomMultiMatcher() : ConcreteProperty<AtomMultiMatcher,AtomMatcher>()
{}

/** Construct from a single match */
AtomMultiMatcher::AtomMultiMatcher(const AtomMatcher &matcher)
                 : ConcreteProperty<AtomMultiMatcher,AtomMatcher>()
{
    if (matcher.isA<AtomMultiMatcher>())
    {
        this->operator=(matcher.asA<AtomMultiMatcher>());
    }
    else
    {
        m.append( matcher );
    }
}

/** Construct from a pair of matches */
AtomMultiMatcher::AtomMultiMatcher(const AtomMatcher &m0, const AtomMatcher &m1)
                 : ConcreteProperty<AtomMultiMatcher,AtomMatcher>()
{
    this->operator=( AtomMultiMatcher(m0) );
    
    if (m1.isA<AtomMultiMatcher>())
    {
        m += m1.asA<AtomMultiMatcher>().m;
    }
    else
    {
        m += m1;
    }
}

/** Copy constructor */
AtomMultiMatcher::AtomMultiMatcher(const AtomMultiMatcher &other)
                 : ConcreteProperty<AtomMultiMatcher,AtomMatcher>(other),
                   m(other.m)
{}

/** Destructor */
AtomMultiMatcher::~AtomMultiMatcher()
{}

/** Copy assignment operator */
AtomMultiMatcher& AtomMultiMatcher::operator=(const AtomMultiMatcher &other)
{
    m = other.m;
    return *this;
}

/** Comparison operator */
bool AtomMultiMatcher::operator==(const AtomMultiMatcher &other) const
{
    return m == other.m;
}

/** Comparison operator */
bool AtomMultiMatcher::operator!=(const AtomMultiMatcher &other) const
{
    return not operator==(*this);
}

/** Return whether or not this matcher is null (cannot be used for matching) */
bool AtomMultiMatcher::isNull() const
{
    return m.isEmpty();
}

QString AtomMultiMatcher::toString() const
{
    if (isNull())
        return QObject::tr("AtomMultiMatcher::null");

    QStringList matches;
    
    for (QList<AtomMatcherPtr>::const_iterator it = m.constBegin();
         it != m.constEnd();
         ++it)
    {
        matches.append( QObject::tr(" %1").arg(it->read().toString()) );
    }

    return QObject::tr("AtomMultiMatcher{ %1 }").arg( matches.join(" +\n") );
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomMultiMatcher::pvt_match(const MoleculeView &mol0,
                                                   const PropertyMap &map0,
                                                   const MoleculeView &mol1,
                                                   const PropertyMap &map1) const
{
    if (m.isEmpty())
        return QHash<AtomIdx,AtomIdx>();
    else if (m.count() == 1)
        return m.at(0).read().match(mol0,mol1);

    QHash<AtomIdx,AtomIdx> map;

    QSet<AtomIdx> found_1;
    const int nats0 = mol0.selection().nSelected();
    const int nats1 = mol1.selection().nSelected();
    
    for (QList<AtomMatcherPtr>::const_iterator it = m.constBegin();
         it != m.constEnd();
         ++it)
    {
        QHash<AtomIdx,AtomIdx> lmap = it->read().match(mol0, map0, mol1, map1);
        
        for (QHash<AtomIdx,AtomIdx>::const_iterator it2 = lmap.constBegin();
             it2 != lmap.constEnd();
             ++it2)
        {
            if (not (map.contains(it2.key()) or found_1.contains(it2.value())))
            {
                map.insert( it2.key(), it2.value() );
                found_1.insert( it2.value() );
            }
        }
        
        if (map.count() == nats0)
            break;
        
        if (found_1.count() == nats1)
            break;
        
        if (map.count() > nats0)
            throw SireError::program_bug( QObject::tr(
                    "Should not have excess matched atoms???"), CODELOC );
        
        if (found_1.count() > nats1)
            throw SireError::program_bug( QObject::tr(
                    "Should not have excess matched atoms???"), CODELOC );
    }
        
    return map;
}

/** Match the atoms in 'mol1' to the atoms in 'mol0' - this
    returns the AtomIdxs of the atoms in 'mol1' that are in
    'mol0', indexed by the AtomIdx of the atom in 'mol0'.
    
     This skips atoms in 'mol1' that are not in 'mol0'
*/
QHash<AtomIdx,AtomIdx> AtomMultiMatcher::pvt_match(const MoleculeInfoData &mol0,
                                                   const MoleculeInfoData &mol1) const
{
    if (m.isEmpty())
        return QHash<AtomIdx,AtomIdx>();
    else if (m.count() == 1)
        return m.at(0).read().match(mol0,mol1);

    QHash<AtomIdx,AtomIdx> map;

    QSet<AtomIdx> found_1;
    const int nats0 = mol0.nAtoms();
    const int nats1 = mol1.nAtoms();
    
    for (QList<AtomMatcherPtr>::const_iterator it = m.constBegin();
         it != m.constEnd();
         ++it)
    {
        QHash<AtomIdx,AtomIdx> lmap = it->read().match(mol0, mol1);
        
        for (QHash<AtomIdx,AtomIdx>::const_iterator it2 = lmap.constBegin();
             it2 != lmap.constEnd();
             ++it2)
        {
            if (not (map.contains(it2.key()) or found_1.contains(it2.value())))
            {
                map.insert( it2.key(), it2.value() );
                found_1.insert( it2.value() );
            }
        }
        
        if (map.count() == nats0)
            break;
        
        if (found_1.count() == nats1)
            break;
        
        if (map.count() > nats0)
            throw SireError::program_bug( QObject::tr(
                    "Should not have excess matched atoms???"), CODELOC );
        
        if (found_1.count() > nats1)
            throw SireError::program_bug( QObject::tr(
                    "Should not have excess matched atoms???"), CODELOC );
    }
        
    return map;
}

const char* AtomMultiMatcher::typeName()
{
    return QMetaType::typeName( qMetaTypeId<AtomMultiMatcher>() );
}
