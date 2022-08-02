#ifndef MOYITHEME_P_H
#define MOYITHEME_P_H

#include <QHash>
#include <QColor>

class MoyiTheme;

class MoyiThemePrivate
{
    Q_DISABLE_COPY(MoyiThemePrivate)
    Q_DECLARE_PUBLIC(MoyiTheme)

public:
    MoyiThemePrivate(MoyiTheme *q);
    ~MoyiThemePrivate();

    QColor rgba(int r, int g, int b, qreal a) const;

    MoyiTheme *const q_ptr;
    QHash<QString, QColor> colors;
};

#endif // MOYITHEME_P_H
