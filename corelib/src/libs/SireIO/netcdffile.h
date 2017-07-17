/********************************************\
  *
  *  Sire - Molecular Simulation Framework
  *
  *  Copyright (C) 2017  Christopher Woods
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

#ifndef SIREIO_NETCDFFILE_H
#define SIREIO_NETCDFFILE_H

#include "sireglobal.h"

#include <QString>
#include <boost/noncopyable.hpp>

SIRE_BEGIN_HEADER

namespace SireIO
{

/** This class provides an internal interface to NetCDF files 

    @author Christopher Woods
*/
class SIREIO_EXPORT NetCDFFile : public boost::noncopyable
{
public:
    NetCDFFile();
    NetCDFFile(const QString &filename);
    
    ~NetCDFFile();
    
    QString getStringAttribute(const QString &name) const;
    
private:
    /** The name of the file */
    QString fname;

    /** Handle to the NetCDF file */
    int hndl;
};

}

SIRE_END_HEADER

#endif
