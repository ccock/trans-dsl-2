//
// Created by Darwin Yuan on 2020/6/15.
//

#ifndef TRANS_DSL_2_TIMEGUARDHELPER_H
#define TRANS_DSL_2_TIMEGUARDHELPER_H

#include <trans-dsl/sched/action/SchedTimeGuard.h>
#include <trans-dsl/porting/timer/TimerId.h>
#include <trans-dsl/sched/concepts/SchedActionConcept.h>
#include <trans-dsl/porting/timer/PlatformSpecifiedTimer.h>
#include <trans-dsl/utils/ThreadActionTrait.h>

TSL_NS_BEGIN

namespace details {

   template<TimerId V_TIMER_ID, CONCEPT(SchedActionConcept) T_ACTION>
   struct TimeGuard final : SchedTimeGuard{
      CONCEPT_ASSERT(SchedActionConcept<T_ACTION>);
      using ThreadActionCreator = ThreadCreator_t<T_ACTION>;
   private:
      IMPL_ROLE_WITH_VAR(SchedAction, action);
      IMPL_ROLE_WITH_VAR(RelativeTimer, timer);
   private:
      T_ACTION action;
      PlatformSpecifiedTimer timer{V_TIMER_ID};
   };
}

TSL_NS_END

#define __time_guard(timerId, ...) TSL_NS::details::TimeGuard<timerId, __VA_ARGS__>

#endif //TRANS_DSL_2_TIMEGUARDHELPER_H
