/*
  Copyright (C) 2014 by Andreas Lauser

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OPM_PARSER_RTEMPVD_TABLE_HPP
#define	OPM_PARSER_RTEMPVD_TABLE_HPP

#include "SingleRecordTable.hpp"

namespace Opm {
    // forward declaration
    class TableManager;

    class RtempvdTable : protected SingleRecordTable {

        friend class TableManager;
        RtempvdTable() = default;

        /*!
         * \brief Read the RTEMPVD keyword and provide some convenience
         *        methods for it.
         */
        void init(Opm::DeckRecordConstPtr record)
        {
            SingleRecordTable::init(record,
                             std::vector<std::string>{
                                 "Depth",
                                 "Temperature"
                             },
                             /*firstEntityOffset=*/0);

            SingleRecordTable::checkNonDefaultable("Depth");
            SingleRecordTable::checkMonotonic("Depth", /*isAscending=*/true);

            SingleRecordTable::checkNonDefaultable("Temperature");
        }

    public:
        using SingleRecordTable::numTables;
        using SingleRecordTable::numRows;
        using SingleRecordTable::numColumns;
        using SingleRecordTable::evaluate;

        const std::vector<double> &getDepthColumn() const
        { return SingleRecordTable::getColumn(0); }

        const std::vector<double> &getTemperatureColumn() const
        { return SingleRecordTable::getColumn(1); }
    };
}

#endif
