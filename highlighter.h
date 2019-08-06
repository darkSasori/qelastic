#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>


class Highlighter : public QSyntaxHighlighter
{
public:
    Highlighter(QTextDocument *parent = nullptr);

private:
    struct Rule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<Rule> rules;

protected:
    void highlightBlock(const QString &text) override;
};

#endif // HIGHLIGHTER_H
