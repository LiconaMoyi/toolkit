#ifndef MOYISTYLE_P_H
#define MOYISTYLE_P_H

#include <QtGlobal>

class MoyiStyle;
class MoyiTheme;

class MoyiStylePrivate
{
    Q_DISABLE_COPY(MoyiStylePrivate)
    Q_DECLARE_PUBLIC(MoyiStyle)

public:
    MoyiStylePrivate(MoyiStyle *q);
    ~MoyiStylePrivate();

    void init();

    MoyiStyle *const q_ptr;
    MoyiTheme *theme;
};

#endif // MOYISTYLE_P_H
#include <QtGlobal>
