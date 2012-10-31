#include "parser.h"
#include <QVector>

Parser::Parser(const QString *data)
{
    site = data;
}

QString Parser::parse()
{
    QString res="";
    int current=0;
    QVector<int> currentMemory;
    int endOfNode=0;

    res = "<h3>Today </h3><div>";

    while (current>=0)
    {
        current = site->indexOf("cell-today\">", current);
        if (current==-1) continue;

        if (parseEventTime(current, endOfNode, res)==-1) continue;
        parseEventSummary(current, endOfNode, res);
        currentMemory.push_back(current);
        current++;
    }

    res += "<h3>Tomorrow </h3> <div>";

    for (QVector<int>::iterator i=currentMemory.begin(); i!=currentMemory.end(); ++i)
    {
        current=*i;
        current = site->indexOf("<td", current);
        if (current==-1) continue;

        if (site->midRef(current+3, 1)!=">") break;
        if (parseEventTime(current, endOfNode, res)==-1) continue;
        parseEventSummary(current, endOfNode, res);
        current++;
    }

    return res;
}

int Parser::parseEventTime(int &current, int &endOfNode, QString &res)
{
    current = site->indexOf("event-time", current);
    if (current==-1) return -1;
    endOfNode = site->indexOf("</", current);
    res += "<b>";
    res += site->midRef(current+12, endOfNode-current-12);
    res += "</b>";
    res += " ";
    return 0;
}

int Parser::parseEventSummary(int &current, int &endOfNode, QString &res)
{
    current = site->indexOf("event-summary", current);
    endOfNode = site->indexOf("</", current);
    res += site->midRef(current+15, endOfNode-current-15);
    res += "<div>";
    return 0;
}

