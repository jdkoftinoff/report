#pragma once

#include "Report_world.hpp"

namespace Report
{

class CSVRow
{
  public:
    using columns_type = std::vector<std::string>;

  private:
    columns_type m_columns;

  public:
    void parse( std::string const &s );

    friend std::istream &operator>>( std::istream &is, CSVRow &r )
    {
        std::string s;
        std::getline( is, s );
        r.parse( s );
        return is;
    }

    friend std::ostream &operator<<( std::ostream &os, CSVRow &r )
    {
        bool first = true;
        for ( auto const &i : r.get() )
        {
            if ( first )
            {
                first = false;
            }
            else
            {
                os << ",";
            }
            os << "\"" << i << "\"";
        }
        os << "\n";
        return os;
    }

    std::string &operator[]( size_t num ) { return m_columns[num]; }

    std::string const &operator[]( size_t num ) const { return m_columns[num]; }

    size_t size() const { return m_columns.size(); }

    columns_type const &get() const { return m_columns; }
};
}
