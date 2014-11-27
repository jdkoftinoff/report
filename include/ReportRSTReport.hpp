#pragma once

#include "Report_world.hpp"
#include "ReportReport.hpp"

namespace Report
{

class RSTReport : public Report
{
  private:
    std::ostream &m_ostr;
    int m_headingLevel;
    static const char *underlineCharacters;

  public:
    RSTReport( std::ostream &ostr );

    ~RSTReport();

    void documentInfo( std::string const &title, std::string const &reportInfo, std::string const &reportDate ) override;

    void pushHeading( std::string const &heading ) override;

    void popHeading() override;

    void putText( std::string const &text ) override;

    void putEmphText( std::string const &text ) override;

    void putLinkText( std::string const &text, std::string const &link ) override;

    void putParagraph( std::string const &text ) override;

    void putBlock( std::string const &text ) override;

    void putNumberedList( std::vector<std::string> const &items ) override;

    void putList( std::vector<std::string> const &items ) override;

    void putTable( CSVRow const &header, CSVMatrix const &csv ) override;

    virtual void printHeading( std::string const &text, char underlineChar, bool topLine = false );

    virtual void printLine( char underlineChar, size_t len );
};
}
