// This file has been generated by Py++.

// (C) Christopher Woods, GPL >= 2 License

#include "boost/python.hpp"
#include "AtomMultiMatcher.pypp.hpp"

namespace bp = boost::python;

#include "SireError/errors.h"

#include "SireStream/datastream.h"

#include "SireUnits/units.h"

#include "atomidentifier.h"

#include "atomidx.h"

#include "atommatcher.h"

#include "atommatchers.h"

#include "atomname.h"

#include "atomselection.h"

#include "evaluator.h"

#include "moleculeinfodata.h"

#include "moleculeview.h"

#include "tostring.h"

#include "atommatchers.h"

SireMol::AtomMultiMatcher __copy__(const SireMol::AtomMultiMatcher &other){ return SireMol::AtomMultiMatcher(other); }

#include "Qt/qdatastream.hpp"

#include "Helpers/str.hpp"

void register_AtomMultiMatcher_class(){

    { //::SireMol::AtomMultiMatcher
        typedef bp::class_< SireMol::AtomMultiMatcher, bp::bases< SireMol::AtomMatcher, SireBase::Property > > AtomMultiMatcher_exposer_t;
        AtomMultiMatcher_exposer_t AtomMultiMatcher_exposer = AtomMultiMatcher_exposer_t( "AtomMultiMatcher", bp::init< >() );
        bp::scope AtomMultiMatcher_scope( AtomMultiMatcher_exposer );
        AtomMultiMatcher_exposer.def( bp::init< SireMol::AtomMatcher const & >(( bp::arg("matcher") )) );
        AtomMultiMatcher_exposer.def( bp::init< SireMol::AtomMatcher const &, SireMol::AtomMatcher const & >(( bp::arg("m0"), bp::arg("m1") )) );
        AtomMultiMatcher_exposer.def( bp::init< SireMol::AtomMultiMatcher const & >(( bp::arg("other") )) );
        { //::SireMol::AtomMultiMatcher::isNull
        
            typedef bool ( ::SireMol::AtomMultiMatcher::*isNull_function_type )(  ) const;
            isNull_function_type isNull_function_value( &::SireMol::AtomMultiMatcher::isNull );
            
            AtomMultiMatcher_exposer.def( 
                "isNull"
                , isNull_function_value );
        
        }
        AtomMultiMatcher_exposer.def( bp::self != bp::self );
        { //::SireMol::AtomMultiMatcher::operator=
        
            typedef ::SireMol::AtomMultiMatcher & ( ::SireMol::AtomMultiMatcher::*assign_function_type )( ::SireMol::AtomMultiMatcher const & ) ;
            assign_function_type assign_function_value( &::SireMol::AtomMultiMatcher::operator= );
            
            AtomMultiMatcher_exposer.def( 
                "assign"
                , assign_function_value
                , ( bp::arg("other") )
                , bp::return_self< >() );
        
        }
        AtomMultiMatcher_exposer.def( bp::self == bp::self );
        { //::SireMol::AtomMultiMatcher::toString
        
            typedef ::QString ( ::SireMol::AtomMultiMatcher::*toString_function_type )(  ) const;
            toString_function_type toString_function_value( &::SireMol::AtomMultiMatcher::toString );
            
            AtomMultiMatcher_exposer.def( 
                "toString"
                , toString_function_value );
        
        }
        { //::SireMol::AtomMultiMatcher::typeName
        
            typedef char const * ( *typeName_function_type )(  );
            typeName_function_type typeName_function_value( &::SireMol::AtomMultiMatcher::typeName );
            
            AtomMultiMatcher_exposer.def( 
                "typeName"
                , typeName_function_value );
        
        }
        { //::SireMol::AtomMultiMatcher::what
        
            typedef char const * ( ::SireMol::AtomMultiMatcher::*what_function_type )(  ) const;
            what_function_type what_function_value( &::SireMol::AtomMultiMatcher::what );
            
            AtomMultiMatcher_exposer.def( 
                "what"
                , what_function_value );
        
        }
        AtomMultiMatcher_exposer.staticmethod( "typeName" );
        AtomMultiMatcher_exposer.def( "__copy__", &__copy__);
        AtomMultiMatcher_exposer.def( "__deepcopy__", &__copy__);
        AtomMultiMatcher_exposer.def( "clone", &__copy__);
        AtomMultiMatcher_exposer.def( "__rlshift__", &__rlshift__QDataStream< ::SireMol::AtomMultiMatcher >,
                            bp::return_internal_reference<1, bp::with_custodian_and_ward<1,2> >() );
        AtomMultiMatcher_exposer.def( "__rrshift__", &__rrshift__QDataStream< ::SireMol::AtomMultiMatcher >,
                            bp::return_internal_reference<1, bp::with_custodian_and_ward<1,2> >() );
        AtomMultiMatcher_exposer.def( "__str__", &__str__< ::SireMol::AtomMultiMatcher > );
        AtomMultiMatcher_exposer.def( "__repr__", &__str__< ::SireMol::AtomMultiMatcher > );
    }

}