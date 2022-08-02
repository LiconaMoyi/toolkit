#include "moyicircularprogress_internal.h"

/*!
 *  \class MoyiCircularProgressDelegate
 *  \internal
 */

MoyiCircularProgressDelegate::MoyiCircularProgressDelegate(MoyiCircularProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_dashOffset(0),
      m_dashLength(89),
      m_angle(0)
{
    Q_ASSERT(parent);
}

MoyiCircularProgressDelegate::~MoyiCircularProgressDelegate()
{
}
