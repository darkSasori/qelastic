#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{
    Rule r;

    // number
    r.pattern = QRegExp("([-0-9.]+)(?!([^\"]*\"[\\s]*\\:))");
    r.format.setForeground(QColor(174,129,248));
    rules.append(r);

    //key
    r.pattern = QRegExp ("(\"[^\"]*\")");
    r.format.setForeground(QColor(102,217,239));
    rules.append(r);

    //value
    r.pattern = QRegExp(":\\s*([\"](?:[^\"])*[\"])");
    r.format.setForeground(QColor(220,229,236));
    rules.append(r);

    //reserved words
    r.pattern = QRegExp("(true|false|null)(?!\"[^\"]*\")");
    r.format.setForeground(QColor(142,189,0));
    rules.append(r);
}


void Highlighter::highlightBlock(const QString &text)
{
    foreach (auto r, rules) {
        QRegExp exp(r.pattern);
        auto i = exp.indexIn(text);

        while (i >= 0) {
            i = exp.pos(1);
            auto len = exp.cap(1).length();
            setFormat(i, len, r.format);
            i = exp.indexIn(text, i + len);
        }
    }
}
