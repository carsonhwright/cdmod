#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include "include/simple.h"

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded
*/
static struct birthday* make_person_proto(void) {
	for (int i = 0; i < 5; i++) {
		struct birthday* person;
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = i + 1;
		person->month = i + 2;
		person->year = 1995 + i;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}
	return list_first_entry(&birthday_list, struct birthday, list);
}

void traverse_list(struct birthday* person) {
	struct birthday *ptr, *n;
	list_for_each_entry_safe(ptr, n, &birthday_list, list) {
		// struct birthday *obj = list_entry(ptr, struct birthday, ptr->list);
		printk(KERN_INFO "Day: %d\n", ptr->day);
		printk(KERN_INFO "Month: %d\n", ptr->month);
		printk(KERN_INFO "Year: %d\n", ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}
	return;
}

static int __init simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	struct birthday *proto_person = make_person_proto();
	traverse_list(proto_person);
	return 0;
}

/* This function is called when the module is removed.
*/
static void __exit simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}


module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("CHW");


