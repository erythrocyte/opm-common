/*
  Copyright (C) 2015 IRIS AS

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
#ifndef OPM_PARSER_SGFN_TABLE_HPP
#define OPM_PARSER_SGFN_TABLE_HPP

#include "SingleRecordTable.hpp"

namespace Opm {
    // forward declaration
    class TableManager;

    class SgfnTable : protected SingleRecordTable {

        friend class TableManager;

        /*!
         * \brief Read the SGFN keyword and provide some convenience
         *        methods for it.
         */
        void init(Opm::DeckRecordConstPtr record)
        {
            SingleRecordTable::init(record,
                             std::vector<std::string>{"SG", "KRG", "PCOG"},
                             /*firstEntityOffset=*/0);

            SingleRecordTable::checkNonDefaultable("SG");
            SingleRecordTable::checkMonotonic("SG",   /*isAscending=*/true);
            SingleRecordTable::applyDefaultsLinear("KRG");
            SingleRecordTable::applyDefaultsLinear("PCOG");
            SingleRecordTable::checkMonotonic("KRG",  /*isAscending=*/true,  /*strict=*/false);
            SingleRecordTable::checkMonotonic("PCOG", /*isAscending=*/true, /*strict=*/false);
        }

    public:
        SgfnTable() = default;

#ifdef BOOST_TEST_MODULE
        // DO NOT TRY TO CALL THIS METHOD! it is only for the unit tests!
        void initFORUNITTESTONLY(Opm::DeckRecordConstPtr record)
        { init(record); }
#endif

        using SingleRecordTable::numTables;
        using SingleRecordTable::numRows;
        using SingleRecordTable::numColumns;
        using SingleRecordTable::evaluate;

        const std::vector<double> &getSgColumn() const
        { return SingleRecordTable::getColumn(0); }

        const std::vector<double> &getKrgColumn() const
        { return SingleRecordTable::getColumn(1); }

        // this column is p_g - p_o (non-wetting phase pressure minus
        // wetting phase pressure for a given gas saturation)
        const std::vector<double> &getPcogColumn() const
        { return SingleRecordTable::getColumn(2); }
    };
}

#endif

