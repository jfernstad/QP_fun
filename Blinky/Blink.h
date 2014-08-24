#include <qp_port.h>

#ifndef __BLINK_H__
#define __BLINK_H__


enum BlinkySignals { // signals for the Blinky application
  TIMEOUT_SIG = 1000//Q_USER_SIG
};

using namespace QP;

class Blinky : public QActive {
  private:
    QTimeEvt m_timeEvt;
  public:
    Blinky();
  protected:
    static QState initial(Blinky * const me, QEvt const * const e);
    static QState off(Blinky * const me, QEvt const * const e);
    static QState on(Blinky * const me, QEvt const * const e);
};

#endif
