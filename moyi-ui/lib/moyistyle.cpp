#include "moyistyle.h"
#include <QFontDatabase>
#include "moyitheme.h"

/*!
 *  \class MoyiStylePrivate
 *  \internal
 */

MoyiStylePrivate::MoyiStylePrivate(MoyiStyle *q)
    : q_ptr(q)
{
}

MoyiStylePrivate::~MoyiStylePrivate()
{
}

void MoyiStylePrivate::init()
{
    Q_Q(MoyiStyle);

    QFontDatabase::addApplicationFont(":/fonts/roboto_regular");
    QFontDatabase::addApplicationFont(":/fonts/roboto_medium");
    QFontDatabase::addApplicationFont(":/fonts/roboto_bold");

    q->setTheme(new MoyiTheme);
}

/*!
 *  \class MoyiStyle
 *  \internal
 */

void MoyiStyle::setTheme(MoyiTheme *theme)
{
    Q_D(MoyiStyle);

    d->theme = theme;
    theme->setParent(this);
}

QColor MoyiStyle::themeColor(const QString &key) const
{
    Q_D(const MoyiStyle);

    Q_ASSERT(d->theme);

    return d->theme->getColor(key);
}

MoyiStyle::MoyiStyle()
    : QCommonStyle(),
      d_ptr(new MoyiStylePrivate(this))
{
    d_func()->init();
}
