#ifndef MOYISLIDER_H
#define MOYISLIDER_H



#include <QtWidgets/QAbstractSlider>
#include <QScopedPointer>

#define QT_MATERIAL_SLIDER_MARGIN 30

class MoyiSliderPrivate;

class MoyiSlider : public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)

public:
    explicit MoyiSlider(QWidget *parent = 0);
    ~MoyiSlider();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setThumbColor(const QColor &color);
    QColor thumbColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    void setInvertedAppearance(bool value);

protected:
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

    void updateThumbOffset();

    const QScopedPointer<MoyiSliderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MoyiSlider)
    Q_DECLARE_PRIVATE(MoyiSlider)
};

#endif // MOYISLIDER_H
