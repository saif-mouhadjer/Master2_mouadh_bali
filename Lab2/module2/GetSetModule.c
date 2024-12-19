#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saif");
MODULE_DESCRIPTION("A simple module that get and set data");
MODULE_VERSION("1.0");

static int value = 42;  

module_param(value, int, S_IRUGO);  
MODULE_PARM_DESC(value, "integer value");

static int __init param_module_init(void) {
    printk(KERN_INFO "Set_value = %d\n", value);
    return 0;
}

static void __exit param_module_exit(void) {
    printk(KERN_INFO "Module is empty");
}

module_init(param_module_init);
module_exit(param_module_exit);