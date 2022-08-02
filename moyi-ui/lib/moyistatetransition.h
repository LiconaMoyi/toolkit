#ifndef MOYISTATETRANSITION_H
#define MOYISTATETRANSITION_H


#include <QAbstractTransition>
#include "moyistatetransitionevent.h"

class MoyiStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    MoyiStateTransition(MoyiStateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    MoyiStateTransitionType m_type;
};


#endif // MOYISTATETRANSITION_H
