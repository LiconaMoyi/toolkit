#ifndef MOYISTATETRANSITIONEVENT_H
#define MOYISTATETRANSITIONEVENT_H


#include <QEvent>

enum MoyiStateTransitionType {
    // Snackbar
    SnackbarShowTransition = 1,
    SnackbarHideTransition,
    SnackbarWaitTransition,
    SnackbarNextTransition,
    // FlatButton
    FlatButtonPressedTransition,
    FlatButtonCheckedTransition,
    FlatButtonUncheckedTransition,
    // CollapsibleMenu
    CollapsibleMenuExpand,
    CollapsibleMenuCollapse,
    // Slider
    SliderChangedToMinimum,
    SliderChangedFromMinimum,
    SliderNoFocusMouseEnter,
    SliderNoFocusMouseLeave,
    // Dialog
    DialogShowTransition,
    DialogHideTransition,
    //
    MaxTransitionType = 65535
};

struct MoyiStateTransitionEvent : public QEvent
{
    MoyiStateTransitionEvent(MoyiStateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    MoyiStateTransitionType type;
};

#endif // MOYISTATETRANSITIONEVENT_H
