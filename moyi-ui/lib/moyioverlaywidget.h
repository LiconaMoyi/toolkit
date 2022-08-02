#ifndef MOYIOVERLAYWIDGET_H
#define MOYIOVERLAYWIDGET_H


#include <QtWidgets/QWidget>

class MoyiOverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MoyiOverlayWidget(QWidget *parent = 0);
    ~MoyiOverlayWidget();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    virtual QRect overlayGeometry() const;

private:
    Q_DISABLE_COPY(MoyiOverlayWidget)
};
#endif // MOYIOVERLAYWIDGET_H
