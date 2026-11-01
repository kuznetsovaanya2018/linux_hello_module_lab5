#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello2: calls print_hello() from hello1");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "How many times to call print_hello() (default 1)");

static int __init hello2_init(void)
{
	unsigned int i;
	int ret;

	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("hello2: count is %u, continuing anyway\n", count);

	if (count > 10) {
		pr_err("hello2: count %u is greater than 10\n", count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		ret = print_hello();
		if (ret)
			return ret;
	}

	return 0;
}

static void __exit hello2_exit(void)
{
}

module_init(hello2_init);
module_exit(hello2_exit);
