#ifndef BIT_MAN_H_
#define BIT_MAN_H_

#define BIT_SET(num, n)      ((num) | (1 << (n)))
#define BIT_CLEAR(num, n)    ((num) & ~(1 << (n)))
#define BIT_TOGGLE(num, n)   ((num) ^ (1 << (n)))
#define BIT_GET(num, n)      (((num) >> (n)) & 1)
#define BIT_VALUE(num, n, v) (!!v) ? BIT_SET(num, n) : BIT_CLEAR(num, n)

#endif /* BIT_MAN_H_ */
