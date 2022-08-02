#ifndef MOYISTYLE_H
#define MOYISTYLE_H

#include <QtWidgets/QCommonStyle>
#include "moyistyle_p.h"

#define MATERIAL_DISABLE_THEME_COLORS \
    if (d->useThemeColors == true) { d->useThemeColors = false; }

class MoyiTheme;

class MoyiStyle : public QCommonStyle
{
    Q_OBJECT

public:
    inline static MoyiStyle &instance();

    void setTheme(MoyiTheme *theme);
    QColor themeColor(const QString &key) const;

protected:
    const QScopedPointer<MoyiStylePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(MoyiStyle)

    MoyiStyle();

    MoyiStyle(MoyiStyle const &);
    void operator=(MoyiStyle const &);
};

inline MoyiStyle &MoyiStyle::instance()
{
    static MoyiStyle instance;
    return instance;
}
#endif // MOYISTYLE_H
