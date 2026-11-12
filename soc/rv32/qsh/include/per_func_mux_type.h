#ifndef PER_FUNC_MUX_TYPE_H_
#define PER_FUNC_MUX_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PINMUX_FUNC1 0
#define PINMUX_FUNC2 1
#define PINMUX_FUNC3 2
#define PINMUX_FUNC4 3

#define PINMUX_FUNC_START PINMUX_FUNC1
#define PINMUX_FUNC_END   PINMUX_FUNC4

#define FUNC1_IDX_MAX  32
#define FUNC_GPIO      (FUNC1_IDX_MAX+1)
#define FUNC_NULL      (FUNC1_IDX_MAX+2)

#ifdef __cplusplus
}
#endif

#endif
