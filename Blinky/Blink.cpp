#include "Blink.h"
#include "bsp.h"

//............................................................................

Blinky::Blinky()
  : QActive(Q_STATE_CAST(&Blinky::initial)),
    m_timeEvt(TIMEOUT_SIG)
{

  // empty

}

// HSM definition ------------------------------------------------------------

QState Blinky::initial(Blinky * const me, QEvt const * const e) {

  (void)e; // avoid compiler warning about unused argument

  // arm the time event to expire in half a second and every half second
  me->m_timeEvt.postIn(me, BSP_TICKS_PER_SEC / 2U);
  return Q_TRAN(&Blinky::off);

}
QState Blinky::off(Blinky * const me, QEvt const * const e) {

  QState status;

  switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_ledOff();
        me->m_timeEvt.postIn(me, BSP_TICKS_PER_SEC / 2U);
        status = Q_HANDLED();
        break;
      }
    case TIMEOUT_SIG: {
        status = Q_TRAN(&Blinky::on);
        break;
      }
    default: {
        status = Q_SUPER(&QHsm::top);
        break;
      }
  }
  return status;

}

//............................................................................

QState Blinky::on(Blinky * const me, QEvt const * const e) {

  QState status;

  switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_ledOn();
        me->m_timeEvt.postIn(me, BSP_TICKS_PER_SEC / 2U);
        status = Q_HANDLED();
        break;
      }

    case TIMEOUT_SIG: {
        status = Q_TRAN(&Blinky::off);
        break;
      }
    default: {
        status = Q_SUPER(&QHsm::top);
        break;
      }
  }
  return status;
}


