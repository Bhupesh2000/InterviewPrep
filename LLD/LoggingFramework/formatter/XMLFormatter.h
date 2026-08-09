#ifndef XML_FORMATTER_H
#define XML_FORMATTER_H

#include <string>

#include "./Formatter.h"
#include "../TimeUtil.h"

class XMLFormatter : public Formatter{

    // A user message containing '<' or '&' would otherwise produce invalid XML.
    static std::string escape(const std::string& s){
        std::string out;
        out.reserve(s.size());
        for(char c : s){
            switch(c){
                case '&':  out += "&amp;";  break;
                case '<':  out += "&lt;";   break;
                case '>':  out += "&gt;";   break;
                case '"':  out += "&quot;"; break;
                case '\'': out += "&apos;"; break;
                default:   out += c;        break;
            }
        }
        return out;
    }

public:
    std::string format(const Message& m) const override{
        return std::string("<record>")
             + "<timestamp>" + formatTimestamp(m.getTimeStamp()) + "</timestamp>"
             + "<level>" + getString(m.getLevel()) + "</level>"
             + "<message>" + escape(m.getMessageString()) + "</message>"
             + "</record>\n";
    }
};

#endif
