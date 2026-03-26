#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include "include/simple.h"

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded
*/
static struct birthday* make_person_proto(void) {
	struct birthday *person;
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 2;
	person->month = 8;
	person->year = 1995;
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);
	return person;
}

void traverse_list(struct birthday* person) {
	struct birthday* ptr = person;
	list_for_each_entry(ptr, &birthday_list, ptr->list) {
		struct birthday *obj = list_entry(ptr, struct birthday, ptr->list);
		printk(KERN_INFO "what am I looking at %d\n", obj);
	}
	return;
}

static int __init simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	struct birthday *proto_person = make_person_proto();
	traverse_list(proto_person);
	// the newline char at the end will block output for dmesg, be careful
	printk(KERN_INFO "day: %d\n", proto_person->day);
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


