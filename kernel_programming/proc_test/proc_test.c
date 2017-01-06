#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define USER_ROOT_DIR   "slndir"
#define USER_ENTRY      "slnfile"

struct proc_dir_entry    *root_dir, *entry;
char                    kbuff[1024];

static int proc_write(struct file *filep, const char __user *buffer,
        unsigned long len, void *data)
{
    if (copy_from_user(kbuff, buffer, len)) {
        return -1;
    }

    kbuff[len] = '\0';
    return len;
}

static int proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    int     len;

    len = sprintf(page, "%s", kbuff);

    return len;
}

static int __init sln_init(void)
{
    printk("Hello, %s\n", __func__);

    root_dir = proc_mkdir(USER_ROOT_DIR, NULL);
    if (NULL == root_dir) {
        printk("proc_mkdir create dir %s failed!\n", USER_ROOT_DIR);
        return -1;
    }

    entry = create_proc_entry(USER_ENTRY, 0666, root_dir);
    if (NULL == entry) {
        printk("create_proc_entry create entry %s failed\n", USER_ENTRY);
        goto err;
    }

    entry->read_proc = proc_read;
    entry->write_proc = proc_write;
    return 0;

err:
    remove_proc_entry(USER_ROOT_DIR, NULL);
    return -1;
}

static void __exit sln_exit(void)
{
    printk("Bye, %s\n", __func__);

    remove_proc_entry(USER_ENTRY, root_dir);
    remove_proc_entry(USER_ROOT_DIR, NULL);
}

module_init(sln_init);
module_exit(sln_exit);

MODULE_LICENSE("GPL");
