#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saif");
MODULE_DESCRIPTION("Kernel Module for Managing Linked List");
MODULE_VERSION("1.0");

struct node_item {
    int value;
    struct list_head list;
};

static LIST_HEAD(linked_list_head);

static int __init list_module_init(void)
{
    struct node_item *new_node;
    int idx;

    printk(KERN_INFO "Initializing List Module\n");

    for (idx = 1; idx <= 10; idx++) {
        new_node = kmalloc(sizeof(*new_node), GFP_KERNEL);
        if (!new_node) {
            printk(KERN_ERR "Memory allocation failed for new_node\n");
            return -ENOMEM;
        }
        new_node->value = idx;
        INIT_LIST_HEAD(&new_node->list);
        list_add_tail(&new_node->list, &linked_list_head);
        printk(KERN_INFO "Inserted node with value: %d\n", new_node->value);
    }

    printk(KERN_INFO "Traversing the list:\n");
    list_for_each_entry(new_node, &linked_list_head, list) {
        printk(KERN_INFO "Node value: %d\n", new_node->value);
    }

    return 0;
}

static void __exit list_module_exit(void)
{
    struct node_item *current_node, *temp_node;

    printk(KERN_INFO "Cleaning up List Module\n");

    list_for_each_entry_safe(current_node, temp_node, &linked_list_head, list) {
        printk(KERN_INFO "Removing node with value: %d\n", current_node->value);
        list_del(&current_node->list);
        kfree(current_node);
    }

    printk(KERN_INFO "List Module cleaned up successfully\n");
}

module_init(list_module_init);
module_exit(list_module_exit);
