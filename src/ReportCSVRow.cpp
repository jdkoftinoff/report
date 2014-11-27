#include "Report_world.hpp"
#include "ReportCSVRow.hpp"

namespace Report
{

void CSVRow::parse( std::string const &s )
{
    m_columns.clear();
    bool in_quote = false;
    std::string cur_value;
    for ( auto i : s )
    {
        if ( !in_quote )
        {
            if ( i == '"' )
            {
                in_quote = true;
            }
            else
            {
                if ( i != ',' && i != '\t' && i != ' ' && i != '\n' && i != '\r' )
                {
                    throw std::runtime_error( "csv parse error, expected ',' or TAB or whitespace" );
                }
            }
        }
        else
        {
            if ( i == '"' )
            {
                m_columns.push_back( cur_value );
                cur_value.clear();
                in_quote = false;
            }
            else
            {
                cur_value.push_back( i );
            }
        }
    }
}
}
