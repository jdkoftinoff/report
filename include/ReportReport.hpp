#pragma once

#include "Report_world.hpp"
#include "ReportCSVMatrix.hpp"

namespace Report
{
class Report
{
  public:
    virtual ~Report() {}

    virtual void documentInfo( std::string const &title, std::string const &reportInfo, std::string const &reportDate ) = 0;

    virtual void pushHeading( std::string const &heading ) = 0;

    virtual void popHeading() = 0;

    virtual void putText( std::string const &text ) = 0;

    virtual void putEmphText( std::string const &text ) = 0;

    virtual void putLinkText( std::string const &text, std::string const &link ) = 0;

    virtual void putParagraph( std::string const &text ) = 0;

    virtual void putBlock( std::string const &text ) = 0;

    virtual void putNumberedList( std::vector<std::string> const &items ) = 0;

    virtual void putList( std::vector<std::string> const &items ) = 0;

    virtual void putTable( CSVRow const &header, CSVMatrix const &csv ) = 0;
};
}
