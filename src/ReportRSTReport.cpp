#include "Report_world.hpp"
#include "ReportRSTReport.hpp"

const char *Report::RSTReport::underlineCharacters = "==\"'-~`.";

Report::RSTReport::RSTReport( std::ostream &ostr ) : m_ostr( ostr ), m_headingLevel( 0 ) {}

Report::RSTReport::~RSTReport() {}

void Report::RSTReport::documentInfo( std::string const &title, std::string const &reportInfo, std::string const &reportDate )
{
    pushHeading( title );

    std::ostringstream ss;
    if ( reportInfo.length() > 0 )
    {
        ss << "info: " << reportInfo << "\n";
    }
    if ( reportDate.length() > 0 )
    {
        ss << "date: " << reportDate << "\n";
    }
    putBlock( ss.str() );

    m_ostr << "\n";
}

void Report::RSTReport::pushHeading( std::string const &heading )
{
    printHeading( heading, underlineCharacters[m_headingLevel], m_headingLevel == 0 );
    m_headingLevel++;
}

void Report::RSTReport::popHeading() { m_headingLevel--; }

void Report::RSTReport::putText( std::string const &text )
{
    for ( auto i = begin( text ); i != end( text ); ++i )
    {
        switch ( *i )
        {
        case '_':
            m_ostr << "\\_";
            break;
        case '*':
            m_ostr << "\\*";
            break;
        case '`':
            m_ostr << "\\`";
            break;
        default:
            m_ostr << *i;
            break;
        }
    }
}

void Report::RSTReport::putEmphText( std::string const &text )
{
    m_ostr << "**";
    for ( auto i = begin( text ); i != end( text ); ++i )
    {
        switch ( *i )
        {
        case '_':
            m_ostr << "\\_";
            break;
        case '*':
            break;
        case '`':
            m_ostr << "'";
            break;
        default:
            m_ostr << *i;
            break;
        }
    }
    m_ostr << "** ";
}

void Report::RSTReport::putLinkText( std::string const &text, std::string const &link )
{
    m_ostr << "`" << text << " <" << link << ">`_ ";
}

void Report::RSTReport::putParagraph( std::string const &text ) { m_ostr << "\n" << text << "\n\n"; }

void Report::RSTReport::putBlock( std::string const &text )
{
    m_ostr << "\n\n::\n\n  ";
    for ( auto i = begin( text ); i != end( text ); ++i )
    {
        switch ( *i )
        {
        case '\n':
            m_ostr << "\n  ";
            break;
        default:
            m_ostr << *i;
            break;
        }
    }
    m_ostr << "\n";
}

void Report::RSTReport::putNumberedList( std::vector<std::string> const &items )
{
    m_ostr << "\n";
    for ( auto i = begin( items ); i != end( items ); ++i )
    {
        m_ostr << "# " << *i << "\n";
    }
    m_ostr << "\n";
}

void Report::RSTReport::putList( std::vector<std::string> const &items )
{
    m_ostr << "\n";
    for ( auto i = begin( items ); i != end( items ); ++i )
    {
        m_ostr << "* " << *i << "\n";
    }
    m_ostr << "\n";
}

void Report::RSTReport::putTable( CSVRow const &header, CSVMatrix const &csv )
{
    std::vector<size_t> columnWidths;
    size_t numColumns = header.size();
    size_t numRows = csv.maxLine();
    std::string spaceBetweenColumns = "   ";

    for ( size_t i = 0; i < numColumns; ++i )
    {
        size_t maxWidth = csv.maxWidthOfColumn( i );
        if ( ( header.size() > i ) )
        {
            size_t w = header[i].length();
            if ( w > maxWidth )
            {
                maxWidth = w;
            }
        }
        columnWidths.push_back( maxWidth );
    }

    m_ostr << "\n";
    for ( size_t i = 0; i < numColumns; ++i )
    {
        printLine( '=', columnWidths[i] + 2 );
        m_ostr << spaceBetweenColumns;
    }
    m_ostr << "\n";
    for ( size_t i = 0; i < numColumns; ++i )
    {
        m_ostr << std::setw( columnWidths[i] + 2 ) << header[i] << spaceBetweenColumns;
    }
    m_ostr << "\n";
    for ( size_t i = 0; i < numColumns; ++i )
    {
        printLine( '=', columnWidths[i] + 2 );
        m_ostr << spaceBetweenColumns;
    }
    m_ostr << "\n";
    for ( size_t row = 0; row < numRows; ++row )
    {
        for ( size_t column = 0; column < numColumns; ++column )
        {
            m_ostr << std::setw( columnWidths[column] + 2 ) << csv.getItem( column, row ) << spaceBetweenColumns;
        }
        m_ostr << "\n";
    }
    for ( size_t i = 0; i < numColumns; ++i )
    {
        printLine( '=', columnWidths[i] + 2 );
        m_ostr << spaceBetweenColumns;
    }
    m_ostr << "\n\n";
}

void Report::RSTReport::printHeading( std::string const &text, char underlineChar, bool topLine )
{
    size_t len = text.length();

    if ( topLine )
    {
        printLine( underlineChar, len );
        m_ostr << "\n";
    }

    m_ostr << text << "\n";
    printLine( underlineChar, len );
    m_ostr << "\n\n";
}

void Report::RSTReport::printLine( char underlineChar, size_t len )
{
    for ( size_t i = 0; i < len; ++i )
    {
        m_ostr << underlineChar;
    }
}
