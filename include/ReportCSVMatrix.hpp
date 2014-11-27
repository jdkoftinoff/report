#pragma once

#include "Report_world.hpp"
#include "ReportCSVRow.hpp"

namespace Report
{
struct CSVMatrix
{
    using Position = std::pair<size_t, size_t>;

    void setItem( size_t column, size_t line, std::string s )
    {
        m_matrix[std::make_pair( column, line )] = s;
        m_max_column = std::max( column, m_max_column );
        m_max_line = std::max( line, m_max_line );
    }

    std::string getItem( size_t column, size_t line ) const
    {
        std::string s = "";
        auto v = m_matrix.find( std::make_pair( column, line ) );
        if ( v != m_matrix.end() )
        {
            s = v->second;
        }
        return s;
    }

    size_t getItemLength( size_t column, size_t line ) const
    {
        size_t r = 4;
        auto v = m_matrix.find( std::make_pair( column, line ) );
        if ( v != m_matrix.end() )
        {
            r = v->second.length();
        }
        return r;
    }

    void putRow( size_t column, size_t line, CSVRow const &r )
    {
        for ( auto i = begin( r.get() ); i != end( r.get() ); ++i )
        {
            setItem( column++, line, *i );
        }
    }

    size_t maxColumn() const { return m_max_column + 1; }

    size_t maxLine() const { return m_max_line + 1; }

    size_t maxWidthOfColumn( size_t column ) const
    {
        size_t w = 4;
        for ( size_t line = 0; line < maxLine(); ++line )
        {
            size_t len = getItemLength( column, line );
            if ( len > w )
            {
                w = len;
            }
        }
        return w;
    }

    friend std::ostream &operator<<( std::ostream &ostr, CSVMatrix const &m )
    {
        size_t max_line = m.maxLine();
        size_t max_column = m.maxColumn();
        for ( size_t line = 0; line < max_line; ++line )
        {
            for ( size_t column = 0; column < max_column; ++column )
            {
                ostr << "\"" << m.getItem( column, line ) << "\"";
                if ( column != max_column - 1 )
                {
                    ostr << "\t";
                }
                ostr << "\n";
            }
        }
        return ostr;
    }

  private:
    size_t m_max_column{0};
    size_t m_max_line{0};
    std::map<Position, std::string> m_matrix;
};
}
