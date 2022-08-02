#include "moyislider.h"
#include "moyislider_p.h"
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include "moyislider_internal.h"
#include "lib/moyistyle.h"
#include "lib/moyistatetransitionevent.h"

/*!
 *  \class MoyiSliderPrivate
 *  \internal
 */

MoyiSliderPrivate::MoyiSliderPrivate(MoyiSlider *q)
    : q_ptr(q)
{
}

MoyiSliderPrivate::~MoyiSliderPrivate()
{
}

void MoyiSliderPrivate::init()
{
    Q_Q(MoyiSlider);

    thumb          = new MoyiSliderThumb(q);
    track          = new MoyiSliderTrack(thumb, q);
    stateMachine   = new MoyiSliderStateMachine(q, thumb, track);
    stepTo         = 0;
    oldValue       = q->value();
    trackWidth     = 2;
    hoverTrack     = false;
    hoverThumb     = false;
    hover          = false;
    step           = false;
    pageStepMode   = true;
    useThemeColors = true;

    q->setMouseTracking(true);
    q->setFocusPolicy(Qt::StrongFocus);
    q->setPageStep(1);

    QSizePolicy sp(QSizePolicy::Expanding,
                   QSizePolicy::Fixed);

    if (q->orientation() == Qt::Vertical) {
        sp.transpose();
    }

    q->setSizePolicy(sp);
    q->setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    stateMachine->start();
    QCoreApplication::processEvents();
}

QRectF MoyiSliderPrivate::trackBoundingRect() const
{
    Q_Q(const MoyiSlider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(QT_MATERIAL_SLIDER_MARGIN, q->height()/2 - hw,
                 q->width() - QT_MATERIAL_SLIDER_MARGIN*2, hw*2)
        : QRectF(q->width()/2 - hw, QT_MATERIAL_SLIDER_MARGIN, hw*2,
                 q->height() - QT_MATERIAL_SLIDER_MARGIN*2);
}

QRectF MoyiSliderPrivate::thumbBoundingRect() const
{
    Q_Q(const MoyiSlider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(thumb->offset(), q->height()/2 - QT_MATERIAL_SLIDER_MARGIN,
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2)
        : QRectF(q->width()/2 - QT_MATERIAL_SLIDER_MARGIN, thumb->offset(),
                 QT_MATERIAL_SLIDER_MARGIN*2, QT_MATERIAL_SLIDER_MARGIN*2);
}

int MoyiSliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const MoyiSlider);

    const int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    const int span = Qt::Horizontal == q->orientation()
        ? q->width() - QT_MATERIAL_SLIDER_MARGIN*2
        : q->height() - QT_MATERIAL_SLIDER_MARGIN*2;

    return MoyiStyle::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - QT_MATERIAL_SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

void MoyiSliderPrivate::setHovered(bool status)
{
    Q_Q(MoyiSlider);

    if (hover == status) {
        return;
    }

    hover = status;

    if (!q->hasFocus()) {
        if (status) {
            stateMachine->postEvent(new MoyiStateTransitionEvent(SliderNoFocusMouseEnter));
        } else {
            stateMachine->postEvent(new MoyiStateTransitionEvent(SliderNoFocusMouseLeave));
        }
    }

    q->update();
}

/*!
 *  \class MoyiSlider
 */

MoyiSlider::MoyiSlider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new MoyiSliderPrivate(this))
{
    d_func()->init();
}

MoyiSlider::~MoyiSlider()
{
}

void MoyiSlider::setUseThemeColors(bool value)
{
    Q_D(MoyiSlider);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool MoyiSlider::useThemeColors() const
{
    Q_D(const MoyiSlider);

    return d->useThemeColors;
}

void MoyiSlider::setThumbColor(const QColor &color)
{
    Q_D(MoyiSlider);

    d->thumbColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor MoyiSlider::thumbColor() const
{
    Q_D(const MoyiSlider);

    if (d->useThemeColors || !d->thumbColor.isValid()) {
        return MoyiStyle::instance().themeColor("primary1");
    } else {
        return d->thumbColor;
    }
}

void MoyiSlider::setTrackColor(const QColor &color)
{
    Q_D(MoyiSlider);

    d->trackColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor MoyiSlider::trackColor() const
{
    Q_D(const MoyiSlider);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return MoyiStyle::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void MoyiSlider::setDisabledColor(const QColor &color)
{
    Q_D(MoyiSlider);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
    update();
}

QColor MoyiSlider::disabledColor() const
{
    Q_D(const MoyiSlider);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return MoyiStyle::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void MoyiSlider::setPageStepMode(bool pageStep)
{
    Q_D(MoyiSlider);

    d->pageStepMode = pageStep;
}

bool MoyiSlider::pageStepMode() const
{
    Q_D(const MoyiSlider);

    return d->pageStepMode;
}

/*!
 *  \remip
 */
QSize MoyiSlider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
            ? QSize(130, 34)
            : QSize(34, 130);
}

void MoyiSlider::setInvertedAppearance(bool value)
{
    QAbstractSlider::setInvertedAppearance(value);

    updateThumbOffset();
}

/*!
 *  \remip
 */
void MoyiSlider::sliderChange(SliderChange change)
{
    Q_D(MoyiSlider);

    if (SliderOrientationChange == change)
    {
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (orientation() == Qt::Vertical) {
            sp.transpose();
        }
        setSizePolicy(sp);
    }
    else if (SliderValueChange == change)
    {
        if (minimum() == value()) {
            triggerAction(SliderToMinimum);
            d->stateMachine->postEvent(new MoyiStateTransitionEvent(SliderChangedToMinimum));
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == d->oldValue) {
            d->stateMachine->postEvent(new MoyiStateTransitionEvent(SliderChangedFromMinimum));
        }
        d->oldValue = value();
    }

    updateThumbOffset();

    QAbstractSlider::sliderChange(change);
}

/*!
 *  \remip
 */
void MoyiSlider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(MoyiSlider);

    if (isSliderDown())
    {
        setSliderPosition(d->valueFromPosition(event->pos()));
    }
    else
    {
        QRectF track(d->trackBoundingRect().adjusted(-2, -2, 2, 2));

        if (track.contains(event->pos()) != d->hoverTrack) {
            d->hoverTrack = !d->hoverTrack;
            update();
        }

        QRectF thumb(0, 0, 16, 16);
        thumb.moveCenter(d->thumbBoundingRect().center());

        if (thumb.contains(event->pos()) != d->hoverThumb) {
            d->hoverThumb = !d->hoverThumb;
            update();
        }

        d->setHovered(d->hoverTrack || d->hoverThumb);
    }

    QAbstractSlider::mouseMoveEvent(event);
}

/*!
 *  \remip
 */
void MoyiSlider::mousePressEvent(QMouseEvent *event)
{
    Q_D(MoyiSlider);

    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbBoundingRect().center());

    if (thumb.contains(pos)) {
        setSliderDown(true);
        return;
    }

    if (!d->pageStepMode) {
        setSliderPosition(d->valueFromPosition(event->pos()));
        d->thumb->setHaloSize(0);
        setSliderDown(true);
        return;
    }

    d->step = true;
    d->stepTo = d->valueFromPosition(pos);

    SliderAction action = d->stepTo > sliderPosition()
        ? SliderPageStepAdd
        : SliderPageStepSub;

    triggerAction(action);
    setRepeatAction(action, 400, 8);
}

/*!
 *  \remip
 */
void MoyiSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(MoyiSlider);

    if (isSliderDown()) {
        setSliderDown(false);
    } else if (d->step) {
        d->step = false;
        setRepeatAction(SliderNoAction, 0);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}

/*!
 *  \remip
 */
void MoyiSlider::leaveEvent(QEvent *event)
{
    Q_D(MoyiSlider);

    if (d->hoverTrack) {
        d->hoverTrack = false;
        update();
    }
    if (d->hoverThumb) {
        d->hoverThumb = false;
        update();
    }

    d->setHovered(false);

    QAbstractSlider::leaveEvent(event);
}

void MoyiSlider::updateThumbOffset()
{
    Q_D(MoyiSlider);

    const int offset = MoyiStyle::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - QT_MATERIAL_SLIDER_MARGIN*2
            : height() - QT_MATERIAL_SLIDER_MARGIN*2,
        invertedAppearance());

    d->thumb->setOffset(offset);
}
