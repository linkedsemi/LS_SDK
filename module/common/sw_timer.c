#include "sw_timer_int.h"
#include "common.h"
#include "cpu.h"
#include "compile_flag.h"
#include "ls_dbg.h"

static struct cdll sw_timer_list;

void sw_timer_callback_set(struct sw_timer_env *timer,bool (*func)(void *),void *param)
{
    timer->callback = func;
    timer->cb_param = param;
}

void sw_timer_period_set(struct sw_timer_env *timer,sw_timer_time_t period)
{
    timer->period = period;
}

sw_timer_time_t sw_timer_period_get(struct sw_timer_env *timer)
{
    return timer->period;
}

void sw_timer_target_set(struct sw_timer_env *timer,sw_timer_time_t target)
{
    timer->target = target;
}

sw_timer_time_t sw_timer_target_get(struct sw_timer_env *timer)
{
    return timer->target;
}

static bool insertion_compare(struct cdll_hdr *ptr,struct cdll_hdr *ref_hdr)
{
    struct sw_timer_env *insert = CONTAINER_OF(ptr,struct sw_timer_env,hdr);
    struct sw_timer_env *ref = CONTAINER_OF(ref_hdr,struct sw_timer_env,hdr);
    return timer_time_compare(insert->target,ref->target)>=0;
}

static void timer_insert(struct sw_timer_env *timer)
{
    cdll_insert(&sw_timer_list,&timer->hdr,insertion_compare);
}

void sw_timer_update()
{
    timer_irq_mask();
    while(1)
    {
        struct cdll_hdr *hdr = cdll_first(&sw_timer_list);
        if(hdr == NULL)
        {
            break;
        }
        struct sw_timer_env *timer = CONTAINER_OF(hdr,struct sw_timer_env,hdr);
        timer_irq_clr();
        timer_match_set(timer->target);
        sw_timer_time_t current = timer_time_get();
        if(timer_time_compare(current,timer->target)>=0)
        {
            cdll_pop_front(&sw_timer_list);
            if(timer->callback(timer->cb_param))
            {
                timer->target = timer_time_add(timer->target,timer->period);
                timer_insert(timer);
            }
        }else
        {
            timer_irq_unmask();
            break;
        }
    }
}

void sw_timer_insert(struct sw_timer_env *timer)
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    timer_insert(timer);
    sw_timer_update();
    EXIT_CRITICAL(cpu_stat);
}

sw_timer_time_t sw_timer_start(struct sw_timer_env *timer)
{
    sw_timer_time_t current = timer_time_get();
    timer->target = timer_time_add(current,timer->period);
    sw_timer_insert(timer);
    return current;
}

void sw_timer_stop(struct sw_timer_env *timer)
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    cdll_extract(&sw_timer_list,&timer->hdr);
    sw_timer_update();
    EXIT_CRITICAL(cpu_stat);
}

bool sw_timer_active(struct sw_timer_env *timer)
{
    return cdll_is_elem_linked(&timer->hdr);
}

LL_EVT_ISR void sw_timer_isr()
{
    sw_timer_update();
}

struct sw_timer_env *sw_timer_list_pick()
{
    struct cdll_hdr *hdr = cdll_first(&sw_timer_list);
    return hdr ? CONTAINER_OF(hdr,struct sw_timer_env,hdr) : NULL;
}

void sw_timer_module_init(void)
{
    timer_setup(sw_timer_isr);
}

void sw_timer_module_reset(void)
{
    cdll_init(&sw_timer_list);
}
