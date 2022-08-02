#include "moyicircularprogress.h"
#include "moyicircularprogress_p.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <QPainterPath>
#include "moyicircularprogress_internal.h"
#include "lib/moyistyle.h"

/*!
 *  \class MoyiCircularProgressPrivate
 *  \internal
 */

MoyiCircularProgressPrivate::MoyiCircularProgressPrivate(MoyiCircularProgress *q)
    : q_ptr(q)
{
}

MoyiCircularProgressPrivate::~MoyiCircularProgressPrivate()
{
}

void MoyiCircularProgressPrivate::init()
{
    Q_Q(MoyiCircularProgress);

    delegate       = new MoyiCircularProgressDelegate(q);
    progressType   = Material::IndeterminateProgress;
    penWidth       = 6.25;
    size           = 64;
    useThemeColors = true;

    q->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                                 QSizePolicy::MinimumExpanding));

    QParallelAnimationGroup *group = new QParallelAnimationGroup(q);
    group->setLoopCount(-1);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashLength");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setStartValue(0.1);
    animation->setKeyValueAt(0.15, 0.2);
    animation->setKeyValueAt(0.6, 20);
    animation->setKeyValueAt(0.7, 20);
    animation->setEndValue(20);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashOffset");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setStartValue(0);
    animation->setKeyValueAt(0.15, 0);
    animation->setKeyValueAt(0.6, -7);
    animation->setKeyValueAt(0.7, -7);
    animation->setEndValue(-25);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("angle");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(719);
    animation->setDuration(2050);

    group->addAnimation(animation);

    group->start();
}

/*!
 *  \class MoyiCircularProgress
 */

MoyiCircularProgress::MoyiCircularProgress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new MoyiCircularProgressPrivate(this))
{
    d_func()->init();
}

MoyiCircularProgress::~MoyiCircularProgress()
{
}

void MoyiCircularProgress::setProgressType(Material::ProgressType type)
{
    Q_D(MoyiCircularProgress);

    d->progressType = type;
    update();
}

Material::ProgressType MoyiCircularProgress::progressType() const
{
    Q_D(const MoyiCircularProgress);

    return d->progressType;
}

void MoyiCircularProgress::setUseThemeColors(bool value)
{
    Q_D(MoyiCircularProgress);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool MoyiCircularProgress::useThemeColors() const
{
    Q_D(const MoyiCircularProgress);

    return d->useThemeColors;
}

void MoyiCircularProgress::setLineWidth(qreal width)
{
    Q_D(MoyiCircularProgress);

    d->penWidth = width;
    update();
    updateGeometry();
}

qreal MoyiCircularProgress::lineWidth() const
{
    Q_D(const MoyiCircularProgress);

    return d->penWidth;
}

void MoyiCircularProgress::setSize(int size)
{
    Q_D(MoyiCircularProgress);

    d->size = size;
    update();
    updateGeometry();
}

int MoyiCircularProgress::size() const
{
    Q_D(const MoyiCircularProgress);

    return d->size;
}

void MoyiCircularProgress::setColor(const QColor &color)
{
    Q_D(MoyiCircularProgress);

    d->color = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor MoyiCircularProgress::color() const
{
    Q_D(const MoyiCircularProgress);

    if (d->useThemeColors || !d->color.isValid()) {
        return MoyiStyle::instance().themeColor("primary1");
    } else {
        return d->color;
    }
}

/*!
 *  \reimp
 */
QSize MoyiCircularProgress::sizeHint() const
{
    Q_D(const MoyiCircularProgress);

    const qreal s = d->size+d->penWidth+8;
    return QSize(s, s);
}

/*!
 *  \reimp
 */
void MoyiCircularProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MoyiCircularProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!isEnabled())
    {
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(d->penWidth);
        pen.setColor(MoyiStyle::instance().themeColor("border"));
        painter.setPen(pen);
        painter.drawLine(rect().center()-QPointF(20, 20), rect().center()+QPointF(20, 20));
        painter.drawLine(rect().center()+QPointF(20, -20), rect().center()-QPointF(20, -20));
        return;
    }

    if (Material::IndeterminateProgress == d->progressType)
    {
        painter.translate(width()/2, height()/2);
        painter.rotate(d->delegate->angle());
    }

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(d->penWidth);
    pen.setColor(color());

    if (Material::IndeterminateProgress == d->progressType)
    {
        QVector<qreal> pattern;
        pattern << d->delegate->dashLength()*d->size/50 << 30*d->size/50;

        pen.setDashOffset(d->delegate->dashOffset()*d->size/50);
        pen.setDashPattern(pattern);

        painter.setPen(pen);

        painter.drawEllipse(QPoint(0, 0), d->size/2, d->size/2);
    }
    else
    {
        painter.setPen(pen);

        const qreal x = (width()-d->size)/2;
        const qreal y = (height()-d->size)/2;

        const qreal a = 360*(value()-minimum())/(maximum()-minimum());

        QPainterPath path;
        path.arcMoveTo(x, y, d->size, d->size, 0);
        path.arcTo(x, y, d->size, d->size, 0, a);

        painter.drawPath(path);
    }
}
