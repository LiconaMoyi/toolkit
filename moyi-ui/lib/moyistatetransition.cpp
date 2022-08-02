#include "moyistatetransition.h"

MoyiStateTransition::MoyiStateTransition(MoyiStateTransitionType type)
    : m_type(type)
{
}

bool MoyiStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    MoyiStateTransitionEvent *transition = static_cast<MoyiStateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void MoyiStateTransition::onTransition(QEvent *)
{
}
