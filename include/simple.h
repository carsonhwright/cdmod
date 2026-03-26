#include <linux/list.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static struct birthday* make_person_proto(void);
void traverse_list(struct birthday* person);