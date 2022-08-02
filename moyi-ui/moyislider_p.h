#ifndef MOYISLIDER_P_H
#define MOYISLIDER_P_H

#include <QtGlobal>
#include <QColor>
#include <QRectF>

class MoyiSlider;
class MoyiSliderThumb;
class MoyiSliderTrack;
class MoyiSliderStateMachine;

class MoyiSliderPrivate
{
    Q_DISABLE_COPY(MoyiSliderPrivate)
    Q_DECLARE_PUBLIC(MoyiSlider)

public:
    MoyiSliderPrivate(MoyiSlider *q);
    ~MoyiSliderPrivate();

    void init();

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    MoyiSlider             *const q_ptr;
    MoyiSliderThumb        *thumb;
    MoyiSliderTrack        *track;
    MoyiSliderStateMachine *stateMachine;
    QColor                        thumbColor;
    QColor                        trackColor;
    QColor                        disabledColor;
    int                           stepTo;
    int                           oldValue;
    int                           trackWidth;
    bool                          hoverTrack;
    bool                          hoverThumb;
    bool                          hover;
    bool                          step;
    bool                          pageStepMode;
    bool                          useThemeColors;
};


#endif // MOYISLIDER_P_H
