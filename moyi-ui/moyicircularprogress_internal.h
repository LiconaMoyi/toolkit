#ifndef MOYICIRCULARPROGRESS_INTERNAL_H
#define MOYICIRCULARPROGRESS_INTERNAL_H


#include <QObject>
#include "moyicircularprogress.h"

class MoyiCircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    MoyiCircularProgressDelegate(MoyiCircularProgress *parent);
    ~MoyiCircularProgressDelegate();

    inline void setDashOffset(qreal offset);
    inline qreal dashOffset() const;

    inline void setDashLength(qreal length);
    inline qreal dashLength() const;

    inline void setAngle(int angle);
    inline int angle() const;

private:
    Q_DISABLE_COPY(MoyiCircularProgressDelegate)

    MoyiCircularProgress *const m_progress;
    qreal                             m_dashOffset;
    qreal                             m_dashLength;
    int                               m_angle;
};

inline void MoyiCircularProgressDelegate::setDashOffset(qreal offset)
{
    m_dashOffset = offset;
    m_progress->update();
}

inline qreal MoyiCircularProgressDelegate::dashOffset() const
{
    return m_dashOffset;
}

inline void MoyiCircularProgressDelegate::setDashLength(qreal length)
{
    m_dashLength = length;
    m_progress->update();
}

inline qreal MoyiCircularProgressDelegate::dashLength() const
{
    return m_dashLength;
}

inline void MoyiCircularProgressDelegate::setAngle(int angle)
{
    m_angle = angle;
    m_progress->update();
}

inline int MoyiCircularProgressDelegate::angle() const
{
    return m_angle;
}

#endif // MOYICIRCULARPROGRESS_INTERNAL_H
