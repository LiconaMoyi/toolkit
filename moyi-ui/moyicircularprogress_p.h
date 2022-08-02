#ifndef MOYICIRCULARPROGRESS_P_H
#define MOYICIRCULARPROGRESS_P_H

#include <QtGlobal>
#include "lib/moyitheme.h"

class MoyiCircularProgress;
class MoyiCircularProgressDelegate;

class MoyiCircularProgressPrivate
{
    Q_DISABLE_COPY(MoyiCircularProgressPrivate)
    Q_DECLARE_PUBLIC(MoyiCircularProgress)

public:
    MoyiCircularProgressPrivate(MoyiCircularProgress *q);
    ~MoyiCircularProgressPrivate();

    void init();

    MoyiCircularProgress         *const q_ptr;
    MoyiCircularProgressDelegate *delegate;
    Material::ProgressType              progressType;
    QColor                              color;
    qreal                               penWidth;
    int                                 size;
    bool                                useThemeColors;
};


#endif // MOYICIRCULARPROGRESS_P_H
