#ifndef PARSER_H
#define PARSER_H

#include <QDebug>
#include <QString>

class Parser
{
public:
    Parser(const QString *data);
    QString parse();
private:
    const QString *site;
private:
    int parseEventTime(int &current, int &endOfNode, QString &res);
    int parseEventSummary(int &current, int &endOfNode, QString &res);
};

#endif // PARSER_H
